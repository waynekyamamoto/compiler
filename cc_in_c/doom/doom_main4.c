#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <execinfo.h>
#include <SDL2/SDL.h>

#define DOOMGENERIC_RESX 640
#define DOOMGENERIC_RESY 400
#define WINDOW_SCALE 2

typedef unsigned int pixel_t;
pixel_t* DG_ScreenBuffer;

void doomgeneric_Create(int argc, char **argv);
void doomgeneric_Tick(void);

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;
static SDL_AudioDeviceID audio_dev = 0;

static int key_queue[64];
static int key_pressed[64];
static int key_head = 0;
static int key_tail = 0;

/* Sound channel info - must match doom_pp4_clang.c */
#define SDL_SND_CHANNELS 16
#define SDL_SND_RATE 44100

typedef struct {
    unsigned char *data;
    int len;
    int pos;
    int vol;
    int sep;
    int handle;
    void *sfxinfo;
} sdl_channel_t;

sdl_channel_t sdl_channels[SDL_SND_CHANNELS];

/* Accessor functions callable from doom_pp4.c (compiled with custom compiler) */
/* These bridge the ABI gap: our compiler uses 8-byte fields, clang uses real C sizes */
void snd_ch_set(int ch, unsigned char *data, int len, int pos, int vol, int sep, int handle, void *sfx) {
    if (ch < 0 || ch >= SDL_SND_CHANNELS) return;
    sdl_channels[ch].data = data;
    sdl_channels[ch].len = len;
    sdl_channels[ch].pos = pos;
    sdl_channels[ch].vol = vol;
    sdl_channels[ch].sep = sep;
    sdl_channels[ch].handle = handle;
    sdl_channels[ch].sfxinfo = sfx;
}
void snd_ch_clear(int ch) {
    if (ch < 0 || ch >= SDL_SND_CHANNELS) return;
    sdl_channels[ch].data = NULL;
}
void snd_ch_set_vol_sep(int ch, int vol, int sep) {
    if (ch < 0 || ch >= SDL_SND_CHANNELS) return;
    sdl_channels[ch].vol = vol;
    sdl_channels[ch].sep = sep;
}
int snd_ch_is_playing(int ch) {
    if (ch < 0 || ch >= SDL_SND_CHANNELS) return 0;
    return sdl_channels[ch].data != NULL;
}
int snd_ch_get_handle(int ch) {
    if (ch < 0 || ch >= SDL_SND_CHANNELS) return 0;
    return sdl_channels[ch].handle;
}

static void audio_callback(void *userdata, unsigned char *stream, int len) {
    int i, j;
    short *out = (short *)stream;
    int samples = len / 4; /* stereo 16-bit = 4 bytes per sample */

    memset(stream, 0, len);

    for (i = 0; i < SDL_SND_CHANNELS; i++) {
        if (sdl_channels[i].data == NULL)
            continue;

        int vol = sdl_channels[i].vol;
        int sep = sdl_channels[i].sep;
        /* sep: 0=left, 128=center, 255=right */
        int left_vol = ((255 - sep) * vol) / 128;
        int right_vol = (sep * vol) / 128;
        if (left_vol > 255) left_vol = 255;
        if (right_vol > 255) right_vol = 255;

        for (j = 0; j < samples; j++) {
            /* DOOM SFX are typically 11025 Hz, upsample to 44100 */
            int src_pos = sdl_channels[i].pos + (j * 11025 / SDL_SND_RATE);
            if (src_pos >= sdl_channels[i].len) {
                sdl_channels[i].data = NULL;
                break;
            }
            /* unsigned 8-bit PCM -> signed 16-bit */
            int sample = ((int)sdl_channels[i].data[src_pos] - 128) * 256;

            out[j * 2]     += (short)((sample * left_vol) / 256);
            out[j * 2 + 1] += (short)((sample * right_vol) / 256);
        }

        if (sdl_channels[i].data != NULL) {
            sdl_channels[i].pos += samples * 11025 / SDL_SND_RATE;
            if (sdl_channels[i].pos >= sdl_channels[i].len)
                sdl_channels[i].data = NULL;
        }
    }
}

static int sdl_to_doom_key(int sdl_key) {
    switch (sdl_key) {
        case SDLK_RIGHT:    return 0xae;
        case SDLK_LEFT:     return 0xac;
        case SDLK_UP:       return 0xad;
        case SDLK_DOWN:     return 0xaf;
        case SDLK_ESCAPE:   return 27;
        case SDLK_RETURN:   return 13;
        case SDLK_TAB:      return 9;
        case SDLK_SPACE:    return ' ';
        case SDLK_BACKSPACE: return 127;
        case SDLK_RCTRL:
        case SDLK_LCTRL:    return 0x80+0x1d;
        case SDLK_RALT:
        case SDLK_LALT:     return 0x80+0x38;
        case SDLK_RSHIFT:
        case SDLK_LSHIFT:   return 0x80+0x36;
        case SDLK_F1:       return 0x80+0x3b;
        case SDLK_F2:       return 0x80+0x3c;
        case SDLK_F3:       return 0x80+0x3d;
        case SDLK_F4:       return 0x80+0x3e;
        case SDLK_F5:       return 0x80+0x3f;
        case SDLK_F6:       return 0x80+0x40;
        case SDLK_F7:       return 0x80+0x41;
        case SDLK_F8:       return 0x80+0x42;
        case SDLK_F9:       return 0x80+0x43;
        case SDLK_F10:      return 0x80+0x44;
        case SDLK_F11:      return 0x80+0x57;
        case SDLK_F12:      return 0x80+0x58;
        case SDLK_PAUSE:    return 0xff;
        case SDLK_EQUALS:
        case SDLK_PLUS:     return '=';
        case SDLK_MINUS:    return '-';
        default:
            if (sdl_key >= SDLK_a && sdl_key <= SDLK_z)
                return sdl_key - SDLK_a + 'a';
            if (sdl_key >= SDLK_0 && sdl_key <= SDLK_9)
                return sdl_key - SDLK_0 + '0';
            return 0;
    }
}

static void push_key(int pressed, int doom_key) {
    if (doom_key == 0) return;
    int next = (key_head + 1) % 64;
    if (next == key_tail) return;
    key_queue[key_head] = doom_key;
    key_pressed[key_head] = pressed;
    key_head = next;
}

void DG_Init(void) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow("DOOM",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        DOOMGENERIC_RESX * WINDOW_SCALE,
        DOOMGENERIC_RESY * WINDOW_SCALE,
        SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        DOOMGENERIC_RESX, DOOMGENERIC_RESY);

    /* Init audio */
    SDL_AudioSpec want, have;
    memset(&want, 0, sizeof(want));
    want.freq = SDL_SND_RATE;
    want.format = AUDIO_S16SYS;
    want.channels = 2;
    want.samples = 1024;
    want.callback = audio_callback;
    audio_dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (audio_dev > 0) {
        SDL_PauseAudioDevice(audio_dev, 0);
    }
}

void DG_DrawFrame(void) {
    SDL_UpdateTexture(texture, NULL, DG_ScreenBuffer, DOOMGENERIC_RESX * sizeof(pixel_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void DG_SleepMs(unsigned int ms) {
    SDL_Delay(ms);
}

unsigned int DG_GetTicksMs(void) {
    return SDL_GetTicks();
}

int DG_GetKey(int *pressed, unsigned char *key) {
    if (key_tail == key_head) return 0;
    *key = (unsigned char)key_queue[key_tail];
    *pressed = key_pressed[key_tail];
    key_tail = (key_tail + 1) % 64;
    return 1;
}

void DG_SetWindowTitle(const char *title) {
    if (window) SDL_SetWindowTitle(window, title);
}

void handler(int sig) {
    void *bt[30];
    int n = backtrace(bt, 30);
    fprintf(stderr, "Signal %d received. Backtrace:\n", sig);
    backtrace_symbols_fd(bt, n, 2);
    _exit(1);
}

int main(int argc, char **argv) {
    signal(SIGSEGV, handler);
    signal(SIGBUS, handler);
    signal(SIGABRT, handler);

    doomgeneric_Create(argc, argv);

    while (1) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) goto done;
            if (e.type == SDL_KEYDOWN)
                push_key(1, sdl_to_doom_key(e.key.keysym.sym));
            if (e.type == SDL_KEYUP)
                push_key(0, sdl_to_doom_key(e.key.keysym.sym));
        }
        doomgeneric_Tick();
    }
done:
    if (audio_dev > 0) SDL_CloseAudioDevice(audio_dev);
    if (texture) SDL_DestroyTexture(texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
