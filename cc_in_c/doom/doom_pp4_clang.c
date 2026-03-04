
typedef long size_t;
typedef long ssize_t;
typedef long off_t;
typedef int mode_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;
typedef long intptr_t;
typedef unsigned long uintptr_t;
typedef long intmax_t;
typedef unsigned long uintmax_t;
typedef long ptrdiff_t;
typedef long time_t;
int *__error(void);
typedef struct FILE FILE;


extern FILE *__stdinp;
extern FILE *__stdoutp;
extern FILE *__stderrp;





int printf(const char *fmt, ...);
int fprintf(FILE *f, const char *fmt, ...);
int sprintf(char *buf, const char *fmt, ...);
int snprintf(char *buf, size_t n, const char *fmt, ...);
int sscanf(const char *s, const char *fmt, ...);
FILE *fopen(const char *path, const char *mode);
int fclose(FILE *f);
size_t fread(void *ptr, size_t size, size_t n, FILE *f);
size_t fwrite(const void *ptr, size_t size, size_t n, FILE *f);
int fseek(FILE *f, long off, int whence);
long ftell(FILE *f);
int feof(FILE *f);
int fflush(FILE *f);
int fputc(int c, FILE *f);
int fputs(const char *s, FILE *f);
int fgetc(FILE *f);
char *fgets(char *s, int n, FILE *f);
int putchar(int c);
int puts(const char *s);
int remove(const char *path);
int rename(const char *old, const char *new);


void *malloc(size_t size);
void *calloc(size_t n, size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);
void exit(int status);
void abort(void);
int atoi(const char *s);
long atol(const char *s);
long strtol(const char *s, char **endptr, int base);
unsigned long strtoul(const char *s, char **endptr, int base);
int abs(int x);
int rand(void);
void srand(unsigned int seed);
char *getenv(const char *name);


void *memcpy(void *dst, const void *src, size_t n);
void *memmove(void *dst, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
size_t strlen(const char *s);
char *strcpy(char *dst, const char *src);
char *strncpy(char *dst, const char *src, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);
char *strcat(char *dst, const char *src);
char *strncat(char *dst, const char *src, size_t n);
char *strdup(const char *s);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strstr(const char *haystack, const char *needle);
size_t strspn(const char *s, const char *accept);
size_t strcspn(const char *s, const char *reject);
char *strtok(char *s, const char *delim);


int isalpha(int c);
int isdigit(int c);
int isalnum(int c);
int isspace(int c);
int isprint(int c);
int isupper(int c);
int islower(int c);
int isxdigit(int c);
int toupper(int c);
int tolower(int c);


double floor(double x);
double ceil(double x);
double fabs(double x);
double sqrt(double x);
double atan2(double y, double x);
double cos(double x);
double sin(double x);
double log(double x);
double pow(double x, double y);


int open(const char *path, int flags, ...);
int close(int fd);
ssize_t read(int fd, void *buf, size_t n);
ssize_t write(int fd, const void *buf, size_t n);
int mkdir(const char *path, mode_t mode);
int access(const char *path, int mode);
int stat(const char *path, void *buf);
int usleep(unsigned int usec);
unsigned int sleep(unsigned int sec);


struct timeval { long tv_sec; long tv_usec; };
int gettimeofday(struct timeval *tv, void *tz);


typedef __builtin_va_list va_list;
typedef enum
{
    false = 0,
    true = 1,
 undef = 0xFFFFFFFF
} boolean;



typedef uint8_t byte;
boolean net_client_connected = false;

boolean drone = false;
void I_InitTimidityConfig(void)
{
}
typedef struct sha1_context_s sha1_context_t;
typedef byte sha1_digest_t[20];

struct sha1_context_s {
    uint32_t h0,h1,h2,h3,h4;
    uint32_t nblocks;
    byte buf[64];
    int count;
};

void SHA1_Init(sha1_context_t *context);
void SHA1_Update(sha1_context_t *context, byte *buf, size_t len);
void SHA1_Final(sha1_digest_t digest, sha1_context_t *context);
void SHA1_UpdateInt32(sha1_context_t *context, unsigned int val);
void SHA1_UpdateString(sha1_context_t *context, char *str);








void DEH_ParseCommandLine(void);
int DEH_LoadFile(char *filename);
int DEH_LoadLump(int lumpnum, boolean allow_long, boolean allow_error);
int DEH_LoadLumpByName(char *name, boolean allow_long, boolean allow_error);

boolean DEH_ParseAssignment(char *line, char **variable_name, char **value);

void DEH_Checksum(sha1_digest_t digest);

extern boolean deh_allow_extended_strings;
extern boolean deh_allow_long_strings;
extern boolean deh_allow_long_cheats;
extern boolean deh_apply_cheats;

enum
{
    PU_STATIC = 1,
    PU_SOUND,
    PU_MUSIC,
    PU_FREE,
    PU_LEVEL,
    PU_LEVSPEC,



    PU_PURGELEVEL,
    PU_CACHE,



    PU_NUM_TAGS
};


void Z_Init (void);
void* Z_Malloc (int size, int tag, void *ptr);
void Z_Free (void *ptr);
void Z_FreeTags (int lowtag, int hightag);
void Z_DumpHeap (int lowtag, int hightag);
void Z_FileDumpHeap (FILE *f);
void Z_CheckHeap (void);
void Z_ChangeTag2 (void *ptr, int tag, char *file, int line);
void Z_ChangeUser(void *ptr, void **user);
int Z_FreeMemory (void);
unsigned int Z_ZoneSize(void);
int I_GetTime (void);


int I_GetTimeMS (void);


void I_Sleep(int ms);


void I_InitTimer(void);


void I_WaitVBL(int count);
typedef enum
{
    doom,
    doom2,
    pack_tnt,
    pack_plut,
    pack_chex,
    pack_hacx,
    heretic,
    hexen,
    strife,

    none
} GameMission_t;





typedef enum
{
    shareware,
    registered,
    commercial,
    retail,
    indetermined
} GameMode_t;



typedef enum
{
    exe_doom_1_2,
    exe_doom_1_666,
    exe_doom_1_7,
    exe_doom_1_8,
    exe_doom_1_9,
    exe_hacx,
    exe_ultimate,
    exe_final,
    exe_final2,
    exe_chex,

    exe_heretic_1_3,

    exe_hexen_1_1,
    exe_strife_1_2,
    exe_strife_1_31
} GameVersion_t;



typedef enum
{
    sk_noitems = -1,
    sk_baby = 0,
    sk_easy,
    sk_medium,
    sk_hard,
    sk_nightmare
} skill_t;

boolean D_ValidGameMode(GameMission_t mission, GameMode_t mode);
boolean D_ValidGameVersion(GameMission_t mission, GameVersion_t version);
boolean D_ValidEpisodeMap(GameMission_t mission, GameMode_t mode,
                          int episode, int map);
int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode);
boolean D_IsEpisodeMap(GameMission_t mission);
char *D_GameMissionString(GameMission_t mission);
typedef enum
{
    GS_LEVEL,
    GS_INTERMISSION,
    GS_FINALE,
    GS_DEMOSCREEN,
} gamestate_t;

typedef enum
{
    ga_nothing,
    ga_loadlevel,
    ga_newgame,
    ga_loadgame,
    ga_savegame,
    ga_playdemo,
    ga_completed,
    ga_victory,
    ga_worlddone,
    ga_screenshot
} gameaction_t;
typedef enum
{
    it_bluecard,
    it_yellowcard,
    it_redcard,
    it_blueskull,
    it_yellowskull,
    it_redskull,

    NUMCARDS

} card_t;






typedef enum
{
    wp_fist,
    wp_pistol,
    wp_shotgun,
    wp_chaingun,
    wp_missile,
    wp_plasma,
    wp_bfg,
    wp_chainsaw,
    wp_supershotgun,

    NUMWEAPONS,


    wp_nochange

} weapontype_t;



typedef enum
{
    am_clip,
    am_shell,
    am_cell,
    am_misl,
    NUMAMMO,
    am_noammo

} ammotype_t;



typedef enum
{
    pw_invulnerability,
    pw_strength,
    pw_invisibility,
    pw_ironfeet,
    pw_allmap,
    pw_infrared,
    NUMPOWERS

} powertype_t;
typedef enum
{
    INVULNTICS = (30*35),
    INVISTICS = (60*35),
    INFRATICS = (120*35),
    IRONTICS = (60*35)

} powerduration_t;
typedef enum
{
    ev_keydown,
    ev_keyup,
    ev_mouse,
    ev_joystick,
    ev_quit
} evtype_t;


typedef struct
{
    evtype_t type;
    int data1, data2, data3, data4;
} event_t;





typedef enum
{

    BT_ATTACK = 1,

    BT_USE = 2,


    BT_SPECIAL = 128,
    BT_SPECIALMASK = 3,



    BT_CHANGE = 4,

    BT_WEAPONMASK = (8+16+32),
    BT_WEAPONSHIFT = 3,


    BTS_PAUSE = 1,

    BTS_SAVEGAME = 2,



    BTS_SAVEMASK = (4+8+16),
    BTS_SAVESHIFT = 2,

} buttoncode_t;



typedef enum
{

    BT2_LOOKUP = 1,

    BT2_LOOKDOWN = 2,

    BT2_CENTERVIEW = 4,

    BT2_INVUSE = 8,

    BT2_INVDROP = 16,

    BT2_JUMP = 32,

    BT2_HEALTH = 128,

} buttoncode2_t;





void D_PostEvent (event_t *ev);



event_t *D_PopEvent(void);
typedef struct
{


    char sequence[25];
    size_t sequence_len;
    int parameter_chars;



    size_t chars_read;
    int param_chars_read;
    char parameter_buf[5];
} cheatseq_t;

int
cht_CheckCheat
( cheatseq_t* cht,
  char key );


void
cht_GetParam
( cheatseq_t* cht,
  char* buffer );
boolean ST_Responder (event_t* ev);


void ST_Ticker (void);


void ST_Drawer (boolean fullscreen, boolean refresh);


void ST_Start (void);


void ST_Init (void);




typedef enum
{
    AutomapState,
    FirstPersonState

} st_stateenum_t;



typedef enum
{
    StartChatState,
    WaitDestState,
    GetChatState

} st_chatstateenum_t;



extern byte *st_backing_screen;
extern cheatseq_t cheat_mus;
extern cheatseq_t cheat_god;
extern cheatseq_t cheat_ammo;
extern cheatseq_t cheat_ammonokey;
extern cheatseq_t cheat_noclip;
extern cheatseq_t cheat_commercial_noclip;
extern cheatseq_t cheat_powerup[7];
extern cheatseq_t cheat_choppers;
extern cheatseq_t cheat_clev;
extern cheatseq_t cheat_mypos;
typedef int fixed_t;

fixed_t FixedMul (fixed_t a, fixed_t b);
fixed_t FixedDiv (fixed_t a, fixed_t b);
extern const fixed_t finesine[5*8192/4];


extern const fixed_t *finecosine;



extern const fixed_t finetangent[8192/2];


extern const byte gammatable[5][256];
typedef unsigned angle_t;





extern const angle_t tantoangle[2048 +1];




int SlopeDiv(unsigned int num, unsigned int den);





typedef void (*actionf_v)();
typedef void (*actionf_p1)( void* );
typedef void (*actionf_p2)( void*, void* );

typedef union
{
  actionf_v acv;
  actionf_p1 acp1;
  actionf_p2 acp2;

} actionf_t;
typedef actionf_t think_t;



typedef struct thinker_s
{
    struct thinker_s* prev;
    struct thinker_s* next;
    think_t function;

} thinker_t;

enum
{
  ML_LABEL,
  ML_THINGS,
  ML_LINEDEFS,
  ML_SIDEDEFS,
  ML_VERTEXES,
  ML_SEGS,
  ML_SSECTORS,
  ML_NODES,
  ML_SECTORS,
  ML_REJECT,
  ML_BLOCKMAP
};



typedef struct
{
  short x;
  short y;
} __attribute__((packed)) mapvertex_t;




typedef struct
{
  short textureoffset;
  short rowoffset;
  char toptexture[8];
  char bottomtexture[8];
  char midtexture[8];

  short sector;
} __attribute__((packed)) mapsidedef_t;





typedef struct
{
  short v1;
  short v2;
  short flags;
  short special;
  short tag;

  short sidenum[2];
} __attribute__((packed)) maplinedef_t;
typedef struct
{
  short floorheight;
  short ceilingheight;
  char floorpic[8];
  char ceilingpic[8];
  short lightlevel;
  short special;
  short tag;
} __attribute__((packed)) mapsector_t;


typedef struct
{
  short numsegs;

  short firstseg;
} __attribute__((packed)) mapsubsector_t;




typedef struct
{
  short v1;
  short v2;
  short angle;
  short linedef;
  short side;
  short offset;
} __attribute__((packed)) mapseg_t;
typedef struct
{

  short x;
  short y;
  short dx;
  short dy;



  short bbox[2][4];



  unsigned short children[2];

} __attribute__((packed)) mapnode_t;






typedef struct
{
    short x;
    short y;
    short angle;
    short type;
    short options;
} __attribute__((packed)) mapthing_t;




typedef enum
{
    SPR_TROO,
    SPR_SHTG,
    SPR_PUNG,
    SPR_PISG,
    SPR_PISF,
    SPR_SHTF,
    SPR_SHT2,
    SPR_CHGG,
    SPR_CHGF,
    SPR_MISG,
    SPR_MISF,
    SPR_SAWG,
    SPR_PLSG,
    SPR_PLSF,
    SPR_BFGG,
    SPR_BFGF,
    SPR_BLUD,
    SPR_PUFF,
    SPR_BAL1,
    SPR_BAL2,
    SPR_PLSS,
    SPR_PLSE,
    SPR_MISL,
    SPR_BFS1,
    SPR_BFE1,
    SPR_BFE2,
    SPR_TFOG,
    SPR_IFOG,
    SPR_PLAY,
    SPR_POSS,
    SPR_SPOS,
    SPR_VILE,
    SPR_FIRE,
    SPR_FATB,
    SPR_FBXP,
    SPR_SKEL,
    SPR_MANF,
    SPR_FATT,
    SPR_CPOS,
    SPR_SARG,
    SPR_HEAD,
    SPR_BAL7,
    SPR_BOSS,
    SPR_BOS2,
    SPR_SKUL,
    SPR_SPID,
    SPR_BSPI,
    SPR_APLS,
    SPR_APBX,
    SPR_CYBR,
    SPR_PAIN,
    SPR_SSWV,
    SPR_KEEN,
    SPR_BBRN,
    SPR_BOSF,
    SPR_ARM1,
    SPR_ARM2,
    SPR_BAR1,
    SPR_BEXP,
    SPR_FCAN,
    SPR_BON1,
    SPR_BON2,
    SPR_BKEY,
    SPR_RKEY,
    SPR_YKEY,
    SPR_BSKU,
    SPR_RSKU,
    SPR_YSKU,
    SPR_STIM,
    SPR_MEDI,
    SPR_SOUL,
    SPR_PINV,
    SPR_PSTR,
    SPR_PINS,
    SPR_MEGA,
    SPR_SUIT,
    SPR_PMAP,
    SPR_PVIS,
    SPR_CLIP,
    SPR_AMMO,
    SPR_ROCK,
    SPR_BROK,
    SPR_CELL,
    SPR_CELP,
    SPR_SHEL,
    SPR_SBOX,
    SPR_BPAK,
    SPR_BFUG,
    SPR_MGUN,
    SPR_CSAW,
    SPR_LAUN,
    SPR_PLAS,
    SPR_SHOT,
    SPR_SGN2,
    SPR_COLU,
    SPR_SMT2,
    SPR_GOR1,
    SPR_POL2,
    SPR_POL5,
    SPR_POL4,
    SPR_POL3,
    SPR_POL1,
    SPR_POL6,
    SPR_GOR2,
    SPR_GOR3,
    SPR_GOR4,
    SPR_GOR5,
    SPR_SMIT,
    SPR_COL1,
    SPR_COL2,
    SPR_COL3,
    SPR_COL4,
    SPR_CAND,
    SPR_CBRA,
    SPR_COL6,
    SPR_TRE1,
    SPR_TRE2,
    SPR_ELEC,
    SPR_CEYE,
    SPR_FSKU,
    SPR_COL5,
    SPR_TBLU,
    SPR_TGRN,
    SPR_TRED,
    SPR_SMBT,
    SPR_SMGT,
    SPR_SMRT,
    SPR_HDB1,
    SPR_HDB2,
    SPR_HDB3,
    SPR_HDB4,
    SPR_HDB5,
    SPR_HDB6,
    SPR_POB1,
    SPR_POB2,
    SPR_BRS1,
    SPR_TLMP,
    SPR_TLP2,
    NUMSPRITES

} spritenum_t;

typedef enum
{
    S_NULL,
    S_LIGHTDONE,
    S_PUNCH,
    S_PUNCHDOWN,
    S_PUNCHUP,
    S_PUNCH1,
    S_PUNCH2,
    S_PUNCH3,
    S_PUNCH4,
    S_PUNCH5,
    S_PISTOL,
    S_PISTOLDOWN,
    S_PISTOLUP,
    S_PISTOL1,
    S_PISTOL2,
    S_PISTOL3,
    S_PISTOL4,
    S_PISTOLFLASH,
    S_SGUN,
    S_SGUNDOWN,
    S_SGUNUP,
    S_SGUN1,
    S_SGUN2,
    S_SGUN3,
    S_SGUN4,
    S_SGUN5,
    S_SGUN6,
    S_SGUN7,
    S_SGUN8,
    S_SGUN9,
    S_SGUNFLASH1,
    S_SGUNFLASH2,
    S_DSGUN,
    S_DSGUNDOWN,
    S_DSGUNUP,
    S_DSGUN1,
    S_DSGUN2,
    S_DSGUN3,
    S_DSGUN4,
    S_DSGUN5,
    S_DSGUN6,
    S_DSGUN7,
    S_DSGUN8,
    S_DSGUN9,
    S_DSGUN10,
    S_DSNR1,
    S_DSNR2,
    S_DSGUNFLASH1,
    S_DSGUNFLASH2,
    S_CHAIN,
    S_CHAINDOWN,
    S_CHAINUP,
    S_CHAIN1,
    S_CHAIN2,
    S_CHAIN3,
    S_CHAINFLASH1,
    S_CHAINFLASH2,
    S_MISSILE,
    S_MISSILEDOWN,
    S_MISSILEUP,
    S_MISSILE1,
    S_MISSILE2,
    S_MISSILE3,
    S_MISSILEFLASH1,
    S_MISSILEFLASH2,
    S_MISSILEFLASH3,
    S_MISSILEFLASH4,
    S_SAW,
    S_SAWB,
    S_SAWDOWN,
    S_SAWUP,
    S_SAW1,
    S_SAW2,
    S_SAW3,
    S_PLASMA,
    S_PLASMADOWN,
    S_PLASMAUP,
    S_PLASMA1,
    S_PLASMA2,
    S_PLASMAFLASH1,
    S_PLASMAFLASH2,
    S_BFG,
    S_BFGDOWN,
    S_BFGUP,
    S_BFG1,
    S_BFG2,
    S_BFG3,
    S_BFG4,
    S_BFGFLASH1,
    S_BFGFLASH2,
    S_BLOOD1,
    S_BLOOD2,
    S_BLOOD3,
    S_PUFF1,
    S_PUFF2,
    S_PUFF3,
    S_PUFF4,
    S_TBALL1,
    S_TBALL2,
    S_TBALLX1,
    S_TBALLX2,
    S_TBALLX3,
    S_RBALL1,
    S_RBALL2,
    S_RBALLX1,
    S_RBALLX2,
    S_RBALLX3,
    S_PLASBALL,
    S_PLASBALL2,
    S_PLASEXP,
    S_PLASEXP2,
    S_PLASEXP3,
    S_PLASEXP4,
    S_PLASEXP5,
    S_ROCKET,
    S_BFGSHOT,
    S_BFGSHOT2,
    S_BFGLAND,
    S_BFGLAND2,
    S_BFGLAND3,
    S_BFGLAND4,
    S_BFGLAND5,
    S_BFGLAND6,
    S_BFGEXP,
    S_BFGEXP2,
    S_BFGEXP3,
    S_BFGEXP4,
    S_EXPLODE1,
    S_EXPLODE2,
    S_EXPLODE3,
    S_TFOG,
    S_TFOG01,
    S_TFOG02,
    S_TFOG2,
    S_TFOG3,
    S_TFOG4,
    S_TFOG5,
    S_TFOG6,
    S_TFOG7,
    S_TFOG8,
    S_TFOG9,
    S_TFOG10,
    S_IFOG,
    S_IFOG01,
    S_IFOG02,
    S_IFOG2,
    S_IFOG3,
    S_IFOG4,
    S_IFOG5,
    S_PLAY,
    S_PLAY_RUN1,
    S_PLAY_RUN2,
    S_PLAY_RUN3,
    S_PLAY_RUN4,
    S_PLAY_ATK1,
    S_PLAY_ATK2,
    S_PLAY_PAIN,
    S_PLAY_PAIN2,
    S_PLAY_DIE1,
    S_PLAY_DIE2,
    S_PLAY_DIE3,
    S_PLAY_DIE4,
    S_PLAY_DIE5,
    S_PLAY_DIE6,
    S_PLAY_DIE7,
    S_PLAY_XDIE1,
    S_PLAY_XDIE2,
    S_PLAY_XDIE3,
    S_PLAY_XDIE4,
    S_PLAY_XDIE5,
    S_PLAY_XDIE6,
    S_PLAY_XDIE7,
    S_PLAY_XDIE8,
    S_PLAY_XDIE9,
    S_POSS_STND,
    S_POSS_STND2,
    S_POSS_RUN1,
    S_POSS_RUN2,
    S_POSS_RUN3,
    S_POSS_RUN4,
    S_POSS_RUN5,
    S_POSS_RUN6,
    S_POSS_RUN7,
    S_POSS_RUN8,
    S_POSS_ATK1,
    S_POSS_ATK2,
    S_POSS_ATK3,
    S_POSS_PAIN,
    S_POSS_PAIN2,
    S_POSS_DIE1,
    S_POSS_DIE2,
    S_POSS_DIE3,
    S_POSS_DIE4,
    S_POSS_DIE5,
    S_POSS_XDIE1,
    S_POSS_XDIE2,
    S_POSS_XDIE3,
    S_POSS_XDIE4,
    S_POSS_XDIE5,
    S_POSS_XDIE6,
    S_POSS_XDIE7,
    S_POSS_XDIE8,
    S_POSS_XDIE9,
    S_POSS_RAISE1,
    S_POSS_RAISE2,
    S_POSS_RAISE3,
    S_POSS_RAISE4,
    S_SPOS_STND,
    S_SPOS_STND2,
    S_SPOS_RUN1,
    S_SPOS_RUN2,
    S_SPOS_RUN3,
    S_SPOS_RUN4,
    S_SPOS_RUN5,
    S_SPOS_RUN6,
    S_SPOS_RUN7,
    S_SPOS_RUN8,
    S_SPOS_ATK1,
    S_SPOS_ATK2,
    S_SPOS_ATK3,
    S_SPOS_PAIN,
    S_SPOS_PAIN2,
    S_SPOS_DIE1,
    S_SPOS_DIE2,
    S_SPOS_DIE3,
    S_SPOS_DIE4,
    S_SPOS_DIE5,
    S_SPOS_XDIE1,
    S_SPOS_XDIE2,
    S_SPOS_XDIE3,
    S_SPOS_XDIE4,
    S_SPOS_XDIE5,
    S_SPOS_XDIE6,
    S_SPOS_XDIE7,
    S_SPOS_XDIE8,
    S_SPOS_XDIE9,
    S_SPOS_RAISE1,
    S_SPOS_RAISE2,
    S_SPOS_RAISE3,
    S_SPOS_RAISE4,
    S_SPOS_RAISE5,
    S_VILE_STND,
    S_VILE_STND2,
    S_VILE_RUN1,
    S_VILE_RUN2,
    S_VILE_RUN3,
    S_VILE_RUN4,
    S_VILE_RUN5,
    S_VILE_RUN6,
    S_VILE_RUN7,
    S_VILE_RUN8,
    S_VILE_RUN9,
    S_VILE_RUN10,
    S_VILE_RUN11,
    S_VILE_RUN12,
    S_VILE_ATK1,
    S_VILE_ATK2,
    S_VILE_ATK3,
    S_VILE_ATK4,
    S_VILE_ATK5,
    S_VILE_ATK6,
    S_VILE_ATK7,
    S_VILE_ATK8,
    S_VILE_ATK9,
    S_VILE_ATK10,
    S_VILE_ATK11,
    S_VILE_HEAL1,
    S_VILE_HEAL2,
    S_VILE_HEAL3,
    S_VILE_PAIN,
    S_VILE_PAIN2,
    S_VILE_DIE1,
    S_VILE_DIE2,
    S_VILE_DIE3,
    S_VILE_DIE4,
    S_VILE_DIE5,
    S_VILE_DIE6,
    S_VILE_DIE7,
    S_VILE_DIE8,
    S_VILE_DIE9,
    S_VILE_DIE10,
    S_FIRE1,
    S_FIRE2,
    S_FIRE3,
    S_FIRE4,
    S_FIRE5,
    S_FIRE6,
    S_FIRE7,
    S_FIRE8,
    S_FIRE9,
    S_FIRE10,
    S_FIRE11,
    S_FIRE12,
    S_FIRE13,
    S_FIRE14,
    S_FIRE15,
    S_FIRE16,
    S_FIRE17,
    S_FIRE18,
    S_FIRE19,
    S_FIRE20,
    S_FIRE21,
    S_FIRE22,
    S_FIRE23,
    S_FIRE24,
    S_FIRE25,
    S_FIRE26,
    S_FIRE27,
    S_FIRE28,
    S_FIRE29,
    S_FIRE30,
    S_SMOKE1,
    S_SMOKE2,
    S_SMOKE3,
    S_SMOKE4,
    S_SMOKE5,
    S_TRACER,
    S_TRACER2,
    S_TRACEEXP1,
    S_TRACEEXP2,
    S_TRACEEXP3,
    S_SKEL_STND,
    S_SKEL_STND2,
    S_SKEL_RUN1,
    S_SKEL_RUN2,
    S_SKEL_RUN3,
    S_SKEL_RUN4,
    S_SKEL_RUN5,
    S_SKEL_RUN6,
    S_SKEL_RUN7,
    S_SKEL_RUN8,
    S_SKEL_RUN9,
    S_SKEL_RUN10,
    S_SKEL_RUN11,
    S_SKEL_RUN12,
    S_SKEL_FIST1,
    S_SKEL_FIST2,
    S_SKEL_FIST3,
    S_SKEL_FIST4,
    S_SKEL_MISS1,
    S_SKEL_MISS2,
    S_SKEL_MISS3,
    S_SKEL_MISS4,
    S_SKEL_PAIN,
    S_SKEL_PAIN2,
    S_SKEL_DIE1,
    S_SKEL_DIE2,
    S_SKEL_DIE3,
    S_SKEL_DIE4,
    S_SKEL_DIE5,
    S_SKEL_DIE6,
    S_SKEL_RAISE1,
    S_SKEL_RAISE2,
    S_SKEL_RAISE3,
    S_SKEL_RAISE4,
    S_SKEL_RAISE5,
    S_SKEL_RAISE6,
    S_FATSHOT1,
    S_FATSHOT2,
    S_FATSHOTX1,
    S_FATSHOTX2,
    S_FATSHOTX3,
    S_FATT_STND,
    S_FATT_STND2,
    S_FATT_RUN1,
    S_FATT_RUN2,
    S_FATT_RUN3,
    S_FATT_RUN4,
    S_FATT_RUN5,
    S_FATT_RUN6,
    S_FATT_RUN7,
    S_FATT_RUN8,
    S_FATT_RUN9,
    S_FATT_RUN10,
    S_FATT_RUN11,
    S_FATT_RUN12,
    S_FATT_ATK1,
    S_FATT_ATK2,
    S_FATT_ATK3,
    S_FATT_ATK4,
    S_FATT_ATK5,
    S_FATT_ATK6,
    S_FATT_ATK7,
    S_FATT_ATK8,
    S_FATT_ATK9,
    S_FATT_ATK10,
    S_FATT_PAIN,
    S_FATT_PAIN2,
    S_FATT_DIE1,
    S_FATT_DIE2,
    S_FATT_DIE3,
    S_FATT_DIE4,
    S_FATT_DIE5,
    S_FATT_DIE6,
    S_FATT_DIE7,
    S_FATT_DIE8,
    S_FATT_DIE9,
    S_FATT_DIE10,
    S_FATT_RAISE1,
    S_FATT_RAISE2,
    S_FATT_RAISE3,
    S_FATT_RAISE4,
    S_FATT_RAISE5,
    S_FATT_RAISE6,
    S_FATT_RAISE7,
    S_FATT_RAISE8,
    S_CPOS_STND,
    S_CPOS_STND2,
    S_CPOS_RUN1,
    S_CPOS_RUN2,
    S_CPOS_RUN3,
    S_CPOS_RUN4,
    S_CPOS_RUN5,
    S_CPOS_RUN6,
    S_CPOS_RUN7,
    S_CPOS_RUN8,
    S_CPOS_ATK1,
    S_CPOS_ATK2,
    S_CPOS_ATK3,
    S_CPOS_ATK4,
    S_CPOS_PAIN,
    S_CPOS_PAIN2,
    S_CPOS_DIE1,
    S_CPOS_DIE2,
    S_CPOS_DIE3,
    S_CPOS_DIE4,
    S_CPOS_DIE5,
    S_CPOS_DIE6,
    S_CPOS_DIE7,
    S_CPOS_XDIE1,
    S_CPOS_XDIE2,
    S_CPOS_XDIE3,
    S_CPOS_XDIE4,
    S_CPOS_XDIE5,
    S_CPOS_XDIE6,
    S_CPOS_RAISE1,
    S_CPOS_RAISE2,
    S_CPOS_RAISE3,
    S_CPOS_RAISE4,
    S_CPOS_RAISE5,
    S_CPOS_RAISE6,
    S_CPOS_RAISE7,
    S_TROO_STND,
    S_TROO_STND2,
    S_TROO_RUN1,
    S_TROO_RUN2,
    S_TROO_RUN3,
    S_TROO_RUN4,
    S_TROO_RUN5,
    S_TROO_RUN6,
    S_TROO_RUN7,
    S_TROO_RUN8,
    S_TROO_ATK1,
    S_TROO_ATK2,
    S_TROO_ATK3,
    S_TROO_PAIN,
    S_TROO_PAIN2,
    S_TROO_DIE1,
    S_TROO_DIE2,
    S_TROO_DIE3,
    S_TROO_DIE4,
    S_TROO_DIE5,
    S_TROO_XDIE1,
    S_TROO_XDIE2,
    S_TROO_XDIE3,
    S_TROO_XDIE4,
    S_TROO_XDIE5,
    S_TROO_XDIE6,
    S_TROO_XDIE7,
    S_TROO_XDIE8,
    S_TROO_RAISE1,
    S_TROO_RAISE2,
    S_TROO_RAISE3,
    S_TROO_RAISE4,
    S_TROO_RAISE5,
    S_SARG_STND,
    S_SARG_STND2,
    S_SARG_RUN1,
    S_SARG_RUN2,
    S_SARG_RUN3,
    S_SARG_RUN4,
    S_SARG_RUN5,
    S_SARG_RUN6,
    S_SARG_RUN7,
    S_SARG_RUN8,
    S_SARG_ATK1,
    S_SARG_ATK2,
    S_SARG_ATK3,
    S_SARG_PAIN,
    S_SARG_PAIN2,
    S_SARG_DIE1,
    S_SARG_DIE2,
    S_SARG_DIE3,
    S_SARG_DIE4,
    S_SARG_DIE5,
    S_SARG_DIE6,
    S_SARG_RAISE1,
    S_SARG_RAISE2,
    S_SARG_RAISE3,
    S_SARG_RAISE4,
    S_SARG_RAISE5,
    S_SARG_RAISE6,
    S_HEAD_STND,
    S_HEAD_RUN1,
    S_HEAD_ATK1,
    S_HEAD_ATK2,
    S_HEAD_ATK3,
    S_HEAD_PAIN,
    S_HEAD_PAIN2,
    S_HEAD_PAIN3,
    S_HEAD_DIE1,
    S_HEAD_DIE2,
    S_HEAD_DIE3,
    S_HEAD_DIE4,
    S_HEAD_DIE5,
    S_HEAD_DIE6,
    S_HEAD_RAISE1,
    S_HEAD_RAISE2,
    S_HEAD_RAISE3,
    S_HEAD_RAISE4,
    S_HEAD_RAISE5,
    S_HEAD_RAISE6,
    S_BRBALL1,
    S_BRBALL2,
    S_BRBALLX1,
    S_BRBALLX2,
    S_BRBALLX3,
    S_BOSS_STND,
    S_BOSS_STND2,
    S_BOSS_RUN1,
    S_BOSS_RUN2,
    S_BOSS_RUN3,
    S_BOSS_RUN4,
    S_BOSS_RUN5,
    S_BOSS_RUN6,
    S_BOSS_RUN7,
    S_BOSS_RUN8,
    S_BOSS_ATK1,
    S_BOSS_ATK2,
    S_BOSS_ATK3,
    S_BOSS_PAIN,
    S_BOSS_PAIN2,
    S_BOSS_DIE1,
    S_BOSS_DIE2,
    S_BOSS_DIE3,
    S_BOSS_DIE4,
    S_BOSS_DIE5,
    S_BOSS_DIE6,
    S_BOSS_DIE7,
    S_BOSS_RAISE1,
    S_BOSS_RAISE2,
    S_BOSS_RAISE3,
    S_BOSS_RAISE4,
    S_BOSS_RAISE5,
    S_BOSS_RAISE6,
    S_BOSS_RAISE7,
    S_BOS2_STND,
    S_BOS2_STND2,
    S_BOS2_RUN1,
    S_BOS2_RUN2,
    S_BOS2_RUN3,
    S_BOS2_RUN4,
    S_BOS2_RUN5,
    S_BOS2_RUN6,
    S_BOS2_RUN7,
    S_BOS2_RUN8,
    S_BOS2_ATK1,
    S_BOS2_ATK2,
    S_BOS2_ATK3,
    S_BOS2_PAIN,
    S_BOS2_PAIN2,
    S_BOS2_DIE1,
    S_BOS2_DIE2,
    S_BOS2_DIE3,
    S_BOS2_DIE4,
    S_BOS2_DIE5,
    S_BOS2_DIE6,
    S_BOS2_DIE7,
    S_BOS2_RAISE1,
    S_BOS2_RAISE2,
    S_BOS2_RAISE3,
    S_BOS2_RAISE4,
    S_BOS2_RAISE5,
    S_BOS2_RAISE6,
    S_BOS2_RAISE7,
    S_SKULL_STND,
    S_SKULL_STND2,
    S_SKULL_RUN1,
    S_SKULL_RUN2,
    S_SKULL_ATK1,
    S_SKULL_ATK2,
    S_SKULL_ATK3,
    S_SKULL_ATK4,
    S_SKULL_PAIN,
    S_SKULL_PAIN2,
    S_SKULL_DIE1,
    S_SKULL_DIE2,
    S_SKULL_DIE3,
    S_SKULL_DIE4,
    S_SKULL_DIE5,
    S_SKULL_DIE6,
    S_SPID_STND,
    S_SPID_STND2,
    S_SPID_RUN1,
    S_SPID_RUN2,
    S_SPID_RUN3,
    S_SPID_RUN4,
    S_SPID_RUN5,
    S_SPID_RUN6,
    S_SPID_RUN7,
    S_SPID_RUN8,
    S_SPID_RUN9,
    S_SPID_RUN10,
    S_SPID_RUN11,
    S_SPID_RUN12,
    S_SPID_ATK1,
    S_SPID_ATK2,
    S_SPID_ATK3,
    S_SPID_ATK4,
    S_SPID_PAIN,
    S_SPID_PAIN2,
    S_SPID_DIE1,
    S_SPID_DIE2,
    S_SPID_DIE3,
    S_SPID_DIE4,
    S_SPID_DIE5,
    S_SPID_DIE6,
    S_SPID_DIE7,
    S_SPID_DIE8,
    S_SPID_DIE9,
    S_SPID_DIE10,
    S_SPID_DIE11,
    S_BSPI_STND,
    S_BSPI_STND2,
    S_BSPI_SIGHT,
    S_BSPI_RUN1,
    S_BSPI_RUN2,
    S_BSPI_RUN3,
    S_BSPI_RUN4,
    S_BSPI_RUN5,
    S_BSPI_RUN6,
    S_BSPI_RUN7,
    S_BSPI_RUN8,
    S_BSPI_RUN9,
    S_BSPI_RUN10,
    S_BSPI_RUN11,
    S_BSPI_RUN12,
    S_BSPI_ATK1,
    S_BSPI_ATK2,
    S_BSPI_ATK3,
    S_BSPI_ATK4,
    S_BSPI_PAIN,
    S_BSPI_PAIN2,
    S_BSPI_DIE1,
    S_BSPI_DIE2,
    S_BSPI_DIE3,
    S_BSPI_DIE4,
    S_BSPI_DIE5,
    S_BSPI_DIE6,
    S_BSPI_DIE7,
    S_BSPI_RAISE1,
    S_BSPI_RAISE2,
    S_BSPI_RAISE3,
    S_BSPI_RAISE4,
    S_BSPI_RAISE5,
    S_BSPI_RAISE6,
    S_BSPI_RAISE7,
    S_ARACH_PLAZ,
    S_ARACH_PLAZ2,
    S_ARACH_PLEX,
    S_ARACH_PLEX2,
    S_ARACH_PLEX3,
    S_ARACH_PLEX4,
    S_ARACH_PLEX5,
    S_CYBER_STND,
    S_CYBER_STND2,
    S_CYBER_RUN1,
    S_CYBER_RUN2,
    S_CYBER_RUN3,
    S_CYBER_RUN4,
    S_CYBER_RUN5,
    S_CYBER_RUN6,
    S_CYBER_RUN7,
    S_CYBER_RUN8,
    S_CYBER_ATK1,
    S_CYBER_ATK2,
    S_CYBER_ATK3,
    S_CYBER_ATK4,
    S_CYBER_ATK5,
    S_CYBER_ATK6,
    S_CYBER_PAIN,
    S_CYBER_DIE1,
    S_CYBER_DIE2,
    S_CYBER_DIE3,
    S_CYBER_DIE4,
    S_CYBER_DIE5,
    S_CYBER_DIE6,
    S_CYBER_DIE7,
    S_CYBER_DIE8,
    S_CYBER_DIE9,
    S_CYBER_DIE10,
    S_PAIN_STND,
    S_PAIN_RUN1,
    S_PAIN_RUN2,
    S_PAIN_RUN3,
    S_PAIN_RUN4,
    S_PAIN_RUN5,
    S_PAIN_RUN6,
    S_PAIN_ATK1,
    S_PAIN_ATK2,
    S_PAIN_ATK3,
    S_PAIN_ATK4,
    S_PAIN_PAIN,
    S_PAIN_PAIN2,
    S_PAIN_DIE1,
    S_PAIN_DIE2,
    S_PAIN_DIE3,
    S_PAIN_DIE4,
    S_PAIN_DIE5,
    S_PAIN_DIE6,
    S_PAIN_RAISE1,
    S_PAIN_RAISE2,
    S_PAIN_RAISE3,
    S_PAIN_RAISE4,
    S_PAIN_RAISE5,
    S_PAIN_RAISE6,
    S_SSWV_STND,
    S_SSWV_STND2,
    S_SSWV_RUN1,
    S_SSWV_RUN2,
    S_SSWV_RUN3,
    S_SSWV_RUN4,
    S_SSWV_RUN5,
    S_SSWV_RUN6,
    S_SSWV_RUN7,
    S_SSWV_RUN8,
    S_SSWV_ATK1,
    S_SSWV_ATK2,
    S_SSWV_ATK3,
    S_SSWV_ATK4,
    S_SSWV_ATK5,
    S_SSWV_ATK6,
    S_SSWV_PAIN,
    S_SSWV_PAIN2,
    S_SSWV_DIE1,
    S_SSWV_DIE2,
    S_SSWV_DIE3,
    S_SSWV_DIE4,
    S_SSWV_DIE5,
    S_SSWV_XDIE1,
    S_SSWV_XDIE2,
    S_SSWV_XDIE3,
    S_SSWV_XDIE4,
    S_SSWV_XDIE5,
    S_SSWV_XDIE6,
    S_SSWV_XDIE7,
    S_SSWV_XDIE8,
    S_SSWV_XDIE9,
    S_SSWV_RAISE1,
    S_SSWV_RAISE2,
    S_SSWV_RAISE3,
    S_SSWV_RAISE4,
    S_SSWV_RAISE5,
    S_KEENSTND,
    S_COMMKEEN,
    S_COMMKEEN2,
    S_COMMKEEN3,
    S_COMMKEEN4,
    S_COMMKEEN5,
    S_COMMKEEN6,
    S_COMMKEEN7,
    S_COMMKEEN8,
    S_COMMKEEN9,
    S_COMMKEEN10,
    S_COMMKEEN11,
    S_COMMKEEN12,
    S_KEENPAIN,
    S_KEENPAIN2,
    S_BRAIN,
    S_BRAIN_PAIN,
    S_BRAIN_DIE1,
    S_BRAIN_DIE2,
    S_BRAIN_DIE3,
    S_BRAIN_DIE4,
    S_BRAINEYE,
    S_BRAINEYESEE,
    S_BRAINEYE1,
    S_SPAWN1,
    S_SPAWN2,
    S_SPAWN3,
    S_SPAWN4,
    S_SPAWNFIRE1,
    S_SPAWNFIRE2,
    S_SPAWNFIRE3,
    S_SPAWNFIRE4,
    S_SPAWNFIRE5,
    S_SPAWNFIRE6,
    S_SPAWNFIRE7,
    S_SPAWNFIRE8,
    S_BRAINEXPLODE1,
    S_BRAINEXPLODE2,
    S_BRAINEXPLODE3,
    S_ARM1,
    S_ARM1A,
    S_ARM2,
    S_ARM2A,
    S_BAR1,
    S_BAR2,
    S_BEXP,
    S_BEXP2,
    S_BEXP3,
    S_BEXP4,
    S_BEXP5,
    S_BBAR1,
    S_BBAR2,
    S_BBAR3,
    S_BON1,
    S_BON1A,
    S_BON1B,
    S_BON1C,
    S_BON1D,
    S_BON1E,
    S_BON2,
    S_BON2A,
    S_BON2B,
    S_BON2C,
    S_BON2D,
    S_BON2E,
    S_BKEY,
    S_BKEY2,
    S_RKEY,
    S_RKEY2,
    S_YKEY,
    S_YKEY2,
    S_BSKULL,
    S_BSKULL2,
    S_RSKULL,
    S_RSKULL2,
    S_YSKULL,
    S_YSKULL2,
    S_STIM,
    S_MEDI,
    S_SOUL,
    S_SOUL2,
    S_SOUL3,
    S_SOUL4,
    S_SOUL5,
    S_SOUL6,
    S_PINV,
    S_PINV2,
    S_PINV3,
    S_PINV4,
    S_PSTR,
    S_PINS,
    S_PINS2,
    S_PINS3,
    S_PINS4,
    S_MEGA,
    S_MEGA2,
    S_MEGA3,
    S_MEGA4,
    S_SUIT,
    S_PMAP,
    S_PMAP2,
    S_PMAP3,
    S_PMAP4,
    S_PMAP5,
    S_PMAP6,
    S_PVIS,
    S_PVIS2,
    S_CLIP,
    S_AMMO,
    S_ROCK,
    S_BROK,
    S_CELL,
    S_CELP,
    S_SHEL,
    S_SBOX,
    S_BPAK,
    S_BFUG,
    S_MGUN,
    S_CSAW,
    S_LAUN,
    S_PLAS,
    S_SHOT,
    S_SHOT2,
    S_COLU,
    S_STALAG,
    S_BLOODYTWITCH,
    S_BLOODYTWITCH2,
    S_BLOODYTWITCH3,
    S_BLOODYTWITCH4,
    S_DEADTORSO,
    S_DEADBOTTOM,
    S_HEADSONSTICK,
    S_GIBS,
    S_HEADONASTICK,
    S_HEADCANDLES,
    S_HEADCANDLES2,
    S_DEADSTICK,
    S_LIVESTICK,
    S_LIVESTICK2,
    S_MEAT2,
    S_MEAT3,
    S_MEAT4,
    S_MEAT5,
    S_STALAGTITE,
    S_TALLGRNCOL,
    S_SHRTGRNCOL,
    S_TALLREDCOL,
    S_SHRTREDCOL,
    S_CANDLESTIK,
    S_CANDELABRA,
    S_SKULLCOL,
    S_TORCHTREE,
    S_BIGTREE,
    S_TECHPILLAR,
    S_EVILEYE,
    S_EVILEYE2,
    S_EVILEYE3,
    S_EVILEYE4,
    S_FLOATSKULL,
    S_FLOATSKULL2,
    S_FLOATSKULL3,
    S_HEARTCOL,
    S_HEARTCOL2,
    S_BLUETORCH,
    S_BLUETORCH2,
    S_BLUETORCH3,
    S_BLUETORCH4,
    S_GREENTORCH,
    S_GREENTORCH2,
    S_GREENTORCH3,
    S_GREENTORCH4,
    S_REDTORCH,
    S_REDTORCH2,
    S_REDTORCH3,
    S_REDTORCH4,
    S_BTORCHSHRT,
    S_BTORCHSHRT2,
    S_BTORCHSHRT3,
    S_BTORCHSHRT4,
    S_GTORCHSHRT,
    S_GTORCHSHRT2,
    S_GTORCHSHRT3,
    S_GTORCHSHRT4,
    S_RTORCHSHRT,
    S_RTORCHSHRT2,
    S_RTORCHSHRT3,
    S_RTORCHSHRT4,
    S_HANGNOGUTS,
    S_HANGBNOBRAIN,
    S_HANGTLOOKDN,
    S_HANGTSKULL,
    S_HANGTLOOKUP,
    S_HANGTNOBRAIN,
    S_COLONGIBS,
    S_SMALLPOOL,
    S_BRAINSTEM,
    S_TECHLAMP,
    S_TECHLAMP2,
    S_TECHLAMP3,
    S_TECHLAMP4,
    S_TECH2LAMP,
    S_TECH2LAMP2,
    S_TECH2LAMP3,
    S_TECH2LAMP4,
    NUMSTATES
} statenum_t;


typedef struct
{
    spritenum_t sprite;
    int frame;
    int tics;

    actionf_t action;
    statenum_t nextstate;
    int misc1;
    int misc2;
} state_t;

extern state_t states[NUMSTATES];
extern char *sprnames[];

typedef enum {
    MT_PLAYER,
    MT_POSSESSED,
    MT_SHOTGUY,
    MT_VILE,
    MT_FIRE,
    MT_UNDEAD,
    MT_TRACER,
    MT_SMOKE,
    MT_FATSO,
    MT_FATSHOT,
    MT_CHAINGUY,
    MT_TROOP,
    MT_SERGEANT,
    MT_SHADOWS,
    MT_HEAD,
    MT_BRUISER,
    MT_BRUISERSHOT,
    MT_KNIGHT,
    MT_SKULL,
    MT_SPIDER,
    MT_BABY,
    MT_CYBORG,
    MT_PAIN,
    MT_WOLFSS,
    MT_KEEN,
    MT_BOSSBRAIN,
    MT_BOSSSPIT,
    MT_BOSSTARGET,
    MT_SPAWNSHOT,
    MT_SPAWNFIRE,
    MT_BARREL,
    MT_TROOPSHOT,
    MT_HEADSHOT,
    MT_ROCKET,
    MT_PLASMA,
    MT_BFG,
    MT_ARACHPLAZ,
    MT_PUFF,
    MT_BLOOD,
    MT_TFOG,
    MT_IFOG,
    MT_TELEPORTMAN,
    MT_EXTRABFG,
    MT_MISC0,
    MT_MISC1,
    MT_MISC2,
    MT_MISC3,
    MT_MISC4,
    MT_MISC5,
    MT_MISC6,
    MT_MISC7,
    MT_MISC8,
    MT_MISC9,
    MT_MISC10,
    MT_MISC11,
    MT_MISC12,
    MT_INV,
    MT_MISC13,
    MT_INS,
    MT_MISC14,
    MT_MISC15,
    MT_MISC16,
    MT_MEGA,
    MT_CLIP,
    MT_MISC17,
    MT_MISC18,
    MT_MISC19,
    MT_MISC20,
    MT_MISC21,
    MT_MISC22,
    MT_MISC23,
    MT_MISC24,
    MT_MISC25,
    MT_CHAINGUN,
    MT_MISC26,
    MT_MISC27,
    MT_MISC28,
    MT_SHOTGUN,
    MT_SUPERSHOTGUN,
    MT_MISC29,
    MT_MISC30,
    MT_MISC31,
    MT_MISC32,
    MT_MISC33,
    MT_MISC34,
    MT_MISC35,
    MT_MISC36,
    MT_MISC37,
    MT_MISC38,
    MT_MISC39,
    MT_MISC40,
    MT_MISC41,
    MT_MISC42,
    MT_MISC43,
    MT_MISC44,
    MT_MISC45,
    MT_MISC46,
    MT_MISC47,
    MT_MISC48,
    MT_MISC49,
    MT_MISC50,
    MT_MISC51,
    MT_MISC52,
    MT_MISC53,
    MT_MISC54,
    MT_MISC55,
    MT_MISC56,
    MT_MISC57,
    MT_MISC58,
    MT_MISC59,
    MT_MISC60,
    MT_MISC61,
    MT_MISC62,
    MT_MISC63,
    MT_MISC64,
    MT_MISC65,
    MT_MISC66,
    MT_MISC67,
    MT_MISC68,
    MT_MISC69,
    MT_MISC70,
    MT_MISC71,
    MT_MISC72,
    MT_MISC73,
    MT_MISC74,
    MT_MISC75,
    MT_MISC76,
    MT_MISC77,
    MT_MISC78,
    MT_MISC79,
    MT_MISC80,
    MT_MISC81,
    MT_MISC82,
    MT_MISC83,
    MT_MISC84,
    MT_MISC85,
    MT_MISC86,
    NUMMOBJTYPES

} mobjtype_t;

typedef struct
{
    int doomednum;
    int spawnstate;
    int spawnhealth;
    int seestate;
    int seesound;
    int reactiontime;
    int attacksound;
    int painstate;
    int painchance;
    int painsound;
    int meleestate;
    int missilestate;
    int deathstate;
    int xdeathstate;
    int deathsound;
    int speed;
    int radius;
    int height;
    int mass;
    int damage;
    int activesound;
    int flags;
    int raisestate;

} mobjinfo_t;

extern mobjinfo_t mobjinfo[NUMMOBJTYPES];
typedef enum
{

    MF_SPECIAL = 1,

    MF_SOLID = 2,

    MF_SHOOTABLE = 4,

    MF_NOSECTOR = 8,

    MF_NOBLOCKMAP = 16,


    MF_AMBUSH = 32,

    MF_JUSTHIT = 64,

    MF_JUSTATTACKED = 128,


    MF_SPAWNCEILING = 256,



    MF_NOGRAVITY = 512,



    MF_DROPOFF = 0x400,

    MF_PICKUP = 0x800,

    MF_NOCLIP = 0x1000,

    MF_SLIDE = 0x2000,


    MF_FLOAT = 0x4000,


    MF_TELEPORT = 0x8000,


    MF_MISSILE = 0x10000,


    MF_DROPPED = 0x20000,


    MF_SHADOW = 0x40000,


    MF_NOBLOOD = 0x80000,


    MF_CORPSE = 0x100000,


    MF_INFLOAT = 0x200000,




    MF_COUNTKILL = 0x400000,



    MF_COUNTITEM = 0x800000,



    MF_SKULLFLY = 0x1000000,



    MF_NOTDMATCH = 0x2000000,





    MF_TRANSLATION = 0xc000000,

    MF_TRANSSHIFT = 26

} mobjflag_t;



typedef struct mobj_s
{

    thinker_t thinker;


    fixed_t x;
    fixed_t y;
    fixed_t z;


    struct mobj_s* snext;
    struct mobj_s* sprev;


    angle_t angle;
    spritenum_t sprite;
    int frame;



    struct mobj_s* bnext;
    struct mobj_s* bprev;

    struct subsector_s* subsector;


    fixed_t floorz;
    fixed_t ceilingz;


    fixed_t radius;
    fixed_t height;


    fixed_t momx;
    fixed_t momy;
    fixed_t momz;


    int validcount;

    mobjtype_t type;
    mobjinfo_t* info;

    int tics;
    state_t* state;
    int flags;
    int health;


    int movedir;
    int movecount;



    struct mobj_s* target;



    int reactiontime;



    int threshold;



    struct player_s* player;


    int lastlook;


    mapthing_t spawnpoint;


    struct mobj_s* tracer;

} mobj_t;

typedef struct
{


    int width;
    int height;






    void (*InitMode)(byte *palette);




    boolean (*DrawScreen)(int x1, int y1, int x2, int y2);
    boolean poor_quality;
} screen_mode_t;

typedef boolean (*grabmouse_callback_t)(void);




void I_InitGraphics (void);

void I_GraphicsCheckCommandLine(void);

void I_ShutdownGraphics(void);


void I_SetPalette (byte* palette);
int I_GetPaletteIndex(int r, int g, int b);

void I_UpdateNoBlit (void);
void I_FinishUpdate (void);

void I_ReadScreen (byte* scr);

void I_BeginRead (void);

void I_SetWindowTitle(char *title);

void I_CheckIsScreensaver(void);
void I_SetGrabMouseCallback(grabmouse_callback_t func);

void I_DisplayFPSDots(boolean dots_on);
void I_BindVideoVariables(void);

void I_InitWindowTitle(void);
void I_InitWindowIcon(void);




void I_StartFrame (void);




void I_StartTic (void);



void I_EnableLoadingDisk(void);

void I_EndRead (void);

struct color {
    uint32_t b:8;
    uint32_t g:8;
    uint32_t r:8;
    uint32_t a:8;
};


extern char *video_driver;
extern boolean screenvisible;

extern float mouse_acceleration;
extern int mouse_threshold;
extern int vanilla_keyboard_mapping;
extern boolean screensaver_mode;
extern int usegamma;
extern byte *I_VideoBuffer;

extern int screen_width;
extern int screen_height;
extern int screen_bpp;
extern int fullscreen;
extern int aspect_ratio_correct;

extern int show_diskicon;
extern int diskicon_readbytes;

typedef struct
{
    short width;
    short height;
    short leftoffset;
    short topoffset;
    int columnofs[8];

} __attribute__((packed)) patch_t;


typedef struct
{
    byte topdelta;
    byte length;
} __attribute__((packed)) post_t;


typedef post_t column_t;
typedef struct
{
    fixed_t x;
    fixed_t y;

} vertex_t;



struct line_s;







typedef struct
{
    thinker_t thinker;
    fixed_t x;
    fixed_t y;
    fixed_t z;

} degenmobj_t;





typedef struct
{
    fixed_t floorheight;
    fixed_t ceilingheight;
    short floorpic;
    short ceilingpic;
    short lightlevel;
    short special;
    short tag;


    int soundtraversed;


    mobj_t* soundtarget;


    int blockbox[4];


    degenmobj_t soundorg;


    int validcount;


    mobj_t* thinglist;


    void* specialdata;

    int linecount;
    struct line_s** lines;

} sector_t;
typedef struct
{

    fixed_t textureoffset;


    fixed_t rowoffset;



    short toptexture;
    short bottomtexture;
    short midtexture;


    sector_t* sector;

} side_t;






typedef enum
{
    ST_HORIZONTAL,
    ST_VERTICAL,
    ST_POSITIVE,
    ST_NEGATIVE

} slopetype_t;



typedef struct line_s
{

    vertex_t* v1;
    vertex_t* v2;


    fixed_t dx;
    fixed_t dy;


    short flags;
    short special;
    short tag;



    short sidenum[2];



    fixed_t bbox[4];


    slopetype_t slopetype;



    sector_t* frontsector;
    sector_t* backsector;


    int validcount;


    void* specialdata;
} line_t;
typedef struct subsector_s
{
    sector_t* sector;
    short numlines;
    short firstline;

} subsector_t;






typedef struct
{
    vertex_t* v1;
    vertex_t* v2;

    fixed_t offset;

    angle_t angle;

    side_t* sidedef;
    line_t* linedef;




    sector_t* frontsector;
    sector_t* backsector;

} seg_t;






typedef struct
{

    fixed_t x;
    fixed_t y;
    fixed_t dx;
    fixed_t dy;


    fixed_t bbox[2][4];


    unsigned short children[2];

} node_t;
typedef byte lighttable_t;







typedef struct drawseg_s
{
    seg_t* curline;
    int x1;
    int x2;

    fixed_t scale1;
    fixed_t scale2;
    fixed_t scalestep;


    int silhouette;


    fixed_t bsilheight;


    fixed_t tsilheight;



    short* sprtopclip;
    short* sprbottomclip;
    short* maskedtexturecol;

} drawseg_t;






typedef struct vissprite_s
{

    struct vissprite_s* prev;
    struct vissprite_s* next;

    int x1;
    int x2;


    fixed_t gx;
    fixed_t gy;


    fixed_t gz;
    fixed_t gzt;


    fixed_t startfrac;

    fixed_t scale;


    fixed_t xiscale;

    fixed_t texturemid;
    int patch;



    lighttable_t* colormap;

    int mobjflags;

} vissprite_t;
typedef struct
{



    boolean rotate;


    short lump[8];


    byte flip[8];

} spriteframe_t;







typedef struct
{
    int numframes;
    spriteframe_t* spriteframes;

} spritedef_t;






typedef struct
{
  fixed_t height;
  int picnum;
  int lightlevel;
  int minx;
  int maxx;



  byte pad1;


  byte top[320];
  byte pad2;
  byte pad3;

  byte bottom[320];
  byte pad4;

} visplane_t;
typedef struct
{
    ammotype_t ammo;
    int upstate;
    int downstate;
    int readystate;
    int atkstate;
    int flashstate;

} weaponinfo_t;

extern weaponinfo_t weaponinfo[NUMWEAPONS];
typedef enum
{
    ps_weapon,
    ps_flash,
    NUMPSPRITES

} psprnum_t;

typedef struct
{
    state_t* state;
    int tics;
    fixed_t sx;
    fixed_t sy;

} pspdef_t;








typedef struct
{
    signed char forwardmove;
    signed char sidemove;
    short angleturn;
    byte chatchar;
    byte buttons;


    byte consistancy;



    byte buttons2;
    int inventory;



    byte lookfly;
    byte arti;
} ticcmd_t;

typedef struct _net_module_s net_module_t;
typedef struct _net_packet_s net_packet_t;
typedef struct _net_addr_s net_addr_t;
typedef struct _net_context_s net_context_t;

struct _net_packet_s
{
    byte *data;
    size_t len;
    size_t alloced;
    unsigned int pos;
};

struct _net_module_s
{


    boolean (*InitClient)(void);



    boolean (*InitServer)(void);



    void (*SendPacket)(net_addr_t *addr, net_packet_t *packet);





    boolean (*RecvPacket)(net_addr_t **addr, net_packet_t **packet);



    void (*AddrToString)(net_addr_t *addr, char *buffer, int buffer_len);



    void (*FreeAddress)(net_addr_t *addr);



    net_addr_t *(*ResolveAddress)(char *addr);
};



struct _net_addr_s
{
    net_module_t *module;
    void *handle;
};
typedef enum
{
    NET_PACKET_TYPE_SYN,
    NET_PACKET_TYPE_ACK,
    NET_PACKET_TYPE_REJECTED,
    NET_PACKET_TYPE_KEEPALIVE,
    NET_PACKET_TYPE_WAITING_DATA,
    NET_PACKET_TYPE_GAMESTART,
    NET_PACKET_TYPE_GAMEDATA,
    NET_PACKET_TYPE_GAMEDATA_ACK,
    NET_PACKET_TYPE_DISCONNECT,
    NET_PACKET_TYPE_DISCONNECT_ACK,
    NET_PACKET_TYPE_RELIABLE_ACK,
    NET_PACKET_TYPE_GAMEDATA_RESEND,
    NET_PACKET_TYPE_CONSOLE_MESSAGE,
    NET_PACKET_TYPE_QUERY,
    NET_PACKET_TYPE_QUERY_RESPONSE,
    NET_PACKET_TYPE_LAUNCH,
} net_packet_type_t;

typedef enum
{
    NET_MASTER_PACKET_TYPE_ADD,
    NET_MASTER_PACKET_TYPE_ADD_RESPONSE,
    NET_MASTER_PACKET_TYPE_QUERY,
    NET_MASTER_PACKET_TYPE_QUERY_RESPONSE,
    NET_MASTER_PACKET_TYPE_GET_METADATA,
    NET_MASTER_PACKET_TYPE_GET_METADATA_RESPONSE,
    NET_MASTER_PACKET_TYPE_SIGN_START,
    NET_MASTER_PACKET_TYPE_SIGN_START_RESPONSE,
    NET_MASTER_PACKET_TYPE_SIGN_END,
    NET_MASTER_PACKET_TYPE_SIGN_END_RESPONSE,
} net_master_packet_type_t;



typedef struct
{
    int gamemode;
    int gamemission;
    int lowres_turn;
    int drone;
    int max_players;
    int is_freedoom;
    sha1_digest_t wad_sha1sum;
    sha1_digest_t deh_sha1sum;
    int player_class;
} net_connect_data_t;




typedef struct
{
    int ticdup;
    int extratics;
    int deathmatch;
    int episode;
    int nomonsters;
    int fast_monsters;
    int respawn_monsters;
    int map;
    int skill;
    int gameversion;
    int lowres_turn;
    int new_sync;
    int timelimit;
    int loadgame;
    int random;




    int num_players;
    int consoleplayer;



    int player_classes[8];

} net_gamesettings_t;
typedef struct
{
    unsigned int diff;
    ticcmd_t cmd;
} net_ticdiff_t;



typedef struct
{
    signed int latency;
    unsigned int seq;
    boolean playeringame[8];
    net_ticdiff_t cmds[8];
} net_full_ticcmd_t;



typedef struct
{
    char *version;
    int server_state;
    int num_players;
    int max_players;
    int gamemode;
    int gamemission;
    char *description;
} net_querydata_t;



typedef struct
{
    int num_players;
    int num_drones;
    int ready_players;
    int max_players;
    int is_controller;
    int consoleplayer;
    char player_names[8][30];
    char player_addrs[8][30];
    sha1_digest_t wad_sha1sum;
    sha1_digest_t deh_sha1sum;
    int is_freedoom;
} net_waitdata_t;







typedef enum
{

    PST_LIVE,

    PST_DEAD,

    PST_REBORN

} playerstate_t;





typedef enum
{

    CF_NOCLIP = 1,

    CF_GODMODE = 2,

    CF_NOMOMENTUM = 4

} cheat_t;





typedef struct player_s
{
    mobj_t* mo;
    playerstate_t playerstate;
    ticcmd_t cmd;




    fixed_t viewz;

    fixed_t viewheight;

    fixed_t deltaviewheight;

    fixed_t bob;



    int health;
    int armorpoints;

    int armortype;


    int powers[NUMPOWERS];
    boolean cards[NUMCARDS];
    boolean backpack;


    int frags[4];
    weapontype_t readyweapon;


    weapontype_t pendingweapon;

    boolean weaponowned[NUMWEAPONS];
    int ammo[NUMAMMO];
    int maxammo[NUMAMMO];


    int attackdown;
    int usedown;



    int cheats;


    int refire;


    int killcount;
    int itemcount;
    int secretcount;


    char* message;


    int damagecount;
    int bonuscount;


    mobj_t* attacker;


    int extralight;



    int fixedcolormap;



    int colormap;


    pspdef_t psprites[NUMPSPRITES];


    boolean didsecret;

} player_t;






typedef struct
{
    boolean in;


    int skills;
    int sitems;
    int ssecret;
    int stime;
    int frags[4];
    int score;

} wbplayerstruct_t;

typedef struct
{
    int epsd;


    boolean didsecret;


    int last;
    int next;

    int maxkills;
    int maxitems;
    int maxsecret;
    int maxfrags;


    int partime;


    int pnum;

    wbplayerstruct_t plyr[4];

} wbstartstruct_t;
extern fixed_t* textureheight;


extern fixed_t* spritewidth;

extern fixed_t* spriteoffset;
extern fixed_t* spritetopoffset;

extern lighttable_t* colormaps;

extern int viewwidth;
extern int scaledviewwidth;
extern int viewheight;

extern int firstflat;


extern int* flattranslation;
extern int* texturetranslation;



extern int firstspritelump;
extern int lastspritelump;
extern int numspritelumps;






extern int numsprites;
extern spritedef_t* sprites;

extern int numvertexes;
extern vertex_t* vertexes;

extern int numsegs;
extern seg_t* segs;

extern int numsectors;
extern sector_t* sectors;

extern int numsubsectors;
extern subsector_t* subsectors;

extern int numnodes;
extern node_t* nodes;

extern int numlines;
extern line_t* lines;

extern int numsides;
extern side_t* sides;





extern fixed_t viewx;
extern fixed_t viewy;
extern fixed_t viewz;

extern angle_t viewangle;
extern player_t* viewplayer;



extern angle_t clipangle;

extern int viewangletox[8192/2];
extern angle_t xtoviewangle[320 +1];


extern fixed_t rw_distance;
extern angle_t rw_normalangle;




extern int rw_angle1;


extern int sscount;

extern visplane_t* floorplane;
extern visplane_t* ceilingplane;



byte*
R_GetColumn
( int tex,
  int col );



void R_InitData (void);
void R_PrecacheLevel (void);





int R_FlatNumForName (char* name);




int R_TextureNumForName (char *name);
int R_CheckTextureNumForName (char *name);






extern fixed_t viewcos;
extern fixed_t viewsin;

extern int viewwindowx;
extern int viewwindowy;



extern int centerx;
extern int centery;

extern fixed_t centerxfrac;
extern fixed_t centeryfrac;
extern fixed_t projection;

extern int validcount;

extern int linecount;
extern int loopcount;
extern lighttable_t* scalelight[16][48];
extern lighttable_t* scalelightfixed[48];
extern lighttable_t* zlight[16][128];

extern int extralight;
extern lighttable_t* fixedcolormap;
extern int detailshift;






extern void (*colfunc) (void);
extern void (*transcolfunc) (void);
extern void (*basecolfunc) (void);
extern void (*fuzzcolfunc) (void);

extern void (*spanfunc) (void);




int
R_PointOnSide
( fixed_t x,
  fixed_t y,
  node_t* node );

int
R_PointOnSegSide
( fixed_t x,
  fixed_t y,
  seg_t* line );

angle_t
R_PointToAngle
( fixed_t x,
  fixed_t y );

angle_t
R_PointToAngle2
( fixed_t x1,
  fixed_t y1,
  fixed_t x2,
  fixed_t y2 );

fixed_t
R_PointToDist
( fixed_t x,
  fixed_t y );


fixed_t R_ScaleFromGlobalAngle (angle_t visangle);

subsector_t*
R_PointInSubsector
( fixed_t x,
  fixed_t y );

void
R_AddPointToBox
( int x,
  int y,
  fixed_t* box );
void R_RenderPlayerView (player_t *player);


void R_Init (void);


void R_SetViewSize (int blocks, int detail);
extern seg_t* curline;
extern side_t* sidedef;
extern line_t* linedef;
extern sector_t* frontsector;
extern sector_t* backsector;

extern int rw_x;
extern int rw_stopx;

extern boolean segtextured;


extern boolean markfloor;
extern boolean markceiling;

extern boolean skymap;

extern drawseg_t drawsegs[256];
extern drawseg_t* ds_p;

extern lighttable_t** hscalelight;
extern lighttable_t** vscalelight;
extern lighttable_t** dscalelight;


typedef void (*drawfunc_t) (int start, int stop);



void R_ClearClipSegs (void);
void R_ClearDrawSegs (void);


void R_RenderBSPNode (int bspnum);
void
R_RenderMaskedSegRange
( drawseg_t* ds,
  int x1,
  int x2 );
extern short* lastopening;


typedef void (*planefunction_t) (int top, int bottom);

extern planefunction_t floorfunc;
extern planefunction_t ceilingfunc_t;

extern short floorclip[320];
extern short ceilingclip[320];

extern fixed_t yslope[200];
extern fixed_t distscale[320];

void R_InitPlanes (void);
void R_ClearPlanes (void);

void
R_MapPlane
( int y,
  int x1,
  int x2 );

void
R_MakeSpans
( int x,
  int t1,
  int b1,
  int t2,
  int b2 );

void R_DrawPlanes (void);

visplane_t*
R_FindPlane
( fixed_t height,
  int picnum,
  int lightlevel );

visplane_t*
R_CheckPlane
( visplane_t* pl,
  int start,
  int stop );

extern vissprite_t vissprites[128];
extern vissprite_t* vissprite_p;
extern vissprite_t vsprsortedhead;



extern short negonearray[320];
extern short screenheightarray[320];


extern short* mfloorclip;
extern short* mceilingclip;
extern fixed_t spryscale;
extern fixed_t sprtopscreen;

extern fixed_t pspritescale;
extern fixed_t pspriteiscale;


void R_DrawMaskedColumn (column_t* column);


void R_SortVisSprites (void);

void R_AddSprites (sector_t* sec);
void R_AddPSprites (void);
void R_DrawSprites (void);
void R_InitSprites (char** namelist);
void R_ClearSprites (void);
void R_DrawMasked (void);

void
R_ClipVisSprite
( vissprite_t* vis,
  int xl,
  int xh );
extern lighttable_t* dc_colormap;
extern int dc_x;
extern int dc_yl;
extern int dc_yh;
extern fixed_t dc_iscale;
extern fixed_t dc_texturemid;


extern byte* dc_source;





void R_DrawColumn (void);
void R_DrawColumnLow (void);


void R_DrawFuzzColumn (void);
void R_DrawFuzzColumnLow (void);




void R_DrawTranslatedColumn (void);
void R_DrawTranslatedColumnLow (void);

void
R_VideoErase
( unsigned ofs,
  int count );

extern int ds_y;
extern int ds_x1;
extern int ds_x2;

extern lighttable_t* ds_colormap;

extern fixed_t ds_xfrac;
extern fixed_t ds_yfrac;
extern fixed_t ds_xstep;
extern fixed_t ds_ystep;


extern byte* ds_source;

extern byte* translationtables;
extern byte* dc_translation;




void R_DrawSpan (void);


void R_DrawSpanLow (void);


void
R_InitBuffer
( int width,
  int height );




void R_InitTranslationTables (void);




void R_FillBackScreen (void);


void R_DrawViewBorder (void);
extern thinker_t thinkercap;


void P_InitThinkers (void);
void P_AddThinker (thinker_t* thinker);
void P_RemoveThinker (thinker_t* thinker);





void P_SetupPsprites (player_t* curplayer);
void P_MovePsprites (player_t* curplayer);
void P_DropWeapon (player_t* player);





void P_PlayerThink (player_t* player);
extern mapthing_t itemrespawnque[128];
extern int itemrespawntime[128];
extern int iquehead;
extern int iquetail;


void P_RespawnSpecials (void);

mobj_t*
P_SpawnMobj
( fixed_t x,
  fixed_t y,
  fixed_t z,
  mobjtype_t type );

void P_RemoveMobj (mobj_t* th);
mobj_t* P_SubstNullMobj (mobj_t* th);
boolean P_SetMobjState (mobj_t* mobj, statenum_t state);
void P_MobjThinker (mobj_t* mobj);

void P_SpawnPuff (fixed_t x, fixed_t y, fixed_t z);
void P_SpawnBlood (fixed_t x, fixed_t y, fixed_t z, int damage);
mobj_t* P_SpawnMissile (mobj_t* source, mobj_t* dest, mobjtype_t type);
void P_SpawnPlayerMissile (mobj_t* source, mobjtype_t type);





void P_NoiseAlert (mobj_t* target, mobj_t* emmiter);





typedef struct
{
    fixed_t x;
    fixed_t y;
    fixed_t dx;
    fixed_t dy;

} divline_t;

typedef struct
{
    fixed_t frac;
    boolean isaline;
    union {
 mobj_t* thing;
 line_t* line;
    } d;
} intercept_t;






extern intercept_t intercepts[(128 + 61)];
extern intercept_t* intercept_p;

typedef boolean (*traverser_t) (intercept_t *in);

fixed_t P_AproxDistance (fixed_t dx, fixed_t dy);
int P_PointOnLineSide (fixed_t x, fixed_t y, line_t* line);
int P_PointOnDivlineSide (fixed_t x, fixed_t y, divline_t* line);
void P_MakeDivline (line_t* li, divline_t* dl);
fixed_t P_InterceptVector (divline_t* v2, divline_t* v1);
int P_BoxOnLineSide (fixed_t* tmbox, line_t* ld);

extern fixed_t opentop;
extern fixed_t openbottom;
extern fixed_t openrange;
extern fixed_t lowfloor;

void P_LineOpening (line_t* linedef);

boolean P_BlockLinesIterator (int x, int y, boolean(*func)(line_t*) );
boolean P_BlockThingsIterator (int x, int y, boolean(*func)(mobj_t*) );





extern divline_t trace;

boolean
P_PathTraverse
( fixed_t x1,
  fixed_t y1,
  fixed_t x2,
  fixed_t y2,
  int flags,
  boolean (*trav) (intercept_t *));

void P_UnsetThingPosition (mobj_t* thing);
void P_SetThingPosition (mobj_t* thing);
extern boolean floatok;
extern fixed_t tmfloorz;
extern fixed_t tmceilingz;


extern line_t* ceilingline;
extern line_t* spechit[20];
extern int numspechit;

boolean P_CheckPosition (mobj_t *thing, fixed_t x, fixed_t y);
boolean P_TryMove (mobj_t* thing, fixed_t x, fixed_t y);
boolean P_TeleportMove (mobj_t* thing, fixed_t x, fixed_t y);
void P_SlideMove (mobj_t* mo);
boolean P_CheckSight (mobj_t* t1, mobj_t* t2);
void P_UseLines (player_t* player);

boolean P_ChangeSector (sector_t* sector, boolean crunch);

extern mobj_t* linetarget;

fixed_t
P_AimLineAttack
( mobj_t* t1,
  angle_t angle,
  fixed_t distance );

void
P_LineAttack
( mobj_t* t1,
  angle_t angle,
  fixed_t distance,
  fixed_t slope,
  int damage );

void
P_RadiusAttack
( mobj_t* spot,
  mobj_t* source,
  int damage );






extern byte* rejectmatrix;
extern short* blockmaplump;
extern short* blockmap;
extern int bmapwidth;
extern int bmapheight;
extern fixed_t bmaporgx;
extern fixed_t bmaporgy;
extern mobj_t** blocklinks;






extern int maxammo[NUMAMMO];
extern int clipammo[NUMAMMO];

void
P_TouchSpecialThing
( mobj_t* special,
  mobj_t* toucher );

void
P_DamageMobj
( mobj_t* target,
  mobj_t* inflictor,
  mobj_t* source,
  int damage );





extern boolean levelTimer;
extern int levelTimeCount;







void P_InitPicAnims (void);


void P_SpawnSpecials (void);


void P_UpdateSpecials (void);


boolean
P_UseSpecialLine
( mobj_t* thing,
  line_t* line,
  int side );

void
P_ShootSpecialLine
( mobj_t* thing,
  line_t* line );

void
P_CrossSpecialLine
( int linenum,
  int side,
  mobj_t* thing );

void P_PlayerInSpecialSector (player_t* player);

int
twoSided
( int sector,
  int line );

sector_t*
getSector
( int currentSector,
  int line,
  int side );

side_t*
getSide
( int currentSector,
  int line,
  int side );

fixed_t P_FindLowestFloorSurrounding(sector_t* sec);
fixed_t P_FindHighestFloorSurrounding(sector_t* sec);

fixed_t
P_FindNextHighestFloor
( sector_t* sec,
  int currentheight );

fixed_t P_FindLowestCeilingSurrounding(sector_t* sec);
fixed_t P_FindHighestCeilingSurrounding(sector_t* sec);

int
P_FindSectorFromLineTag
( line_t* line,
  int start );

int
P_FindMinSurroundingLight
( sector_t* sector,
  int max );

sector_t*
getNextSector
( line_t* line,
  sector_t* sec );





int EV_DoDonut(line_t* line);






typedef struct
{
    thinker_t thinker;
    sector_t* sector;
    int count;
    int maxlight;
    int minlight;

} fireflicker_t;



typedef struct
{
    thinker_t thinker;
    sector_t* sector;
    int count;
    int maxlight;
    int minlight;
    int maxtime;
    int mintime;

} lightflash_t;



typedef struct
{
    thinker_t thinker;
    sector_t* sector;
    int count;
    int minlight;
    int maxlight;
    int darktime;
    int brighttime;

} strobe_t;




typedef struct
{
    thinker_t thinker;
    sector_t* sector;
    int minlight;
    int maxlight;
    int direction;

} glow_t;







void P_SpawnFireFlicker (sector_t* sector);
void T_LightFlash (lightflash_t* flash);
void P_SpawnLightFlash (sector_t* sector);
void T_StrobeFlash (strobe_t* flash);

void
P_SpawnStrobeFlash
( sector_t* sector,
  int fastOrSlow,
  int inSync );

void EV_StartLightStrobing(line_t* line);
void EV_TurnTagLightsOff(line_t* line);

void
EV_LightTurnOn
( line_t* line,
  int bright );

void T_Glow(glow_t* g);
void P_SpawnGlowingLight(sector_t* sector);







typedef struct
{
    char name1[9];
    char name2[9];
    short episode;

} switchlist_t;


typedef enum
{
    top,
    middle,
    bottom

} bwhere_e;


typedef struct
{
    line_t* line;
    bwhere_e where;
    int btexture;
    int btimer;
    degenmobj_t *soundorg;

} button_t;
extern button_t buttonlist[16];

void
P_ChangeSwitchTexture
( line_t* line,
  int useAgain );

void P_InitSwitchList(void);





typedef enum
{
    up,
    down,
    waiting,
    in_stasis

} plat_e;



typedef enum
{
    perpetualRaise,
    downWaitUpStay,
    raiseAndChange,
    raiseToNearestAndChange,
    blazeDWUS

} plattype_e;



typedef struct
{
    thinker_t thinker;
    sector_t* sector;
    fixed_t speed;
    fixed_t low;
    fixed_t high;
    int wait;
    int count;
    plat_e status;
    plat_e oldstatus;
    boolean crush;
    int tag;
    plattype_e type;

} plat_t;
extern plat_t* activeplats[30];

void T_PlatRaise(plat_t* plat);

int
EV_DoPlat
( line_t* line,
  plattype_e type,
  int amount );

void P_AddActivePlat(plat_t* plat);
void P_RemoveActivePlat(plat_t* plat);
void EV_StopPlat(line_t* line);
void P_ActivateInStasis(int tag);





typedef enum
{
    vld_normal,
    vld_close30ThenOpen,
    vld_close,
    vld_open,
    vld_raiseIn5Mins,
    vld_blazeRaise,
    vld_blazeOpen,
    vld_blazeClose

} vldoor_e;



typedef struct
{
    thinker_t thinker;
    vldoor_e type;
    sector_t* sector;
    fixed_t topheight;
    fixed_t speed;


    int direction;


    int topwait;


    int topcountdown;

} vldoor_t;






void
EV_VerticalDoor
( line_t* line,
  mobj_t* thing );

int
EV_DoDoor
( line_t* line,
  vldoor_e type );

int
EV_DoLockedDoor
( line_t* line,
  vldoor_e type,
  mobj_t* thing );

void T_VerticalDoor (vldoor_t* door);
void P_SpawnDoorCloseIn30 (sector_t* sec);

void
P_SpawnDoorRaiseIn5Mins
( sector_t* sec,
  int secnum );
typedef enum
{
    lowerToFloor,
    raiseToHighest,
    lowerAndCrush,
    crushAndRaise,
    fastCrushAndRaise,
    silentCrushAndRaise

} ceiling_e;



typedef struct
{
    thinker_t thinker;
    ceiling_e type;
    sector_t* sector;
    fixed_t bottomheight;
    fixed_t topheight;
    fixed_t speed;
    boolean crush;


    int direction;


    int tag;
    int olddirection;

} ceiling_t;
extern ceiling_t* activeceilings[30];

int
EV_DoCeiling
( line_t* line,
  ceiling_e type );

void T_MoveCeiling (ceiling_t* ceiling);
void P_AddActiveCeiling(ceiling_t* c);
void P_RemoveActiveCeiling(ceiling_t* c);
int EV_CeilingCrushStop(line_t* line);
void P_ActivateInStasisCeiling(line_t* line);





typedef enum
{

    lowerFloor,


    lowerFloorToLowest,


    turboLower,


    raiseFloor,


    raiseFloorToNearest,


    raiseToTexture,



    lowerAndChange,

    raiseFloor24,
    raiseFloor24AndChange,
    raiseFloorCrush,


    raiseFloorTurbo,
    donutRaise,
    raiseFloor512

} floor_e;




typedef enum
{
    build8,
    turbo16

} stair_e;



typedef struct
{
    thinker_t thinker;
    floor_e type;
    boolean crush;
    sector_t* sector;
    int direction;
    int newspecial;
    short texture;
    fixed_t floordestheight;
    fixed_t speed;

} floormove_t;





typedef enum
{
    ok,
    crushed,
    pastdest

} result_e;

result_e
T_MovePlane
( sector_t* sector,
  fixed_t speed,
  fixed_t dest,
  boolean crush,
  int floorOrCeiling,
  int direction );

int
EV_BuildStairs
( line_t* line,
  stair_e type );

int
EV_DoFloor
( line_t* line,
  floor_e floortype );

void T_MoveFloor( floormove_t* floor);




int
EV_Teleport
( line_t* line,
  int side,
  mobj_t* thing );
typedef struct _wad_file_s wad_file_t;

typedef struct
{


    wad_file_t *(*OpenFile)(char *path);



    void (*CloseFile)(wad_file_t *file);




    size_t (*Read)(wad_file_t *file, unsigned int offset,
                   void *buffer, size_t buffer_len);

} wad_file_class_t;

struct _wad_file_s
{


    wad_file_class_t *file_class;




    byte *mapped;



    unsigned int length;
};




wad_file_t *W_OpenFile(char *path);



void W_CloseFile(wad_file_t *wad);





size_t W_Read(wad_file_t *wad, unsigned int offset,
              void *buffer, size_t buffer_len);
typedef struct lumpinfo_s lumpinfo_t;

struct lumpinfo_s
{
    char name[8];
    wad_file_t *wad_file;
    int position;
    int size;
    void *cache;



    lumpinfo_t *next;
};


extern lumpinfo_t *lumpinfo;
extern unsigned int numlumps;

wad_file_t *W_AddFile (char *filename);

int W_CheckNumForName (char* name);
int W_GetNumForName (char* name);

int W_LumpLength (unsigned int lump);
void W_ReadLump (unsigned int lump, void *dest);

void* W_CacheLumpNum (int lump, int tag);
void* W_CacheLumpName (char* name, int tag);

void W_GenerateHashTable(void);

extern unsigned int W_LumpNameHash(const char *s);

void W_ReleaseLumpNum(int lump);
void W_ReleaseLumpName(char *name);

void W_CheckCorrectIWAD(GameMission_t mission);


extern int key_right;
extern int key_left;

extern int key_up;
extern int key_down;
extern int key_strafeleft;
extern int key_straferight;
extern int key_fire;
extern int key_use;
extern int key_strafe;
extern int key_speed;

extern int key_jump;

extern int key_flyup;
extern int key_flydown;
extern int key_flycenter;
extern int key_lookup;
extern int key_lookdown;
extern int key_lookcenter;
extern int key_invleft;
extern int key_invright;
extern int key_useartifact;


extern int key_usehealth;
extern int key_invquery;
extern int key_mission;
extern int key_invpop;
extern int key_invkey;
extern int key_invhome;
extern int key_invend;
extern int key_invuse;
extern int key_invdrop;

extern int key_message_refresh;
extern int key_pause;

extern int key_multi_msg;
extern int key_multi_msgplayer[8];

extern int key_weapon1;
extern int key_weapon2;
extern int key_weapon3;
extern int key_weapon4;
extern int key_weapon5;
extern int key_weapon6;
extern int key_weapon7;
extern int key_weapon8;

extern int key_arti_all;
extern int key_arti_health;
extern int key_arti_poisonbag;
extern int key_arti_blastradius;
extern int key_arti_teleport;
extern int key_arti_teleportother;
extern int key_arti_egg;
extern int key_arti_invulnerability;

extern int key_demo_quit;
extern int key_spy;
extern int key_prevweapon;
extern int key_nextweapon;

extern int key_map_north;
extern int key_map_south;
extern int key_map_east;
extern int key_map_west;
extern int key_map_zoomin;
extern int key_map_zoomout;
extern int key_map_toggle;
extern int key_map_maxzoom;
extern int key_map_follow;
extern int key_map_grid;
extern int key_map_mark;
extern int key_map_clearmark;



extern int key_menu_activate;
extern int key_menu_up;
extern int key_menu_down;
extern int key_menu_left;
extern int key_menu_right;
extern int key_menu_back;
extern int key_menu_forward;
extern int key_menu_confirm;
extern int key_menu_abort;

extern int key_menu_help;
extern int key_menu_save;
extern int key_menu_load;
extern int key_menu_volume;
extern int key_menu_detail;
extern int key_menu_qsave;
extern int key_menu_endgame;
extern int key_menu_messages;
extern int key_menu_qload;
extern int key_menu_quit;
extern int key_menu_gamma;

extern int key_menu_incscreen;
extern int key_menu_decscreen;
extern int key_menu_screenshot;

extern int mousebfire;
extern int mousebstrafe;
extern int mousebforward;

extern int mousebjump;

extern int mousebstrafeleft;
extern int mousebstraferight;
extern int mousebbackward;
extern int mousebuse;

extern int mousebprevweapon;
extern int mousebnextweapon;

extern int joybfire;
extern int joybstrafe;
extern int joybuse;
extern int joybspeed;

extern int joybjump;

extern int joybstrafeleft;
extern int joybstraferight;

extern int joybprevweapon;
extern int joybnextweapon;

extern int joybmenu;

extern int dclick_use;

void M_BindBaseControls(void);
void M_BindHereticControls(void);
void M_BindHexenControls(void);
void M_BindStrifeControls(void);
void M_BindWeaponControls(void);
void M_BindMapControls(void);
void M_BindMenuControls(void);
void M_BindChatControls(unsigned int num_players);

void M_ApplyPlatformDefaults(void);
boolean M_WriteFile(char *name, void *source, int length);
int M_ReadFile(char *name, byte **buffer);
void M_MakeDirectory(char *dir);
char *M_TempFile(char *s);
boolean M_FileExists(char *file);
long M_FileLength(FILE *handle);
boolean M_StrToInt(const char *str, int *result);
void M_ExtractFileBase(char *path, char *dest);
void M_ForceUppercase(char *text);
char *M_StrCaseStr(char *haystack, char *needle);
char *M_StringDuplicate(const char *orig);
boolean M_StringCopy(char *dest, const char *src, size_t dest_size);
boolean M_StringConcat(char *dest, const char *src, size_t dest_size);
char *M_StringReplace(const char *haystack, const char *needle,
                      const char *replacement);
char *M_StringJoin(const char *s, ...);
boolean M_StringStartsWith(const char *s, const char *prefix);
boolean M_StringEndsWith(const char *s, const char *suffix);
int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args);
int M_snprintf(char *buf, size_t buf_len, const char *s, ...);
char *M_OEMToUTF8(const char *ansi);
typedef void (*atexit_func_t)(void);


void I_Init (void);




byte* I_ZoneBase (int *size);

boolean I_ConsoleStdout(void);
ticcmd_t* I_BaseTiccmd (void);




void I_Quit (void);

void I_Error (char *error, ...);

void I_Tactile (int on, int off, int total);

boolean I_GetMemoryValue(unsigned int offset, void *value, int size);





void I_AtExit(atexit_func_t func, boolean run_if_error);



void I_BindVariables(void);



void I_PrintStartupBanner(char *gamedescription);



void I_PrintBanner(char *text);



void I_PrintDivider(void);


extern int dirtybox[4];

extern byte *tinttable;




typedef boolean (*vpatchclipfunc_t)(patch_t *, int, int);
void V_SetPatchClipCallback(vpatchclipfunc_t func);



void V_Init (void);



void V_CopyRect(int srcx, int srcy, byte *source,
                int width, int height,
                int destx, int desty);

void V_DrawPatch(int x, int y, patch_t *patch);
void V_DrawPatchFlipped(int x, int y, patch_t *patch);
void V_DrawTLPatch(int x, int y, patch_t *patch);
void V_DrawAltTLPatch(int x, int y, patch_t * patch);
void V_DrawShadowedPatch(int x, int y, patch_t *patch);
void V_DrawXlaPatch(int x, int y, patch_t * patch);
void V_DrawPatchDirect(int x, int y, patch_t *patch);



void V_DrawBlock(int x, int y, int width, int height, byte *src);

void V_MarkRect(int x, int y, int width, int height);

void V_DrawFilledBox(int x, int y, int w, int h, int c);
void V_DrawHorizLine(int x, int y, int w, int c);
void V_DrawVertLine(int x, int y, int h, int c);
void V_DrawBox(int x, int y, int w, int h, int c);



void V_DrawRawScreen(byte *raw);



void V_UseBuffer(byte *buffer);



void V_RestoreBuffer(void);





void V_ScreenShot(char *format);




void V_LoadTintTable(void);





void V_LoadXlaTable(void);

void V_DrawMouseSpeedBox(int speed);


typedef boolean (*netgame_startup_callback_t)(int ready_players,
                                              int num_players);

typedef struct
{


    void (*ProcessEvents)();




    void (*BuildTiccmd)(ticcmd_t *cmd, int maketic);



    void (*RunTic)(ticcmd_t *cmds, boolean *ingame);



    void (*RunMenu)();
} loop_interface_t;


void D_RegisterLoopCallbacks(loop_interface_t *i);


void NetUpdate (void);



void D_QuitNetGame (void);


void TryRunTics (void);


void D_StartGameLoop(void);



boolean D_InitNetGame(net_connect_data_t *connect_data);




void D_StartNetGame(net_gamesettings_t *settings,
                    netgame_startup_callback_t callback);

extern boolean singletics;
extern int gametic, ticdup;
extern boolean nomonsters;
extern boolean respawnparm;
extern boolean fastparm;

extern boolean devparm;





extern GameMode_t gamemode;
extern GameMission_t gamemission;
extern GameVersion_t gameversion;
extern char *gamedescription;


extern boolean bfgedition;
extern boolean modifiedgame;







extern skill_t startskill;
extern int startepisode;
extern int startmap;




extern int startloadgame;

extern boolean autostart;


extern skill_t gameskill;
extern int gameepisode;
extern int gamemap;


extern int timelimit;


extern boolean respawnmonsters;


extern boolean netgame;


extern int deathmatch;
extern int sfxVolume;
extern int musicVolume;





extern int snd_MusicDevice;
extern int snd_SfxDevice;

extern int snd_DesiredMusicDevice;
extern int snd_DesiredSfxDevice;
extern boolean statusbaractive;

extern boolean automapactive;
extern boolean menuactive;
extern boolean paused;


extern boolean viewactive;

extern boolean nodrawers;


extern boolean testcontrols;
extern int testcontrols_mousespeed;






extern int viewangleoffset;


extern int consoleplayer;
extern int displayplayer;






extern int totalkills;
extern int totalitems;
extern int totalsecret;


extern int levelstarttic;
extern int leveltime;







extern boolean usergame;


extern boolean demoplayback;
extern boolean demorecording;




extern boolean lowres_turn;


extern boolean singledemo;





extern gamestate_t gamestate;
extern player_t players[4];


extern boolean playeringame[4];




extern mapthing_t deathmatchstarts[10];
extern mapthing_t* deathmatch_p;


extern mapthing_t playerstarts[4];



extern wbstartstruct_t wminfo;
extern char * savegamedir;
extern char basedefault[1024];


extern boolean precache;




extern gamestate_t wipegamestate;

extern int mouseSensitivity;

extern int bodyqueslot;






extern int skyflatnum;






extern int rndindex;

extern ticcmd_t *netcmds;



extern char *doom1_endmsg[];
extern char *doom2_endmsg[];

boolean AM_Responder (event_t* ev);


void AM_Ticker (void);



void AM_Drawer (void);



void AM_Stop (void);


extern cheatseq_t cheat_amap;
typedef struct
{
    int x, y;
} fpoint_t;

typedef struct
{
    fpoint_t a, b;
} fline_t;

typedef struct
{
    fixed_t x,y;
} mpoint_t;

typedef struct
{
    mpoint_t a, b;
} mline_t;

typedef struct
{
    fixed_t slp, islp;
} islope_t;
mline_t player_arrow[] = {
    { { -((8*16*(1<<16))/7)+((8*16*(1<<16))/7)/8, 0 }, { ((8*16*(1<<16))/7), 0 } },
    { { ((8*16*(1<<16))/7), 0 }, { ((8*16*(1<<16))/7)-((8*16*(1<<16))/7)/2, ((8*16*(1<<16))/7)/4 } },
    { { ((8*16*(1<<16))/7), 0 }, { ((8*16*(1<<16))/7)-((8*16*(1<<16))/7)/2, -((8*16*(1<<16))/7)/4 } },
    { { -((8*16*(1<<16))/7)+((8*16*(1<<16))/7)/8, 0 }, { -((8*16*(1<<16))/7)-((8*16*(1<<16))/7)/8, ((8*16*(1<<16))/7)/4 } },
    { { -((8*16*(1<<16))/7)+((8*16*(1<<16))/7)/8, 0 }, { -((8*16*(1<<16))/7)-((8*16*(1<<16))/7)/8, -((8*16*(1<<16))/7)/4 } },
    { { -((8*16*(1<<16))/7)+3*((8*16*(1<<16))/7)/8, 0 }, { -((8*16*(1<<16))/7)+((8*16*(1<<16))/7)/8, ((8*16*(1<<16))/7)/4 } },
    { { -((8*16*(1<<16))/7)+3*((8*16*(1<<16))/7)/8, 0 }, { -((8*16*(1<<16))/7)+((8*16*(1<<16))/7)/8, -((8*16*(1<<16))/7)/4 } }
};



mline_t cheat_player_arrow[] = {
    { { -((8*16*(1<<16))/7)+((8*16*(1<<16))/7)/8, 0 }, { ((8*16*(1<<16))/7), 0 } },
    { { ((8*16*(1<<16))/7), 0 }, { ((8*16*(1<<16))/7)-((8*16*(1<<16))/7)/2, ((8*16*(1<<16))/7)/6 } },
    { { ((8*16*(1<<16))/7), 0 }, { ((8*16*(1<<16))/7)-((8*16*(1<<16))/7)/2, -((8*16*(1<<16))/7)/6 } },
    { { -((8*16*(1<<16))/7)+((8*16*(1<<16))/7)/8, 0 }, { -((8*16*(1<<16))/7)-((8*16*(1<<16))/7)/8, ((8*16*(1<<16))/7)/6 } },
    { { -((8*16*(1<<16))/7)+((8*16*(1<<16))/7)/8, 0 }, { -((8*16*(1<<16))/7)-((8*16*(1<<16))/7)/8, -((8*16*(1<<16))/7)/6 } },
    { { -((8*16*(1<<16))/7)+3*((8*16*(1<<16))/7)/8, 0 }, { -((8*16*(1<<16))/7)+((8*16*(1<<16))/7)/8, ((8*16*(1<<16))/7)/6 } },
    { { -((8*16*(1<<16))/7)+3*((8*16*(1<<16))/7)/8, 0 }, { -((8*16*(1<<16))/7)+((8*16*(1<<16))/7)/8, -((8*16*(1<<16))/7)/6 } },
    { { -((8*16*(1<<16))/7)/2, 0 }, { -((8*16*(1<<16))/7)/2, -((8*16*(1<<16))/7)/6 } },
    { { -((8*16*(1<<16))/7)/2, -((8*16*(1<<16))/7)/6 }, { -((8*16*(1<<16))/7)/2+((8*16*(1<<16))/7)/6, -((8*16*(1<<16))/7)/6 } },
    { { -((8*16*(1<<16))/7)/2+((8*16*(1<<16))/7)/6, -((8*16*(1<<16))/7)/6 }, { -((8*16*(1<<16))/7)/2+((8*16*(1<<16))/7)/6, ((8*16*(1<<16))/7)/4 } },
    { { -((8*16*(1<<16))/7)/6, 0 }, { -((8*16*(1<<16))/7)/6, -((8*16*(1<<16))/7)/6 } },
    { { -((8*16*(1<<16))/7)/6, -((8*16*(1<<16))/7)/6 }, { 0, -((8*16*(1<<16))/7)/6 } },
    { { 0, -((8*16*(1<<16))/7)/6 }, { 0, ((8*16*(1<<16))/7)/4 } },
    { { ((8*16*(1<<16))/7)/6, ((8*16*(1<<16))/7)/4 }, { ((8*16*(1<<16))/7)/6, -((8*16*(1<<16))/7)/7 } },
    { { ((8*16*(1<<16))/7)/6, -((8*16*(1<<16))/7)/7 }, { ((8*16*(1<<16))/7)/6+((8*16*(1<<16))/7)/32, -((8*16*(1<<16))/7)/7-((8*16*(1<<16))/7)/32 } },
    { { ((8*16*(1<<16))/7)/6+((8*16*(1<<16))/7)/32, -((8*16*(1<<16))/7)/7-((8*16*(1<<16))/7)/32 }, { ((8*16*(1<<16))/7)/6+((8*16*(1<<16))/7)/10, -((8*16*(1<<16))/7)/7 } }
};



mline_t triangle_guy[] = {
    { { (fixed_t)((-56819)), (fixed_t)((-32768)) }, { (fixed_t)((56819) ), (fixed_t)((-32768)) } },
    { { (fixed_t)((56819) ), (fixed_t)((-32768)) }, { (fixed_t)(0 ), (fixed_t)(((1<<16)) ) } },
    { { (fixed_t)(0 ), (fixed_t)(((1<<16)) ) }, { (fixed_t)((-56819)), (fixed_t)((-32768)) } }
};



mline_t thintriangle_guy[] = {
    { { (fixed_t)((-32768)), (fixed_t)((-45875)) }, { (fixed_t)(((1<<16)) ), (fixed_t)(0 ) } },
    { { (fixed_t)(((1<<16)) ), (fixed_t)(0 ) }, { (fixed_t)((-32768)), (fixed_t)((45875) ) } },
    { { (fixed_t)((-32768)), (fixed_t)((45875) ) }, { (fixed_t)((-32768)), (fixed_t)((-45875)) } }
};





static int cheating = 0;
static int grid = 0;

static int leveljuststarted = 1;

boolean automapactive = false;
static int finit_width = 320;
static int finit_height = 200 - 32;


static int f_x;
static int f_y;


static int f_w;
static int f_h;

static int lightlev;
static byte* fb;
static int amclock;

static mpoint_t m_paninc;
static fixed_t mtof_zoommul;
static fixed_t ftom_zoommul;

static fixed_t m_x, m_y;
static fixed_t m_x2, m_y2;




static fixed_t m_w;
static fixed_t m_h;


static fixed_t min_x;
static fixed_t min_y;
static fixed_t max_x;
static fixed_t max_y;

static fixed_t max_w;
static fixed_t max_h;


static fixed_t min_w;
static fixed_t min_h;


static fixed_t min_scale_mtof;
static fixed_t max_scale_mtof;


static fixed_t old_m_w, old_m_h;
static fixed_t old_m_x, old_m_y;


static mpoint_t f_oldloc;


static fixed_t scale_mtof = (fixed_t)(0*(1<<16));

static fixed_t scale_ftom;

static player_t *plr;

static patch_t *marknums[10];
static mpoint_t markpoints[10];
static int markpointnum = 0;

static int followplayer = 1;

cheatseq_t cheat_amap = { "iddt", sizeof("iddt") - 1, 0, 0, 0, "" };

static boolean stopped = true;





void
AM_getIslope
( mline_t* ml,
  islope_t* is )
{
    int dx, dy;

    dy = ml->a.y - ml->b.y;
    dx = ml->b.x - ml->a.x;
    if (!dy) is->islp = (dx<0?-2147483647:2147483647);
    else is->islp = FixedDiv(dx, dy);
    if (!dx) is->slp = (dy<0?-2147483647:2147483647);
    else is->slp = FixedDiv(dy, dx);

}




void AM_activateNewScale(void)
{
    m_x += m_w/2;
    m_y += m_h/2;
    m_w = FixedMul(((f_w)<<16),scale_ftom);
    m_h = FixedMul(((f_h)<<16),scale_ftom);
    m_x -= m_w/2;
    m_y -= m_h/2;
    m_x2 = m_x + m_w;
    m_y2 = m_y + m_h;
}




void AM_saveScaleAndLoc(void)
{
    old_m_x = m_x;
    old_m_y = m_y;
    old_m_w = m_w;
    old_m_h = m_h;
}




void AM_restoreScaleAndLoc(void)
{

    m_w = old_m_w;
    m_h = old_m_h;
    if (!followplayer)
    {
 m_x = old_m_x;
 m_y = old_m_y;
    } else {
 m_x = plr->mo->x - m_w/2;
 m_y = plr->mo->y - m_h/2;
    }
    m_x2 = m_x + m_w;
    m_y2 = m_y + m_h;


    scale_mtof = FixedDiv(f_w<<16, m_w);
    scale_ftom = FixedDiv((1<<16), scale_mtof);
}




void AM_addMark(void)
{
    markpoints[markpointnum].x = m_x + m_w/2;
    markpoints[markpointnum].y = m_y + m_h/2;
    markpointnum = (markpointnum + 1) % 10;

}





void AM_findMinMaxBoundaries(void)
{
    int i;
    fixed_t a;
    fixed_t b;

    min_x = min_y = 2147483647;
    max_x = max_y = -2147483647;

    for (i=0;i<numvertexes;i++)
    {
 if (vertexes[i].x < min_x)
     min_x = vertexes[i].x;
 else if (vertexes[i].x > max_x)
     max_x = vertexes[i].x;

 if (vertexes[i].y < min_y)
     min_y = vertexes[i].y;
 else if (vertexes[i].y > max_y)
     max_y = vertexes[i].y;
    }

    max_w = max_x - min_x;
    max_h = max_y - min_y;

    min_w = 2*16*(1<<16);
    min_h = 2*16*(1<<16);

    a = FixedDiv(f_w<<16, max_w);
    b = FixedDiv(f_h<<16, max_h);

    min_scale_mtof = a < b ? a : b;
    max_scale_mtof = FixedDiv(f_h<<16, 2*16*(1<<16));

}





void AM_changeWindowLoc(void)
{
    if (m_paninc.x || m_paninc.y)
    {
 followplayer = 0;
 f_oldloc.x = 2147483647;
    }

    m_x += m_paninc.x;
    m_y += m_paninc.y;

    if (m_x + m_w/2 > max_x)
 m_x = max_x - m_w/2;
    else if (m_x + m_w/2 < min_x)
 m_x = min_x - m_w/2;

    if (m_y + m_h/2 > max_y)
 m_y = max_y - m_h/2;
    else if (m_y + m_h/2 < min_y)
 m_y = min_y - m_h/2;

    m_x2 = m_x + m_w;
    m_y2 = m_y + m_h;
}





void AM_initVariables(void)
{
    int pnum;
    static event_t st_notify = { ev_keyup, ((('a'<<24)+('m'<<16)) | ('e'<<8)), 0, 0 };

    automapactive = true;
    fb = I_VideoBuffer;

    f_oldloc.x = 2147483647;
    amclock = 0;
    lightlev = 0;

    m_paninc.x = m_paninc.y = 0;
    ftom_zoommul = (1<<16);
    mtof_zoommul = (1<<16);

    m_w = FixedMul(((f_w)<<16),scale_ftom);
    m_h = FixedMul(((f_h)<<16),scale_ftom);


    if (playeringame[consoleplayer])
    {
        plr = &players[consoleplayer];
    }
    else
    {
        plr = &players[0];

 for (pnum=0;pnum<4;pnum++)
        {
     if (playeringame[pnum])
            {
                plr = &players[pnum];
  break;
            }
        }
    }

    m_x = plr->mo->x - m_w/2;
    m_y = plr->mo->y - m_h/2;
    AM_changeWindowLoc();


    old_m_x = m_x;
    old_m_y = m_y;
    old_m_w = m_w;
    old_m_h = m_h;


    ST_Responder(&st_notify);

}




void AM_loadPics(void)
{
    int i;
    char namebuf[9];

    for (i=0;i<10;i++)
    {
 snprintf(namebuf, 9, "AMMNUM%d", i);
 marknums[i] = W_CacheLumpName(namebuf, PU_STATIC);
    }

}

void AM_unloadPics(void)
{
    int i;
    char namebuf[9];

    for (i=0;i<10;i++)
    {
 snprintf(namebuf, 9, "AMMNUM%d", i);
 W_ReleaseLumpName(namebuf);
    }
}

void AM_clearMarks(void)
{
    int i;

    for (i=0;i<10;i++)
 markpoints[i].x = -1;
    markpointnum = 0;
}





void AM_LevelInit(void)
{
    leveljuststarted = 0;

    f_x = f_y = 0;
    f_w = finit_width;
    f_h = finit_height;

    AM_clearMarks();

    AM_findMinMaxBoundaries();
    scale_mtof = FixedDiv(min_scale_mtof, (int) (0*(1<<16)));
    if (scale_mtof > max_scale_mtof)
 scale_mtof = min_scale_mtof;
    scale_ftom = FixedDiv((1<<16), scale_mtof);
}







void AM_Stop (void)
{
    static event_t st_notify = { 0, ev_keyup, ((('a'<<24)+('m'<<16)) | ('x'<<8)), 0 };

    AM_unloadPics();
    automapactive = false;
    ST_Responder(&st_notify);
    stopped = true;
}




void AM_Start (void)
{
    static int lastlevel = -1, lastepisode = -1;

    if (!stopped) AM_Stop();
    stopped = false;
    if (lastlevel != gamemap || lastepisode != gameepisode)
    {
 AM_LevelInit();
 lastlevel = gamemap;
 lastepisode = gameepisode;
    }
    AM_initVariables();
    AM_loadPics();
}




void AM_minOutWindowScale(void)
{
    scale_mtof = min_scale_mtof;
    scale_ftom = FixedDiv((1<<16), scale_mtof);
    AM_activateNewScale();
}




void AM_maxOutWindowScale(void)
{
    scale_mtof = max_scale_mtof;
    scale_ftom = FixedDiv((1<<16), scale_mtof);
    AM_activateNewScale();
}





boolean
AM_Responder
( event_t* ev )
{

    int rc;
    static int bigstate=0;
    static char buffer[20];
    int key;

    rc = false;

    if (!automapactive)
    {
 if (ev->type == ev_keydown && ev->data1 == key_map_toggle)
 {
     AM_Start ();
     viewactive = false;
     rc = true;
 }
    }
    else if (ev->type == ev_keydown)
    {
 rc = true;
        key = ev->data1;

        if (key == key_map_east)
        {
            if (!followplayer) m_paninc.x = FixedMul(((4)<<16),scale_ftom);
            else rc = false;
        }
        else if (key == key_map_west)
        {
            if (!followplayer) m_paninc.x = -FixedMul(((4)<<16),scale_ftom);
            else rc = false;
        }
        else if (key == key_map_north)
        {
            if (!followplayer) m_paninc.y = FixedMul(((4)<<16),scale_ftom);
            else rc = false;
        }
        else if (key == key_map_south)
        {
            if (!followplayer) m_paninc.y = -FixedMul(((4)<<16),scale_ftom);
            else rc = false;
        }
        else if (key == key_map_zoomout)
        {
            mtof_zoommul = ((int) ((1<<16)/0));
            ftom_zoommul = ((int) (0*(1<<16)));
        }
        else if (key == key_map_zoomin)
        {
            mtof_zoommul = ((int) (0*(1<<16)));
            ftom_zoommul = ((int) ((1<<16)/0));
        }
        else if (key == key_map_toggle)
        {
            bigstate = 0;
            viewactive = true;
            AM_Stop ();
        }
        else if (key == key_map_maxzoom)
        {
            bigstate = !bigstate;
            if (bigstate)
            {
                AM_saveScaleAndLoc();
                AM_minOutWindowScale();
            }
            else AM_restoreScaleAndLoc();
        }
        else if (key == key_map_follow)
        {
            followplayer = !followplayer;
            f_oldloc.x = 2147483647;
            if (followplayer)
                plr->message = ("Follow Mode ON");
            else
                plr->message = ("Follow Mode OFF");
        }
        else if (key == key_map_grid)
        {
            grid = !grid;
            if (grid)
                plr->message = ("Grid ON");
            else
                plr->message = ("Grid OFF");
        }
        else if (key == key_map_mark)
        {
            M_snprintf(buffer, sizeof(buffer), "%s %d",
                       ("Marked Spot"), markpointnum);
            plr->message = buffer;
            AM_addMark();
        }
        else if (key == key_map_clearmark)
        {
            AM_clearMarks();
            plr->message = ("All Marks Cleared");
        }
        else
        {
            rc = false;
        }

 if (!deathmatch && cht_CheckCheat(&cheat_amap, ev->data2))
 {
     rc = false;
     cheating = (cheating+1) % 3;
 }
    }
    else if (ev->type == ev_keyup)
    {
        rc = false;
        key = ev->data1;

        if (key == key_map_east)
        {
            if (!followplayer) m_paninc.x = 0;
        }
        else if (key == key_map_west)
        {
            if (!followplayer) m_paninc.x = 0;
        }
        else if (key == key_map_north)
        {
            if (!followplayer) m_paninc.y = 0;
        }
        else if (key == key_map_south)
        {
            if (!followplayer) m_paninc.y = 0;
        }
        else if (key == key_map_zoomout || key == key_map_zoomin)
        {
            mtof_zoommul = (1<<16);
            ftom_zoommul = (1<<16);
        }
    }

    return rc;

}





void AM_changeWindowScale(void)
{


    scale_mtof = FixedMul(scale_mtof, mtof_zoommul);
    scale_ftom = FixedDiv((1<<16), scale_mtof);

    if (scale_mtof < min_scale_mtof)
 AM_minOutWindowScale();
    else if (scale_mtof > max_scale_mtof)
 AM_maxOutWindowScale();
    else
 AM_activateNewScale();
}





void AM_doFollowPlayer(void)
{

    if (f_oldloc.x != plr->mo->x || f_oldloc.y != plr->mo->y)
    {
 m_x = FixedMul((((FixedMul((plr->mo->x),scale_mtof)>>16))<<16),scale_ftom) - m_w/2;
 m_y = FixedMul((((FixedMul((plr->mo->y),scale_mtof)>>16))<<16),scale_ftom) - m_h/2;
 m_x2 = m_x + m_w;
 m_y2 = m_y + m_h;
 f_oldloc.x = plr->mo->x;
 f_oldloc.y = plr->mo->y;






    }

}




void AM_updateLightLev(void)
{
    static int nexttic = 0;

    static int litelevels[] = { 0, 4, 7, 10, 12, 14, 15, 15 };
    static int litelevelscnt = 0;


    if (amclock>nexttic)
    {
 lightlev = litelevels[litelevelscnt++];
 if (litelevelscnt == (sizeof(litelevels) / sizeof(*litelevels))) litelevelscnt = 0;
 nexttic = amclock + 6 - (amclock % 6);
    }

}





void AM_Ticker (void)
{

    if (!automapactive)
 return;

    amclock++;

    if (followplayer)
 AM_doFollowPlayer();


    if (ftom_zoommul != (1<<16))
 AM_changeWindowScale();


    if (m_paninc.x || m_paninc.y)
 AM_changeWindowLoc();




}





void AM_clearFB(int color)
{
    memset(fb, color, f_w*f_h);
}
boolean
AM_clipMline
( mline_t* ml,
  fline_t* fl )
{
    enum
    {
 LEFT =1,
 RIGHT =2,
 BOTTOM =4,
 TOP =8
    };

    register int outcode1 = 0;
    register int outcode2 = 0;
    register int outside;

    fpoint_t tmp;
    int dx;
    int dy;
    if (ml->a.y > m_y2)
 outcode1 = TOP;
    else if (ml->a.y < m_y)
 outcode1 = BOTTOM;

    if (ml->b.y > m_y2)
 outcode2 = TOP;
    else if (ml->b.y < m_y)
 outcode2 = BOTTOM;

    if (outcode1 & outcode2)
 return false;

    if (ml->a.x < m_x)
 outcode1 |= LEFT;
    else if (ml->a.x > m_x2)
 outcode1 |= RIGHT;

    if (ml->b.x < m_x)
 outcode2 |= LEFT;
    else if (ml->b.x > m_x2)
 outcode2 |= RIGHT;

    if (outcode1 & outcode2)
 return false;


    fl->a.x = (f_x + (FixedMul(((ml->a.x)-m_x),scale_mtof)>>16));
    fl->a.y = (f_y + (f_h - (FixedMul(((ml->a.y)-m_y),scale_mtof)>>16)));
    fl->b.x = (f_x + (FixedMul(((ml->b.x)-m_x),scale_mtof)>>16));
    fl->b.y = (f_y + (f_h - (FixedMul(((ml->b.y)-m_y),scale_mtof)>>16)));

    (outcode1) = 0; if ((fl->a.y) < 0) (outcode1) |= TOP; else if ((fl->a.y) >= f_h) (outcode1) |= BOTTOM; if ((fl->a.x) < 0) (outcode1) |= LEFT; else if ((fl->a.x) >= f_w) (outcode1) |= RIGHT;;
    (outcode2) = 0; if ((fl->b.y) < 0) (outcode2) |= TOP; else if ((fl->b.y) >= f_h) (outcode2) |= BOTTOM; if ((fl->b.x) < 0) (outcode2) |= LEFT; else if ((fl->b.x) >= f_w) (outcode2) |= RIGHT;;

    if (outcode1 & outcode2)
 return false;

    while (outcode1 | outcode2)
    {


 if (outcode1)
     outside = outcode1;
 else
     outside = outcode2;


 if (outside & TOP)
 {
     dy = fl->a.y - fl->b.y;
     dx = fl->b.x - fl->a.x;
     tmp.x = fl->a.x + (dx*(fl->a.y))/dy;
     tmp.y = 0;
 }
 else if (outside & BOTTOM)
 {
     dy = fl->a.y - fl->b.y;
     dx = fl->b.x - fl->a.x;
     tmp.x = fl->a.x + (dx*(fl->a.y-f_h))/dy;
     tmp.y = f_h-1;
 }
 else if (outside & RIGHT)
 {
     dy = fl->b.y - fl->a.y;
     dx = fl->b.x - fl->a.x;
     tmp.y = fl->a.y + (dy*(f_w-1 - fl->a.x))/dx;
     tmp.x = f_w-1;
 }
 else if (outside & LEFT)
 {
     dy = fl->b.y - fl->a.y;
     dx = fl->b.x - fl->a.x;
     tmp.y = fl->a.y + (dy*(-fl->a.x))/dx;
     tmp.x = 0;
 }
        else
        {
            tmp.x = 0;
            tmp.y = 0;
        }

 if (outside == outcode1)
 {
     fl->a = tmp;
     (outcode1) = 0; if ((fl->a.y) < 0) (outcode1) |= TOP; else if ((fl->a.y) >= f_h) (outcode1) |= BOTTOM; if ((fl->a.x) < 0) (outcode1) |= LEFT; else if ((fl->a.x) >= f_w) (outcode1) |= RIGHT;;
 }
 else
 {
     fl->b = tmp;
     (outcode2) = 0; if ((fl->b.y) < 0) (outcode2) |= TOP; else if ((fl->b.y) >= f_h) (outcode2) |= BOTTOM; if ((fl->b.x) < 0) (outcode2) |= LEFT; else if ((fl->b.x) >= f_w) (outcode2) |= RIGHT;;
 }

 if (outcode1 & outcode2)
     return false;
    }

    return true;
}






void
AM_drawFline
( fline_t* fl,
  int color )
{
    register int x;
    register int y;
    register int dx;
    register int dy;
    register int sx;
    register int sy;
    register int ax;
    register int ay;
    register int d;

    static int fuck = 0;


    if ( fl->a.x < 0 || fl->a.x >= f_w
    || fl->a.y < 0 || fl->a.y >= f_h
    || fl->b.x < 0 || fl->b.x >= f_w
    || fl->b.y < 0 || fl->b.y >= f_h)
    {
        fprintf(__stderrp, "fuck %d \r", fuck++);
 return;
    }



    dx = fl->b.x - fl->a.x;
    ax = 2 * (dx<0 ? -dx : dx);
    sx = dx<0 ? -1 : 1;

    dy = fl->b.y - fl->a.y;
    ay = 2 * (dy<0 ? -dy : dy);
    sy = dy<0 ? -1 : 1;

    x = fl->a.x;
    y = fl->a.y;

    if (ax > ay)
    {
 d = ay - ax/2;
 while (1)
 {
     fb[(y)*f_w+(x)]=(color);
     if (x == fl->b.x) return;
     if (d>=0)
     {
  y += sy;
  d -= ax;
     }
     x += sx;
     d += ay;
 }
    }
    else
    {
 d = ax - ay/2;
 while (1)
 {
     fb[(y)*f_w+(x)]=(color);
     if (y == fl->b.y) return;
     if (d >= 0)
     {
  x += sx;
  d -= ay;
     }
     y += sy;
     d += ax;
 }
    }
}





void
AM_drawMline
( mline_t* ml,
  int color )
{
    static fline_t fl;

    if (AM_clipMline(ml, &fl))
 AM_drawFline(&fl, color);
}






void AM_drawGrid(int color)
{
    fixed_t x, y;
    fixed_t start, end;
    mline_t ml;


    start = m_x;
    if ((start-bmaporgx)%(128<<16))
 start += (128<<16)
     - ((start-bmaporgx)%(128<<16));
    end = m_x + m_w;


    ml.a.y = m_y;
    ml.b.y = m_y+m_h;
    for (x=start; x<end; x+=(128<<16))
    {
 ml.a.x = x;
 ml.b.x = x;
 AM_drawMline(&ml, color);
    }


    start = m_y;
    if ((start-bmaporgy)%(128<<16))
 start += (128<<16)
     - ((start-bmaporgy)%(128<<16));
    end = m_y + m_h;


    ml.a.x = m_x;
    ml.b.x = m_x + m_w;
    for (y=start; y<end; y+=(128<<16))
    {
 ml.a.y = y;
 ml.b.y = y;
 AM_drawMline(&ml, color);
    }

}





void AM_drawWalls(void)
{
    int i;
    static mline_t l;

    for (i=0;i<numlines;i++)
    {
 l.a.x = lines[i].v1->x;
 l.a.y = lines[i].v1->y;
 l.b.x = lines[i].v2->x;
 l.b.y = lines[i].v2->y;
 if (cheating || (lines[i].flags & 256))
 {
     if ((lines[i].flags & 128) && !cheating)
  continue;
     if (!lines[i].backsector)
     {
  AM_drawMline(&l, (256-5*16)+lightlev);
     }
     else
     {
  if (lines[i].special == 39)
  {
      AM_drawMline(&l, (256-5*16)+16/2);
  }
  else if (lines[i].flags & 32)
  {
      if (cheating) AM_drawMline(&l, (256-5*16) + lightlev);
      else AM_drawMline(&l, (256-5*16)+lightlev);
  }
  else if (lines[i].backsector->floorheight
      != lines[i].frontsector->floorheight) {
      AM_drawMline(&l, (4*16) + lightlev);
  }
  else if (lines[i].backsector->ceilingheight
      != lines[i].frontsector->ceilingheight) {
      AM_drawMline(&l, (256-32+7)+lightlev);
  }
  else if (cheating) {
      AM_drawMline(&l, (6*16)+lightlev);
  }
     }
 }
 else if (plr->powers[pw_allmap])
 {
     if (!(lines[i].flags & 128)) AM_drawMline(&l, (6*16)+3);
 }
    }
}






void
AM_rotate
( fixed_t* x,
  fixed_t* y,
  angle_t a )
{
    fixed_t tmpx;

    tmpx =
 FixedMul(*x,finecosine[a>>19])
 - FixedMul(*y,finesine[a>>19]);

    *y =
 FixedMul(*x,finesine[a>>19])
 + FixedMul(*y,finecosine[a>>19]);

    *x = tmpx;
}

void
AM_drawLineCharacter
( mline_t* lineguy,
  int lineguylines,
  fixed_t scale,
  angle_t angle,
  int color,
  fixed_t x,
  fixed_t y )
{
    int i;
    mline_t l;

    for (i=0;i<lineguylines;i++)
    {
 l.a.x = lineguy[i].a.x;
 l.a.y = lineguy[i].a.y;

 if (scale)
 {
     l.a.x = FixedMul(scale, l.a.x);
     l.a.y = FixedMul(scale, l.a.y);
 }

 if (angle)
     AM_rotate(&l.a.x, &l.a.y, angle);

 l.a.x += x;
 l.a.y += y;

 l.b.x = lineguy[i].b.x;
 l.b.y = lineguy[i].b.y;

 if (scale)
 {
     l.b.x = FixedMul(scale, l.b.x);
     l.b.y = FixedMul(scale, l.b.y);
 }

 if (angle)
     AM_rotate(&l.b.x, &l.b.y, angle);

 l.b.x += x;
 l.b.y += y;

 AM_drawMline(&l, color);
    }
}

void AM_drawPlayers(void)
{
    int i;
    player_t* p;
    static int their_colors[] = { (7*16), (6*16), (4*16), (256-5*16) };
    int their_color = -1;
    int color;

    if (!netgame)
    {
 if (cheating)
     AM_drawLineCharacter
  (cheat_player_arrow, (sizeof(cheat_player_arrow) / sizeof(*cheat_player_arrow)), 0,
   plr->mo->angle, (256-47), plr->mo->x, plr->mo->y);
 else
     AM_drawLineCharacter
  (player_arrow, (sizeof(player_arrow) / sizeof(*player_arrow)), 0, plr->mo->angle,
   (256-47), plr->mo->x, plr->mo->y);
 return;
    }

    for (i=0;i<4;i++)
    {
 their_color++;
 p = &players[i];

 if ( (deathmatch && !singledemo) && p != plr)
     continue;

 if (!playeringame[i])
     continue;

 if (p->powers[pw_invisibility])
     color = 246;
 else
     color = their_colors[their_color];

 AM_drawLineCharacter
     (player_arrow, (sizeof(player_arrow) / sizeof(*player_arrow)), 0, p->mo->angle,
      color, p->mo->x, p->mo->y);
    }

}

void
AM_drawThings
( int colors,
  int colorrange)
{
    int i;
    mobj_t* t;

    for (i=0;i<numsectors;i++)
    {
 t = sectors[i].thinglist;
 while (t)
 {
     AM_drawLineCharacter
  (thintriangle_guy, (sizeof(thintriangle_guy) / sizeof(*thintriangle_guy)),
   16<<16, t->angle, colors+lightlev, t->x, t->y);
     t = t->snext;
 }
    }
}

void AM_drawMarks(void)
{
    int i, fx, fy, w, h;

    for (i=0;i<10;i++)
    {
 if (markpoints[i].x != -1)
 {


     w = 5;
     h = 6;
     fx = (f_x + (FixedMul(((markpoints[i].x)-m_x),scale_mtof)>>16));
     fy = (f_y + (f_h - (FixedMul(((markpoints[i].y)-m_y),scale_mtof)>>16)));
     if (fx >= f_x && fx <= f_w - w && fy >= f_y && fy <= f_h - h)
  V_DrawPatch(fx, fy, marknums[i]);
 }
    }

}

void AM_drawCrosshair(int color)
{
    fb[(f_w*(f_h+1))/2] = color;

}

void AM_Drawer (void)
{
    if (!automapactive) return;

    AM_clearFB(0);
    if (grid)
 AM_drawGrid(((6*16) + 16/2));
    AM_drawWalls();
    AM_drawPlayers();
    if (cheating==2)
 AM_drawThings((7*16), 16);
    AM_drawCrosshair((6*16));

    AM_drawMarks();

    V_MarkRect(f_x, f_y, f_w, f_h);

}
GameMode_t gamemode = indetermined;
GameMission_t gamemission = doom;
GameVersion_t gameversion = exe_final2;
char *gamedescription;


boolean modifiedgame;
char *doom1_endmsg[] =
{
  "are you sure you want to\nquit this great game?",
  "please don't leave, there's more\ndemons to toast!",
  "let's beat it -- this is turning\ninto a bloodbath!",
  "i wouldn't leave if i were you.\ndos is much worse.",
  "you're trying to say you like dos\nbetter than me, right?",
  "don't leave yet -- there's a\ndemon around that corner!",
  "ya know, next time you come in here\ni'm gonna toast ya.",
  "go ahead and leave. see if i care.",
};

char *doom2_endmsg[] =
{

  "are you sure you want to\nquit this great game?",
  "you want to quit?\nthen, thou hast lost an eighth!",
  "don't go now, there's a \ndimensional shambler waiting\nat the dos prompt!",
  "get outta here and go back\nto your boring programs.",
  "if i were your boss, i'd \n deathmatch ya in a minute!",
  "look, bud. you leave now\nand you forfeit your body count!",
  "just leave. when you come\nback, i'll be waiting with a bat.",
  "you're lucky i don't smack\nyou for thinking about leaving.",
};
static event_t events[64];
static int eventhead;
static int eventtail;





void D_PostEvent (event_t* ev)
{
    events[eventhead] = *ev;
    eventhead = (eventhead + 1) % 64;
}



event_t *D_PopEvent(void)
{
    event_t *result;



    if (eventtail == eventhead)
    {
        return ((void*)0);
    }

    result = &events[eventtail];



    eventtail = (eventtail + 1) % 64;

    return result;
}
weaponinfo_t weaponinfo[NUMWEAPONS] =
{
    {

 am_noammo,
 S_PUNCHUP,
 S_PUNCHDOWN,
 S_PUNCH,
 S_PUNCH1,
 S_NULL
    },
    {

 am_clip,
 S_PISTOLUP,
 S_PISTOLDOWN,
 S_PISTOL,
 S_PISTOL1,
 S_PISTOLFLASH
    },
    {

 am_shell,
 S_SGUNUP,
 S_SGUNDOWN,
 S_SGUN,
 S_SGUN1,
 S_SGUNFLASH1
    },
    {

 am_clip,
 S_CHAINUP,
 S_CHAINDOWN,
 S_CHAIN,
 S_CHAIN1,
 S_CHAINFLASH1
    },
    {

 am_misl,
 S_MISSILEUP,
 S_MISSILEDOWN,
 S_MISSILE,
 S_MISSILE1,
 S_MISSILEFLASH1
    },
    {

 am_cell,
 S_PLASMAUP,
 S_PLASMADOWN,
 S_PLASMA,
 S_PLASMA1,
 S_PLASMAFLASH1
    },
    {

 am_cell,
 S_BFGUP,
 S_BFGDOWN,
 S_BFG,
 S_BFG1,
 S_BFGFLASH1
    },
    {

 am_noammo,
 S_SAWUP,
 S_SAWDOWN,
 S_SAW,
 S_SAW1,
 S_NULL
    },
    {

 am_shell,
 S_DSGUNUP,
 S_DSGUNDOWN,
 S_DSGUN,
 S_DSGUN1,
 S_DSGUNFLASH1
    },
};


typedef struct
{
    char *name;
    GameMission_t mission;
    GameMode_t mode;
    char *description;
} iwad_t;

char *D_FindWADByName(char *filename);
char *D_TryFindWADByName(char *filename);
char *D_FindIWAD(int mask, GameMission_t *mission);
const iwad_t **D_FindAllIWADs(int mask);
char *D_SaveGameIWADName(GameMission_t gamemission);
char *D_SuggestIWADName(GameMission_t mission, GameMode_t mode);
char *D_SuggestGameName(GameMission_t mission, GameMode_t mode);
void D_CheckCorrectIWAD(GameMission_t mission);

extern int myargc;
extern char** myargv;



int M_CheckParm (char* check);



int M_CheckParmWithArgs(char *check, int num_args);

void M_FindResponseFile(void);



boolean M_ParmExists(char *check);



char *M_GetExecutableName(void);
void M_LoadDefaults(void);
void M_SaveDefaults(void);
void M_SaveDefaultsAlternate(char *main, char *extra);
void M_SetConfigDir(char *dir);
void M_BindVariable(char *name, void *variable);
boolean M_SetVariable(char *name, char *value);
int M_GetIntVariable(char *name);
const char *M_GetStrVariable(char *name);
float M_GetFloatVariable(char *name);
void M_SetConfigFilenames(char *main_config, char *extra_config);
char *M_GetSaveGameDir(char *iwadname);

extern char *configdir;




static const iwad_t iwads[] =
{
    { "doom2.wad", doom2, commercial, "Doom II" },
    { "plutonia.wad", pack_plut, commercial, "Final Doom: Plutonia Experiment" },
    { "tnt.wad", pack_tnt, commercial, "Final Doom: TNT: Evilution" },
    { "doom.wad", doom, retail, "Doom" },
    { "doom1.wad", doom, shareware, "Doom Shareware" },
    { "chex.wad", pack_chex, shareware, "Chex Quest" },
    { "hacx.wad", pack_hacx, commercial, "Hacx" },
    { "freedm.wad", doom2, commercial, "FreeDM" },
    { "freedoom2.wad", doom2, commercial, "Freedoom: Phase 2" },
    { "freedoom1.wad", doom, retail, "Freedoom: Phase 1" },
    { "heretic.wad", heretic, retail, "Heretic" },
    { "heretic1.wad", heretic, shareware, "Heretic Shareware" },
    { "hexen.wad", hexen, commercial, "Hexen" },

    { "strife1.wad", strife, commercial, "Strife" },
};







static boolean iwad_dirs_built = false;
static char *iwad_dirs[128];
static int num_iwad_dirs = 0;

static void AddIWADDir(char *dir)
{
    if (num_iwad_dirs < 128)
    {
        iwad_dirs[num_iwad_dirs] = dir;
        ++num_iwad_dirs;
    }
}
static boolean DirIsFile(char *path, char *filename)
{
    size_t path_len;
    size_t filename_len;

    path_len = strlen(path);
    filename_len = strlen(filename);

    return path_len >= filename_len + 1
        && path[path_len - filename_len - 1] == '/'
        && !strcasecmp(&path[path_len - filename_len], filename);
}





static char *CheckDirectoryHasIWAD(char *dir, char *iwadname)
{
    char *filename;




    if (DirIsFile(dir, iwadname) && M_FileExists(dir))
    {
        return strdup(dir);
    }




    if (!strcmp(dir, "."))
    {
        filename = strdup(iwadname);
    }
    else
    {
        filename = M_StringJoin(dir, "/", iwadname, ((void*)0));
    }

    printf("Trying IWAD file:%s\n", filename);

    if (M_FileExists(filename))
    {
        return filename;
    }

    free(filename);

    return ((void*)0);
}




static char *SearchDirectoryForIWAD(char *dir, int mask, GameMission_t *mission)
{
    char *filename;
    size_t i;

    for (i=0; i<(sizeof(iwads) / sizeof(*iwads)); ++i)
    {
        if (((1 << iwads[i].mission) & mask) == 0)
        {
            continue;
        }

        filename = CheckDirectoryHasIWAD(dir, (iwads[i].name));

        if (filename != ((void*)0))
        {
            *mission = iwads[i].mission;

            return filename;
        }
    }

    return ((void*)0);
}




static GameMission_t IdentifyIWADByName(char *name, int mask)
{
    size_t i;
    GameMission_t mission;
    char *p;

    p = strrchr(name, '/');

    if (p != ((void*)0))
    {
        name = p + 1;
    }

    mission = none;

    for (i=0; i<(sizeof(iwads) / sizeof(*iwads)); ++i)
    {




        if (((1 << iwads[i].mission) & mask) == 0)
            continue;



        if (!strcasecmp(name, iwads[i].name))
        {
            mission = iwads[i].mission;
            break;
        }
    }

    return mission;
}
static void BuildIWADDirList(void)
{
    AddIWADDir (".");



    iwad_dirs_built = true;

}





char *D_FindWADByName(char *name)
{
    char *path;
    int i;



    if (M_FileExists(name))
    {
        return name;
    }

    BuildIWADDirList();



    for (i=0; i<num_iwad_dirs; ++i)
    {




        if (DirIsFile(iwad_dirs[i], name) && M_FileExists(iwad_dirs[i]))
        {
            return strdup(iwad_dirs[i]);
        }



        path = M_StringJoin(iwad_dirs[i], "/", name, ((void*)0));

        if (M_FileExists(path))
        {
            return path;
        }

        free(path);
    }



    return ((void*)0);
}
char *D_TryFindWADByName(char *filename)
{
    char *result;

    result = D_FindWADByName(filename);

    if (result != ((void*)0))
    {
        return result;
    }
    else
    {
        return filename;
    }
}
char *D_FindIWAD(int mask, GameMission_t *mission)
{
    char *result;
    char *iwadfile;
    int iwadparm;
    int i;
    iwadparm = M_CheckParmWithArgs("-iwad", 1);

    if (iwadparm)
    {


        iwadfile = myargv[iwadparm + 1];

        result = D_FindWADByName(iwadfile);

        if (result == ((void*)0))
        {
            I_Error("IWAD file '%s' not found!", iwadfile);
        }

        *mission = IdentifyIWADByName(result, mask);
    }
    else
    {


        printf("-iwad not specified, trying a few iwad names\n");

        result = ((void*)0);

        BuildIWADDirList();

        for (i=0; result == ((void*)0) && i<num_iwad_dirs; ++i)
        {
            result = SearchDirectoryForIWAD(iwad_dirs[i], mask, mission);
        }
    }

    return result;
}



const iwad_t **D_FindAllIWADs(int mask)
{
    const iwad_t **result;
    int result_len;
    char *filename;
    int i;

    result = malloc(sizeof(iwad_t *) * ((sizeof(iwads) / sizeof(*iwads)) + 1));
    result_len = 0;



    for (i=0; i<(sizeof(iwads) / sizeof(*iwads)); ++i)
    {
        if (((1 << iwads[i].mission) & mask) == 0)
        {
            continue;
        }

        filename = D_FindWADByName(iwads[i].name);

        if (filename != ((void*)0))
        {
            result[result_len] = &iwads[i];
            ++result_len;
        }
    }



    result[result_len] = ((void*)0);

    return result;
}





char *D_SaveGameIWADName(GameMission_t gamemission)
{
    size_t i;
    for (i=0; i<(sizeof(iwads) / sizeof(*iwads)); ++i)
    {
        if (gamemission == iwads[i].mission)
        {
            return iwads[i].name;
        }
    }



    return "unknown.wad";
}

char *D_SuggestIWADName(GameMission_t mission, GameMode_t mode)
{
    int i;

    for (i = 0; i < (sizeof(iwads) / sizeof(*iwads)); ++i)
    {
        if (iwads[i].mission == mission && iwads[i].mode == mode)
        {
            return iwads[i].name;
        }
    }

    return "unknown.wad";
}

char *D_SuggestGameName(GameMission_t mission, GameMode_t mode)
{
    int i;

    for (i = 0; i < (sizeof(iwads) / sizeof(*iwads)); ++i)
    {
        if (iwads[i].mission == mission
         && (mode == indetermined || iwads[i].mode == mode))
        {
            return iwads[i].description;
        }
    }

    return "Unknown game?";
}
boolean NET_CL_Connect(net_addr_t *addr, net_connect_data_t *data);
void NET_CL_Disconnect(void);
void NET_CL_Run(void);
void NET_CL_Init(void);
void NET_CL_LaunchGame(void);
void NET_CL_StartGame(net_gamesettings_t *settings);
void NET_CL_SendTiccmd(ticcmd_t *ticcmd, int maketic);
boolean NET_CL_GetSettings(net_gamesettings_t *_settings);
void NET_Init(void);

void NET_BindVariables(void);

extern boolean net_client_connected;
extern boolean net_client_received_wait_data;
extern net_waitdata_t net_client_wait_data;
extern boolean net_waiting_for_launch;
extern char *net_player_name;

extern sha1_digest_t net_server_wad_sha1sum;
extern sha1_digest_t net_server_deh_sha1sum;
extern unsigned int net_server_is_freedoom;
extern sha1_digest_t net_local_wad_sha1sum;
extern sha1_digest_t net_local_deh_sha1sum;
extern unsigned int net_local_is_freedoom;

extern boolean drone;
extern void NET_WaitForLaunch(void);
extern net_addr_t net_broadcast_addr;

net_context_t *NET_NewContext(void);
void NET_AddModule(net_context_t *context, net_module_t *module);
void NET_SendPacket(net_addr_t *addr, net_packet_t *packet);
void NET_SendBroadcast(net_context_t *context, net_packet_t *packet);
boolean NET_RecvPacket(net_context_t *context, net_addr_t **addr,
                       net_packet_t **packet);
char *NET_AddrToString(net_addr_t *addr);
void NET_FreeAddress(net_addr_t *addr);
net_addr_t *NET_ResolveAddress(net_context_t *context, char *address);
typedef void (*net_query_callback_t)(net_addr_t *addr,
                                     net_querydata_t *querydata,
                                     unsigned int ping_time,
                                     void *user_data);

extern int NET_StartLANQuery(void);
extern int NET_StartMasterQuery(void);

extern void NET_LANQuery(void);
extern void NET_MasterQuery(void);
extern void NET_QueryAddress(char *addr);
extern net_addr_t *NET_FindLANServer(void);

extern int NET_Query_Poll(net_query_callback_t callback, void *user_data);

extern net_addr_t *NET_Query_ResolveMaster(net_context_t *context);
extern void NET_Query_AddToMaster(net_addr_t *master_addr);
extern boolean NET_Query_CheckAddedToMaster(boolean *result);
extern void NET_Query_MasterResponse(net_packet_t *packet);
void NET_SV_Init(void);



void NET_SV_Run(void);




void NET_SV_Shutdown(void);



void NET_SV_AddModule(net_module_t *module);



void NET_SV_RegisterWithMaster(void);
extern net_module_t net_sdl_module;
extern net_module_t net_loop_client_module;
extern net_module_t net_loop_server_module;



typedef struct
{
    ticcmd_t cmds[8];
    boolean ingame[8];
} ticcmd_set_t;
static ticcmd_set_t ticdata[128];



static int maketic;



static int recvtic;



int gametic;




boolean singletics = false;



static int localplayer;



static int skiptics = 0;




int ticdup;



fixed_t offsetms;



static boolean new_sync = true;



static loop_interface_t *loop_interface = ((void*)0);





static boolean local_playeringame[8];





static int player_class;




static int GetAdjustedTime(void)
{
    int time_ms;

    time_ms = I_GetTimeMS();

    if (new_sync)
    {



        time_ms += (offsetms / (1<<16));
    }

    return (time_ms * 35) / 1000;
}

static boolean BuildNewTic(void)
{
    int gameticdiv;
    ticcmd_t cmd;

    gameticdiv = gametic/ticdup;

    I_StartTic ();
    loop_interface->ProcessEvents();



    loop_interface->RunMenu();

    if (drone)
    {


        return false;
    }

    if (new_sync)
    {



       if (!net_client_connected && maketic - gameticdiv > 2)
           return false;



       if (maketic - gameticdiv > 8)
           return false;
    }
    else
    {
       if (maketic - gameticdiv >= 5)
           return false;
    }


    memset(&cmd, 0, sizeof(ticcmd_t));
    loop_interface->BuildTiccmd(&cmd, maketic);
    ticdata[maketic % 128].cmds[localplayer] = cmd;
    ticdata[maketic % 128].ingame[localplayer] = true;

    ++maketic;

    return true;
}






int lasttime;

void NetUpdate (void)
{
    int nowtime;
    int newtics;
    int i;




    if (singletics)
        return;
    nowtime = GetAdjustedTime() / ticdup;
    newtics = nowtime - lasttime;

    lasttime = nowtime;

    if (skiptics <= newtics)
    {
        newtics -= skiptics;
        skiptics = 0;
    }
    else
    {
        skiptics -= newtics;
        newtics = 0;
    }



    for (i=0 ; i<newtics ; i++)
    {
        if (!BuildNewTic())
        {
            break;
        }
    }
}

static void D_Disconnected(void)
{


    if (drone)
    {
        I_Error("Disconnected from server in drone mode.");
    }



    printf("Disconnected from server.\n");
}






void D_ReceiveTic(ticcmd_t *ticcmds, boolean *players_mask)
{
    int i;



    if (ticcmds == ((void*)0) && players_mask == ((void*)0))
    {
        D_Disconnected();
        return;
    }

    for (i = 0; i < 8; ++i)
    {
        if (!drone && i == localplayer)
        {

        }
        else
        {
            ticdata[recvtic % 128].cmds[i] = ticcmds[i];
            ticdata[recvtic % 128].ingame[i] = players_mask[i];
        }
    }

    ++recvtic;
}







void D_StartGameLoop(void)
{
    lasttime = GetAdjustedTime() / ticdup;
}
void D_StartNetGame(net_gamesettings_t *settings,
                    netgame_startup_callback_t callback)
{
    settings->consoleplayer = 0;
 settings->num_players = 1;
 settings->player_classes[0] = player_class;
 settings->new_sync = 0;
 settings->extratics = 1;
 settings->ticdup = 1;

 ticdup = settings->ticdup;
 new_sync = settings->new_sync;

}

boolean D_InitNetGame(net_connect_data_t *connect_data)
{
    boolean result = false;







    I_AtExit(D_QuitNetGame, true);

    player_class = connect_data->player_class;
    return result;
}







void D_QuitNetGame (void)
{




}

static int GetLowTic(void)
{
    int lowtic;

    lowtic = maketic;
    return lowtic;
}

static int frameon;
static int frameskip[4];
static int oldnettics;

static void OldNetSync(void)
{
    unsigned int i;
    int keyplayer = -1;

    frameon++;




    for (i=0 ; i<8 ; i++)
    {
        if (local_playeringame[i])
        {
            keyplayer = i;
            break;
        }
    }

    if (keyplayer < 0)
    {


        return;
    }

    if (localplayer == keyplayer)
    {

    }
    else
    {
        if (maketic <= recvtic)
        {
            lasttime--;

        }

        frameskip[frameon & 3] = oldnettics > recvtic;
        oldnettics = maketic;

        if (frameskip[0] && frameskip[1] && frameskip[2] && frameskip[3])
        {
            skiptics = 1;

        }
    }
}



static boolean PlayersInGame(void)
{
    boolean result = false;
    unsigned int i;




    if (net_client_connected)
    {
        for (i = 0; i < 8; ++i)
        {
            result = result || local_playeringame[i];
        }
    }




    if (!drone)
    {
        result = true;
    }

    return result;
}




static void TicdupSquash(ticcmd_set_t *set)
{
    ticcmd_t *cmd;
    unsigned int i;

    for (i = 0; i < 8 ; ++i)
    {
        cmd = &set->cmds[i];
        cmd->chatchar = 0;
        if (cmd->buttons & BT_SPECIAL)
            cmd->buttons = 0;
    }
}




static void SinglePlayerClear(ticcmd_set_t *set)
{
    unsigned int i;

    for (i = 0; i < 8; ++i)
    {
        if (i != localplayer)
        {
            set->ingame[i] = false;
        }
    }
}





void TryRunTics (void)
{
    int i;
    int lowtic;
    int entertic;
    static int oldentertics;
    int realtics;
    int availabletics;
    int counts;


    entertic = I_GetTime() / ticdup;
    realtics = entertic - oldentertics;
    oldentertics = entertic;




    if (singletics)
    {
        BuildNewTic();
    }
    else
    {
        NetUpdate ();
    }

    lowtic = GetLowTic();

    availabletics = lowtic - gametic/ticdup;



    if (new_sync)
    {
 counts = availabletics;
    }
    else
    {

        if (realtics < availabletics-1)
            counts = realtics+1;
        else if (realtics < availabletics)
            counts = realtics;
        else
            counts = availabletics;

        if (counts < 1)
            counts = 1;

        if (net_client_connected)
        {
            OldNetSync();
        }
    }

    if (counts < 1)
 counts = 1;



    while (!PlayersInGame() || lowtic < gametic/ticdup + counts)
    {
 NetUpdate ();

        lowtic = GetLowTic();

 if (lowtic < gametic/ticdup)
     I_Error ("TryRunTics: lowtic < gametic");




 if (I_GetTime() / ticdup - entertic > 0)
 {
     return;
 }

        I_Sleep(1);
    }


    while (counts--)
    {
        ticcmd_set_t *set;

        if (!PlayersInGame())
        {
            return;
        }

        set = &ticdata[(gametic / ticdup) % 128];

        if (!net_client_connected)
        {
            SinglePlayerClear(set);
        }

 for (i=0 ; i<ticdup ; i++)
 {
            if (gametic/ticdup > lowtic)
                I_Error ("gametic>lowtic");

            memcpy(local_playeringame, set->ingame, sizeof(local_playeringame));

            loop_interface->RunTic(set->cmds, set->ingame);
     gametic++;



            TicdupSquash(set);
 }

 NetUpdate ();
    }
}

void D_RegisterLoopCallbacks(loop_interface_t *i)
{
    loop_interface = i;
}






typedef struct sfxinfo_struct sfxinfo_t;

struct sfxinfo_struct
{

    char *tagname;




    char name[9];


    int priority;


    sfxinfo_t *link;


    int pitch;


    int volume;




    int usefulness;


    int lumpnum;



    int numchannels;


    void *driver_data;
};




typedef struct
{

    char *name;


    int lumpnum;


    void *data;


    void *handle;

} musicinfo_t;

typedef enum
{
    SNDDEVICE_NONE = 0,
    SNDDEVICE_PCSPEAKER = 1,
    SNDDEVICE_ADLIB = 2,
    SNDDEVICE_SB = 3,
    SNDDEVICE_PAS = 4,
    SNDDEVICE_GUS = 5,
    SNDDEVICE_WAVEBLASTER = 6,
    SNDDEVICE_SOUNDCANVAS = 7,
    SNDDEVICE_GENMIDI = 8,
    SNDDEVICE_AWE32 = 9,
    SNDDEVICE_CD = 10,
} snddevice_t;



typedef struct
{


    snddevice_t *sound_devices;
    int num_sound_devices;




    boolean (*Init)(boolean use_sfx_prefix);



    void (*Shutdown)(void);



    int (*GetSfxLumpNum)(sfxinfo_t *sfxinfo);



    void (*Update)(void);



    void (*UpdateSoundParams)(int channel, int vol, int sep);




    int (*StartSound)(sfxinfo_t *sfxinfo, int channel, int vol, int sep);



    void (*StopSound)(int channel);



    boolean (*SoundIsPlaying)(int channel);



    void (*CacheSounds)(sfxinfo_t *sounds, int num_sounds);

} sound_module_t;

void I_InitSound(boolean use_sfx_prefix);
void I_ShutdownSound(void);
int I_GetSfxLumpNum(sfxinfo_t *sfxinfo);
void I_UpdateSound(void);
void I_UpdateSoundParams(int channel, int vol, int sep);
int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep);
void I_StopSound(int channel);
boolean I_SoundIsPlaying(int channel);
void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds);



typedef struct
{


    snddevice_t *sound_devices;
    int num_sound_devices;



    boolean (*Init)(void);



    void (*Shutdown)(void);



    void (*SetMusicVolume)(int volume);



    void (*PauseMusic)(void);



    void (*ResumeMusic)(void);




    void *(*RegisterSong)(void *data, int len);



    void (*UnRegisterSong)(void *handle);



    void (*PlaySong)(void *handle, boolean looping);



    void (*StopSong)(void);



    boolean (*MusicIsPlaying)(void);



    void (*Poll)(void);
} music_module_t;

void I_InitMusic(void);
void I_ShutdownMusic(void);
void I_SetMusicVolume(int volume);
void I_PauseSong(void);
void I_ResumeSong(void);
void *I_RegisterSong(void *data, int len);
void I_UnRegisterSong(void *handle);
void I_PlaySong(void *handle, boolean looping);
void I_StopSong(void);
boolean I_MusicIsPlaying(void);

extern int snd_sfxdevice;
extern int snd_musicdevice;
extern int snd_samplerate;
extern int snd_cachesize;
extern int snd_maxslicetime_ms;
extern char *snd_musiccmd;

void I_BindSoundVariables(void);



void I_InitTimidityConfig(void);




extern sound_module_t sound_pcsound_module;
extern music_module_t music_opl_module;



extern int opl_io_port;



extern char *timidity_cfg_path;


extern sfxinfo_t S_sfx[];


extern musicinfo_t S_music[];





typedef enum
{
    mus_None,
    mus_e1m1,
    mus_e1m2,
    mus_e1m3,
    mus_e1m4,
    mus_e1m5,
    mus_e1m6,
    mus_e1m7,
    mus_e1m8,
    mus_e1m9,
    mus_e2m1,
    mus_e2m2,
    mus_e2m3,
    mus_e2m4,
    mus_e2m5,
    mus_e2m6,
    mus_e2m7,
    mus_e2m8,
    mus_e2m9,
    mus_e3m1,
    mus_e3m2,
    mus_e3m3,
    mus_e3m4,
    mus_e3m5,
    mus_e3m6,
    mus_e3m7,
    mus_e3m8,
    mus_e3m9,
    mus_inter,
    mus_intro,
    mus_bunny,
    mus_victor,
    mus_introa,
    mus_runnin,
    mus_stalks,
    mus_countd,
    mus_betwee,
    mus_doom,
    mus_the_da,
    mus_shawn,
    mus_ddtblu,
    mus_in_cit,
    mus_dead,
    mus_stlks2,
    mus_theda2,
    mus_doom2,
    mus_ddtbl2,
    mus_runni2,
    mus_dead2,
    mus_stlks3,
    mus_romero,
    mus_shawn2,
    mus_messag,
    mus_count2,
    mus_ddtbl3,
    mus_ampie,
    mus_theda3,
    mus_adrian,
    mus_messg2,
    mus_romer2,
    mus_tense,
    mus_shawn3,
    mus_openin,
    mus_evil,
    mus_ultima,
    mus_read_m,
    mus_dm2ttl,
    mus_dm2int,
    NUMMUSIC
} musicenum_t;






typedef enum
{
    sfx_None,
    sfx_pistol,
    sfx_shotgn,
    sfx_sgcock,
    sfx_dshtgn,
    sfx_dbopn,
    sfx_dbcls,
    sfx_dbload,
    sfx_plasma,
    sfx_bfg,
    sfx_sawup,
    sfx_sawidl,
    sfx_sawful,
    sfx_sawhit,
    sfx_rlaunc,
    sfx_rxplod,
    sfx_firsht,
    sfx_firxpl,
    sfx_pstart,
    sfx_pstop,
    sfx_doropn,
    sfx_dorcls,
    sfx_stnmov,
    sfx_swtchn,
    sfx_swtchx,
    sfx_plpain,
    sfx_dmpain,
    sfx_popain,
    sfx_vipain,
    sfx_mnpain,
    sfx_pepain,
    sfx_slop,
    sfx_itemup,
    sfx_wpnup,
    sfx_oof,
    sfx_telept,
    sfx_posit1,
    sfx_posit2,
    sfx_posit3,
    sfx_bgsit1,
    sfx_bgsit2,
    sfx_sgtsit,
    sfx_cacsit,
    sfx_brssit,
    sfx_cybsit,
    sfx_spisit,
    sfx_bspsit,
    sfx_kntsit,
    sfx_vilsit,
    sfx_mansit,
    sfx_pesit,
    sfx_sklatk,
    sfx_sgtatk,
    sfx_skepch,
    sfx_vilatk,
    sfx_claw,
    sfx_skeswg,
    sfx_pldeth,
    sfx_pdiehi,
    sfx_podth1,
    sfx_podth2,
    sfx_podth3,
    sfx_bgdth1,
    sfx_bgdth2,
    sfx_sgtdth,
    sfx_cacdth,
    sfx_skldth,
    sfx_brsdth,
    sfx_cybdth,
    sfx_spidth,
    sfx_bspdth,
    sfx_vildth,
    sfx_kntdth,
    sfx_pedth,
    sfx_skedth,
    sfx_posact,
    sfx_bgact,
    sfx_dmact,
    sfx_bspact,
    sfx_bspwlk,
    sfx_vilact,
    sfx_noway,
    sfx_barexp,
    sfx_punch,
    sfx_hoof,
    sfx_metal,
    sfx_chgun,
    sfx_tink,
    sfx_bdopn,
    sfx_bdcls,
    sfx_itmbk,
    sfx_flame,
    sfx_flamst,
    sfx_getpow,
    sfx_bospit,
    sfx_boscub,
    sfx_bossit,
    sfx_bospn,
    sfx_bosdth,
    sfx_manatk,
    sfx_mandth,
    sfx_sssit,
    sfx_ssdth,
    sfx_keenpn,
    sfx_keendt,
    sfx_skeact,
    sfx_skesit,
    sfx_skeatk,
    sfx_radio,
    NUMSFX
} sfxenum_t;




boolean W_ParseCommandLine(void);

void S_Init(int sfxVolume, int musicVolume);




void S_Shutdown(void);
void S_Start(void);






void S_StartSound(void *origin, int sound_id);


void S_StopSound(mobj_t *origin);



void S_StartMusic(int music_id);



void S_ChangeMusic(int music_id, int looping);


boolean S_MusicPlaying(void);


void S_StopMusic(void);


void S_PauseSound(void);
void S_ResumeSound(void);





void S_UpdateSounds(mobj_t *listener);

void S_SetMusicVolume(int volume);
void S_SetSfxVolume(int volume);

extern int snd_channels;


boolean F_Responder (event_t* ev);


void F_Ticker (void);


void F_Drawer (void);


void F_StartFinale (void);
enum
{

    wipe_ColorXForm,


    wipe_Melt,

    wipe_NUMWIPES
};

int
wipe_StartScreen
( int x,
  int y,
  int width,
  int height );


int
wipe_EndScreen
( int x,
  int y,
  int width,
  int height );


int
wipe_ScreenWipe
( int wipeno,
  int x,
  int y,
  int width,
  int height,
  int ticks );





boolean M_Responder (event_t *ev);




void M_Ticker (void);



void M_Drawer (void);



void M_Init (void);



void M_StartControlPanel (void);



extern int detailLevel;
extern int screenblocks;
char *P_TempSaveGameFile(void);



char *P_SaveGameFile(int slot);



boolean P_ReadSaveGameHeader(void);
void P_WriteSaveGameHeader(char *description);



boolean P_ReadSaveGameEOF(void);
void P_WriteSaveGameEOF(void);



void P_ArchivePlayers (void);
void P_UnArchivePlayers (void);
void P_ArchiveWorld (void);
void P_UnArchiveWorld (void);
void P_ArchiveThinkers (void);
void P_UnArchiveThinkers (void);
void P_ArchiveSpecials (void);
void P_UnArchiveSpecials (void);

extern FILE *save_stream;
extern boolean savegame_error;

void I_Endoom(byte *data);
void I_InitJoystick(void);
void I_ShutdownJoystick(void);
void I_UpdateJoystick(void);

void I_BindJoystickVariables(void);




void G_DeathMatchSpawnPlayer (int playernum);

void G_InitNew (skill_t skill, int episode, int map);




void G_DeferedInitNew (skill_t skill, int episode, int map);

void G_DeferedPlayDemo (char* demo);



void G_LoadGame (char* name);

void G_DoLoadGame (void);


void G_SaveGame (int slot, char* description);


void G_RecordDemo (char* name);

void G_BeginRecording (void);

void G_PlayDemo (char* name);
void G_TimeDemo (char* name);
boolean G_CheckDemoStatus (void);

void G_ExitLevel (void);
void G_SecretExitLevel (void);

void G_WorldDone (void);



void G_BuildTiccmd (ticcmd_t *cmd, int maketic);

void G_Ticker (void);
boolean G_Responder (event_t* ev);

void G_ScreenShot (void);

void G_DrawMouseSpeedBox(void);
int G_VanillaVersionCode(void);

extern int vanilla_savegame_limit;
extern int vanilla_demo_limit;

void HU_Init(void);
void HU_Start(void);

boolean HU_Responder(event_t* ev);

void HU_Ticker(void);
void HU_Drawer(void);
char HU_dequeueChatChar(void);
void HU_Erase(void);

extern char *chat_macros[10];
typedef enum
{
    NoState = -1,
    StatCount,
    ShowNextLoc,
} stateenum_t;


void WI_Ticker (void);



void WI_Drawer (void);


void WI_Start(wbstartstruct_t* wbstartstruct);


void WI_End(void);



void NET_DedicatedServer(void);


void
P_SetupLevel
( int episode,
  int map,
  int playermask,
  skill_t skill);


void P_Init (void);

void StatCopy(wbstartstruct_t *stats);
void StatDump(void);

void D_ProcessEvents (void);





void D_PageTicker (void);
void D_PageDrawer (void);
void D_AdvanceDemo (void);
void D_DoAdvanceDemo (void);
void D_StartTitle (void);





extern gameaction_t gameaction;
void D_DoomLoop (void);



char * savegamedir;



char * iwadfile;


boolean devparm;
boolean nomonsters;
boolean respawnparm;
boolean fastparm;





extern boolean inhelpscreens;

skill_t startskill;
int startepisode;
int startmap;
boolean autostart;
int startloadgame;

boolean advancedemo;


boolean storedemo;


boolean bfgedition;


boolean main_loop_started = false;

char wadfile[1024];
char mapdir[1024];

int show_endoom = 1;


void D_ConnectNetGame(void);
void D_CheckNetGame(void);






void D_ProcessEvents (void)
{
    event_t* ev;


    if (storedemo)
        return;

    while ((ev = D_PopEvent()) != ((void*)0))
    {
 if (M_Responder (ev))
     continue;
 G_Responder (ev);
    }
}
gamestate_t wipegamestate = GS_DEMOSCREEN;
extern boolean setsizeneeded;
extern int showMessages;
void R_ExecuteSetViewSize (void);

void D_Display (void)
{
    static boolean viewactivestate = false;
    static boolean menuactivestate = false;
    static boolean inhelpscreensstate = false;
    static boolean fullscreen = false;
    static gamestate_t oldgamestate = -1;
    static int borderdrawcount;
    int nowtime;
    int tics;
    int wipestart;
    int y;
    boolean done;
    boolean wipe;
    boolean redrawsbar;

    if (nodrawers)
     return;

    redrawsbar = false;


    if (setsizeneeded)
    {
  R_ExecuteSetViewSize ();
  oldgamestate = -1;
  borderdrawcount = 3;
    }


    if (gamestate != wipegamestate)
  {
  wipe = true;
  wipe_StartScreen(0, 0, 320, 200);
    }
    else
     wipe = false;

    if (gamestate == GS_LEVEL && gametic)
     HU_Erase();


    switch (gamestate)
    {
      case GS_LEVEL:
  if (!gametic)
   break;
  if (automapactive)
   AM_Drawer ();
  if (wipe || (viewheight != 200 && fullscreen) )
   redrawsbar = true;
  if (inhelpscreensstate && !inhelpscreens)
   redrawsbar = true;
  ST_Drawer (viewheight == 200, redrawsbar );
  fullscreen = viewheight == 200;
  break;

      case GS_INTERMISSION:
  WI_Drawer ();
  break;

      case GS_FINALE:
  F_Drawer ();
  break;

      case GS_DEMOSCREEN:
  D_PageDrawer ();
  break;
    }


    I_UpdateNoBlit ();


    if (gamestate == GS_LEVEL && !automapactive && gametic)
     R_RenderPlayerView (&players[displayplayer]);

    if (gamestate == GS_LEVEL && gametic)
     HU_Drawer ();


    if (gamestate != oldgamestate && gamestate != GS_LEVEL)
     I_SetPalette (W_CacheLumpName (("PLAYPAL"),PU_CACHE));


    if (gamestate == GS_LEVEL && oldgamestate != GS_LEVEL)
    {
  viewactivestate = false;
  R_FillBackScreen ();
    }


    if (gamestate == GS_LEVEL && !automapactive && scaledviewwidth != 320)
    {
  if (menuactive || menuactivestate || !viewactivestate)
   borderdrawcount = 3;
  if (borderdrawcount)
  {
   R_DrawViewBorder ();
   borderdrawcount--;
  }
    }

    if (testcontrols)
    {


        V_DrawMouseSpeedBox(testcontrols_mousespeed);
    }

    menuactivestate = menuactive;
    viewactivestate = viewactive;
    inhelpscreensstate = inhelpscreens;
    oldgamestate = wipegamestate = gamestate;


    if (paused)
    {
  if (automapactive)
   y = 4;
  else
   y = viewwindowy+4;
  V_DrawPatchDirect(viewwindowx + (scaledviewwidth - 68) / 2, y,
         W_CacheLumpName (("M_PAUSE"), PU_CACHE));
    }



    M_Drawer ();
    NetUpdate ();



    if (!wipe)
    {
 I_FinishUpdate ();
 return;
    }


    wipe_EndScreen(0, 0, 320, 200);

    wipestart = I_GetTime () - 1;

    do
    {
 do
 {
     nowtime = I_GetTime ();
     tics = nowtime - wipestart;
            I_Sleep(1);
 } while (tics <= 0);

 wipestart = nowtime;
 done = wipe_ScreenWipe(wipe_Melt
          , 0, 0, 320, 200, tics);
 I_UpdateNoBlit ();
 M_Drawer ();
 I_FinishUpdate ();
    } while (!done);
}





void D_BindVariables(void)
{
    int i;

    M_ApplyPlatformDefaults();

    I_BindVideoVariables();
    I_BindJoystickVariables();
    I_BindSoundVariables();

    M_BindBaseControls();
    M_BindWeaponControls();
    M_BindMapControls();
    M_BindMenuControls();
    M_BindChatControls(4);

    key_multi_msgplayer[0] = 'g';
    key_multi_msgplayer[1] = 'i';
    key_multi_msgplayer[2] = 'b';
    key_multi_msgplayer[3] = 'r';





    M_BindVariable("mouse_sensitivity", &mouseSensitivity);
    M_BindVariable("sfx_volume", &sfxVolume);
    M_BindVariable("music_volume", &musicVolume);
    M_BindVariable("show_messages", &showMessages);
    M_BindVariable("screenblocks", &screenblocks);
    M_BindVariable("detaillevel", &detailLevel);
    M_BindVariable("snd_channels", &snd_channels);
    M_BindVariable("vanilla_savegame_limit", &vanilla_savegame_limit);
    M_BindVariable("vanilla_demo_limit", &vanilla_demo_limit);
    M_BindVariable("show_endoom", &show_endoom);



    for (i=0; i<10; ++i)
    {
        char buf[12];

        M_snprintf(buf, sizeof(buf), "chatmacro%i", i);
        M_BindVariable(buf, &chat_macros[i]);
    }
}







boolean D_GrabMouseCallback(void)
{


    if (drone)
        return false;



    if (menuactive || paused)
        return false;



    return (gamestate == GS_LEVEL) && !demoplayback && !advancedemo;
}

void doomgeneric_Tick()
{

    I_StartFrame ();

    TryRunTics ();

    S_UpdateSounds (players[consoleplayer].mo);


    if (screenvisible)
    {
        D_Display ();
    }
}




void D_DoomLoop (void)
{
    if (bfgedition &&
        (demorecording || (gameaction == ga_playdemo) || netgame))
    {
        printf(" WARNING: You are playing using one of the Doom Classic\n"
               " IWAD files shipped with the Doom 3: BFG Edition. These are\n"
               " known to be incompatible with the regular IWAD files and\n"
               " may cause demos and network games to get out of sync.\n");
    }

    if (demorecording)
     G_BeginRecording ();

    main_loop_started = true;

    TryRunTics();

    I_SetWindowTitle(gamedescription);
    I_GraphicsCheckCommandLine();
    I_SetGrabMouseCallback(D_GrabMouseCallback);
    I_InitGraphics();
    I_EnableLoadingDisk();

    V_RestoreBuffer();
    R_ExecuteSetViewSize();

    D_StartGameLoop();

    if (testcontrols)
    {
        wipegamestate = gamestate;
    }

    doomgeneric_Tick();
}






int demosequence;
int pagetic;
char *pagename;






void D_PageTicker (void)
{
    if (--pagetic < 0)
 D_AdvanceDemo ();
}






void D_PageDrawer (void)
{
    V_DrawPatch (0, 0, W_CacheLumpName(pagename, PU_CACHE));
}






void D_AdvanceDemo (void)
{
    advancedemo = true;
}






void D_DoAdvanceDemo (void)
{
    players[consoleplayer].playerstate = PST_LIVE;
    advancedemo = false;
    usergame = false;
    paused = false;
    gameaction = ga_nothing;
    if (gameversion == exe_ultimate || gameversion == exe_final)
      demosequence = (demosequence+1)%7;
    else
      demosequence = (demosequence+1)%6;

    switch (demosequence)
    {
      case 0:
 if ( gamemode == commercial )
     pagetic = 35 * 11;
 else
     pagetic = 170;
 gamestate = GS_DEMOSCREEN;
 pagename = ("TITLEPIC");
 if ( gamemode == commercial )
   S_StartMusic(mus_dm2ttl);
 else
   S_StartMusic (mus_intro);
 break;
      case 1:
 G_DeferedPlayDemo(("demo1"));
 break;
      case 2:
 pagetic = 200;
 gamestate = GS_DEMOSCREEN;
 pagename = ("CREDIT");
 break;
      case 3:
 G_DeferedPlayDemo(("demo2"));
 break;
      case 4:
 gamestate = GS_DEMOSCREEN;
 if ( gamemode == commercial)
 {
     pagetic = 35 * 11;
     pagename = ("TITLEPIC");
     S_StartMusic(mus_dm2ttl);
 }
 else
 {
     pagetic = 200;

     if ( gamemode == retail )
       pagename = ("CREDIT");
     else
       pagename = ("HELP2");
 }
 break;
      case 5:
 G_DeferedPlayDemo(("demo3"));
 break;

      case 6:
 G_DeferedPlayDemo(("demo4"));
 break;
    }



    if (bfgedition && !strcasecmp(pagename, "TITLEPIC")
        && W_CheckNumForName("titlepic") < 0)
    {
        pagename = ("INTERPIC");
    }
}






void D_StartTitle (void)
{
    gameaction = ga_nothing;
    demosequence = -1;
    D_AdvanceDemo ();
}






static char *banners[] =
{

    "                         "
    "DOOM 2: Hell on Earth v%i.%i"
    "                           ",

    "                            "
    "DOOM Shareware Startup v%i.%i"
    "                           ",

    "                            "
    "DOOM Registered Startup v%i.%i"
    "                           ",

    "                          "
    "DOOM System Startup v%i.%i"
    "                          ",

    "                         "
    "The Ultimate DOOM Startup v%i.%i"
    "                        ",

    "                     "
    "DOOM 2: TNT - Evilution v%i.%i"
    "                           ",

    "                   "
    "DOOM 2: Plutonia Experiment v%i.%i"
    "                           ",
};






static char *GetGameName(char *gamename)
{
    size_t i;
    char *deh_sub;

    for (i=0; i<(sizeof(banners) / sizeof(*banners)); ++i)
    {


        deh_sub = (banners[i]);

        if (deh_sub != banners[i])
        {
            size_t gamename_size;
            int version;





            gamename_size = strlen(deh_sub) + 10;
            gamename = Z_Malloc(gamename_size, PU_STATIC, 0);
            version = G_VanillaVersionCode();
            M_snprintf(gamename, gamename_size, deh_sub,
                       version / 100, version % 100);

            while (gamename[0] != '\0' && isspace((int)gamename[0]))
            {
                memmove(gamename, gamename + 1, gamename_size - 1);
            }

            while (gamename[0] != '\0' && isspace((int)gamename[strlen(gamename)-1]))
            {
                gamename[strlen(gamename) - 1] = '\0';
            }

            return gamename;
        }
    }

    return gamename;
}

static void SetMissionForPackName(char *pack_name)
{
    int i;
    static const struct
    {
        char *name;
        int mission;
    } packs[] = {
        { "doom2", doom2 },
        { "tnt", pack_tnt },
        { "plutonia", pack_plut },
    };

    for (i = 0; i < (sizeof(packs) / sizeof(*packs)); ++i)
    {
        if (!strcasecmp(pack_name, packs[i].name))
        {
            gamemission = packs[i].mission;
            return;
        }
    }

    printf("Valid mission packs are:\n");

    for (i = 0; i < (sizeof(packs) / sizeof(*packs)); ++i)
    {
        printf("\t%s\n", packs[i].name);
    }

    I_Error("Unknown mission pack name: %s", pack_name);
}





void D_IdentifyVersion(void)
{






    if (gamemission == none)
    {
        unsigned int i;

        for (i=0; i<numlumps; ++i)
        {
            if (!strncasecmp(lumpinfo[i].name, "MAP01", 8))
            {
                gamemission = doom2;
                break;
            }
            else if (!strncasecmp(lumpinfo[i].name, "E1M1", 8))
            {
                gamemission = doom;
                break;
            }
        }

        if (gamemission == none)
        {


            I_Error("Unknown or invalid IWAD file.");
        }
    }



    if ((gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) == doom)
    {


        if (W_CheckNumForName("E4M1") > 0)
        {


            gamemode = retail;
        }
        else if (W_CheckNumForName("E3M1") > 0)
        {
            gamemode = registered;
        }
        else
        {
            gamemode = shareware;
        }
    }
    else
    {
        int p;


        gamemode = commercial;
        p = M_CheckParmWithArgs("-pack", 1);
        if (p > 0)
        {
            SetMissionForPackName(myargv[p + 1]);
        }
    }
}



void D_SetGameDescription(void)
{
    boolean is_freedoom = W_CheckNumForName("FREEDOOM") >= 0,
            is_freedm = W_CheckNumForName("FREEDM") >= 0;

    gamedescription = "Unknown";

    if ((gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) == doom)
    {


        if (is_freedoom)
        {
            gamedescription = GetGameName("Freedoom: Phase 1");
        }
        else if (gamemode == retail)
        {


            gamedescription = GetGameName("The Ultimate DOOM");
        }
        else if (gamemode == registered)
        {
            gamedescription = GetGameName("DOOM Registered");
        }
        else if (gamemode == shareware)
        {
            gamedescription = GetGameName("DOOM Shareware");
        }
    }
    else
    {


        if (is_freedoom)
        {
            if (is_freedm)
            {
                gamedescription = GetGameName("FreeDM");
            }
            else
            {
                gamedescription = GetGameName("Freedoom: Phase 2");
            }
        }
        else if ((gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) == doom2)
        {
            gamedescription = GetGameName("DOOM 2: Hell on Earth");
        }
        else if ((gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) == pack_plut)
        {
            gamedescription = GetGameName("DOOM 2: Plutonia Experiment");
        }
        else if ((gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) == pack_tnt)
        {
            gamedescription = GetGameName("DOOM 2: TNT - Evilution");
        }
    }
}


char title[128];

static boolean D_AddFile(char *filename)
{
    wad_file_t *handle;

    printf(" adding %s\n", filename);
    handle = W_AddFile(filename);

    return handle != ((void*)0);
}





static char *copyright_banners[] =
{
    "===========================================================================\n"
    "ATTENTION:  This version of DOOM has been modified.  If you would like to\n"
    "get a copy of the original game, call 1-800-IDGAMES or see the readme file.\n"
    "        You will not receive technical support for modified games.\n"
    "                      press enter to continue\n"
    "===========================================================================\n",

    "===========================================================================\n"
    "                 Commercial product - do not distribute!\n"
    "         Please report software piracy to the SPA: 1-800-388-PIR8\n"
    "===========================================================================\n",

    "===========================================================================\n"
    "                                Shareware!\n"
    "===========================================================================\n"
};



void PrintDehackedBanners(void)
{
    size_t i;

    for (i=0; i<(sizeof(copyright_banners) / sizeof(*copyright_banners)); ++i)
    {
        char *deh_s;

        deh_s = (copyright_banners[i]);

        if (deh_s != copyright_banners[i])
        {
            printf("%s", deh_s);




            if (deh_s[strlen(deh_s) - 1] != '\n')
            {
                printf("\n");
            }
        }
    }
}

static struct
{
    char *description;
    char *cmdline;
    GameVersion_t version;
} gameversions[] = {
    {"Doom 0", "0", exe_doom_1_666},
    {"Doom 0/0a", "0", exe_doom_1_7},
    {"Doom 0", "0", exe_doom_1_8},
    {"Doom 0", "0", exe_doom_1_9},
    {"Hacx", "hacx", exe_hacx},
    {"Ultimate Doom", "ultimate", exe_ultimate},
    {"Final Doom", "final", exe_final},
    {"Final Doom (alt)", "final2", exe_final2},
    {"Chex Quest", "chex", exe_chex},
    { ((void*)0), ((void*)0), 0},
};



static void InitGameVersion(void)
{
    int p;
    int i;
    p = M_CheckParmWithArgs("-gameversion", 1);

    if (p)
    {
        for (i=0; gameversions[i].description != ((void*)0); ++i)
        {
            if (!strcmp(myargv[p+1], gameversions[i].cmdline))
            {
                gameversion = gameversions[i].version;
                break;
            }
        }

        if (gameversions[i].description == ((void*)0))
        {
            printf("Supported game versions:\n");

            for (i=0; gameversions[i].description != ((void*)0); ++i)
            {
                printf("\t%s (%s)\n", gameversions[i].cmdline,
                        gameversions[i].description);
            }

            I_Error("Unknown game version '%s'", myargv[p+1]);
        }
    }
    else
    {


        if (gamemission == pack_chex)
        {


            gameversion = exe_chex;
        }
        else if (gamemission == pack_hacx)
        {


            gameversion = exe_hacx;
        }
        else if (gamemode == shareware || gamemode == registered)
        {


            gameversion = exe_doom_1_9;


        }
        else if (gamemode == retail)
        {
            gameversion = exe_ultimate;
        }
        else if (gamemode == commercial)
        {
            if (gamemission == doom2)
            {
                gameversion = exe_doom_1_9;
            }
            else
            {






                gameversion = exe_final;
            }
        }
    }



    if (gameversion < exe_ultimate && gamemode == retail)
    {
        gamemode = registered;
    }



    if (gameversion < exe_final && gamemode == commercial
     && (gamemission == pack_tnt || gamemission == pack_plut))
    {
        gamemission = doom2;
    }
}

void PrintGameVersion(void)
{
    int i;

    for (i=0; gameversions[i].description != ((void*)0); ++i)
    {
        if (gameversions[i].version == gameversion)
        {
            printf("Emulating the behavior of the "
                   "'%s' executable.\n", gameversions[i].description);
            break;
        }
    }
}



static void D_Endoom(void)
{
    byte *endoom;





    if (!show_endoom || !main_loop_started
     || screensaver_mode || M_CheckParm("-testcontrols") > 0)
    {
        return;
    }

    endoom = W_CacheLumpName(("ENDOOM"), PU_STATIC);

    I_Endoom(endoom);

 exit(0);
}
void D_DoomMain (void)
{
    int p;
    char file[256];
    char demolumpname[9];




    I_AtExit(D_Endoom, false);



    I_PrintBanner("Doom Generic 0");

    printf("Z_Init: Init zone memory allocation daemon. \n");
    Z_Init ();
    nomonsters = M_CheckParm ("-nomonsters");







    respawnparm = M_CheckParm ("-respawn");







    fastparm = M_CheckParm ("-fast");
    devparm = M_CheckParm ("-devparm");

    I_DisplayFPSDots(devparm);
    if (M_CheckParm ("-deathmatch"))
 deathmatch = 1;
    if (M_CheckParm ("-altdeath"))
 deathmatch = 2;

    if (devparm)
 printf("Development mode ON.\n");
    {


        M_SetConfigDir(((void*)0));
    }
    if ( (p=M_CheckParm ("-turbo")) )
    {
 int scale = 200;
 extern int forwardmove[2];
 extern int sidemove[2];

 if (p<myargc-1)
     scale = atoi (myargv[p+1]);
 if (scale < 10)
     scale = 10;
 if (scale > 400)
     scale = 400;
        printf("turbo scale: %i%%\n", scale);
 forwardmove[0] = forwardmove[0]*scale/100;
 forwardmove[1] = forwardmove[1]*scale/100;
 sidemove[0] = sidemove[0]*scale/100;
 sidemove[1] = sidemove[1]*scale/100;
    }


    printf("V_Init: allocate screens.\n");
    V_Init ();


    printf("M_LoadDefaults: Load system defaults.\n");
    M_SetConfigFilenames("default.cfg", "doomgeneric" "doom.cfg");
    D_BindVariables();
    M_LoadDefaults();


    I_AtExit(M_SaveDefaults, false);


    iwadfile = D_FindIWAD(((1 << doom) | (1 << doom2) | (1 << pack_tnt) | (1 << pack_plut) | (1 << pack_chex) | (1 << pack_hacx)), &gamemission);



    if (iwadfile == ((void*)0))
    {
        I_Error("Game mode indeterminate.  No IWAD file was found.  Try\n"
                "specifying one with the '-iwad' command line parameter.\n");
    }

    modifiedgame = false;

    printf("W_Init: Init WADfiles.\n");
    D_AddFile(iwadfile);




    W_CheckCorrectIWAD(doom);



    D_IdentifyVersion();
    InitGameVersion();
    if (W_CheckNumForName("dmenupic") >= 0)
    {
        printf("BFG Edition: Using workarounds as needed.\n");
        bfgedition = true;







                                                             ;
                                                            ;
                                                              ;
                                                       ;
                                                       ;
    }
    modifiedgame = W_ParseCommandLine();
    p = M_CheckParmWithArgs ("-playdemo", 1);

    if (!p)
    {
 p = M_CheckParmWithArgs("-timedemo", 1);

    }

    if (p)
    {


        if (M_StringEndsWith(myargv[p + 1], ".lmp"))
        {
            M_StringCopy(file, myargv[p + 1], sizeof(file));
        }
        else
        {
            snprintf(file, sizeof(file), "%s.lmp", myargv[p+1]);
        }

        if (D_AddFile(file))
        {
            M_StringCopy(demolumpname, lumpinfo[numlumps - 1].name,
                         sizeof(demolumpname));
        }
        else
        {




            M_StringCopy(demolumpname, myargv[p + 1], sizeof(demolumpname));
        }

        printf("Playing demo %s.\n", file);
    }

    I_AtExit((atexit_func_t) G_CheckDemoStatus, true);


    W_GenerateHashTable();
    D_SetGameDescription();
    {
        savegamedir = M_GetSaveGameDir(D_SaveGameIWADName(gamemission));
    }


    if (modifiedgame)
    {


 char name[23][8]=
 {
     "e2m1","e2m2","e2m3","e2m4","e2m5","e2m6","e2m7","e2m8","e2m9",
     "e3m1","e3m3","e3m3","e3m4","e3m5","e3m6","e3m7","e3m8","e3m9",
     "dphoof","bfgga0","heada1","cybra1","spida1d1"
 };
 int i;

 if ( gamemode == shareware)
     I_Error(("\nYou cannot -file with the shareware " "version. Register!"));




 if (gamemode == registered)
     for (i = 0;i < 23; i++)
  if (W_CheckNumForName(name[i])<0)
      I_Error(("\nThis is not the registered version."));
    }

    if (W_CheckNumForName("SS_START") >= 0
     || W_CheckNumForName("FF_END") >= 0)
    {
        I_PrintDivider();
        printf(" WARNING: The loaded WAD file contains modified sprites or\n"
               " floor textures.  You may want to use the '-merge' command\n"
               " line option instead of '-file'.\n");
    }

    I_PrintStartupBanner(gamedescription);
    PrintDehackedBanners();




    if (W_CheckNumForName("FREEDOOM") >= 0 && W_CheckNumForName("FREEDM") < 0)
    {
        printf(" WARNING: You are playing using one of the Freedoom IWAD\n"
               " files, which might not work in this port. See this page\n"
               " for more information on how to play using Freedoom:\n"
               "   http://www.chocolate-doom.org/wiki/index.php/Freedoom\n");
        I_PrintDivider();
    }

    printf("I_Init: Setting up machine state.\n");
    I_CheckIsScreensaver();
    I_InitTimer();
    I_InitJoystick();
    I_InitSound(true);
    I_InitMusic();







    D_ConnectNetGame();


    startskill = sk_medium;
    startepisode = 1;
    startmap = 1;
    autostart = false;
    p = M_CheckParmWithArgs("-skill", 1);

    if (p)
    {
 startskill = myargv[p+1][0]-'1';
 autostart = true;
    }
    p = M_CheckParmWithArgs("-episode", 1);

    if (p)
    {
 startepisode = myargv[p+1][0]-'0';
 startmap = 1;
 autostart = true;
    }

    timelimit = 0;
    p = M_CheckParmWithArgs("-timer", 1);

    if (p)
    {
 timelimit = atoi(myargv[p+1]);
    }
    p = M_CheckParm ("-avg");

    if (p)
    {
 timelimit = 20;
    }
    p = M_CheckParmWithArgs("-warp", 1);

    if (p)
    {
        if (gamemode == commercial)
            startmap = atoi (myargv[p+1]);
        else
        {
            startepisode = myargv[p+1][0]-'0';

            if (p + 2 < myargc)
            {
                startmap = myargv[p+2][0]-'0';
            }
            else
            {
                startmap = 1;
            }
        }
        autostart = true;
    }




    p = M_CheckParm("-testcontrols");

    if (p > 0)
    {
        startepisode = 1;
        startmap = 1;
        autostart = true;
        testcontrols = true;
    }
    p = M_CheckParmWithArgs("-loadgame", 1);

    if (p)
    {
        startloadgame = atoi(myargv[p+1]);
    }
    else
    {

        startloadgame = -1;
    }

    printf("M_Init: Init miscellaneous info.\n");
    M_Init ();

    printf("R_Init: Init DOOM refresh daemon - ");
    R_Init ();

    printf("\nP_Init: Init Playloop state.\n");
    P_Init ();

    printf("S_Init: Setting up sound.\n");
    S_Init (sfxVolume * 8, musicVolume * 8);

    printf("D_CheckNetGame: Checking network game status.\n");
    D_CheckNetGame ();

    PrintGameVersion();

    printf("HU_Init: Setting up heads up display.\n");
    HU_Init ();

    printf("ST_Init: Init status bar.\n");
    ST_Init ();





    if (gamemode == commercial && W_CheckNumForName("map01") < 0)
        storedemo = true;

    if (M_CheckParmWithArgs("-statdump", 1))
    {
        I_AtExit(StatDump, true);
        printf("External statistics registered.\n");
    }
    p = M_CheckParmWithArgs("-record", 1);

    if (p)
    {
  G_RecordDemo (myargv[p+1]);
  autostart = true;
    }

    p = M_CheckParmWithArgs("-playdemo", 1);
    if (p)
    {
  singledemo = true;
  G_DeferedPlayDemo (demolumpname);
  D_DoomLoop ();
        return;
    }

    p = M_CheckParmWithArgs("-timedemo", 1);
    if (p)
    {
  G_TimeDemo (demolumpname);
  D_DoomLoop ();
        return;
    }

    if (startloadgame >= 0)
    {
        M_StringCopy(file, P_SaveGameFile(startloadgame), sizeof(file));
        G_LoadGame(file);
    }

    if (gameaction != ga_loadgame )
    {
  if (autostart || netgame)
   G_InitNew (startskill, startepisode, startmap);
  else
   D_StartTitle ();
    }

    D_DoomLoop ();
}
static struct
{
    GameMission_t mission;
    GameMode_t mode;
    int episode;
    int map;
} valid_modes[] = {
    { pack_chex, shareware, 1, 5 },
    { doom, shareware, 1, 9 },
    { doom, registered, 3, 9 },
    { doom, retail, 4, 9 },
    { doom2, commercial, 1, 32 },
    { pack_tnt, commercial, 1, 32 },
    { pack_plut, commercial, 1, 32 },
    { pack_hacx, commercial, 1, 32 },
    { heretic, shareware, 1, 9 },
    { heretic, registered, 3, 9 },
    { heretic, retail, 5, 9 },
    { hexen, commercial, 1, 60 },
    { strife, commercial, 1, 34 },
};



boolean D_ValidGameMode(GameMission_t mission, GameMode_t mode)
{
    int i;

    for (i=0; i<(sizeof(valid_modes) / sizeof(*valid_modes)); ++i)
    {
        if (valid_modes[i].mode == mode && valid_modes[i].mission == mission)
        {
            return true;
        }
    }

    return false;
}

boolean D_ValidEpisodeMap(GameMission_t mission, GameMode_t mode,
                          int episode, int map)
{
    int i;



    if (mission == heretic)
    {
        if (mode == retail && episode == 6)
        {
            return map >= 1 && map <= 3;
        }
        else if (mode == registered && episode == 4)
        {
            return map == 1;
        }
    }



    for (i=0; i<(sizeof(valid_modes) / sizeof(*valid_modes)); ++i)
    {
        if (mission == valid_modes[i].mission
         && mode == valid_modes[i].mode)
        {
            return episode >= 1 && episode <= valid_modes[i].episode
                && map >= 1 && map <= valid_modes[i].map;
        }
    }



    return false;
}



int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode)
{
    int episode;

    episode = 1;

    while (D_ValidEpisodeMap(mission, mode, episode, 1))
    {
        ++episode;
    }

    return episode - 1;
}



static struct {
    GameMission_t mission;
    GameVersion_t version;
} valid_versions[] = {
    { doom, exe_doom_1_9 },
    { doom, exe_hacx },
    { doom, exe_ultimate },
    { doom, exe_final },
    { doom, exe_final2 },
    { doom, exe_chex },
    { heretic, exe_heretic_1_3 },
    { hexen, exe_hexen_1_1 },
    { strife, exe_strife_1_2 },
    { strife, exe_strife_1_31 },
};

boolean D_ValidGameVersion(GameMission_t mission, GameVersion_t version)
{
    int i;



    if (mission == doom2 || mission == pack_plut || mission == pack_tnt
     || mission == pack_hacx || mission == pack_chex)
    {
        mission = doom;
    }

    for (i=0; i<(sizeof(valid_versions) / sizeof(*valid_versions)); ++i)
    {
        if (valid_versions[i].mission == mission
         && valid_versions[i].version == version)
        {
            return true;
        }
    }

    return false;
}



boolean D_IsEpisodeMap(GameMission_t mission)
{
    switch (mission)
    {
        case doom:
        case heretic:
        case pack_chex:
            return true;

        case none:
        case hexen:
        case doom2:
        case pack_hacx:
        case pack_tnt:
        case pack_plut:
        case strife:
        default:
            return false;
    }
}

char *D_GameMissionString(GameMission_t mission)
{
    switch (mission)
    {
        case none:
        default:
            return "none";
        case doom:
            return "doom";
        case doom2:
            return "doom2";
        case pack_tnt:
            return "tnt";
        case pack_plut:
            return "plutonia";
        case pack_hacx:
            return "hacx";
        case pack_chex:
            return "chex";
        case heretic:
            return "heretic";
        case hexen:
            return "hexen";
        case strife:
            return "strife";
    }
}
extern void W_Checksum(sha1_digest_t digest);






ticcmd_t *netcmds;



static void PlayerQuitGame(player_t *player)
{
    static char exitmsg[80];
    unsigned int player_num;

    player_num = player - players;




    M_StringCopy(exitmsg, ("Player 1 left the game"),
                 sizeof(exitmsg));

    exitmsg[7] += player_num;

    playeringame[player_num] = false;
    players[consoleplayer].message = exitmsg;



    if (demorecording)
    {
        G_CheckDemoStatus ();
    }
}

static void RunTic(ticcmd_t *cmds, boolean *ingame)
{
    extern boolean advancedemo;
    unsigned int i;



    for (i = 0; i < 4; ++i)
    {
        if (!demoplayback && playeringame[i] && !ingame[i])
        {
            PlayerQuitGame(&players[i]);
        }
    }

    netcmds = cmds;




    if (advancedemo)
        D_DoAdvanceDemo ();

    G_Ticker ();
}

static loop_interface_t doom_loop_interface = {
    D_ProcessEvents,
    G_BuildTiccmd,
    RunTic,
    M_Ticker
};





static void LoadGameSettings(net_gamesettings_t *settings)
{
    unsigned int i;

    deathmatch = settings->deathmatch;
    startepisode = settings->episode;
    startmap = settings->map;
    startskill = settings->skill;
    startloadgame = settings->loadgame;
    lowres_turn = settings->lowres_turn;
    nomonsters = settings->nomonsters;
    fastparm = settings->fast_monsters;
    respawnparm = settings->respawn_monsters;
    timelimit = settings->timelimit;
    consoleplayer = settings->consoleplayer;

    if (lowres_turn)
    {
        printf("NOTE: Turning resolution is reduced; this is probably "
               "because there is a client recording a Vanilla demo.\n");
    }

    for (i = 0; i < 4; ++i)
    {
        playeringame[i] = i < settings->num_players;
    }
}




static void SaveGameSettings(net_gamesettings_t *settings)
{



    settings->deathmatch = deathmatch;
    settings->episode = startepisode;
    settings->map = startmap;
    settings->skill = startskill;
    settings->loadgame = startloadgame;
    settings->gameversion = gameversion;
    settings->nomonsters = nomonsters;
    settings->fast_monsters = fastparm;
    settings->respawn_monsters = respawnparm;
    settings->timelimit = timelimit;

    settings->lowres_turn = M_CheckParm("-record") > 0
                         && M_CheckParm("-longtics") == 0;
}

static void InitConnectData(net_connect_data_t *connect_data)
{
    connect_data->max_players = 4;
    connect_data->drone = false;







    if (M_CheckParm("-left") > 0)
    {
        viewangleoffset = 0x40000000;
        connect_data->drone = true;
    }







    if (M_CheckParm("-right") > 0)
    {
        viewangleoffset = 0xc0000000;
        connect_data->drone = true;
    }







    connect_data->gamemode = gamemode;
    connect_data->gamemission = gamemission;



    connect_data->lowres_turn = M_CheckParm("-record") > 0
                             && M_CheckParm("-longtics") == 0;



    /* W_Checksum(connect_data->wad_sha1sum); -- stubbed, crashes on byte array struct fields */







    connect_data->is_freedoom = W_CheckNumForName("FREEDOOM") >= 0;
}

void D_ConnectNetGame(void)
{
    net_connect_data_t connect_data;

    InitConnectData(&connect_data);
    netgame = D_InitNetGame(&connect_data);
    if (M_CheckParm("-solo-net") > 0)
    {
        netgame = true;
    }
}





void D_CheckNetGame (void)
{
    net_gamesettings_t settings;

    if (netgame)
    {
        autostart = true;
    }

    D_RegisterLoopCallbacks(&doom_loop_interface);

    SaveGameSettings(&settings);
    D_StartNetGame(&settings, ((void*)0));
    LoadGameSettings(&settings);

    printf("startskill %i  deathmatch: %i  startmap: %i  startepisode: %i\n",
               startskill, deathmatch, startmap, startepisode);

    printf("player %i of %i (%i nodes)\n",
               consoleplayer+1, settings.num_players, settings.num_players);



    if (timelimit > 0 && deathmatch)
    {


        if (timelimit == 20 && M_CheckParm("-avg"))
        {
            printf("Austin Virtual Gaming: Levels will end "
                           "after 20 minutes\n");
        }
        else
        {
            printf("Levels will end after %d minute", timelimit);
            if (timelimit > 1)
                printf("s");
            printf(".\n");
        }
    }
}
typedef enum
{
    F_STAGE_TEXT,
    F_STAGE_ARTSCREEN,
    F_STAGE_CAST,
} finalestage_t;







finalestage_t finalestage;

unsigned int finalecount;




typedef struct
{
    GameMission_t mission;
    int episode, level;
    char *background;
    char *text;
} textscreen_t;

static textscreen_t textscreens[] =
{
    { doom, 1, 8, "FLOOR4_8", "Once you beat the big badasses and\n""clean out the moon base you're supposed\n""to win, aren't you? Aren't you? Where's\n""your fat reward and ticket home? What\n""the hell is this? It's not supposed to\n""end this way!\n""\n" "It stinks like rotten meat, but looks\n""like the lost Deimos base.  Looks like\n""you're stuck on The Shores of Hell.\n""The only way out is through.\n""\n""To continue the DOOM experience, play\n""The Shores of Hell and its amazing\n""sequel, Inferno!\n"},
    { doom, 2, 8, "SFLR6_1", "You've done it! The hideous cyber-\n""demon lord that ruled the lost Deimos\n""moon base has been slain and you\n""are triumphant! But ... where are\n""you? You clamber to the edge of the\n""moon and look down to see the awful\n""truth.\n" "\n""Deimos floats above Hell itself!\n""You've never heard of anyone escaping\n""from Hell, but you'll make the bastards\n""sorry they ever heard of you! Quickly,\n""you rappel down to  the surface of\n""Hell.\n""\n" "Now, it's on to the final chapter of\n""DOOM! -- Inferno."},
    { doom, 3, 8, "MFLR8_4", "The loathsome spiderdemon that\n""masterminded the invasion of the moon\n""bases and caused so much death has had\n""its ass kicked for all time.\n""\n""A hidden doorway opens and you enter.\n""You've proven too tough for Hell to\n""contain, and now Hell at last plays\n""fair -- for you emerge from the door\n""to see the green fields of Earth!\n""Home at last.\n" "\n""You wonder what's been happening on\n""Earth while you were battling evil\n""unleashed. It's good that no Hell-\n""spawn could have come through that\n""door with you ..."},
    { doom, 4, 8, "MFLR8_3", "the spider mastermind must have sent forth\n""its legions of hellspawn before your\n""final confrontation with that terrible\n""beast from hell.  but you stepped forward\n""and brought forth eternal damnation and\n""suffering upon the horde as a true hero\n""would in the face of something so evil.\n""\n""besides, someone was gonna pay for what\n""happened to daisy, your pet rabbit.\n""\n""but now, you see spread before you more\n""potential pain and gibbitude as a nation\n""of demons run amok among our cities.\n""\n""next stop, hell on earth!"},

    { doom2, 1, 6, "SLIME16", "YOU HAVE ENTERED DEEPLY INTO THE INFESTED\n" "STARPORT. BUT SOMETHING IS WRONG. THE\n" "MONSTERS HAVE BROUGHT THEIR OWN REALITY\n" "WITH THEM, AND THE STARPORT'S TECHNOLOGY\n" "IS BEING SUBVERTED BY THEIR PRESENCE.\n" "\n""AHEAD, YOU SEE AN OUTPOST OF HELL, A\n" "FORTIFIED ZONE. IF YOU CAN GET PAST IT,\n" "YOU CAN PENETRATE INTO THE HAUNTED HEART\n" "OF THE STARBASE AND FIND THE CONTROLLING\n" "SWITCH WHICH HOLDS EARTH'S POPULATION\n" "HOSTAGE."},
    { doom2, 1, 11, "RROCK14", "YOU HAVE WON! YOUR VICTORY HAS ENABLED\n" "HUMANKIND TO EVACUATE EARTH AND ESCAPE\n""THE NIGHTMARE.  NOW YOU ARE THE ONLY\n""HUMAN LEFT ON THE FACE OF THE PLANET.\n""CANNIBAL MUTATIONS, CARNIVOROUS ALIENS,\n""AND EVIL SPIRITS ARE YOUR ONLY NEIGHBORS.\n""YOU SIT BACK AND WAIT FOR DEATH, CONTENT\n""THAT YOU HAVE SAVED YOUR SPECIES.\n""\n""BUT THEN, EARTH CONTROL BEAMS DOWN A\n""MESSAGE FROM SPACE: \"SENSORS HAVE LOCATED\n""THE SOURCE OF THE ALIEN INVASION. IF YOU\n""GO THERE, YOU MAY BE ABLE TO BLOCK THEIR\n""ENTRY.  THE ALIEN BASE IS IN THE HEART OF\n""YOUR OWN HOME CITY, NOT FAR FROM THE\n""STARPORT.\" SLOWLY AND PAINFULLY YOU GET\n""UP AND RETURN TO THE FRAY."},
    { doom2, 1, 20, "RROCK07", "YOU ARE AT THE CORRUPT HEART OF THE CITY,\n""SURROUNDED BY THE CORPSES OF YOUR ENEMIES.\n""YOU SEE NO WAY TO DESTROY THE CREATURES'\n""ENTRYWAY ON THIS SIDE, SO YOU CLENCH YOUR\n""TEETH AND PLUNGE THROUGH IT.\n""\n""THERE MUST BE A WAY TO CLOSE IT ON THE\n""OTHER SIDE. WHAT DO YOU CARE IF YOU'VE\n""GOT TO GO THROUGH HELL TO GET TO IT?"},
    { doom2, 1, 30, "RROCK17", "THE HORRENDOUS VISAGE OF THE BIGGEST\n""DEMON YOU'VE EVER SEEN CRUMBLES BEFORE\n""YOU, AFTER YOU PUMP YOUR ROCKETS INTO\n""HIS EXPOSED BRAIN. THE MONSTER SHRIVELS\n""UP AND DIES, ITS THRASHING LIMBS\n""DEVASTATING UNTOLD MILES OF HELL'S\n""SURFACE.\n""\n""YOU'VE DONE IT. THE INVASION IS OVER.\n""EARTH IS SAVED. HELL IS A WRECK. YOU\n""WONDER WHERE BAD FOLKS WILL GO WHEN THEY\n""DIE, NOW. WIPING THE SWEAT FROM YOUR\n""FOREHEAD YOU BEGIN THE LONG TREK BACK\n""HOME. REBUILDING EARTH OUGHT TO BE A\n""LOT MORE FUN THAN RUINING IT WAS.\n"},
    { doom2, 1, 15, "RROCK13", "CONGRATULATIONS, YOU'VE FOUND THE SECRET\n""LEVEL! LOOKS LIKE IT'S BEEN BUILT BY\n""HUMANS, RATHER THAN DEMONS. YOU WONDER\n""WHO THE INMATES OF THIS CORNER OF HELL\n""WILL BE."},
    { doom2, 1, 31, "RROCK19", "CONGRATULATIONS, YOU'VE FOUND THE\n""SUPER SECRET LEVEL!  YOU'D BETTER\n""BLAZE THROUGH THIS ONE!\n"},

    { pack_tnt, 1, 6, "SLIME16", "You've fought your way out of the infested\n""experimental labs.   It seems that UAC has\n""once again gulped it down.  With their\n""high turnover, it must be hard for poor\n""old UAC to buy corporate health insurance\n""nowadays..\n""\n""Ahead lies the military complex, now\n""swarming with diseased horrors hot to get\n""their teeth into you. With luck, the\n""complex still has some warlike ordnance\n""laying around."},
    { pack_tnt, 1, 11, "RROCK14", "You hear the grinding of heavy machinery\n""ahead.  You sure hope they're not stamping\n""out new hellspawn, but you're ready to\n""ream out a whole herd if you have to.\n""They might be planning a blood feast, but\n""you feel about as mean as two thousand\n""maniacs packed into one mad killer.\n""\n""You don't plan to go down easy."},
    { pack_tnt, 1, 20, "RROCK07", "The vista opening ahead looks real damn\n""familiar. Smells familiar, too -- like\n""fried excrement. You didn't like this\n""place before, and you sure as hell ain't\n""planning to like it now. The more you\n""brood on it, the madder you get.\n""Hefting your gun, an evil grin trickles\n""onto your face. Time to take some names."},
    { pack_tnt, 1, 30, "RROCK17", "Suddenly, all is silent, from one horizon\n""to the other. The agonizing echo of Hell\n""fades away, the nightmare sky turns to\n""blue, the heaps of monster corpses start \n""to evaporate along with the evil stench \n""that filled the air. Jeeze, maybe you've\n""done it. Have you really won?\n""\n""Something rumbles in the distance.\n""A blue light begins to glow inside the\n""ruined skull of the demon-spitter."},
    { pack_tnt, 1, 15, "RROCK13", "What now? Looks totally different. Kind\n""of like King Tut's condo. Well,\n""whatever's here can't be any worse\n""than usual. Can it?  Or maybe it's best\n""to let sleeping gods lie.."},
    { pack_tnt, 1, 31, "RROCK19", "Time for a vacation. You've burst the\n""bowels of hell and by golly you're ready\n""for a break. You mutter to yourself,\n""Maybe someone else can kick Hell's ass\n""next time around. Ahead lies a quiet town,\n""with peaceful flowing water, quaint\n""buildings, and presumably no Hellspawn.\n""\n""As you step off the transport, you hear\n""the stomp of a cyberdemon's iron shoe."},

    { pack_plut, 1, 6, "SLIME16", "You gloat over the steaming carcass of the\n""Guardian.  With its death, you've wrested\n""the Accelerator from the stinking claws\n""of Hell.  You relax and glance around the\n""room.  Damn!  There was supposed to be at\n""least one working prototype, but you can't\n""see it. The demons must have taken it.\n""\n""You must find the prototype, or all your\n""struggles will have been wasted. Keep\n""moving, keep fighting, keep killing.\n""Oh yes, keep living, too."},
    { pack_plut, 1, 11, "RROCK14", "Even the deadly Arch-Vile labyrinth could\n""not stop you, and you've gotten to the\n""prototype Accelerator which is soon\n""efficiently and permanently deactivated.\n""\n""You're good at that kind of thing."},
    { pack_plut, 1, 20, "RROCK07", "You've bashed and battered your way into\n""the heart of the devil-hive.  Time for a\n""Search-and-Destroy mission, aimed at the\n""Gatekeeper, whose foul offspring is\n""cascading to Earth.  Yeah, he's bad. But\n""you know who's worse!\n""\n""Grinning evilly, you check your gear, and\n""get ready to give the bastard a little Hell\n""of your own making!"},
    { pack_plut, 1, 30, "RROCK17", "The Gatekeeper's evil face is splattered\n""all over the place.  As its tattered corpse\n""collapses, an inverted Gate forms and\n""sucks down the shards of the last\n""prototype Accelerator, not to mention the\n""few remaining demons.  You're done. Hell\n""has gone back to pounding bad dead folks \n""instead of good live ones.  Remember to\n""tell your grandkids to put a rocket\n""launcher in your coffin. If you go to Hell\n""when you die, you'll need it for some\n""final cleaning-up ..."},
    { pack_plut, 1, 15, "RROCK13", "You've found the second-hardest level we\n""got. Hope you have a saved game a level or\n""two previous.  If not, be prepared to die\n""aplenty. For master marines only."},
    { pack_plut, 1, 31, "RROCK19", "Betcha wondered just what WAS the hardest\n""level we had ready for ya?  Now you know.\n""No one gets out alive."},
};

char* finaletext;
char* finaleflat;

void F_StartCast (void);
void F_CastTicker (void);
boolean F_CastResponder (event_t *ev);
void F_CastDrawer (void);




void F_StartFinale (void)
{
    size_t i;

    gameaction = ga_nothing;
    gamestate = GS_FINALE;
    viewactive = false;
    automapactive = false;

    if ((gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) == doom)
    {
        S_ChangeMusic(mus_victor, true);
    }
    else
    {
        S_ChangeMusic(mus_read_m, true);
    }



    for (i=0; i<(sizeof(textscreens) / sizeof(*textscreens)); ++i)
    {
        textscreen_t *screen = &textscreens[i];



        if (gameversion == exe_chex && screen->mission == doom)
        {
            screen->level = 5;
        }

        if ((gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) == screen->mission
         && ((gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) != doom || gameepisode == screen->episode)
         && gamemap == screen->level)
        {
            finaletext = screen->text;
            finaleflat = screen->background;
        }
    }



    finaletext = (finaletext);
    finaleflat = (finaleflat);

    finalestage = F_STAGE_TEXT;
    finalecount = 0;

}



boolean F_Responder (event_t *event)
{
    if (finalestage == F_STAGE_CAST)
 return F_CastResponder (event);

    return false;
}





void F_Ticker (void)
{
    size_t i;


    if ( (gamemode == commercial)
      && ( finalecount > 50) )
    {

      for (i=0 ; i<4 ; i++)
 if (players[i].cmd.buttons)
   break;

      if (i < 4)
      {
 if (gamemap == 30)
   F_StartCast ();
 else
   gameaction = ga_worlddone;
      }
    }


    finalecount++;

    if (finalestage == F_STAGE_CAST)
    {
 F_CastTicker ();
 return;
    }

    if ( gamemode == commercial)
 return;

    if (finalestage == F_STAGE_TEXT
     && finalecount>strlen (finaletext)*3 + 250)
    {
 finalecount = 0;
 finalestage = F_STAGE_ARTSCREEN;
 wipegamestate = -1;
 if (gameepisode == 3)
     S_StartMusic (mus_bunny);
    }
}
extern patch_t *hu_font[('_' - '!' + 1)];


void F_TextWrite (void)
{
    byte* src;
    byte* dest;

    int x,y,w;
    signed int count;
    char* ch;
    int c;
    int cx;
    int cy;


    src = W_CacheLumpName ( finaleflat , PU_CACHE);
    dest = I_VideoBuffer;

    for (y=0 ; y<200 ; y++)
    {
 for (x=0 ; x<320/64 ; x++)
 {
     memcpy (dest, src+((y&63)<<6), 64);
     dest += 64;
 }
 if (320&63)
 {
     memcpy (dest, src+((y&63)<<6), 320&63);
     dest += (320&63);
 }
    }

    V_MarkRect (0, 0, 320, 200);


    cx = 10;
    cy = 10;
    ch = finaletext;

    count = ((signed int) finalecount - 10) / 3;
    if (count < 0)
 count = 0;
    for ( ; count ; count-- )
    {
 c = *ch++;
 if (!c)
     break;
 if (c == '\n')
 {
     cx = 10;
     cy += 11;
     continue;
 }

 c = toupper(c) - '!';
 if (c < 0 || c> ('_' - '!' + 1))
 {
     cx += 4;
     continue;
 }

 w = ((signed short) (hu_font[c]->width));
 if (cx+w > 320)
     break;
 V_DrawPatch(cx, cy, hu_font[c]);
 cx+=w;
    }

}






typedef struct
{
    char *name;
    mobjtype_t type;
} castinfo_t;

castinfo_t castorder[] = {
    {"ZOMBIEMAN", MT_POSSESSED},
    {"SHOTGUN GUY", MT_SHOTGUY},
    {"HEAVY WEAPON DUDE", MT_CHAINGUY},
    {"IMP", MT_TROOP},
    {"DEMON", MT_SERGEANT},
    {"LOST SOUL", MT_SKULL},
    {"CACODEMON", MT_HEAD},
    {"HELL KNIGHT", MT_KNIGHT},
    {"BARON OF HELL", MT_BRUISER},
    {"ARACHNOTRON", MT_BABY},
    {"PAIN ELEMENTAL", MT_PAIN},
    {"REVENANT", MT_UNDEAD},
    {"MANCUBUS", MT_FATSO},
    {"ARCH-VILE", MT_VILE},
    {"THE SPIDER MASTERMIND", MT_SPIDER},
    {"THE CYBERDEMON", MT_CYBORG},
    {"OUR HERO", MT_PLAYER},

    {((void*)0),0}
};

int castnum;
int casttics;
state_t* caststate;
boolean castdeath;
int castframes;
int castonmelee;
boolean castattacking;





void F_StartCast (void)
{
    wipegamestate = -1;
    castnum = 0;
    caststate = &states[mobjinfo[castorder[castnum].type].seestate];
    casttics = caststate->tics;
    castdeath = false;
    finalestage = F_STAGE_CAST;
    castframes = 0;
    castonmelee = 0;
    castattacking = false;
    S_ChangeMusic(mus_evil, true);
}





void F_CastTicker (void)
{
    int st;
    int sfx;

    if (--casttics > 0)
 return;

    if (caststate->tics == -1 || caststate->nextstate == S_NULL)
    {

 castnum++;
 castdeath = false;
 if (castorder[castnum].name == ((void*)0))
     castnum = 0;
 if (mobjinfo[castorder[castnum].type].seesound)
     S_StartSound (((void*)0), mobjinfo[castorder[castnum].type].seesound);
 caststate = &states[mobjinfo[castorder[castnum].type].seestate];
 castframes = 0;
    }
    else
    {

 if (caststate == &states[S_PLAY_ATK1])
     goto stopattack;
 st = caststate->nextstate;
 caststate = &states[st];
 castframes++;


 switch (st)
 {
   case S_PLAY_ATK1: sfx = sfx_dshtgn; break;
   case S_POSS_ATK2: sfx = sfx_pistol; break;
   case S_SPOS_ATK2: sfx = sfx_shotgn; break;
   case S_VILE_ATK2: sfx = sfx_vilatk; break;
   case S_SKEL_FIST2: sfx = sfx_skeswg; break;
   case S_SKEL_FIST4: sfx = sfx_skepch; break;
   case S_SKEL_MISS2: sfx = sfx_skeatk; break;
   case S_FATT_ATK8:
   case S_FATT_ATK5:
   case S_FATT_ATK2: sfx = sfx_firsht; break;
   case S_CPOS_ATK2:
   case S_CPOS_ATK3:
   case S_CPOS_ATK4: sfx = sfx_shotgn; break;
   case S_TROO_ATK3: sfx = sfx_claw; break;
   case S_SARG_ATK2: sfx = sfx_sgtatk; break;
   case S_BOSS_ATK2:
   case S_BOS2_ATK2:
   case S_HEAD_ATK2: sfx = sfx_firsht; break;
   case S_SKULL_ATK2: sfx = sfx_sklatk; break;
   case S_SPID_ATK2:
   case S_SPID_ATK3: sfx = sfx_shotgn; break;
   case S_BSPI_ATK2: sfx = sfx_plasma; break;
   case S_CYBER_ATK2:
   case S_CYBER_ATK4:
   case S_CYBER_ATK6: sfx = sfx_rlaunc; break;
   case S_PAIN_ATK3: sfx = sfx_sklatk; break;
   default: sfx = 0; break;
 }

 if (sfx)
     S_StartSound (((void*)0), sfx);
    }

    if (castframes == 12)
    {

 castattacking = true;
 if (castonmelee)
     caststate=&states[mobjinfo[castorder[castnum].type].meleestate];
 else
     caststate=&states[mobjinfo[castorder[castnum].type].missilestate];
 castonmelee ^= 1;
 if (caststate == &states[S_NULL])
 {
     if (castonmelee)
  caststate=
      &states[mobjinfo[castorder[castnum].type].meleestate];
     else
  caststate=
      &states[mobjinfo[castorder[castnum].type].missilestate];
 }
    }

    if (castattacking)
    {
 if (castframes == 24
     || caststate == &states[mobjinfo[castorder[castnum].type].seestate] )
 {
   stopattack:
     castattacking = false;
     castframes = 0;
     caststate = &states[mobjinfo[castorder[castnum].type].seestate];
 }
    }

    casttics = caststate->tics;
    if (casttics == -1)
 casttics = 15;
}






boolean F_CastResponder (event_t* ev)
{
    if (ev->type != ev_keydown)
 return false;

    if (castdeath)
 return true;


    castdeath = true;
    caststate = &states[mobjinfo[castorder[castnum].type].deathstate];
    casttics = caststate->tics;
    castframes = 0;
    castattacking = false;
    if (mobjinfo[castorder[castnum].type].deathsound)
 S_StartSound (((void*)0), mobjinfo[castorder[castnum].type].deathsound);

    return true;
}


void F_CastPrint (char* text)
{
    char* ch;
    int c;
    int cx;
    int w;
    int width;


    ch = text;
    width = 0;

    while (ch)
    {
 c = *ch++;
 if (!c)
     break;
 c = toupper(c) - '!';
 if (c < 0 || c> ('_' - '!' + 1))
 {
     width += 4;
     continue;
 }

 w = ((signed short) (hu_font[c]->width));
 width += w;
    }


    cx = 160-width/2;
    ch = text;
    while (ch)
    {
 c = *ch++;
 if (!c)
     break;
 c = toupper(c) - '!';
 if (c < 0 || c> ('_' - '!' + 1))
 {
     cx += 4;
     continue;
 }

 w = ((signed short) (hu_font[c]->width));
 V_DrawPatch(cx, 180, hu_font[c]);
 cx+=w;
    }

}






void F_CastDrawer (void)
{
    spritedef_t* sprdef;
    spriteframe_t* sprframe;
    int lump;
    boolean flip;
    patch_t* patch;


    V_DrawPatch (0, 0, W_CacheLumpName (("BOSSBACK"), PU_CACHE));

    F_CastPrint ((castorder[castnum].name));


    sprdef = &sprites[caststate->sprite];
    sprframe = &sprdef->spriteframes[ caststate->frame & 0x7fff];
    lump = sprframe->lump[0];
    flip = (boolean)sprframe->flip[0];

    patch = W_CacheLumpNum (lump+firstspritelump, PU_CACHE);
    if (flip)
 V_DrawPatchFlipped(160, 170, patch);
    else
 V_DrawPatch(160, 170, patch);
}





void
F_DrawPatchCol
( int x,
  patch_t* patch,
  int col )
{
    column_t* column;
    byte* source;
    byte* dest;
    byte* desttop;
    int count;

    column = (column_t *)((byte *)patch + ((signed int) (patch->columnofs[col])));
    desttop = I_VideoBuffer + x;


    while (column->topdelta != 0xff )
    {
 source = (byte *)column + 3;
 dest = desttop + column->topdelta*320;
 count = column->length;

 while (count--)
 {
     *dest = *source++;
     dest += 320;
 }
 column = (column_t *)( (byte *)column + column->length + 4 );
    }
}





void F_BunnyScroll (void)
{
    signed int scrolled;
    int x;
    patch_t* p1;
    patch_t* p2;
    char name[10];
    int stage;
    static int laststage;

    p1 = W_CacheLumpName (("PFUB2"), PU_LEVEL);
    p2 = W_CacheLumpName (("PFUB1"), PU_LEVEL);

    V_MarkRect (0, 0, 320, 200);

    scrolled = (320 - ((signed int) finalecount-230)/2);
    if (scrolled > 320)
 scrolled = 320;
    if (scrolled < 0)
 scrolled = 0;

    for ( x=0 ; x<320 ; x++)
    {
 if (x+scrolled < 320)
     F_DrawPatchCol (x, p1, x+scrolled);
 else
     F_DrawPatchCol (x, p2, x+scrolled - 320);
    }

    if (finalecount < 1130)
 return;
    if (finalecount < 1180)
    {
        V_DrawPatch((320 - 13 * 8) / 2,
                    (200 - 8 * 8) / 2,
                    W_CacheLumpName(("END0"), PU_CACHE));
 laststage = 0;
 return;
    }

    stage = (finalecount-1180) / 5;
    if (stage > 6)
 stage = 6;
    if (stage > laststage)
    {
 S_StartSound (((void*)0), sfx_pistol);
 laststage = stage;
    }

    snprintf(name, 10, "END%i", stage);
    V_DrawPatch((320 - 13 * 8) / 2,
                (200 - 8 * 8) / 2,
                W_CacheLumpName (name,PU_CACHE));
}

static void F_ArtScreenDrawer(void)
{
    char *lumpname;

    if (gameepisode == 3)
    {
        F_BunnyScroll();
    }
    else
    {
        switch (gameepisode)
        {
            case 1:
                if (gamemode == retail)
                {
                    lumpname = "CREDIT";
                }
                else
                {
                    lumpname = "HELP2";
                }
                break;
            case 2:
                lumpname = "VICTORY2";
                break;
            case 4:
                lumpname = "ENDPIC";
                break;
            default:
                return;
        }

        lumpname = (lumpname);

        V_DrawPatch (0, 0, W_CacheLumpName(lumpname, PU_CACHE));
    }
}




void F_Drawer (void)
{
    switch (finalestage)
    {
        case F_STAGE_CAST:
            F_CastDrawer();
            break;
        case F_STAGE_TEXT:
            F_TextWrite();
            break;
        case F_STAGE_ARTSCREEN:
            F_ArtScreenDrawer();
            break;
    }
}
int M_Random (void);


int P_Random (void);


void M_ClearRandom (void);
static boolean go = 0;

static byte* wipe_scr_start;
static byte* wipe_scr_end;
static byte* wipe_scr;


void
wipe_shittyColMajorXform
( short* array,
  int width,
  int height )
{
    int x;
    int y;
    short* dest;

    dest = (short*) Z_Malloc(width*height*2, PU_STATIC, 0);

    for(y=0;y<height;y++)
 for(x=0;x<width;x++)
     dest[x*height+y] = array[y*width+x];

    memcpy(array, dest, width*height*2);

    Z_Free(dest);

}

int
wipe_initColorXForm
( int width,
  int height,
  int ticks )
{
    memcpy(wipe_scr, wipe_scr_start, width*height);
    return 0;
}

int
wipe_doColorXForm
( int width,
  int height,
  int ticks )
{
    boolean changed;
    byte* w;
    byte* e;
    int newval;

    changed = false;
    w = wipe_scr;
    e = wipe_scr_end;

    while (w!=wipe_scr+width*height)
    {
 if (*w != *e)
 {
     if (*w > *e)
     {
  newval = *w - ticks;
  if (newval < *e)
      *w = *e;
  else
      *w = newval;
  changed = true;
     }
     else if (*w < *e)
     {
  newval = *w + ticks;
  if (newval > *e)
      *w = *e;
  else
      *w = newval;
  changed = true;
     }
 }
 w++;
 e++;
    }

    return !changed;

}

int
wipe_exitColorXForm
( int width,
  int height,
  int ticks )
{
    return 0;
}


static int* y;

int
wipe_initMelt
( int width,
  int height,
  int ticks )
{
    int i, r;


    memcpy(wipe_scr, wipe_scr_start, width*height);



    wipe_shittyColMajorXform((short*)wipe_scr_start, width/2, height);
    wipe_shittyColMajorXform((short*)wipe_scr_end, width/2, height);



    y = (int *) Z_Malloc(width*sizeof(int), PU_STATIC, 0);
    y[0] = -(M_Random()%16);
    for (i=1;i<width;i++)
    {
 r = (M_Random()%3) - 1;
 y[i] = y[i-1] + r;
 if (y[i] > 0) y[i] = 0;
 else if (y[i] == -16) y[i] = -15;
    }

    return 0;
}

int
wipe_doMelt
( int width,
  int height,
  int ticks )
{
    int i;
    int j;
    int dy;
    int idx;

    short* s;
    short* d;
    boolean done = true;

    width/=2;

    while (ticks--)
    {
 for (i=0;i<width;i++)
 {
     if (y[i]<0)
     {
  y[i]++; done = false;
     }
     else if (y[i] < height)
     {
  dy = (y[i] < 16) ? y[i]+1 : 8;
  if (y[i]+dy >= height) dy = height - y[i];
  s = &((short *)wipe_scr_end)[i*height+y[i]];
  d = &((short *)wipe_scr)[y[i]*width+i];
  idx = 0;
  for (j=dy;j;j--)
  {
      d[idx] = *(s++);
      idx += width;
  }
  y[i] += dy;
  s = &((short *)wipe_scr_start)[i*height];
  d = &((short *)wipe_scr)[y[i]*width+i];
  idx = 0;
  for (j=height-y[i];j;j--)
  {
      d[idx] = *(s++);
      idx += width;
  }
  done = false;
     }
 }
    }

    return done;

}

int
wipe_exitMelt
( int width,
  int height,
  int ticks )
{
    Z_Free(y);
    Z_Free(wipe_scr_start);
    Z_Free(wipe_scr_end);
    return 0;
}

int
wipe_StartScreen
( int x,
  int y,
  int width,
  int height )
{
    wipe_scr_start = Z_Malloc(320 * 200, PU_STATIC, ((void*)0));
    I_ReadScreen(wipe_scr_start);
    return 0;
}

int
wipe_EndScreen
( int x,
  int y,
  int width,
  int height )
{
    wipe_scr_end = Z_Malloc(320 * 200, PU_STATIC, ((void*)0));
    I_ReadScreen(wipe_scr_end);
    V_DrawBlock(x, y, width, height, wipe_scr_start);
    return 0;
}

int
wipe_ScreenWipe
( int wipeno,
  int x,
  int y,
  int width,
  int height,
  int ticks )
{
    int rc;
    static int (*wipes[])(int, int, int) =
    {
 wipe_initColorXForm, wipe_doColorXForm, wipe_exitColorXForm,
 wipe_initMelt, wipe_doMelt, wipe_exitMelt
    };


    if (!go)
    {
 go = 1;

 wipe_scr = I_VideoBuffer;
 (*wipes[wipeno*3])(width, height, ticks);
    }


    V_MarkRect(0, 0, width, height);
    rc = (*wipes[wipeno*3+1])(width, height, ticks);



    if (rc)
    {
 go = 0;
 (*wipes[wipeno*3+2])(width, height, ticks);
    }

    return !go;
}
void P_Ticker (void);
extern int skytexture;
extern int skytexturemid;


void R_InitSkyMap (void);








void G_ReadDemoTiccmd (ticcmd_t* cmd);
void G_WriteDemoTiccmd (ticcmd_t* cmd);
void G_PlayerReborn (int player);

void G_DoReborn (int playernum);

void G_DoLoadLevel (void);
void G_DoNewGame (void);
void G_DoPlayDemo (void);
void G_DoCompleted (void);
void G_DoVictory (void);
void G_DoWorldDone (void);
void G_DoSaveGame (void);



gamestate_t oldgamestate;

gameaction_t gameaction;
gamestate_t gamestate;
skill_t gameskill;
boolean respawnmonsters;
int gameepisode;
int gamemap;



int timelimit;

boolean paused;
boolean sendpause;
boolean sendsave;
boolean usergame;

boolean timingdemo;
boolean nodrawers;
int starttime;

boolean viewactive;

int deathmatch;
boolean netgame;
boolean playeringame[4];
player_t players[4];

boolean turbodetected[4];

int consoleplayer;
int displayplayer;
int levelstarttic;
int totalkills, totalitems, totalsecret;

char *demoname;
boolean demorecording;
boolean longtics;
boolean lowres_turn;
boolean demoplayback;
boolean netdemo;
byte* demobuffer;
byte* demo_p;
byte* demoend;
boolean singledemo;

boolean precache = true;

boolean testcontrols = false;
int testcontrols_mousespeed;



wbstartstruct_t wminfo;

byte consistancy[4][128];





fixed_t forwardmove[2] = {0x19, 0x32};
fixed_t sidemove[2] = {0x18, 0x28};
fixed_t angleturn[3] = {640, 1280, 320};

static int *weapon_keys[] = {
    &key_weapon1,
    &key_weapon2,
    &key_weapon3,
    &key_weapon4,
    &key_weapon5,
    &key_weapon6,
    &key_weapon7,
    &key_weapon8
};



static int next_weapon = 0;



static const struct
{
    weapontype_t weapon;
    weapontype_t weapon_num;
} weapon_order_table[] = {
    { wp_fist, wp_fist },
    { wp_chainsaw, wp_fist },
    { wp_pistol, wp_pistol },
    { wp_shotgun, wp_shotgun },
    { wp_supershotgun, wp_shotgun },
    { wp_chaingun, wp_chaingun },
    { wp_missile, wp_missile },
    { wp_plasma, wp_plasma },
    { wp_bfg, wp_bfg }
};






static boolean gamekeydown[256];
static int turnheld;

static boolean mousearray[8 + 1];
static boolean *mousebuttons = &mousearray[1];


int mousex;
int mousey;

static int dclicktime;
static boolean dclickstate;
static int dclicks;
static int dclicktime2;
static boolean dclickstate2;
static int dclicks2;


static int joyxmove;
static int joyymove;
static int joystrafemove;
static boolean joyarray[20 + 1];
static boolean *joybuttons = &joyarray[1];

static int savegameslot;
static char savedescription[32];



mobj_t* bodyque[32];
int bodyqueslot;

int vanilla_savegame_limit = 1;
int vanilla_demo_limit = 1;

int G_CmdChecksum (ticcmd_t* cmd)
{
    size_t i;
    int sum = 0;

    for (i=0 ; i< sizeof(*cmd)/4 - 1 ; i++)
 sum += ((int *)cmd)[i];

    return sum;
}

static boolean WeaponSelectable(weapontype_t weapon)
{


    if (weapon == wp_supershotgun && (gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) == doom)
    {
        return false;
    }



    if ((weapon == wp_plasma || weapon == wp_bfg)
     && gamemission == doom && gamemode == shareware)
    {
        return false;
    }



    if (!players[consoleplayer].weaponowned[weapon])
    {
        return false;
    }




    if (weapon == wp_fist
     && players[consoleplayer].weaponowned[wp_chainsaw]
     && !players[consoleplayer].powers[pw_strength])
    {
        return false;
    }

    return true;
}

static int G_NextWeapon(int direction)
{
    weapontype_t weapon;
    int start_i, i;



    if (players[consoleplayer].pendingweapon == wp_nochange)
    {
        weapon = players[consoleplayer].readyweapon;
    }
    else
    {
        weapon = players[consoleplayer].pendingweapon;
    }

    for (i=0; i<(sizeof(weapon_order_table) / sizeof(*weapon_order_table)); ++i)
    {
        if (weapon_order_table[i].weapon == weapon)
        {
            break;
        }
    }


    start_i = i;
    do
    {
        i += direction;
        i = (i + (sizeof(weapon_order_table) / sizeof(*weapon_order_table))) % (sizeof(weapon_order_table) / sizeof(*weapon_order_table));
    } while (i != start_i && !WeaponSelectable(weapon_order_table[i].weapon));

    return weapon_order_table[i].weapon_num;
}







void G_BuildTiccmd (ticcmd_t* cmd, int maketic)
{
    int i;
    boolean strafe;
    boolean bstrafe;
    int speed;
    int tspeed;
    int forward;
    int side;

    memset(cmd, 0, sizeof(ticcmd_t));

    cmd->consistancy =
 consistancy[consoleplayer][maketic%128];

    strafe = gamekeydown[key_strafe] || mousebuttons[mousebstrafe]
 || joybuttons[joybstrafe];




    speed = key_speed >= 256
         || joybspeed >= 20
         || gamekeydown[key_speed]
         || joybuttons[joybspeed];

    forward = side = 0;



    if (joyxmove < 0
 || joyxmove > 0
 || gamekeydown[key_right]
 || gamekeydown[key_left])
 turnheld += ticdup;
    else
 turnheld = 0;

    if (turnheld < 6)
 tspeed = 2;
    else
 tspeed = speed;


    if (strafe)
    {
 if (gamekeydown[key_right])
 {

     side += sidemove[speed];
 }
 if (gamekeydown[key_left])
 {

     side -= sidemove[speed];
 }
 if (joyxmove > 0)
     side += sidemove[speed];
 if (joyxmove < 0)
     side -= sidemove[speed];

    }
    else
    {
 if (gamekeydown[key_right])
     cmd->angleturn -= angleturn[tspeed];
 if (gamekeydown[key_left])
     cmd->angleturn += angleturn[tspeed];
 if (joyxmove > 0)
     cmd->angleturn -= angleturn[tspeed];
 if (joyxmove < 0)
     cmd->angleturn += angleturn[tspeed];
    }

    if (gamekeydown[key_up])
    {

 forward += forwardmove[speed];
    }
    if (gamekeydown[key_down])
    {

 forward -= forwardmove[speed];
    }

    if (joyymove < 0)
        forward += forwardmove[speed];
    if (joyymove > 0)
        forward -= forwardmove[speed];

    if (gamekeydown[key_strafeleft]
     || joybuttons[joybstrafeleft]
     || mousebuttons[mousebstrafeleft]
     || joystrafemove < 0)
    {
        side -= sidemove[speed];
    }

    if (gamekeydown[key_straferight]
     || joybuttons[joybstraferight]
     || mousebuttons[mousebstraferight]
     || joystrafemove > 0)
    {
        side += sidemove[speed];
    }


    cmd->chatchar = HU_dequeueChatChar();

    if (gamekeydown[key_fire] || mousebuttons[mousebfire]
 || joybuttons[joybfire])
 cmd->buttons |= BT_ATTACK;

    if (gamekeydown[key_use]
     || joybuttons[joybuse]
     || mousebuttons[mousebuse])
    {
 cmd->buttons |= BT_USE;

 dclicks = 0;
    }





    if (gamestate == GS_LEVEL && next_weapon != 0)
    {
        i = G_NextWeapon(next_weapon);
        cmd->buttons |= BT_CHANGE;
        cmd->buttons |= i << BT_WEAPONSHIFT;
    }
    else
    {


        for (i=0; i<(sizeof(weapon_keys) / sizeof(*weapon_keys)); ++i)
        {
            int key = *weapon_keys[i];

            if (gamekeydown[key])
            {
                cmd->buttons |= BT_CHANGE;
                cmd->buttons |= i<<BT_WEAPONSHIFT;
                break;
            }
        }
    }

    next_weapon = 0;


    if (mousebuttons[mousebforward])
    {
 forward += forwardmove[speed];
    }
    if (mousebuttons[mousebbackward])
    {
        forward -= forwardmove[speed];
    }

    if (dclick_use)
    {

        if (mousebuttons[mousebforward] != dclickstate && dclicktime > 1 )
        {
            dclickstate = mousebuttons[mousebforward];
            if (dclickstate)
                dclicks++;
            if (dclicks == 2)
            {
                cmd->buttons |= BT_USE;
                dclicks = 0;
            }
            else
                dclicktime = 0;
        }
        else
        {
            dclicktime += ticdup;
            if (dclicktime > 20)
            {
                dclicks = 0;
                dclickstate = 0;
            }
        }


        bstrafe =
            mousebuttons[mousebstrafe]
            || joybuttons[joybstrafe];
        if (bstrafe != dclickstate2 && dclicktime2 > 1 )
        {
            dclickstate2 = bstrafe;
            if (dclickstate2)
                dclicks2++;
            if (dclicks2 == 2)
            {
                cmd->buttons |= BT_USE;
                dclicks2 = 0;
            }
            else
                dclicktime2 = 0;
        }
        else
        {
            dclicktime2 += ticdup;
            if (dclicktime2 > 20)
            {
                dclicks2 = 0;
                dclickstate2 = 0;
            }
        }
    }

    forward += mousey;

    if (strafe)
 side += mousex*2;
    else
 cmd->angleturn -= mousex*0x8;

    if (mousex == 0)
    {


        testcontrols_mousespeed = 0;
    }

    mousex = mousey = 0;

    if (forward > (forwardmove[1]))
 forward = (forwardmove[1]);
    else if (forward < -(forwardmove[1]))
 forward = -(forwardmove[1]);
    if (side > (forwardmove[1]))
 side = (forwardmove[1]);
    else if (side < -(forwardmove[1]))
 side = -(forwardmove[1]);

    cmd->forwardmove += forward;
    cmd->sidemove += side;


    if (sendpause)
    {
 sendpause = false;
 cmd->buttons = BT_SPECIAL | BTS_PAUSE;
    }

    if (sendsave)
    {
 sendsave = false;
 cmd->buttons = BT_SPECIAL | BTS_SAVEGAME | (savegameslot<<BTS_SAVESHIFT);
    }



    if (lowres_turn)
    {
        static signed short carry = 0;
        signed short desired_angleturn;

        desired_angleturn = cmd->angleturn + carry;




        cmd->angleturn = (desired_angleturn + 128) & 0xff00;




        carry = desired_angleturn - cmd->angleturn;
    }
}





void G_DoLoadLevel (void)
{
    int i;







    skyflatnum = R_FlatNumForName(("F_SKY1"));



    if ((gamemode == commercial)
     && (gameversion == exe_final2 || gameversion == exe_chex))
    {
        char *skytexturename;

        if (gamemap < 12)
        {
            skytexturename = "SKY1";
        }
        else if (gamemap < 21)
        {
            skytexturename = "SKY2";
        }
        else
        {
            skytexturename = "SKY3";
        }

        skytexturename = (skytexturename);

        skytexture = R_TextureNumForName(skytexturename);
    }

    levelstarttic = gametic;

    if (wipegamestate == GS_LEVEL)
 wipegamestate = -1;

    gamestate = GS_LEVEL;

    for (i=0 ; i<4 ; i++)
    {
 turbodetected[i] = false;
 if (playeringame[i] && players[i].playerstate == PST_DEAD)
     players[i].playerstate = PST_REBORN;
 memset (players[i].frags,0,sizeof(players[i].frags));
    }

    P_SetupLevel (gameepisode, gamemap, 0, gameskill);
    displayplayer = consoleplayer;
    gameaction = ga_nothing;
    Z_CheckHeap ();



    memset (gamekeydown, 0, sizeof(gamekeydown));
    joyxmove = joyymove = joystrafemove = 0;
    mousex = mousey = 0;
    sendpause = sendsave = paused = false;
    memset(mousearray, 0, sizeof(mousearray));
    memset(joyarray, 0, sizeof(joyarray));

    if (testcontrols)
    {
        players[consoleplayer].message = "Press escape to quit.";
    }
}

static void SetJoyButtons(unsigned int buttons_mask)
{
    int i;

    for (i=0; i<20; ++i)
    {
        int button_on = (buttons_mask & (1 << i)) != 0;



        if (!joybuttons[i] && button_on)
        {


            if (i == joybprevweapon)
            {
                next_weapon = -1;
            }
            else if (i == joybnextweapon)
            {
                next_weapon = 1;
            }
        }

        joybuttons[i] = button_on;
    }
}

static void SetMouseButtons(unsigned int buttons_mask)
{
    int i;

    for (i=0; i<8; ++i)
    {
        unsigned int button_on = (buttons_mask & (1 << i)) != 0;



        if (!mousebuttons[i] && button_on)
        {
            if (i == mousebprevweapon)
            {
                next_weapon = -1;
            }
            else if (i == mousebnextweapon)
            {
                next_weapon = 1;
            }
        }

 mousebuttons[i] = button_on;
    }
}





boolean G_Responder (event_t* ev)
{

    if (gamestate == GS_LEVEL && ev->type == ev_keydown
     && ev->data1 == key_spy && (singledemo || !deathmatch) )
    {

 do
 {
     displayplayer++;
     if (displayplayer == 4)
  displayplayer = 0;
 } while (!playeringame[displayplayer] && displayplayer != consoleplayer);
 return true;
    }


    if (gameaction == ga_nothing && !singledemo &&
 (demoplayback || gamestate == GS_DEMOSCREEN)
 )
    {
 if (ev->type == ev_keydown ||
     (ev->type == ev_mouse && ev->data1) ||
     (ev->type == ev_joystick && ev->data1) )
 {
     M_StartControlPanel ();
     return true;
 }
 return false;
    }

    if (gamestate == GS_LEVEL)
    {







 if (HU_Responder (ev))
     return true;
 if (ST_Responder (ev))
     return true;
 if (AM_Responder (ev))
     return true;
    }

    if (gamestate == GS_FINALE)
    {
 if (F_Responder (ev))
     return true;
    }

    if (testcontrols && ev->type == ev_mouse)
    {





        testcontrols_mousespeed = abs(ev->data2);
    }




    if (ev->type == ev_keydown && ev->data1 == key_prevweapon)
    {
        next_weapon = -1;
    }
    else if (ev->type == ev_keydown && ev->data1 == key_nextweapon)
    {
        next_weapon = 1;
    }

    switch (ev->type)
    {
      case ev_keydown:
 if (ev->data1 == key_pause)
 {
     sendpause = true;
 }
        else if (ev->data1 <256)
        {
     gamekeydown[ev->data1] = true;
        }

 return true;

      case ev_keyup:
 if (ev->data1 <256)
     gamekeydown[ev->data1] = false;
 return false;

      case ev_mouse:
        SetMouseButtons(ev->data1);
 mousex = ev->data2*(mouseSensitivity+5)/10;
 mousey = ev->data3*(mouseSensitivity+5)/10;
 return true;

      case ev_joystick:
        SetJoyButtons(ev->data1);
 joyxmove = ev->data2;
 joyymove = ev->data3;
        joystrafemove = ev->data4;
 return true;

      default:
 break;
    }

    return false;
}







void G_Ticker (void)
{
    int i;
    int buf;
    ticcmd_t* cmd;


    for (i=0 ; i<4 ; i++)
 if (playeringame[i] && players[i].playerstate == PST_REBORN)
     G_DoReborn (i);


    while (gameaction != ga_nothing)
    {
 switch (gameaction)
 {
   case ga_loadlevel:
     G_DoLoadLevel ();
     break;
   case ga_newgame:
     G_DoNewGame ();
     break;
   case ga_loadgame:
     G_DoLoadGame ();
     break;
   case ga_savegame:
     G_DoSaveGame ();
     break;
   case ga_playdemo:
     G_DoPlayDemo ();
     break;
   case ga_completed:
     G_DoCompleted ();
     break;
   case ga_victory:
     F_StartFinale ();
     break;
   case ga_worlddone:
     G_DoWorldDone ();
     break;
   case ga_screenshot:
     V_ScreenShot("DOOM%02i.%s");
            players[consoleplayer].message = ("screen shot");
     gameaction = ga_nothing;
     break;
   case ga_nothing:
     break;
 }
    }



    buf = (gametic/ticdup)%128;

    for (i=0 ; i<4 ; i++)
    {
 if (playeringame[i])
 {
     cmd = &players[i].cmd;

     memcpy(cmd, &netcmds[i], sizeof(ticcmd_t));

     if (demoplayback)
  G_ReadDemoTiccmd (cmd);
     if (demorecording)
  G_WriteDemoTiccmd (cmd);
            if (cmd->forwardmove > 0x32)
            {
                turbodetected[i] = true;
            }

            if ((gametic & 31) == 0
             && ((gametic >> 5) % 4) == i
             && turbodetected[i])
            {
                static char turbomessage[80];
                extern char *player_names[4];
                M_snprintf(turbomessage, sizeof(turbomessage),
                           "%s is turbo!", player_names[i]);
                players[consoleplayer].message = turbomessage;
                turbodetected[i] = false;
            }

     if (netgame && !netdemo && !(gametic%ticdup) )
     {
  if (gametic > 128
      && consistancy[i][buf] != cmd->consistancy)
  {
      I_Error ("consistency failure (%i should be %i)",
        cmd->consistancy, consistancy[i][buf]);
  }
  if (players[i].mo)
      consistancy[i][buf] = players[i].mo->x;
  else
      consistancy[i][buf] = rndindex;
     }
 }
    }


    for (i=0 ; i<4 ; i++)
    {
 if (playeringame[i])
 {
     if (players[i].cmd.buttons & BT_SPECIAL)
     {
  switch (players[i].cmd.buttons & BT_SPECIALMASK)
  {
    case BTS_PAUSE:
      paused ^= 1;
      if (paused)
   S_PauseSound ();
      else
   S_ResumeSound ();
      break;

    case BTS_SAVEGAME:
      if (!savedescription[0])
                    {
                        M_StringCopy(savedescription, "NET GAME",
                                     sizeof(savedescription));
                    }

      savegameslot =
   (players[i].cmd.buttons & BTS_SAVEMASK)>>BTS_SAVESHIFT;
      gameaction = ga_savegame;
      break;
  }
     }
 }
    }



    if (oldgamestate == GS_INTERMISSION && gamestate != GS_INTERMISSION)
    {
        WI_End();
    }

    oldgamestate = gamestate;


    switch (gamestate)
    {
      case GS_LEVEL:
 P_Ticker ();
 ST_Ticker ();
 AM_Ticker ();
 HU_Ticker ();
 break;

      case GS_INTERMISSION:
 WI_Ticker ();
 break;

      case GS_FINALE:
 F_Ticker ();
 break;

      case GS_DEMOSCREEN:
 D_PageTicker ();
 break;
    }
}
void G_InitPlayer (int player)
{

    G_PlayerReborn (player);
}







void G_PlayerFinishLevel (int player)
{
    player_t* p;

    p = &players[player];

    memset (p->powers, 0, sizeof (p->powers));
    memset (p->cards, 0, sizeof (p->cards));
    p->mo->flags &= ~MF_SHADOW;
    p->extralight = 0;
    p->fixedcolormap = 0;
    p->damagecount = 0;
    p->bonuscount = 0;
}







void G_PlayerReborn (int player)
{
    player_t* p;
    int i;
    int frags[4];
    int killcount;
    int itemcount;
    int secretcount;

    memcpy (frags,players[player].frags,sizeof(frags));
    killcount = players[player].killcount;
    itemcount = players[player].itemcount;
    secretcount = players[player].secretcount;

    p = &players[player];
    memset (p, 0, sizeof(*p));

    memcpy (players[player].frags, frags, sizeof(players[player].frags));
    players[player].killcount = killcount;
    players[player].itemcount = itemcount;
    players[player].secretcount = secretcount;

    p->usedown = p->attackdown = true;
    p->playerstate = PST_LIVE;
    p->health = 100;
    p->readyweapon = p->pendingweapon = wp_pistol;
    p->weaponowned[wp_fist] = true;
    p->weaponowned[wp_pistol] = true;
    p->ammo[am_clip] = 50;

    for (i=0 ; i<NUMAMMO ; i++)
 p->maxammo[i] = maxammo[i];

}







void P_SpawnPlayer (mapthing_t* mthing);

boolean
G_CheckSpot
( int playernum,
  mapthing_t* mthing )
{
    fixed_t x;
    fixed_t y;
    subsector_t* ss;
    mobj_t* mo;
    int i;

    if (!players[playernum].mo)
    {

 for (i=0 ; i<playernum ; i++)
     if (players[i].mo->x == mthing->x << 16
  && players[i].mo->y == mthing->y << 16)
  return false;
 return true;
    }

    x = mthing->x << 16;
    y = mthing->y << 16;

    if (!P_CheckPosition (players[playernum].mo, x, y) )
 return false;


    if (bodyqueslot >= 32)
 P_RemoveMobj (bodyque[bodyqueslot%32]);
    bodyque[bodyqueslot%32] = players[playernum].mo;
    bodyqueslot++;


    ss = R_PointInSubsector (x,y);
    {
        fixed_t xa, ya;
        signed int an;




        an = (0x20000000 >> 19) * ((signed int) mthing->angle / 45);

        switch (an)
        {
            case 4096:
                xa = finetangent[2048];
                ya = finetangent[0];
                break;
            case 5120:
                xa = finetangent[3072];
                ya = finetangent[1024];
                break;
            case 6144:
                xa = finesine[0];
                ya = finetangent[2048];
                break;
            case 7168:
                xa = finesine[1024];
                ya = finetangent[3072];
                break;
            case 0:
            case 1024:
            case 2048:
            case 3072:
                xa = finecosine[an];
                ya = finesine[an];
                break;
            default:
                I_Error("G_CheckSpot: unexpected angle %d\n", an);
                xa = ya = 0;
                break;
        }
        mo = P_SpawnMobj(x + 20 * xa, y + 20 * ya,
                         ss->sector->floorheight, MT_TFOG);
    }

    if (players[consoleplayer].viewz != 1)
 S_StartSound (mo, sfx_telept);

    return true;
}







void G_DeathMatchSpawnPlayer (int playernum)
{
    int i,j;
    int selections;

    selections = deathmatch_p - deathmatchstarts;
    if (selections < 4)
 I_Error ("Only %i deathmatch spots, 4 required", selections);

    for (j=0 ; j<20 ; j++)
    {
 i = P_Random() % selections;
 if (G_CheckSpot (playernum, &deathmatchstarts[i]) )
 {
     deathmatchstarts[i].type = playernum+1;
     P_SpawnPlayer (&deathmatchstarts[i]);
     return;
 }
    }


    P_SpawnPlayer (&playerstarts[playernum]);
}




void G_DoReborn (int playernum)
{
    int i;

    if (!netgame)
    {

 gameaction = ga_loadlevel;
    }
    else
    {



 players[playernum].mo->player = ((void*)0);


 if (deathmatch)
 {
     G_DeathMatchSpawnPlayer (playernum);
     return;
 }

 if (G_CheckSpot (playernum, &playerstarts[playernum]) )
 {
     P_SpawnPlayer (&playerstarts[playernum]);
     return;
 }


 for (i=0 ; i<4 ; i++)
 {
     if (G_CheckSpot (playernum, &playerstarts[i]) )
     {
  playerstarts[i].type = playernum+1;
  P_SpawnPlayer (&playerstarts[i]);
  playerstarts[i].type = i+1;
  return;
     }

 }
 P_SpawnPlayer (&playerstarts[playernum]);
    }
}


void G_ScreenShot (void)
{
    gameaction = ga_screenshot;
}




int pars[4][10] =
{
    {0},
    {0,30,75,120,90,165,180,180,30,165},
    {0,90,90,90,120,90,360,240,30,170},
    {0,90,45,90,150,90,90,165,30,135}
};


int cpars[32] =
{
    30,90,120,120,90,150,120,120,270,90,
    210,150,150,150,210,150,420,150,210,150,
    240,150,180,150,150,300,330,420,300,180,
    120,30
};





boolean secretexit;
extern char* pagename;

void G_ExitLevel (void)
{
    secretexit = false;
    gameaction = ga_completed;
}


void G_SecretExitLevel (void)
{

    if ( (gamemode == commercial)
      && (W_CheckNumForName("map31")<0))
 secretexit = false;
    else
 secretexit = true;
    gameaction = ga_completed;
}

void G_DoCompleted (void)
{
    int i;

    gameaction = ga_nothing;

    for (i=0 ; i<4 ; i++)
 if (playeringame[i])
     G_PlayerFinishLevel (i);

    if (automapactive)
 AM_Stop ();

    if (gamemode != commercial)
    {


        if (gameversion == exe_chex)
        {
            if (gamemap == 5)
            {
                gameaction = ga_victory;
                return;
            }
        }
        else
        {
            switch(gamemap)
            {
              case 8:
                gameaction = ga_victory;
                return;
              case 9:
                for (i=0 ; i<4 ; i++)
                    players[i].didsecret = true;
                break;
            }
        }
    }


    if ( (gamemap == 8)
  && (gamemode != commercial) )
    {

 gameaction = ga_victory;
 return;
    }

    if ( (gamemap == 9)
  && (gamemode != commercial) )
    {

 for (i=0 ; i<4 ; i++)
     players[i].didsecret = true;
    }



    wminfo.didsecret = players[consoleplayer].didsecret;
    wminfo.epsd = gameepisode -1;
    wminfo.last = gamemap -1;


    if ( gamemode == commercial)
    {
 if (secretexit)
     switch(gamemap)
     {
       case 15: wminfo.next = 30; break;
       case 31: wminfo.next = 31; break;
     }
 else
     switch(gamemap)
     {
       case 31:
       case 32: wminfo.next = 15; break;
       default: wminfo.next = gamemap;
     }
    }
    else
    {
 if (secretexit)
     wminfo.next = 8;
 else if (gamemap == 9)
 {

     switch (gameepisode)
     {
       case 1:
  wminfo.next = 3;
  break;
       case 2:
  wminfo.next = 5;
  break;
       case 3:
  wminfo.next = 6;
  break;
       case 4:
  wminfo.next = 2;
  break;
     }
 }
 else
     wminfo.next = gamemap;
    }

    wminfo.maxkills = totalkills;
    wminfo.maxitems = totalitems;
    wminfo.maxsecret = totalsecret;
    wminfo.maxfrags = 0;




    if (gamemode == commercial)
 wminfo.partime = 35*cpars[gamemap-1];
    else if (gameepisode < 4)
 wminfo.partime = 35*pars[gameepisode][gamemap];
    else
        wminfo.partime = 35*cpars[gamemap];

    wminfo.pnum = consoleplayer;

    for (i=0 ; i<4 ; i++)
    {
 wminfo.plyr[i].in = playeringame[i];
 wminfo.plyr[i].skills = players[i].killcount;
 wminfo.plyr[i].sitems = players[i].itemcount;
 wminfo.plyr[i].ssecret = players[i].secretcount;
 wminfo.plyr[i].stime = leveltime;
 memcpy (wminfo.plyr[i].frags, players[i].frags
  , sizeof(wminfo.plyr[i].frags));
    }

    gamestate = GS_INTERMISSION;
    viewactive = false;
    automapactive = false;

    StatCopy(&wminfo);

    WI_Start (&wminfo);
}





void G_WorldDone (void)
{
    gameaction = ga_worlddone;

    if (secretexit)
 players[consoleplayer].didsecret = true;

    if ( gamemode == commercial )
    {
 switch (gamemap)
 {
   case 15:
   case 31:
     if (!secretexit)
  break;
   case 6:
   case 11:
   case 20:
   case 30:
     F_StartFinale ();
     break;
 }
    }
}

void G_DoWorldDone (void)
{
    gamestate = GS_LEVEL;
    gamemap = wminfo.next+1;
    G_DoLoadLevel ();
    gameaction = ga_nothing;
    viewactive = true;
}







extern boolean setsizeneeded;
void R_ExecuteSetViewSize (void);

char savename[256];

void G_LoadGame (char* name)
{
    M_StringCopy(savename, name, sizeof(savename));
    gameaction = ga_loadgame;
}




void G_DoLoadGame (void)
{
    int savedleveltime;

    gameaction = ga_nothing;

    save_stream = fopen(savename, "rb");

    if (save_stream == ((void*)0))
    {
     return;
    }

    savegame_error = false;

    if (!P_ReadSaveGameHeader())
    {
        fclose(save_stream);
        return;
    }

    savedleveltime = leveltime;


    G_InitNew (gameskill, gameepisode, gamemap);

    leveltime = savedleveltime;


    P_UnArchivePlayers ();
    P_UnArchiveWorld ();
    P_UnArchiveThinkers ();
    P_UnArchiveSpecials ();

    if (!P_ReadSaveGameEOF())
 I_Error ("Bad savegame");

    fclose(save_stream);

    if (setsizeneeded)
     R_ExecuteSetViewSize ();


    R_FillBackScreen ();
}







void
G_SaveGame
( int slot,
  char* description )
{
    savegameslot = slot;
    M_StringCopy(savedescription, description, sizeof(savedescription));
    sendsave = true;
}

void G_DoSaveGame (void)
{
    char *savegame_file;
    char *temp_savegame_file;
    char *recovery_savegame_file;

    recovery_savegame_file = ((void*)0);
    temp_savegame_file = P_TempSaveGameFile();
    savegame_file = P_SaveGameFile(savegameslot);





    save_stream = fopen(temp_savegame_file, "wb");

    if (save_stream == ((void*)0))
    {


        recovery_savegame_file = M_TempFile("recovery.dsg");
        save_stream = fopen(recovery_savegame_file, "wb");
        if (save_stream == ((void*)0))
        {
            I_Error("Failed to open either '%s' or '%s' to write savegame.",
                    temp_savegame_file, recovery_savegame_file);
        }
    }

    savegame_error = false;

    P_WriteSaveGameHeader(savedescription);

    P_ArchivePlayers ();
    P_ArchiveWorld ();
    P_ArchiveThinkers ();
    P_ArchiveSpecials ();

    P_WriteSaveGameEOF();




    if (vanilla_savegame_limit && ftell(save_stream) > 0x2c000)
    {
        I_Error ("Savegame buffer overrun");
    }



    fclose(save_stream);

    if (recovery_savegame_file != ((void*)0))
    {



        I_Error("Failed to open savegame file '%s' for writing.\n"
                "But your game has been saved to '%s' for recovery.",
                temp_savegame_file, recovery_savegame_file);
    }




    remove(savegame_file);
    rename(temp_savegame_file, savegame_file);

    gameaction = ga_nothing;
    M_StringCopy(savedescription, "", sizeof(savedescription));

    players[consoleplayer].message = ("game saved.");


    R_FillBackScreen ();
}







skill_t d_skill;
int d_episode;
int d_map;

void
G_DeferedInitNew
( skill_t skill,
  int episode,
  int map)
{
    d_skill = skill;
    d_episode = episode;
    d_map = map;
    gameaction = ga_newgame;
}


void G_DoNewGame (void)
{
    demoplayback = false;
    netdemo = false;
    netgame = false;
    deathmatch = false;
    playeringame[1] = playeringame[2] = playeringame[3] = 0;
    respawnparm = false;
    fastparm = false;
    nomonsters = false;
    consoleplayer = 0;
    G_InitNew (d_skill, d_episode, d_map);
    gameaction = ga_nothing;
}


void
G_InitNew
( skill_t skill,
  int episode,
  int map )
{
    char *skytexturename;
    int i;

    if (paused)
    {
 paused = false;
 S_ResumeSound ();
    }
    if (skill > sk_nightmare)
 skill = sk_nightmare;

    if (gameversion >= exe_ultimate)
    {
        if (episode == 0)
        {
            episode = 4;
        }
    }
    else
    {
        if (episode < 1)
        {
            episode = 1;
        }
        if (episode > 3)
        {
            episode = 3;
        }
    }

    if (episode > 1 && gamemode == shareware)
    {
        episode = 1;
    }

    if (map < 1)
 map = 1;

    if ( (map > 9)
  && ( gamemode != commercial) )
      map = 9;

    M_ClearRandom ();

    if (skill == sk_nightmare || respawnparm )
 respawnmonsters = true;
    else
 respawnmonsters = false;

    if (fastparm || (skill == sk_nightmare && gameskill != sk_nightmare) )
    {
 for (i=S_SARG_RUN1 ; i<=S_SARG_PAIN2 ; i++)
     states[i].tics >>= 1;
 mobjinfo[MT_BRUISERSHOT].speed = 20*(1<<16);
 mobjinfo[MT_HEADSHOT].speed = 20*(1<<16);
 mobjinfo[MT_TROOPSHOT].speed = 20*(1<<16);
    }
    else if (skill != sk_nightmare && gameskill == sk_nightmare)
    {
 for (i=S_SARG_RUN1 ; i<=S_SARG_PAIN2 ; i++)
     states[i].tics <<= 1;
 mobjinfo[MT_BRUISERSHOT].speed = 15*(1<<16);
 mobjinfo[MT_HEADSHOT].speed = 10*(1<<16);
 mobjinfo[MT_TROOPSHOT].speed = 10*(1<<16);
    }


    for (i=0 ; i<4 ; i++)
 players[i].playerstate = PST_REBORN;

    usergame = true;
    paused = false;
    demoplayback = false;
    automapactive = false;
    viewactive = true;
    gameepisode = episode;
    gamemap = map;
    gameskill = skill;

    viewactive = true;
    if (gamemode == commercial)
    {
        if (gamemap < 12)
            skytexturename = "SKY1";
        else if (gamemap < 21)
            skytexturename = "SKY2";
        else
            skytexturename = "SKY3";
    }
    else
    {
        switch (gameepisode)
        {
          default:
          case 1:
            skytexturename = "SKY1";
            break;
          case 2:
            skytexturename = "SKY2";
            break;
          case 3:
            skytexturename = "SKY3";
            break;
          case 4:
            skytexturename = "SKY4";
            break;
        }
    }

    skytexturename = (skytexturename);

    skytexture = R_TextureNumForName(skytexturename);


    G_DoLoadLevel ();
}
void G_ReadDemoTiccmd (ticcmd_t* cmd)
{
    if (*demo_p == 0x80)
    {

 G_CheckDemoStatus ();
 return;
    }
    cmd->forwardmove = ((signed char)*demo_p++);
    cmd->sidemove = ((signed char)*demo_p++);



    if (longtics)
    {
        cmd->angleturn = *demo_p++;
        cmd->angleturn |= (*demo_p++) << 8;
    }
    else
    {
        cmd->angleturn = ((unsigned char) *demo_p++)<<8;
    }

    cmd->buttons = (unsigned char)*demo_p++;
}



static void IncreaseDemoBuffer(void)
{
    int current_length;
    byte *new_demobuffer;
    byte *new_demop;
    int new_length;



    current_length = demoend - demobuffer;


    new_length = current_length * 2;

    new_demobuffer = Z_Malloc(new_length, PU_STATIC, 0);
    new_demop = new_demobuffer + (demo_p - demobuffer);



    memcpy(new_demobuffer, demobuffer, current_length);



    Z_Free(demobuffer);

    demobuffer = new_demobuffer;
    demo_p = new_demop;
    demoend = demobuffer + new_length;
}

void G_WriteDemoTiccmd (ticcmd_t* cmd)
{
    byte *demo_start;

    if (gamekeydown[key_demo_quit])
 G_CheckDemoStatus ();

    demo_start = demo_p;

    *demo_p++ = cmd->forwardmove;
    *demo_p++ = cmd->sidemove;



    if (longtics)
    {
        *demo_p++ = (cmd->angleturn & 0xff);
        *demo_p++ = (cmd->angleturn >> 8) & 0xff;
    }
    else
    {
        *demo_p++ = cmd->angleturn >> 8;
    }

    *demo_p++ = cmd->buttons;


    demo_p = demo_start;

    if (demo_p > demoend - 16)
    {
        if (vanilla_demo_limit)
        {

            G_CheckDemoStatus ();
            return;
        }
        else
        {



            IncreaseDemoBuffer();
        }
    }

    G_ReadDemoTiccmd (cmd);
}






void G_RecordDemo (char *name)
{
    size_t demoname_size;
    int i;
    int maxsize;

    usergame = false;
    demoname_size = strlen(name) + 5;
    demoname = Z_Malloc(demoname_size, PU_STATIC, ((void*)0));
    M_snprintf(demoname, demoname_size, "%s.lmp", name);
    maxsize = 0x20000;
    i = M_CheckParmWithArgs("-maxdemo", 1);
    if (i)
 maxsize = atoi(myargv[i+1])*1024;
    demobuffer = Z_Malloc (maxsize,PU_STATIC,((void*)0));
    demoend = demobuffer + maxsize;

    demorecording = true;
}


int G_VanillaVersionCode(void)
{
    switch (gameversion)
    {
        case exe_doom_1_2:
            I_Error("Doom 0 does not have a version code!");
        case exe_doom_1_666:
            return 106;
        case exe_doom_1_7:
            return 107;
        case exe_doom_1_8:
            return 108;
        case exe_doom_1_9:
        default:
            return 109;
    }
}

void G_BeginRecording (void)
{
    int i;







    longtics = M_CheckParm("-longtics") != 0;



    lowres_turn = !longtics;

    demo_p = demobuffer;



    if (longtics)
    {
        *demo_p++ = 111;
    }
    else
    {
        *demo_p++ = G_VanillaVersionCode();
    }

    *demo_p++ = gameskill;
    *demo_p++ = gameepisode;
    *demo_p++ = gamemap;
    *demo_p++ = deathmatch;
    *demo_p++ = respawnparm;
    *demo_p++ = fastparm;
    *demo_p++ = nomonsters;
    *demo_p++ = consoleplayer;

    for (i=0 ; i<4 ; i++)
 *demo_p++ = playeringame[i];
}






char* defdemoname;

void G_DeferedPlayDemo (char* name)
{
    defdemoname = name;
    gameaction = ga_playdemo;
}



static char *DemoVersionDescription(int version)
{
    static char resultbuf[16];

    switch (version)
    {
        case 104:
            return "v1.4";
        case 105:
            return "v1.5";
        case 106:
            return "v1.6/v1.666";
        case 107:
            return "v1.7/v1.7a";
        case 108:
            return "v1.8";
        case 109:
            return "v1.9";
        default:
            break;
    }




    if (version >= 0 && version <= 4)
    {
        return "v1.0/v1.1/v1.2";
    }
    else
    {
        M_snprintf(resultbuf, sizeof(resultbuf),
                   "%i.%i (unknown)", version / 100, version % 100);
        return resultbuf;
    }
}

void G_DoPlayDemo (void)
{
    skill_t skill;
    int i, episode, map;
    int demoversion;

    gameaction = ga_nothing;
    demobuffer = demo_p = W_CacheLumpName (defdemoname, PU_STATIC);

    demoversion = *demo_p++;

    if (demoversion == G_VanillaVersionCode())
    {
        longtics = false;
    }
    else if (demoversion == 111)
    {

        longtics = true;
    }
    else
    {
        char *message = "Demo is from a different game version!\n"
                        "(read %i, should be %i)\n"
                        "\n"
                        "*** You may need to upgrade your version "
                            "of Doom to v1.9. ***\n"
                        "    See: https://www.doomworld.com/classicdoom"
                                  "/info/patches.php\n"
                        "    This appears to be %s.";


        printf(message, demoversion, G_VanillaVersionCode(),
                         DemoVersionDescription(demoversion));
    }

    skill = *demo_p++;
    episode = *demo_p++;
    map = *demo_p++;
    deathmatch = *demo_p++;
    respawnparm = *demo_p++;
    fastparm = *demo_p++;
    nomonsters = *demo_p++;
    consoleplayer = *demo_p++;

    for (i=0 ; i<4 ; i++)
 playeringame[i] = *demo_p++;

    if (playeringame[1] || M_CheckParm("-solo-net") > 0
                        || M_CheckParm("-netdemo") > 0)
    {
 netgame = true;
 netdemo = true;
    }


    precache = false;
    G_InitNew (skill, episode, map);
    precache = true;
    starttime = I_GetTime ();

    usergame = false;
    demoplayback = true;
}




void G_TimeDemo (char* name)
{






    nodrawers = M_CheckParm ("-nodraw");

    timingdemo = true;
    singletics = true;

    defdemoname = name;
    gameaction = ga_playdemo;
}
boolean G_CheckDemoStatus (void)
{
    int endtime;

    if (timingdemo)
    {
        float fps;
        int realtics;

 endtime = I_GetTime ();
        realtics = endtime - starttime;
        fps = ((float) gametic * 35) / realtics;


        timingdemo = false;
        demoplayback = false;

 I_Error ("timed %i gametics in %i realtics (%f fps)",
                 gametic, realtics, fps);
    }

    if (demoplayback)
    {
        W_ReleaseLumpName(defdemoname);
 demoplayback = false;
 netdemo = false;
 netgame = false;
 deathmatch = false;
 playeringame[1] = playeringame[2] = playeringame[3] = 0;
 respawnparm = false;
 fastparm = false;
 nomonsters = false;
 consoleplayer = 0;

        if (singledemo)
            I_Quit ();
        else
            D_AdvanceDemo ();

 return true;
    }

    if (demorecording)
    {
 *demo_p++ = 0x80;
 M_WriteFile (demoname, demobuffer, demo_p - demobuffer);
 Z_Free (demobuffer);
 demorecording = false;
 I_Error ("Demo %s recorded",demoname);
    }

    return false;
}
typedef struct
{

    int x;
    int y;

    patch_t** f;
    int sc;
    char l[80 +1];
    int len;


    int needsupdate;

} hu_textline_t;





typedef struct
{
    hu_textline_t l[4];
    int h;
    int cl;


    boolean* on;
    boolean laston;

} hu_stext_t;





typedef struct
{
    hu_textline_t l;


    int lm;


    boolean* on;
    boolean laston;

} hu_itext_t;







void HUlib_init(void);






void HUlib_clearTextLine(hu_textline_t *t);

void HUlib_initTextLine(hu_textline_t *t, int x, int y, patch_t **f, int sc);


boolean HUlib_addCharToTextLine(hu_textline_t *t, char ch);


boolean HUlib_delCharFromTextLine(hu_textline_t *t);


void HUlib_drawTextLine(hu_textline_t *l, boolean drawcursor);


void HUlib_eraseTextLine(hu_textline_t *l);







void
HUlib_initSText
( hu_stext_t* s,
  int x,
  int y,
  int h,
  patch_t** font,
  int startchar,
  boolean* on );


void HUlib_addLineToSText(hu_stext_t* s);


void
HUlib_addMessageToSText
( hu_stext_t* s,
  char* prefix,
  char* msg );


void HUlib_drawSText(hu_stext_t* s);


void HUlib_eraseSText(hu_stext_t* s);


void
HUlib_initIText
( hu_itext_t* it,
  int x,
  int y,
  patch_t** font,
  int startchar,
  boolean* on );


void HUlib_delCharFromIText(hu_itext_t* it);


void HUlib_eraseLineFromIText(hu_itext_t* it);


void HUlib_resetIText(hu_itext_t* it);


void
HUlib_addPrefixToIText
( hu_itext_t* it,
  char* str );


boolean
HUlib_keyInIText
( hu_itext_t* it,
  unsigned char ch );

void HUlib_drawIText(hu_itext_t* it);


void HUlib_eraseIText(hu_itext_t* it);






extern boolean automapactive;

void HUlib_init(void)
{
}

void HUlib_clearTextLine(hu_textline_t* t)
{
    t->len = 0;
    t->l[0] = 0;
    t->needsupdate = true;
}

void
HUlib_initTextLine
( hu_textline_t* t,
  int x,
  int y,
  patch_t** f,
  int sc )
{
    t->x = x;
    t->y = y;
    t->f = f;
    t->sc = sc;
    HUlib_clearTextLine(t);
}

boolean
HUlib_addCharToTextLine
( hu_textline_t* t,
  char ch )
{

    if (t->len == 80)
 return false;
    else
    {
 t->l[t->len++] = ch;
 t->l[t->len] = 0;
 t->needsupdate = 4;
 return true;
    }

}

boolean HUlib_delCharFromTextLine(hu_textline_t* t)
{

    if (!t->len) return false;
    else
    {
 t->l[--t->len] = 0;
 t->needsupdate = 4;
 return true;
    }

}

void
HUlib_drawTextLine
( hu_textline_t* l,
  boolean drawcursor )
{

    int i;
    int w;
    int x;
    unsigned char c;


    x = l->x;
    for (i=0;i<l->len;i++)
    {
 c = toupper((int)l->l[i]);
 if (c != ' '
     && c >= l->sc
     && c <= '_')
 {
     w = ((signed short) (l->f[c - l->sc]->width));
     if (x+w > 320)
  break;
     V_DrawPatchDirect(x, l->y, l->f[c - l->sc]);
     x += w;
 }
 else
 {
     x += 4;
     if (x >= 320)
  break;
 }
    }


    if (drawcursor
 && x + ((signed short) (l->f['_' - l->sc]->width)) <= 320)
    {
 V_DrawPatchDirect(x, l->y, l->f['_' - l->sc]);
    }
}



void HUlib_eraseTextLine(hu_textline_t* l)
{
    int lh;
    int y;
    int yoffset;





    if (!automapactive &&
 viewwindowx && l->needsupdate)
    {
 lh = ((signed short) (l->f[0]->height)) + 1;
 for (y=l->y,yoffset=y*320 ; y<l->y+lh ; y++,yoffset+=320)
 {
     if (y < viewwindowy || y >= viewwindowy + viewheight)
  R_VideoErase(yoffset, 320);
     else
     {
  R_VideoErase(yoffset, viewwindowx);
  R_VideoErase(yoffset + viewwindowx + viewwidth, viewwindowx);

     }
 }
    }

    if (l->needsupdate) l->needsupdate--;

}

void
HUlib_initSText
( hu_stext_t* s,
  int x,
  int y,
  int h,
  patch_t** font,
  int startchar,
  boolean* on )
{

    int i;

    s->h = h;
    s->on = on;
    s->laston = true;
    s->cl = 0;
    for (i=0;i<h;i++)
 HUlib_initTextLine(&s->l[i],
      x, y - i*(((signed short) (font[0]->height))+1),
      font, startchar);

}

void HUlib_addLineToSText(hu_stext_t* s)
{

    int i;


    if (++s->cl == s->h)
 s->cl = 0;
    HUlib_clearTextLine(&s->l[s->cl]);


    for (i=0 ; i<s->h ; i++)
 s->l[i].needsupdate = 4;

}

void
HUlib_addMessageToSText
( hu_stext_t* s,
  char* prefix,
  char* msg )
{
    HUlib_addLineToSText(s);
    if (prefix)
 while (*prefix)
     HUlib_addCharToTextLine(&s->l[s->cl], *(prefix++));

    while (*msg)
 HUlib_addCharToTextLine(&s->l[s->cl], *(msg++));
}

void HUlib_drawSText(hu_stext_t* s)
{
    int i, idx;
    hu_textline_t *l;

    if (!*s->on)
 return;


    for (i=0 ; i<s->h ; i++)
    {
 idx = s->cl - i;
 if (idx < 0)
     idx += s->h;

 l = &s->l[idx];


 HUlib_drawTextLine(l, false);
    }

}

void HUlib_eraseSText(hu_stext_t* s)
{

    int i;

    for (i=0 ; i<s->h ; i++)
    {
 if (s->laston && !*s->on)
     s->l[i].needsupdate = 4;
 HUlib_eraseTextLine(&s->l[i]);
    }
    s->laston = *s->on;

}

void
HUlib_initIText
( hu_itext_t* it,
  int x,
  int y,
  patch_t** font,
  int startchar,
  boolean* on )
{
    it->lm = 0;
    it->on = on;
    it->laston = true;
    HUlib_initTextLine(&it->l, x, y, font, startchar);
}



void HUlib_delCharFromIText(hu_itext_t* it)
{
    if (it->l.len != it->lm)
 HUlib_delCharFromTextLine(&it->l);
}

void HUlib_eraseLineFromIText(hu_itext_t* it)
{
    while (it->lm != it->l.len)
 HUlib_delCharFromTextLine(&it->l);
}


void HUlib_resetIText(hu_itext_t* it)
{
    it->lm = 0;
    HUlib_clearTextLine(&it->l);
}

void
HUlib_addPrefixToIText
( hu_itext_t* it,
  char* str )
{
    while (*str)
 HUlib_addCharToTextLine(&it->l, *(str++));
    it->lm = it->l.len;
}



boolean
HUlib_keyInIText
( hu_itext_t* it,
  unsigned char ch )
{
    ch = toupper(ch);

    if (ch >= ' ' && ch <= '_')
   HUlib_addCharToTextLine(&it->l, (char) ch);
    else
 if (ch == 0x7f)
     HUlib_delCharFromIText(it);
 else
     if (ch != 13)
  return false;

    return true;

}

void HUlib_drawIText(hu_itext_t* it)
{

    hu_textline_t *l = &it->l;

    if (!*it->on)
 return;
    HUlib_drawTextLine(l, true);

}

void HUlib_eraseIText(hu_itext_t* it)
{
    if (it->laston && !*it->on)
 it->l.needsupdate = 4;
    HUlib_eraseTextLine(&it->l);
    it->laston = *it->on;
}
char *chat_macros[10] =
{
    "No",
    "I'm ready to kick butt!",
    "I'm OK.",
    "I'm not looking too good!",
    "Help!",
    "You suck!",
    "Next time, scumbag...",
    "Come here!",
    "I'll take care of it.",
    "Yes"
};

char* player_names[] =
{
    "Green: ",
    "Indigo: ",
    "Brown: ",
    "Red: "
};

char chat_char;
static player_t* st_plr;
patch_t* hu_font[('_' - '!' + 1)];
static hu_textline_t w_title;
boolean chat_on;
static hu_itext_t w_chat;
static boolean always_off = false;
static char chat_dest[4];
static hu_itext_t w_inputbuffer[4];

static boolean message_on;
boolean message_dontfuckwithme;
static boolean message_nottobefuckedwith;

static hu_stext_t w_message;
static int message_counter;

extern int showMessages;

static boolean headsupactive = false;






char* mapnames[] =
{

    "E1M1: Hangar",
    "E1M2: Nuclear Plant",
    "E1M3: Toxin Refinery",
    "E1M4: Command Control",
    "E1M5: Phobos Lab",
    "E1M6: Central Processing",
    "E1M7: Computer Station",
    "E1M8: Phobos Anomaly",
    "E1M9: Military Base",

    "E2M1: Deimos Anomaly",
    "E2M2: Containment Area",
    "E2M3: Refinery",
    "E2M4: Deimos Lab",
    "E2M5: Command Center",
    "E2M6: Halls of the Damned",
    "E2M7: Spawning Vats",
    "E2M8: Tower of Babel",
    "E2M9: Fortress of Mystery",

    "E3M1: Hell Keep",
    "E3M2: Slough of Despair",
    "E3M3: Pandemonium",
    "E3M4: House of Pain",
    "E3M5: Unholy Cathedral",
    "E3M6: Mt. Erebus",
    "E3M7: Limbo",
    "E3M8: Dis",
    "E3M9: Warrens",

    "E4M1: Hell Beneath",
    "E4M2: Perfect Hatred",
    "E4M3: Sever The Wicked",
    "E4M4: Unruly Evil",
    "E4M5: They Will Repent",
    "E4M6: Against Thee Wickedly",
    "E4M7: And Hell Followed",
    "E4M8: Unto The Cruel",
    "E4M9: Fear",

    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL",
    "NEWLEVEL"
};







char *mapnames_commercial[] =
{


    "level 1: entryway",
    "level 2: underhalls",
    "level 3: the gantlet",
    "level 4: the focus",
    "level 5: the waste tunnels",
    "level 6: the crusher",
    "level 7: dead simple",
    "level 8: tricks and traps",
    "level 9: the pit",
    "level 10: refueling base",
    "level 11: 'o' of destruction!",

    "level 12: the factory",
    "level 13: downtown",
    "level 14: the inmost dens",
    "level 15: industrial zone",
    "level 16: suburbs",
    "level 17: tenements",
    "level 18: the courtyard",
    "level 19: the citadel",
    "level 20: gotcha!",

    "level 21: nirvana",
    "level 22: the catacombs",
    "level 23: barrels o' fun",
    "level 24: the chasm",
    "level 25: bloodfalls",
    "level 26: the abandoned mines",
    "level 27: monster condo",
    "level 28: the spirit world",
    "level 29: the living end",
    "level 30: icon of sin",
    "level 31: wolfenstein",
    "level 32: grosse",



    "level 1: congo",
    "level 2: well of souls",
    "level 3: aztec",
    "level 4: caged",
    "level 5: ghost town",
    "level 6: baron's lair",
    "level 7: caughtyard",
    "level 8: realm",
    "level 9: abattoire",
    "level 10: onslaught",
    "level 11: hunted",

    "level 12: speed",
    "level 13: the crypt",
    "level 14: genesis",
    "level 15: the twilight",
    "level 16: the omen",
    "level 17: compound",
    "level 18: neurosphere",
    "level 19: nme",
    "level 20: the death domain",

    "level 21: slayer",
    "level 22: impossible mission",
    "level 23: tombstone",
    "level 24: the final frontier",
    "level 25: the temple of darkness",
    "level 26: bunker",
    "level 27: anti-christ",
    "level 28: the sewers",
    "level 29: odyssey of noises",
    "level 30: the gateway of hell",
    "level 31: cyberden",
    "level 32: go 2 it",



    "level 1: system control",
    "level 2: human bbq",
    "level 3: power control",
    "level 4: wormhole",
    "level 5: hanger",
    "level 6: open season",
    "level 7: prison",
    "level 8: metal",
    "level 9: stronghold",
    "level 10: redemption",
    "level 11: storage facility",

    "level 12: crater",
    "level 13: nukage processing",
    "level 14: steel works",
    "level 15: dead zone",
    "level 16: deepest reaches",
    "level 17: processing area",
    "level 18: mill",
    "level 19: shipping/respawning",
    "level 20: central processing",

    "level 21: administration center",
    "level 22: habitat",
    "level 23: lunar mining project",
    "level 24: quarry",
    "level 25: baron's den",
    "level 26: ballistyx",
    "level 27: mount pain",
    "level 28: heck",
    "level 29: river styx",
    "level 30: last call",
    "level 31: pharaoh",
    "level 32: caribbean"
};

void HU_Init(void)
{

    int i;
    int j;
    char buffer[9];


    j = '!';
    for (i=0;i<('_' - '!' + 1);i++)
    {
 snprintf(buffer, 9, "STCFN%.3d", j++);
 hu_font[i] = (patch_t *) W_CacheLumpName(buffer, PU_STATIC);
    }

}

void HU_Stop(void)
{
    headsupactive = false;
}

void HU_Start(void)
{

    int i;
    char* s;

    if (headsupactive)
 HU_Stop();

    st_plr = &players[consoleplayer];
    message_on = false;
    message_dontfuckwithme = false;
    message_nottobefuckedwith = false;
    chat_on = false;


    HUlib_initSText(&w_message,
      0, 0, 1,
      hu_font,
      '!', &message_on);


    HUlib_initTextLine(&w_title,
         0, (167 - ((signed short) (hu_font[0]->height))),
         hu_font,
         '!');

    switch ( (gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) )
    {
      case doom:
 s = (mapnames[(gameepisode-1)*9+gamemap-1]);
 break;
      case doom2:
  s = (mapnames_commercial[gamemap-1]);
  break;
      case pack_plut:
 s = (mapnames_commercial[gamemap-1 + 32]);
 break;
      case pack_tnt:
 s = (mapnames_commercial[gamemap-1 + 64]);
 break;
      default:
         s = "Unknown level";
         break;
    }




    if (gameversion == exe_chex)
    {
        s = (mapnames[gamemap - 1]);
    }



    s = (s);

    while (*s)
 HUlib_addCharToTextLine(&w_title, *(s++));


    HUlib_initIText(&w_chat,
      0, (0 + 1*(((signed short) (hu_font[0]->height)) +1)),
      hu_font,
      '!', &chat_on);


    for (i=0 ; i<4 ; i++)
 HUlib_initIText(&w_inputbuffer[i], 0, 0, 0, 0, &always_off);

    headsupactive = true;

}

void HU_Drawer(void)
{

    HUlib_drawSText(&w_message);
    HUlib_drawIText(&w_chat);
    if (automapactive)
 HUlib_drawTextLine(&w_title, false);

}

void HU_Erase(void)
{

    HUlib_eraseSText(&w_message);
    HUlib_eraseIText(&w_chat);
    HUlib_eraseTextLine(&w_title);

}

void HU_Ticker(void)
{

    int i, rc;
    char c;


    if (message_counter && !--message_counter)
    {
 message_on = false;
 message_nottobefuckedwith = false;
    }

    if (showMessages || message_dontfuckwithme)
    {


 if ((st_plr->message && !message_nottobefuckedwith)
     || (st_plr->message && message_dontfuckwithme))
 {
     HUlib_addMessageToSText(&w_message, 0, st_plr->message);
     st_plr->message = 0;
     message_on = true;
     message_counter = (4*35);
     message_nottobefuckedwith = message_dontfuckwithme;
     message_dontfuckwithme = 0;
 }

    }


    if (netgame)
    {
 for (i=0 ; i<4; i++)
 {
     if (!playeringame[i])
  continue;
     if (i != consoleplayer
  && (c = players[i].cmd.chatchar))
     {
  if (c <= 5)
      chat_dest[i] = c;
  else
  {
      rc = HUlib_keyInIText(&w_inputbuffer[i], c);
      if (rc && c == 13)
      {
   if (w_inputbuffer[i].l.len
       && (chat_dest[i] == consoleplayer+1
    || chat_dest[i] == 5))
   {
       HUlib_addMessageToSText(&w_message,
          (player_names[i]),
          w_inputbuffer[i].l.l);

       message_nottobefuckedwith = true;
       message_on = true;
       message_counter = (4*35);
       if ( gamemode == commercial )
         S_StartSound(0, sfx_radio);
       else
         S_StartSound(0, sfx_tink);
   }
   HUlib_resetIText(&w_inputbuffer[i]);
      }
  }
  players[i].cmd.chatchar = 0;
     }
 }
    }

}



static char chatchars[128];
static int head = 0;
static int tail = 0;


void HU_queueChatChar(char c)
{
    if (((head + 1) & (128 -1)) == tail)
    {
 st_plr->message = ("[Message unsent]");
    }
    else
    {
 chatchars[head] = c;
 head = (head + 1) & (128 -1);
    }
}

char HU_dequeueChatChar(void)
{
    char c;

    if (head != tail)
    {
 c = chatchars[tail];
 tail = (tail + 1) & (128 -1);
    }
    else
    {
 c = 0;
    }

    return c;
}

boolean HU_Responder(event_t *ev)
{

    static char lastmessage[80 +1];
    char* macromessage;
    boolean eatkey = false;
    static boolean altdown = false;
    unsigned char c;
    int i;
    int numplayers;

    static int num_nobrainers = 0;

    numplayers = 0;
    for (i=0 ; i<4 ; i++)
 numplayers += playeringame[i];

    if (ev->data1 == (0x80+0x36))
    {
 return false;
    }
    else if (ev->data1 == (0x80+0x38) || ev->data1 == (0x80+0x38))
    {
 altdown = ev->type == ev_keydown;
 return false;
    }

    if (ev->type != ev_keydown)
 return false;

    if (!chat_on)
    {
 if (ev->data1 == key_message_refresh)
 {
     message_on = true;
     message_counter = (4*35);
     eatkey = true;
 }
 else if (netgame && ev->data2 == key_multi_msg)
 {
     eatkey = chat_on = true;
     HUlib_resetIText(&w_chat);
     HU_queueChatChar(5);
 }
 else if (netgame && numplayers > 2)
 {
     for (i=0; i<4 ; i++)
     {
  if (ev->data2 == key_multi_msgplayer[i])
  {
      if (playeringame[i] && i!=consoleplayer)
      {
   eatkey = chat_on = true;
   HUlib_resetIText(&w_chat);
   HU_queueChatChar(i+1);
   break;
      }
      else if (i == consoleplayer)
      {
   num_nobrainers++;
   if (num_nobrainers < 3)
       st_plr->message = ("You mumble to yourself");
   else if (num_nobrainers < 6)
       st_plr->message = ("Who's there?");
   else if (num_nobrainers < 9)
       st_plr->message = ("You scare yourself");
   else if (num_nobrainers < 32)
       st_plr->message = ("You start to rave");
   else
       st_plr->message = ("You've lost it...");
      }
  }
     }
 }
    }
    else
    {

 if (altdown)
 {
     c = ev->data1 - '0';
     if (c > 9)
  return false;

     macromessage = chat_macros[c];


     HU_queueChatChar(13);


     while (*macromessage)
  HU_queueChatChar(*macromessage++);
     HU_queueChatChar(13);


            chat_on = false;
            M_StringCopy(lastmessage, chat_macros[c], sizeof(lastmessage));
            st_plr->message = lastmessage;
            eatkey = true;
 }
 else
 {
            c = ev->data2;

     eatkey = HUlib_keyInIText(&w_chat, c);
     if (eatkey)
     {

  HU_queueChatChar(c);



     }
     if (c == 13)
     {
  chat_on = false;
                if (w_chat.l.len)
                {
                    M_StringCopy(lastmessage, w_chat.l.l, sizeof(lastmessage));
                    st_plr->message = lastmessage;
                }
     }
     else if (c == 27)
  chat_on = false;
 }
    }

    return eatkey;

}
char *sprnames[] = {
    "TROO","SHTG","PUNG","PISG","PISF","SHTF","SHT2","CHGG","CHGF","MISG",
    "MISF","SAWG","PLSG","PLSF","BFGG","BFGF","BLUD","PUFF","BAL1","BAL2",
    "PLSS","PLSE","MISL","BFS1","BFE1","BFE2","TFOG","IFOG","PLAY","POSS",
    "SPOS","VILE","FIRE","FATB","FBXP","SKEL","MANF","FATT","CPOS","SARG",
    "HEAD","BAL7","BOSS","BOS2","SKUL","SPID","BSPI","APLS","APBX","CYBR",
    "PAIN","SSWV","KEEN","BBRN","BOSF","ARM1","ARM2","BAR1","BEXP","FCAN",
    "BON1","BON2","BKEY","RKEY","YKEY","BSKU","RSKU","YSKU","STIM","MEDI",
    "SOUL","PINV","PSTR","PINS","MEGA","SUIT","PMAP","PVIS","CLIP","AMMO",
    "ROCK","BROK","CELL","CELP","SHEL","SBOX","BPAK","BFUG","MGUN","CSAW",
    "LAUN","PLAS","SHOT","SGN2","COLU","SMT2","GOR1","POL2","POL5","POL4",
    "POL3","POL1","POL6","GOR2","GOR3","GOR4","GOR5","SMIT","COL1","COL2",
    "COL3","COL4","CAND","CBRA","COL6","TRE1","TRE2","ELEC","CEYE","FSKU",
    "COL5","TBLU","TGRN","TRED","SMBT","SMGT","SMRT","HDB1","HDB2","HDB3",
    "HDB4","HDB5","HDB6","POB1","POB2","BRS1","TLMP","TLP2", ((void*)0)
};



void A_Light0();
void A_WeaponReady();
void A_Lower();
void A_Raise();
void A_Punch();
void A_ReFire();
void A_FirePistol();
void A_Light1();
void A_FireShotgun();
void A_Light2();
void A_FireShotgun2();
void A_CheckReload();
void A_OpenShotgun2();
void A_LoadShotgun2();
void A_CloseShotgun2();
void A_FireCGun();
void A_GunFlash();
void A_FireMissile();
void A_Saw();
void A_FirePlasma();
void A_BFGsound();
void A_FireBFG();
void A_BFGSpray();
void A_Explode();
void A_Pain();
void A_PlayerScream();
void A_Fall();
void A_XScream();
void A_Look();
void A_Chase();
void A_FaceTarget();
void A_PosAttack();
void A_Scream();
void A_SPosAttack();
void A_VileChase();
void A_VileStart();
void A_VileTarget();
void A_VileAttack();
void A_StartFire();
void A_Fire();
void A_FireCrackle();
void A_Tracer();
void A_SkelWhoosh();
void A_SkelFist();
void A_SkelMissile();
void A_FatRaise();
void A_FatAttack1();
void A_FatAttack2();
void A_FatAttack3();
void A_BossDeath();
void A_CPosAttack();
void A_CPosRefire();
void A_TroopAttack();
void A_SargAttack();
void A_HeadAttack();
void A_BruisAttack();
void A_SkullAttack();
void A_Metal();
void A_SpidRefire();
void A_BabyMetal();
void A_BspiAttack();
void A_Hoof();
void A_CyberAttack();
void A_PainAttack();
void A_PainDie();
void A_KeenDie();
void A_BrainPain();
void A_BrainScream();
void A_BrainDie();
void A_BrainAwake();
void A_BrainSpit();
void A_SpawnSound();
void A_SpawnFly();
void A_BrainExplode();


state_t states[NUMSTATES] = {
    {SPR_TROO,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SHTG,4,0,{A_Light0},S_NULL,0,0},
    {SPR_PUNG,0,1,{A_WeaponReady},S_PUNCH,0,0},
    {SPR_PUNG,0,1,{A_Lower},S_PUNCHDOWN,0,0},
    {SPR_PUNG,0,1,{A_Raise},S_PUNCHUP,0,0},
    {SPR_PUNG,1,4,{((void*)0)},S_PUNCH2,0,0},
    {SPR_PUNG,2,4,{A_Punch},S_PUNCH3,0,0},
    {SPR_PUNG,3,5,{((void*)0)},S_PUNCH4,0,0},
    {SPR_PUNG,2,4,{((void*)0)},S_PUNCH5,0,0},
    {SPR_PUNG,1,5,{A_ReFire},S_PUNCH,0,0},
    {SPR_PISG,0,1,{A_WeaponReady},S_PISTOL,0,0},
    {SPR_PISG,0,1,{A_Lower},S_PISTOLDOWN,0,0},
    {SPR_PISG,0,1,{A_Raise},S_PISTOLUP,0,0},
    {SPR_PISG,0,4,{((void*)0)},S_PISTOL2,0,0},
    {SPR_PISG,1,6,{A_FirePistol},S_PISTOL3,0,0},
    {SPR_PISG,2,4,{((void*)0)},S_PISTOL4,0,0},
    {SPR_PISG,1,5,{A_ReFire},S_PISTOL,0,0},
    {SPR_PISF,32768,7,{A_Light1},S_LIGHTDONE,0,0},
    {SPR_SHTG,0,1,{A_WeaponReady},S_SGUN,0,0},
    {SPR_SHTG,0,1,{A_Lower},S_SGUNDOWN,0,0},
    {SPR_SHTG,0,1,{A_Raise},S_SGUNUP,0,0},
    {SPR_SHTG,0,3,{((void*)0)},S_SGUN2,0,0},
    {SPR_SHTG,0,7,{A_FireShotgun},S_SGUN3,0,0},
    {SPR_SHTG,1,5,{((void*)0)},S_SGUN4,0,0},
    {SPR_SHTG,2,5,{((void*)0)},S_SGUN5,0,0},
    {SPR_SHTG,3,4,{((void*)0)},S_SGUN6,0,0},
    {SPR_SHTG,2,5,{((void*)0)},S_SGUN7,0,0},
    {SPR_SHTG,1,5,{((void*)0)},S_SGUN8,0,0},
    {SPR_SHTG,0,3,{((void*)0)},S_SGUN9,0,0},
    {SPR_SHTG,0,7,{A_ReFire},S_SGUN,0,0},
    {SPR_SHTF,32768,4,{A_Light1},S_SGUNFLASH2,0,0},
    {SPR_SHTF,32769,3,{A_Light2},S_LIGHTDONE,0,0},
    {SPR_SHT2,0,1,{A_WeaponReady},S_DSGUN,0,0},
    {SPR_SHT2,0,1,{A_Lower},S_DSGUNDOWN,0,0},
    {SPR_SHT2,0,1,{A_Raise},S_DSGUNUP,0,0},
    {SPR_SHT2,0,3,{((void*)0)},S_DSGUN2,0,0},
    {SPR_SHT2,0,7,{A_FireShotgun2},S_DSGUN3,0,0},
    {SPR_SHT2,1,7,{((void*)0)},S_DSGUN4,0,0},
    {SPR_SHT2,2,7,{A_CheckReload},S_DSGUN5,0,0},
    {SPR_SHT2,3,7,{A_OpenShotgun2},S_DSGUN6,0,0},
    {SPR_SHT2,4,7,{((void*)0)},S_DSGUN7,0,0},
    {SPR_SHT2,5,7,{A_LoadShotgun2},S_DSGUN8,0,0},
    {SPR_SHT2,6,6,{((void*)0)},S_DSGUN9,0,0},
    {SPR_SHT2,7,6,{A_CloseShotgun2},S_DSGUN10,0,0},
    {SPR_SHT2,0,5,{A_ReFire},S_DSGUN,0,0},
    {SPR_SHT2,1,7,{((void*)0)},S_DSNR2,0,0},
    {SPR_SHT2,0,3,{((void*)0)},S_DSGUNDOWN,0,0},
    {SPR_SHT2,32776,5,{A_Light1},S_DSGUNFLASH2,0,0},
    {SPR_SHT2,32777,4,{A_Light2},S_LIGHTDONE,0,0},
    {SPR_CHGG,0,1,{A_WeaponReady},S_CHAIN,0,0},
    {SPR_CHGG,0,1,{A_Lower},S_CHAINDOWN,0,0},
    {SPR_CHGG,0,1,{A_Raise},S_CHAINUP,0,0},
    {SPR_CHGG,0,4,{A_FireCGun},S_CHAIN2,0,0},
    {SPR_CHGG,1,4,{A_FireCGun},S_CHAIN3,0,0},
    {SPR_CHGG,1,0,{A_ReFire},S_CHAIN,0,0},
    {SPR_CHGF,32768,5,{A_Light1},S_LIGHTDONE,0,0},
    {SPR_CHGF,32769,5,{A_Light2},S_LIGHTDONE,0,0},
    {SPR_MISG,0,1,{A_WeaponReady},S_MISSILE,0,0},
    {SPR_MISG,0,1,{A_Lower},S_MISSILEDOWN,0,0},
    {SPR_MISG,0,1,{A_Raise},S_MISSILEUP,0,0},
    {SPR_MISG,1,8,{A_GunFlash},S_MISSILE2,0,0},
    {SPR_MISG,1,12,{A_FireMissile},S_MISSILE3,0,0},
    {SPR_MISG,1,0,{A_ReFire},S_MISSILE,0,0},
    {SPR_MISF,32768,3,{A_Light1},S_MISSILEFLASH2,0,0},
    {SPR_MISF,32769,4,{((void*)0)},S_MISSILEFLASH3,0,0},
    {SPR_MISF,32770,4,{A_Light2},S_MISSILEFLASH4,0,0},
    {SPR_MISF,32771,4,{A_Light2},S_LIGHTDONE,0,0},
    {SPR_SAWG,2,4,{A_WeaponReady},S_SAWB,0,0},
    {SPR_SAWG,3,4,{A_WeaponReady},S_SAW,0,0},
    {SPR_SAWG,2,1,{A_Lower},S_SAWDOWN,0,0},
    {SPR_SAWG,2,1,{A_Raise},S_SAWUP,0,0},
    {SPR_SAWG,0,4,{A_Saw},S_SAW2,0,0},
    {SPR_SAWG,1,4,{A_Saw},S_SAW3,0,0},
    {SPR_SAWG,1,0,{A_ReFire},S_SAW,0,0},
    {SPR_PLSG,0,1,{A_WeaponReady},S_PLASMA,0,0},
    {SPR_PLSG,0,1,{A_Lower},S_PLASMADOWN,0,0},
    {SPR_PLSG,0,1,{A_Raise},S_PLASMAUP,0,0},
    {SPR_PLSG,0,3,{A_FirePlasma},S_PLASMA2,0,0},
    {SPR_PLSG,1,20,{A_ReFire},S_PLASMA,0,0},
    {SPR_PLSF,32768,4,{A_Light1},S_LIGHTDONE,0,0},
    {SPR_PLSF,32769,4,{A_Light1},S_LIGHTDONE,0,0},
    {SPR_BFGG,0,1,{A_WeaponReady},S_BFG,0,0},
    {SPR_BFGG,0,1,{A_Lower},S_BFGDOWN,0,0},
    {SPR_BFGG,0,1,{A_Raise},S_BFGUP,0,0},
    {SPR_BFGG,0,20,{A_BFGsound},S_BFG2,0,0},
    {SPR_BFGG,1,10,{A_GunFlash},S_BFG3,0,0},
    {SPR_BFGG,1,10,{A_FireBFG},S_BFG4,0,0},
    {SPR_BFGG,1,20,{A_ReFire},S_BFG,0,0},
    {SPR_BFGF,32768,11,{A_Light1},S_BFGFLASH2,0,0},
    {SPR_BFGF,32769,6,{A_Light2},S_LIGHTDONE,0,0},
    {SPR_BLUD,2,8,{((void*)0)},S_BLOOD2,0,0},
    {SPR_BLUD,1,8,{((void*)0)},S_BLOOD3,0,0},
    {SPR_BLUD,0,8,{((void*)0)},S_NULL,0,0},
    {SPR_PUFF,32768,4,{((void*)0)},S_PUFF2,0,0},
    {SPR_PUFF,1,4,{((void*)0)},S_PUFF3,0,0},
    {SPR_PUFF,2,4,{((void*)0)},S_PUFF4,0,0},
    {SPR_PUFF,3,4,{((void*)0)},S_NULL,0,0},
    {SPR_BAL1,32768,4,{((void*)0)},S_TBALL2,0,0},
    {SPR_BAL1,32769,4,{((void*)0)},S_TBALL1,0,0},
    {SPR_BAL1,32770,6,{((void*)0)},S_TBALLX2,0,0},
    {SPR_BAL1,32771,6,{((void*)0)},S_TBALLX3,0,0},
    {SPR_BAL1,32772,6,{((void*)0)},S_NULL,0,0},
    {SPR_BAL2,32768,4,{((void*)0)},S_RBALL2,0,0},
    {SPR_BAL2,32769,4,{((void*)0)},S_RBALL1,0,0},
    {SPR_BAL2,32770,6,{((void*)0)},S_RBALLX2,0,0},
    {SPR_BAL2,32771,6,{((void*)0)},S_RBALLX3,0,0},
    {SPR_BAL2,32772,6,{((void*)0)},S_NULL,0,0},
    {SPR_PLSS,32768,6,{((void*)0)},S_PLASBALL2,0,0},
    {SPR_PLSS,32769,6,{((void*)0)},S_PLASBALL,0,0},
    {SPR_PLSE,32768,4,{((void*)0)},S_PLASEXP2,0,0},
    {SPR_PLSE,32769,4,{((void*)0)},S_PLASEXP3,0,0},
    {SPR_PLSE,32770,4,{((void*)0)},S_PLASEXP4,0,0},
    {SPR_PLSE,32771,4,{((void*)0)},S_PLASEXP5,0,0},
    {SPR_PLSE,32772,4,{((void*)0)},S_NULL,0,0},
    {SPR_MISL,32768,1,{((void*)0)},S_ROCKET,0,0},
    {SPR_BFS1,32768,4,{((void*)0)},S_BFGSHOT2,0,0},
    {SPR_BFS1,32769,4,{((void*)0)},S_BFGSHOT,0,0},
    {SPR_BFE1,32768,8,{((void*)0)},S_BFGLAND2,0,0},
    {SPR_BFE1,32769,8,{((void*)0)},S_BFGLAND3,0,0},
    {SPR_BFE1,32770,8,{A_BFGSpray},S_BFGLAND4,0,0},
    {SPR_BFE1,32771,8,{((void*)0)},S_BFGLAND5,0,0},
    {SPR_BFE1,32772,8,{((void*)0)},S_BFGLAND6,0,0},
    {SPR_BFE1,32773,8,{((void*)0)},S_NULL,0,0},
    {SPR_BFE2,32768,8,{((void*)0)},S_BFGEXP2,0,0},
    {SPR_BFE2,32769,8,{((void*)0)},S_BFGEXP3,0,0},
    {SPR_BFE2,32770,8,{((void*)0)},S_BFGEXP4,0,0},
    {SPR_BFE2,32771,8,{((void*)0)},S_NULL,0,0},
    {SPR_MISL,32769,8,{A_Explode},S_EXPLODE2,0,0},
    {SPR_MISL,32770,6,{((void*)0)},S_EXPLODE3,0,0},
    {SPR_MISL,32771,4,{((void*)0)},S_NULL,0,0},
    {SPR_TFOG,32768,6,{((void*)0)},S_TFOG01,0,0},
    {SPR_TFOG,32769,6,{((void*)0)},S_TFOG02,0,0},
    {SPR_TFOG,32768,6,{((void*)0)},S_TFOG2,0,0},
    {SPR_TFOG,32769,6,{((void*)0)},S_TFOG3,0,0},
    {SPR_TFOG,32770,6,{((void*)0)},S_TFOG4,0,0},
    {SPR_TFOG,32771,6,{((void*)0)},S_TFOG5,0,0},
    {SPR_TFOG,32772,6,{((void*)0)},S_TFOG6,0,0},
    {SPR_TFOG,32773,6,{((void*)0)},S_TFOG7,0,0},
    {SPR_TFOG,32774,6,{((void*)0)},S_TFOG8,0,0},
    {SPR_TFOG,32775,6,{((void*)0)},S_TFOG9,0,0},
    {SPR_TFOG,32776,6,{((void*)0)},S_TFOG10,0,0},
    {SPR_TFOG,32777,6,{((void*)0)},S_NULL,0,0},
    {SPR_IFOG,32768,6,{((void*)0)},S_IFOG01,0,0},
    {SPR_IFOG,32769,6,{((void*)0)},S_IFOG02,0,0},
    {SPR_IFOG,32768,6,{((void*)0)},S_IFOG2,0,0},
    {SPR_IFOG,32769,6,{((void*)0)},S_IFOG3,0,0},
    {SPR_IFOG,32770,6,{((void*)0)},S_IFOG4,0,0},
    {SPR_IFOG,32771,6,{((void*)0)},S_IFOG5,0,0},
    {SPR_IFOG,32772,6,{((void*)0)},S_NULL,0,0},
    {SPR_PLAY,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_PLAY,0,4,{((void*)0)},S_PLAY_RUN2,0,0},
    {SPR_PLAY,1,4,{((void*)0)},S_PLAY_RUN3,0,0},
    {SPR_PLAY,2,4,{((void*)0)},S_PLAY_RUN4,0,0},
    {SPR_PLAY,3,4,{((void*)0)},S_PLAY_RUN1,0,0},
    {SPR_PLAY,4,12,{((void*)0)},S_PLAY,0,0},
    {SPR_PLAY,32773,6,{((void*)0)},S_PLAY_ATK1,0,0},
    {SPR_PLAY,6,4,{((void*)0)},S_PLAY_PAIN2,0,0},
    {SPR_PLAY,6,4,{A_Pain},S_PLAY,0,0},
    {SPR_PLAY,7,10,{((void*)0)},S_PLAY_DIE2,0,0},
    {SPR_PLAY,8,10,{A_PlayerScream},S_PLAY_DIE3,0,0},
    {SPR_PLAY,9,10,{A_Fall},S_PLAY_DIE4,0,0},
    {SPR_PLAY,10,10,{((void*)0)},S_PLAY_DIE5,0,0},
    {SPR_PLAY,11,10,{((void*)0)},S_PLAY_DIE6,0,0},
    {SPR_PLAY,12,10,{((void*)0)},S_PLAY_DIE7,0,0},
    {SPR_PLAY,13,-1,{((void*)0)},S_NULL,0,0},
    {SPR_PLAY,14,5,{((void*)0)},S_PLAY_XDIE2,0,0},
    {SPR_PLAY,15,5,{A_XScream},S_PLAY_XDIE3,0,0},
    {SPR_PLAY,16,5,{A_Fall},S_PLAY_XDIE4,0,0},
    {SPR_PLAY,17,5,{((void*)0)},S_PLAY_XDIE5,0,0},
    {SPR_PLAY,18,5,{((void*)0)},S_PLAY_XDIE6,0,0},
    {SPR_PLAY,19,5,{((void*)0)},S_PLAY_XDIE7,0,0},
    {SPR_PLAY,20,5,{((void*)0)},S_PLAY_XDIE8,0,0},
    {SPR_PLAY,21,5,{((void*)0)},S_PLAY_XDIE9,0,0},
    {SPR_PLAY,22,-1,{((void*)0)},S_NULL,0,0},
    {SPR_POSS,0,10,{A_Look},S_POSS_STND2,0,0},
    {SPR_POSS,1,10,{A_Look},S_POSS_STND,0,0},
    {SPR_POSS,0,4,{A_Chase},S_POSS_RUN2,0,0},
    {SPR_POSS,0,4,{A_Chase},S_POSS_RUN3,0,0},
    {SPR_POSS,1,4,{A_Chase},S_POSS_RUN4,0,0},
    {SPR_POSS,1,4,{A_Chase},S_POSS_RUN5,0,0},
    {SPR_POSS,2,4,{A_Chase},S_POSS_RUN6,0,0},
    {SPR_POSS,2,4,{A_Chase},S_POSS_RUN7,0,0},
    {SPR_POSS,3,4,{A_Chase},S_POSS_RUN8,0,0},
    {SPR_POSS,3,4,{A_Chase},S_POSS_RUN1,0,0},
    {SPR_POSS,4,10,{A_FaceTarget},S_POSS_ATK2,0,0},
    {SPR_POSS,5,8,{A_PosAttack},S_POSS_ATK3,0,0},
    {SPR_POSS,4,8,{((void*)0)},S_POSS_RUN1,0,0},
    {SPR_POSS,6,3,{((void*)0)},S_POSS_PAIN2,0,0},
    {SPR_POSS,6,3,{A_Pain},S_POSS_RUN1,0,0},
    {SPR_POSS,7,5,{((void*)0)},S_POSS_DIE2,0,0},
    {SPR_POSS,8,5,{A_Scream},S_POSS_DIE3,0,0},
    {SPR_POSS,9,5,{A_Fall},S_POSS_DIE4,0,0},
    {SPR_POSS,10,5,{((void*)0)},S_POSS_DIE5,0,0},
    {SPR_POSS,11,-1,{((void*)0)},S_NULL,0,0},
    {SPR_POSS,12,5,{((void*)0)},S_POSS_XDIE2,0,0},
    {SPR_POSS,13,5,{A_XScream},S_POSS_XDIE3,0,0},
    {SPR_POSS,14,5,{A_Fall},S_POSS_XDIE4,0,0},
    {SPR_POSS,15,5,{((void*)0)},S_POSS_XDIE5,0,0},
    {SPR_POSS,16,5,{((void*)0)},S_POSS_XDIE6,0,0},
    {SPR_POSS,17,5,{((void*)0)},S_POSS_XDIE7,0,0},
    {SPR_POSS,18,5,{((void*)0)},S_POSS_XDIE8,0,0},
    {SPR_POSS,19,5,{((void*)0)},S_POSS_XDIE9,0,0},
    {SPR_POSS,20,-1,{((void*)0)},S_NULL,0,0},
    {SPR_POSS,10,5,{((void*)0)},S_POSS_RAISE2,0,0},
    {SPR_POSS,9,5,{((void*)0)},S_POSS_RAISE3,0,0},
    {SPR_POSS,8,5,{((void*)0)},S_POSS_RAISE4,0,0},
    {SPR_POSS,7,5,{((void*)0)},S_POSS_RUN1,0,0},
    {SPR_SPOS,0,10,{A_Look},S_SPOS_STND2,0,0},
    {SPR_SPOS,1,10,{A_Look},S_SPOS_STND,0,0},
    {SPR_SPOS,0,3,{A_Chase},S_SPOS_RUN2,0,0},
    {SPR_SPOS,0,3,{A_Chase},S_SPOS_RUN3,0,0},
    {SPR_SPOS,1,3,{A_Chase},S_SPOS_RUN4,0,0},
    {SPR_SPOS,1,3,{A_Chase},S_SPOS_RUN5,0,0},
    {SPR_SPOS,2,3,{A_Chase},S_SPOS_RUN6,0,0},
    {SPR_SPOS,2,3,{A_Chase},S_SPOS_RUN7,0,0},
    {SPR_SPOS,3,3,{A_Chase},S_SPOS_RUN8,0,0},
    {SPR_SPOS,3,3,{A_Chase},S_SPOS_RUN1,0,0},
    {SPR_SPOS,4,10,{A_FaceTarget},S_SPOS_ATK2,0,0},
    {SPR_SPOS,32773,10,{A_SPosAttack},S_SPOS_ATK3,0,0},
    {SPR_SPOS,4,10,{((void*)0)},S_SPOS_RUN1,0,0},
    {SPR_SPOS,6,3,{((void*)0)},S_SPOS_PAIN2,0,0},
    {SPR_SPOS,6,3,{A_Pain},S_SPOS_RUN1,0,0},
    {SPR_SPOS,7,5,{((void*)0)},S_SPOS_DIE2,0,0},
    {SPR_SPOS,8,5,{A_Scream},S_SPOS_DIE3,0,0},
    {SPR_SPOS,9,5,{A_Fall},S_SPOS_DIE4,0,0},
    {SPR_SPOS,10,5,{((void*)0)},S_SPOS_DIE5,0,0},
    {SPR_SPOS,11,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SPOS,12,5,{((void*)0)},S_SPOS_XDIE2,0,0},
    {SPR_SPOS,13,5,{A_XScream},S_SPOS_XDIE3,0,0},
    {SPR_SPOS,14,5,{A_Fall},S_SPOS_XDIE4,0,0},
    {SPR_SPOS,15,5,{((void*)0)},S_SPOS_XDIE5,0,0},
    {SPR_SPOS,16,5,{((void*)0)},S_SPOS_XDIE6,0,0},
    {SPR_SPOS,17,5,{((void*)0)},S_SPOS_XDIE7,0,0},
    {SPR_SPOS,18,5,{((void*)0)},S_SPOS_XDIE8,0,0},
    {SPR_SPOS,19,5,{((void*)0)},S_SPOS_XDIE9,0,0},
    {SPR_SPOS,20,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SPOS,11,5,{((void*)0)},S_SPOS_RAISE2,0,0},
    {SPR_SPOS,10,5,{((void*)0)},S_SPOS_RAISE3,0,0},
    {SPR_SPOS,9,5,{((void*)0)},S_SPOS_RAISE4,0,0},
    {SPR_SPOS,8,5,{((void*)0)},S_SPOS_RAISE5,0,0},
    {SPR_SPOS,7,5,{((void*)0)},S_SPOS_RUN1,0,0},
    {SPR_VILE,0,10,{A_Look},S_VILE_STND2,0,0},
    {SPR_VILE,1,10,{A_Look},S_VILE_STND,0,0},
    {SPR_VILE,0,2,{A_VileChase},S_VILE_RUN2,0,0},
    {SPR_VILE,0,2,{A_VileChase},S_VILE_RUN3,0,0},
    {SPR_VILE,1,2,{A_VileChase},S_VILE_RUN4,0,0},
    {SPR_VILE,1,2,{A_VileChase},S_VILE_RUN5,0,0},
    {SPR_VILE,2,2,{A_VileChase},S_VILE_RUN6,0,0},
    {SPR_VILE,2,2,{A_VileChase},S_VILE_RUN7,0,0},
    {SPR_VILE,3,2,{A_VileChase},S_VILE_RUN8,0,0},
    {SPR_VILE,3,2,{A_VileChase},S_VILE_RUN9,0,0},
    {SPR_VILE,4,2,{A_VileChase},S_VILE_RUN10,0,0},
    {SPR_VILE,4,2,{A_VileChase},S_VILE_RUN11,0,0},
    {SPR_VILE,5,2,{A_VileChase},S_VILE_RUN12,0,0},
    {SPR_VILE,5,2,{A_VileChase},S_VILE_RUN1,0,0},
    {SPR_VILE,32774,0,{A_VileStart},S_VILE_ATK2,0,0},
    {SPR_VILE,32774,10,{A_FaceTarget},S_VILE_ATK3,0,0},
    {SPR_VILE,32775,8,{A_VileTarget},S_VILE_ATK4,0,0},
    {SPR_VILE,32776,8,{A_FaceTarget},S_VILE_ATK5,0,0},
    {SPR_VILE,32777,8,{A_FaceTarget},S_VILE_ATK6,0,0},
    {SPR_VILE,32778,8,{A_FaceTarget},S_VILE_ATK7,0,0},
    {SPR_VILE,32779,8,{A_FaceTarget},S_VILE_ATK8,0,0},
    {SPR_VILE,32780,8,{A_FaceTarget},S_VILE_ATK9,0,0},
    {SPR_VILE,32781,8,{A_FaceTarget},S_VILE_ATK10,0,0},
    {SPR_VILE,32782,8,{A_VileAttack},S_VILE_ATK11,0,0},
    {SPR_VILE,32783,20,{((void*)0)},S_VILE_RUN1,0,0},
    {SPR_VILE,32794,10,{((void*)0)},S_VILE_HEAL2,0,0},
    {SPR_VILE,32795,10,{((void*)0)},S_VILE_HEAL3,0,0},
    {SPR_VILE,32796,10,{((void*)0)},S_VILE_RUN1,0,0},
    {SPR_VILE,16,5,{((void*)0)},S_VILE_PAIN2,0,0},
    {SPR_VILE,16,5,{A_Pain},S_VILE_RUN1,0,0},
    {SPR_VILE,16,7,{((void*)0)},S_VILE_DIE2,0,0},
    {SPR_VILE,17,7,{A_Scream},S_VILE_DIE3,0,0},
    {SPR_VILE,18,7,{A_Fall},S_VILE_DIE4,0,0},
    {SPR_VILE,19,7,{((void*)0)},S_VILE_DIE5,0,0},
    {SPR_VILE,20,7,{((void*)0)},S_VILE_DIE6,0,0},
    {SPR_VILE,21,7,{((void*)0)},S_VILE_DIE7,0,0},
    {SPR_VILE,22,7,{((void*)0)},S_VILE_DIE8,0,0},
    {SPR_VILE,23,5,{((void*)0)},S_VILE_DIE9,0,0},
    {SPR_VILE,24,5,{((void*)0)},S_VILE_DIE10,0,0},
    {SPR_VILE,25,-1,{((void*)0)},S_NULL,0,0},
    {SPR_FIRE,32768,2,{A_StartFire},S_FIRE2,0,0},
    {SPR_FIRE,32769,2,{A_Fire},S_FIRE3,0,0},
    {SPR_FIRE,32768,2,{A_Fire},S_FIRE4,0,0},
    {SPR_FIRE,32769,2,{A_Fire},S_FIRE5,0,0},
    {SPR_FIRE,32770,2,{A_FireCrackle},S_FIRE6,0,0},
    {SPR_FIRE,32769,2,{A_Fire},S_FIRE7,0,0},
    {SPR_FIRE,32770,2,{A_Fire},S_FIRE8,0,0},
    {SPR_FIRE,32769,2,{A_Fire},S_FIRE9,0,0},
    {SPR_FIRE,32770,2,{A_Fire},S_FIRE10,0,0},
    {SPR_FIRE,32771,2,{A_Fire},S_FIRE11,0,0},
    {SPR_FIRE,32770,2,{A_Fire},S_FIRE12,0,0},
    {SPR_FIRE,32771,2,{A_Fire},S_FIRE13,0,0},
    {SPR_FIRE,32770,2,{A_Fire},S_FIRE14,0,0},
    {SPR_FIRE,32771,2,{A_Fire},S_FIRE15,0,0},
    {SPR_FIRE,32772,2,{A_Fire},S_FIRE16,0,0},
    {SPR_FIRE,32771,2,{A_Fire},S_FIRE17,0,0},
    {SPR_FIRE,32772,2,{A_Fire},S_FIRE18,0,0},
    {SPR_FIRE,32771,2,{A_Fire},S_FIRE19,0,0},
    {SPR_FIRE,32772,2,{A_FireCrackle},S_FIRE20,0,0},
    {SPR_FIRE,32773,2,{A_Fire},S_FIRE21,0,0},
    {SPR_FIRE,32772,2,{A_Fire},S_FIRE22,0,0},
    {SPR_FIRE,32773,2,{A_Fire},S_FIRE23,0,0},
    {SPR_FIRE,32772,2,{A_Fire},S_FIRE24,0,0},
    {SPR_FIRE,32773,2,{A_Fire},S_FIRE25,0,0},
    {SPR_FIRE,32774,2,{A_Fire},S_FIRE26,0,0},
    {SPR_FIRE,32775,2,{A_Fire},S_FIRE27,0,0},
    {SPR_FIRE,32774,2,{A_Fire},S_FIRE28,0,0},
    {SPR_FIRE,32775,2,{A_Fire},S_FIRE29,0,0},
    {SPR_FIRE,32774,2,{A_Fire},S_FIRE30,0,0},
    {SPR_FIRE,32775,2,{A_Fire},S_NULL,0,0},
    {SPR_PUFF,1,4,{((void*)0)},S_SMOKE2,0,0},
    {SPR_PUFF,2,4,{((void*)0)},S_SMOKE3,0,0},
    {SPR_PUFF,1,4,{((void*)0)},S_SMOKE4,0,0},
    {SPR_PUFF,2,4,{((void*)0)},S_SMOKE5,0,0},
    {SPR_PUFF,3,4,{((void*)0)},S_NULL,0,0},
    {SPR_FATB,32768,2,{A_Tracer},S_TRACER2,0,0},
    {SPR_FATB,32769,2,{A_Tracer},S_TRACER,0,0},
    {SPR_FBXP,32768,8,{((void*)0)},S_TRACEEXP2,0,0},
    {SPR_FBXP,32769,6,{((void*)0)},S_TRACEEXP3,0,0},
    {SPR_FBXP,32770,4,{((void*)0)},S_NULL,0,0},
    {SPR_SKEL,0,10,{A_Look},S_SKEL_STND2,0,0},
    {SPR_SKEL,1,10,{A_Look},S_SKEL_STND,0,0},
    {SPR_SKEL,0,2,{A_Chase},S_SKEL_RUN2,0,0},
    {SPR_SKEL,0,2,{A_Chase},S_SKEL_RUN3,0,0},
    {SPR_SKEL,1,2,{A_Chase},S_SKEL_RUN4,0,0},
    {SPR_SKEL,1,2,{A_Chase},S_SKEL_RUN5,0,0},
    {SPR_SKEL,2,2,{A_Chase},S_SKEL_RUN6,0,0},
    {SPR_SKEL,2,2,{A_Chase},S_SKEL_RUN7,0,0},
    {SPR_SKEL,3,2,{A_Chase},S_SKEL_RUN8,0,0},
    {SPR_SKEL,3,2,{A_Chase},S_SKEL_RUN9,0,0},
    {SPR_SKEL,4,2,{A_Chase},S_SKEL_RUN10,0,0},
    {SPR_SKEL,4,2,{A_Chase},S_SKEL_RUN11,0,0},
    {SPR_SKEL,5,2,{A_Chase},S_SKEL_RUN12,0,0},
    {SPR_SKEL,5,2,{A_Chase},S_SKEL_RUN1,0,0},
    {SPR_SKEL,6,0,{A_FaceTarget},S_SKEL_FIST2,0,0},
    {SPR_SKEL,6,6,{A_SkelWhoosh},S_SKEL_FIST3,0,0},
    {SPR_SKEL,7,6,{A_FaceTarget},S_SKEL_FIST4,0,0},
    {SPR_SKEL,8,6,{A_SkelFist},S_SKEL_RUN1,0,0},
    {SPR_SKEL,32777,0,{A_FaceTarget},S_SKEL_MISS2,0,0},
    {SPR_SKEL,32777,10,{A_FaceTarget},S_SKEL_MISS3,0,0},
    {SPR_SKEL,10,10,{A_SkelMissile},S_SKEL_MISS4,0,0},
    {SPR_SKEL,10,10,{A_FaceTarget},S_SKEL_RUN1,0,0},
    {SPR_SKEL,11,5,{((void*)0)},S_SKEL_PAIN2,0,0},
    {SPR_SKEL,11,5,{A_Pain},S_SKEL_RUN1,0,0},
    {SPR_SKEL,11,7,{((void*)0)},S_SKEL_DIE2,0,0},
    {SPR_SKEL,12,7,{((void*)0)},S_SKEL_DIE3,0,0},
    {SPR_SKEL,13,7,{A_Scream},S_SKEL_DIE4,0,0},
    {SPR_SKEL,14,7,{A_Fall},S_SKEL_DIE5,0,0},
    {SPR_SKEL,15,7,{((void*)0)},S_SKEL_DIE6,0,0},
    {SPR_SKEL,16,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SKEL,16,5,{((void*)0)},S_SKEL_RAISE2,0,0},
    {SPR_SKEL,15,5,{((void*)0)},S_SKEL_RAISE3,0,0},
    {SPR_SKEL,14,5,{((void*)0)},S_SKEL_RAISE4,0,0},
    {SPR_SKEL,13,5,{((void*)0)},S_SKEL_RAISE5,0,0},
    {SPR_SKEL,12,5,{((void*)0)},S_SKEL_RAISE6,0,0},
    {SPR_SKEL,11,5,{((void*)0)},S_SKEL_RUN1,0,0},
    {SPR_MANF,32768,4,{((void*)0)},S_FATSHOT2,0,0},
    {SPR_MANF,32769,4,{((void*)0)},S_FATSHOT1,0,0},
    {SPR_MISL,32769,8,{((void*)0)},S_FATSHOTX2,0,0},
    {SPR_MISL,32770,6,{((void*)0)},S_FATSHOTX3,0,0},
    {SPR_MISL,32771,4,{((void*)0)},S_NULL,0,0},
    {SPR_FATT,0,15,{A_Look},S_FATT_STND2,0,0},
    {SPR_FATT,1,15,{A_Look},S_FATT_STND,0,0},
    {SPR_FATT,0,4,{A_Chase},S_FATT_RUN2,0,0},
    {SPR_FATT,0,4,{A_Chase},S_FATT_RUN3,0,0},
    {SPR_FATT,1,4,{A_Chase},S_FATT_RUN4,0,0},
    {SPR_FATT,1,4,{A_Chase},S_FATT_RUN5,0,0},
    {SPR_FATT,2,4,{A_Chase},S_FATT_RUN6,0,0},
    {SPR_FATT,2,4,{A_Chase},S_FATT_RUN7,0,0},
    {SPR_FATT,3,4,{A_Chase},S_FATT_RUN8,0,0},
    {SPR_FATT,3,4,{A_Chase},S_FATT_RUN9,0,0},
    {SPR_FATT,4,4,{A_Chase},S_FATT_RUN10,0,0},
    {SPR_FATT,4,4,{A_Chase},S_FATT_RUN11,0,0},
    {SPR_FATT,5,4,{A_Chase},S_FATT_RUN12,0,0},
    {SPR_FATT,5,4,{A_Chase},S_FATT_RUN1,0,0},
    {SPR_FATT,6,20,{A_FatRaise},S_FATT_ATK2,0,0},
    {SPR_FATT,32775,10,{A_FatAttack1},S_FATT_ATK3,0,0},
    {SPR_FATT,8,5,{A_FaceTarget},S_FATT_ATK4,0,0},
    {SPR_FATT,6,5,{A_FaceTarget},S_FATT_ATK5,0,0},
    {SPR_FATT,32775,10,{A_FatAttack2},S_FATT_ATK6,0,0},
    {SPR_FATT,8,5,{A_FaceTarget},S_FATT_ATK7,0,0},
    {SPR_FATT,6,5,{A_FaceTarget},S_FATT_ATK8,0,0},
    {SPR_FATT,32775,10,{A_FatAttack3},S_FATT_ATK9,0,0},
    {SPR_FATT,8,5,{A_FaceTarget},S_FATT_ATK10,0,0},
    {SPR_FATT,6,5,{A_FaceTarget},S_FATT_RUN1,0,0},
    {SPR_FATT,9,3,{((void*)0)},S_FATT_PAIN2,0,0},
    {SPR_FATT,9,3,{A_Pain},S_FATT_RUN1,0,0},
    {SPR_FATT,10,6,{((void*)0)},S_FATT_DIE2,0,0},
    {SPR_FATT,11,6,{A_Scream},S_FATT_DIE3,0,0},
    {SPR_FATT,12,6,{A_Fall},S_FATT_DIE4,0,0},
    {SPR_FATT,13,6,{((void*)0)},S_FATT_DIE5,0,0},
    {SPR_FATT,14,6,{((void*)0)},S_FATT_DIE6,0,0},
    {SPR_FATT,15,6,{((void*)0)},S_FATT_DIE7,0,0},
    {SPR_FATT,16,6,{((void*)0)},S_FATT_DIE8,0,0},
    {SPR_FATT,17,6,{((void*)0)},S_FATT_DIE9,0,0},
    {SPR_FATT,18,6,{((void*)0)},S_FATT_DIE10,0,0},
    {SPR_FATT,19,-1,{A_BossDeath},S_NULL,0,0},
    {SPR_FATT,17,5,{((void*)0)},S_FATT_RAISE2,0,0},
    {SPR_FATT,16,5,{((void*)0)},S_FATT_RAISE3,0,0},
    {SPR_FATT,15,5,{((void*)0)},S_FATT_RAISE4,0,0},
    {SPR_FATT,14,5,{((void*)0)},S_FATT_RAISE5,0,0},
    {SPR_FATT,13,5,{((void*)0)},S_FATT_RAISE6,0,0},
    {SPR_FATT,12,5,{((void*)0)},S_FATT_RAISE7,0,0},
    {SPR_FATT,11,5,{((void*)0)},S_FATT_RAISE8,0,0},
    {SPR_FATT,10,5,{((void*)0)},S_FATT_RUN1,0,0},
    {SPR_CPOS,0,10,{A_Look},S_CPOS_STND2,0,0},
    {SPR_CPOS,1,10,{A_Look},S_CPOS_STND,0,0},
    {SPR_CPOS,0,3,{A_Chase},S_CPOS_RUN2,0,0},
    {SPR_CPOS,0,3,{A_Chase},S_CPOS_RUN3,0,0},
    {SPR_CPOS,1,3,{A_Chase},S_CPOS_RUN4,0,0},
    {SPR_CPOS,1,3,{A_Chase},S_CPOS_RUN5,0,0},
    {SPR_CPOS,2,3,{A_Chase},S_CPOS_RUN6,0,0},
    {SPR_CPOS,2,3,{A_Chase},S_CPOS_RUN7,0,0},
    {SPR_CPOS,3,3,{A_Chase},S_CPOS_RUN8,0,0},
    {SPR_CPOS,3,3,{A_Chase},S_CPOS_RUN1,0,0},
    {SPR_CPOS,4,10,{A_FaceTarget},S_CPOS_ATK2,0,0},
    {SPR_CPOS,32773,4,{A_CPosAttack},S_CPOS_ATK3,0,0},
    {SPR_CPOS,32772,4,{A_CPosAttack},S_CPOS_ATK4,0,0},
    {SPR_CPOS,5,1,{A_CPosRefire},S_CPOS_ATK2,0,0},
    {SPR_CPOS,6,3,{((void*)0)},S_CPOS_PAIN2,0,0},
    {SPR_CPOS,6,3,{A_Pain},S_CPOS_RUN1,0,0},
    {SPR_CPOS,7,5,{((void*)0)},S_CPOS_DIE2,0,0},
    {SPR_CPOS,8,5,{A_Scream},S_CPOS_DIE3,0,0},
    {SPR_CPOS,9,5,{A_Fall},S_CPOS_DIE4,0,0},
    {SPR_CPOS,10,5,{((void*)0)},S_CPOS_DIE5,0,0},
    {SPR_CPOS,11,5,{((void*)0)},S_CPOS_DIE6,0,0},
    {SPR_CPOS,12,5,{((void*)0)},S_CPOS_DIE7,0,0},
    {SPR_CPOS,13,-1,{((void*)0)},S_NULL,0,0},
    {SPR_CPOS,14,5,{((void*)0)},S_CPOS_XDIE2,0,0},
    {SPR_CPOS,15,5,{A_XScream},S_CPOS_XDIE3,0,0},
    {SPR_CPOS,16,5,{A_Fall},S_CPOS_XDIE4,0,0},
    {SPR_CPOS,17,5,{((void*)0)},S_CPOS_XDIE5,0,0},
    {SPR_CPOS,18,5,{((void*)0)},S_CPOS_XDIE6,0,0},
    {SPR_CPOS,19,-1,{((void*)0)},S_NULL,0,0},
    {SPR_CPOS,13,5,{((void*)0)},S_CPOS_RAISE2,0,0},
    {SPR_CPOS,12,5,{((void*)0)},S_CPOS_RAISE3,0,0},
    {SPR_CPOS,11,5,{((void*)0)},S_CPOS_RAISE4,0,0},
    {SPR_CPOS,10,5,{((void*)0)},S_CPOS_RAISE5,0,0},
    {SPR_CPOS,9,5,{((void*)0)},S_CPOS_RAISE6,0,0},
    {SPR_CPOS,8,5,{((void*)0)},S_CPOS_RAISE7,0,0},
    {SPR_CPOS,7,5,{((void*)0)},S_CPOS_RUN1,0,0},
    {SPR_TROO,0,10,{A_Look},S_TROO_STND2,0,0},
    {SPR_TROO,1,10,{A_Look},S_TROO_STND,0,0},
    {SPR_TROO,0,3,{A_Chase},S_TROO_RUN2,0,0},
    {SPR_TROO,0,3,{A_Chase},S_TROO_RUN3,0,0},
    {SPR_TROO,1,3,{A_Chase},S_TROO_RUN4,0,0},
    {SPR_TROO,1,3,{A_Chase},S_TROO_RUN5,0,0},
    {SPR_TROO,2,3,{A_Chase},S_TROO_RUN6,0,0},
    {SPR_TROO,2,3,{A_Chase},S_TROO_RUN7,0,0},
    {SPR_TROO,3,3,{A_Chase},S_TROO_RUN8,0,0},
    {SPR_TROO,3,3,{A_Chase},S_TROO_RUN1,0,0},
    {SPR_TROO,4,8,{A_FaceTarget},S_TROO_ATK2,0,0},
    {SPR_TROO,5,8,{A_FaceTarget},S_TROO_ATK3,0,0},
    {SPR_TROO,6,6,{A_TroopAttack},S_TROO_RUN1,0,0},
    {SPR_TROO,7,2,{((void*)0)},S_TROO_PAIN2,0,0},
    {SPR_TROO,7,2,{A_Pain},S_TROO_RUN1,0,0},
    {SPR_TROO,8,8,{((void*)0)},S_TROO_DIE2,0,0},
    {SPR_TROO,9,8,{A_Scream},S_TROO_DIE3,0,0},
    {SPR_TROO,10,6,{((void*)0)},S_TROO_DIE4,0,0},
    {SPR_TROO,11,6,{A_Fall},S_TROO_DIE5,0,0},
    {SPR_TROO,12,-1,{((void*)0)},S_NULL,0,0},
    {SPR_TROO,13,5,{((void*)0)},S_TROO_XDIE2,0,0},
    {SPR_TROO,14,5,{A_XScream},S_TROO_XDIE3,0,0},
    {SPR_TROO,15,5,{((void*)0)},S_TROO_XDIE4,0,0},
    {SPR_TROO,16,5,{A_Fall},S_TROO_XDIE5,0,0},
    {SPR_TROO,17,5,{((void*)0)},S_TROO_XDIE6,0,0},
    {SPR_TROO,18,5,{((void*)0)},S_TROO_XDIE7,0,0},
    {SPR_TROO,19,5,{((void*)0)},S_TROO_XDIE8,0,0},
    {SPR_TROO,20,-1,{((void*)0)},S_NULL,0,0},
    {SPR_TROO,12,8,{((void*)0)},S_TROO_RAISE2,0,0},
    {SPR_TROO,11,8,{((void*)0)},S_TROO_RAISE3,0,0},
    {SPR_TROO,10,6,{((void*)0)},S_TROO_RAISE4,0,0},
    {SPR_TROO,9,6,{((void*)0)},S_TROO_RAISE5,0,0},
    {SPR_TROO,8,6,{((void*)0)},S_TROO_RUN1,0,0},
    {SPR_SARG,0,10,{A_Look},S_SARG_STND2,0,0},
    {SPR_SARG,1,10,{A_Look},S_SARG_STND,0,0},
    {SPR_SARG,0,2,{A_Chase},S_SARG_RUN2,0,0},
    {SPR_SARG,0,2,{A_Chase},S_SARG_RUN3,0,0},
    {SPR_SARG,1,2,{A_Chase},S_SARG_RUN4,0,0},
    {SPR_SARG,1,2,{A_Chase},S_SARG_RUN5,0,0},
    {SPR_SARG,2,2,{A_Chase},S_SARG_RUN6,0,0},
    {SPR_SARG,2,2,{A_Chase},S_SARG_RUN7,0,0},
    {SPR_SARG,3,2,{A_Chase},S_SARG_RUN8,0,0},
    {SPR_SARG,3,2,{A_Chase},S_SARG_RUN1,0,0},
    {SPR_SARG,4,8,{A_FaceTarget},S_SARG_ATK2,0,0},
    {SPR_SARG,5,8,{A_FaceTarget},S_SARG_ATK3,0,0},
    {SPR_SARG,6,8,{A_SargAttack},S_SARG_RUN1,0,0},
    {SPR_SARG,7,2,{((void*)0)},S_SARG_PAIN2,0,0},
    {SPR_SARG,7,2,{A_Pain},S_SARG_RUN1,0,0},
    {SPR_SARG,8,8,{((void*)0)},S_SARG_DIE2,0,0},
    {SPR_SARG,9,8,{A_Scream},S_SARG_DIE3,0,0},
    {SPR_SARG,10,4,{((void*)0)},S_SARG_DIE4,0,0},
    {SPR_SARG,11,4,{A_Fall},S_SARG_DIE5,0,0},
    {SPR_SARG,12,4,{((void*)0)},S_SARG_DIE6,0,0},
    {SPR_SARG,13,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SARG,13,5,{((void*)0)},S_SARG_RAISE2,0,0},
    {SPR_SARG,12,5,{((void*)0)},S_SARG_RAISE3,0,0},
    {SPR_SARG,11,5,{((void*)0)},S_SARG_RAISE4,0,0},
    {SPR_SARG,10,5,{((void*)0)},S_SARG_RAISE5,0,0},
    {SPR_SARG,9,5,{((void*)0)},S_SARG_RAISE6,0,0},
    {SPR_SARG,8,5,{((void*)0)},S_SARG_RUN1,0,0},
    {SPR_HEAD,0,10,{A_Look},S_HEAD_STND,0,0},
    {SPR_HEAD,0,3,{A_Chase},S_HEAD_RUN1,0,0},
    {SPR_HEAD,1,5,{A_FaceTarget},S_HEAD_ATK2,0,0},
    {SPR_HEAD,2,5,{A_FaceTarget},S_HEAD_ATK3,0,0},
    {SPR_HEAD,32771,5,{A_HeadAttack},S_HEAD_RUN1,0,0},
    {SPR_HEAD,4,3,{((void*)0)},S_HEAD_PAIN2,0,0},
    {SPR_HEAD,4,3,{A_Pain},S_HEAD_PAIN3,0,0},
    {SPR_HEAD,5,6,{((void*)0)},S_HEAD_RUN1,0,0},
    {SPR_HEAD,6,8,{((void*)0)},S_HEAD_DIE2,0,0},
    {SPR_HEAD,7,8,{A_Scream},S_HEAD_DIE3,0,0},
    {SPR_HEAD,8,8,{((void*)0)},S_HEAD_DIE4,0,0},
    {SPR_HEAD,9,8,{((void*)0)},S_HEAD_DIE5,0,0},
    {SPR_HEAD,10,8,{A_Fall},S_HEAD_DIE6,0,0},
    {SPR_HEAD,11,-1,{((void*)0)},S_NULL,0,0},
    {SPR_HEAD,11,8,{((void*)0)},S_HEAD_RAISE2,0,0},
    {SPR_HEAD,10,8,{((void*)0)},S_HEAD_RAISE3,0,0},
    {SPR_HEAD,9,8,{((void*)0)},S_HEAD_RAISE4,0,0},
    {SPR_HEAD,8,8,{((void*)0)},S_HEAD_RAISE5,0,0},
    {SPR_HEAD,7,8,{((void*)0)},S_HEAD_RAISE6,0,0},
    {SPR_HEAD,6,8,{((void*)0)},S_HEAD_RUN1,0,0},
    {SPR_BAL7,32768,4,{((void*)0)},S_BRBALL2,0,0},
    {SPR_BAL7,32769,4,{((void*)0)},S_BRBALL1,0,0},
    {SPR_BAL7,32770,6,{((void*)0)},S_BRBALLX2,0,0},
    {SPR_BAL7,32771,6,{((void*)0)},S_BRBALLX3,0,0},
    {SPR_BAL7,32772,6,{((void*)0)},S_NULL,0,0},
    {SPR_BOSS,0,10,{A_Look},S_BOSS_STND2,0,0},
    {SPR_BOSS,1,10,{A_Look},S_BOSS_STND,0,0},
    {SPR_BOSS,0,3,{A_Chase},S_BOSS_RUN2,0,0},
    {SPR_BOSS,0,3,{A_Chase},S_BOSS_RUN3,0,0},
    {SPR_BOSS,1,3,{A_Chase},S_BOSS_RUN4,0,0},
    {SPR_BOSS,1,3,{A_Chase},S_BOSS_RUN5,0,0},
    {SPR_BOSS,2,3,{A_Chase},S_BOSS_RUN6,0,0},
    {SPR_BOSS,2,3,{A_Chase},S_BOSS_RUN7,0,0},
    {SPR_BOSS,3,3,{A_Chase},S_BOSS_RUN8,0,0},
    {SPR_BOSS,3,3,{A_Chase},S_BOSS_RUN1,0,0},
    {SPR_BOSS,4,8,{A_FaceTarget},S_BOSS_ATK2,0,0},
    {SPR_BOSS,5,8,{A_FaceTarget},S_BOSS_ATK3,0,0},
    {SPR_BOSS,6,8,{A_BruisAttack},S_BOSS_RUN1,0,0},
    {SPR_BOSS,7,2,{((void*)0)},S_BOSS_PAIN2,0,0},
    {SPR_BOSS,7,2,{A_Pain},S_BOSS_RUN1,0,0},
    {SPR_BOSS,8,8,{((void*)0)},S_BOSS_DIE2,0,0},
    {SPR_BOSS,9,8,{A_Scream},S_BOSS_DIE3,0,0},
    {SPR_BOSS,10,8,{((void*)0)},S_BOSS_DIE4,0,0},
    {SPR_BOSS,11,8,{A_Fall},S_BOSS_DIE5,0,0},
    {SPR_BOSS,12,8,{((void*)0)},S_BOSS_DIE6,0,0},
    {SPR_BOSS,13,8,{((void*)0)},S_BOSS_DIE7,0,0},
    {SPR_BOSS,14,-1,{A_BossDeath},S_NULL,0,0},
    {SPR_BOSS,14,8,{((void*)0)},S_BOSS_RAISE2,0,0},
    {SPR_BOSS,13,8,{((void*)0)},S_BOSS_RAISE3,0,0},
    {SPR_BOSS,12,8,{((void*)0)},S_BOSS_RAISE4,0,0},
    {SPR_BOSS,11,8,{((void*)0)},S_BOSS_RAISE5,0,0},
    {SPR_BOSS,10,8,{((void*)0)},S_BOSS_RAISE6,0,0},
    {SPR_BOSS,9,8,{((void*)0)},S_BOSS_RAISE7,0,0},
    {SPR_BOSS,8,8,{((void*)0)},S_BOSS_RUN1,0,0},
    {SPR_BOS2,0,10,{A_Look},S_BOS2_STND2,0,0},
    {SPR_BOS2,1,10,{A_Look},S_BOS2_STND,0,0},
    {SPR_BOS2,0,3,{A_Chase},S_BOS2_RUN2,0,0},
    {SPR_BOS2,0,3,{A_Chase},S_BOS2_RUN3,0,0},
    {SPR_BOS2,1,3,{A_Chase},S_BOS2_RUN4,0,0},
    {SPR_BOS2,1,3,{A_Chase},S_BOS2_RUN5,0,0},
    {SPR_BOS2,2,3,{A_Chase},S_BOS2_RUN6,0,0},
    {SPR_BOS2,2,3,{A_Chase},S_BOS2_RUN7,0,0},
    {SPR_BOS2,3,3,{A_Chase},S_BOS2_RUN8,0,0},
    {SPR_BOS2,3,3,{A_Chase},S_BOS2_RUN1,0,0},
    {SPR_BOS2,4,8,{A_FaceTarget},S_BOS2_ATK2,0,0},
    {SPR_BOS2,5,8,{A_FaceTarget},S_BOS2_ATK3,0,0},
    {SPR_BOS2,6,8,{A_BruisAttack},S_BOS2_RUN1,0,0},
    {SPR_BOS2,7,2,{((void*)0)},S_BOS2_PAIN2,0,0},
    {SPR_BOS2,7,2,{A_Pain},S_BOS2_RUN1,0,0},
    {SPR_BOS2,8,8,{((void*)0)},S_BOS2_DIE2,0,0},
    {SPR_BOS2,9,8,{A_Scream},S_BOS2_DIE3,0,0},
    {SPR_BOS2,10,8,{((void*)0)},S_BOS2_DIE4,0,0},
    {SPR_BOS2,11,8,{A_Fall},S_BOS2_DIE5,0,0},
    {SPR_BOS2,12,8,{((void*)0)},S_BOS2_DIE6,0,0},
    {SPR_BOS2,13,8,{((void*)0)},S_BOS2_DIE7,0,0},
    {SPR_BOS2,14,-1,{((void*)0)},S_NULL,0,0},
    {SPR_BOS2,14,8,{((void*)0)},S_BOS2_RAISE2,0,0},
    {SPR_BOS2,13,8,{((void*)0)},S_BOS2_RAISE3,0,0},
    {SPR_BOS2,12,8,{((void*)0)},S_BOS2_RAISE4,0,0},
    {SPR_BOS2,11,8,{((void*)0)},S_BOS2_RAISE5,0,0},
    {SPR_BOS2,10,8,{((void*)0)},S_BOS2_RAISE6,0,0},
    {SPR_BOS2,9,8,{((void*)0)},S_BOS2_RAISE7,0,0},
    {SPR_BOS2,8,8,{((void*)0)},S_BOS2_RUN1,0,0},
    {SPR_SKUL,32768,10,{A_Look},S_SKULL_STND2,0,0},
    {SPR_SKUL,32769,10,{A_Look},S_SKULL_STND,0,0},
    {SPR_SKUL,32768,6,{A_Chase},S_SKULL_RUN2,0,0},
    {SPR_SKUL,32769,6,{A_Chase},S_SKULL_RUN1,0,0},
    {SPR_SKUL,32770,10,{A_FaceTarget},S_SKULL_ATK2,0,0},
    {SPR_SKUL,32771,4,{A_SkullAttack},S_SKULL_ATK3,0,0},
    {SPR_SKUL,32770,4,{((void*)0)},S_SKULL_ATK4,0,0},
    {SPR_SKUL,32771,4,{((void*)0)},S_SKULL_ATK3,0,0},
    {SPR_SKUL,32772,3,{((void*)0)},S_SKULL_PAIN2,0,0},
    {SPR_SKUL,32772,3,{A_Pain},S_SKULL_RUN1,0,0},
    {SPR_SKUL,32773,6,{((void*)0)},S_SKULL_DIE2,0,0},
    {SPR_SKUL,32774,6,{A_Scream},S_SKULL_DIE3,0,0},
    {SPR_SKUL,32775,6,{((void*)0)},S_SKULL_DIE4,0,0},
    {SPR_SKUL,32776,6,{A_Fall},S_SKULL_DIE5,0,0},
    {SPR_SKUL,9,6,{((void*)0)},S_SKULL_DIE6,0,0},
    {SPR_SKUL,10,6,{((void*)0)},S_NULL,0,0},
    {SPR_SPID,0,10,{A_Look},S_SPID_STND2,0,0},
    {SPR_SPID,1,10,{A_Look},S_SPID_STND,0,0},
    {SPR_SPID,0,3,{A_Metal},S_SPID_RUN2,0,0},
    {SPR_SPID,0,3,{A_Chase},S_SPID_RUN3,0,0},
    {SPR_SPID,1,3,{A_Chase},S_SPID_RUN4,0,0},
    {SPR_SPID,1,3,{A_Chase},S_SPID_RUN5,0,0},
    {SPR_SPID,2,3,{A_Metal},S_SPID_RUN6,0,0},
    {SPR_SPID,2,3,{A_Chase},S_SPID_RUN7,0,0},
    {SPR_SPID,3,3,{A_Chase},S_SPID_RUN8,0,0},
    {SPR_SPID,3,3,{A_Chase},S_SPID_RUN9,0,0},
    {SPR_SPID,4,3,{A_Metal},S_SPID_RUN10,0,0},
    {SPR_SPID,4,3,{A_Chase},S_SPID_RUN11,0,0},
    {SPR_SPID,5,3,{A_Chase},S_SPID_RUN12,0,0},
    {SPR_SPID,5,3,{A_Chase},S_SPID_RUN1,0,0},
    {SPR_SPID,32768,20,{A_FaceTarget},S_SPID_ATK2,0,0},
    {SPR_SPID,32774,4,{A_SPosAttack},S_SPID_ATK3,0,0},
    {SPR_SPID,32775,4,{A_SPosAttack},S_SPID_ATK4,0,0},
    {SPR_SPID,32775,1,{A_SpidRefire},S_SPID_ATK2,0,0},
    {SPR_SPID,8,3,{((void*)0)},S_SPID_PAIN2,0,0},
    {SPR_SPID,8,3,{A_Pain},S_SPID_RUN1,0,0},
    {SPR_SPID,9,20,{A_Scream},S_SPID_DIE2,0,0},
    {SPR_SPID,10,10,{A_Fall},S_SPID_DIE3,0,0},
    {SPR_SPID,11,10,{((void*)0)},S_SPID_DIE4,0,0},
    {SPR_SPID,12,10,{((void*)0)},S_SPID_DIE5,0,0},
    {SPR_SPID,13,10,{((void*)0)},S_SPID_DIE6,0,0},
    {SPR_SPID,14,10,{((void*)0)},S_SPID_DIE7,0,0},
    {SPR_SPID,15,10,{((void*)0)},S_SPID_DIE8,0,0},
    {SPR_SPID,16,10,{((void*)0)},S_SPID_DIE9,0,0},
    {SPR_SPID,17,10,{((void*)0)},S_SPID_DIE10,0,0},
    {SPR_SPID,18,30,{((void*)0)},S_SPID_DIE11,0,0},
    {SPR_SPID,18,-1,{A_BossDeath},S_NULL,0,0},
    {SPR_BSPI,0,10,{A_Look},S_BSPI_STND2,0,0},
    {SPR_BSPI,1,10,{A_Look},S_BSPI_STND,0,0},
    {SPR_BSPI,0,20,{((void*)0)},S_BSPI_RUN1,0,0},
    {SPR_BSPI,0,3,{A_BabyMetal},S_BSPI_RUN2,0,0},
    {SPR_BSPI,0,3,{A_Chase},S_BSPI_RUN3,0,0},
    {SPR_BSPI,1,3,{A_Chase},S_BSPI_RUN4,0,0},
    {SPR_BSPI,1,3,{A_Chase},S_BSPI_RUN5,0,0},
    {SPR_BSPI,2,3,{A_Chase},S_BSPI_RUN6,0,0},
    {SPR_BSPI,2,3,{A_Chase},S_BSPI_RUN7,0,0},
    {SPR_BSPI,3,3,{A_BabyMetal},S_BSPI_RUN8,0,0},
    {SPR_BSPI,3,3,{A_Chase},S_BSPI_RUN9,0,0},
    {SPR_BSPI,4,3,{A_Chase},S_BSPI_RUN10,0,0},
    {SPR_BSPI,4,3,{A_Chase},S_BSPI_RUN11,0,0},
    {SPR_BSPI,5,3,{A_Chase},S_BSPI_RUN12,0,0},
    {SPR_BSPI,5,3,{A_Chase},S_BSPI_RUN1,0,0},
    {SPR_BSPI,32768,20,{A_FaceTarget},S_BSPI_ATK2,0,0},
    {SPR_BSPI,32774,4,{A_BspiAttack},S_BSPI_ATK3,0,0},
    {SPR_BSPI,32775,4,{((void*)0)},S_BSPI_ATK4,0,0},
    {SPR_BSPI,32775,1,{A_SpidRefire},S_BSPI_ATK2,0,0},
    {SPR_BSPI,8,3,{((void*)0)},S_BSPI_PAIN2,0,0},
    {SPR_BSPI,8,3,{A_Pain},S_BSPI_RUN1,0,0},
    {SPR_BSPI,9,20,{A_Scream},S_BSPI_DIE2,0,0},
    {SPR_BSPI,10,7,{A_Fall},S_BSPI_DIE3,0,0},
    {SPR_BSPI,11,7,{((void*)0)},S_BSPI_DIE4,0,0},
    {SPR_BSPI,12,7,{((void*)0)},S_BSPI_DIE5,0,0},
    {SPR_BSPI,13,7,{((void*)0)},S_BSPI_DIE6,0,0},
    {SPR_BSPI,14,7,{((void*)0)},S_BSPI_DIE7,0,0},
    {SPR_BSPI,15,-1,{A_BossDeath},S_NULL,0,0},
    {SPR_BSPI,15,5,{((void*)0)},S_BSPI_RAISE2,0,0},
    {SPR_BSPI,14,5,{((void*)0)},S_BSPI_RAISE3,0,0},
    {SPR_BSPI,13,5,{((void*)0)},S_BSPI_RAISE4,0,0},
    {SPR_BSPI,12,5,{((void*)0)},S_BSPI_RAISE5,0,0},
    {SPR_BSPI,11,5,{((void*)0)},S_BSPI_RAISE6,0,0},
    {SPR_BSPI,10,5,{((void*)0)},S_BSPI_RAISE7,0,0},
    {SPR_BSPI,9,5,{((void*)0)},S_BSPI_RUN1,0,0},
    {SPR_APLS,32768,5,{((void*)0)},S_ARACH_PLAZ2,0,0},
    {SPR_APLS,32769,5,{((void*)0)},S_ARACH_PLAZ,0,0},
    {SPR_APBX,32768,5,{((void*)0)},S_ARACH_PLEX2,0,0},
    {SPR_APBX,32769,5,{((void*)0)},S_ARACH_PLEX3,0,0},
    {SPR_APBX,32770,5,{((void*)0)},S_ARACH_PLEX4,0,0},
    {SPR_APBX,32771,5,{((void*)0)},S_ARACH_PLEX5,0,0},
    {SPR_APBX,32772,5,{((void*)0)},S_NULL,0,0},
    {SPR_CYBR,0,10,{A_Look},S_CYBER_STND2,0,0},
    {SPR_CYBR,1,10,{A_Look},S_CYBER_STND,0,0},
    {SPR_CYBR,0,3,{A_Hoof},S_CYBER_RUN2,0,0},
    {SPR_CYBR,0,3,{A_Chase},S_CYBER_RUN3,0,0},
    {SPR_CYBR,1,3,{A_Chase},S_CYBER_RUN4,0,0},
    {SPR_CYBR,1,3,{A_Chase},S_CYBER_RUN5,0,0},
    {SPR_CYBR,2,3,{A_Chase},S_CYBER_RUN6,0,0},
    {SPR_CYBR,2,3,{A_Chase},S_CYBER_RUN7,0,0},
    {SPR_CYBR,3,3,{A_Metal},S_CYBER_RUN8,0,0},
    {SPR_CYBR,3,3,{A_Chase},S_CYBER_RUN1,0,0},
    {SPR_CYBR,4,6,{A_FaceTarget},S_CYBER_ATK2,0,0},
    {SPR_CYBR,5,12,{A_CyberAttack},S_CYBER_ATK3,0,0},
    {SPR_CYBR,4,12,{A_FaceTarget},S_CYBER_ATK4,0,0},
    {SPR_CYBR,5,12,{A_CyberAttack},S_CYBER_ATK5,0,0},
    {SPR_CYBR,4,12,{A_FaceTarget},S_CYBER_ATK6,0,0},
    {SPR_CYBR,5,12,{A_CyberAttack},S_CYBER_RUN1,0,0},
    {SPR_CYBR,6,10,{A_Pain},S_CYBER_RUN1,0,0},
    {SPR_CYBR,7,10,{((void*)0)},S_CYBER_DIE2,0,0},
    {SPR_CYBR,8,10,{A_Scream},S_CYBER_DIE3,0,0},
    {SPR_CYBR,9,10,{((void*)0)},S_CYBER_DIE4,0,0},
    {SPR_CYBR,10,10,{((void*)0)},S_CYBER_DIE5,0,0},
    {SPR_CYBR,11,10,{((void*)0)},S_CYBER_DIE6,0,0},
    {SPR_CYBR,12,10,{A_Fall},S_CYBER_DIE7,0,0},
    {SPR_CYBR,13,10,{((void*)0)},S_CYBER_DIE8,0,0},
    {SPR_CYBR,14,10,{((void*)0)},S_CYBER_DIE9,0,0},
    {SPR_CYBR,15,30,{((void*)0)},S_CYBER_DIE10,0,0},
    {SPR_CYBR,15,-1,{A_BossDeath},S_NULL,0,0},
    {SPR_PAIN,0,10,{A_Look},S_PAIN_STND,0,0},
    {SPR_PAIN,0,3,{A_Chase},S_PAIN_RUN2,0,0},
    {SPR_PAIN,0,3,{A_Chase},S_PAIN_RUN3,0,0},
    {SPR_PAIN,1,3,{A_Chase},S_PAIN_RUN4,0,0},
    {SPR_PAIN,1,3,{A_Chase},S_PAIN_RUN5,0,0},
    {SPR_PAIN,2,3,{A_Chase},S_PAIN_RUN6,0,0},
    {SPR_PAIN,2,3,{A_Chase},S_PAIN_RUN1,0,0},
    {SPR_PAIN,3,5,{A_FaceTarget},S_PAIN_ATK2,0,0},
    {SPR_PAIN,4,5,{A_FaceTarget},S_PAIN_ATK3,0,0},
    {SPR_PAIN,32773,5,{A_FaceTarget},S_PAIN_ATK4,0,0},
    {SPR_PAIN,32773,0,{A_PainAttack},S_PAIN_RUN1,0,0},
    {SPR_PAIN,6,6,{((void*)0)},S_PAIN_PAIN2,0,0},
    {SPR_PAIN,6,6,{A_Pain},S_PAIN_RUN1,0,0},
    {SPR_PAIN,32775,8,{((void*)0)},S_PAIN_DIE2,0,0},
    {SPR_PAIN,32776,8,{A_Scream},S_PAIN_DIE3,0,0},
    {SPR_PAIN,32777,8,{((void*)0)},S_PAIN_DIE4,0,0},
    {SPR_PAIN,32778,8,{((void*)0)},S_PAIN_DIE5,0,0},
    {SPR_PAIN,32779,8,{A_PainDie},S_PAIN_DIE6,0,0},
    {SPR_PAIN,32780,8,{((void*)0)},S_NULL,0,0},
    {SPR_PAIN,12,8,{((void*)0)},S_PAIN_RAISE2,0,0},
    {SPR_PAIN,11,8,{((void*)0)},S_PAIN_RAISE3,0,0},
    {SPR_PAIN,10,8,{((void*)0)},S_PAIN_RAISE4,0,0},
    {SPR_PAIN,9,8,{((void*)0)},S_PAIN_RAISE5,0,0},
    {SPR_PAIN,8,8,{((void*)0)},S_PAIN_RAISE6,0,0},
    {SPR_PAIN,7,8,{((void*)0)},S_PAIN_RUN1,0,0},
    {SPR_SSWV,0,10,{A_Look},S_SSWV_STND2,0,0},
    {SPR_SSWV,1,10,{A_Look},S_SSWV_STND,0,0},
    {SPR_SSWV,0,3,{A_Chase},S_SSWV_RUN2,0,0},
    {SPR_SSWV,0,3,{A_Chase},S_SSWV_RUN3,0,0},
    {SPR_SSWV,1,3,{A_Chase},S_SSWV_RUN4,0,0},
    {SPR_SSWV,1,3,{A_Chase},S_SSWV_RUN5,0,0},
    {SPR_SSWV,2,3,{A_Chase},S_SSWV_RUN6,0,0},
    {SPR_SSWV,2,3,{A_Chase},S_SSWV_RUN7,0,0},
    {SPR_SSWV,3,3,{A_Chase},S_SSWV_RUN8,0,0},
    {SPR_SSWV,3,3,{A_Chase},S_SSWV_RUN1,0,0},
    {SPR_SSWV,4,10,{A_FaceTarget},S_SSWV_ATK2,0,0},
    {SPR_SSWV,5,10,{A_FaceTarget},S_SSWV_ATK3,0,0},
    {SPR_SSWV,32774,4,{A_CPosAttack},S_SSWV_ATK4,0,0},
    {SPR_SSWV,5,6,{A_FaceTarget},S_SSWV_ATK5,0,0},
    {SPR_SSWV,32774,4,{A_CPosAttack},S_SSWV_ATK6,0,0},
    {SPR_SSWV,5,1,{A_CPosRefire},S_SSWV_ATK2,0,0},
    {SPR_SSWV,7,3,{((void*)0)},S_SSWV_PAIN2,0,0},
    {SPR_SSWV,7,3,{A_Pain},S_SSWV_RUN1,0,0},
    {SPR_SSWV,8,5,{((void*)0)},S_SSWV_DIE2,0,0},
    {SPR_SSWV,9,5,{A_Scream},S_SSWV_DIE3,0,0},
    {SPR_SSWV,10,5,{A_Fall},S_SSWV_DIE4,0,0},
    {SPR_SSWV,11,5,{((void*)0)},S_SSWV_DIE5,0,0},
    {SPR_SSWV,12,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SSWV,13,5,{((void*)0)},S_SSWV_XDIE2,0,0},
    {SPR_SSWV,14,5,{A_XScream},S_SSWV_XDIE3,0,0},
    {SPR_SSWV,15,5,{A_Fall},S_SSWV_XDIE4,0,0},
    {SPR_SSWV,16,5,{((void*)0)},S_SSWV_XDIE5,0,0},
    {SPR_SSWV,17,5,{((void*)0)},S_SSWV_XDIE6,0,0},
    {SPR_SSWV,18,5,{((void*)0)},S_SSWV_XDIE7,0,0},
    {SPR_SSWV,19,5,{((void*)0)},S_SSWV_XDIE8,0,0},
    {SPR_SSWV,20,5,{((void*)0)},S_SSWV_XDIE9,0,0},
    {SPR_SSWV,21,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SSWV,12,5,{((void*)0)},S_SSWV_RAISE2,0,0},
    {SPR_SSWV,11,5,{((void*)0)},S_SSWV_RAISE3,0,0},
    {SPR_SSWV,10,5,{((void*)0)},S_SSWV_RAISE4,0,0},
    {SPR_SSWV,9,5,{((void*)0)},S_SSWV_RAISE5,0,0},
    {SPR_SSWV,8,5,{((void*)0)},S_SSWV_RUN1,0,0},
    {SPR_KEEN,0,-1,{((void*)0)},S_KEENSTND,0,0},
    {SPR_KEEN,0,6,{((void*)0)},S_COMMKEEN2,0,0},
    {SPR_KEEN,1,6,{((void*)0)},S_COMMKEEN3,0,0},
    {SPR_KEEN,2,6,{A_Scream},S_COMMKEEN4,0,0},
    {SPR_KEEN,3,6,{((void*)0)},S_COMMKEEN5,0,0},
    {SPR_KEEN,4,6,{((void*)0)},S_COMMKEEN6,0,0},
    {SPR_KEEN,5,6,{((void*)0)},S_COMMKEEN7,0,0},
    {SPR_KEEN,6,6,{((void*)0)},S_COMMKEEN8,0,0},
    {SPR_KEEN,7,6,{((void*)0)},S_COMMKEEN9,0,0},
    {SPR_KEEN,8,6,{((void*)0)},S_COMMKEEN10,0,0},
    {SPR_KEEN,9,6,{((void*)0)},S_COMMKEEN11,0,0},
    {SPR_KEEN,10,6,{A_KeenDie},S_COMMKEEN12,0,0},
    {SPR_KEEN,11,-1,{((void*)0)},S_NULL,0,0},
    {SPR_KEEN,12,4,{((void*)0)},S_KEENPAIN2,0,0},
    {SPR_KEEN,12,8,{A_Pain},S_KEENSTND,0,0},
    {SPR_BBRN,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_BBRN,1,36,{A_BrainPain},S_BRAIN,0,0},
    {SPR_BBRN,0,100,{A_BrainScream},S_BRAIN_DIE2,0,0},
    {SPR_BBRN,0,10,{((void*)0)},S_BRAIN_DIE3,0,0},
    {SPR_BBRN,0,10,{((void*)0)},S_BRAIN_DIE4,0,0},
    {SPR_BBRN,0,-1,{A_BrainDie},S_NULL,0,0},
    {SPR_SSWV,0,10,{A_Look},S_BRAINEYE,0,0},
    {SPR_SSWV,0,181,{A_BrainAwake},S_BRAINEYE1,0,0},
    {SPR_SSWV,0,150,{A_BrainSpit},S_BRAINEYE1,0,0},
    {SPR_BOSF,32768,3,{A_SpawnSound},S_SPAWN2,0,0},
    {SPR_BOSF,32769,3,{A_SpawnFly},S_SPAWN3,0,0},
    {SPR_BOSF,32770,3,{A_SpawnFly},S_SPAWN4,0,0},
    {SPR_BOSF,32771,3,{A_SpawnFly},S_SPAWN1,0,0},
    {SPR_FIRE,32768,4,{A_Fire},S_SPAWNFIRE2,0,0},
    {SPR_FIRE,32769,4,{A_Fire},S_SPAWNFIRE3,0,0},
    {SPR_FIRE,32770,4,{A_Fire},S_SPAWNFIRE4,0,0},
    {SPR_FIRE,32771,4,{A_Fire},S_SPAWNFIRE5,0,0},
    {SPR_FIRE,32772,4,{A_Fire},S_SPAWNFIRE6,0,0},
    {SPR_FIRE,32773,4,{A_Fire},S_SPAWNFIRE7,0,0},
    {SPR_FIRE,32774,4,{A_Fire},S_SPAWNFIRE8,0,0},
    {SPR_FIRE,32775,4,{A_Fire},S_NULL,0,0},
    {SPR_MISL,32769,10,{((void*)0)},S_BRAINEXPLODE2,0,0},
    {SPR_MISL,32770,10,{((void*)0)},S_BRAINEXPLODE3,0,0},
    {SPR_MISL,32771,10,{A_BrainExplode},S_NULL,0,0},
    {SPR_ARM1,0,6,{((void*)0)},S_ARM1A,0,0},
    {SPR_ARM1,32769,7,{((void*)0)},S_ARM1,0,0},
    {SPR_ARM2,0,6,{((void*)0)},S_ARM2A,0,0},
    {SPR_ARM2,32769,6,{((void*)0)},S_ARM2,0,0},
    {SPR_BAR1,0,6,{((void*)0)},S_BAR2,0,0},
    {SPR_BAR1,1,6,{((void*)0)},S_BAR1,0,0},
    {SPR_BEXP,32768,5,{((void*)0)},S_BEXP2,0,0},
    {SPR_BEXP,32769,5,{A_Scream},S_BEXP3,0,0},
    {SPR_BEXP,32770,5,{((void*)0)},S_BEXP4,0,0},
    {SPR_BEXP,32771,10,{A_Explode},S_BEXP5,0,0},
    {SPR_BEXP,32772,10,{((void*)0)},S_NULL,0,0},
    {SPR_FCAN,32768,4,{((void*)0)},S_BBAR2,0,0},
    {SPR_FCAN,32769,4,{((void*)0)},S_BBAR3,0,0},
    {SPR_FCAN,32770,4,{((void*)0)},S_BBAR1,0,0},
    {SPR_BON1,0,6,{((void*)0)},S_BON1A,0,0},
    {SPR_BON1,1,6,{((void*)0)},S_BON1B,0,0},
    {SPR_BON1,2,6,{((void*)0)},S_BON1C,0,0},
    {SPR_BON1,3,6,{((void*)0)},S_BON1D,0,0},
    {SPR_BON1,2,6,{((void*)0)},S_BON1E,0,0},
    {SPR_BON1,1,6,{((void*)0)},S_BON1,0,0},
    {SPR_BON2,0,6,{((void*)0)},S_BON2A,0,0},
    {SPR_BON2,1,6,{((void*)0)},S_BON2B,0,0},
    {SPR_BON2,2,6,{((void*)0)},S_BON2C,0,0},
    {SPR_BON2,3,6,{((void*)0)},S_BON2D,0,0},
    {SPR_BON2,2,6,{((void*)0)},S_BON2E,0,0},
    {SPR_BON2,1,6,{((void*)0)},S_BON2,0,0},
    {SPR_BKEY,0,10,{((void*)0)},S_BKEY2,0,0},
    {SPR_BKEY,32769,10,{((void*)0)},S_BKEY,0,0},
    {SPR_RKEY,0,10,{((void*)0)},S_RKEY2,0,0},
    {SPR_RKEY,32769,10,{((void*)0)},S_RKEY,0,0},
    {SPR_YKEY,0,10,{((void*)0)},S_YKEY2,0,0},
    {SPR_YKEY,32769,10,{((void*)0)},S_YKEY,0,0},
    {SPR_BSKU,0,10,{((void*)0)},S_BSKULL2,0,0},
    {SPR_BSKU,32769,10,{((void*)0)},S_BSKULL,0,0},
    {SPR_RSKU,0,10,{((void*)0)},S_RSKULL2,0,0},
    {SPR_RSKU,32769,10,{((void*)0)},S_RSKULL,0,0},
    {SPR_YSKU,0,10,{((void*)0)},S_YSKULL2,0,0},
    {SPR_YSKU,32769,10,{((void*)0)},S_YSKULL,0,0},
    {SPR_STIM,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_MEDI,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SOUL,32768,6,{((void*)0)},S_SOUL2,0,0},
    {SPR_SOUL,32769,6,{((void*)0)},S_SOUL3,0,0},
    {SPR_SOUL,32770,6,{((void*)0)},S_SOUL4,0,0},
    {SPR_SOUL,32771,6,{((void*)0)},S_SOUL5,0,0},
    {SPR_SOUL,32770,6,{((void*)0)},S_SOUL6,0,0},
    {SPR_SOUL,32769,6,{((void*)0)},S_SOUL,0,0},
    {SPR_PINV,32768,6,{((void*)0)},S_PINV2,0,0},
    {SPR_PINV,32769,6,{((void*)0)},S_PINV3,0,0},
    {SPR_PINV,32770,6,{((void*)0)},S_PINV4,0,0},
    {SPR_PINV,32771,6,{((void*)0)},S_PINV,0,0},
    {SPR_PSTR,32768,-1,{((void*)0)},S_NULL,0,0},
    {SPR_PINS,32768,6,{((void*)0)},S_PINS2,0,0},
    {SPR_PINS,32769,6,{((void*)0)},S_PINS3,0,0},
    {SPR_PINS,32770,6,{((void*)0)},S_PINS4,0,0},
    {SPR_PINS,32771,6,{((void*)0)},S_PINS,0,0},
    {SPR_MEGA,32768,6,{((void*)0)},S_MEGA2,0,0},
    {SPR_MEGA,32769,6,{((void*)0)},S_MEGA3,0,0},
    {SPR_MEGA,32770,6,{((void*)0)},S_MEGA4,0,0},
    {SPR_MEGA,32771,6,{((void*)0)},S_MEGA,0,0},
    {SPR_SUIT,32768,-1,{((void*)0)},S_NULL,0,0},
    {SPR_PMAP,32768,6,{((void*)0)},S_PMAP2,0,0},
    {SPR_PMAP,32769,6,{((void*)0)},S_PMAP3,0,0},
    {SPR_PMAP,32770,6,{((void*)0)},S_PMAP4,0,0},
    {SPR_PMAP,32771,6,{((void*)0)},S_PMAP5,0,0},
    {SPR_PMAP,32770,6,{((void*)0)},S_PMAP6,0,0},
    {SPR_PMAP,32769,6,{((void*)0)},S_PMAP,0,0},
    {SPR_PVIS,32768,6,{((void*)0)},S_PVIS2,0,0},
    {SPR_PVIS,1,6,{((void*)0)},S_PVIS,0,0},
    {SPR_CLIP,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_AMMO,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_ROCK,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_BROK,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_CELL,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_CELP,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SHEL,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SBOX,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_BPAK,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_BFUG,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_MGUN,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_CSAW,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_LAUN,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_PLAS,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SHOT,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SGN2,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_COLU,32768,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SMT2,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_GOR1,0,10,{((void*)0)},S_BLOODYTWITCH2,0,0},
    {SPR_GOR1,1,15,{((void*)0)},S_BLOODYTWITCH3,0,0},
    {SPR_GOR1,2,8,{((void*)0)},S_BLOODYTWITCH4,0,0},
    {SPR_GOR1,1,6,{((void*)0)},S_BLOODYTWITCH,0,0},
    {SPR_PLAY,13,-1,{((void*)0)},S_NULL,0,0},
    {SPR_PLAY,18,-1,{((void*)0)},S_NULL,0,0},
    {SPR_POL2,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_POL5,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_POL4,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_POL3,32768,6,{((void*)0)},S_HEADCANDLES2,0,0},
    {SPR_POL3,32769,6,{((void*)0)},S_HEADCANDLES,0,0},
    {SPR_POL1,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_POL6,0,6,{((void*)0)},S_LIVESTICK2,0,0},
    {SPR_POL6,1,8,{((void*)0)},S_LIVESTICK,0,0},
    {SPR_GOR2,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_GOR3,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_GOR4,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_GOR5,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_SMIT,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_COL1,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_COL2,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_COL3,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_COL4,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_CAND,32768,-1,{((void*)0)},S_NULL,0,0},
    {SPR_CBRA,32768,-1,{((void*)0)},S_NULL,0,0},
    {SPR_COL6,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_TRE1,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_TRE2,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_ELEC,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_CEYE,32768,6,{((void*)0)},S_EVILEYE2,0,0},
    {SPR_CEYE,32769,6,{((void*)0)},S_EVILEYE3,0,0},
    {SPR_CEYE,32770,6,{((void*)0)},S_EVILEYE4,0,0},
    {SPR_CEYE,32769,6,{((void*)0)},S_EVILEYE,0,0},
    {SPR_FSKU,32768,6,{((void*)0)},S_FLOATSKULL2,0,0},
    {SPR_FSKU,32769,6,{((void*)0)},S_FLOATSKULL3,0,0},
    {SPR_FSKU,32770,6,{((void*)0)},S_FLOATSKULL,0,0},
    {SPR_COL5,0,14,{((void*)0)},S_HEARTCOL2,0,0},
    {SPR_COL5,1,14,{((void*)0)},S_HEARTCOL,0,0},
    {SPR_TBLU,32768,4,{((void*)0)},S_BLUETORCH2,0,0},
    {SPR_TBLU,32769,4,{((void*)0)},S_BLUETORCH3,0,0},
    {SPR_TBLU,32770,4,{((void*)0)},S_BLUETORCH4,0,0},
    {SPR_TBLU,32771,4,{((void*)0)},S_BLUETORCH,0,0},
    {SPR_TGRN,32768,4,{((void*)0)},S_GREENTORCH2,0,0},
    {SPR_TGRN,32769,4,{((void*)0)},S_GREENTORCH3,0,0},
    {SPR_TGRN,32770,4,{((void*)0)},S_GREENTORCH4,0,0},
    {SPR_TGRN,32771,4,{((void*)0)},S_GREENTORCH,0,0},
    {SPR_TRED,32768,4,{((void*)0)},S_REDTORCH2,0,0},
    {SPR_TRED,32769,4,{((void*)0)},S_REDTORCH3,0,0},
    {SPR_TRED,32770,4,{((void*)0)},S_REDTORCH4,0,0},
    {SPR_TRED,32771,4,{((void*)0)},S_REDTORCH,0,0},
    {SPR_SMBT,32768,4,{((void*)0)},S_BTORCHSHRT2,0,0},
    {SPR_SMBT,32769,4,{((void*)0)},S_BTORCHSHRT3,0,0},
    {SPR_SMBT,32770,4,{((void*)0)},S_BTORCHSHRT4,0,0},
    {SPR_SMBT,32771,4,{((void*)0)},S_BTORCHSHRT,0,0},
    {SPR_SMGT,32768,4,{((void*)0)},S_GTORCHSHRT2,0,0},
    {SPR_SMGT,32769,4,{((void*)0)},S_GTORCHSHRT3,0,0},
    {SPR_SMGT,32770,4,{((void*)0)},S_GTORCHSHRT4,0,0},
    {SPR_SMGT,32771,4,{((void*)0)},S_GTORCHSHRT,0,0},
    {SPR_SMRT,32768,4,{((void*)0)},S_RTORCHSHRT2,0,0},
    {SPR_SMRT,32769,4,{((void*)0)},S_RTORCHSHRT3,0,0},
    {SPR_SMRT,32770,4,{((void*)0)},S_RTORCHSHRT4,0,0},
    {SPR_SMRT,32771,4,{((void*)0)},S_RTORCHSHRT,0,0},
    {SPR_HDB1,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_HDB2,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_HDB3,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_HDB4,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_HDB5,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_HDB6,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_POB1,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_POB2,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_BRS1,0,-1,{((void*)0)},S_NULL,0,0},
    {SPR_TLMP,32768,4,{((void*)0)},S_TECHLAMP2,0,0},
    {SPR_TLMP,32769,4,{((void*)0)},S_TECHLAMP3,0,0},
    {SPR_TLMP,32770,4,{((void*)0)},S_TECHLAMP4,0,0},
    {SPR_TLMP,32771,4,{((void*)0)},S_TECHLAMP,0,0},
    {SPR_TLP2,32768,4,{((void*)0)},S_TECH2LAMP2,0,0},
    {SPR_TLP2,32769,4,{((void*)0)},S_TECH2LAMP3,0,0},
    {SPR_TLP2,32770,4,{((void*)0)},S_TECH2LAMP4,0,0},
    {SPR_TLP2,32771,4,{((void*)0)},S_TECH2LAMP,0,0}
};


mobjinfo_t mobjinfo[NUMMOBJTYPES] = {

    {
 -1,
 S_PLAY,
 100,
 S_PLAY_RUN1,
 sfx_None,
 0,
 sfx_None,
 S_PLAY_PAIN,
 255,
 sfx_plpain,
 S_NULL,
 S_PLAY_ATK1,
 S_PLAY_DIE1,
 S_PLAY_XDIE1,
 sfx_pldeth,
 0,
 16*(1<<16),
 56*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SHOOTABLE|MF_DROPOFF|MF_PICKUP|MF_NOTDMATCH,
 S_NULL
    },

    {
 3004,
 S_POSS_STND,
 20,
 S_POSS_RUN1,
 sfx_posit1,
 8,
 sfx_pistol,
 S_POSS_PAIN,
 200,
 sfx_popain,
 0,
 S_POSS_ATK1,
 S_POSS_DIE1,
 S_POSS_XDIE1,
 sfx_podth1,
 8,
 20*(1<<16),
 56*(1<<16),
 100,
 0,
 sfx_posact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_POSS_RAISE1
    },

    {
 9,
 S_SPOS_STND,
 30,
 S_SPOS_RUN1,
 sfx_posit2,
 8,
 0,
 S_SPOS_PAIN,
 170,
 sfx_popain,
 0,
 S_SPOS_ATK1,
 S_SPOS_DIE1,
 S_SPOS_XDIE1,
 sfx_podth2,
 8,
 20*(1<<16),
 56*(1<<16),
 100,
 0,
 sfx_posact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_SPOS_RAISE1
    },

    {
 64,
 S_VILE_STND,
 700,
 S_VILE_RUN1,
 sfx_vilsit,
 8,
 0,
 S_VILE_PAIN,
 10,
 sfx_vipain,
 0,
 S_VILE_ATK1,
 S_VILE_DIE1,
 S_NULL,
 sfx_vildth,
 15,
 20*(1<<16),
 56*(1<<16),
 500,
 0,
 sfx_vilact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_NULL
    },

    {
 -1,
 S_FIRE1,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP|MF_NOGRAVITY,
 S_NULL
    },

    {
 66,
 S_SKEL_STND,
 300,
 S_SKEL_RUN1,
 sfx_skesit,
 8,
 0,
 S_SKEL_PAIN,
 100,
 sfx_popain,
 S_SKEL_FIST1,
 S_SKEL_MISS1,
 S_SKEL_DIE1,
 S_NULL,
 sfx_skedth,
 10,
 20*(1<<16),
 56*(1<<16),
 500,
 0,
 sfx_skeact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_SKEL_RAISE1
    },

    {
 -1,
 S_TRACER,
 1000,
 S_NULL,
 sfx_skeatk,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_TRACEEXP1,
 S_NULL,
 sfx_barexp,
 10*(1<<16),
 11*(1<<16),
 8*(1<<16),
 100,
 10,
 sfx_None,
 MF_NOBLOCKMAP|MF_MISSILE|MF_DROPOFF|MF_NOGRAVITY,
 S_NULL
    },

    {
 -1,
 S_SMOKE1,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP|MF_NOGRAVITY,
 S_NULL
    },

    {
 67,
 S_FATT_STND,
 600,
 S_FATT_RUN1,
 sfx_mansit,
 8,
 0,
 S_FATT_PAIN,
 80,
 sfx_mnpain,
 0,
 S_FATT_ATK1,
 S_FATT_DIE1,
 S_NULL,
 sfx_mandth,
 8,
 48*(1<<16),
 64*(1<<16),
 1000,
 0,
 sfx_posact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_FATT_RAISE1
    },

    {
 -1,
 S_FATSHOT1,
 1000,
 S_NULL,
 sfx_firsht,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_FATSHOTX1,
 S_NULL,
 sfx_firxpl,
 20*(1<<16),
 6*(1<<16),
 8*(1<<16),
 100,
 8,
 sfx_None,
 MF_NOBLOCKMAP|MF_MISSILE|MF_DROPOFF|MF_NOGRAVITY,
 S_NULL
    },

    {
 65,
 S_CPOS_STND,
 70,
 S_CPOS_RUN1,
 sfx_posit2,
 8,
 0,
 S_CPOS_PAIN,
 170,
 sfx_popain,
 0,
 S_CPOS_ATK1,
 S_CPOS_DIE1,
 S_CPOS_XDIE1,
 sfx_podth2,
 8,
 20*(1<<16),
 56*(1<<16),
 100,
 0,
 sfx_posact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_CPOS_RAISE1
    },

    {
 3001,
 S_TROO_STND,
 60,
 S_TROO_RUN1,
 sfx_bgsit1,
 8,
 0,
 S_TROO_PAIN,
 200,
 sfx_popain,
 S_TROO_ATK1,
 S_TROO_ATK1,
 S_TROO_DIE1,
 S_TROO_XDIE1,
 sfx_bgdth1,
 8,
 20*(1<<16),
 56*(1<<16),
 100,
 0,
 sfx_bgact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_TROO_RAISE1
    },

    {
 3002,
 S_SARG_STND,
 150,
 S_SARG_RUN1,
 sfx_sgtsit,
 8,
 sfx_sgtatk,
 S_SARG_PAIN,
 180,
 sfx_dmpain,
 S_SARG_ATK1,
 0,
 S_SARG_DIE1,
 S_NULL,
 sfx_sgtdth,
 10,
 30*(1<<16),
 56*(1<<16),
 400,
 0,
 sfx_dmact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_SARG_RAISE1
    },

    {
 58,
 S_SARG_STND,
 150,
 S_SARG_RUN1,
 sfx_sgtsit,
 8,
 sfx_sgtatk,
 S_SARG_PAIN,
 180,
 sfx_dmpain,
 S_SARG_ATK1,
 0,
 S_SARG_DIE1,
 S_NULL,
 sfx_sgtdth,
 10,
 30*(1<<16),
 56*(1<<16),
 400,
 0,
 sfx_dmact,
 MF_SOLID|MF_SHOOTABLE|MF_SHADOW|MF_COUNTKILL,
 S_SARG_RAISE1
    },

    {
 3005,
 S_HEAD_STND,
 400,
 S_HEAD_RUN1,
 sfx_cacsit,
 8,
 0,
 S_HEAD_PAIN,
 128,
 sfx_dmpain,
 0,
 S_HEAD_ATK1,
 S_HEAD_DIE1,
 S_NULL,
 sfx_cacdth,
 8,
 31*(1<<16),
 56*(1<<16),
 400,
 0,
 sfx_dmact,
 MF_SOLID|MF_SHOOTABLE|MF_FLOAT|MF_NOGRAVITY|MF_COUNTKILL,
 S_HEAD_RAISE1
    },

    {
 3003,
 S_BOSS_STND,
 1000,
 S_BOSS_RUN1,
 sfx_brssit,
 8,
 0,
 S_BOSS_PAIN,
 50,
 sfx_dmpain,
 S_BOSS_ATK1,
 S_BOSS_ATK1,
 S_BOSS_DIE1,
 S_NULL,
 sfx_brsdth,
 8,
 24*(1<<16),
 64*(1<<16),
 1000,
 0,
 sfx_dmact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_BOSS_RAISE1
    },

    {
 -1,
 S_BRBALL1,
 1000,
 S_NULL,
 sfx_firsht,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_BRBALLX1,
 S_NULL,
 sfx_firxpl,
 15*(1<<16),
 6*(1<<16),
 8*(1<<16),
 100,
 8,
 sfx_None,
 MF_NOBLOCKMAP|MF_MISSILE|MF_DROPOFF|MF_NOGRAVITY,
 S_NULL
    },

    {
 69,
 S_BOS2_STND,
 500,
 S_BOS2_RUN1,
 sfx_kntsit,
 8,
 0,
 S_BOS2_PAIN,
 50,
 sfx_dmpain,
 S_BOS2_ATK1,
 S_BOS2_ATK1,
 S_BOS2_DIE1,
 S_NULL,
 sfx_kntdth,
 8,
 24*(1<<16),
 64*(1<<16),
 1000,
 0,
 sfx_dmact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_BOS2_RAISE1
    },

    {
 3006,
 S_SKULL_STND,
 100,
 S_SKULL_RUN1,
 0,
 8,
 sfx_sklatk,
 S_SKULL_PAIN,
 256,
 sfx_dmpain,
 0,
 S_SKULL_ATK1,
 S_SKULL_DIE1,
 S_NULL,
 sfx_firxpl,
 8,
 16*(1<<16),
 56*(1<<16),
 50,
 3,
 sfx_dmact,
 MF_SOLID|MF_SHOOTABLE|MF_FLOAT|MF_NOGRAVITY,
 S_NULL
    },

    {
 7,
 S_SPID_STND,
 3000,
 S_SPID_RUN1,
 sfx_spisit,
 8,
 sfx_shotgn,
 S_SPID_PAIN,
 40,
 sfx_dmpain,
 0,
 S_SPID_ATK1,
 S_SPID_DIE1,
 S_NULL,
 sfx_spidth,
 12,
 128*(1<<16),
 100*(1<<16),
 1000,
 0,
 sfx_dmact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_NULL
    },

    {
 68,
 S_BSPI_STND,
 500,
 S_BSPI_SIGHT,
 sfx_bspsit,
 8,
 0,
 S_BSPI_PAIN,
 128,
 sfx_dmpain,
 0,
 S_BSPI_ATK1,
 S_BSPI_DIE1,
 S_NULL,
 sfx_bspdth,
 12,
 64*(1<<16),
 64*(1<<16),
 600,
 0,
 sfx_bspact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_BSPI_RAISE1
    },

    {
 16,
 S_CYBER_STND,
 4000,
 S_CYBER_RUN1,
 sfx_cybsit,
 8,
 0,
 S_CYBER_PAIN,
 20,
 sfx_dmpain,
 0,
 S_CYBER_ATK1,
 S_CYBER_DIE1,
 S_NULL,
 sfx_cybdth,
 16,
 40*(1<<16),
 110*(1<<16),
 1000,
 0,
 sfx_dmact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_NULL
    },

    {
 71,
 S_PAIN_STND,
 400,
 S_PAIN_RUN1,
 sfx_pesit,
 8,
 0,
 S_PAIN_PAIN,
 128,
 sfx_pepain,
 0,
 S_PAIN_ATK1,
 S_PAIN_DIE1,
 S_NULL,
 sfx_pedth,
 8,
 31*(1<<16),
 56*(1<<16),
 400,
 0,
 sfx_dmact,
 MF_SOLID|MF_SHOOTABLE|MF_FLOAT|MF_NOGRAVITY|MF_COUNTKILL,
 S_PAIN_RAISE1
    },

    {
 84,
 S_SSWV_STND,
 50,
 S_SSWV_RUN1,
 sfx_sssit,
 8,
 0,
 S_SSWV_PAIN,
 170,
 sfx_popain,
 0,
 S_SSWV_ATK1,
 S_SSWV_DIE1,
 S_SSWV_XDIE1,
 sfx_ssdth,
 8,
 20*(1<<16),
 56*(1<<16),
 100,
 0,
 sfx_posact,
 MF_SOLID|MF_SHOOTABLE|MF_COUNTKILL,
 S_SSWV_RAISE1
    },

    {
 72,
 S_KEENSTND,
 100,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_KEENPAIN,
 256,
 sfx_keenpn,
 S_NULL,
 S_NULL,
 S_COMMKEEN,
 S_NULL,
 sfx_keendt,
 0,
 16*(1<<16),
 72*(1<<16),
 10000000,
 0,
 sfx_None,
 MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY|MF_SHOOTABLE|MF_COUNTKILL,
 S_NULL
    },

    {
 88,
 S_BRAIN,
 250,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_BRAIN_PAIN,
 255,
 sfx_bospn,
 S_NULL,
 S_NULL,
 S_BRAIN_DIE1,
 S_NULL,
 sfx_bosdth,
 0,
 16*(1<<16),
 16*(1<<16),
 10000000,
 0,
 sfx_None,
 MF_SOLID|MF_SHOOTABLE,
 S_NULL
    },

    {
 89,
 S_BRAINEYE,
 1000,
 S_BRAINEYESEE,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 32*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP|MF_NOSECTOR,
 S_NULL
    },

    {
 87,
 S_NULL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 32*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP|MF_NOSECTOR,
 S_NULL
    },

    {
 -1,
 S_SPAWN1,
 1000,
 S_NULL,
 sfx_bospit,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_firxpl,
 10*(1<<16),
 6*(1<<16),
 32*(1<<16),
 100,
 3,
 sfx_None,
 MF_NOBLOCKMAP|MF_MISSILE|MF_DROPOFF|MF_NOGRAVITY|MF_NOCLIP,
 S_NULL
    },

    {
 -1,
 S_SPAWNFIRE1,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP|MF_NOGRAVITY,
 S_NULL
    },

    {
 2035,
 S_BAR1,
 20,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_BEXP,
 S_NULL,
 sfx_barexp,
 0,
 10*(1<<16),
 42*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SHOOTABLE|MF_NOBLOOD,
 S_NULL
    },

    {
 -1,
 S_TBALL1,
 1000,
 S_NULL,
 sfx_firsht,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_TBALLX1,
 S_NULL,
 sfx_firxpl,
 10*(1<<16),
 6*(1<<16),
 8*(1<<16),
 100,
 3,
 sfx_None,
 MF_NOBLOCKMAP|MF_MISSILE|MF_DROPOFF|MF_NOGRAVITY,
 S_NULL
    },

    {
 -1,
 S_RBALL1,
 1000,
 S_NULL,
 sfx_firsht,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_RBALLX1,
 S_NULL,
 sfx_firxpl,
 10*(1<<16),
 6*(1<<16),
 8*(1<<16),
 100,
 5,
 sfx_None,
 MF_NOBLOCKMAP|MF_MISSILE|MF_DROPOFF|MF_NOGRAVITY,
 S_NULL
    },

    {
 -1,
 S_ROCKET,
 1000,
 S_NULL,
 sfx_rlaunc,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_EXPLODE1,
 S_NULL,
 sfx_barexp,
 20*(1<<16),
 11*(1<<16),
 8*(1<<16),
 100,
 20,
 sfx_None,
 MF_NOBLOCKMAP|MF_MISSILE|MF_DROPOFF|MF_NOGRAVITY,
 S_NULL
    },

    {
 -1,
 S_PLASBALL,
 1000,
 S_NULL,
 sfx_plasma,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_PLASEXP,
 S_NULL,
 sfx_firxpl,
 25*(1<<16),
 13*(1<<16),
 8*(1<<16),
 100,
 5,
 sfx_None,
 MF_NOBLOCKMAP|MF_MISSILE|MF_DROPOFF|MF_NOGRAVITY,
 S_NULL
    },

    {
 -1,
 S_BFGSHOT,
 1000,
 S_NULL,
 0,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_BFGLAND,
 S_NULL,
 sfx_rxplod,
 25*(1<<16),
 13*(1<<16),
 8*(1<<16),
 100,
 100,
 sfx_None,
 MF_NOBLOCKMAP|MF_MISSILE|MF_DROPOFF|MF_NOGRAVITY,
 S_NULL
    },

    {
 -1,
 S_ARACH_PLAZ,
 1000,
 S_NULL,
 sfx_plasma,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_ARACH_PLEX,
 S_NULL,
 sfx_firxpl,
 25*(1<<16),
 13*(1<<16),
 8*(1<<16),
 100,
 5,
 sfx_None,
 MF_NOBLOCKMAP|MF_MISSILE|MF_DROPOFF|MF_NOGRAVITY,
 S_NULL
    },

    {
 -1,
 S_PUFF1,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP|MF_NOGRAVITY,
 S_NULL
    },

    {
 -1,
 S_BLOOD1,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP,
 S_NULL
    },

    {
 -1,
 S_TFOG,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP|MF_NOGRAVITY,
 S_NULL
    },

    {
 -1,
 S_IFOG,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP|MF_NOGRAVITY,
 S_NULL
    },

    {
 14,
 S_NULL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP|MF_NOSECTOR,
 S_NULL
    },

    {
 -1,
 S_BFGEXP,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP|MF_NOGRAVITY,
 S_NULL
    },

    {
 2018,
 S_ARM1,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2019,
 S_ARM2,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2014,
 S_BON1,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_COUNTITEM,
 S_NULL
    },

    {
 2015,
 S_BON2,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_COUNTITEM,
 S_NULL
    },

    {
 5,
 S_BKEY,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_NOTDMATCH,
 S_NULL
    },

    {
 13,
 S_RKEY,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_NOTDMATCH,
 S_NULL
    },

    {
 6,
 S_YKEY,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_NOTDMATCH,
 S_NULL
    },

    {
 39,
 S_YSKULL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_NOTDMATCH,
 S_NULL
    },

    {
 38,
 S_RSKULL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_NOTDMATCH,
 S_NULL
    },

    {
 40,
 S_BSKULL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_NOTDMATCH,
 S_NULL
    },

    {
 2011,
 S_STIM,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2012,
 S_MEDI,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2013,
 S_SOUL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_COUNTITEM,
 S_NULL
    },

    {
 2022,
 S_PINV,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_COUNTITEM,
 S_NULL
    },

    {
 2023,
 S_PSTR,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_COUNTITEM,
 S_NULL
    },

    {
 2024,
 S_PINS,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_COUNTITEM,
 S_NULL
    },

    {
 2025,
 S_SUIT,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2026,
 S_PMAP,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_COUNTITEM,
 S_NULL
    },

    {
 2045,
 S_PVIS,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_COUNTITEM,
 S_NULL
    },

    {
 83,
 S_MEGA,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL|MF_COUNTITEM,
 S_NULL
    },

    {
 2007,
 S_CLIP,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2048,
 S_AMMO,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2010,
 S_ROCK,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2046,
 S_BROK,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2047,
 S_CELL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 17,
 S_CELP,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2008,
 S_SHEL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2049,
 S_SBOX,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 8,
 S_BPAK,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2006,
 S_BFUG,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2002,
 S_MGUN,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2005,
 S_CSAW,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2003,
 S_LAUN,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2004,
 S_PLAS,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 2001,
 S_SHOT,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 82,
 S_SHOT2,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPECIAL,
 S_NULL
    },

    {
 85,
 S_TECHLAMP,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 86,
 S_TECH2LAMP,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 2028,
 S_COLU,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 30,
 S_TALLGRNCOL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 31,
 S_SHRTGRNCOL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 32,
 S_TALLREDCOL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 33,
 S_SHRTREDCOL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 37,
 S_SKULLCOL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 36,
 S_HEARTCOL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 41,
 S_EVILEYE,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 42,
 S_FLOATSKULL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 43,
 S_TORCHTREE,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 44,
 S_BLUETORCH,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 45,
 S_GREENTORCH,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 46,
 S_REDTORCH,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 55,
 S_BTORCHSHRT,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 56,
 S_GTORCHSHRT,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 57,
 S_RTORCHSHRT,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 47,
 S_STALAGTITE,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 48,
 S_TECHPILLAR,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 34,
 S_CANDLESTIK,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 0,
 S_NULL
    },

    {
 35,
 S_CANDELABRA,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 49,
 S_BLOODYTWITCH,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 68*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 50,
 S_MEAT2,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 84*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 51,
 S_MEAT3,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 84*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 52,
 S_MEAT4,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 68*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 53,
 S_MEAT5,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 52*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 59,
 S_MEAT2,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 84*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 60,
 S_MEAT4,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 68*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 61,
 S_MEAT3,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 52*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 62,
 S_MEAT5,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 52*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 63,
 S_BLOODYTWITCH,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 68*(1<<16),
 100,
 0,
 sfx_None,
 MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 22,
 S_HEAD_DIE6,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 0,
 S_NULL
    },

    {
 15,
 S_PLAY_DIE7,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 0,
 S_NULL
    },

    {
 18,
 S_POSS_DIE5,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 0,
 S_NULL
    },

    {
 21,
 S_SARG_DIE6,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 0,
 S_NULL
    },

    {
 23,
 S_SKULL_DIE6,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 0,
 S_NULL
    },

    {
 20,
 S_TROO_DIE5,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 0,
 S_NULL
    },

    {
 19,
 S_SPOS_DIE5,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 0,
 S_NULL
    },

    {
 10,
 S_PLAY_XDIE9,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 0,
 S_NULL
    },

    {
 12,
 S_PLAY_XDIE9,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 0,
 S_NULL
    },

    {
 28,
 S_HEADSONSTICK,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 24,
 S_GIBS,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 0,
 S_NULL
    },

    {
 27,
 S_HEADONASTICK,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 29,
 S_HEADCANDLES,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 25,
 S_DEADSTICK,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 26,
 S_LIVESTICK,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 54,
 S_BIGTREE,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 32*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 70,
 S_BBAR1,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID,
 S_NULL
    },

    {
 73,
 S_HANGNOGUTS,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 88*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 74,
 S_HANGBNOBRAIN,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 88*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 75,
 S_HANGTLOOKDN,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 64*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 76,
 S_HANGTSKULL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 64*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 77,
 S_HANGTLOOKUP,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 64*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 78,
 S_HANGTNOBRAIN,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 16*(1<<16),
 64*(1<<16),
 100,
 0,
 sfx_None,
 MF_SOLID|MF_SPAWNCEILING|MF_NOGRAVITY,
 S_NULL
    },

    {
 79,
 S_COLONGIBS,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP,
 S_NULL
    },

    {
 80,
 S_SMALLPOOL,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP,
 S_NULL
    },

    {
 81,
 S_BRAINSTEM,
 1000,
 S_NULL,
 sfx_None,
 8,
 sfx_None,
 S_NULL,
 0,
 sfx_None,
 S_NULL,
 S_NULL,
 S_NULL,
 S_NULL,
 sfx_None,
 0,
 20*(1<<16),
 16*(1<<16),
 100,
 0,
 sfx_None,
 MF_NOBLOCKMAP,
 S_NULL
    }
};
extern int cd_Error;

int I_CDMusInit(void);
void I_CDMusPrintStartup(void);
int I_CDMusPlay(int track);
int I_CDMusStop(void);
int I_CDMusResume(void);
int I_CDMusSetVolume(int volume);
int I_CDMusFirstTrack(void);
int I_CDMusLastTrack(void);
int I_CDMusTrackLength(int track);







int cd_Error;

int I_CDMusInit(void)
{
    return 0;
}




void I_CDMusPrintStartup(void)
{
}

int I_CDMusPlay(int track)
{
 return 0;

}

int I_CDMusStop(void)
{
 return 0;

}

int I_CDMusResume(void)
{
 return 0;

}

int I_CDMusSetVolume(int volume)
{


    cd_Error = 0;

    return 0;
}

int I_CDMusFirstTrack(void)
{
 return 0;

}

int I_CDMusLastTrack(void)
{
 return 0;

}

int I_CDMusTrackLength(int track_num)
{
 return 0;

}
void I_Endoom(byte *endoom_data)
{
}
static int usejoystick = 0;



static int joystick_index = -1;




static int joystick_x_axis = 0;
static int joystick_x_invert = 0;




static int joystick_y_axis = 1;
static int joystick_y_invert = 0;



static int joystick_strafe_axis = -1;
static int joystick_strafe_invert = 0;



static int joystick_physical_buttons[10] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

void I_ShutdownJoystick(void)
{
}
void I_InitJoystick(void)
{
}
void I_UpdateJoystick(void)
{
}

void I_BindJoystickVariables(void)
{
    int i;

    M_BindVariable("use_joystick", &usejoystick);
    M_BindVariable("joystick_index", &joystick_index);
    M_BindVariable("joystick_x_axis", &joystick_x_axis);
    M_BindVariable("joystick_y_axis", &joystick_y_axis);
    M_BindVariable("joystick_strafe_axis", &joystick_strafe_axis);
    M_BindVariable("joystick_x_invert", &joystick_x_invert);
    M_BindVariable("joystick_y_invert", &joystick_y_invert);
    M_BindVariable("joystick_strafe_invert",&joystick_strafe_invert);

    for (i = 0; i < 10; ++i)
    {
        char name[32];
        M_snprintf(name, sizeof(name), "joystick_physical_button%i", i);
        M_BindVariable(name, &joystick_physical_buttons[i]);
    }
}
static byte *src_buffer;



static byte *dest_buffer;



static int dest_pitch;






static byte *stretch_tables[2] = { ((void*)0), ((void*)0) };



static byte *half_stretch_table = ((void*)0);




void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch)
{
    src_buffer = _src_buffer;
    dest_buffer = _dest_buffer;
    dest_pitch = _dest_pitch;
}
static boolean I_Scale1x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp;
    int y;
    int w = x2 - x1;



    bufp = src_buffer + y1 * 320 + x1;
    screenp = (byte *) dest_buffer + y1 * dest_pitch + x1;

    for (y=y1; y<y2; ++y)
    {
        memcpy(screenp, bufp, w);
        screenp += dest_pitch;
        bufp += 320;
    }

    return true;
}

screen_mode_t mode_scale_1x = {
    320, 200,
    ((void*)0),
    I_Scale1x,
    false,
};



static boolean I_Scale2x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp, *screenp2;
    int x, y;
    int multi_pitch;

    multi_pitch = dest_pitch * 2;
    bufp = src_buffer + y1 * 320 + x1;
    screenp = (byte *) dest_buffer + (y1 * dest_pitch + x1) * 2;
    screenp2 = screenp + dest_pitch;

    for (y=y1; y<y2; ++y)
    {
        byte *sp, *sp2, *bp;
        sp = screenp;
        sp2 = screenp2;
        bp = bufp;

        for (x=x1; x<x2; ++x)
        {
            *sp++ = *bp; *sp++ = *bp;
            *sp2++ = *bp; *sp2++ = *bp;
            ++bp;
        }
        screenp += multi_pitch;
        screenp2 += multi_pitch;
        bufp += 320;
    }

    return true;
}

screen_mode_t mode_scale_2x = {
    320 * 2, 200 * 2,
    ((void*)0),
    I_Scale2x,
    false,
};



static boolean I_Scale3x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp, *screenp2, *screenp3;
    int x, y;
    int multi_pitch;

    multi_pitch = dest_pitch * 3;
    bufp = src_buffer + y1 * 320 + x1;
    screenp = (byte *) dest_buffer + (y1 * dest_pitch + x1) * 3;
    screenp2 = screenp + dest_pitch;
    screenp3 = screenp + dest_pitch * 2;

    for (y=y1; y<y2; ++y)
    {
        byte *sp, *sp2, *sp3, *bp;
        sp = screenp;
        sp2 = screenp2;
        sp3 = screenp3;
        bp = bufp;

        for (x=x1; x<x2; ++x)
        {
            *sp++ = *bp; *sp++ = *bp; *sp++ = *bp;
            *sp2++ = *bp; *sp2++ = *bp; *sp2++ = *bp;
            *sp3++ = *bp; *sp3++ = *bp; *sp3++ = *bp;
            ++bp;
        }
        screenp += multi_pitch;
        screenp2 += multi_pitch;
        screenp3 += multi_pitch;
        bufp += 320;
    }

    return true;
}

screen_mode_t mode_scale_3x = {
    320 * 3, 200 * 3,
    ((void*)0),
    I_Scale3x,
    false,
};



static boolean I_Scale4x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp, *screenp2, *screenp3, *screenp4;
    int x, y;
    int multi_pitch;

    multi_pitch = dest_pitch * 4;
    bufp = src_buffer + y1 * 320 + x1;
    screenp = (byte *) dest_buffer + (y1 * dest_pitch + x1) * 4;
    screenp2 = screenp + dest_pitch;
    screenp3 = screenp + dest_pitch * 2;
    screenp4 = screenp + dest_pitch * 3;

    for (y=y1; y<y2; ++y)
    {
        byte *sp, *sp2, *sp3, *sp4, *bp;
        sp = screenp;
        sp2 = screenp2;
        sp3 = screenp3;
        sp4 = screenp4;
        bp = bufp;

        for (x=x1; x<x2; ++x)
        {
            *sp++ = *bp; *sp++ = *bp; *sp++ = *bp; *sp++ = *bp;
            *sp2++ = *bp; *sp2++ = *bp; *sp2++ = *bp; *sp2++ = *bp;
            *sp3++ = *bp; *sp3++ = *bp; *sp3++ = *bp; *sp3++ = *bp;
            *sp4++ = *bp; *sp4++ = *bp; *sp4++ = *bp; *sp4++ = *bp;
            ++bp;
        }
        screenp += multi_pitch;
        screenp2 += multi_pitch;
        screenp3 += multi_pitch;
        screenp4 += multi_pitch;
        bufp += 320;
    }

    return true;
}

screen_mode_t mode_scale_4x = {
    320 * 4, 200 * 4,
    ((void*)0),
    I_Scale4x,
    false,
};



static boolean I_Scale5x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp, *screenp2, *screenp3, *screenp4, *screenp5;
    int x, y;
    int multi_pitch;

    multi_pitch = dest_pitch * 5;
    bufp = src_buffer + y1 * 320 + x1;
    screenp = (byte *) dest_buffer + (y1 * dest_pitch + x1) * 5;
    screenp2 = screenp + dest_pitch;
    screenp3 = screenp + dest_pitch * 2;
    screenp4 = screenp + dest_pitch * 3;
    screenp5 = screenp + dest_pitch * 4;

    for (y=y1; y<y2; ++y)
    {
        byte *sp, *sp2, *sp3, *sp4, *sp5, *bp;
        sp = screenp;
        sp2 = screenp2;
        sp3 = screenp3;
        sp4 = screenp4;
        sp5 = screenp5;
        bp = bufp;

        for (x=x1; x<x2; ++x)
        {
            *sp++ = *bp; *sp++ = *bp; *sp++ = *bp; *sp++ = *bp; *sp++ = *bp;
            *sp2++ = *bp; *sp2++ = *bp; *sp2++ = *bp; *sp2++ = *bp; *sp2++ = *bp;
            *sp3++ = *bp; *sp3++ = *bp; *sp3++ = *bp; *sp3++ = *bp; *sp3++ = *bp;
            *sp4++ = *bp; *sp4++ = *bp; *sp4++ = *bp; *sp4++ = *bp; *sp4++ = *bp;
            *sp5++ = *bp; *sp5++ = *bp; *sp5++ = *bp; *sp5++ = *bp; *sp5++ = *bp;
            ++bp;
        }
        screenp += multi_pitch;
        screenp2 += multi_pitch;
        screenp3 += multi_pitch;
        screenp4 += multi_pitch;
        screenp5 += multi_pitch;
        bufp += 320;
    }

    return true;
}

screen_mode_t mode_scale_5x = {
    320 * 5, 200 * 5,
    ((void*)0),
    I_Scale5x,
    false,
};





static int FindNearestColor(byte *palette, int r, int g, int b)
{
    byte *col;
    int best;
    int best_diff;
    int diff;
    int i;

    best = 0;
    best_diff = 2147483647;

    for (i=0; i<256; ++i)
    {
        col = palette + i * 3;
        diff = (r - col[0]) * (r - col[0])
             + (g - col[1]) * (g - col[1])
             + (b - col[2]) * (b - col[2]);

        if (diff == 0)
        {
            return i;
        }
        else if (diff < best_diff)
        {
            best = i;
            best_diff = diff;
        }
    }

    return best;
}






static byte *GenerateStretchTable(byte *palette, int pct)
{
    byte *result;
    int x, y;
    int r, g, b;
    byte *col1;
    byte *col2;

    result = Z_Malloc(256 * 256, PU_STATIC, ((void*)0));

    for (x=0; x<256; ++x)
    {
        for (y=0; y<256; ++y)
        {
            col1 = palette + x * 3;
            col2 = palette + y * 3;
            r = (((int) col1[0]) * pct + ((int) col2[0]) * (100 - pct)) / 100;
            g = (((int) col1[1]) * pct + ((int) col2[1]) * (100 - pct)) / 100;
            b = (((int) col1[2]) * pct + ((int) col2[2]) * (100 - pct)) / 100;
            result[x * 256 + y] = FindNearestColor(palette, r, g, b);
        }
    }

    return result;
}




static void I_InitStretchTables(byte *palette)
{
    if (stretch_tables[0] != ((void*)0))
    {
        return;
    }
    printf("I_InitStretchTables: Generating lookup tables..");
    fflush(__stdoutp);
    stretch_tables[0] = GenerateStretchTable(palette, 20);
    printf(".."); fflush(__stdoutp);
    stretch_tables[1] = GenerateStretchTable(palette, 40);
    puts("");
}



static void I_InitSquashTable(byte *palette)
{
    if (half_stretch_table != ((void*)0))
    {
        return;
    }

    printf("I_InitSquashTable: Generating lookup table..");
    fflush(__stdoutp);
    half_stretch_table = GenerateStretchTable(palette, 50);
    puts("");
}





void I_ResetScaleTables(byte *palette)
{
    if (stretch_tables[0] != ((void*)0))
    {
        Z_Free(stretch_tables[0]);
        Z_Free(stretch_tables[1]);

        printf("I_ResetScaleTables: Regenerating lookup tables..\n");
        stretch_tables[0] = GenerateStretchTable(palette, 20);
        stretch_tables[1] = GenerateStretchTable(palette, 40);
    }

    if (half_stretch_table != ((void*)0))
    {
        Z_Free(half_stretch_table);

        printf("I_ResetScaleTables: Regenerating lookup table..\n");

        half_stretch_table = GenerateStretchTable(palette, 50);
    }
}
static inline void WriteBlendedLine1x(byte *dest, byte *src1, byte *src2,
                               byte *stretch_table)
{
    int x;

    for (x=0; x<320; ++x)
    {
        *dest = stretch_table[*src1 * 256 + *src2];
        ++dest;
        ++src1;
        ++src2;
    }
}



static boolean I_Stretch1x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp;
    int y;



    if (x1 != 0 || y1 != 0 || x2 != 320 || y2 != 200)
    {
        return false;
    }



    bufp = src_buffer + y1 * 320 + x1;
    screenp = (byte *) dest_buffer + y1 * dest_pitch + x1;




    for (y=0; y<200; y += 5)
    {

        memcpy(screenp, bufp, 320);
        screenp += dest_pitch;


        WriteBlendedLine1x(screenp, bufp, bufp + 320, stretch_tables[0]);
        screenp += dest_pitch; bufp += 320;


        WriteBlendedLine1x(screenp, bufp, bufp + 320, stretch_tables[1]);
        screenp += dest_pitch; bufp += 320;


        WriteBlendedLine1x(screenp, bufp + 320, bufp, stretch_tables[1]);
        screenp += dest_pitch; bufp += 320;


        WriteBlendedLine1x(screenp, bufp + 320, bufp, stretch_tables[0]);
        screenp += dest_pitch; bufp += 320;


        memcpy(screenp, bufp, 320);
        screenp += dest_pitch; bufp += 320;
    }

    return true;
}

screen_mode_t mode_stretch_1x = {
    320, 240,
    I_InitStretchTables,
    I_Stretch1x,
    true,
};

static inline void WriteLine2x(byte *dest, byte *src)
{
    int x;

    for (x=0; x<320; ++x)
    {
        dest[0] = *src;
        dest[1] = *src;
        dest += 2;
        ++src;
    }
}

static inline void WriteBlendedLine2x(byte *dest, byte *src1, byte *src2,
                               byte *stretch_table)
{
    int x;
    int val;

    for (x=0; x<320; ++x)
    {
        val = stretch_table[*src1 * 256 + *src2];
        dest[0] = val;
        dest[1] = val;
        dest += 2;
        ++src1;
        ++src2;
    }
}



static boolean I_Stretch2x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp;
    int y;



    if (x1 != 0 || y1 != 0 || x2 != 320 || y2 != 200)
    {
        return false;
    }



    bufp = src_buffer + y1 * 320 + x1;
    screenp = (byte *) dest_buffer + y1 * dest_pitch + x1;




    for (y=0; y<200; y += 5)
    {

        WriteLine2x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine2x(screenp, bufp);
        screenp += dest_pitch;


        WriteBlendedLine2x(screenp, bufp, bufp + 320, stretch_tables[1]);
        screenp += dest_pitch; bufp += 320;


        WriteLine2x(screenp, bufp);
        screenp += dest_pitch;


        WriteBlendedLine2x(screenp, bufp + 320, bufp, stretch_tables[0]);
        screenp += dest_pitch; bufp += 320;


        WriteLine2x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine2x(screenp, bufp);
        screenp += dest_pitch;


        WriteBlendedLine2x(screenp, bufp, bufp + 320, stretch_tables[0]);
        screenp += dest_pitch; bufp += 320;


        WriteLine2x(screenp, bufp);
        screenp += dest_pitch;


        WriteBlendedLine2x(screenp, bufp + 320, bufp, stretch_tables[1]);
        screenp += dest_pitch; bufp += 320;


        WriteLine2x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine2x(screenp, bufp);
        screenp += dest_pitch; bufp += 320;
    }

    return true;
}

screen_mode_t mode_stretch_2x = {
    320 * 2, 240 * 2,
    I_InitStretchTables,
    I_Stretch2x,
    false,
};

static inline void WriteLine3x(byte *dest, byte *src)
{
    int x;

    for (x=0; x<320; ++x)
    {
        dest[0] = *src;
        dest[1] = *src;
        dest[2] = *src;
        dest += 3;
        ++src;
    }
}

static inline void WriteBlendedLine3x(byte *dest, byte *src1, byte *src2,
                               byte *stretch_table)
{
    int x;
    int val;

    for (x=0; x<320; ++x)
    {
        val = stretch_table[*src1 * 256 + *src2];
        dest[0] = val;
        dest[1] = val;
        dest[2] = val;
        dest += 3;
        ++src1;
        ++src2;
    }
}



static boolean I_Stretch3x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp;
    int y;



    if (x1 != 0 || y1 != 0 || x2 != 320 || y2 != 200)
    {
        return false;
    }



    bufp = src_buffer + y1 * 320 + x1;
    screenp = (byte *) dest_buffer + y1 * dest_pitch + x1;




    for (y=0; y<200; y += 5)
    {

        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteBlendedLine3x(screenp, bufp + 320, bufp, stretch_tables[1]);
        screenp += dest_pitch; bufp += 320;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteBlendedLine3x(screenp, bufp, bufp + 320, stretch_tables[0]);
        screenp += dest_pitch; bufp += 320;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteBlendedLine3x(screenp, bufp + 320, bufp, stretch_tables[0]);
        screenp += dest_pitch; bufp += 320;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteBlendedLine3x(screenp, bufp, bufp + 320, stretch_tables[1]);
        screenp += dest_pitch; bufp += 320;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine3x(screenp, bufp);
        screenp += dest_pitch; bufp += 320;
    }

    return true;
}

screen_mode_t mode_stretch_3x = {
    320 * 3, 240 * 3,
    I_InitStretchTables,
    I_Stretch3x,
    false,
};

static inline void WriteLine4x(byte *dest, byte *src)
{
    int x;

    for (x=0; x<320; ++x)
    {
        dest[0] = *src;
        dest[1] = *src;
        dest[2] = *src;
        dest[3] = *src;
        dest += 4;
        ++src;
    }
}

static inline void WriteBlendedLine4x(byte *dest, byte *src1, byte *src2,
                               byte *stretch_table)
{
    int x;
    int val;

    for (x=0; x<320; ++x)
    {
        val = stretch_table[*src1 * 256 + *src2];
        dest[0] = val;
        dest[1] = val;
        dest[2] = val;
        dest[3] = val;
        dest += 4;
        ++src1;
        ++src2;
    }
}



static boolean I_Stretch4x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp;
    int y;



    if (x1 != 0 || y1 != 0 || x2 != 320 || y2 != 200)
    {
        return false;
    }



    bufp = src_buffer + y1 * 320 + x1;
    screenp = (byte *) dest_buffer + y1 * dest_pitch + x1;




    for (y=0; y<200; y += 5)
    {

        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteBlendedLine4x(screenp, bufp + 320, bufp, stretch_tables[0]);
        screenp += dest_pitch; bufp += 320;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteBlendedLine4x(screenp, bufp + 320, bufp, stretch_tables[1]);
        screenp += dest_pitch; bufp += 320;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteBlendedLine4x(screenp, bufp, bufp + 320, stretch_tables[1]);
        screenp += dest_pitch; bufp += 320;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteBlendedLine4x(screenp, bufp, bufp + 320, stretch_tables[0]);
        screenp += dest_pitch; bufp += 320;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine4x(screenp, bufp);
        screenp += dest_pitch; bufp += 320;
    }

    return true;
}

screen_mode_t mode_stretch_4x = {
    320 * 4, 240 * 4,
    I_InitStretchTables,
    I_Stretch4x,
    false,
};

static inline void WriteLine5x(byte *dest, byte *src)
{
    int x;

    for (x=0; x<320; ++x)
    {
        dest[0] = *src;
        dest[1] = *src;
        dest[2] = *src;
        dest[3] = *src;
        dest[4] = *src;
        dest += 5;
        ++src;
    }
}



static boolean I_Stretch5x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp;
    int y;



    if (x1 != 0 || y1 != 0 || x2 != 320 || y2 != 200)
    {
        return false;
    }



    bufp = src_buffer + y1 * 320 + x1;
    screenp = (byte *) dest_buffer + y1 * dest_pitch + x1;




    for (y=0; y<200; y += 1)
    {

        WriteLine5x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine5x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine5x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine5x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine5x(screenp, bufp);
        screenp += dest_pitch;


        WriteLine5x(screenp, bufp);
        screenp += dest_pitch; bufp += 320;
    }




    if (M_CheckParm("-scanline") > 0)
    {
        screenp = (byte *) dest_buffer + 2 * dest_pitch;

        for (y=0; y<1198; y += 3)
        {
            memset(screenp, 0, 1600);

            screenp += dest_pitch * 3;
        }
    }

    return true;
}

screen_mode_t mode_stretch_5x = {
    320 * 5, 240 * 5,
    I_InitStretchTables,
    I_Stretch5x,
    false,
};
static inline void WriteSquashedLine1x(byte *dest, byte *src)
{
    int x;

    for (x=0; x<320; )
    {




        *dest++ = stretch_tables[0][src[1] * 256 + src[0]];



        *dest++ = stretch_tables[1][src[2] * 256 + src[1]];



        *dest++ = stretch_tables[1][src[2] * 256 + src[3]];



        *dest++ = stretch_tables[0][src[3] * 256 + src[4]];

        x += 5;
        src += 5;
    }
}



static boolean I_Squash1x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp;
    int y;



    if (x1 != 0 || y1 != 0 || x2 != 320 || y2 != 200)
    {
        return false;
    }

    bufp = src_buffer;
    screenp = (byte *) dest_buffer;

    for (y=0; y<200; ++y)
    {
        WriteSquashedLine1x(screenp, bufp);

        screenp += dest_pitch;
        bufp += 320;
    }

    return true;
}

screen_mode_t mode_squash_1x = {
    256, 200,
    I_InitStretchTables,
    I_Squash1x,
    true,
};
static inline void WriteSquashedLine2x(byte *dest, byte *src)
{
    byte *dest2;
    int x, c;

    dest2 = dest + dest_pitch;

    for (x=0; x<320; )
    {




        c = src[0];
        *dest++ = *dest2++ = c;;



        c = stretch_tables[1][src[1] * 256 + src[0]];
        *dest++ = *dest2++ = c;;



        c = src[1];
        *dest++ = *dest2++ = c;;



        c = stretch_tables[0][src[1] * 256 + src[2]];
        *dest++ = *dest2++ = c;;



        c = stretch_tables[0][src[3] * 256 + src[2]];
        *dest++ = *dest2++ = c;;



        c = src[3];
        *dest++ = *dest2++ = c;;



        c = stretch_tables[1][src[3] * 256 + src[4]];
        *dest++ = *dest2++ = c;;



        c = src[4];
        *dest++ = *dest2++ = c;;

        x += 5;
        src += 5;
    }
}



static boolean I_Squash2x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp;
    int y;



    if (x1 != 0 || y1 != 0 || x2 != 320 || y2 != 200)
    {
        return false;
    }

    bufp = src_buffer;
    screenp = (byte *) dest_buffer;

    for (y=0; y<200; ++y)
    {
        WriteSquashedLine2x(screenp, bufp);

        screenp += dest_pitch * 2;
        bufp += 320;
    }

    return true;
}

screen_mode_t mode_squash_2x = {
    256 * 2, 200 * 2,
    I_InitStretchTables,
    I_Squash2x,
    false,
};





static inline void WriteSquashedLine3x(byte *dest, byte *src)
{
    byte *dest2, *dest3;
    int x, c;

    dest2 = dest + dest_pitch;
    dest3 = dest + dest_pitch * 2;

    for (x=0; x<320; )
    {




        c = src[0];

        *dest++ = *dest2++ = *dest3++ = c;
        *dest++ = *dest2++ = *dest3++ = c;



        c = half_stretch_table[src[0] * 256 + src[1]];

        *dest++ = *dest2++ = *dest3++ = c;



        c = src[1];

        *dest++ = *dest2++ = *dest3++ = c;
        *dest++ = *dest2++ = *dest3++ = c;

        x += 2;
        src += 2;
    }
}
static boolean I_Squash3x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp;
    int y;



    if (x1 != 0 || y1 != 0 || x2 != 320 || y2 != 200)
    {
        return false;
    }

    bufp = src_buffer;
    screenp = (byte *) dest_buffer;

    for (y=0; y<200; ++y)
    {
        WriteSquashedLine3x(screenp, bufp);

        screenp += dest_pitch * 3;
        bufp += 320;
    }

    return true;
}

screen_mode_t mode_squash_3x = {
    800, 600,
    I_InitSquashTable,
    I_Squash3x,
    false,
};




static inline void WriteSquashedLine4x(byte *dest, byte *src)
{
    int x;
    int c;
    byte *dest2, *dest3, *dest4;

    dest2 = dest + dest_pitch;
    dest3 = dest + dest_pitch * 2;
    dest4 = dest + dest_pitch * 3;

    for (x=0; x<320; )
    {




        c = src[0];
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;



        c = stretch_tables[0][src[0] * 256 + src[1]];
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;



        c = src[1];
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;



        c = stretch_tables[1][src[1] * 256 + src[2]];
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;



        c = src[2];
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;



        c = stretch_tables[1][src[3] * 256 + src[2]];
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;



        c = src[3];
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;



        c = stretch_tables[0][src[4] * 256 + src[3]];
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;



        c = src[4];
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;
        *dest++ = *dest2++ = *dest3++ = *dest4++ = c;;

        x += 5;
        src += 5;
    }
}





static boolean I_Squash4x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp;
    int y;



    if (x1 != 0 || y1 != 0 || x2 != 320 || y2 != 200)
    {
        return false;
    }

    bufp = src_buffer;
    screenp = (byte *) dest_buffer;

    for (y=0; y<200; ++y)
    {
        WriteSquashedLine4x(screenp, bufp);

        screenp += dest_pitch * 4;
        bufp += 320;
    }

    return true;
}

screen_mode_t mode_squash_4x = {
    256 * 4, 200 * 4,
    I_InitStretchTables,
    I_Squash4x,
    false,
};




static inline void WriteSquashedLine5x(byte *dest, byte *src)
{
    int x;
    int c;
    byte *dest2, *dest3, *dest4, *dest5;

    dest2 = dest + dest_pitch;
    dest3 = dest + dest_pitch * 2;
    dest4 = dest + dest_pitch * 3;
    dest5 = dest + dest_pitch * 4;

    for (x=0; x<320; ++x)
    {




        c = *src++;
        *dest++ = *dest2++ = *dest3++ = *dest4++ = *dest5++ = c;
        *dest++ = *dest2++ = *dest3++ = *dest4++ = *dest5++ = c;
        *dest++ = *dest2++ = *dest3++ = *dest4++ = *dest5++ = c;
        *dest++ = *dest2++ = *dest3++ = *dest4++ = *dest5++ = c;
    }
}





static boolean I_Squash5x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp;
    int y;



    if (x1 != 0 || y1 != 0 || x2 != 320 || y2 != 200)
    {
        return false;
    }

    bufp = src_buffer;
    screenp = (byte *) dest_buffer;

    for (y=0; y<200; ++y)
    {
        WriteSquashedLine5x(screenp, bufp);

        screenp += dest_pitch * 5;
        bufp += 320;
    }

    return true;
}

screen_mode_t mode_squash_5x = {
    256 * 5, 200 * 5,
    I_InitStretchTables,
    I_Squash5x,
    false,
};
int snd_samplerate = 44100;




int snd_cachesize = 64 * 1024 * 1024;




int snd_maxslicetime_ms = 28;



char *snd_musiccmd = "";



static sound_module_t *sound_module = ((void*)0);
static music_module_t *music_module = ((void*)0);

int snd_musicdevice = SNDDEVICE_SB;
int snd_sfxdevice = SNDDEVICE_SB;





static int snd_sbport = 0;
static int snd_sbirq = 0;
static int snd_sbdma = 0;
static int snd_mport = 0;



/* SDL2 sound module */

#define SDL_SND_CHANNELS 16
#define SDL_SND_RATE 44100

typedef struct {
    unsigned char *data;
    int len;
    int pos;
    int vol;
    int sep;
    int handle;
    sfxinfo_t *sfxinfo;
} sdl_channel_t;

sdl_channel_t sdl_channels[SDL_SND_CHANNELS];
static int sdl_sfx_started = 0;
static boolean sdl_use_prefix = true;
static int sdl_handle_counter = 1;

static boolean sdl_snd_init(boolean use_sfx_prefix) {
    int i;
    sdl_use_prefix = use_sfx_prefix;
    for (i = 0; i < SDL_SND_CHANNELS; i++) {
        sdl_channels[i].data = ((void*)0);
        sdl_channels[i].len = 0;
        sdl_channels[i].pos = 0;
    }
    sdl_sfx_started = 1;
    return true;
}

static void sdl_snd_shutdown(void) {
    sdl_sfx_started = 0;
}

static int sdl_snd_getsfxlumpnum(sfxinfo_t *sfxinfo) {
    char namebuf[16];
    if (sdl_use_prefix) {
        sprintf(namebuf, "ds%s", sfxinfo->name);
    } else {
        sprintf(namebuf, "%s", sfxinfo->name);
    }
    return W_GetNumForName(namebuf);
}

static void sdl_snd_update(void) {
}

static void sdl_snd_update_params(int channel, int vol, int sep) {
    if (channel >= 0 && channel < SDL_SND_CHANNELS) {
        sdl_channels[channel].vol = vol;
        sdl_channels[channel].sep = sep;
    }
}

static int sdl_snd_start(sfxinfo_t *sfxinfo, int channel, int vol, int sep) {
    unsigned char *lumpdata;
    int lumplen;
    int samplerate;
    int numsamples;

    if (channel < 0 || channel >= SDL_SND_CHANNELS)
        return -1;

    lumpdata = W_CacheLumpNum(sfxinfo->lumpnum, PU_STATIC);
    lumplen = W_LumpLength(sfxinfo->lumpnum);

    if (lumplen < 8)
        return -1;

    /* DMX sound lump: u16 format, u16 samplerate, u32 numsamples, then data */
    samplerate = lumpdata[2] | (lumpdata[3] << 8);
    numsamples = lumpdata[4] | (lumpdata[5] << 8) | (lumpdata[6] << 16) | (lumpdata[7] << 24);

    if (numsamples <= 0 || 8 + numsamples > lumplen)
        numsamples = lumplen - 8;
    if (numsamples <= 0)
        return -1;

    sdl_channels[channel].data = lumpdata + 8;
    sdl_channels[channel].len = numsamples;
    sdl_channels[channel].pos = 0;
    sdl_channels[channel].vol = vol;
    sdl_channels[channel].sep = sep;
    sdl_channels[channel].sfxinfo = sfxinfo;
    sdl_channels[channel].handle = sdl_handle_counter++;

    return sdl_channels[channel].handle;
}

static void sdl_snd_stop(int channel) {
    if (channel >= 0 && channel < SDL_SND_CHANNELS) {
        sdl_channels[channel].data = ((void*)0);
    }
}

static boolean sdl_snd_playing(int channel) {
    if (channel >= 0 && channel < SDL_SND_CHANNELS) {
        return sdl_channels[channel].data != ((void*)0);
    }
    return false;
}

static void sdl_snd_cachesounds(sfxinfo_t *sounds, int num_sounds) {
}

static snddevice_t sdl_snd_devices[] = { SNDDEVICE_SB };

sound_module_t sound_sdl_module = {
    sdl_snd_devices,
    1,
    sdl_snd_init,
    sdl_snd_shutdown,
    sdl_snd_getsfxlumpnum,
    sdl_snd_update,
    sdl_snd_update_params,
    sdl_snd_start,
    sdl_snd_stop,
    sdl_snd_playing,
    sdl_snd_cachesounds,
};

static sound_module_t *sound_modules[] =
{
    &sound_sdl_module,
    ((void*)0),
};



static boolean SndDeviceInList(snddevice_t device, snddevice_t *list,
                               int len)
{
    int i;

    for (i=0; i<len; ++i)
    {
        if (device == list[i])
        {
            return true;
        }
    }

    return false;
}




static void InitSfxModule(boolean use_sfx_prefix)
{
    int i;

    sound_module = ((void*)0);

    for (i=0; sound_modules[i] != ((void*)0); ++i)
    {



        if (SndDeviceInList(snd_sfxdevice,
                            sound_modules[i]->sound_devices,
                            sound_modules[i]->num_sound_devices))
        {


            if (sound_modules[i]->Init(use_sfx_prefix))
            {
                sound_module = sound_modules[i];
                return;
            }
        }
    }
}



static void InitMusicModule(void)
{



}







void I_InitSound(boolean use_sfx_prefix)
{
    boolean nosound, nosfx, nomusic;







    nosound = M_CheckParm("-nosound") > 0;







    nosfx = M_CheckParm("-nosfx") > 0;







    nomusic = M_CheckParm("-nomusic") > 0;



    if (!nosound && !screensaver_mode)
    {




        if (!nomusic
         && (snd_musicdevice == SNDDEVICE_GENMIDI
          || snd_musicdevice == SNDDEVICE_GUS))
        {

        }

        if (!nosfx)
        {
            InitSfxModule(use_sfx_prefix);
        }

        if (!nomusic)
        {
            InitMusicModule();
        }
    }

}

void I_ShutdownSound(void)
{
    if (sound_module != ((void*)0))
    {
        sound_module->Shutdown();
    }

    if (music_module != ((void*)0))
    {
        music_module->Shutdown();
    }
}

int I_GetSfxLumpNum(sfxinfo_t *sfxinfo)
{
    if (sound_module != ((void*)0))
    {
        return sound_module->GetSfxLumpNum(sfxinfo);
    }
    else
    {
        return 0;
    }
}

void I_UpdateSound(void)
{
    if (sound_module != ((void*)0))
    {
        sound_module->Update();
    }

    if (music_module != ((void*)0) && music_module->Poll != ((void*)0))
    {
        music_module->Poll();
    }
}

static void CheckVolumeSeparation(int *vol, int *sep)
{
    if (*sep < 0)
    {
        *sep = 0;
    }
    else if (*sep > 254)
    {
        *sep = 254;
    }

    if (*vol < 0)
    {
        *vol = 0;
    }
    else if (*vol > 127)
    {
        *vol = 127;
    }
}

void I_UpdateSoundParams(int channel, int vol, int sep)
{
    if (sound_module != ((void*)0))
    {
        CheckVolumeSeparation(&vol, &sep);
        sound_module->UpdateSoundParams(channel, vol, sep);
    }
}

int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep)
{
    if (sound_module != ((void*)0))
    {
        CheckVolumeSeparation(&vol, &sep);
        return sound_module->StartSound(sfxinfo, channel, vol, sep);
    }
    else
    {
        return 0;
    }
}

void I_StopSound(int channel)
{
    if (sound_module != ((void*)0))
    {
        sound_module->StopSound(channel);
    }
}

boolean I_SoundIsPlaying(int channel)
{
    if (sound_module != ((void*)0))
    {
        return sound_module->SoundIsPlaying(channel);
    }
    else
    {
        return false;
    }
}

void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds)
{
    if (sound_module != ((void*)0) && sound_module->CacheSounds != ((void*)0))
    {
 sound_module->CacheSounds(sounds, num_sounds);
    }
}

void I_InitMusic(void)
{
    if(music_module != ((void*)0))
    {
        music_module->Init();
    }
}

void I_ShutdownMusic(void)
{

}

void I_SetMusicVolume(int volume)
{
    if (music_module != ((void*)0))
    {
        music_module->SetMusicVolume(volume);
    }
}

void I_PauseSong(void)
{
    if (music_module != ((void*)0))
    {
        music_module->PauseMusic();
    }
}

void I_ResumeSong(void)
{
    if (music_module != ((void*)0))
    {
        music_module->ResumeMusic();
    }
}

void *I_RegisterSong(void *data, int len)
{
    if (music_module != ((void*)0))
    {
        return music_module->RegisterSong(data, len);
    }
    else
    {
        return ((void*)0);
    }
}

void I_UnRegisterSong(void *handle)
{
    if (music_module != ((void*)0))
    {
        music_module->UnRegisterSong(handle);
    }
}

void I_PlaySong(void *handle, boolean looping)
{
    if (music_module != ((void*)0))
    {
        music_module->PlaySong(handle, looping);
    }
}

void I_StopSong(void)
{
    if (music_module != ((void*)0))
    {
        music_module->StopSong();
    }
}

boolean I_MusicIsPlaying(void)
{
    if (music_module != ((void*)0))
    {
        return music_module->MusicIsPlaying();
    }
    else
    {
        return false;
    }

}

void I_BindSoundVariables(void)
{
    extern int use_libsamplerate;
    extern float libsamplerate_scale;

    M_BindVariable("snd_musicdevice", &snd_musicdevice);
    M_BindVariable("snd_sfxdevice", &snd_sfxdevice);
    M_BindVariable("snd_sbport", &snd_sbport);
    M_BindVariable("snd_sbirq", &snd_sbirq);
    M_BindVariable("snd_sbdma", &snd_sbdma);
    M_BindVariable("snd_mport", &snd_mport);
    M_BindVariable("snd_maxslicetime_ms", &snd_maxslicetime_ms);
    M_BindVariable("snd_musiccmd", &snd_musiccmd);
    M_BindVariable("snd_samplerate", &snd_samplerate);
    M_BindVariable("snd_cachesize", &snd_cachesize);
}
typedef struct atexit_listentry_s atexit_listentry_t;

struct atexit_listentry_s
{
    atexit_func_t func;
    boolean run_on_error;
    atexit_listentry_t *next;
};

static atexit_listentry_t *exit_funcs = ((void*)0);

void I_AtExit(atexit_func_t func, boolean run_on_error)
{
    atexit_listentry_t *entry;

    entry = malloc(sizeof(*entry));

    entry->func = func;
    entry->run_on_error = run_on_error;
    entry->next = exit_funcs;
    exit_funcs = entry;
}



void I_Tactile(int on, int off, int total)
{
}





static byte *AutoAllocMemory(int *size, int default_ram, int min_ram)
{
    byte *zonemem;






    zonemem = ((void*)0);

    while (zonemem == ((void*)0))
    {


        if (default_ram < min_ram)
        {
            I_Error("Unable to allocate %i MiB of RAM for zone", default_ram);
        }



        *size = default_ram * 1024 * 1024;

        zonemem = malloc(*size);




        if (zonemem == ((void*)0))
        {
            default_ram -= 1;
        }
    }

    return zonemem;
}

byte *I_ZoneBase (int *size)
{
    byte *zonemem;
    int min_ram, default_ram;
    int p;







    p = M_CheckParmWithArgs("-mb", 1);

    if (p > 0)
    {
        default_ram = atoi(myargv[p+1]);
        min_ram = default_ram;
    }
    else
    {
        default_ram = 32;
        min_ram = 32;
    }

    zonemem = AutoAllocMemory(size, default_ram, min_ram);

    printf("zone memory: %p, %x allocated for zone\n",
           zonemem, *size);

    return zonemem;
}

void I_PrintBanner(char *msg)
{
    int i;
    int spaces = 35 - (strlen(msg) / 2);

    for (i=0; i<spaces; ++i)
        putchar(' ');

    puts(msg);
}

void I_PrintDivider(void)
{
    int i;

    for (i=0; i<75; ++i)
    {
        putchar('=');
    }

    putchar('\n');
}

void I_PrintStartupBanner(char *gamedescription)
{
    I_PrintDivider();
    I_PrintBanner(gamedescription);
    I_PrintDivider();

    printf(
    " " "Doom Generic" " is free software, covered by the GNU General Public\n"
    " License.  There is NO warranty; not even for MERCHANTABILITY or FITNESS\n"
    " FOR A PARTICULAR PURPOSE. You are welcome to change and distribute\n"
    " copies under certain conditions. See the source for more information.\n");

    I_PrintDivider();
}







boolean I_ConsoleStdout(void)
{







 return 0;


}
void I_Quit (void)
{
    atexit_listentry_t *entry;



    entry = exit_funcs;

    while (entry != ((void*)0))
    {
        entry->func();
        entry = entry->next;
    }






}






static int ZenityAvailable(void)
{
    return system("/usr/bin/zenity" " --help >/dev/null 2>&1") == 0;
}




static char *EscapeShellString(char *string)
{
    char *result;
    char *r, *s;


    result = malloc(strlen(string) * 2 + 3);
    r = result;


    *r = '"';
    ++r;

    for (s = string; *s != '\0'; ++s)
    {
        if (strchr("$`\\!", *s) != ((void*)0))
        {
            *r = '\\';
            ++r;
        }

        *r = *s;
        ++r;
    }


    *r = '"';
    ++r;
    *r = '\0';

    return result;
}



static int ZenityErrorBox(char *message)
{
    int result;
    char *escaped_message;
    char *errorboxpath;
    static size_t errorboxpath_size;

    if (!ZenityAvailable())
    {
        return 0;
    }

    escaped_message = EscapeShellString(message);

    errorboxpath_size = strlen("/usr/bin/zenity") + strlen(escaped_message) + 19;
    errorboxpath = malloc(errorboxpath_size);
    M_snprintf(errorboxpath, errorboxpath_size, "%s --error --text=%s",
               "/usr/bin/zenity", escaped_message);

    result = system(errorboxpath);

    free(errorboxpath);
    free(escaped_message);

    return result;
}
static boolean already_quitting = false;

void I_Error (char *error, ...)
{
    char msgbuf[512];
    va_list argptr;
    atexit_listentry_t *entry;
    boolean exit_gui_popup;

    if (already_quitting)
    {
        fprintf(__stderrp, "Warning: recursive call to I_Error detected.\n");



    }
    else
    {
        already_quitting = true;
    }


    __builtin_va_start(argptr, error);

    vfprintf(__stderrp, error, argptr);
    fprintf(__stderrp, "\n\n");
    __builtin_va_end(argptr);
    fflush(__stderrp);


    __builtin_va_start(argptr, error);
    memset(msgbuf, 0, sizeof(msgbuf));
    M_vsnprintf(msgbuf, sizeof(msgbuf), error, argptr);
    __builtin_va_end(argptr);



    entry = exit_funcs;

    while (entry != ((void*)0))
    {
        if (entry->run_on_error)
        {
            entry->func();
        }

        entry = entry->next;
    }

    exit_gui_popup = !M_ParmExists("-nogui");




    if (exit_gui_popup && !I_ConsoleStdout())
    {
        ZenityErrorBox(msgbuf);
    }
    exit(-1);

}
static const unsigned char mem_dump_dos622[10] = {
  0x57, 0x92, 0x19, 0x00, 0xF4, 0x06, 0x70, 0x00, 0x16, 0x00};
static const unsigned char mem_dump_win98[10] = {
  0x9E, 0x0F, 0xC9, 0x00, 0x65, 0x04, 0x70, 0x00, 0x16, 0x00};
static const unsigned char mem_dump_dosbox[10] = {
  0x00, 0x00, 0x00, 0xF1, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00};
static unsigned char mem_dump_custom[10];

static const unsigned char *dos_mem_dump = mem_dump_dos622;

boolean I_GetMemoryValue(unsigned int offset, void *value, int size)
{
    static boolean firsttime = true;

    if (firsttime)
    {
        int p, i, val;

        firsttime = false;
        i = 0;
        p = M_CheckParmWithArgs("-setmem", 1);

        if (p > 0)
        {
            if (!strcasecmp(myargv[p + 1], "dos622"))
            {
                dos_mem_dump = mem_dump_dos622;
            }
            if (!strcasecmp(myargv[p + 1], "dos71"))
            {
                dos_mem_dump = mem_dump_win98;
            }
            else if (!strcasecmp(myargv[p + 1], "dosbox"))
            {
                dos_mem_dump = mem_dump_dosbox;
            }
            else
            {
                for (i = 0; i < 10; ++i)
                {
                    ++p;

                    if (p >= myargc || myargv[p][0] == '-')
                    {
                        break;
                    }

                    M_StrToInt(myargv[p], &val);
                    mem_dump_custom[i++] = (unsigned char) val;
                }

                dos_mem_dump = mem_dump_custom;
            }
        }
    }

    switch (size)
    {
    case 1:
        *((unsigned char *) value) = dos_mem_dump[offset];
        return true;
    case 2:
        *((unsigned short *) value) = dos_mem_dump[offset]
                                    | (dos_mem_dump[offset + 1] << 8);
        return true;
    case 4:
        *((unsigned int *) value) = dos_mem_dump[offset]
                                  | (dos_mem_dump[offset + 1] << 8)
                                  | (dos_mem_dump[offset + 2] << 16)
                                  | (dos_mem_dump[offset + 3] << 24);
        return true;
    }

    return false;
}
typedef uint32_t pixel_t;




extern pixel_t* DG_ScreenBuffer;





void doomgeneric_Create(int argc, char **argv);
void doomgeneric_Tick();



void DG_Init();
void DG_DrawFrame();
void DG_SleepMs(uint32_t ms);
uint32_t DG_GetTicksMs();
int DG_GetKey(int* pressed, unsigned char* key);
void DG_SetWindowTitle(const char * title);
static uint32_t basetime = 0;


int I_GetTicks(void)
{
 return DG_GetTicksMs();
}

int I_GetTime (void)
{
    uint32_t ticks;

    ticks = I_GetTicks();

    if (basetime == 0)
        basetime = ticks;

    ticks -= basetime;

    return (ticks * 35) / 1000;
}






int I_GetTimeMS(void)
{
    uint32_t ticks;

    ticks = I_GetTicks();

    if (basetime == 0)
        basetime = ticks;

    return ticks - basetime;
}



void I_Sleep(int ms)
{



 DG_SleepMs(ms);
}

void I_WaitVBL(int count)
{

}


void I_InitTimer(void)
{



}
typedef struct _MEMFILE MEMFILE;

typedef enum
{
 MEM_SEEK_SET,
 MEM_SEEK_CUR,
 MEM_SEEK_END,
} mem_rel_t;

MEMFILE *mem_fopen_read(void *buf, size_t buflen);
size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream);
MEMFILE *mem_fopen_write(void);
size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream);
void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen);
void mem_fclose(MEMFILE *stream);
long mem_ftell(MEMFILE *stream);
int mem_fseek(MEMFILE *stream, signed long offset, mem_rel_t whence);



typedef enum {
 MODE_READ,
 MODE_WRITE,
} memfile_mode_t;

struct _MEMFILE {
 unsigned char *buf;
 size_t buflen;
 size_t alloced;
 unsigned int position;
 memfile_mode_t mode;
};



MEMFILE *mem_fopen_read(void *buf, size_t buflen)
{
 MEMFILE *file;

 file = Z_Malloc(sizeof(MEMFILE), PU_STATIC, 0);

 file->buf = (unsigned char *) buf;
 file->buflen = buflen;
 file->position = 0;
 file->mode = MODE_READ;

 return file;
}



size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream)
{
 size_t items;

 if (stream->mode != MODE_READ)
 {
  printf("not a read stream\n");
  return -1;
 }



 items = nmemb;

 if (items * size > stream->buflen - stream->position)
 {
  items = (stream->buflen - stream->position) / size;
 }



 memcpy(buf, stream->buf + stream->position, items * size);



 stream->position += items * size;

 return items;
}



MEMFILE *mem_fopen_write(void)
{
 MEMFILE *file;

 file = Z_Malloc(sizeof(MEMFILE), PU_STATIC, 0);

 file->alloced = 1024;
 file->buf = Z_Malloc(file->alloced, PU_STATIC, 0);
 file->buflen = 0;
 file->position = 0;
 file->mode = MODE_WRITE;

 return file;
}



size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream)
{
 size_t bytes;

 if (stream->mode != MODE_WRITE)
 {
  return -1;
 }




 bytes = size * nmemb;

 while (bytes > stream->alloced - stream->position)
 {
  unsigned char *newbuf;

  newbuf = Z_Malloc(stream->alloced * 2, PU_STATIC, 0);
  memcpy(newbuf, stream->buf, stream->alloced);
  Z_Free(stream->buf);
  stream->buf = newbuf;
  stream->alloced *= 2;
 }



 memcpy(stream->buf + stream->position, ptr, bytes);
 stream->position += bytes;

 if (stream->position > stream->buflen)
  stream->buflen = stream->position;

 return nmemb;
}

void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen)
{
 *buf = stream->buf;
 *buflen = stream->buflen;
}

void mem_fclose(MEMFILE *stream)
{
 if (stream->mode == MODE_WRITE)
 {
  Z_Free(stream->buf);
 }

 Z_Free(stream);
}

long mem_ftell(MEMFILE *stream)
{
 return stream->position;
}

int mem_fseek(MEMFILE *stream, signed long position, mem_rel_t whence)
{
 unsigned int newpos;

 switch (whence)
 {
  case MEM_SEEK_SET:
   newpos = (int) position;
   break;

  case MEM_SEEK_CUR:
   newpos = (int) (stream->position + position);
   break;

  case MEM_SEEK_END:
   newpos = (int) (stream->buflen + position);
   break;
  default:
   return -1;
 }

 if (newpos < stream->buflen)
 {
  stream->position = newpos;
  return 0;
 }
 else
 {
  printf("Error seeking to %i\n", newpos);
  return -1;
 }
}
int myargc;
char** myargv;
int M_CheckParmWithArgs(char *check, int num_args)
{
    int i;

    for (i = 1; i < myargc - num_args; i++)
    {
 if (!strcasecmp(check, myargv[i]))
     return i;
    }

    return 0;
}
boolean M_ParmExists(char *check)
{
    return M_CheckParm(check) != 0;
}

int M_CheckParm(char *check)
{
    return M_CheckParmWithArgs(check, 0);
}



static void LoadResponseFile(int argv_index)
{
}





void M_FindResponseFile(void)
{
    int i;

    for (i = 1; i < myargc; i++)
    {
        if (myargv[i][0] == '@')
        {
            LoadResponseFile(i);
        }
    }
}



char *M_GetExecutableName(void)
{
    char *sep;

    sep = strrchr(myargv[0], '/');

    if (sep == ((void*)0))
    {
        return myargv[0];
    }
    else
    {
        return sep + 1;
    }
}
enum
{
    BOXTOP,
    BOXBOTTOM,
    BOXLEFT,
    BOXRIGHT
};


void M_ClearBox (fixed_t* box);

void
M_AddToBox
( fixed_t* box,
  fixed_t x,
  fixed_t y );




void M_ClearBox (fixed_t *box)
{
    box[BOXTOP] = box[BOXRIGHT] = (-2147483647-1);
    box[BOXBOTTOM] = box[BOXLEFT] = 2147483647;
}

void
M_AddToBox
( fixed_t* box,
  fixed_t x,
  fixed_t y )
{
    if (x<box[BOXLEFT])
 box[BOXLEFT] = x;
    else if (x>box[BOXRIGHT])
 box[BOXRIGHT] = x;
    if (y<box[BOXBOTTOM])
 box[BOXBOTTOM] = y;
    else if (y>box[BOXTOP])
 box[BOXTOP] = y;
}
int
cht_CheckCheat
( cheatseq_t* cht,
  char key )
{



    if (cht->parameter_chars > 0 && strlen(cht->sequence) < cht->sequence_len)
        return false;

    if (cht->chars_read < strlen(cht->sequence))
    {




        if (key == cht->sequence[cht->chars_read])
            ++cht->chars_read;
        else
            cht->chars_read = 0;

        cht->param_chars_read = 0;
    }
    else if (cht->param_chars_read < cht->parameter_chars)
    {



        cht->parameter_buf[cht->param_chars_read] = key;

        ++cht->param_chars_read;
    }

    if (cht->chars_read >= strlen(cht->sequence)
     && cht->param_chars_read >= cht->parameter_chars)
    {
        cht->chars_read = cht->param_chars_read = 0;

        return true;
    }



    return false;
}

void
cht_GetParam
( cheatseq_t* cht,
  char* buffer )
{
    memcpy(buffer, cht->parameter_buf, cht->parameter_chars);
}
char *configdir;



static char *default_main_config;
static char *default_extra_config;

typedef enum
{
    DEFAULT_INT,
    DEFAULT_INT_HEX,
    DEFAULT_STRING,
    DEFAULT_FLOAT,
    DEFAULT_KEY,
} default_type_t;

typedef struct
{

    char *name;


    void *location;


    default_type_t type;




    int untranslated;





    int original_translated;



    boolean bound;
} default_t;

typedef struct
{
    default_t *defaults;
    int numdefaults;
    char *filename;
} default_collection_t;
static default_t doom_defaults_list[] =
{
    { "mouse_sensitivity", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "sfx_volume", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "music_volume", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "show_talk", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "voice_volume", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "show_messages", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "key_right", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_left", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_up", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_down", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_strafeleft", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_straferight", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_useHealth", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_jump", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_flyup", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_flydown", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_flycenter", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_lookup", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_lookdown", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_lookcenter", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_invquery", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_mission", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_invPop", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_invKey", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_invHome", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_invEnd", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_invleft", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_invright", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_invLeft", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_invRight", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_useartifact", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_invUse", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_invDrop", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_lookUp", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_lookDown", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_fire", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_use", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_strafe", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_speed", ((void*)0), DEFAULT_KEY, 0, 0, false },






    { "use_mouse", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "mouseb_fire", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "mouseb_strafe", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "mouseb_forward", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "mouseb_jump", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "use_joystick", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "joyb_fire", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "joyb_strafe", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "joyb_use", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "joyb_speed", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "joyb_jump", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "screenblocks", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "screensize", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "detaillevel", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "snd_channels", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "snd_musicdevice", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "snd_sfxdevice", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "snd_sbport", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "snd_sbirq", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "snd_sbdma", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "snd_mport", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "usegamma", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "savedir", ((void*)0), DEFAULT_STRING, 0, 0, false },
    { "messageson", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "back_flat", ((void*)0), DEFAULT_STRING, 0, 0, false },







    { "nickname", ((void*)0), DEFAULT_STRING, 0, 0, false },





    { "chatmacro0", ((void*)0), DEFAULT_STRING, 0, 0, false },





    { "chatmacro1", ((void*)0), DEFAULT_STRING, 0, 0, false },





    { "chatmacro2", ((void*)0), DEFAULT_STRING, 0, 0, false },





    { "chatmacro3", ((void*)0), DEFAULT_STRING, 0, 0, false },





    { "chatmacro4", ((void*)0), DEFAULT_STRING, 0, 0, false },





    { "chatmacro5", ((void*)0), DEFAULT_STRING, 0, 0, false },





    { "chatmacro6", ((void*)0), DEFAULT_STRING, 0, 0, false },





    { "chatmacro7", ((void*)0), DEFAULT_STRING, 0, 0, false },





    { "chatmacro8", ((void*)0), DEFAULT_STRING, 0, 0, false },





    { "chatmacro9", ((void*)0), DEFAULT_STRING, 0, 0, false },







    { "comport", ((void*)0), DEFAULT_INT, 0, 0, false },
};

static default_collection_t doom_defaults =
{
    doom_defaults_list,
    76,
    ((void*)0),
};



static default_t extra_defaults_list[] =
{






    { "graphical_startup", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "autoadjust_video_settings", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "fullscreen", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "aspect_ratio_correct", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "startup_delay", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "screen_width", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "screen_height", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "screen_bpp", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "grabmouse", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "novert", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "mouse_acceleration", ((void*)0), DEFAULT_FLOAT, 0, 0, false },







    { "mouse_threshold", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "snd_samplerate", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "snd_cachesize", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "snd_maxslicetime_ms", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "snd_musiccmd", ((void*)0), DEFAULT_STRING, 0, 0, false },






    { "opl_io_port", ((void*)0), DEFAULT_INT_HEX, 0, 0, false },
    { "show_endoom", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "png_screenshots", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "vanilla_savegame_limit", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "vanilla_demo_limit", ((void*)0), DEFAULT_INT, 0, 0, false },







    { "vanilla_keyboard_mapping", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "video_driver", ((void*)0), DEFAULT_STRING, 0, 0, false },







    { "window_position", ((void*)0), DEFAULT_STRING, 0, 0, false },
    { "joystick_index", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "joystick_x_axis", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "joystick_x_invert", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "joystick_y_axis", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "joystick_y_invert", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "joystick_strafe_axis", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "joystick_strafe_invert", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "joystick_physical_button0", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "joystick_physical_button1", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "joystick_physical_button2", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "joystick_physical_button3", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "joystick_physical_button4", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "joystick_physical_button5", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "joystick_physical_button6", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "joystick_physical_button7", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "joystick_physical_button8", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "joystick_physical_button9", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "joyb_strafeleft", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "joyb_straferight", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "joyb_menu_activate", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "joyb_prevweapon", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "joyb_nextweapon", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "mouseb_strafeleft", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "mouseb_straferight", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "mouseb_use", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "mouseb_backward", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "mouseb_prevweapon", ((void*)0), DEFAULT_INT, 0, 0, false },





    { "mouseb_nextweapon", ((void*)0), DEFAULT_INT, 0, 0, false },






    { "dclick_use", ((void*)0), DEFAULT_INT, 0, 0, false },
    { "key_pause", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_activate", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_up", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_down", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_left", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_right", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_back", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_forward", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_confirm", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_abort", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_help", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_save", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_load", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_volume", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_detail", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_qsave", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_endgame", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_messages", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_qload", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_quit", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_gamma", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_spy", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_incscreen", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_decscreen", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_menu_screenshot", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_map_toggle", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_map_north", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_map_south", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_map_east", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_map_west", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_map_zoomin", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_map_zoomout", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_map_maxzoom", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_map_follow", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_map_grid", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_map_mark", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_map_clearmark", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_weapon1", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_weapon2", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_weapon3", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_weapon4", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_weapon5", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_weapon6", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_weapon7", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_weapon8", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_prevweapon", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_nextweapon", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_arti_all", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_arti_health", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_arti_poisonbag", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_arti_blastradius", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_arti_teleport", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_arti_teleportother", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_arti_egg", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_arti_invulnerability", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_message_refresh", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_demo_quit", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_multi_msg", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_multi_msgplayer1", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_multi_msgplayer2", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_multi_msgplayer3", ((void*)0), DEFAULT_KEY, 0, 0, false },





    { "key_multi_msgplayer4", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_multi_msgplayer5", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_multi_msgplayer6", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_multi_msgplayer7", ((void*)0), DEFAULT_KEY, 0, 0, false },







    { "key_multi_msgplayer8", ((void*)0), DEFAULT_KEY, 0, 0, false },
};

static default_collection_t extra_defaults =
{
    extra_defaults_list,
    119,
    ((void*)0),
};



static default_t *SearchCollection(default_collection_t *collection, char *name)
{
    int i;

    for (i=0; i<collection->numdefaults; ++i)
    {
        if (!strcmp(name, collection->defaults[i].name))
        {
            return &collection->defaults[i];
        }
    }

    return ((void*)0);
}
static const int scantokey[128] =
{
    0 , 27, '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', 0x7f, 9,
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p', '[', ']', 13, (0x80+0x1d), 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', (0x80+0x36),'\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', (0x80+0x36),'*',
    (0x80+0x38), ' ', (0x80+0x3a),(0x80+0x3b), (0x80+0x3c), (0x80+0x3d), (0x80+0x3e), (0x80+0x3f),
    (0x80+0x40), (0x80+0x41), (0x80+0x42), (0x80+0x43), (0x80+0x44), 0xff,(0x80+0x46),(0x80+0x47),
    0xad,(0x80+0x49),0x2d,0xac,'5',0xae,'+',(0x80+0x4f),
    0xaf,(0x80+0x51),(0x80+0x52),(0x80+0x53),0, 0, 0, (0x80+0x57),
    (0x80+0x58), 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, (0x80+0x59), 0
};


static void SaveDefaultCollection(default_collection_t *collection)
{
}



static int ParseIntParameter(char *strparm)
{
    int parm;

    if (strparm[0] == '0' && strparm[1] == 'x')
        sscanf(strparm+2, "%x", &parm);
    else
        sscanf(strparm, "%i", &parm);

    return parm;
}

static void SetVariable(default_t *def, char *value)
{
    int intparm;



    switch (def->type)
    {
        case DEFAULT_STRING:
            * (char **) def->location = strdup(value);
            break;

        case DEFAULT_INT:
        case DEFAULT_INT_HEX:
            * (int *) def->location = ParseIntParameter(value);
            break;

        case DEFAULT_KEY:




            intparm = ParseIntParameter(value);
            def->untranslated = intparm;
            if (intparm >= 0 && intparm < 128)
            {
                intparm = scantokey[intparm];
            }
            else
            {
                intparm = 0;
            }

            def->original_translated = intparm;
            * (int *) def->location = intparm;
            break;

        case DEFAULT_FLOAT:
            * (float *) def->location = (float) atof(value);
            break;
    }
}

static void LoadDefaultCollection(default_collection_t *collection)
{
}



void M_SetConfigFilenames(char *main_config, char *extra_config)
{
    default_main_config = main_config;
    default_extra_config = extra_config;
}





void M_SaveDefaults (void)
{
    SaveDefaultCollection(&doom_defaults);
    SaveDefaultCollection(&extra_defaults);
}





void M_SaveDefaultsAlternate(char *main, char *extra)
{
    char *orig_main;
    char *orig_extra;



    orig_main = doom_defaults.filename;
    orig_extra = extra_defaults.filename;

    doom_defaults.filename = main;
    extra_defaults.filename = extra;

    M_SaveDefaults();



    doom_defaults.filename = orig_main;
    extra_defaults.filename = orig_extra;
}





void M_LoadDefaults (void)
{
    int i;
    i = M_CheckParmWithArgs("-config", 1);

    if (i)
    {
 doom_defaults.filename = myargv[i+1];
 printf ("	default file: %s\n",doom_defaults.filename);
    }
    else
    {
        doom_defaults.filename
            = M_StringJoin(configdir, default_main_config, ((void*)0));
    }

    printf("saving config in %s\n", doom_defaults.filename);
    i = M_CheckParmWithArgs("-extraconfig", 1);

    if (i)
    {
        extra_defaults.filename = myargv[i+1];
        printf("        extra configuration file: %s\n",
               extra_defaults.filename);
    }
    else
    {
        extra_defaults.filename
            = M_StringJoin(configdir, default_extra_config, ((void*)0));
    }

    LoadDefaultCollection(&doom_defaults);
    LoadDefaultCollection(&extra_defaults);
}



static default_t *GetDefaultForName(char *name)
{
    default_t *result;



    result = SearchCollection(&doom_defaults, name);

    if (result == ((void*)0))
    {
        result = SearchCollection(&extra_defaults, name);
    }



    if (result == ((void*)0))
    {
        I_Error("Unknown configuration variable: '%s'", name);
    }

    return result;
}





void M_BindVariable(char *name, void *location)
{
    default_t *variable;

    variable = GetDefaultForName(name);

    variable->location = location;
    variable->bound = true;
}




boolean M_SetVariable(char *name, char *value)
{
    default_t *variable;

    variable = GetDefaultForName(name);

    if (variable == ((void*)0) || !variable->bound)
    {
        return false;
    }

    SetVariable(variable, value);

    return true;
}



int M_GetIntVariable(char *name)
{
    default_t *variable;

    variable = GetDefaultForName(name);

    if (variable == ((void*)0) || !variable->bound
     || (variable->type != DEFAULT_INT && variable->type != DEFAULT_INT_HEX))
    {
        return 0;
    }

    return *((int *) variable->location);
}

const char *M_GetStrVariable(char *name)
{
    default_t *variable;

    variable = GetDefaultForName(name);

    if (variable == ((void*)0) || !variable->bound
     || variable->type != DEFAULT_STRING)
    {
        return ((void*)0);
    }

    return *((const char **) variable->location);
}

float M_GetFloatVariable(char *name)
{
    default_t *variable;

    variable = GetDefaultForName(name);

    if (variable == ((void*)0) || !variable->bound
     || variable->type != DEFAULT_FLOAT)
    {
        return 0;
    }

    return *((float *) variable->location);
}




static char *GetDefaultConfigDir(void)
{
    char *result = (char *)malloc(2);
    result[0] = '.';
    result[1] = '\0';

    return result;
}
void M_SetConfigDir(char *dir)
{


    if (dir != ((void*)0))
    {
        configdir = dir;
    }
    else
    {
        configdir = GetDefaultConfigDir();
    }

    if (strcmp(configdir, "") != 0)
    {
        printf("Using %s for configuration and saves\n", configdir);
    }



    M_MakeDirectory(configdir);
}






char *M_GetSaveGameDir(char *iwadname)
{
    char *savegamedir;







    if (!strcmp(configdir, ""))
    {
     savegamedir = strdup("");
    }
    else
    {
        savegamedir = M_StringJoin(configdir, "/", ".savegame/", ((void*)0));

        M_MakeDirectory(savegamedir);

        printf ("Using %s for savegames\n", savegamedir);

    }

    return savegamedir;
}
int key_right = 0xae;
int key_left = 0xac;
int key_up = 0xad;
int key_down = 0xaf;
int key_strafeleft = 0xa0;
int key_straferight = 0xa1;
int key_fire = 0xa3;
int key_use = 0xa2;
int key_strafe = (0x80+0x38);
int key_speed = (0x80+0x36);





int key_flyup = (0x80+0x49);
int key_flydown = (0x80+0x52);
int key_flycenter = (0x80+0x47);

int key_lookup = (0x80+0x51);
int key_lookdown = (0x80+0x53);
int key_lookcenter = (0x80+0x4f);

int key_invleft = '[';
int key_invright = ']';
int key_useartifact = 13;





int key_jump = '/';

int key_arti_all = 0x7f;
int key_arti_health = '\\';
int key_arti_poisonbag = '0';
int key_arti_blastradius = '9';
int key_arti_teleport = '8';
int key_arti_teleportother = '7';
int key_arti_egg = '6';
int key_arti_invulnerability = '5';
int key_usehealth = 'h';
int key_invquery = 'q';
int key_mission = 'w';
int key_invpop = 'z';
int key_invkey = 'k';
int key_invhome = (0x80+0x47);
int key_invend = (0x80+0x4f);
int key_invuse = 13;
int key_invdrop = 0x7f;






int mousebfire = 0;
int mousebstrafe = 1;
int mousebforward = 2;

int mousebjump = -1;

int mousebstrafeleft = -1;
int mousebstraferight = -1;
int mousebbackward = -1;
int mousebuse = -1;

int mousebprevweapon = -1;
int mousebnextweapon = -1;


int key_message_refresh = 13;
int key_pause = 0xff;
int key_demo_quit = 'q';
int key_spy = (0x80+0x58);



int key_multi_msg = 't';
int key_multi_msgplayer[8];



int key_weapon1 = '1';
int key_weapon2 = '2';
int key_weapon3 = '3';
int key_weapon4 = '4';
int key_weapon5 = '5';
int key_weapon6 = '6';
int key_weapon7 = '7';
int key_weapon8 = '8';
int key_prevweapon = 0;
int key_nextweapon = 0;



int key_map_north = 0xad;
int key_map_south = 0xaf;
int key_map_east = 0xae;
int key_map_west = 0xac;
int key_map_zoomin = '=';
int key_map_zoomout = '-';
int key_map_toggle = 9;
int key_map_maxzoom = '0';
int key_map_follow = 'f';
int key_map_grid = 'g';
int key_map_mark = 'm';
int key_map_clearmark = 'c';



int key_menu_activate = 27;
int key_menu_up = 0xad;
int key_menu_down = 0xaf;
int key_menu_left = 0xac;
int key_menu_right = 0xae;
int key_menu_back = 0x7f;
int key_menu_forward = 13;
int key_menu_confirm = 'y';
int key_menu_abort = 'n';

int key_menu_help = (0x80+0x3b);
int key_menu_save = (0x80+0x3c);
int key_menu_load = (0x80+0x3d);
int key_menu_volume = (0x80+0x3e);
int key_menu_detail = (0x80+0x3f);
int key_menu_qsave = (0x80+0x40);
int key_menu_endgame = (0x80+0x41);
int key_menu_messages = (0x80+0x42);
int key_menu_qload = (0x80+0x43);
int key_menu_quit = (0x80+0x44);
int key_menu_gamma = (0x80+0x57);

int key_menu_incscreen = 0x3d;
int key_menu_decscreen = 0x2d;
int key_menu_screenshot = 0;





int joybfire = 0;
int joybstrafe = 1;
int joybuse = 3;
int joybspeed = 2;

int joybstrafeleft = -1;
int joybstraferight = -1;

int joybjump = -1;

int joybprevweapon = -1;
int joybnextweapon = -1;

int joybmenu = -1;




int dclick_use = 1;





void M_BindBaseControls(void)
{
    M_BindVariable("key_right", &key_right);
    M_BindVariable("key_left", &key_left);
    M_BindVariable("key_up", &key_up);
    M_BindVariable("key_down", &key_down);
    M_BindVariable("key_strafeleft", &key_strafeleft);
    M_BindVariable("key_straferight", &key_straferight);
    M_BindVariable("key_fire", &key_fire);
    M_BindVariable("key_use", &key_use);
    M_BindVariable("key_strafe", &key_strafe);
    M_BindVariable("key_speed", &key_speed);

    M_BindVariable("mouseb_fire", &mousebfire);
    M_BindVariable("mouseb_strafe", &mousebstrafe);
    M_BindVariable("mouseb_forward", &mousebforward);

    M_BindVariable("joyb_fire", &joybfire);
    M_BindVariable("joyb_strafe", &joybstrafe);
    M_BindVariable("joyb_use", &joybuse);
    M_BindVariable("joyb_speed", &joybspeed);

    M_BindVariable("joyb_menu_activate", &joybmenu);



    M_BindVariable("joyb_strafeleft", &joybstrafeleft);
    M_BindVariable("joyb_straferight", &joybstraferight);
    M_BindVariable("mouseb_strafeleft", &mousebstrafeleft);
    M_BindVariable("mouseb_straferight", &mousebstraferight);
    M_BindVariable("mouseb_use", &mousebuse);
    M_BindVariable("mouseb_backward", &mousebbackward);
    M_BindVariable("dclick_use", &dclick_use);
    M_BindVariable("key_pause", &key_pause);
    M_BindVariable("key_message_refresh", &key_message_refresh);
}

void M_BindHereticControls(void)
{
    M_BindVariable("key_flyup", &key_flyup);
    M_BindVariable("key_flydown", &key_flydown);
    M_BindVariable("key_flycenter", &key_flycenter);

    M_BindVariable("key_lookup", &key_lookup);
    M_BindVariable("key_lookdown", &key_lookdown);
    M_BindVariable("key_lookcenter", &key_lookcenter);

    M_BindVariable("key_invleft", &key_invleft);
    M_BindVariable("key_invright", &key_invright);
    M_BindVariable("key_useartifact", &key_useartifact);
}

void M_BindHexenControls(void)
{
    M_BindVariable("key_jump", &key_jump);
    M_BindVariable("mouseb_jump", &mousebjump);
    M_BindVariable("joyb_jump", &joybjump);

    M_BindVariable("key_arti_all", &key_arti_all);
    M_BindVariable("key_arti_health", &key_arti_health);
    M_BindVariable("key_arti_poisonbag", &key_arti_poisonbag);
    M_BindVariable("key_arti_blastradius", &key_arti_blastradius);
    M_BindVariable("key_arti_teleport", &key_arti_teleport);
    M_BindVariable("key_arti_teleportother", &key_arti_teleportother);
    M_BindVariable("key_arti_egg", &key_arti_egg);
    M_BindVariable("key_arti_invulnerability", &key_arti_invulnerability);
}

void M_BindStrifeControls(void)
{

    key_message_refresh = '/';


    key_jump = 'a';
    key_lookup = (0x80+0x49);
    key_lookdown = (0x80+0x51);
    key_invleft = (0x80+0x52);
    key_invright = (0x80+0x53);

    M_BindVariable("key_jump", &key_jump);
    M_BindVariable("key_lookUp", &key_lookup);
    M_BindVariable("key_lookDown", &key_lookdown);
    M_BindVariable("key_invLeft", &key_invleft);
    M_BindVariable("key_invRight", &key_invright);


    M_BindVariable("key_useHealth", &key_usehealth);
    M_BindVariable("key_invquery", &key_invquery);
    M_BindVariable("key_mission", &key_mission);
    M_BindVariable("key_invPop", &key_invpop);
    M_BindVariable("key_invKey", &key_invkey);
    M_BindVariable("key_invHome", &key_invhome);
    M_BindVariable("key_invEnd", &key_invend);
    M_BindVariable("key_invUse", &key_invuse);
    M_BindVariable("key_invDrop", &key_invdrop);



    M_BindVariable("mouseb_jump", &mousebjump);
    M_BindVariable("joyb_jump", &joybjump);
}

void M_BindWeaponControls(void)
{
    M_BindVariable("key_weapon1", &key_weapon1);
    M_BindVariable("key_weapon2", &key_weapon2);
    M_BindVariable("key_weapon3", &key_weapon3);
    M_BindVariable("key_weapon4", &key_weapon4);
    M_BindVariable("key_weapon5", &key_weapon5);
    M_BindVariable("key_weapon6", &key_weapon6);
    M_BindVariable("key_weapon7", &key_weapon7);
    M_BindVariable("key_weapon8", &key_weapon8);

    M_BindVariable("key_prevweapon", &key_prevweapon);
    M_BindVariable("key_nextweapon", &key_nextweapon);

    M_BindVariable("joyb_prevweapon", &joybprevweapon);
    M_BindVariable("joyb_nextweapon", &joybnextweapon);

    M_BindVariable("mouseb_prevweapon", &mousebprevweapon);
    M_BindVariable("mouseb_nextweapon", &mousebnextweapon);
}

void M_BindMapControls(void)
{
    M_BindVariable("key_map_north", &key_map_north);
    M_BindVariable("key_map_south", &key_map_south);
    M_BindVariable("key_map_east", &key_map_east);
    M_BindVariable("key_map_west", &key_map_west);
    M_BindVariable("key_map_zoomin", &key_map_zoomin);
    M_BindVariable("key_map_zoomout", &key_map_zoomout);
    M_BindVariable("key_map_toggle", &key_map_toggle);
    M_BindVariable("key_map_maxzoom", &key_map_maxzoom);
    M_BindVariable("key_map_follow", &key_map_follow);
    M_BindVariable("key_map_grid", &key_map_grid);
    M_BindVariable("key_map_mark", &key_map_mark);
    M_BindVariable("key_map_clearmark", &key_map_clearmark);
}

void M_BindMenuControls(void)
{
    M_BindVariable("key_menu_activate", &key_menu_activate);
    M_BindVariable("key_menu_up", &key_menu_up);
    M_BindVariable("key_menu_down", &key_menu_down);
    M_BindVariable("key_menu_left", &key_menu_left);
    M_BindVariable("key_menu_right", &key_menu_right);
    M_BindVariable("key_menu_back", &key_menu_back);
    M_BindVariable("key_menu_forward", &key_menu_forward);
    M_BindVariable("key_menu_confirm", &key_menu_confirm);
    M_BindVariable("key_menu_abort", &key_menu_abort);

    M_BindVariable("key_menu_help", &key_menu_help);
    M_BindVariable("key_menu_save", &key_menu_save);
    M_BindVariable("key_menu_load", &key_menu_load);
    M_BindVariable("key_menu_volume", &key_menu_volume);
    M_BindVariable("key_menu_detail", &key_menu_detail);
    M_BindVariable("key_menu_qsave", &key_menu_qsave);
    M_BindVariable("key_menu_endgame", &key_menu_endgame);
    M_BindVariable("key_menu_messages", &key_menu_messages);
    M_BindVariable("key_menu_qload", &key_menu_qload);
    M_BindVariable("key_menu_quit", &key_menu_quit);
    M_BindVariable("key_menu_gamma", &key_menu_gamma);

    M_BindVariable("key_menu_incscreen", &key_menu_incscreen);
    M_BindVariable("key_menu_decscreen", &key_menu_decscreen);
    M_BindVariable("key_menu_screenshot",&key_menu_screenshot);
    M_BindVariable("key_demo_quit", &key_demo_quit);
    M_BindVariable("key_spy", &key_spy);
}

void M_BindChatControls(unsigned int num_players)
{
    char name[32];
    unsigned int i;

    M_BindVariable("key_multi_msg", &key_multi_msg);

    for (i=0; i<num_players; ++i)
    {
        M_snprintf(name, sizeof(name), "key_multi_msgplayer%i", i + 1);
        M_BindVariable(name, &key_multi_msgplayer[i]);
    }
}






void M_ApplyPlatformDefaults(void)
{

}
fixed_t
FixedMul
( fixed_t a,
  fixed_t b )
{
    return ((long long) a * (long long) b) >> 16;
}







fixed_t FixedDiv(fixed_t a, fixed_t b)
{
    if ((abs(a) >> 14) >= abs(b))
    {
 return (a^b) < 0 ? (-2147483647-1) : 2147483647;
    }
    else
    {
 long long result;

 result = ((long long) a << 16) / b;

 return (fixed_t) result;
    }
}
extern patch_t* hu_font[('_' - '!' + 1)];
extern boolean message_dontfuckwithme;

extern boolean chat_on;




int mouseSensitivity = 5;


int showMessages = 1;



int detailLevel = 0;
int screenblocks = 10;


int screenSize;


int quickSaveSlot;


int messageToPrint;

char* messageString;


int messx;
int messy;
int messageLastMenuActive;


boolean messageNeedsInput;

void (*messageRoutine)(int response);

char gammamsg[5][26] =
{
    "Gamma correction OFF",
    "Gamma correction level 1",
    "Gamma correction level 2",
    "Gamma correction level 3",
    "Gamma correction level 4"
};


int saveStringEnter;
int saveSlot;
int saveCharIndex;

char saveOldString[24];

boolean inhelpscreens;
boolean menuactive;




extern boolean sendpause;
char savegamestrings[10][24];

char endstring[160];






typedef struct
{

    short status;

    char name[10];




    void (*routine)(int choice);


    char alphaKey;
} menuitem_t;



typedef struct menu_s
{
    short numitems;
    struct menu_s* prevMenu;
    menuitem_t* menuitems;
    void (*routine)();
    short x;
    short y;
    short lastOn;
} menu_t;

short itemOn;
short skullAnimCounter;
short whichSkull;



char *skullName[2] = {"M_SKULL1","M_SKULL2"};


menu_t* currentMenu;




void M_NewGame(int choice);
void M_Episode(int choice);
void M_ChooseSkill(int choice);
void M_LoadGame(int choice);
void M_SaveGame(int choice);
void M_Options(int choice);
void M_EndGame(int choice);
void M_ReadThis(int choice);
void M_ReadThis2(int choice);
void M_QuitDOOM(int choice);

void M_ChangeMessages(int choice);
void M_ChangeSensitivity(int choice);
void M_SfxVol(int choice);
void M_MusicVol(int choice);
void M_ChangeDetail(int choice);
void M_SizeDisplay(int choice);
void M_StartGame(int choice);
void M_Sound(int choice);

void M_FinishReadThis(int choice);
void M_LoadSelect(int choice);
void M_SaveSelect(int choice);
void M_ReadSaveStrings(void);
void M_QuickSave(void);
void M_QuickLoad(void);

void M_DrawMainMenu(void);
void M_DrawReadThis1(void);
void M_DrawReadThis2(void);
void M_DrawNewGame(void);
void M_DrawEpisode(void);
void M_DrawOptions(void);
void M_DrawSound(void);
void M_DrawLoad(void);
void M_DrawSave(void);

void M_DrawSaveLoadBorder(int x,int y);
void M_SetupNextMenu(menu_t *menudef);
void M_DrawThermo(int x,int y,int thermWidth,int thermDot);
void M_DrawEmptyCell(menu_t *menu,int item);
void M_DrawSelCell(menu_t *menu,int item);
void M_WriteText(int x, int y, char *string);
int M_StringWidth(char *string);
int M_StringHeight(char *string);
void M_StartMessage(char *string,void *routine,boolean input);
void M_StopMessage(void);
void M_ClearMenus (void);







enum
{
    newgame = 0,
    options,
    loadgame,
    savegame,
    readthis,
    quitdoom,
    main_end
} main_e;

menuitem_t MainMenu[]=
{
    {1,"M_NGAME",M_NewGame,'n'},
    {1,"M_OPTION",M_Options,'o'},
    {1,"M_LOADG",M_LoadGame,'l'},
    {1,"M_SAVEG",M_SaveGame,'s'},

    {1,"M_RDTHIS",M_ReadThis,'r'},
    {1,"M_QUITG",M_QuitDOOM,'q'}
};

menu_t MainDef =
{
    main_end,
    ((void*)0),
    MainMenu,
    M_DrawMainMenu,
    97,64,
    0
};





enum
{
    ep1,
    ep2,
    ep3,
    ep4,
    ep_end
} episodes_e;

menuitem_t EpisodeMenu[]=
{
    {1,"M_EPI1", M_Episode,'k'},
    {1,"M_EPI2", M_Episode,'t'},
    {1,"M_EPI3", M_Episode,'i'},
    {1,"M_EPI4", M_Episode,'t'}
};

menu_t EpiDef =
{
    ep_end,
    &MainDef,
    EpisodeMenu,
    M_DrawEpisode,
    48,63,
    ep1
};




enum
{
    killthings,
    toorough,
    hurtme,
    violence,
    nightmare,
    newg_end
} newgame_e;

menuitem_t NewGameMenu[]=
{
    {1,"M_JKILL", M_ChooseSkill, 'i'},
    {1,"M_ROUGH", M_ChooseSkill, 'h'},
    {1,"M_HURT", M_ChooseSkill, 'h'},
    {1,"M_ULTRA", M_ChooseSkill, 'u'},
    {1,"M_NMARE", M_ChooseSkill, 'n'}
};

menu_t NewDef =
{
    newg_end,
    &EpiDef,
    NewGameMenu,
    M_DrawNewGame,
    48,63,
    hurtme
};






enum
{
    endgame,
    messages,
    detail,
    scrnsize,
    option_empty1,
    mousesens,
    option_empty2,
    soundvol,
    opt_end
} options_e;

menuitem_t OptionsMenu[]=
{
    {1,"M_ENDGAM", M_EndGame,'e'},
    {1,"M_MESSG", M_ChangeMessages,'m'},
    {1,"M_DETAIL", M_ChangeDetail,'g'},
    {2,"M_SCRNSZ", M_SizeDisplay,'s'},
    {-1,"",0,'\0'},
    {2,"M_MSENS", M_ChangeSensitivity,'m'},
    {-1,"",0,'\0'},
    {1,"M_SVOL", M_Sound,'s'}
};

menu_t OptionsDef =
{
    opt_end,
    &MainDef,
    OptionsMenu,
    M_DrawOptions,
    60,37,
    0
};




enum
{
    rdthsempty1,
    read1_end
} read_e;

menuitem_t ReadMenu1[] =
{
    {1,"",M_ReadThis2,0}
};

menu_t ReadDef1 =
{
    read1_end,
    &MainDef,
    ReadMenu1,
    M_DrawReadThis1,
    280,185,
    0
};

enum
{
    rdthsempty2,
    read2_end
} read_e2;

menuitem_t ReadMenu2[]=
{
    {1,"",M_FinishReadThis,0}
};

menu_t ReadDef2 =
{
    read2_end,
    &ReadDef1,
    ReadMenu2,
    M_DrawReadThis2,
    330,175,
    0
};




enum
{
    sfx_vol,
    sfx_empty1,
    music_vol,
    sfx_empty2,
    sound_end
} sound_e;

menuitem_t SoundMenu[]=
{
    {2,"M_SFXVOL",M_SfxVol,'s'},
    {-1,"",0,'\0'},
    {2,"M_MUSVOL",M_MusicVol,'m'},
    {-1,"",0,'\0'}
};

menu_t SoundDef =
{
    sound_end,
    &OptionsDef,
    SoundMenu,
    M_DrawSound,
    80,64,
    0
};




enum
{
    load1,
    load2,
    load3,
    load4,
    load5,
    load6,
    load_end
} load_e;

menuitem_t LoadMenu[]=
{
    {1,"", M_LoadSelect,'1'},
    {1,"", M_LoadSelect,'2'},
    {1,"", M_LoadSelect,'3'},
    {1,"", M_LoadSelect,'4'},
    {1,"", M_LoadSelect,'5'},
    {1,"", M_LoadSelect,'6'}
};

menu_t LoadDef =
{
    load_end,
    &MainDef,
    LoadMenu,
    M_DrawLoad,
    80,54,
    0
};




menuitem_t SaveMenu[]=
{
    {1,"", M_SaveSelect,'1'},
    {1,"", M_SaveSelect,'2'},
    {1,"", M_SaveSelect,'3'},
    {1,"", M_SaveSelect,'4'},
    {1,"", M_SaveSelect,'5'},
    {1,"", M_SaveSelect,'6'}
};

menu_t SaveDef =
{
    load_end,
    &MainDef,
    SaveMenu,
    M_DrawSave,
    80,54,
    0
};






void M_ReadSaveStrings(void)
{
    FILE *handle;
    int i;
    char name[256];

    for (i = 0;i < load_end;i++)
    {
        M_StringCopy(name, P_SaveGameFile(i), sizeof(name));

 handle = fopen(name, "rb");
        if (handle == ((void*)0))
        {
            M_StringCopy(savegamestrings[i], "empty slot", 24);
            LoadMenu[i].status = 0;
            continue;
        }
 fread(&savegamestrings[i], 1, 24, handle);
 fclose(handle);
 LoadMenu[i].status = 1;
    }
}





void M_DrawLoad(void)
{
    int i;

    V_DrawPatchDirect(72, 28,
                      W_CacheLumpName(("M_LOADG"), PU_CACHE));

    for (i = 0;i < load_end; i++)
    {
 M_DrawSaveLoadBorder(LoadDef.x,LoadDef.y+16*i);
 M_WriteText(LoadDef.x,LoadDef.y+16*i,savegamestrings[i]);
    }
}






void M_DrawSaveLoadBorder(int x,int y)
{
    int i;

    V_DrawPatchDirect(x - 8, y + 7,
                      W_CacheLumpName(("M_LSLEFT"), PU_CACHE));

    for (i = 0;i < 24;i++)
    {
 V_DrawPatchDirect(x, y + 7,
                          W_CacheLumpName(("M_LSCNTR"), PU_CACHE));
 x += 8;
    }

    V_DrawPatchDirect(x, y + 7,
                      W_CacheLumpName(("M_LSRGHT"), PU_CACHE));
}






void M_LoadSelect(int choice)
{
    char name[256];

    M_StringCopy(name, P_SaveGameFile(choice), sizeof(name));

    G_LoadGame (name);
    M_ClearMenus ();
}




void M_LoadGame (int choice)
{
    if (netgame)
    {
 M_StartMessage(("you can't do load while in a net game!\n\n""press a key."),((void*)0),false);
 return;
    }

    M_SetupNextMenu(&LoadDef);
    M_ReadSaveStrings();
}





void M_DrawSave(void)
{
    int i;

    V_DrawPatchDirect(72, 28, W_CacheLumpName(("M_SAVEG"), PU_CACHE));
    for (i = 0;i < load_end; i++)
    {
 M_DrawSaveLoadBorder(LoadDef.x,LoadDef.y+16*i);
 M_WriteText(LoadDef.x,LoadDef.y+16*i,savegamestrings[i]);
    }

    if (saveStringEnter)
    {
 i = M_StringWidth(savegamestrings[saveSlot]);
 M_WriteText(LoadDef.x + i,LoadDef.y+16*saveSlot,"_");
    }
}




void M_DoSave(int slot)
{
    G_SaveGame (slot,savegamestrings[slot]);
    M_ClearMenus ();


    if (quickSaveSlot == -2)
 quickSaveSlot = slot;
}




void M_SaveSelect(int choice)
{

    saveStringEnter = 1;

    saveSlot = choice;
    M_StringCopy(saveOldString,savegamestrings[choice], 24);
    if (!strcmp(savegamestrings[choice], "empty slot"))
 savegamestrings[choice][0] = 0;
    saveCharIndex = strlen(savegamestrings[choice]);
}




void M_SaveGame (int choice)
{
    if (!usergame)
    {
 M_StartMessage(("you can't save if you aren't playing!\n\n""press a key."),((void*)0),false);
 return;
    }

    if (gamestate != GS_LEVEL)
 return;

    M_SetupNextMenu(&SaveDef);
    M_ReadSaveStrings();
}






char tempstring[80];

void M_QuickSaveResponse(int key)
{
    if (key == key_menu_confirm)
    {
 M_DoSave(quickSaveSlot);
 S_StartSound(((void*)0),sfx_swtchx);
    }
}

void M_QuickSave(void)
{
    if (!usergame)
    {
 S_StartSound(((void*)0),sfx_oof);
 return;
    }

    if (gamestate != GS_LEVEL)
 return;

    if (quickSaveSlot < 0)
    {
 M_StartControlPanel();
 M_ReadSaveStrings();
 M_SetupNextMenu(&SaveDef);
 quickSaveSlot = -2;
 return;
    }
    snprintf(tempstring, 80, "quicksave over your game named\n\n'%s'?\n\n""press y or n.", savegamestrings[quickSaveSlot]);
    M_StartMessage(tempstring,M_QuickSaveResponse,true);
}






void M_QuickLoadResponse(int key)
{
    if (key == key_menu_confirm)
    {
 M_LoadSelect(quickSaveSlot);
 S_StartSound(((void*)0),sfx_swtchx);
    }
}


void M_QuickLoad(void)
{
    if (netgame)
    {
 M_StartMessage(("you can't quickload during a netgame!\n\n""press a key."),((void*)0),false);
 return;
    }

    if (quickSaveSlot < 0)
    {
 M_StartMessage(("you haven't picked a quicksave slot yet!\n\n""press a key."),((void*)0),false);
 return;
    }
    snprintf(tempstring, 80, "do you want to quickload the game named\n\n'%s'?\n\n""press y or n.", savegamestrings[quickSaveSlot]);
    M_StartMessage(tempstring,M_QuickLoadResponse,true);
}
void M_DrawReadThis1(void)
{
    char *lumpname = "CREDIT";
    int skullx = 330, skully = 175;

    inhelpscreens = true;



    switch (gameversion)
    {
        case exe_doom_1_666:
        case exe_doom_1_7:
        case exe_doom_1_8:
        case exe_doom_1_9:
        case exe_hacx:

            if (gamemode == commercial)
            {


                lumpname = "HELP";

                skullx = 330;
                skully = 165;
            }
            else
            {



                lumpname = "HELP2";

                skullx = 280;
                skully = 185;
            }
            break;

        case exe_ultimate:
        case exe_chex:






            lumpname = "HELP1";

            break;

        case exe_final:
        case exe_final2:



            lumpname = "HELP";

            break;

        default:
            I_Error("Unhandled game version");
            break;
    }

    lumpname = (lumpname);

    V_DrawPatchDirect (0, 0, W_CacheLumpName(lumpname, PU_CACHE));

    ReadDef1.x = skullx;
    ReadDef1.y = skully;
}






void M_DrawReadThis2(void)
{
    inhelpscreens = true;




    V_DrawPatchDirect(0, 0, W_CacheLumpName(("HELP1"), PU_CACHE));
}





void M_DrawSound(void)
{
    V_DrawPatchDirect (60, 38, W_CacheLumpName(("M_SVOL"), PU_CACHE));

    M_DrawThermo(SoundDef.x,SoundDef.y+16*(sfx_vol+1),
   16,sfxVolume);

    M_DrawThermo(SoundDef.x,SoundDef.y+16*(music_vol+1),
   16,musicVolume);
}

void M_Sound(int choice)
{
    M_SetupNextMenu(&SoundDef);
}

void M_SfxVol(int choice)
{
    switch(choice)
    {
      case 0:
 if (sfxVolume)
     sfxVolume--;
 break;
      case 1:
 if (sfxVolume < 15)
     sfxVolume++;
 break;
    }

    S_SetSfxVolume(sfxVolume * 8);
}

void M_MusicVol(int choice)
{
    switch(choice)
    {
      case 0:
 if (musicVolume)
     musicVolume--;
 break;
      case 1:
 if (musicVolume < 15)
     musicVolume++;
 break;
    }

    S_SetMusicVolume(musicVolume * 8);
}







void M_DrawMainMenu(void)
{
    V_DrawPatchDirect(94, 2,
                      W_CacheLumpName(("M_DOOM"), PU_CACHE));
}







void M_DrawNewGame(void)
{
    V_DrawPatchDirect(96, 14, W_CacheLumpName(("M_NEWG"), PU_CACHE));
    V_DrawPatchDirect(54, 38, W_CacheLumpName(("M_SKILL"), PU_CACHE));
}

void M_NewGame(int choice)
{
    if (netgame && !demoplayback)
    {
 M_StartMessage(("you can't start a new game\n""while in a network game.\n\n""press a key."),((void*)0),false);
 return;
    }



    if (gamemode == commercial || gameversion == exe_chex)
 M_SetupNextMenu(&NewDef);
    else
 M_SetupNextMenu(&EpiDef);
}





int epi;

void M_DrawEpisode(void)
{
    V_DrawPatchDirect(54, 38, W_CacheLumpName(("M_EPISOD"), PU_CACHE));
}

void M_VerifyNightmare(int key)
{
    if (key != key_menu_confirm)
 return;

    G_DeferedInitNew(nightmare,epi+1,1);
    M_ClearMenus ();
}

void M_ChooseSkill(int choice)
{
    if (choice == nightmare)
    {
 M_StartMessage(("are you sure? this skill level\n""isn't even remotely fair.\n\n""press y or n."),M_VerifyNightmare,true);
 return;
    }

    G_DeferedInitNew(choice,epi+1,1);
    M_ClearMenus ();
}

void M_Episode(int choice)
{
    if ( (gamemode == shareware)
  && choice)
    {
 M_StartMessage(("this is the shareware version of doom.\n\n""you need to order the entire trilogy.\n\n""press a key."),((void*)0),false);
 M_SetupNextMenu(&ReadDef1);
 return;
    }


    if ( (gamemode == registered)
  && (choice > 2))
    {
      fprintf( __stderrp,
        "M_Episode: 4th episode requires UltimateDOOM\n");
      choice = 0;
    }

    epi = choice;
    M_SetupNextMenu(&NewDef);
}






static char *detailNames[2] = {"M_GDHIGH","M_GDLOW"};
static char *msgNames[2] = {"M_MSGOFF","M_MSGON"};

void M_DrawOptions(void)
{
    V_DrawPatchDirect(108, 15, W_CacheLumpName(("M_OPTTTL"),
                                               PU_CACHE));

    V_DrawPatchDirect(OptionsDef.x + 175, OptionsDef.y + 16 * detail,
        W_CacheLumpName((detailNames[detailLevel]),
                 PU_CACHE));

    V_DrawPatchDirect(OptionsDef.x + 120, OptionsDef.y + 16 * messages,
                      W_CacheLumpName((msgNames[showMessages]),
                                      PU_CACHE));

    M_DrawThermo(OptionsDef.x, OptionsDef.y + 16 * (mousesens + 1),
   10, mouseSensitivity);

    M_DrawThermo(OptionsDef.x,OptionsDef.y+16*(scrnsize+1),
   9,screenSize);
}

void M_Options(int choice)
{
    M_SetupNextMenu(&OptionsDef);
}






void M_ChangeMessages(int choice)
{

    choice = 0;
    showMessages = 1 - showMessages;

    if (!showMessages)
 players[consoleplayer].message = ("Messages OFF");
    else
 players[consoleplayer].message = ("Messages ON");

    message_dontfuckwithme = true;
}





void M_EndGameResponse(int key)
{
    if (key != key_menu_confirm)
 return;

    currentMenu->lastOn = itemOn;
    M_ClearMenus ();
    D_StartTitle ();
}

void M_EndGame(int choice)
{
    choice = 0;
    if (!usergame)
    {
 S_StartSound(((void*)0),sfx_oof);
 return;
    }

    if (netgame)
    {
 M_StartMessage(("you can't end a netgame!\n\n""press a key."),((void*)0),false);
 return;
    }

    M_StartMessage(("are you sure you want to end the game?\n\n""press y or n."),M_EndGameResponse,true);
}







void M_ReadThis(int choice)
{
    choice = 0;
    M_SetupNextMenu(&ReadDef1);
}

void M_ReadThis2(int choice)
{



    if (gameversion <= exe_doom_1_9 && gamemode != commercial)
    {
        choice = 0;
        M_SetupNextMenu(&ReadDef2);
    }
    else
    {


        M_FinishReadThis(0);
    }
}

void M_FinishReadThis(int choice)
{
    choice = 0;
    M_SetupNextMenu(&MainDef);
}







int quitsounds[8] =
{
    sfx_pldeth,
    sfx_dmpain,
    sfx_popain,
    sfx_slop,
    sfx_telept,
    sfx_posit1,
    sfx_posit3,
    sfx_sgtatk
};

int quitsounds2[8] =
{
    sfx_vilact,
    sfx_getpow,
    sfx_boscub,
    sfx_slop,
    sfx_skeswg,
    sfx_kntdth,
    sfx_bspact,
    sfx_sgtatk
};



void M_QuitResponse(int key)
{
    if (key != key_menu_confirm)
 return;
    if (!netgame)
    {
 if (gamemode == commercial)
     S_StartSound(((void*)0),quitsounds2[(gametic>>2)&7]);
 else
     S_StartSound(((void*)0),quitsounds[(gametic>>2)&7]);
 I_WaitVBL(105);
    }
    I_Quit ();
}


static char *M_SelectEndMessage(void)
{
    char **endmsg;

    if ((gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) == doom)
    {


        endmsg = doom1_endmsg;
    }
    else
    {


        endmsg = doom2_endmsg;
    }

    return endmsg[gametic % 8];
}


void M_QuitDOOM(int choice)
{
    snprintf(endstring, sizeof(endstring), "%s\n\n" "(press y to quit to dos.)",
                 (M_SelectEndMessage()));

    M_StartMessage(endstring,M_QuitResponse,true);
}




void M_ChangeSensitivity(int choice)
{
    switch(choice)
    {
      case 0:
 if (mouseSensitivity)
     mouseSensitivity--;
 break;
      case 1:
 if (mouseSensitivity < 9)
     mouseSensitivity++;
 break;
    }
}




void M_ChangeDetail(int choice)
{
    choice = 0;
    detailLevel = 1 - detailLevel;

    R_SetViewSize (screenblocks, detailLevel);

    if (!detailLevel)
 players[consoleplayer].message = ("High detail");
    else
 players[consoleplayer].message = ("Low detail");
}




void M_SizeDisplay(int choice)
{
    switch(choice)
    {
      case 0:
 if (screenSize > 0)
 {
     screenblocks--;
     screenSize--;
 }
 break;
      case 1:
 if (screenSize < 8)
 {
     screenblocks++;
     screenSize++;
 }
 break;
    }


    R_SetViewSize (screenblocks, detailLevel);
}







void
M_DrawThermo
( int x,
  int y,
  int thermWidth,
  int thermDot )
{
    int xx;
    int i;

    xx = x;
    V_DrawPatchDirect(xx, y, W_CacheLumpName(("M_THERML"), PU_CACHE));
    xx += 8;
    for (i=0;i<thermWidth;i++)
    {
 V_DrawPatchDirect(xx, y, W_CacheLumpName(("M_THERMM"), PU_CACHE));
 xx += 8;
    }
    V_DrawPatchDirect(xx, y, W_CacheLumpName(("M_THERMR"), PU_CACHE));

    V_DrawPatchDirect((x + 8) + thermDot * 8, y,
        W_CacheLumpName(("M_THERMO"), PU_CACHE));
}



void
M_DrawEmptyCell
( menu_t* menu,
  int item )
{
    V_DrawPatchDirect(menu->x - 10, menu->y + item * 16 - 1,
                      W_CacheLumpName(("M_CELL1"), PU_CACHE));
}

void
M_DrawSelCell
( menu_t* menu,
  int item )
{
    V_DrawPatchDirect(menu->x - 10, menu->y + item * 16 - 1,
                      W_CacheLumpName(("M_CELL2"), PU_CACHE));
}


void
M_StartMessage
( char* string,
  void* routine,
  boolean input )
{
    messageLastMenuActive = menuactive;
    messageToPrint = 1;
    messageString = string;
    messageRoutine = routine;
    messageNeedsInput = input;
    menuactive = true;
    return;
}


void M_StopMessage(void)
{
    menuactive = messageLastMenuActive;
    messageToPrint = 0;
}






int M_StringWidth(char* string)
{
    size_t i;
    int w = 0;
    int c;

    for (i = 0;i < strlen(string);i++)
    {
 c = toupper(string[i]) - '!';
 if (c < 0 || c >= ('_' - '!' + 1))
     w += 4;
 else
     w += ((signed short) (hu_font[c]->width));
    }

    return w;
}






int M_StringHeight(char* string)
{
    size_t i;
    int h;
    int height = ((signed short) (hu_font[0]->height));

    h = height;
    for (i = 0;i < strlen(string);i++)
 if (string[i] == '\n')
     h += height;

    return h;
}





void
M_WriteText
( int x,
  int y,
  char* string)
{
    int w;
    char* ch;
    int c;
    int cx;
    int cy;


    ch = string;
    cx = x;
    cy = y;

    while(1)
    {
 c = *ch++;
 if (!c)
     break;
 if (c == '\n')
 {
     cx = x;
     cy += 12;
     continue;
 }

 c = toupper(c) - '!';
 if (c < 0 || c>= ('_' - '!' + 1))
 {
     cx += 4;
     continue;
 }

 w = ((signed short) (hu_font[c]->width));
 if (cx+w > 320)
     break;
 V_DrawPatchDirect(cx, cy, hu_font[c]);
 cx+=w;
    }
}




static boolean IsNullKey(int key)
{
    return key == 0xff || key == (0x80+0x3a)
        || key == (0x80+0x46) || key == (0x80+0x45);
}
boolean M_Responder (event_t* ev)
{
    int ch;
    int key;
    int i;
    static int joywait = 0;
    static int mousewait = 0;
    static int mousey = 0;
    static int lasty = 0;
    static int mousex = 0;
    static int lastx = 0;




    if (testcontrols)
    {
        if (ev->type == ev_quit
         || (ev->type == ev_keydown
          && (ev->data1 == key_menu_activate || ev->data1 == key_menu_quit)))
        {
            I_Quit();
            return true;
        }

        return false;
    }


    if (ev->type == ev_quit)
    {



        if (menuactive && messageToPrint && messageRoutine == M_QuitResponse)
        {
            M_QuitResponse(key_menu_confirm);
        }
        else
        {
            S_StartSound(((void*)0),sfx_swtchn);
            M_QuitDOOM(0);
        }

        return true;
    }



    ch = 0;
    key = -1;

    if (ev->type == ev_joystick && joywait < I_GetTime())
    {
 if (ev->data3 < 0)
 {
     key = key_menu_up;
     joywait = I_GetTime() + 5;
 }
 else if (ev->data3 > 0)
 {
     key = key_menu_down;
     joywait = I_GetTime() + 5;
 }

 if (ev->data2 < 0)
 {
     key = key_menu_left;
     joywait = I_GetTime() + 2;
 }
 else if (ev->data2 > 0)
 {
     key = key_menu_right;
     joywait = I_GetTime() + 2;
 }

 if (ev->data1&1)
 {
     key = key_menu_forward;
     joywait = I_GetTime() + 5;
 }
 if (ev->data1&2)
 {
     key = key_menu_back;
     joywait = I_GetTime() + 5;
 }
        if (joybmenu >= 0 && (ev->data1 & (1 << joybmenu)) != 0)
        {
            key = key_menu_activate;
     joywait = I_GetTime() + 5;
        }
    }
    else
    {
 if (ev->type == ev_mouse && mousewait < I_GetTime())
 {
     mousey += ev->data3;
     if (mousey < lasty-30)
     {
  key = key_menu_down;
  mousewait = I_GetTime() + 5;
  mousey = lasty -= 30;
     }
     else if (mousey > lasty+30)
     {
  key = key_menu_up;
  mousewait = I_GetTime() + 5;
  mousey = lasty += 30;
     }

     mousex += ev->data2;
     if (mousex < lastx-30)
     {
  key = key_menu_left;
  mousewait = I_GetTime() + 5;
  mousex = lastx -= 30;
     }
     else if (mousex > lastx+30)
     {
  key = key_menu_right;
  mousewait = I_GetTime() + 5;
  mousex = lastx += 30;
     }

     if (ev->data1&1)
     {
  key = key_menu_forward;
  mousewait = I_GetTime() + 15;
     }

     if (ev->data1&2)
     {
  key = key_menu_back;
  mousewait = I_GetTime() + 15;
     }
 }
 else
 {
     if (ev->type == ev_keydown)
     {
  key = ev->data1;
  ch = ev->data2;
     }
 }
    }

    if (key == -1)
 return false;


    if (saveStringEnter)
    {
 switch(key)
 {
   case 0x7f:
     if (saveCharIndex > 0)
     {
  saveCharIndex--;
  savegamestrings[saveSlot][saveCharIndex] = 0;
     }
     break;

          case 27:
            saveStringEnter = 0;
            M_StringCopy(savegamestrings[saveSlot], saveOldString,
                         24);
            break;

   case 13:
     saveStringEnter = 0;
     if (savegamestrings[saveSlot][0])
  M_DoSave(saveSlot);
     break;

   default:







            if (vanilla_keyboard_mapping)
            {
                ch = key;
            }

            ch = toupper(ch);

            if (ch != ' '
             && (ch - '!' < 0 || ch - '!' >= ('_' - '!' + 1)))
            {
                break;
            }

     if (ch >= 32 && ch <= 127 &&
  saveCharIndex < 24 -1 &&
  M_StringWidth(savegamestrings[saveSlot]) <
  (24 -2)*8)
     {
  savegamestrings[saveSlot][saveCharIndex++] = ch;
  savegamestrings[saveSlot][saveCharIndex] = 0;
     }
     break;
 }
 return true;
    }


    if (messageToPrint)
    {
 if (messageNeedsInput)
        {
            if (key != ' ' && key != 27
             && key != key_menu_confirm && key != key_menu_abort)
            {
                return false;
            }
 }

 menuactive = messageLastMenuActive;
 messageToPrint = 0;
 if (messageRoutine)
     messageRoutine(key);

 menuactive = false;
 S_StartSound(((void*)0),sfx_swtchx);
 return true;
    }

    if ((devparm && key == key_menu_help) ||
        (key != 0 && key == key_menu_screenshot))
    {
 G_ScreenShot ();
 return true;
    }


    if (!menuactive)
    {
 if (key == key_menu_decscreen)
        {
     if (automapactive || chat_on)
  return false;
     M_SizeDisplay(0);
     S_StartSound(((void*)0),sfx_stnmov);
     return true;
 }
        else if (key == key_menu_incscreen)
        {
     if (automapactive || chat_on)
  return false;
     M_SizeDisplay(1);
     S_StartSound(((void*)0),sfx_stnmov);
     return true;
 }
        else if (key == key_menu_help)
        {
     M_StartControlPanel ();

     if ( gamemode == retail )
       currentMenu = &ReadDef2;
     else
       currentMenu = &ReadDef1;

     itemOn = 0;
     S_StartSound(((void*)0),sfx_swtchn);
     return true;
 }
        else if (key == key_menu_save)
        {
     M_StartControlPanel();
     S_StartSound(((void*)0),sfx_swtchn);
     M_SaveGame(0);
     return true;
        }
        else if (key == key_menu_load)
        {
     M_StartControlPanel();
     S_StartSound(((void*)0),sfx_swtchn);
     M_LoadGame(0);
     return true;
        }
        else if (key == key_menu_volume)
        {
     M_StartControlPanel ();
     currentMenu = &SoundDef;
     itemOn = sfx_vol;
     S_StartSound(((void*)0),sfx_swtchn);
     return true;
 }
        else if (key == key_menu_detail)
        {
     M_ChangeDetail(0);
     S_StartSound(((void*)0),sfx_swtchn);
     return true;
        }
        else if (key == key_menu_qsave)
        {
     S_StartSound(((void*)0),sfx_swtchn);
     M_QuickSave();
     return true;
        }
        else if (key == key_menu_endgame)
        {
     S_StartSound(((void*)0),sfx_swtchn);
     M_EndGame(0);
     return true;
        }
        else if (key == key_menu_messages)
        {
     M_ChangeMessages(0);
     S_StartSound(((void*)0),sfx_swtchn);
     return true;
        }
        else if (key == key_menu_qload)
        {
     S_StartSound(((void*)0),sfx_swtchn);
     M_QuickLoad();
     return true;
        }
        else if (key == key_menu_quit)
        {
     S_StartSound(((void*)0),sfx_swtchn);
     M_QuitDOOM(0);
     return true;
        }
        else if (key == key_menu_gamma)
        {
     usegamma++;
     if (usegamma > 4)
  usegamma = 0;
     players[consoleplayer].message = (gammamsg[usegamma]);
            I_SetPalette (W_CacheLumpName (("PLAYPAL"),PU_CACHE));
     return true;
 }
    }


    if (!menuactive)
    {
 if (key == key_menu_activate)
 {
     M_StartControlPanel ();
     S_StartSound(((void*)0),sfx_swtchn);
     return true;
 }
 return false;
    }



    if (key == key_menu_down)
    {


        do
 {
     if (itemOn+1 > currentMenu->numitems-1)
  itemOn = 0;
     else itemOn++;
     S_StartSound(((void*)0),sfx_pstop);
 } while(currentMenu->menuitems[itemOn].status==-1);

 return true;
    }
    else if (key == key_menu_up)
    {


 do
 {
     if (!itemOn)
  itemOn = currentMenu->numitems-1;
     else itemOn--;
     S_StartSound(((void*)0),sfx_pstop);
 } while(currentMenu->menuitems[itemOn].status==-1);

 return true;
    }
    else if (key == key_menu_left)
    {


 if (currentMenu->menuitems[itemOn].routine &&
     currentMenu->menuitems[itemOn].status == 2)
 {
     S_StartSound(((void*)0),sfx_stnmov);
     currentMenu->menuitems[itemOn].routine(0);
 }
 return true;
    }
    else if (key == key_menu_right)
    {


 if (currentMenu->menuitems[itemOn].routine &&
     currentMenu->menuitems[itemOn].status == 2)
 {
     S_StartSound(((void*)0),sfx_stnmov);
     currentMenu->menuitems[itemOn].routine(1);
 }
 return true;
    }
    else if (key == key_menu_forward)
    {


 if (currentMenu->menuitems[itemOn].routine &&
     currentMenu->menuitems[itemOn].status)
 {
     currentMenu->lastOn = itemOn;
     if (currentMenu->menuitems[itemOn].status == 2)
     {
  currentMenu->menuitems[itemOn].routine(1);
  S_StartSound(((void*)0),sfx_stnmov);
     }
     else
     {
  currentMenu->menuitems[itemOn].routine(itemOn);
  S_StartSound(((void*)0),sfx_pistol);
     }
 }
 return true;
    }
    else if (key == key_menu_activate)
    {


 currentMenu->lastOn = itemOn;
 M_ClearMenus ();
 S_StartSound(((void*)0),sfx_swtchx);
 return true;
    }
    else if (key == key_menu_back)
    {


 currentMenu->lastOn = itemOn;
 if (currentMenu->prevMenu)
 {
     currentMenu = currentMenu->prevMenu;
     itemOn = currentMenu->lastOn;
     S_StartSound(((void*)0),sfx_swtchn);
 }
 return true;
    }





    else if (ch != 0 || IsNullKey(key))
    {
 for (i = itemOn+1;i < currentMenu->numitems;i++)
        {
     if (currentMenu->menuitems[i].alphaKey == ch)
     {
  itemOn = i;
  S_StartSound(((void*)0),sfx_pstop);
  return true;
     }
        }

 for (i = 0;i <= itemOn;i++)
        {
     if (currentMenu->menuitems[i].alphaKey == ch)
     {
  itemOn = i;
  S_StartSound(((void*)0),sfx_pstop);
  return true;
     }
        }
    }

    return false;
}






void M_StartControlPanel (void)
{

    if (menuactive)
 return;

    menuactive = 1;
    currentMenu = &MainDef;
    itemOn = currentMenu->lastOn;
}
void M_Drawer (void)
{
    static short x;
    static short y;
    unsigned int i;
    unsigned int max;
    char string[80];
    char *name;
    int start;

    inhelpscreens = false;


    if (messageToPrint)
    {
 start = 0;
 y = 200/2 - M_StringHeight(messageString) / 2;
 while (messageString[start] != '\0')
 {
     int foundnewline = 0;

            for (i = 0; i < strlen(messageString + start); i++)
            {
                if (messageString[start + i] == '\n')
                {
                    M_StringCopy(string, messageString + start,
                                 sizeof(string));
                    if (i < sizeof(string))
                    {
                        string[i] = '\0';
                    }

                    foundnewline = 1;
                    start += i + 1;
                    break;
                }
            }

            if (!foundnewline)
            {
                M_StringCopy(string, messageString + start, sizeof(string));
                start += strlen(string);
            }

     x = 320/2 - M_StringWidth(string) / 2;
     M_WriteText(x, y, string);
     y += ((signed short) (hu_font[0]->height));
 }

 return;
    }






    if (!menuactive)
 return;

    if (currentMenu->routine)
 currentMenu->routine();


    x = currentMenu->x;
    y = currentMenu->y;
    max = currentMenu->numitems;

    for (i=0;i<max;i++)
    {
        name = (currentMenu->menuitems[i].name);

 if (name[0])
 {
     V_DrawPatchDirect (x, y, W_CacheLumpName(name, PU_CACHE));
 }
 y += 16;
    }



    V_DrawPatchDirect(x + -32, currentMenu->y - 5 + itemOn*16,
        W_CacheLumpName((skullName[whichSkull]),
          PU_CACHE));
}





void M_ClearMenus (void)
{
    menuactive = 0;


}







void M_SetupNextMenu(menu_t *menudef)
{
    currentMenu = menudef;
    itemOn = currentMenu->lastOn;
}





void M_Ticker (void)
{
    if (--skullAnimCounter <= 0)
    {
 whichSkull ^= 1;
 skullAnimCounter = 8;
    }
}





void M_Init (void)
{
    currentMenu = &MainDef;
    menuactive = 0;
    itemOn = currentMenu->lastOn;
    whichSkull = 0;
    skullAnimCounter = 10;
    screenSize = screenblocks - 3;
    messageToPrint = 0;
    messageString = ((void*)0);
    messageLastMenuActive = menuactive;
    quickSaveSlot = -1;





    switch ( gamemode )
    {
      case commercial:

 MainMenu[readthis] = MainMenu[quitdoom];
 MainDef.numitems--;
 MainDef.y += 8;
 NewDef.prevMenu = &MainDef;
 break;
      case shareware:


      case registered:
 break;
      case retail:

      default:
 break;
    }





    if (gameversion < exe_ultimate)
    {
 EpiDef.numitems--;
    }


}
void M_MakeDirectory(char *path)
{



    mkdir(path, 0755);

}



boolean M_FileExists(char *filename)
{
    FILE *fstream;

    fstream = fopen(filename, "r");

    if (fstream != ((void*)0))
    {
        fclose(fstream);
        return true;
    }
    else
    {



        return (*__error()) == 21;
    }
}





long M_FileLength(FILE *handle)
{
    long savedpos;
    long length;


    savedpos = ftell(handle);


    fseek(handle, 0, 2);
    length = ftell(handle);


    fseek(handle, savedpos, 0);

    return length;
}





boolean M_WriteFile(char *name, void *source, int length)
{
    FILE *handle;
    int count;

    handle = fopen(name, "wb");

    if (handle == ((void*)0))
 return false;

    count = fwrite(source, 1, length, handle);
    fclose(handle);

    if (count < length)
 return false;

    return true;
}






int M_ReadFile(char *name, byte **buffer)
{
    FILE *handle;
    int count, length;
    byte *buf;

    handle = fopen(name, "rb");
    if (handle == ((void*)0))
 I_Error ("Couldn't read file %s", name);




    length = M_FileLength(handle);

    buf = Z_Malloc (length, PU_STATIC, ((void*)0));
    count = fread(buf, 1, length, handle);
    fclose (handle);

    if (count < length)
 I_Error ("Couldn't read file %s", name);

    *buffer = buf;
    return length;
}






char *M_TempFile(char *s)
{
    char *tempdir;
    tempdir = "/tmp";


    return M_StringJoin(tempdir, "/", s, ((void*)0));
}

boolean M_StrToInt(const char *str, int *result)
{
    return sscanf(str, " 0x%x", result) == 1
        || sscanf(str, " 0X%x", result) == 1
        || sscanf(str, " 0%o", result) == 1
        || sscanf(str, " %d", result) == 1;
}

void M_ExtractFileBase(char *path, char *dest)
{
    char *src;
    char *filename;
    int length;

    src = path + strlen(path) - 1;


    while (src != path && *(src - 1) != '/')
    {
 src--;
    }

    filename = src;






    length = 0;
    memset(dest, 0, 8);

    while (*src != '\0' && *src != '.')
    {
        if (length >= 8)
        {
            printf("Warning: Truncated '%s' lump name to '%0s'.\n",
                   filename, dest);
            break;
        }

 dest[length++] = toupper((int)*src++);
    }
}
void M_ForceUppercase(char *text)
{
    char *p;

    for (p = text; *p != '\0'; ++p)
    {
        *p = toupper(*p);
    }
}







char *M_StrCaseStr(char *haystack, char *needle)
{
    unsigned int haystack_len;
    unsigned int needle_len;
    unsigned int len;
    unsigned int i;

    haystack_len = strlen(haystack);
    needle_len = strlen(needle);

    if (haystack_len < needle_len)
    {
        return ((void*)0);
    }

    len = haystack_len - needle_len;

    for (i = 0; i <= len; ++i)
    {
        if (!strncasecmp(haystack + i, needle, needle_len))
        {
            return haystack + i;
        }
    }

    return ((void*)0);
}






char *M_StringDuplicate(const char *orig)
{
    char *result;

    result = strdup(orig);

    if (result == ((void*)0))
    {
        I_Error("Failed to duplicate string (length %i)\n",
                strlen(orig));
    }

    return result;
}





char *M_StringReplace(const char *haystack, const char *needle,
                      const char *replacement)
{
    char *result, *dst;
    const char *p;
    size_t needle_len = strlen(needle);
    size_t result_len, dst_len;



    result_len = strlen(haystack) + 1;
    p = haystack;

    for (;;)
    {
        p = strstr(p, needle);
        if (p == ((void*)0))
        {
            break;
        }

        p += needle_len;
        result_len += strlen(replacement) - needle_len;
    }



    result = malloc(result_len);
    if (result == ((void*)0))
    {
        I_Error("M_StringReplace: Failed to allocate new string");
        return ((void*)0);
    }

    dst = result; dst_len = result_len;
    p = haystack;

    while (*p != '\0')
    {
        if (!strncmp(p, needle, needle_len))
        {
            M_StringCopy(dst, replacement, dst_len);
            p += needle_len;
            dst += strlen(replacement);
            dst_len -= strlen(replacement);
        }
        else
        {
            *dst = *p;
            ++dst; --dst_len;
            ++p;
        }
    }

    *dst = '\0';

    return result;
}




boolean M_StringCopy(char *dest, const char *src, size_t dest_size)
{
    size_t len;

    if (dest_size >= 1)
    {
        dest[dest_size - 1] = '\0';
        strncpy(dest, src, dest_size - 1);
    }
    else
    {
        return false;
    }

    len = strlen(dest);
    return src[len] == '\0';
}




boolean M_StringConcat(char *dest, const char *src, size_t dest_size)
{
    size_t offset;

    offset = strlen(dest);
    if (offset > dest_size)
    {
        offset = dest_size;
    }

    return M_StringCopy(dest + offset, src, dest_size - offset);
}



boolean M_StringStartsWith(const char *s, const char *prefix)
{
    return strlen(s) > strlen(prefix)
        && strncmp(s, prefix, strlen(prefix)) == 0;
}



boolean M_StringEndsWith(const char *s, const char *suffix)
{
    return strlen(s) >= strlen(suffix)
        && strcmp(s + strlen(s) - strlen(suffix), suffix) == 0;
}




char *M_StringJoin(const char *s, ...)
{
    char *result;
    const char *v;
    va_list args;
    size_t result_len;

    result_len = strlen(s) + 1;

    __builtin_va_start(args, s);
    for (;;)
    {
        v = __builtin_va_arg(args, const char *);
        if (v == ((void*)0))
        {
            break;
        }

        result_len += strlen(v);
    }
    __builtin_va_end(args);

    result = malloc(result_len);

    if (result == ((void*)0))
    {
        I_Error("M_StringJoin: Failed to allocate new string.");
        return ((void*)0);
    }

    M_StringCopy(result, s, result_len);

    __builtin_va_start(args, s);
    for (;;)
    {
        v = __builtin_va_arg(args, const char *);
        if (v == ((void*)0))
        {
            break;
        }

        M_StringConcat(result, v, result_len);
    }
    __builtin_va_end(args);

    return result;
}
int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args)
{
    int result;

    if (buf_len < 1)
    {
        return 0;
    }




    result = vsnprintf(buf, buf_len, s, args);



    if (result < 0 || result >= buf_len)
    {
        buf[buf_len - 1] = '\0';
        result = buf_len - 1;
    }

    return result;
}


int M_snprintf(char *buf, size_t buf_len, const char *s, ...)
{
    va_list args;
    int result;
    __builtin_va_start(args, s);
    result = M_vsnprintf(buf, buf_len, s, args);
    __builtin_va_end(args);
    return result;
}
static const unsigned char rndtable[256] = {
    0, 8, 109, 220, 222, 241, 149, 107, 75, 248, 254, 140, 16, 66 ,
    74, 21, 211, 47, 80, 242, 154, 27, 205, 128, 161, 89, 77, 36 ,
    95, 110, 85, 48, 212, 140, 211, 249, 22, 79, 200, 50, 28, 188 ,
    52, 140, 202, 120, 68, 145, 62, 70, 184, 190, 91, 197, 152, 224 ,
    149, 104, 25, 178, 252, 182, 202, 182, 141, 197, 4, 81, 181, 242 ,
    145, 42, 39, 227, 156, 198, 225, 193, 219, 93, 122, 175, 249, 0 ,
    175, 143, 70, 239, 46, 246, 163, 53, 163, 109, 168, 135, 2, 235 ,
    25, 92, 20, 145, 138, 77, 69, 166, 78, 176, 173, 212, 166, 113 ,
    94, 161, 41, 50, 239, 49, 111, 164, 70, 60, 2, 37, 171, 75 ,
    136, 156, 11, 56, 42, 146, 138, 229, 73, 146, 77, 61, 98, 196 ,
    135, 106, 63, 197, 195, 86, 96, 203, 113, 101, 170, 247, 181, 113 ,
    80, 250, 108, 7, 255, 237, 129, 226, 79, 107, 112, 166, 103, 241 ,
    24, 223, 239, 120, 198, 58, 60, 82, 128, 3, 184, 66, 143, 224 ,
    145, 224, 81, 206, 163, 45, 63, 90, 168, 114, 59, 33, 159, 95 ,
    28, 139, 123, 98, 125, 196, 15, 70, 194, 253, 54, 14, 109, 226 ,
    71, 17, 161, 93, 186, 87, 244, 138, 20, 52, 123, 251, 26, 36 ,
    17, 46, 52, 231, 232, 76, 31, 221, 84, 37, 216, 165, 212, 106 ,
    197, 242, 98, 43, 39, 175, 254, 145, 190, 84, 118, 222, 187, 136 ,
    120, 163, 236, 249
};

int rndindex = 0;
int prndindex = 0;


int P_Random (void)
{
    prndindex = (prndindex+1)&0xff;
    return rndtable[prndindex];
}

int M_Random (void)
{
    rndindex = (rndindex+1)&0xff;
    return rndtable[rndindex];
}

void M_ClearRandom (void)
{
    rndindex = prndindex = 0;
}
ceiling_t* activeceilings[30];






void T_MoveCeiling (ceiling_t* ceiling)
{
    result_e res;

    switch(ceiling->direction)
    {
      case 0:

 break;
      case 1:

 res = T_MovePlane(ceiling->sector,
     ceiling->speed,
     ceiling->topheight,
     false,1,ceiling->direction);

 if (!(leveltime&7))
 {
     switch(ceiling->type)
     {
       case silentCrushAndRaise:
  break;
       default:
  S_StartSound(&ceiling->sector->soundorg, sfx_stnmov);

  break;
     }
 }

 if (res == pastdest)
 {
     switch(ceiling->type)
     {
       case raiseToHighest:
  P_RemoveActiveCeiling(ceiling);
  break;

       case silentCrushAndRaise:
  S_StartSound(&ceiling->sector->soundorg, sfx_pstop);
       case fastCrushAndRaise:
       case crushAndRaise:
  ceiling->direction = -1;
  break;

       default:
  break;
     }

 }
 break;

      case -1:

 res = T_MovePlane(ceiling->sector,
     ceiling->speed,
     ceiling->bottomheight,
     ceiling->crush,1,ceiling->direction);

 if (!(leveltime&7))
 {
     switch(ceiling->type)
     {
       case silentCrushAndRaise: break;
       default:
  S_StartSound(&ceiling->sector->soundorg, sfx_stnmov);
     }
 }

 if (res == pastdest)
 {
     switch(ceiling->type)
     {
       case silentCrushAndRaise:
  S_StartSound(&ceiling->sector->soundorg, sfx_pstop);
       case crushAndRaise:
  ceiling->speed = (1<<16);
       case fastCrushAndRaise:
  ceiling->direction = 1;
  break;

       case lowerAndCrush:
       case lowerToFloor:
  P_RemoveActiveCeiling(ceiling);
  break;

       default:
  break;
     }
 }
 else
 {
     if (res == crushed)
     {
  switch(ceiling->type)
  {
    case silentCrushAndRaise:
    case crushAndRaise:
    case lowerAndCrush:
      ceiling->speed = (1<<16) / 8;
      break;

    default:
      break;
  }
     }
 }
 break;
    }
}






int
EV_DoCeiling
( line_t* line,
  ceiling_e type )
{
    int secnum;
    int rtn;
    sector_t* sec;
    ceiling_t* ceiling;

    secnum = -1;
    rtn = 0;


    switch(type)
    {
      case fastCrushAndRaise:
      case silentCrushAndRaise:
      case crushAndRaise:
 P_ActivateInStasisCeiling(line);
      default:
 break;
    }

    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
 sec = &sectors[secnum];
 if (sec->specialdata)
     continue;


 rtn = 1;
 ceiling = Z_Malloc (sizeof(*ceiling), PU_LEVSPEC, 0);
 P_AddThinker (&ceiling->thinker);
 sec->specialdata = ceiling;
 ceiling->thinker.function.acp1 = (actionf_p1)T_MoveCeiling;
 ceiling->sector = sec;
 ceiling->crush = false;

 switch(type)
 {
   case fastCrushAndRaise:
     ceiling->crush = true;
     ceiling->topheight = sec->ceilingheight;
     ceiling->bottomheight = sec->floorheight + (8*(1<<16));
     ceiling->direction = -1;
     ceiling->speed = (1<<16) * 2;
     break;

   case silentCrushAndRaise:
   case crushAndRaise:
     ceiling->crush = true;
     ceiling->topheight = sec->ceilingheight;
   case lowerAndCrush:
   case lowerToFloor:
     ceiling->bottomheight = sec->floorheight;
     if (type != lowerToFloor)
  ceiling->bottomheight += 8*(1<<16);
     ceiling->direction = -1;
     ceiling->speed = (1<<16);
     break;

   case raiseToHighest:
     ceiling->topheight = P_FindHighestCeilingSurrounding(sec);
     ceiling->direction = 1;
     ceiling->speed = (1<<16);
     break;
 }

 ceiling->tag = sec->tag;
 ceiling->type = type;
 P_AddActiveCeiling(ceiling);
    }
    return rtn;
}





void P_AddActiveCeiling(ceiling_t* c)
{
    int i;

    for (i = 0; i < 30;i++)
    {
 if (activeceilings[i] == ((void*)0))
 {
     activeceilings[i] = c;
     return;
 }
    }
}






void P_RemoveActiveCeiling(ceiling_t* c)
{
    int i;

    for (i = 0;i < 30;i++)
    {
 if (activeceilings[i] == c)
 {
     activeceilings[i]->sector->specialdata = ((void*)0);
     P_RemoveThinker (&activeceilings[i]->thinker);
     activeceilings[i] = ((void*)0);
     break;
 }
    }
}






void P_ActivateInStasisCeiling(line_t* line)
{
    int i;

    for (i = 0;i < 30;i++)
    {
 if (activeceilings[i]
     && (activeceilings[i]->tag == line->tag)
     && (activeceilings[i]->direction == 0))
 {
     activeceilings[i]->direction = activeceilings[i]->olddirection;
     activeceilings[i]->thinker.function.acp1
       = (actionf_p1)T_MoveCeiling;
 }
    }
}







int EV_CeilingCrushStop(line_t *line)
{
    int i;
    int rtn;

    rtn = 0;
    for (i = 0;i < 30;i++)
    {
 if (activeceilings[i]
     && (activeceilings[i]->tag == line->tag)
     && (activeceilings[i]->direction != 0))
 {
     activeceilings[i]->olddirection = activeceilings[i]->direction;
     activeceilings[i]->thinker.function.acv = (actionf_v)((void*)0);
     activeceilings[i]->direction = 0;
     rtn = 1;
 }
    }


    return rtn;
}
void T_VerticalDoor (vldoor_t* door)
{
    result_e res;

    switch(door->direction)
    {
      case 0:

 if (!--door->topcountdown)
 {
     switch(door->type)
     {
       case vld_blazeRaise:
  door->direction = -1;
  S_StartSound(&door->sector->soundorg, sfx_bdcls);
  break;

       case vld_normal:
  door->direction = -1;
  S_StartSound(&door->sector->soundorg, sfx_dorcls);
  break;

       case vld_close30ThenOpen:
  door->direction = 1;
  S_StartSound(&door->sector->soundorg, sfx_doropn);
  break;

       default:
  break;
     }
 }
 break;

      case 2:

 if (!--door->topcountdown)
 {
     switch(door->type)
     {
       case vld_raiseIn5Mins:
  door->direction = 1;
  door->type = vld_normal;
  S_StartSound(&door->sector->soundorg, sfx_doropn);
  break;

       default:
  break;
     }
 }
 break;

      case -1:

 res = T_MovePlane(door->sector,
     door->speed,
     door->sector->floorheight,
     false,1,door->direction);
 if (res == pastdest)
 {
     switch(door->type)
     {
       case vld_blazeRaise:
       case vld_blazeClose:
  door->sector->specialdata = ((void*)0);
  P_RemoveThinker (&door->thinker);
  S_StartSound(&door->sector->soundorg, sfx_bdcls);
  break;

       case vld_normal:
       case vld_close:
  door->sector->specialdata = ((void*)0);
  P_RemoveThinker (&door->thinker);
  break;

       case vld_close30ThenOpen:
  door->direction = 0;
  door->topcountdown = 35*30;
  break;

       default:
  break;
     }
 }
 else if (res == crushed)
 {
     switch(door->type)
     {
       case vld_blazeClose:
       case vld_close:
  break;

       default:
  door->direction = 1;
  S_StartSound(&door->sector->soundorg, sfx_doropn);
  break;
     }
 }
 break;

      case 1:

 res = T_MovePlane(door->sector,
     door->speed,
     door->topheight,
     false,1,door->direction);

 if (res == pastdest)
 {
     switch(door->type)
     {
       case vld_blazeRaise:
       case vld_normal:
  door->direction = 0;
  door->topcountdown = door->topwait;
  break;

       case vld_close30ThenOpen:
       case vld_blazeOpen:
       case vld_open:
  door->sector->specialdata = ((void*)0);
  P_RemoveThinker (&door->thinker);
  break;

       default:
  break;
     }
 }
 break;
    }
}







int
EV_DoLockedDoor
( line_t* line,
  vldoor_e type,
  mobj_t* thing )
{
    player_t* p;

    p = thing->player;

    if (!p)
 return 0;

    switch(line->special)
    {
      case 99:
      case 133:
 if ( !p )
     return 0;
 if (!p->cards[it_bluecard] && !p->cards[it_blueskull])
 {
     p->message = ("You need a blue key to activate this object");
     S_StartSound(((void*)0),sfx_oof);
     return 0;
 }
 break;

      case 134:
      case 135:
 if ( !p )
     return 0;
 if (!p->cards[it_redcard] && !p->cards[it_redskull])
 {
     p->message = ("You need a red key to activate this object");
     S_StartSound(((void*)0),sfx_oof);
     return 0;
 }
 break;

      case 136:
      case 137:
 if ( !p )
     return 0;
 if (!p->cards[it_yellowcard] &&
     !p->cards[it_yellowskull])
 {
     p->message = ("You need a yellow key to activate this object");
     S_StartSound(((void*)0),sfx_oof);
     return 0;
 }
 break;
    }

    return EV_DoDoor(line,type);
}


int
EV_DoDoor
( line_t* line,
  vldoor_e type )
{
    int secnum,rtn;
    sector_t* sec;
    vldoor_t* door;

    secnum = -1;
    rtn = 0;

    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
 sec = &sectors[secnum];
 if (sec->specialdata)
     continue;



 rtn = 1;
 door = Z_Malloc (sizeof(*door), PU_LEVSPEC, 0);
 P_AddThinker (&door->thinker);
 sec->specialdata = door;

 door->thinker.function.acp1 = (actionf_p1) T_VerticalDoor;
 door->sector = sec;
 door->type = type;
 door->topwait = 150;
 door->speed = (1<<16)*2;

 switch(type)
 {
   case vld_blazeClose:
     door->topheight = P_FindLowestCeilingSurrounding(sec);
     door->topheight -= 4*(1<<16);
     door->direction = -1;
     door->speed = (1<<16)*2 * 4;
     S_StartSound(&door->sector->soundorg, sfx_bdcls);
     break;

   case vld_close:
     door->topheight = P_FindLowestCeilingSurrounding(sec);
     door->topheight -= 4*(1<<16);
     door->direction = -1;
     S_StartSound(&door->sector->soundorg, sfx_dorcls);
     break;

   case vld_close30ThenOpen:
     door->topheight = sec->ceilingheight;
     door->direction = -1;
     S_StartSound(&door->sector->soundorg, sfx_dorcls);
     break;

   case vld_blazeRaise:
   case vld_blazeOpen:
     door->direction = 1;
     door->topheight = P_FindLowestCeilingSurrounding(sec);
     door->topheight -= 4*(1<<16);
     door->speed = (1<<16)*2 * 4;
     if (door->topheight != sec->ceilingheight)
  S_StartSound(&door->sector->soundorg, sfx_bdopn);
     break;

   case vld_normal:
   case vld_open:
     door->direction = 1;
     door->topheight = P_FindLowestCeilingSurrounding(sec);
     door->topheight -= 4*(1<<16);
     if (door->topheight != sec->ceilingheight)
  S_StartSound(&door->sector->soundorg, sfx_doropn);
     break;

   default:
     break;
 }

    }
    return rtn;
}





void
EV_VerticalDoor
( line_t* line,
  mobj_t* thing )
{
    player_t* player;
    sector_t* sec;
    vldoor_t* door;
    int side;

    side = 0;


    player = thing->player;

    switch(line->special)
    {
      case 26:
      case 32:
 if ( !player )
     return;

 if (!player->cards[it_bluecard] && !player->cards[it_blueskull])
 {
     player->message = ("You need a blue key to open this door");
     S_StartSound(((void*)0),sfx_oof);
     return;
 }
 break;

      case 27:
      case 34:
 if ( !player )
     return;

 if (!player->cards[it_yellowcard] &&
     !player->cards[it_yellowskull])
 {
     player->message = ("You need a yellow key to open this door");
     S_StartSound(((void*)0),sfx_oof);
     return;
 }
 break;

      case 28:
      case 33:
 if ( !player )
     return;

 if (!player->cards[it_redcard] && !player->cards[it_redskull])
 {
     player->message = ("You need a red key to open this door");
     S_StartSound(((void*)0),sfx_oof);
     return;
 }
 break;
    }


    sec = sides[ line->sidenum[side^1]] .sector;

    if (sec->specialdata)
    {
 door = sec->specialdata;
 switch(line->special)
 {
   case 1:
   case 26:
   case 27:
   case 28:
   case 117:
     if (door->direction == -1)
  door->direction = 1;
     else
     {
  if (!thing->player)
      return;





                if (door->thinker.function.acp1 == (actionf_p1) T_VerticalDoor)
                {
                    door->direction = -1;
                }
                else if (door->thinker.function.acp1 == (actionf_p1) T_PlatRaise)
                {







                    plat_t *plat;

                    plat = (plat_t *) door;
                    plat->wait = -1;
                }
                else
                {


                    fprintf(__stderrp, "EV_VerticalDoor: Tried to close "
                                    "something that wasn't a door.\n");




                    door->direction = -1;
                }
     }
     return;
 }
    }


    switch(line->special)
    {
      case 117:
      case 118:
 S_StartSound(&sec->soundorg,sfx_bdopn);
 break;

      case 1:
      case 31:
 S_StartSound(&sec->soundorg,sfx_doropn);
 break;

      default:
 S_StartSound(&sec->soundorg,sfx_doropn);
 break;
    }



    door = Z_Malloc (sizeof(*door), PU_LEVSPEC, 0);
    P_AddThinker (&door->thinker);
    sec->specialdata = door;
    door->thinker.function.acp1 = (actionf_p1) T_VerticalDoor;
    door->sector = sec;
    door->direction = 1;
    door->speed = (1<<16)*2;
    door->topwait = 150;

    switch(line->special)
    {
      case 1:
      case 26:
      case 27:
      case 28:
 door->type = vld_normal;
 break;

      case 31:
      case 32:
      case 33:
      case 34:
 door->type = vld_open;
 line->special = 0;
 break;

      case 117:
 door->type = vld_blazeRaise;
 door->speed = (1<<16)*2*4;
 break;
      case 118:
 door->type = vld_blazeOpen;
 line->special = 0;
 door->speed = (1<<16)*2*4;
 break;
    }


    door->topheight = P_FindLowestCeilingSurrounding(sec);
    door->topheight -= 4*(1<<16);
}





void P_SpawnDoorCloseIn30 (sector_t* sec)
{
    vldoor_t* door;

    door = Z_Malloc ( sizeof(*door), PU_LEVSPEC, 0);

    P_AddThinker (&door->thinker);

    sec->specialdata = door;
    sec->special = 0;

    door->thinker.function.acp1 = (actionf_p1)T_VerticalDoor;
    door->sector = sec;
    door->direction = 0;
    door->type = vld_normal;
    door->speed = (1<<16)*2;
    door->topcountdown = 30 * 35;
}




void
P_SpawnDoorRaiseIn5Mins
( sector_t* sec,
  int secnum )
{
    vldoor_t* door;

    door = Z_Malloc ( sizeof(*door), PU_LEVSPEC, 0);

    P_AddThinker (&door->thinker);

    sec->specialdata = door;
    sec->special = 0;

    door->thinker.function.acp1 = (actionf_p1)T_VerticalDoor;
    door->sector = sec;
    door->direction = 2;
    door->type = vld_raiseIn5Mins;
    door->speed = (1<<16)*2;
    door->topheight = P_FindLowestCeilingSurrounding(sec);
    door->topheight -= 4*(1<<16);
    door->topwait = 150;
    door->topcountdown = 5 * 60 * 35;
}
typedef enum
{
    DI_EAST,
    DI_NORTHEAST,
    DI_NORTH,
    DI_NORTHWEST,
    DI_WEST,
    DI_SOUTHWEST,
    DI_SOUTH,
    DI_SOUTHEAST,
    DI_NODIR,
    NUMDIRS

} dirtype_t;





dirtype_t opposite[] =
{
  DI_WEST, DI_SOUTHWEST, DI_SOUTH, DI_SOUTHEAST,
  DI_EAST, DI_NORTHEAST, DI_NORTH, DI_NORTHWEST, DI_NODIR
};

dirtype_t diags[] =
{
    DI_NORTHWEST, DI_NORTHEAST, DI_SOUTHWEST, DI_SOUTHEAST
};





void A_Fall (mobj_t *actor);
mobj_t* soundtarget;

void
P_RecursiveSound
( sector_t* sec,
  int soundblocks )
{
    int i;
    line_t* check;
    sector_t* other;


    if (sec->validcount == validcount
 && sec->soundtraversed <= soundblocks+1)
    {
 return;
    }

    sec->validcount = validcount;
    sec->soundtraversed = soundblocks+1;
    sec->soundtarget = soundtarget;

    for (i=0 ;i<sec->linecount ; i++)
    {
 check = sec->lines[i];
 if (! (check->flags & 4) )
     continue;

 P_LineOpening (check);

 if (openrange <= 0)
     continue;

 if ( sides[ check->sidenum[0] ].sector == sec)
     other = sides[ check->sidenum[1] ] .sector;
 else
     other = sides[ check->sidenum[0] ].sector;

 if (check->flags & 64)
 {
     if (!soundblocks)
  P_RecursiveSound (other, 1);
 }
 else
     P_RecursiveSound (other, soundblocks);
    }
}
void
P_NoiseAlert
( mobj_t* target,
  mobj_t* emmiter )
{
    soundtarget = target;
    validcount++;
    P_RecursiveSound (emmiter->subsector->sector, 0);
}







boolean P_CheckMeleeRange (mobj_t* actor)
{
    mobj_t* pl;
    fixed_t dist;

    if (!actor->target)
 return false;

    pl = actor->target;
    dist = P_AproxDistance (pl->x-actor->x, pl->y-actor->y);

    if (dist >= (64*(1<<16))-20*(1<<16)+pl->info->radius)
 return false;

    if (! P_CheckSight (actor, actor->target) )
 return false;

    return true;
}




boolean P_CheckMissileRange (mobj_t* actor)
{
    fixed_t dist;

    if (! P_CheckSight (actor, actor->target) )
 return false;

    if ( actor->flags & MF_JUSTHIT )
    {


 actor->flags &= ~MF_JUSTHIT;
 return true;
    }

    if (actor->reactiontime)
 return false;


    dist = P_AproxDistance ( actor->x-actor->target->x,
        actor->y-actor->target->y) - 64*(1<<16);

    if (!actor->info->meleestate)
 dist -= 128*(1<<16);

    dist >>= 16;

    if (actor->type == MT_VILE)
    {
 if (dist > 14*64)
     return false;
    }


    if (actor->type == MT_UNDEAD)
    {
 if (dist < 196)
     return false;
 dist >>= 1;
    }


    if (actor->type == MT_CYBORG
 || actor->type == MT_SPIDER
 || actor->type == MT_SKULL)
    {
 dist >>= 1;
    }

    if (dist > 200)
 dist = 200;

    if (actor->type == MT_CYBORG && dist > 160)
 dist = 160;

    if (P_Random () < dist)
 return false;

    return true;
}







fixed_t xspeed[8] = {(1<<16),47000,0,-47000,-(1<<16),-47000,0,47000};
fixed_t yspeed[8] = {0,47000,(1<<16),47000,0,-47000,-(1<<16),-47000};

boolean P_Move (mobj_t* actor)
{
    fixed_t tryx;
    fixed_t tryy;

    line_t* ld;



    boolean try_ok;
    boolean good;

    if (actor->movedir == DI_NODIR)
 return false;

    if ((unsigned)actor->movedir >= 8)
 I_Error ("Weird actor->movedir!");

    tryx = actor->x + actor->info->speed*xspeed[actor->movedir];
    tryy = actor->y + actor->info->speed*yspeed[actor->movedir];

    try_ok = P_TryMove (actor, tryx, tryy);

    if (!try_ok)
    {

 if (actor->flags & MF_FLOAT && floatok)
 {

     if (actor->z < tmfloorz)
  actor->z += ((1<<16)*4);
     else
  actor->z -= ((1<<16)*4);

     actor->flags |= MF_INFLOAT;
     return true;
 }

 if (!numspechit)
     return false;

 actor->movedir = DI_NODIR;
 good = false;
 while (numspechit--)
 {
     ld = spechit[numspechit];



     if (P_UseSpecialLine (actor, ld,0))
  good = true;
 }
 return good;
    }
    else
    {
 actor->flags &= ~MF_INFLOAT;
    }


    if (! (actor->flags & MF_FLOAT) )
 actor->z = actor->floorz;
    return true;
}
boolean P_TryWalk (mobj_t* actor)
{
    if (!P_Move (actor))
    {
 return false;
    }

    actor->movecount = P_Random()&15;
    return true;
}




void P_NewChaseDir (mobj_t* actor)
{
    fixed_t deltax;
    fixed_t deltay;

    dirtype_t d[3];

    int tdir;
    dirtype_t olddir;

    dirtype_t turnaround;

    if (!actor->target)
 I_Error ("P_NewChaseDir: called with no target");

    olddir = actor->movedir;
    turnaround=opposite[olddir];

    deltax = actor->target->x - actor->x;
    deltay = actor->target->y - actor->y;

    if (deltax>10*(1<<16))
 d[1]= DI_EAST;
    else if (deltax<-10*(1<<16))
 d[1]= DI_WEST;
    else
 d[1]=DI_NODIR;

    if (deltay<-10*(1<<16))
 d[2]= DI_SOUTH;
    else if (deltay>10*(1<<16))
 d[2]= DI_NORTH;
    else
 d[2]=DI_NODIR;


    if (d[1] != DI_NODIR
 && d[2] != DI_NODIR)
    {
 actor->movedir = diags[((deltay<0)<<1)+(deltax>0)];
 if (actor->movedir != (int) turnaround && P_TryWalk(actor))
     return;
    }


    if (P_Random() > 200
 || abs(deltay)>abs(deltax))
    {
 tdir=d[1];
 d[1]=d[2];
 d[2]=tdir;
    }

    if (d[1]==turnaround)
 d[1]=DI_NODIR;
    if (d[2]==turnaround)
 d[2]=DI_NODIR;

    if (d[1]!=DI_NODIR)
    {
 actor->movedir = d[1];
 if (P_TryWalk(actor))
 {

     return;
 }
    }

    if (d[2]!=DI_NODIR)
    {
 actor->movedir =d[2];

 if (P_TryWalk(actor))
     return;
    }



    if (olddir!=DI_NODIR)
    {
 actor->movedir =olddir;

 if (P_TryWalk(actor))
     return;
    }


    if (P_Random()&1)
    {
 for ( tdir=DI_EAST;
       tdir<=DI_SOUTHEAST;
       tdir++ )
 {
     if (tdir != (int) turnaround)
     {
  actor->movedir =tdir;

  if ( P_TryWalk(actor) )
      return;
     }
 }
    }
    else
    {
 for ( tdir=DI_SOUTHEAST;
       tdir != (DI_EAST-1);
       tdir-- )
 {
     if (tdir != (int) turnaround)
     {
  actor->movedir = tdir;

  if ( P_TryWalk(actor) )
      return;
     }
 }
    }

    if (turnaround != DI_NODIR)
    {
 actor->movedir =turnaround;
 if ( P_TryWalk(actor) )
     return;
    }

    actor->movedir = DI_NODIR;
}
boolean
P_LookForPlayers
( mobj_t* actor,
  boolean allaround )
{
    int c;
    int stop;
    player_t* player;
    angle_t an;
    fixed_t dist;

    c = 0;
    stop = (actor->lastlook-1)&3;

    for ( ; ; actor->lastlook = (actor->lastlook+1)&3 )
    {
 if (!playeringame[actor->lastlook])
     continue;

 if (c++ == 2
     || actor->lastlook == stop)
 {

     return false;
 }

 player = &players[actor->lastlook];

 if (player->health <= 0)
     continue;

 if (!P_CheckSight (actor, player->mo))
     continue;

 if (!allaround)
 {
     an = R_PointToAngle2 (actor->x,
      actor->y,
      player->mo->x,
      player->mo->y)
  - actor->angle;

     if (an > 0x40000000 && an < 0xc0000000)
     {
  dist = P_AproxDistance (player->mo->x - actor->x,
     player->mo->y - actor->y);

  if (dist > (64*(1<<16)))
      continue;
     }
 }

 actor->target = player->mo;
 return true;
    }

    return false;
}







void A_KeenDie (mobj_t* mo)
{
    thinker_t* th;
    mobj_t* mo2;
    line_t junk;

    A_Fall (mo);



    for (th = thinkercap.next ; th != &thinkercap ; th=th->next)
    {
 if (th->function.acp1 != (actionf_p1)P_MobjThinker)
     continue;

 mo2 = (mobj_t *)th;
 if (mo2 != mo
     && mo2->type == mo->type
     && mo2->health > 0)
 {

     return;
 }
    }

    junk.tag = 666;
    EV_DoDoor(&junk, vld_open);
}
void A_Look (mobj_t* actor)
{
    mobj_t* targ;

    actor->threshold = 0;
    targ = actor->subsector->sector->soundtarget;

    if (targ
 && (targ->flags & MF_SHOOTABLE) )
    {
 actor->target = targ;

 if ( actor->flags & MF_AMBUSH )
 {
     if (P_CheckSight (actor, actor->target))
  goto seeyou;
 }
 else
     goto seeyou;
    }


    if (!P_LookForPlayers (actor, false) )
 return;


  seeyou:
    if (actor->info->seesound)
    {
 int sound;

 switch (actor->info->seesound)
 {
   case sfx_posit1:
   case sfx_posit2:
   case sfx_posit3:
     sound = sfx_posit1+P_Random()%3;
     break;

   case sfx_bgsit1:
   case sfx_bgsit2:
     sound = sfx_bgsit1+P_Random()%2;
     break;

   default:
     sound = actor->info->seesound;
     break;
 }

 if (actor->type==MT_SPIDER
     || actor->type == MT_CYBORG)
 {

     S_StartSound (((void*)0), sound);
 }
 else
     S_StartSound (actor, sound);
    }

    P_SetMobjState (actor, actor->info->seestate);
}







void A_Chase (mobj_t* actor)
{
    int delta;

    if (actor->reactiontime)
 actor->reactiontime--;



    if (actor->threshold)
    {
 if (!actor->target
     || actor->target->health <= 0)
 {
     actor->threshold = 0;
 }
 else
     actor->threshold--;
    }


    if (actor->movedir < 8)
    {
 actor->angle &= (7<<29);
 delta = actor->angle - (actor->movedir << 29);

 if (delta > 0)
     actor->angle -= 0x40000000/2;
 else if (delta < 0)
     actor->angle += 0x40000000/2;
    }

    if (!actor->target
 || !(actor->target->flags&MF_SHOOTABLE))
    {

 if (P_LookForPlayers(actor,true))
     return;

 P_SetMobjState (actor, actor->info->spawnstate);
 return;
    }


    if (actor->flags & MF_JUSTATTACKED)
    {
 actor->flags &= ~MF_JUSTATTACKED;
 if (gameskill != sk_nightmare && !fastparm)
     P_NewChaseDir (actor);
 return;
    }


    if (actor->info->meleestate
 && P_CheckMeleeRange (actor))
    {
 if (actor->info->attacksound)
     S_StartSound (actor, actor->info->attacksound);

 P_SetMobjState (actor, actor->info->meleestate);
 return;
    }


    if (actor->info->missilestate)
    {
 if (gameskill < sk_nightmare
     && !fastparm && actor->movecount)
 {
     goto nomissile;
 }

 if (!P_CheckMissileRange (actor))
     goto nomissile;

 P_SetMobjState (actor, actor->info->missilestate);
 actor->flags |= MF_JUSTATTACKED;
 return;
    }


  nomissile:

    if (netgame
 && !actor->threshold
 && !P_CheckSight (actor, actor->target) )
    {
 if (P_LookForPlayers(actor,true))
     return;
    }


    if (--actor->movecount<0
 || !P_Move (actor))
    {
 P_NewChaseDir (actor);
    }


    if (actor->info->activesound
 && P_Random () < 3)
    {
 S_StartSound (actor, actor->info->activesound);
    }
}





void A_FaceTarget (mobj_t* actor)
{
    if (!actor->target)
 return;

    actor->flags &= ~MF_AMBUSH;

    actor->angle = R_PointToAngle2 (actor->x,
        actor->y,
        actor->target->x,
        actor->target->y);

    if (actor->target->flags & MF_SHADOW)
 actor->angle += (P_Random()-P_Random())<<21;
}





void A_PosAttack (mobj_t* actor)
{
    int angle;
    int damage;
    int slope;

    if (!actor->target)
 return;

    A_FaceTarget (actor);
    angle = actor->angle;
    slope = P_AimLineAttack (actor, angle, (32*64*(1<<16)));

    S_StartSound (actor, sfx_pistol);
    angle += (P_Random()-P_Random())<<20;
    damage = ((P_Random()%5)+1)*3;
    P_LineAttack (actor, angle, (32*64*(1<<16)), slope, damage);
}

void A_SPosAttack (mobj_t* actor)
{
    int i;
    int angle;
    int bangle;
    int damage;
    int slope;

    if (!actor->target)
 return;

    S_StartSound (actor, sfx_shotgn);
    A_FaceTarget (actor);
    bangle = actor->angle;
    slope = P_AimLineAttack (actor, bangle, (32*64*(1<<16)));

    for (i=0 ; i<3 ; i++)
    {
 angle = bangle + ((P_Random()-P_Random())<<20);
 damage = ((P_Random()%5)+1)*3;
 P_LineAttack (actor, angle, (32*64*(1<<16)), slope, damage);
    }
}

void A_CPosAttack (mobj_t* actor)
{
    int angle;
    int bangle;
    int damage;
    int slope;

    if (!actor->target)
 return;

    S_StartSound (actor, sfx_shotgn);
    A_FaceTarget (actor);
    bangle = actor->angle;
    slope = P_AimLineAttack (actor, bangle, (32*64*(1<<16)));

    angle = bangle + ((P_Random()-P_Random())<<20);
    damage = ((P_Random()%5)+1)*3;
    P_LineAttack (actor, angle, (32*64*(1<<16)), slope, damage);
}

void A_CPosRefire (mobj_t* actor)
{

    A_FaceTarget (actor);

    if (P_Random () < 40)
 return;

    if (!actor->target
 || actor->target->health <= 0
 || !P_CheckSight (actor, actor->target) )
    {
 P_SetMobjState (actor, actor->info->seestate);
    }
}


void A_SpidRefire (mobj_t* actor)
{

    A_FaceTarget (actor);

    if (P_Random () < 10)
 return;

    if (!actor->target
 || actor->target->health <= 0
 || !P_CheckSight (actor, actor->target) )
    {
 P_SetMobjState (actor, actor->info->seestate);
    }
}

void A_BspiAttack (mobj_t *actor)
{
    if (!actor->target)
 return;

    A_FaceTarget (actor);


    P_SpawnMissile (actor, actor->target, MT_ARACHPLAZ);
}





void A_TroopAttack (mobj_t* actor)
{
    int damage;

    if (!actor->target)
 return;

    A_FaceTarget (actor);
    if (P_CheckMeleeRange (actor))
    {
 S_StartSound (actor, sfx_claw);
 damage = (P_Random()%8+1)*3;
 P_DamageMobj (actor->target, actor, actor, damage);
 return;
    }



    P_SpawnMissile (actor, actor->target, MT_TROOPSHOT);
}


void A_SargAttack (mobj_t* actor)
{
    int damage;

    if (!actor->target)
 return;

    A_FaceTarget (actor);
    if (P_CheckMeleeRange (actor))
    {
 damage = ((P_Random()%10)+1)*4;
 P_DamageMobj (actor->target, actor, actor, damage);
    }
}

void A_HeadAttack (mobj_t* actor)
{
    int damage;

    if (!actor->target)
 return;

    A_FaceTarget (actor);
    if (P_CheckMeleeRange (actor))
    {
 damage = (P_Random()%6+1)*10;
 P_DamageMobj (actor->target, actor, actor, damage);
 return;
    }


    P_SpawnMissile (actor, actor->target, MT_HEADSHOT);
}

void A_CyberAttack (mobj_t* actor)
{
    if (!actor->target)
 return;

    A_FaceTarget (actor);
    P_SpawnMissile (actor, actor->target, MT_ROCKET);
}


void A_BruisAttack (mobj_t* actor)
{
    int damage;

    if (!actor->target)
 return;

    if (P_CheckMeleeRange (actor))
    {
 S_StartSound (actor, sfx_claw);
 damage = (P_Random()%8+1)*10;
 P_DamageMobj (actor->target, actor, actor, damage);
 return;
    }


    P_SpawnMissile (actor, actor->target, MT_BRUISERSHOT);
}





void A_SkelMissile (mobj_t* actor)
{
    mobj_t* mo;

    if (!actor->target)
 return;

    A_FaceTarget (actor);
    actor->z += 16*(1<<16);
    mo = P_SpawnMissile (actor, actor->target, MT_TRACER);
    actor->z -= 16*(1<<16);

    mo->x += mo->momx;
    mo->y += mo->momy;
    mo->tracer = actor->target;
}

int TRACEANGLE = 0xc000000;

void A_Tracer (mobj_t* actor)
{
    angle_t exact;
    fixed_t dist;
    fixed_t slope;
    mobj_t* dest;
    mobj_t* th;

    if (gametic & 3)
 return;


    P_SpawnPuff (actor->x, actor->y, actor->z);

    th = P_SpawnMobj (actor->x-actor->momx,
        actor->y-actor->momy,
        actor->z, MT_SMOKE);

    th->momz = (1<<16);
    th->tics -= P_Random()&3;
    if (th->tics < 1)
 th->tics = 1;


    dest = actor->tracer;

    if (!dest || dest->health <= 0)
 return;


    exact = R_PointToAngle2 (actor->x,
        actor->y,
        dest->x,
        dest->y);

    if (exact != actor->angle)
    {
 if (exact - actor->angle > 0x80000000)
 {
     actor->angle -= TRACEANGLE;
     if (exact - actor->angle < 0x80000000)
  actor->angle = exact;
 }
 else
 {
     actor->angle += TRACEANGLE;
     if (exact - actor->angle > 0x80000000)
  actor->angle = exact;
 }
    }

    exact = actor->angle>>19;
    actor->momx = FixedMul (actor->info->speed, finecosine[exact]);
    actor->momy = FixedMul (actor->info->speed, finesine[exact]);


    dist = P_AproxDistance (dest->x - actor->x,
       dest->y - actor->y);

    dist = dist / actor->info->speed;

    if (dist < 1)
 dist = 1;
    slope = (dest->z+40*(1<<16) - actor->z) / dist;

    if (slope < actor->momz)
 actor->momz -= (1<<16)/8;
    else
 actor->momz += (1<<16)/8;
}


void A_SkelWhoosh (mobj_t* actor)
{
    if (!actor->target)
 return;
    A_FaceTarget (actor);
    S_StartSound (actor,sfx_skeswg);
}

void A_SkelFist (mobj_t* actor)
{
    int damage;

    if (!actor->target)
 return;

    A_FaceTarget (actor);

    if (P_CheckMeleeRange (actor))
    {
 damage = ((P_Random()%10)+1)*6;
 S_StartSound (actor, sfx_skepch);
 P_DamageMobj (actor->target, actor, actor, damage);
    }
}







mobj_t* corpsehit;
mobj_t* vileobj;
fixed_t viletryx;
fixed_t viletryy;

boolean PIT_VileCheck (mobj_t* thing)
{
    int maxdist;
    boolean check;

    if (!(thing->flags & MF_CORPSE) )
 return true;

    if (thing->tics != -1)
 return true;

    if (thing->info->raisestate == S_NULL)
 return true;

    maxdist = thing->info->radius + mobjinfo[MT_VILE].radius;

    if ( abs(thing->x - viletryx) > maxdist
  || abs(thing->y - viletryy) > maxdist )
 return true;

    corpsehit = thing;
    corpsehit->momx = corpsehit->momy = 0;
    corpsehit->height <<= 2;
    check = P_CheckPosition (corpsehit, corpsehit->x, corpsehit->y);
    corpsehit->height >>= 2;

    if (!check)
 return true;

    return false;
}







void A_VileChase (mobj_t* actor)
{
    int xl;
    int xh;
    int yl;
    int yh;

    int bx;
    int by;

    mobjinfo_t* info;
    mobj_t* temp;

    if (actor->movedir != DI_NODIR)
    {

 viletryx =
     actor->x + actor->info->speed*xspeed[actor->movedir];
 viletryy =
     actor->y + actor->info->speed*yspeed[actor->movedir];

 xl = (viletryx - bmaporgx - 32*(1<<16)*2)>>(16 +7);
 xh = (viletryx - bmaporgx + 32*(1<<16)*2)>>(16 +7);
 yl = (viletryy - bmaporgy - 32*(1<<16)*2)>>(16 +7);
 yh = (viletryy - bmaporgy + 32*(1<<16)*2)>>(16 +7);

 vileobj = actor;
 for (bx=xl ; bx<=xh ; bx++)
 {
     for (by=yl ; by<=yh ; by++)
     {



  if (!P_BlockThingsIterator(bx,by,PIT_VileCheck))
  {

      temp = actor->target;
      actor->target = corpsehit;
      A_FaceTarget (actor);
      actor->target = temp;

      P_SetMobjState (actor, S_VILE_HEAL1);
      S_StartSound (corpsehit, sfx_slop);
      info = corpsehit->info;

      P_SetMobjState (corpsehit,info->raisestate);
      corpsehit->height <<= 2;
      corpsehit->flags = info->flags;
      corpsehit->health = info->spawnhealth;
      corpsehit->target = ((void*)0);

      return;
  }
     }
 }
    }


    A_Chase (actor);
}





void A_VileStart (mobj_t* actor)
{
    S_StartSound (actor, sfx_vilatk);
}






void A_Fire (mobj_t* actor);

void A_StartFire (mobj_t* actor)
{
    S_StartSound(actor,sfx_flamst);
    A_Fire(actor);
}

void A_FireCrackle (mobj_t* actor)
{
    S_StartSound(actor,sfx_flame);
    A_Fire(actor);
}

void A_Fire (mobj_t* actor)
{
    mobj_t* dest;
    mobj_t* target;
    unsigned an;

    dest = actor->tracer;
    if (!dest)
 return;

    target = P_SubstNullMobj(actor->target);


    if (!P_CheckSight (target, dest) )
 return;

    an = dest->angle >> 19;

    P_UnsetThingPosition (actor);
    actor->x = dest->x + FixedMul (24*(1<<16), finecosine[an]);
    actor->y = dest->y + FixedMul (24*(1<<16), finesine[an]);
    actor->z = dest->z;
    P_SetThingPosition (actor);
}







void A_VileTarget (mobj_t* actor)
{
    mobj_t* fog;

    if (!actor->target)
 return;

    A_FaceTarget (actor);

    fog = P_SpawnMobj (actor->target->x,
         actor->target->x,
         actor->target->z, MT_FIRE);

    actor->tracer = fog;
    fog->target = actor;
    fog->tracer = actor->target;
    A_Fire (fog);
}







void A_VileAttack (mobj_t* actor)
{
    mobj_t* fire;
    int an;

    if (!actor->target)
 return;

    A_FaceTarget (actor);

    if (!P_CheckSight (actor, actor->target) )
 return;

    S_StartSound (actor, sfx_barexp);
    P_DamageMobj (actor->target, actor, actor, 20);
    actor->target->momz = 1000*(1<<16)/actor->target->info->mass;

    an = actor->angle >> 19;

    fire = actor->tracer;

    if (!fire)
 return;


    fire->x = actor->target->x - FixedMul (24*(1<<16), finecosine[an]);
    fire->y = actor->target->y - FixedMul (24*(1<<16), finesine[an]);
    P_RadiusAttack (fire, actor, 70 );
}
void A_FatRaise (mobj_t *actor)
{
    A_FaceTarget (actor);
    S_StartSound (actor, sfx_manatk);
}


void A_FatAttack1 (mobj_t* actor)
{
    mobj_t* mo;
    mobj_t* target;
    int an;

    A_FaceTarget (actor);


    actor->angle += (0x40000000/8);
    target = P_SubstNullMobj(actor->target);
    P_SpawnMissile (actor, target, MT_FATSHOT);

    mo = P_SpawnMissile (actor, target, MT_FATSHOT);
    mo->angle += (0x40000000/8);
    an = mo->angle >> 19;
    mo->momx = FixedMul (mo->info->speed, finecosine[an]);
    mo->momy = FixedMul (mo->info->speed, finesine[an]);
}

void A_FatAttack2 (mobj_t* actor)
{
    mobj_t* mo;
    mobj_t* target;
    int an;

    A_FaceTarget (actor);

    actor->angle -= (0x40000000/8);
    target = P_SubstNullMobj(actor->target);
    P_SpawnMissile (actor, target, MT_FATSHOT);

    mo = P_SpawnMissile (actor, target, MT_FATSHOT);
    mo->angle -= (0x40000000/8)*2;
    an = mo->angle >> 19;
    mo->momx = FixedMul (mo->info->speed, finecosine[an]);
    mo->momy = FixedMul (mo->info->speed, finesine[an]);
}

void A_FatAttack3 (mobj_t* actor)
{
    mobj_t* mo;
    mobj_t* target;
    int an;

    A_FaceTarget (actor);

    target = P_SubstNullMobj(actor->target);

    mo = P_SpawnMissile (actor, target, MT_FATSHOT);
    mo->angle -= (0x40000000/8)/2;
    an = mo->angle >> 19;
    mo->momx = FixedMul (mo->info->speed, finecosine[an]);
    mo->momy = FixedMul (mo->info->speed, finesine[an]);

    mo = P_SpawnMissile (actor, target, MT_FATSHOT);
    mo->angle += (0x40000000/8)/2;
    an = mo->angle >> 19;
    mo->momx = FixedMul (mo->info->speed, finecosine[an]);
    mo->momy = FixedMul (mo->info->speed, finesine[an]);
}
void A_SkullAttack (mobj_t* actor)
{
    mobj_t* dest;
    angle_t an;
    int dist;

    if (!actor->target)
 return;

    dest = actor->target;
    actor->flags |= MF_SKULLFLY;

    S_StartSound (actor, actor->info->attacksound);
    A_FaceTarget (actor);
    an = actor->angle >> 19;
    actor->momx = FixedMul ((20*(1<<16)), finecosine[an]);
    actor->momy = FixedMul ((20*(1<<16)), finesine[an]);
    dist = P_AproxDistance (dest->x - actor->x, dest->y - actor->y);
    dist = dist / (20*(1<<16));

    if (dist < 1)
 dist = 1;
    actor->momz = (dest->z+(dest->height>>1) - actor->z) / dist;
}






void
A_PainShootSkull
( mobj_t* actor,
  angle_t angle )
{
    fixed_t x;
    fixed_t y;
    fixed_t z;

    mobj_t* newmobj;
    angle_t an;
    int prestep;
    int count;
    thinker_t* currentthinker;


    count = 0;

    currentthinker = thinkercap.next;
    while (currentthinker != &thinkercap)
    {
 if ( (currentthinker->function.acp1 == (actionf_p1)P_MobjThinker)
     && ((mobj_t *)currentthinker)->type == MT_SKULL)
     count++;
 currentthinker = currentthinker->next;
    }



    if (count > 20)
 return;



    an = angle >> 19;

    prestep =
 4*(1<<16)
 + 3*(actor->info->radius + mobjinfo[MT_SKULL].radius)/2;

    x = actor->x + FixedMul (prestep, finecosine[an]);
    y = actor->y + FixedMul (prestep, finesine[an]);
    z = actor->z + 8*(1<<16);

    newmobj = P_SpawnMobj (x , y, z, MT_SKULL);


    if (!P_TryMove (newmobj, newmobj->x, newmobj->y))
    {

 P_DamageMobj (newmobj,actor,actor,10000);
 return;
    }

    newmobj->target = actor->target;
    A_SkullAttack (newmobj);
}






void A_PainAttack (mobj_t* actor)
{
    if (!actor->target)
 return;

    A_FaceTarget (actor);
    A_PainShootSkull (actor, actor->angle);
}


void A_PainDie (mobj_t* actor)
{
    A_Fall (actor);
    A_PainShootSkull (actor, actor->angle+0x40000000);
    A_PainShootSkull (actor, actor->angle+0x80000000);
    A_PainShootSkull (actor, actor->angle+0xc0000000);
}






void A_Scream (mobj_t* actor)
{
    int sound;

    switch (actor->info->deathsound)
    {
      case 0:
 return;

      case sfx_podth1:
      case sfx_podth2:
      case sfx_podth3:
 sound = sfx_podth1 + P_Random ()%3;
 break;

      case sfx_bgdth1:
      case sfx_bgdth2:
 sound = sfx_bgdth1 + P_Random ()%2;
 break;

      default:
 sound = actor->info->deathsound;
 break;
    }


    if (actor->type==MT_SPIDER
 || actor->type == MT_CYBORG)
    {

 S_StartSound (((void*)0), sound);
    }
    else
 S_StartSound (actor, sound);
}


void A_XScream (mobj_t* actor)
{
    S_StartSound (actor, sfx_slop);
}

void A_Pain (mobj_t* actor)
{
    if (actor->info->painsound)
 S_StartSound (actor, actor->info->painsound);
}



void A_Fall (mobj_t *actor)
{

    actor->flags &= ~MF_SOLID;



}





void A_Explode (mobj_t* thingy)
{
    P_RadiusAttack(thingy, thingy->target, 128);
}







static boolean CheckBossEnd(mobjtype_t motype)
{
    if (gameversion < exe_ultimate)
    {
        if (gamemap != 8)
        {
            return false;
        }



        if (motype == MT_BRUISER && gameepisode != 1)
        {
            return false;
        }

        return true;
    }
    else
    {





 switch(gameepisode)
 {
            case 1:
                return gamemap == 8 && motype == MT_BRUISER;

            case 2:
                return gamemap == 8 && motype == MT_CYBORG;

            case 3:
                return gamemap == 8 && motype == MT_SPIDER;

     case 4:
                return (gamemap == 6 && motype == MT_CYBORG)
                    || (gamemap == 8 && motype == MT_SPIDER);

            default:
                return gamemap == 8;
 }
    }
}






void A_BossDeath (mobj_t* mo)
{
    thinker_t* th;
    mobj_t* mo2;
    line_t junk;
    int i;

    if ( gamemode == commercial)
    {
 if (gamemap != 7)
     return;

 if ((mo->type != MT_FATSO)
     && (mo->type != MT_BABY))
     return;
    }
    else
    {
        if (!CheckBossEnd(mo->type))
        {
            return;
        }
    }


    for (i=0 ; i<4 ; i++)
 if (playeringame[i] && players[i].health > 0)
     break;

    if (i==4)
 return;



    for (th = thinkercap.next ; th != &thinkercap ; th=th->next)
    {
 if (th->function.acp1 != (actionf_p1)P_MobjThinker)
     continue;

 mo2 = (mobj_t *)th;
 if (mo2 != mo
     && mo2->type == mo->type
     && mo2->health > 0)
 {

     return;
 }
    }


    if ( gamemode == commercial)
    {
 if (gamemap == 7)
 {
     if (mo->type == MT_FATSO)
     {
  junk.tag = 666;
  EV_DoFloor(&junk,lowerFloorToLowest);
  return;
     }

     if (mo->type == MT_BABY)
     {
  junk.tag = 667;
  EV_DoFloor(&junk,raiseToTexture);
  return;
     }
 }
    }
    else
    {
 switch(gameepisode)
 {
   case 1:
     junk.tag = 666;
     EV_DoFloor (&junk, lowerFloorToLowest);
     return;
     break;

   case 4:
     switch(gamemap)
     {
       case 6:
  junk.tag = 666;
  EV_DoDoor (&junk, vld_blazeOpen);
  return;
  break;

       case 8:
  junk.tag = 666;
  EV_DoFloor (&junk, lowerFloorToLowest);
  return;
  break;
     }
 }
    }

    G_ExitLevel ();
}


void A_Hoof (mobj_t* mo)
{
    S_StartSound (mo, sfx_hoof);
    A_Chase (mo);
}

void A_Metal (mobj_t* mo)
{
    S_StartSound (mo, sfx_metal);
    A_Chase (mo);
}

void A_BabyMetal (mobj_t* mo)
{
    S_StartSound (mo, sfx_bspwlk);
    A_Chase (mo);
}

void
A_OpenShotgun2
( player_t* player,
  pspdef_t* psp )
{
    S_StartSound (player->mo, sfx_dbopn);
}

void
A_LoadShotgun2
( player_t* player,
  pspdef_t* psp )
{
    S_StartSound (player->mo, sfx_dbload);
}

void
A_ReFire
( player_t* player,
  pspdef_t* psp );

void
A_CloseShotgun2
( player_t* player,
  pspdef_t* psp )
{
    S_StartSound (player->mo, sfx_dbcls);
    A_ReFire(player,psp);
}



mobj_t* braintargets[32];
int numbraintargets;
int braintargeton = 0;

void A_BrainAwake (mobj_t* mo)
{
    thinker_t* thinker;
    mobj_t* m;


    numbraintargets = 0;
    braintargeton = 0;

    thinker = thinkercap.next;
    for (thinker = thinkercap.next ;
  thinker != &thinkercap ;
  thinker = thinker->next)
    {
 if (thinker->function.acp1 != (actionf_p1)P_MobjThinker)
     continue;

 m = (mobj_t *)thinker;

 if (m->type == MT_BOSSTARGET )
 {
     braintargets[numbraintargets] = m;
     numbraintargets++;
 }
    }

    S_StartSound (((void*)0),sfx_bossit);
}


void A_BrainPain (mobj_t* mo)
{
    S_StartSound (((void*)0),sfx_bospn);
}


void A_BrainScream (mobj_t* mo)
{
    int x;
    int y;
    int z;
    mobj_t* th;

    for (x=mo->x - 196*(1<<16) ; x< mo->x + 320*(1<<16) ; x+= (1<<16)*8)
    {
 y = mo->y - 320*(1<<16);
 z = 128 + P_Random()*2*(1<<16);
 th = P_SpawnMobj (x,y,z, MT_ROCKET);
 th->momz = P_Random()*512;

 P_SetMobjState (th, S_BRAINEXPLODE1);

 th->tics -= P_Random()&7;
 if (th->tics < 1)
     th->tics = 1;
    }

    S_StartSound (((void*)0),sfx_bosdth);
}



void A_BrainExplode (mobj_t* mo)
{
    int x;
    int y;
    int z;
    mobj_t* th;

    x = mo->x + (P_Random () - P_Random ())*2048;
    y = mo->y;
    z = 128 + P_Random()*2*(1<<16);
    th = P_SpawnMobj (x,y,z, MT_ROCKET);
    th->momz = P_Random()*512;

    P_SetMobjState (th, S_BRAINEXPLODE1);

    th->tics -= P_Random()&7;
    if (th->tics < 1)
 th->tics = 1;
}


void A_BrainDie (mobj_t* mo)
{
    G_ExitLevel ();
}

void A_BrainSpit (mobj_t* mo)
{
    mobj_t* targ;
    mobj_t* newmobj;

    static int easy = 0;

    easy ^= 1;
    if (gameskill <= sk_easy && (!easy))
 return;


    targ = braintargets[braintargeton];
    braintargeton = (braintargeton+1)%numbraintargets;


    newmobj = P_SpawnMissile (mo, targ, MT_SPAWNSHOT);
    newmobj->target = targ;
    newmobj->reactiontime =
 ((targ->y - mo->y)/newmobj->momy) / newmobj->state->tics;

    S_StartSound(((void*)0), sfx_bospit);
}



void A_SpawnFly (mobj_t* mo);


void A_SpawnSound (mobj_t* mo)
{
    S_StartSound (mo,sfx_boscub);
    A_SpawnFly(mo);
}

void A_SpawnFly (mobj_t* mo)
{
    mobj_t* newmobj;
    mobj_t* fog;
    mobj_t* targ;
    int r;
    mobjtype_t type;

    if (--mo->reactiontime)
 return;

    targ = P_SubstNullMobj(mo->target);


    fog = P_SpawnMobj (targ->x, targ->y, targ->z, MT_SPAWNFIRE);
    S_StartSound (fog, sfx_telept);


    r = P_Random ();



    if ( r<50 )
 type = MT_TROOP;
    else if (r<90)
 type = MT_SERGEANT;
    else if (r<120)
 type = MT_SHADOWS;
    else if (r<130)
 type = MT_PAIN;
    else if (r<160)
 type = MT_HEAD;
    else if (r<162)
 type = MT_VILE;
    else if (r<172)
 type = MT_UNDEAD;
    else if (r<192)
 type = MT_BABY;
    else if (r<222)
 type = MT_FATSO;
    else if (r<246)
 type = MT_KNIGHT;
    else
 type = MT_BRUISER;

    newmobj = P_SpawnMobj (targ->x, targ->y, targ->z, type);
    if (P_LookForPlayers (newmobj, true) )
 P_SetMobjState (newmobj, newmobj->info->seestate);


    P_TeleportMove (newmobj, newmobj->x, newmobj->y);


    P_RemoveMobj (mo);
}



void A_PlayerScream (mobj_t* mo)
{

    int sound = sfx_pldeth;

    if ( (gamemode == commercial)
 && (mo->health < -50))
    {


 sound = sfx_pdiehi;
    }

    S_StartSound (mo, sound);
}
result_e
T_MovePlane
( sector_t* sector,
  fixed_t speed,
  fixed_t dest,
  boolean crush,
  int floorOrCeiling,
  int direction )
{
    boolean flag;
    fixed_t lastpos;

    switch(floorOrCeiling)
    {
      case 0:

 switch(direction)
 {
   case -1:

     if (sector->floorheight - speed < dest)
     {
  lastpos = sector->floorheight;
  sector->floorheight = dest;
  flag = P_ChangeSector(sector,crush);
  if (flag == true)
  {
      sector->floorheight =lastpos;
      P_ChangeSector(sector,crush);

  }
  return pastdest;
     }
     else
     {
  lastpos = sector->floorheight;
  sector->floorheight -= speed;
  flag = P_ChangeSector(sector,crush);
  if (flag == true)
  {
      sector->floorheight = lastpos;
      P_ChangeSector(sector,crush);
      return crushed;
  }
     }
     break;

   case 1:

     if (sector->floorheight + speed > dest)
     {
  lastpos = sector->floorheight;
  sector->floorheight = dest;
  flag = P_ChangeSector(sector,crush);
  if (flag == true)
  {
      sector->floorheight = lastpos;
      P_ChangeSector(sector,crush);

  }
  return pastdest;
     }
     else
     {

  lastpos = sector->floorheight;
  sector->floorheight += speed;
  flag = P_ChangeSector(sector,crush);
  if (flag == true)
  {
      if (crush == true)
   return crushed;
      sector->floorheight = lastpos;
      P_ChangeSector(sector,crush);
      return crushed;
  }
     }
     break;
 }
 break;

      case 1:

 switch(direction)
 {
   case -1:

     if (sector->ceilingheight - speed < dest)
     {
  lastpos = sector->ceilingheight;
  sector->ceilingheight = dest;
  flag = P_ChangeSector(sector,crush);

  if (flag == true)
  {
      sector->ceilingheight = lastpos;
      P_ChangeSector(sector,crush);

  }
  return pastdest;
     }
     else
     {

  lastpos = sector->ceilingheight;
  sector->ceilingheight -= speed;
  flag = P_ChangeSector(sector,crush);

  if (flag == true)
  {
      if (crush == true)
   return crushed;
      sector->ceilingheight = lastpos;
      P_ChangeSector(sector,crush);
      return crushed;
  }
     }
     break;

   case 1:

     if (sector->ceilingheight + speed > dest)
     {
  lastpos = sector->ceilingheight;
  sector->ceilingheight = dest;
  flag = P_ChangeSector(sector,crush);
  if (flag == true)
  {
      sector->ceilingheight = lastpos;
      P_ChangeSector(sector,crush);

  }
  return pastdest;
     }
     else
     {
  lastpos = sector->ceilingheight;
  sector->ceilingheight += speed;
  flag = P_ChangeSector(sector,crush);
     }
     break;
 }
 break;

    }
    return ok;
}





void T_MoveFloor(floormove_t* floor)
{
    result_e res;

    res = T_MovePlane(floor->sector,
        floor->speed,
        floor->floordestheight,
        floor->crush,0,floor->direction);

    if (!(leveltime&7))
 S_StartSound(&floor->sector->soundorg, sfx_stnmov);

    if (res == pastdest)
    {
 floor->sector->specialdata = ((void*)0);

 if (floor->direction == 1)
 {
     switch(floor->type)
     {
       case donutRaise:
  floor->sector->special = floor->newspecial;
  floor->sector->floorpic = floor->texture;
       default:
  break;
     }
 }
 else if (floor->direction == -1)
 {
     switch(floor->type)
     {
       case lowerAndChange:
  floor->sector->special = floor->newspecial;
  floor->sector->floorpic = floor->texture;
       default:
  break;
     }
 }
 P_RemoveThinker(&floor->thinker);

 S_StartSound(&floor->sector->soundorg, sfx_pstop);
    }

}




int
EV_DoFloor
( line_t* line,
  floor_e floortype )
{
    int secnum;
    int rtn;
    int i;
    sector_t* sec;
    floormove_t* floor;

    secnum = -1;
    rtn = 0;
    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
 sec = &sectors[secnum];


 if (sec->specialdata)
     continue;


 rtn = 1;
 floor = Z_Malloc (sizeof(*floor), PU_LEVSPEC, 0);
 P_AddThinker (&floor->thinker);
 sec->specialdata = floor;
 floor->thinker.function.acp1 = (actionf_p1) T_MoveFloor;
 floor->type = floortype;
 floor->crush = false;

 switch(floortype)
 {
   case lowerFloor:
     floor->direction = -1;
     floor->sector = sec;
     floor->speed = (1<<16);
     floor->floordestheight =
  P_FindHighestFloorSurrounding(sec);
     break;

   case lowerFloorToLowest:
     floor->direction = -1;
     floor->sector = sec;
     floor->speed = (1<<16);
     floor->floordestheight =
  P_FindLowestFloorSurrounding(sec);
     break;

   case turboLower:
     floor->direction = -1;
     floor->sector = sec;
     floor->speed = (1<<16) * 4;
     floor->floordestheight =
  P_FindHighestFloorSurrounding(sec);
     if (floor->floordestheight != sec->floorheight)
  floor->floordestheight += 8*(1<<16);
     break;

   case raiseFloorCrush:
     floor->crush = true;
   case raiseFloor:
     floor->direction = 1;
     floor->sector = sec;
     floor->speed = (1<<16);
     floor->floordestheight =
  P_FindLowestCeilingSurrounding(sec);
     if (floor->floordestheight > sec->ceilingheight)
  floor->floordestheight = sec->ceilingheight;
     floor->floordestheight -= (8*(1<<16))*
  (floortype == raiseFloorCrush);
     break;

   case raiseFloorTurbo:
     floor->direction = 1;
     floor->sector = sec;
     floor->speed = (1<<16)*4;
     floor->floordestheight =
  P_FindNextHighestFloor(sec,sec->floorheight);
     break;

   case raiseFloorToNearest:
     floor->direction = 1;
     floor->sector = sec;
     floor->speed = (1<<16);
     floor->floordestheight =
  P_FindNextHighestFloor(sec,sec->floorheight);
     break;

   case raiseFloor24:
     floor->direction = 1;
     floor->sector = sec;
     floor->speed = (1<<16);
     floor->floordestheight = floor->sector->floorheight +
  24 * (1<<16);
     break;
   case raiseFloor512:
     floor->direction = 1;
     floor->sector = sec;
     floor->speed = (1<<16);
     floor->floordestheight = floor->sector->floorheight +
  512 * (1<<16);
     break;

   case raiseFloor24AndChange:
     floor->direction = 1;
     floor->sector = sec;
     floor->speed = (1<<16);
     floor->floordestheight = floor->sector->floorheight +
  24 * (1<<16);
     sec->floorpic = line->frontsector->floorpic;
     sec->special = line->frontsector->special;
     break;

   case raiseToTexture:
   {
       int minsize = 2147483647;
       side_t* side;

       floor->direction = 1;
       floor->sector = sec;
       floor->speed = (1<<16);
       for (i = 0; i < sec->linecount; i++)
       {
    if (twoSided (secnum, i) )
    {
        side = getSide(secnum,i,0);
        if (side->bottomtexture >= 0)
     if (textureheight[side->bottomtexture] <
         minsize)
         minsize =
      textureheight[side->bottomtexture];
        side = getSide(secnum,i,1);
        if (side->bottomtexture >= 0)
     if (textureheight[side->bottomtexture] <
         minsize)
         minsize =
      textureheight[side->bottomtexture];
    }
       }
       floor->floordestheight =
    floor->sector->floorheight + minsize;
   }
   break;

   case lowerAndChange:
     floor->direction = -1;
     floor->sector = sec;
     floor->speed = (1<<16);
     floor->floordestheight =
  P_FindLowestFloorSurrounding(sec);
     floor->texture = sec->floorpic;

     for (i = 0; i < sec->linecount; i++)
     {
  if ( twoSided(secnum, i) )
  {
      if (getSide(secnum,i,0)->sector-sectors == secnum)
      {
   sec = getSector(secnum,i,1);

   if (sec->floorheight == floor->floordestheight)
   {
       floor->texture = sec->floorpic;
       floor->newspecial = sec->special;
       break;
   }
      }
      else
      {
   sec = getSector(secnum,i,0);

   if (sec->floorheight == floor->floordestheight)
   {
       floor->texture = sec->floorpic;
       floor->newspecial = sec->special;
       break;
   }
      }
  }
     }
   default:
     break;
 }
    }
    return rtn;
}







int
EV_BuildStairs
( line_t* line,
  stair_e type )
{
    int secnum;
    int height;
    int i;
    int newsecnum;
    int texture;
    int ok;
    int rtn;

    sector_t* sec;
    sector_t* tsec;

    floormove_t* floor;

    fixed_t stairsize = 0;
    fixed_t speed = 0;

    secnum = -1;
    rtn = 0;
    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
 sec = &sectors[secnum];


 if (sec->specialdata)
     continue;


 rtn = 1;
 floor = Z_Malloc (sizeof(*floor), PU_LEVSPEC, 0);
 P_AddThinker (&floor->thinker);
 sec->specialdata = floor;
 floor->thinker.function.acp1 = (actionf_p1) T_MoveFloor;
 floor->direction = 1;
 floor->sector = sec;
 switch(type)
 {
   case build8:
     speed = (1<<16)/4;
     stairsize = 8*(1<<16);
     break;
   case turbo16:
     speed = (1<<16)*4;
     stairsize = 16*(1<<16);
     break;
 }
 floor->speed = speed;
 height = sec->floorheight + stairsize;
 floor->floordestheight = height;

 texture = sec->floorpic;




 do
 {
     ok = 0;
     for (i = 0;i < sec->linecount;i++)
     {
  if ( !((sec->lines[i])->flags & 4) )
      continue;

  tsec = (sec->lines[i])->frontsector;
  newsecnum = tsec-sectors;

  if (secnum != newsecnum)
      continue;

  tsec = (sec->lines[i])->backsector;
  newsecnum = tsec - sectors;

  if (tsec->floorpic != texture)
      continue;

  height += stairsize;

  if (tsec->specialdata)
      continue;

  sec = tsec;
  secnum = newsecnum;
  floor = Z_Malloc (sizeof(*floor), PU_LEVSPEC, 0);

  P_AddThinker (&floor->thinker);

  sec->specialdata = floor;
  floor->thinker.function.acp1 = (actionf_p1) T_MoveFloor;
  floor->direction = 1;
  floor->sector = sec;
  floor->speed = speed;
  floor->floordestheight = height;
  ok = 1;
  break;
     }
 } while(ok);
    }
    return rtn;
}
boolean P_GivePower(player_t*, int);
int maxammo[NUMAMMO] = {200, 50, 300, 50};
int clipammo[NUMAMMO] = {10, 4, 20, 1};
boolean
P_GiveAmmo
( player_t* player,
  ammotype_t ammo,
  int num )
{
    int oldammo;

    if (ammo == am_noammo)
 return false;

    if (ammo > NUMAMMO)
 I_Error ("P_GiveAmmo: bad type %i", ammo);

    if ( player->ammo[ammo] == player->maxammo[ammo] )
 return false;

    if (num)
 num *= clipammo[ammo];
    else
 num = clipammo[ammo]/2;

    if (gameskill == sk_baby
 || gameskill == sk_nightmare)
    {


 num <<= 1;
    }


    oldammo = player->ammo[ammo];
    player->ammo[ammo] += num;

    if (player->ammo[ammo] > player->maxammo[ammo])
 player->ammo[ammo] = player->maxammo[ammo];




    if (oldammo)
 return true;




    switch (ammo)
    {
      case am_clip:
 if (player->readyweapon == wp_fist)
 {
     if (player->weaponowned[wp_chaingun])
  player->pendingweapon = wp_chaingun;
     else
  player->pendingweapon = wp_pistol;
 }
 break;

      case am_shell:
 if (player->readyweapon == wp_fist
     || player->readyweapon == wp_pistol)
 {
     if (player->weaponowned[wp_shotgun])
  player->pendingweapon = wp_shotgun;
 }
 break;

      case am_cell:
 if (player->readyweapon == wp_fist
     || player->readyweapon == wp_pistol)
 {
     if (player->weaponowned[wp_plasma])
  player->pendingweapon = wp_plasma;
 }
 break;

      case am_misl:
 if (player->readyweapon == wp_fist)
 {
     if (player->weaponowned[wp_missile])
  player->pendingweapon = wp_missile;
 }
      default:
 break;
    }

    return true;
}






boolean
P_GiveWeapon
( player_t* player,
  weapontype_t weapon,
  boolean dropped )
{
    boolean gaveammo;
    boolean gaveweapon;

    if (netgame && (deathmatch!=2) && !dropped )
 {

  if (player->weaponowned[weapon])
   return false;

  player->bonuscount += 6;
  player->weaponowned[weapon] = true;

  if (deathmatch)
   P_GiveAmmo (player, weaponinfo[weapon].ammo, 5);
  else
   P_GiveAmmo (player, weaponinfo[weapon].ammo, 2);
  player->pendingweapon = weapon;

  if (player == &players[consoleplayer])
   S_StartSound (((void*)0), sfx_wpnup);
  return false;
    }

    if (weaponinfo[weapon].ammo != am_noammo)
    {


  if (dropped)
   gaveammo = P_GiveAmmo (player, weaponinfo[weapon].ammo, 1);
  else
   gaveammo = P_GiveAmmo (player, weaponinfo[weapon].ammo, 2);
    }
    else
    {
     gaveammo = false;
    }

    if (player->weaponowned[weapon])
    {
     gaveweapon = false;
    }
    else
    {
  gaveweapon = true;
  player->weaponowned[weapon] = true;
  player->pendingweapon = weapon;
    }

    return (gaveweapon || gaveammo);
}







boolean
P_GiveBody
( player_t* player,
  int num )
{
    if (player->health >= 100)
 return false;

    player->health += num;
    if (player->health > 100)
 player->health = 100;
    player->mo->health = player->health;

    return true;
}
boolean
P_GiveArmor
( player_t* player,
  int armortype )
{
    int hits;

    hits = armortype*100;
    if (player->armorpoints >= hits)
 return false;

    player->armortype = armortype;
    player->armorpoints = hits;

    return true;
}






void
P_GiveCard
( player_t* player,
  card_t card )
{
    if (player->cards[card])
 return;

    player->bonuscount = 6;
    player->cards[card] = 1;
}





boolean
P_GivePower
( player_t* player,
  int power )
{
    if (power == pw_invulnerability)
    {
 player->powers[power] = INVULNTICS;
 return true;
    }

    if (power == pw_invisibility)
    {
 player->powers[power] = INVISTICS;
 player->mo->flags |= MF_SHADOW;
 return true;
    }

    if (power == pw_infrared)
    {
 player->powers[power] = INFRATICS;
 return true;
    }

    if (power == pw_ironfeet)
    {
 player->powers[power] = IRONTICS;
 return true;
    }

    if (power == pw_strength)
    {
 P_GiveBody (player, 100);
 player->powers[power] = 1;
 return true;
    }

    if (player->powers[power])
 return false;

    player->powers[power] = 1;
    return true;
}






void
P_TouchSpecialThing
( mobj_t* special,
  mobj_t* toucher )
{
    player_t* player;
    int i;
    fixed_t delta;
    int sound;

    delta = special->z - toucher->z;

    if (delta > toucher->height
 || delta < -8*(1<<16))
    {

 return;
    }


    sound = sfx_itemup;
    player = toucher->player;



    if (toucher->health <= 0)
 return;


    switch (special->sprite)
    {

      case SPR_ARM1:
 if (!P_GiveArmor (player, 1))
     return;
 player->message = ("Picked up the armor.");
 break;

      case SPR_ARM2:
 if (!P_GiveArmor (player, 2))
     return;
 player->message = ("Picked up the MegaArmor!");
 break;


      case SPR_BON1:
 player->health++;
 if (player->health > 200)
     player->health = 200;
 player->mo->health = player->health;
 player->message = ("Picked up a health bonus.");
 break;

      case SPR_BON2:
 player->armorpoints++;
 if (player->armorpoints > 200)
     player->armorpoints = 200;


 if (!player->armortype)
     player->armortype = 1;
 player->message = ("Picked up an armor bonus.");
 break;

      case SPR_SOUL:
 player->health += 100;
 if (player->health > 200)
     player->health = 200;
 player->mo->health = player->health;
 player->message = ("Supercharge!");
 sound = sfx_getpow;
 break;

      case SPR_MEGA:
 if (gamemode != commercial)
     return;
 player->health = 200;
 player->mo->health = player->health;


 P_GiveArmor (player, 2);
 player->message = ("MegaSphere!");
 sound = sfx_getpow;
 break;



      case SPR_BKEY:
 if (!player->cards[it_bluecard])
     player->message = ("Picked up a blue keycard.");
 P_GiveCard (player, it_bluecard);
 if (!netgame)
     break;
 return;

      case SPR_YKEY:
 if (!player->cards[it_yellowcard])
     player->message = ("Picked up a yellow keycard.");
 P_GiveCard (player, it_yellowcard);
 if (!netgame)
     break;
 return;

      case SPR_RKEY:
 if (!player->cards[it_redcard])
     player->message = ("Picked up a red keycard.");
 P_GiveCard (player, it_redcard);
 if (!netgame)
     break;
 return;

      case SPR_BSKU:
 if (!player->cards[it_blueskull])
     player->message = ("Picked up a blue skull key.");
 P_GiveCard (player, it_blueskull);
 if (!netgame)
     break;
 return;

      case SPR_YSKU:
 if (!player->cards[it_yellowskull])
     player->message = ("Picked up a yellow skull key.");
 P_GiveCard (player, it_yellowskull);
 if (!netgame)
     break;
 return;

      case SPR_RSKU:
 if (!player->cards[it_redskull])
     player->message = ("Picked up a red skull key.");
 P_GiveCard (player, it_redskull);
 if (!netgame)
     break;
 return;


      case SPR_STIM:
 if (!P_GiveBody (player, 10))
     return;
 player->message = ("Picked up a stimpack.");
 break;

      case SPR_MEDI:
 if (!P_GiveBody (player, 25))
     return;

 if (player->health < 25)
     player->message = ("Picked up a medikit that you REALLY need!");
 else
     player->message = ("Picked up a medikit.");
 break;



      case SPR_PINV:
 if (!P_GivePower (player, pw_invulnerability))
     return;
 player->message = ("Invulnerability!");
 sound = sfx_getpow;
 break;

      case SPR_PSTR:
 if (!P_GivePower (player, pw_strength))
     return;
 player->message = ("Berserk!");
 if (player->readyweapon != wp_fist)
     player->pendingweapon = wp_fist;
 sound = sfx_getpow;
 break;

      case SPR_PINS:
 if (!P_GivePower (player, pw_invisibility))
     return;
 player->message = ("Partial Invisibility");
 sound = sfx_getpow;
 break;

      case SPR_SUIT:
 if (!P_GivePower (player, pw_ironfeet))
     return;
 player->message = ("Radiation Shielding Suit");
 sound = sfx_getpow;
 break;

      case SPR_PMAP:
 if (!P_GivePower (player, pw_allmap))
     return;
 player->message = ("Computer Area Map");
 sound = sfx_getpow;
 break;

      case SPR_PVIS:
 if (!P_GivePower (player, pw_infrared))
     return;
 player->message = ("Light Amplification Visor");
 sound = sfx_getpow;
 break;


      case SPR_CLIP:
 if (special->flags & MF_DROPPED)
 {
     if (!P_GiveAmmo (player,am_clip,0))
  return;
 }
 else
 {
     if (!P_GiveAmmo (player,am_clip,1))
  return;
 }
 player->message = ("Picked up a clip.");
 break;

      case SPR_AMMO:
 if (!P_GiveAmmo (player, am_clip,5))
     return;
 player->message = ("Picked up a box of bullets.");
 break;

      case SPR_ROCK:
 if (!P_GiveAmmo (player, am_misl,1))
     return;
 player->message = ("Picked up a rocket.");
 break;

      case SPR_BROK:
 if (!P_GiveAmmo (player, am_misl,5))
     return;
 player->message = ("Picked up a box of rockets.");
 break;

      case SPR_CELL:
 if (!P_GiveAmmo (player, am_cell,1))
     return;
 player->message = ("Picked up an energy cell.");
 break;

      case SPR_CELP:
 if (!P_GiveAmmo (player, am_cell,5))
     return;
 player->message = ("Picked up an energy cell pack.");
 break;

      case SPR_SHEL:
 if (!P_GiveAmmo (player, am_shell,1))
     return;
 player->message = ("Picked up 4 shotgun shells.");
 break;

      case SPR_SBOX:
 if (!P_GiveAmmo (player, am_shell,5))
     return;
 player->message = ("Picked up a box of shotgun shells.");
 break;

      case SPR_BPAK:
 if (!player->backpack)
 {
     for (i=0 ; i<NUMAMMO ; i++)
  player->maxammo[i] *= 2;
     player->backpack = true;
 }
 for (i=0 ; i<NUMAMMO ; i++)
     P_GiveAmmo (player, i, 1);
 player->message = ("Picked up a backpack full of ammo!");
 break;


      case SPR_BFUG:
 if (!P_GiveWeapon (player, wp_bfg, false) )
     return;
 player->message = ("You got the BFG9000!  Oh, yes.");
 sound = sfx_wpnup;
 break;

      case SPR_MGUN:
 if (!P_GiveWeapon (player, wp_chaingun, (special->flags&MF_DROPPED) != 0) )
     return;
 player->message = ("You got the chaingun!");
 sound = sfx_wpnup;
 break;

      case SPR_CSAW:
 if (!P_GiveWeapon (player, wp_chainsaw, false) )
     return;
 player->message = ("A chainsaw!  Find some meat!");
 sound = sfx_wpnup;
 break;

      case SPR_LAUN:
 if (!P_GiveWeapon (player, wp_missile, false) )
     return;
 player->message = ("You got the rocket launcher!");
 sound = sfx_wpnup;
 break;

      case SPR_PLAS:
 if (!P_GiveWeapon (player, wp_plasma, false) )
     return;
 player->message = ("You got the plasma gun!");
 sound = sfx_wpnup;
 break;

      case SPR_SHOT:
 if (!P_GiveWeapon (player, wp_shotgun, (special->flags&MF_DROPPED) != 0 ) )
     return;
 player->message = ("You got the shotgun!");
 sound = sfx_wpnup;
 break;

      case SPR_SGN2:
 if (!P_GiveWeapon (player, wp_supershotgun, (special->flags&MF_DROPPED) != 0 ) )
     return;
 player->message = ("You got the super shotgun!");
 sound = sfx_wpnup;
 break;

      default:
 I_Error ("P_SpecialThing: Unknown gettable thing");
    }

    if (special->flags & MF_COUNTITEM)
 player->itemcount++;
    P_RemoveMobj (special);
    player->bonuscount += 6;
    if (player == &players[consoleplayer])
 S_StartSound (((void*)0), sound);
}





void
P_KillMobj
( mobj_t* source,
  mobj_t* target )
{
    mobjtype_t item;
    mobj_t* mo;

    target->flags &= ~(MF_SHOOTABLE|MF_FLOAT|MF_SKULLFLY);

    if (target->type != MT_SKULL)
 target->flags &= ~MF_NOGRAVITY;

    target->flags |= MF_CORPSE|MF_DROPOFF;
    target->height >>= 2;

    if (source && source->player)
    {

 if (target->flags & MF_COUNTKILL)
     source->player->killcount++;

 if (target->player)
     source->player->frags[target->player-players]++;
    }
    else if (!netgame && (target->flags & MF_COUNTKILL) )
    {


 players[0].killcount++;
    }

    if (target->player)
    {

 if (!source)
     target->player->frags[target->player-players]++;

 target->flags &= ~MF_SOLID;
 target->player->playerstate = PST_DEAD;
 P_DropWeapon (target->player);

 if (target->player == &players[consoleplayer]
     && automapactive)
 {


     AM_Stop ();
 }

    }

    if (target->health < -target->info->spawnhealth
 && target->info->xdeathstate)
    {
 P_SetMobjState (target, target->info->xdeathstate);
    }
    else
 P_SetMobjState (target, target->info->deathstate);
    target->tics -= P_Random()&3;

    if (target->tics < 1)
 target->tics = 1;





    if (gameversion == exe_chex)
    {
        return;
    }




    switch (target->type)
    {
      case MT_WOLFSS:
      case MT_POSSESSED:
 item = MT_CLIP;
 break;

      case MT_SHOTGUY:
 item = MT_SHOTGUN;
 break;

      case MT_CHAINGUY:
 item = MT_CHAINGUN;
 break;

      default:
 return;
    }

    mo = P_SpawnMobj (target->x,target->y,(-2147483647-1), item);
    mo->flags |= MF_DROPPED;
}
void
P_DamageMobj
( mobj_t* target,
  mobj_t* inflictor,
  mobj_t* source,
  int damage )
{
    unsigned ang;
    int saved;
    player_t* player;
    fixed_t thrust;
    int temp;

    if ( !(target->flags & MF_SHOOTABLE) )
 return;

    if (target->health <= 0)
 return;

    if ( target->flags & MF_SKULLFLY )
    {
 target->momx = target->momy = target->momz = 0;
    }

    player = target->player;
    if (player && gameskill == sk_baby)
 damage >>= 1;





    if (inflictor
 && !(target->flags & MF_NOCLIP)
 && (!source
     || !source->player
     || source->player->readyweapon != wp_chainsaw))
    {
 ang = R_PointToAngle2 ( inflictor->x,
    inflictor->y,
    target->x,
    target->y);

 thrust = damage*((1<<16)>>3)*100/target->info->mass;


 if ( damage < 40
      && damage > target->health
      && target->z - inflictor->z > 64*(1<<16)
      && (P_Random ()&1) )
 {
     ang += 0x80000000;
     thrust *= 4;
 }

 ang >>= 19;
 target->momx += FixedMul (thrust, finecosine[ang]);
 target->momy += FixedMul (thrust, finesine[ang]);
    }


    if (player)
    {

 if (target->subsector->sector->special == 11
     && damage >= target->health)
 {
     damage = target->health - 1;
 }




 if ( damage < 1000
      && ( (player->cheats&CF_GODMODE)
    || player->powers[pw_invulnerability] ) )
 {
     return;
 }

 if (player->armortype)
 {
     if (player->armortype == 1)
  saved = damage/3;
     else
  saved = damage/2;

     if (player->armorpoints <= saved)
     {

  saved = player->armorpoints;
  player->armortype = 0;
     }
     player->armorpoints -= saved;
     damage -= saved;
 }
 player->health -= damage;
 if (player->health < 0)
     player->health = 0;

 player->attacker = source;
 player->damagecount += damage;

 if (player->damagecount > 100)
     player->damagecount = 100;

 temp = damage < 100 ? damage : 100;

 if (player == &players[consoleplayer])
     I_Tactile (40,10,40+temp*2);
    }


    target->health -= damage;
    if (target->health <= 0)
    {
 P_KillMobj (source, target);
 return;
    }

    if ( (P_Random () < target->info->painchance)
  && !(target->flags&MF_SKULLFLY) )
    {
 target->flags |= MF_JUSTHIT;

 P_SetMobjState (target, target->info->painstate);
    }

    target->reactiontime = 0;

    if ( (!target->threshold || target->type == MT_VILE)
  && source && source != target
  && source->type != MT_VILE)
    {


 target->target = source;
 target->threshold = 100;
 if (target->state == &states[target->info->spawnstate]
     && target->info->seestate != S_NULL)
     P_SetMobjState (target, target->info->seestate);
    }

}
void T_FireFlicker (fireflicker_t* flick)
{
    int amount;

    if (--flick->count)
 return;

    amount = (P_Random()&3)*16;

    if (flick->sector->lightlevel - amount < flick->minlight)
 flick->sector->lightlevel = flick->minlight;
    else
 flick->sector->lightlevel = flick->maxlight - amount;

    flick->count = 4;
}






void P_SpawnFireFlicker (sector_t* sector)
{
    fireflicker_t* flick;



    sector->special = 0;

    flick = Z_Malloc ( sizeof(*flick), PU_LEVSPEC, 0);

    P_AddThinker (&flick->thinker);

    flick->thinker.function.acp1 = (actionf_p1) T_FireFlicker;
    flick->sector = sector;
    flick->maxlight = sector->lightlevel;
    flick->minlight = P_FindMinSurroundingLight(sector,sector->lightlevel)+16;
    flick->count = 4;
}
void T_LightFlash (lightflash_t* flash)
{
    if (--flash->count)
 return;

    if (flash->sector->lightlevel == flash->maxlight)
    {
 flash-> sector->lightlevel = flash->minlight;
 flash->count = (P_Random()&flash->mintime)+1;
    }
    else
    {
 flash-> sector->lightlevel = flash->maxlight;
 flash->count = (P_Random()&flash->maxtime)+1;
    }

}
void P_SpawnLightFlash (sector_t* sector)
{
    lightflash_t* flash;


    sector->special = 0;

    flash = Z_Malloc ( sizeof(*flash), PU_LEVSPEC, 0);

    P_AddThinker (&flash->thinker);

    flash->thinker.function.acp1 = (actionf_p1) T_LightFlash;
    flash->sector = sector;
    flash->maxlight = sector->lightlevel;

    flash->minlight = P_FindMinSurroundingLight(sector,sector->lightlevel);
    flash->maxtime = 64;
    flash->mintime = 7;
    flash->count = (P_Random()&flash->maxtime)+1;
}
void T_StrobeFlash (strobe_t* flash)
{
    if (--flash->count)
 return;

    if (flash->sector->lightlevel == flash->minlight)
    {
 flash-> sector->lightlevel = flash->maxlight;
 flash->count = flash->brighttime;
    }
    else
    {
 flash-> sector->lightlevel = flash->minlight;
 flash->count =flash->darktime;
    }

}
void
P_SpawnStrobeFlash
( sector_t* sector,
  int fastOrSlow,
  int inSync )
{
    strobe_t* flash;

    flash = Z_Malloc ( sizeof(*flash), PU_LEVSPEC, 0);

    P_AddThinker (&flash->thinker);

    flash->sector = sector;
    flash->darktime = fastOrSlow;
    flash->brighttime = 5;
    flash->thinker.function.acp1 = (actionf_p1) T_StrobeFlash;
    flash->maxlight = sector->lightlevel;
    flash->minlight = P_FindMinSurroundingLight(sector, sector->lightlevel);

    if (flash->minlight == flash->maxlight)
 flash->minlight = 0;


    sector->special = 0;

    if (!inSync)
 flash->count = (P_Random()&7)+1;
    else
 flash->count = 1;
}





void EV_StartLightStrobing(line_t* line)
{
    int secnum;
    sector_t* sec;

    secnum = -1;
    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
 sec = &sectors[secnum];
 if (sec->specialdata)
     continue;

 P_SpawnStrobeFlash (sec,35, 0);
    }
}






void EV_TurnTagLightsOff(line_t* line)
{
    int i;
    int j;
    int min;
    sector_t* sector;
    sector_t* tsec;
    line_t* templine;

    sector = sectors;

    for (j = 0;j < numsectors; j++, sector++)
    {
 if (sector->tag == line->tag)
 {
     min = sector->lightlevel;
     for (i = 0;i < sector->linecount; i++)
     {
  templine = sector->lines[i];
  tsec = getNextSector(templine,sector);
  if (!tsec)
      continue;
  if (tsec->lightlevel < min)
      min = tsec->lightlevel;
     }
     sector->lightlevel = min;
 }
    }
}





void
EV_LightTurnOn
( line_t* line,
  int bright )
{
    int i;
    int j;
    sector_t* sector;
    sector_t* temp;
    line_t* templine;

    sector = sectors;

    for (i=0;i<numsectors;i++, sector++)
    {
 if (sector->tag == line->tag)
 {



     if (!bright)
     {
  for (j = 0;j < sector->linecount; j++)
  {
      templine = sector->lines[j];
      temp = getNextSector(templine,sector);

      if (!temp)
   continue;

      if (temp->lightlevel > bright)
   bright = temp->lightlevel;
  }
     }
     sector-> lightlevel = bright;
 }
    }
}






void T_Glow(glow_t* g)
{
    switch(g->direction)
    {
      case -1:

 g->sector->lightlevel -= 8;
 if (g->sector->lightlevel <= g->minlight)
 {
     g->sector->lightlevel += 8;
     g->direction = 1;
 }
 break;

      case 1:

 g->sector->lightlevel += 8;
 if (g->sector->lightlevel >= g->maxlight)
 {
     g->sector->lightlevel -= 8;
     g->direction = -1;
 }
 break;
    }
}


void P_SpawnGlowingLight(sector_t* sector)
{
    glow_t* g;

    g = Z_Malloc( sizeof(*g), PU_LEVSPEC, 0);

    P_AddThinker(&g->thinker);

    g->sector = sector;
    g->minlight = P_FindMinSurroundingLight(sector,sector->lightlevel);
    g->maxlight = sector->lightlevel;
    g->thinker.function.acp1 = (actionf_p1) T_Glow;
    g->direction = -1;

    sector->special = 0;
}
fixed_t tmbbox[4];
mobj_t* tmthing;
int tmflags;
fixed_t tmx;
fixed_t tmy;




boolean floatok;

fixed_t tmfloorz;
fixed_t tmceilingz;
fixed_t tmdropoffz;



line_t* ceilingline;




line_t* spechit[20];
int numspechit;
boolean PIT_StompThing (mobj_t* thing)
{
    fixed_t blockdist;

    if (!(thing->flags & MF_SHOOTABLE) )
 return true;

    blockdist = thing->radius + tmthing->radius;

    if ( abs(thing->x - tmx) >= blockdist
  || abs(thing->y - tmy) >= blockdist )
    {

 return true;
    }


    if (thing == tmthing)
 return true;


    if ( !tmthing->player && gamemap != 30)
 return false;

    P_DamageMobj (thing, tmthing, tmthing, 10000);

    return true;
}





boolean
P_TeleportMove
( mobj_t* thing,
  fixed_t x,
  fixed_t y )
{
    int xl;
    int xh;
    int yl;
    int yh;
    int bx;
    int by;

    subsector_t* newsubsec;


    tmthing = thing;
    tmflags = thing->flags;

    tmx = x;
    tmy = y;

    tmbbox[BOXTOP] = y + tmthing->radius;
    tmbbox[BOXBOTTOM] = y - tmthing->radius;
    tmbbox[BOXRIGHT] = x + tmthing->radius;
    tmbbox[BOXLEFT] = x - tmthing->radius;

    newsubsec = R_PointInSubsector (x,y);
    ceilingline = ((void*)0);





    tmfloorz = tmdropoffz = newsubsec->sector->floorheight;
    tmceilingz = newsubsec->sector->ceilingheight;

    validcount++;
    numspechit = 0;


    xl = (tmbbox[BOXLEFT] - bmaporgx - 32*(1<<16))>>(16 +7);
    xh = (tmbbox[BOXRIGHT] - bmaporgx + 32*(1<<16))>>(16 +7);
    yl = (tmbbox[BOXBOTTOM] - bmaporgy - 32*(1<<16))>>(16 +7);
    yh = (tmbbox[BOXTOP] - bmaporgy + 32*(1<<16))>>(16 +7);

    for (bx=xl ; bx<=xh ; bx++)
 for (by=yl ; by<=yh ; by++)
     if (!P_BlockThingsIterator(bx,by,PIT_StompThing))
  return false;



    P_UnsetThingPosition (thing);

    thing->floorz = tmfloorz;
    thing->ceilingz = tmceilingz;
    thing->x = x;
    thing->y = y;

    P_SetThingPosition (thing);

    return true;
}






static void SpechitOverrun(line_t *ld);





boolean PIT_CheckLine (line_t* ld)
{
    if (tmbbox[BOXRIGHT] <= ld->bbox[BOXLEFT]
 || tmbbox[BOXLEFT] >= ld->bbox[BOXRIGHT]
 || tmbbox[BOXTOP] <= ld->bbox[BOXBOTTOM]
 || tmbbox[BOXBOTTOM] >= ld->bbox[BOXTOP] )
 return true;

    if (P_BoxOnLineSide (tmbbox, ld) != -1)
 return true;
    if (!ld->backsector)
 return false;

    if (!(tmthing->flags & MF_MISSILE) )
    {
 if ( ld->flags & 1 )
     return false;

 if ( !tmthing->player && ld->flags & 2 )
     return false;
    }


    P_LineOpening (ld);


    if (opentop < tmceilingz)
    {
 tmceilingz = opentop;
 ceilingline = ld;
    }

    if (openbottom > tmfloorz)
 tmfloorz = openbottom;

    if (lowfloor < tmdropoffz)
 tmdropoffz = lowfloor;


    if (ld->special)
    {
        spechit[numspechit] = ld;
 numspechit++;


        if (numspechit > 8)
        {
            SpechitOverrun(ld);
        }
    }

    return true;
}




boolean PIT_CheckThing (mobj_t* thing)
{
    fixed_t blockdist;
    boolean solid;
    int damage;

    if (!(thing->flags & (MF_SOLID|MF_SPECIAL|MF_SHOOTABLE) ))
 return true;

    blockdist = thing->radius + tmthing->radius;

    if ( abs(thing->x - tmx) >= blockdist
  || abs(thing->y - tmy) >= blockdist )
    {

 return true;
    }


    if (thing == tmthing)
 return true;


    if (tmthing->flags & MF_SKULLFLY)
    {
 damage = ((P_Random()%8)+1)*tmthing->info->damage;

 P_DamageMobj (thing, tmthing, tmthing, damage);

 tmthing->flags &= ~MF_SKULLFLY;
 tmthing->momx = tmthing->momy = tmthing->momz = 0;

 P_SetMobjState (tmthing, tmthing->info->spawnstate);

 return false;
    }



    if (tmthing->flags & MF_MISSILE)
    {

 if (tmthing->z > thing->z + thing->height)
     return true;
 if (tmthing->z+tmthing->height < thing->z)
     return true;

 if (tmthing->target
         && (tmthing->target->type == thing->type ||
     (tmthing->target->type == MT_KNIGHT && thing->type == MT_BRUISER)||
     (tmthing->target->type == MT_BRUISER && thing->type == MT_KNIGHT) ) )
 {

     if (thing == tmthing->target)
  return true;





     if (thing->type != MT_PLAYER && !0)
     {


  return false;
     }
 }

 if (! (thing->flags & MF_SHOOTABLE) )
 {

     return !(thing->flags & MF_SOLID);
 }


 damage = ((P_Random()%8)+1)*tmthing->info->damage;
 P_DamageMobj (thing, tmthing, tmthing->target, damage);


 return false;
    }


    if (thing->flags & MF_SPECIAL)
    {
 solid = thing->flags&MF_SOLID;
 if (tmflags&MF_PICKUP)
 {

     P_TouchSpecialThing (thing, tmthing);
 }
 return !solid;
    }

    return !(thing->flags & MF_SOLID);
}
boolean
P_CheckPosition
( mobj_t* thing,
  fixed_t x,
  fixed_t y )
{
    int xl;
    int xh;
    int yl;
    int yh;
    int bx;
    int by;
    subsector_t* newsubsec;

    tmthing = thing;
    tmflags = thing->flags;

    tmx = x;
    tmy = y;

    tmbbox[BOXTOP] = y + tmthing->radius;
    tmbbox[BOXBOTTOM] = y - tmthing->radius;
    tmbbox[BOXRIGHT] = x + tmthing->radius;
    tmbbox[BOXLEFT] = x - tmthing->radius;

    newsubsec = R_PointInSubsector (x,y);
    ceilingline = ((void*)0);





    tmfloorz = tmdropoffz = newsubsec->sector->floorheight;
    tmceilingz = newsubsec->sector->ceilingheight;

    validcount++;
    numspechit = 0;

    if ( tmflags & MF_NOCLIP )
 return true;






    xl = (tmbbox[BOXLEFT] - bmaporgx - 32*(1<<16))>>(16 +7);
    xh = (tmbbox[BOXRIGHT] - bmaporgx + 32*(1<<16))>>(16 +7);
    yl = (tmbbox[BOXBOTTOM] - bmaporgy - 32*(1<<16))>>(16 +7);
    yh = (tmbbox[BOXTOP] - bmaporgy + 32*(1<<16))>>(16 +7);

    for (bx=xl ; bx<=xh ; bx++)
 for (by=yl ; by<=yh ; by++)
     if (!P_BlockThingsIterator(bx,by,PIT_CheckThing))
  return false;


    xl = (tmbbox[BOXLEFT] - bmaporgx)>>(16 +7);
    xh = (tmbbox[BOXRIGHT] - bmaporgx)>>(16 +7);
    yl = (tmbbox[BOXBOTTOM] - bmaporgy)>>(16 +7);
    yh = (tmbbox[BOXTOP] - bmaporgy)>>(16 +7);

    for (bx=xl ; bx<=xh ; bx++)
 for (by=yl ; by<=yh ; by++)
     if (!P_BlockLinesIterator (bx,by,PIT_CheckLine))
  return false;

    return true;
}







boolean
P_TryMove
( mobj_t* thing,
  fixed_t x,
  fixed_t y )
{
    fixed_t oldx;
    fixed_t oldy;
    int side;
    int oldside;
    line_t* ld;

    floatok = false;
    if (!P_CheckPosition (thing, x, y))
 return false;

    if ( !(thing->flags & MF_NOCLIP) )
    {
 if (tmceilingz - tmfloorz < thing->height)
     return false;

 floatok = true;

 if ( !(thing->flags&MF_TELEPORT)
      &&tmceilingz - thing->z < thing->height)
     return false;

 if ( !(thing->flags&MF_TELEPORT)
      && tmfloorz - thing->z > 24*(1<<16) )
     return false;

 if ( !(thing->flags&(MF_DROPOFF|MF_FLOAT))
      && tmfloorz - tmdropoffz > 24*(1<<16) )
     return false;
    }



    P_UnsetThingPosition (thing);

    oldx = thing->x;
    oldy = thing->y;
    thing->floorz = tmfloorz;
    thing->ceilingz = tmceilingz;
    thing->x = x;
    thing->y = y;

    P_SetThingPosition (thing);


    if (! (thing->flags&(MF_TELEPORT|MF_NOCLIP)) )
    {
 while (numspechit--)
 {

     ld = spechit[numspechit];
     side = P_PointOnLineSide (thing->x, thing->y, ld);
     oldside = P_PointOnLineSide (oldx, oldy, ld);
     if (side != oldside)
     {
  if (ld->special)
      P_CrossSpecialLine (ld-lines, oldside, thing);
     }
 }
    }

    return true;
}
boolean P_ThingHeightClip (mobj_t* thing)
{
    boolean onfloor;

    onfloor = (thing->z == thing->floorz);

    P_CheckPosition (thing, thing->x, thing->y);


    thing->floorz = tmfloorz;
    thing->ceilingz = tmceilingz;

    if (onfloor)
    {

 thing->z = thing->floorz;
    }
    else
    {

 if (thing->z+thing->height > thing->ceilingz)
     thing->z = thing->ceilingz - thing->height;
    }

    if (thing->ceilingz - thing->floorz < thing->height)
 return false;

    return true;
}







fixed_t bestslidefrac;
fixed_t secondslidefrac;

line_t* bestslideline;
line_t* secondslideline;

mobj_t* slidemo;

fixed_t tmxmove;
fixed_t tmymove;
void P_HitSlideLine (line_t* ld)
{
    int side;

    angle_t lineangle;
    angle_t moveangle;
    angle_t deltaangle;

    fixed_t movelen;
    fixed_t newlen;


    if (ld->slopetype == ST_HORIZONTAL)
    {
 tmymove = 0;
 return;
    }

    if (ld->slopetype == ST_VERTICAL)
    {
 tmxmove = 0;
 return;
    }

    side = P_PointOnLineSide (slidemo->x, slidemo->y, ld);

    lineangle = R_PointToAngle2 (0,0, ld->dx, ld->dy);

    if (side == 1)
 lineangle += 0x80000000;

    moveangle = R_PointToAngle2 (0,0, tmxmove, tmymove);
    deltaangle = moveangle-lineangle;

    if (deltaangle > 0x80000000)
 deltaangle += 0x80000000;


    lineangle >>= 19;
    deltaangle >>= 19;

    movelen = P_AproxDistance (tmxmove, tmymove);
    newlen = FixedMul (movelen, finecosine[deltaangle]);

    tmxmove = FixedMul (newlen, finecosine[lineangle]);
    tmymove = FixedMul (newlen, finesine[lineangle]);
}





boolean PTR_SlideTraverse (intercept_t* in)
{
    line_t* li;

    if (!in->isaline)
 I_Error ("PTR_SlideTraverse: not a line?");

    li = in->d.line;

    if ( ! (li->flags & 4) )
    {
 if (P_PointOnLineSide (slidemo->x, slidemo->y, li))
 {

     return true;
 }
 goto isblocking;
    }


    P_LineOpening (li);

    if (openrange < slidemo->height)
 goto isblocking;

    if (opentop - slidemo->z < slidemo->height)
 goto isblocking;

    if (openbottom - slidemo->z > 24*(1<<16) )
 goto isblocking;


    return true;



  isblocking:
    if (in->frac < bestslidefrac)
    {
 secondslidefrac = bestslidefrac;
 secondslideline = bestslideline;
 bestslidefrac = in->frac;
 bestslideline = li;
    }

    return false;
}
void P_SlideMove (mobj_t* mo)
{
    fixed_t leadx;
    fixed_t leady;
    fixed_t trailx;
    fixed_t traily;
    fixed_t newx;
    fixed_t newy;
    int hitcount;

    slidemo = mo;
    hitcount = 0;

  retry:
    if (++hitcount == 3)
 goto stairstep;



    if (mo->momx > 0)
    {
 leadx = mo->x + mo->radius;
 trailx = mo->x - mo->radius;
    }
    else
    {
 leadx = mo->x - mo->radius;
 trailx = mo->x + mo->radius;
    }

    if (mo->momy > 0)
    {
 leady = mo->y + mo->radius;
 traily = mo->y - mo->radius;
    }
    else
    {
 leady = mo->y - mo->radius;
 traily = mo->y + mo->radius;
    }

    bestslidefrac = (1<<16)+1;

    P_PathTraverse ( leadx, leady, leadx+mo->momx, leady+mo->momy,
       1, PTR_SlideTraverse );
    P_PathTraverse ( trailx, leady, trailx+mo->momx, leady+mo->momy,
       1, PTR_SlideTraverse );
    P_PathTraverse ( leadx, traily, leadx+mo->momx, traily+mo->momy,
       1, PTR_SlideTraverse );


    if (bestslidefrac == (1<<16)+1)
    {

      stairstep:
 if (!P_TryMove (mo, mo->x, mo->y + mo->momy))
     P_TryMove (mo, mo->x + mo->momx, mo->y);
 return;
    }


    bestslidefrac -= 0x800;
    if (bestslidefrac > 0)
    {
 newx = FixedMul (mo->momx, bestslidefrac);
 newy = FixedMul (mo->momy, bestslidefrac);

 if (!P_TryMove (mo, mo->x+newx, mo->y+newy))
     goto stairstep;
    }



    bestslidefrac = (1<<16)-(bestslidefrac+0x800);

    if (bestslidefrac > (1<<16))
 bestslidefrac = (1<<16);

    if (bestslidefrac <= 0)
 return;

    tmxmove = FixedMul (mo->momx, bestslidefrac);
    tmymove = FixedMul (mo->momy, bestslidefrac);

    P_HitSlideLine (bestslideline);

    mo->momx = tmxmove;
    mo->momy = tmymove;

    if (!P_TryMove (mo, mo->x+tmxmove, mo->y+tmymove))
    {
 goto retry;
    }
}





mobj_t* linetarget;
mobj_t* shootthing;



fixed_t shootz;

int la_damage;
fixed_t attackrange;

fixed_t aimslope;


extern fixed_t topslope;
extern fixed_t bottomslope;






boolean
PTR_AimTraverse (intercept_t* in)
{
    line_t* li;
    mobj_t* th;
    fixed_t slope;
    fixed_t thingtopslope;
    fixed_t thingbottomslope;
    fixed_t dist;

    if (in->isaline)
    {
 li = in->d.line;

 if ( !(li->flags & 4) )
     return false;




 P_LineOpening (li);

 if (openbottom >= opentop)
     return false;

 dist = FixedMul (attackrange, in->frac);

        if (li->backsector == ((void*)0)
         || li->frontsector->floorheight != li->backsector->floorheight)
 {
     slope = FixedDiv (openbottom - shootz , dist);
     if (slope > bottomslope)
  bottomslope = slope;
 }

 if (li->backsector == ((void*)0)
         || li->frontsector->ceilingheight != li->backsector->ceilingheight)
 {
     slope = FixedDiv (opentop - shootz , dist);
     if (slope < topslope)
  topslope = slope;
 }

 if (topslope <= bottomslope)
     return false;

 return true;
    }


    th = in->d.thing;
    if (th == shootthing)
 return true;

    if (!(th->flags&MF_SHOOTABLE))
 return true;


    dist = FixedMul (attackrange, in->frac);
    thingtopslope = FixedDiv (th->z+th->height - shootz , dist);

    if (thingtopslope < bottomslope)
 return true;

    thingbottomslope = FixedDiv (th->z - shootz, dist);

    if (thingbottomslope > topslope)
 return true;


    if (thingtopslope > topslope)
 thingtopslope = topslope;

    if (thingbottomslope < bottomslope)
 thingbottomslope = bottomslope;

    aimslope = (thingtopslope+thingbottomslope)/2;
    linetarget = th;

    return false;
}





boolean PTR_ShootTraverse (intercept_t* in)
{
    fixed_t x;
    fixed_t y;
    fixed_t z;
    fixed_t frac;

    line_t* li;

    mobj_t* th;

    fixed_t slope;
    fixed_t dist;
    fixed_t thingtopslope;
    fixed_t thingbottomslope;

    if (in->isaline)
    {
 li = in->d.line;

 if (li->special)
     P_ShootSpecialLine (shootthing, li);

 if ( !(li->flags & 4) )
     goto hitline;


 P_LineOpening (li);

 dist = FixedMul (attackrange, in->frac);




        if (li->backsector == ((void*)0))
        {
            slope = FixedDiv (openbottom - shootz , dist);
            if (slope > aimslope)
                goto hitline;

            slope = FixedDiv (opentop - shootz , dist);
            if (slope < aimslope)
                goto hitline;
        }
        else
        {
            if (li->frontsector->floorheight != li->backsector->floorheight)
            {
                slope = FixedDiv (openbottom - shootz , dist);
                if (slope > aimslope)
                    goto hitline;
            }

            if (li->frontsector->ceilingheight != li->backsector->ceilingheight)
            {
                slope = FixedDiv (opentop - shootz , dist);
                if (slope < aimslope)
                    goto hitline;
            }
        }


 return true;



      hitline:

 frac = in->frac - FixedDiv (4*(1<<16),attackrange);
 x = trace.x + FixedMul (trace.dx, frac);
 y = trace.y + FixedMul (trace.dy, frac);
 z = shootz + FixedMul (aimslope, FixedMul(frac, attackrange));

 if (li->frontsector->ceilingpic == skyflatnum)
 {

     if (z > li->frontsector->ceilingheight)
  return false;


     if (li->backsector && li->backsector->ceilingpic == skyflatnum)
  return false;
 }


 P_SpawnPuff (x,y,z);


 return false;
    }


    th = in->d.thing;
    if (th == shootthing)
 return true;

    if (!(th->flags&MF_SHOOTABLE))
 return true;


    dist = FixedMul (attackrange, in->frac);
    thingtopslope = FixedDiv (th->z+th->height - shootz , dist);

    if (thingtopslope < aimslope)
 return true;

    thingbottomslope = FixedDiv (th->z - shootz, dist);

    if (thingbottomslope > aimslope)
 return true;




    frac = in->frac - FixedDiv (10*(1<<16),attackrange);

    x = trace.x + FixedMul (trace.dx, frac);
    y = trace.y + FixedMul (trace.dy, frac);
    z = shootz + FixedMul (aimslope, FixedMul(frac, attackrange));



    if (in->d.thing->flags & MF_NOBLOOD)
 P_SpawnPuff (x,y,z);
    else
 P_SpawnBlood (x,y,z, la_damage);

    if (la_damage)
 P_DamageMobj (th, shootthing, shootthing, la_damage);


    return false;

}





fixed_t
P_AimLineAttack
( mobj_t* t1,
  angle_t angle,
  fixed_t distance )
{
    fixed_t x2;
    fixed_t y2;

    t1 = P_SubstNullMobj(t1);

    angle >>= 19;
    shootthing = t1;

    x2 = t1->x + (distance>>16)*finecosine[angle];
    y2 = t1->y + (distance>>16)*finesine[angle];
    shootz = t1->z + (t1->height>>1) + 8*(1<<16);


    topslope = 100*(1<<16)/160;
    bottomslope = -100*(1<<16)/160;

    attackrange = distance;
    linetarget = ((void*)0);

    P_PathTraverse ( t1->x, t1->y,
       x2, y2,
       1|2,
       PTR_AimTraverse );

    if (linetarget)
 return aimslope;

    return 0;
}







void
P_LineAttack
( mobj_t* t1,
  angle_t angle,
  fixed_t distance,
  fixed_t slope,
  int damage )
{
    fixed_t x2;
    fixed_t y2;

    angle >>= 19;
    shootthing = t1;
    la_damage = damage;
    x2 = t1->x + (distance>>16)*finecosine[angle];
    y2 = t1->y + (distance>>16)*finesine[angle];
    shootz = t1->z + (t1->height>>1) + 8*(1<<16);
    attackrange = distance;
    aimslope = slope;

    P_PathTraverse ( t1->x, t1->y,
       x2, y2,
       1|2,
       PTR_ShootTraverse );
}






mobj_t* usething;

boolean PTR_UseTraverse (intercept_t* in)
{
    int side;

    if (!in->d.line->special)
    {
 P_LineOpening (in->d.line);
 if (openrange <= 0)
 {
     S_StartSound (usething, sfx_noway);


     return false;
 }

 return true ;
    }

    side = 0;
    if (P_PointOnLineSide (usething->x, usething->y, in->d.line) == 1)
 side = 1;



    P_UseSpecialLine (usething, in->d.line, side);


    return false;
}






void P_UseLines (player_t* player)
{
    int angle;
    fixed_t x1;
    fixed_t y1;
    fixed_t x2;
    fixed_t y2;

    usething = player->mo;

    angle = player->mo->angle >> 19;

    x1 = player->mo->x;
    y1 = player->mo->y;
    x2 = x1 + ((64*(1<<16))>>16)*finecosine[angle];
    y2 = y1 + ((64*(1<<16))>>16)*finesine[angle];

    P_PathTraverse ( x1, y1, x2, y2, 1, PTR_UseTraverse );
}





mobj_t* bombsource;
mobj_t* bombspot;
int bombdamage;







boolean PIT_RadiusAttack (mobj_t* thing)
{
    fixed_t dx;
    fixed_t dy;
    fixed_t dist;

    if (!(thing->flags & MF_SHOOTABLE) )
 return true;



    if (thing->type == MT_CYBORG
 || thing->type == MT_SPIDER)
 return true;

    dx = abs(thing->x - bombspot->x);
    dy = abs(thing->y - bombspot->y);

    dist = dx>dy ? dx : dy;
    dist = (dist - thing->radius) >> 16;

    if (dist < 0)
 dist = 0;

    if (dist >= bombdamage)
 return true;

    if ( P_CheckSight (thing, bombspot) )
    {

 P_DamageMobj (thing, bombspot, bombsource, bombdamage - dist);
    }

    return true;
}






void
P_RadiusAttack
( mobj_t* spot,
  mobj_t* source,
  int damage )
{
    int x;
    int y;

    int xl;
    int xh;
    int yl;
    int yh;

    fixed_t dist;

    dist = (damage+32*(1<<16))<<16;
    yh = (spot->y + dist - bmaporgy)>>(16 +7);
    yl = (spot->y - dist - bmaporgy)>>(16 +7);
    xh = (spot->x + dist - bmaporgx)>>(16 +7);
    xl = (spot->x - dist - bmaporgx)>>(16 +7);
    bombspot = spot;
    bombsource = source;
    bombdamage = damage;

    for (y=yl ; y<=yh ; y++)
 for (x=xl ; x<=xh ; x++)
     P_BlockThingsIterator (x, y, PIT_RadiusAttack );
}
boolean crushchange;
boolean nofit;





boolean PIT_ChangeSector (mobj_t* thing)
{
    mobj_t* mo;

    if (P_ThingHeightClip (thing))
    {

 return true;
    }



    if (thing->health <= 0)
    {
 P_SetMobjState (thing, S_GIBS);

 thing->flags &= ~MF_SOLID;
 thing->height = 0;
 thing->radius = 0;


 return true;
    }


    if (thing->flags & MF_DROPPED)
    {
 P_RemoveMobj (thing);


 return true;
    }

    if (! (thing->flags & MF_SHOOTABLE) )
    {

 return true;
    }

    nofit = true;

    if (crushchange && !(leveltime&3) )
    {
 P_DamageMobj(thing,((void*)0),((void*)0),10);


 mo = P_SpawnMobj (thing->x,
     thing->y,
     thing->z + thing->height/2, MT_BLOOD);

 mo->momx = (P_Random() - P_Random ())<<12;
 mo->momy = (P_Random() - P_Random ())<<12;
    }


    return true;
}






boolean
P_ChangeSector
( sector_t* sector,
  boolean crunch )
{
    int x;
    int y;

    nofit = false;
    crushchange = crunch;


    for (x=sector->blockbox[BOXLEFT] ; x<= sector->blockbox[BOXRIGHT] ; x++)
 for (y=sector->blockbox[BOXBOTTOM];y<= sector->blockbox[BOXTOP] ; y++)
     P_BlockThingsIterator (x, y, PIT_ChangeSector);


    return nofit;
}





static void SpechitOverrun(line_t *ld)
{
    static unsigned int baseaddr = 0;
    unsigned int addr;

    if (baseaddr == 0)
    {
        int p;
        p = M_CheckParmWithArgs("-spechit", 1);

        if (p > 0)
        {
            M_StrToInt(myargv[p+1], (int *) &baseaddr);
        }
        else
        {
            baseaddr = 0x01C09C98;
        }
    }



    addr = baseaddr + (ld - lines) * 0x3E;

    switch(numspechit)
    {
        case 9:
        case 10:
        case 11:
        case 12:
            tmbbox[numspechit-9] = addr;
            break;
        case 13:
            crushchange = addr;
            break;
        case 14:
            nofit = addr;
            break;
        default:
            fprintf(__stderrp, "SpechitOverrun: Warning: unable to emulate"
                            "an overrun where numspechit=%i\n",
                            numspechit);
            break;
    }
}
fixed_t
P_AproxDistance
( fixed_t dx,
  fixed_t dy )
{
    dx = abs(dx);
    dy = abs(dy);
    if (dx < dy)
 return dx+dy-(dx>>1);
    return dx+dy-(dy>>1);
}






int
P_PointOnLineSide
( fixed_t x,
  fixed_t y,
  line_t* line )
{
    fixed_t dx;
    fixed_t dy;
    fixed_t left;
    fixed_t right;

    if (!line->dx)
    {
 if (x <= line->v1->x)
     return line->dy > 0;

 return line->dy < 0;
    }
    if (!line->dy)
    {
 if (y <= line->v1->y)
     return line->dx < 0;

 return line->dx > 0;
    }

    dx = (x - line->v1->x);
    dy = (y - line->v1->y);

    left = FixedMul ( line->dy>>16 , dx );
    right = FixedMul ( dy , line->dx>>16 );

    if (right < left)
 return 0;
    return 1;
}
int
P_BoxOnLineSide
( fixed_t* tmbox,
  line_t* ld )
{
    int p1 = 0;
    int p2 = 0;

    switch (ld->slopetype)
    {
      case ST_HORIZONTAL:
 p1 = tmbox[BOXTOP] > ld->v1->y;
 p2 = tmbox[BOXBOTTOM] > ld->v1->y;
 if (ld->dx < 0)
 {
     p1 ^= 1;
     p2 ^= 1;
 }
 break;

      case ST_VERTICAL:
 p1 = tmbox[BOXRIGHT] < ld->v1->x;
 p2 = tmbox[BOXLEFT] < ld->v1->x;
 if (ld->dy < 0)
 {
     p1 ^= 1;
     p2 ^= 1;
 }
 break;

      case ST_POSITIVE:
 p1 = P_PointOnLineSide (tmbox[BOXLEFT], tmbox[BOXTOP], ld);
 p2 = P_PointOnLineSide (tmbox[BOXRIGHT], tmbox[BOXBOTTOM], ld);
 break;

      case ST_NEGATIVE:
 p1 = P_PointOnLineSide (tmbox[BOXRIGHT], tmbox[BOXTOP], ld);
 p2 = P_PointOnLineSide (tmbox[BOXLEFT], tmbox[BOXBOTTOM], ld);
 break;
    }

    if (p1 == p2)
 return p1;
    return -1;
}






int
P_PointOnDivlineSide
( fixed_t x,
  fixed_t y,
  divline_t* line )
{
    fixed_t dx;
    fixed_t dy;
    fixed_t left;
    fixed_t right;

    if (!line->dx)
    {
 if (x <= line->x)
     return line->dy > 0;

 return line->dy < 0;
    }
    if (!line->dy)
    {
 if (y <= line->y)
     return line->dx < 0;

 return line->dx > 0;
    }

    dx = (x - line->x);
    dy = (y - line->y);


    if ( (line->dy ^ line->dx ^ dx ^ dy)&0x80000000 )
    {
 if ( (line->dy ^ dx) & 0x80000000 )
     return 1;
 return 0;
    }

    left = FixedMul ( line->dy>>8, dx>>8 );
    right = FixedMul ( dy>>8 , line->dx>>8 );

    if (right < left)
 return 0;
    return 1;
}






void
P_MakeDivline
( line_t* li,
  divline_t* dl )
{
    dl->x = li->v1->x;
    dl->y = li->v1->y;
    dl->dx = li->dx;
    dl->dy = li->dy;
}
fixed_t
P_InterceptVector
( divline_t* v2,
  divline_t* v1 )
{

    fixed_t frac;
    fixed_t num;
    fixed_t den;

    den = FixedMul (v1->dy>>8,v2->dx) - FixedMul(v1->dx>>8,v2->dy);

    if (den == 0)
 return 0;


    num =
 FixedMul ( (v1->x - v2->x)>>8 ,v1->dy )
 +FixedMul ( (v2->y - v1->y)>>8, v1->dx );

    frac = FixedDiv (num , den);

    return frac;
}
fixed_t opentop;
fixed_t openbottom;
fixed_t openrange;
fixed_t lowfloor;


void P_LineOpening (line_t* linedef)
{
    sector_t* front;
    sector_t* back;

    if (linedef->sidenum[1] == -1)
    {

 openrange = 0;
 return;
    }

    front = linedef->frontsector;
    back = linedef->backsector;

    if (front->ceilingheight < back->ceilingheight)
 opentop = front->ceilingheight;
    else
 opentop = back->ceilingheight;

    if (front->floorheight > back->floorheight)
    {
 openbottom = front->floorheight;
 lowfloor = back->floorheight;
    }
    else
    {
 openbottom = back->floorheight;
 lowfloor = front->floorheight;
    }

    openrange = opentop - openbottom;
}
void P_UnsetThingPosition (mobj_t* thing)
{
    int blockx;
    int blocky;

    if ( ! (thing->flags & MF_NOSECTOR) )
    {


 if (thing->snext)
     thing->snext->sprev = thing->sprev;

 if (thing->sprev)
     thing->sprev->snext = thing->snext;
 else
     thing->subsector->sector->thinglist = thing->snext;
    }

    if ( ! (thing->flags & MF_NOBLOCKMAP) )
    {


 if (thing->bnext)
     thing->bnext->bprev = thing->bprev;

 if (thing->bprev)
     thing->bprev->bnext = thing->bnext;
 else
 {
     blockx = (thing->x - bmaporgx)>>(16 +7);
     blocky = (thing->y - bmaporgy)>>(16 +7);

     if (blockx>=0 && blockx < bmapwidth
  && blocky>=0 && blocky <bmapheight)
     {
  blocklinks[blocky*bmapwidth+blockx] = thing->bnext;
     }
 }
    }
}
void
P_SetThingPosition (mobj_t* thing)
{
    subsector_t* ss;
    sector_t* sec;
    int blockx;
    int blocky;
    mobj_t** link;



    ss = R_PointInSubsector (thing->x,thing->y);
    thing->subsector = ss;

    if ( ! (thing->flags & MF_NOSECTOR) )
    {

 sec = ss->sector;

 thing->sprev = ((void*)0);
 thing->snext = sec->thinglist;

 if (sec->thinglist)
     sec->thinglist->sprev = thing;

 sec->thinglist = thing;
    }



    if ( ! (thing->flags & MF_NOBLOCKMAP) )
    {

 blockx = (thing->x - bmaporgx)>>(16 +7);
 blocky = (thing->y - bmaporgy)>>(16 +7);

 if (blockx>=0
     && blockx < bmapwidth
     && blocky>=0
     && blocky < bmapheight)
 {
     link = &blocklinks[blocky*bmapwidth+blockx];
     thing->bprev = ((void*)0);
     thing->bnext = *link;
     if (*link)
  (*link)->bprev = thing;

     *link = thing;
 }
 else
 {

     thing->bnext = thing->bprev = ((void*)0);
 }
    }
}
boolean
P_BlockLinesIterator
( int x,
  int y,
  boolean(*func)(line_t*) )
{
    int offset;
    short* list;
    line_t* ld;

    if (x<0
 || y<0
 || x>=bmapwidth
 || y>=bmapheight)
    {
 return true;
    }

    offset = y*bmapwidth+x;

    offset = *(blockmap+offset);

    for ( list = blockmaplump+offset ; *list != -1 ; list++)
    {
 ld = &lines[*list];

 if (ld->validcount == validcount)
     continue;

 ld->validcount = validcount;

 if ( !func(ld) )
     return false;
    }
    return true;
}





boolean
P_BlockThingsIterator
( int x,
  int y,
  boolean(*func)(mobj_t*) )
{
    mobj_t* mobj;

    if ( x<0
  || y<0
  || x>=bmapwidth
  || y>=bmapheight)
    {
 return true;
    }


    for (mobj = blocklinks[y*bmapwidth+x] ;
  mobj ;
  mobj = mobj->bnext)
    {
 if (!func( mobj ) )
     return false;
    }
    return true;
}






intercept_t intercepts[(128 + 61)];
intercept_t* intercept_p;

divline_t trace;
boolean earlyout;
int ptflags;

static void InterceptsOverrun(int num_intercepts, intercept_t *intercept);
boolean
PIT_AddLineIntercepts (line_t* ld)
{
    int s1;
    int s2;
    fixed_t frac;
    divline_t dl;


    if ( trace.dx > (1<<16)*16
  || trace.dy > (1<<16)*16
  || trace.dx < -(1<<16)*16
  || trace.dy < -(1<<16)*16)
    {
 s1 = P_PointOnDivlineSide (ld->v1->x, ld->v1->y, &trace);
 s2 = P_PointOnDivlineSide (ld->v2->x, ld->v2->y, &trace);
    }
    else
    {
 s1 = P_PointOnLineSide (trace.x, trace.y, ld);
 s2 = P_PointOnLineSide (trace.x+trace.dx, trace.y+trace.dy, ld);
    }

    if (s1 == s2)
 return true;


    P_MakeDivline (ld, &dl);
    frac = P_InterceptVector (&trace, &dl);

    if (frac < 0)
 return true;


    if (earlyout
 && frac < (1<<16)
 && !ld->backsector)
    {
 return false;
    }


    intercept_p->frac = frac;
    intercept_p->isaline = true;
    intercept_p->d.line = ld;
    InterceptsOverrun(intercept_p - intercepts, intercept_p);
    intercept_p++;

    return true;
}






boolean PIT_AddThingIntercepts (mobj_t* thing)
{
    fixed_t x1;
    fixed_t y1;
    fixed_t x2;
    fixed_t y2;

    int s1;
    int s2;

    boolean tracepositive;

    divline_t dl;

    fixed_t frac;

    tracepositive = (trace.dx ^ trace.dy)>0;


    if (tracepositive)
    {
 x1 = thing->x - thing->radius;
 y1 = thing->y + thing->radius;

 x2 = thing->x + thing->radius;
 y2 = thing->y - thing->radius;
    }
    else
    {
 x1 = thing->x - thing->radius;
 y1 = thing->y - thing->radius;

 x2 = thing->x + thing->radius;
 y2 = thing->y + thing->radius;
    }

    s1 = P_PointOnDivlineSide (x1, y1, &trace);
    s2 = P_PointOnDivlineSide (x2, y2, &trace);

    if (s1 == s2)
 return true;

    dl.x = x1;
    dl.y = y1;
    dl.dx = x2-x1;
    dl.dy = y2-y1;

    frac = P_InterceptVector (&trace, &dl);

    if (frac < 0)
 return true;

    intercept_p->frac = frac;
    intercept_p->isaline = false;
    intercept_p->d.thing = thing;
    InterceptsOverrun(intercept_p - intercepts, intercept_p);
    intercept_p++;

    return true;
}







boolean
P_TraverseIntercepts
( traverser_t func,
  fixed_t maxfrac )
{
    int count;
    fixed_t dist;
    intercept_t* scan;
    intercept_t* in;

    count = intercept_p - intercepts;

    in = 0;

    while (count--)
    {
 dist = 2147483647;
 for (scan = intercepts ; scan<intercept_p ; scan++)
 {
     if (scan->frac < dist)
     {
  dist = scan->frac;
  in = scan;
     }
 }

 if (dist > maxfrac)
     return true;
        if ( !func (in) )
     return false;

 in->frac = 2147483647;
    }

    return true;
}

extern fixed_t bulletslope;






typedef struct
{
    int len;
    void *addr;
    boolean int16_array;
} intercepts_overrun_t;
static intercepts_overrun_t intercepts_overrun[] =
{
    {4, ((void*)0), false},
    {4, ((void*)0), false},
    {4, ((void*)0), false},
    {4, &lowfloor, false},
    {4, &openbottom, false},
    {4, &opentop, false},
    {4, &openrange, false},
    {4, ((void*)0), false},
    {120, ((void*)0), false},
    {8, ((void*)0), false},
    {4, &bulletslope, false},
    {4, ((void*)0), false},
    {4, ((void*)0), false},
    {4, ((void*)0), false},
    {40, &playerstarts, true},
    {4, ((void*)0), false},
    {4, &bmapwidth, false},
    {4, ((void*)0), false},
    {4, &bmaporgx, false},
    {4, &bmaporgy, false},
    {4, ((void*)0), false},
    {4, &bmapheight, false},
    {0, ((void*)0), false},
};



static void InterceptsMemoryOverrun(int location, int value)
{
    int i, offset;
    int index;
    void *addr;

    i = 0;
    offset = 0;



    while (intercepts_overrun[i].len != 0)
    {
        if (offset + intercepts_overrun[i].len > location)
        {
            addr = intercepts_overrun[i].addr;




            if (addr != ((void*)0))
            {
                if (intercepts_overrun[i].int16_array)
                {
                    index = (location - offset) / 2;
                    ((short *) addr)[index] = value & 0xffff;
                    ((short *) addr)[index + 1] = (value >> 16) & 0xffff;
                }
                else
                {
                    index = (location - offset) / 4;
                    ((int *) addr)[index] = value;
                }
            }

            break;
        }

        offset += intercepts_overrun[i].len;
        ++i;
    }
}



static void InterceptsOverrun(int num_intercepts, intercept_t *intercept)
{
    int location;

    if (num_intercepts <= 128)
    {


        return;
    }

    location = (num_intercepts - 128 - 1) * 12;
    InterceptsMemoryOverrun(location, intercept->frac);
    InterceptsMemoryOverrun(location + 4, intercept->isaline);
    InterceptsMemoryOverrun(location + 8, (int) intercept->d.thing);
}
boolean
P_PathTraverse
( fixed_t x1,
  fixed_t y1,
  fixed_t x2,
  fixed_t y2,
  int flags,
  boolean (*trav) (intercept_t *))
{
    fixed_t xt1;
    fixed_t yt1;
    fixed_t xt2;
    fixed_t yt2;

    fixed_t xstep;
    fixed_t ystep;

    fixed_t partial;

    fixed_t xintercept;
    fixed_t yintercept;

    int mapx;
    int mapy;

    int mapxstep;
    int mapystep;

    int count;

    earlyout = flags & 4;

    validcount++;
    intercept_p = intercepts;

    if ( ((x1-bmaporgx)&((128*(1<<16))-1)) == 0)
 x1 += (1<<16);

    if ( ((y1-bmaporgy)&((128*(1<<16))-1)) == 0)
 y1 += (1<<16);

    trace.x = x1;
    trace.y = y1;
    trace.dx = x2 - x1;
    trace.dy = y2 - y1;

    x1 -= bmaporgx;
    y1 -= bmaporgy;
    xt1 = x1>>(16 +7);
    yt1 = y1>>(16 +7);

    x2 -= bmaporgx;
    y2 -= bmaporgy;
    xt2 = x2>>(16 +7);
    yt2 = y2>>(16 +7);

    if (xt2 > xt1)
    {
 mapxstep = 1;
 partial = (1<<16) - ((x1>>((16 +7)-16))&((1<<16)-1));
 ystep = FixedDiv (y2-y1,abs(x2-x1));
    }
    else if (xt2 < xt1)
    {
 mapxstep = -1;
 partial = (x1>>((16 +7)-16))&((1<<16)-1);
 ystep = FixedDiv (y2-y1,abs(x2-x1));
    }
    else
    {
 mapxstep = 0;
 partial = (1<<16);
 ystep = 256*(1<<16);
    }

    yintercept = (y1>>((16 +7)-16)) + FixedMul (partial, ystep);


    if (yt2 > yt1)
    {
 mapystep = 1;
 partial = (1<<16) - ((y1>>((16 +7)-16))&((1<<16)-1));
 xstep = FixedDiv (x2-x1,abs(y2-y1));
    }
    else if (yt2 < yt1)
    {
 mapystep = -1;
 partial = (y1>>((16 +7)-16))&((1<<16)-1);
 xstep = FixedDiv (x2-x1,abs(y2-y1));
    }
    else
    {
 mapystep = 0;
 partial = (1<<16);
 xstep = 256*(1<<16);
    }
    xintercept = (x1>>((16 +7)-16)) + FixedMul (partial, xstep);




    mapx = xt1;
    mapy = yt1;

    for (count = 0 ; count < 64 ; count++)
    {
 if (flags & 1)
 {
     if (!P_BlockLinesIterator (mapx, mapy,PIT_AddLineIntercepts))
  return false;
 }

 if (flags & 2)
 {
     if (!P_BlockThingsIterator (mapx, mapy,PIT_AddThingIntercepts))
  return false;
 }

 if (mapx == xt2
     && mapy == yt2)
 {
     break;
 }

 if ( (yintercept >> 16) == mapy)
 {
     yintercept += ystep;
     mapx += mapxstep;
 }
 else if ( (xintercept >> 16) == mapx)
 {
     xintercept += xstep;
     mapy += mapystep;
 }

    }

    return P_TraverseIntercepts ( trav, (1<<16) );
}
void G_PlayerReborn (int player);
void P_SpawnMapThing (mapthing_t* mthing);






int test;

boolean
P_SetMobjState
( mobj_t* mobj,
  statenum_t state )
{
    state_t* st;

    do
    {
 if (state == S_NULL)
 {
     mobj->state = (state_t *) S_NULL;
     P_RemoveMobj (mobj);
     return false;
 }

 st = &states[state];
 mobj->state = st;
 mobj->tics = st->tics;
 mobj->sprite = st->sprite;
 mobj->frame = st->frame;



 if (st->action.acp1)
     st->action.acp1(mobj);

 state = st->nextstate;
    } while (!mobj->tics);

    return true;
}





void P_ExplodeMissile (mobj_t* mo)
{
    mo->momx = mo->momy = mo->momz = 0;

    P_SetMobjState (mo, mobjinfo[mo->type].deathstate);

    mo->tics -= P_Random()&3;

    if (mo->tics < 1)
 mo->tics = 1;

    mo->flags &= ~MF_MISSILE;

    if (mo->info->deathsound)
 S_StartSound (mo, mo->info->deathsound);
}
void P_XYMovement (mobj_t* mo)
{
    fixed_t ptryx;
    fixed_t ptryy;
    player_t* player;
    fixed_t xmove;
    fixed_t ymove;

    if (!mo->momx && !mo->momy)
    {
 if (mo->flags & MF_SKULLFLY)
 {

     mo->flags &= ~MF_SKULLFLY;
     mo->momx = mo->momy = mo->momz = 0;

     P_SetMobjState (mo, mo->info->spawnstate);
 }
 return;
    }

    player = mo->player;

    if (mo->momx > (30*(1<<16)))
 mo->momx = (30*(1<<16));
    else if (mo->momx < -(30*(1<<16)))
 mo->momx = -(30*(1<<16));

    if (mo->momy > (30*(1<<16)))
 mo->momy = (30*(1<<16));
    else if (mo->momy < -(30*(1<<16)))
 mo->momy = -(30*(1<<16));

    xmove = mo->momx;
    ymove = mo->momy;

    do
    {
 if (xmove > (30*(1<<16))/2 || ymove > (30*(1<<16))/2)
 {
     ptryx = mo->x + xmove/2;
     ptryy = mo->y + ymove/2;
     xmove >>= 1;
     ymove >>= 1;
 }
 else
 {
     ptryx = mo->x + xmove;
     ptryy = mo->y + ymove;
     xmove = ymove = 0;
 }

 if (!P_TryMove (mo, ptryx, ptryy))
 {

     if (mo->player)
     {
  P_SlideMove (mo);
     }
     else if (mo->flags & MF_MISSILE)
     {

  if (ceilingline &&
      ceilingline->backsector &&
      ceilingline->backsector->ceilingpic == skyflatnum)
  {



      P_RemoveMobj (mo);
      return;
  }
  P_ExplodeMissile (mo);
     }
     else
  mo->momx = mo->momy = 0;
 }
    } while (xmove || ymove);


    if (player && player->cheats & CF_NOMOMENTUM)
    {

 mo->momx = mo->momy = 0;
 return;
    }

    if (mo->flags & (MF_MISSILE | MF_SKULLFLY) )
 return;

    if (mo->z > mo->floorz)
 return;

    if (mo->flags & MF_CORPSE)
    {


 if (mo->momx > (1<<16)/4
     || mo->momx < -(1<<16)/4
     || mo->momy > (1<<16)/4
     || mo->momy < -(1<<16)/4)
 {
     if (mo->floorz != mo->subsector->sector->floorheight)
  return;
 }
    }

    if (mo->momx > -0x1000
 && mo->momx < 0x1000
 && mo->momy > -0x1000
 && mo->momy < 0x1000
 && (!player
     || (player->cmd.forwardmove== 0
  && player->cmd.sidemove == 0 ) ) )
    {

 if ( player&&(unsigned)((player->mo->state - states)- S_PLAY_RUN1) < 4)
     P_SetMobjState (player->mo, S_PLAY);

 mo->momx = 0;
 mo->momy = 0;
    }
    else
    {
 mo->momx = FixedMul (mo->momx, 0xe800);
 mo->momy = FixedMul (mo->momy, 0xe800);
    }
}




void P_ZMovement (mobj_t* mo)
{
    fixed_t dist;
    fixed_t delta;


    if (mo->player && mo->z < mo->floorz)
    {
 mo->player->viewheight -= mo->floorz-mo->z;

 mo->player->deltaviewheight
     = ((41*(1<<16)) - mo->player->viewheight)>>3;
    }


    mo->z += mo->momz;

    if ( mo->flags & MF_FLOAT
  && mo->target)
    {

 if ( !(mo->flags & MF_SKULLFLY)
      && !(mo->flags & MF_INFLOAT) )
 {
     dist = P_AproxDistance (mo->x - mo->target->x,
        mo->y - mo->target->y);

     delta =(mo->target->z + (mo->height>>1)) - mo->z;

     if (delta<0 && dist < -(delta*3) )
  mo->z -= ((1<<16)*4);
     else if (delta>0 && dist < (delta*3) )
  mo->z += ((1<<16)*4);
 }

    }


    if (mo->z <= mo->floorz)
    {
 int correct_lost_soul_bounce = gameversion >= exe_ultimate;

 if (correct_lost_soul_bounce && mo->flags & MF_SKULLFLY)
 {

     mo->momz = -mo->momz;
 }

 if (mo->momz < 0)
 {
     if (mo->player
  && mo->momz < -(1<<16)*8)
     {




  mo->player->deltaviewheight = mo->momz>>3;
  S_StartSound (mo, sfx_oof);
     }
     mo->momz = 0;
 }
 mo->z = mo->floorz;
        if (!correct_lost_soul_bounce && mo->flags & MF_SKULLFLY)
            mo->momz = -mo->momz;

 if ( (mo->flags & MF_MISSILE)
      && !(mo->flags & MF_NOCLIP) )
 {
     P_ExplodeMissile (mo);
     return;
 }
    }
    else if (! (mo->flags & MF_NOGRAVITY) )
    {
 if (mo->momz == 0)
     mo->momz = -(1<<16)*2;
 else
     mo->momz -= (1<<16);
    }

    if (mo->z + mo->height > mo->ceilingz)
    {

 if (mo->momz > 0)
     mo->momz = 0;
 {
     mo->z = mo->ceilingz - mo->height;
 }

 if (mo->flags & MF_SKULLFLY)
 {
     mo->momz = -mo->momz;
 }

 if ( (mo->flags & MF_MISSILE)
      && !(mo->flags & MF_NOCLIP) )
 {
     P_ExplodeMissile (mo);
     return;
 }
    }
}






void
P_NightmareRespawn (mobj_t* mobj)
{
    fixed_t x;
    fixed_t y;
    fixed_t z;
    subsector_t* ss;
    mobj_t* mo;
    mapthing_t* mthing;

    x = mobj->spawnpoint.x << 16;
    y = mobj->spawnpoint.y << 16;


    if (!P_CheckPosition (mobj, x, y) )
 return;



    mo = P_SpawnMobj (mobj->x,
        mobj->y,
        mobj->subsector->sector->floorheight , MT_TFOG);

    S_StartSound (mo, sfx_telept);


    ss = R_PointInSubsector (x,y);

    mo = P_SpawnMobj (x, y, ss->sector->floorheight , MT_TFOG);

    S_StartSound (mo, sfx_telept);


    mthing = &mobj->spawnpoint;


    if (mobj->info->flags & MF_SPAWNCEILING)
 z = 2147483647;
    else
 z = (-2147483647-1);


    mo = P_SpawnMobj (x,y,z, mobj->type);
    mo->spawnpoint = mobj->spawnpoint;
    mo->angle = 0x20000000 * (mthing->angle/45);

    if (mthing->options & 8)
 mo->flags |= MF_AMBUSH;

    mo->reactiontime = 18;


    P_RemoveMobj (mobj);
}





void P_MobjThinker (mobj_t* mobj)
{

    if (mobj->momx
 || mobj->momy
 || (mobj->flags&MF_SKULLFLY) )
    {
 P_XYMovement (mobj);


 if (mobj->thinker.function.acv == (actionf_v) (-1))
     return;
    }
    if ( (mobj->z != mobj->floorz)
  || mobj->momz )
    {
 P_ZMovement (mobj);


 if (mobj->thinker.function.acv == (actionf_v) (-1))
     return;
    }




    if (mobj->tics != -1)
    {
 mobj->tics--;


 if (!mobj->tics)
     if (!P_SetMobjState (mobj, mobj->state->nextstate) )
  return;
    }
    else
    {

 if (! (mobj->flags & MF_COUNTKILL) )
     return;

 if (!respawnmonsters)
     return;

 mobj->movecount++;

 if (mobj->movecount < 12*35)
     return;

 if ( leveltime&31 )
     return;

 if (P_Random () > 4)
     return;

 P_NightmareRespawn (mobj);
    }

}





mobj_t*
P_SpawnMobj
( fixed_t x,
  fixed_t y,
  fixed_t z,
  mobjtype_t type )
{
    mobj_t* mobj;
    state_t* st;
    mobjinfo_t* info;

    mobj = Z_Malloc (sizeof(*mobj), PU_LEVEL, ((void*)0));
    memset (mobj, 0, sizeof (*mobj));
    info = &mobjinfo[type];

    mobj->type = type;
    mobj->info = info;
    mobj->x = x;
    mobj->y = y;
    mobj->radius = info->radius;
    mobj->height = info->height;
    mobj->flags = info->flags;
    mobj->health = info->spawnhealth;

    if (gameskill != sk_nightmare)
 mobj->reactiontime = info->reactiontime;

    mobj->lastlook = P_Random () % 4;


    st = &states[info->spawnstate];

    mobj->state = st;
    mobj->tics = st->tics;
    mobj->sprite = st->sprite;
    mobj->frame = st->frame;


    P_SetThingPosition (mobj);

    mobj->floorz = mobj->subsector->sector->floorheight;
    mobj->ceilingz = mobj->subsector->sector->ceilingheight;

    if (z == (-2147483647-1))
 mobj->z = mobj->floorz;
    else if (z == 2147483647)
 mobj->z = mobj->ceilingz - mobj->info->height;
    else
 mobj->z = z;

    mobj->thinker.function.acp1 = (actionf_p1)P_MobjThinker;

    P_AddThinker (&mobj->thinker);

    return mobj;
}





mapthing_t itemrespawnque[128];
int itemrespawntime[128];
int iquehead;
int iquetail;


void P_RemoveMobj (mobj_t* mobj)
{
    if ((mobj->flags & MF_SPECIAL)
 && !(mobj->flags & MF_DROPPED)
 && (mobj->type != MT_INV)
 && (mobj->type != MT_INS))
    {
 itemrespawnque[iquehead] = mobj->spawnpoint;
 itemrespawntime[iquehead] = leveltime;
 iquehead = (iquehead+1)&(128 -1);


 if (iquehead == iquetail)
     iquetail = (iquetail+1)&(128 -1);
    }


    P_UnsetThingPosition (mobj);


    S_StopSound (mobj);


    P_RemoveThinker ((thinker_t*)mobj);
}







void P_RespawnSpecials (void)
{
    fixed_t x;
    fixed_t y;
    fixed_t z;

    subsector_t* ss;
    mobj_t* mo;
    mapthing_t* mthing;

    int i;


    if (deathmatch != 2)
 return;


    if (iquehead == iquetail)
 return;


    if (leveltime - itemrespawntime[iquetail] < 30*35)
 return;

    mthing = &itemrespawnque[iquetail];

    x = mthing->x << 16;
    y = mthing->y << 16;


    ss = R_PointInSubsector (x,y);
    mo = P_SpawnMobj (x, y, ss->sector->floorheight , MT_IFOG);
    S_StartSound (mo, sfx_itmbk);


    for (i=0 ; i< NUMMOBJTYPES ; i++)
    {
 if (mthing->type == mobjinfo[i].doomednum)
     break;
    }


    if (mobjinfo[i].flags & MF_SPAWNCEILING)
 z = 2147483647;
    else
 z = (-2147483647-1);

    mo = P_SpawnMobj (x,y,z, i);
    mo->spawnpoint = *mthing;
    mo->angle = 0x20000000 * (mthing->angle/45);


    iquetail = (iquetail+1)&(128 -1);
}
void P_SpawnPlayer (mapthing_t* mthing)
{
    player_t* p;
    fixed_t x;
    fixed_t y;
    fixed_t z;

    mobj_t* mobj;

    int i;

    if (mthing->type == 0)
    {
        return;
    }


    if (!playeringame[mthing->type-1])
 return;

    p = &players[mthing->type-1];

    if (p->playerstate == PST_REBORN)
 G_PlayerReborn (mthing->type-1);

    x = mthing->x << 16;
    y = mthing->y << 16;
    z = (-2147483647-1);
    mobj = P_SpawnMobj (x,y,z, MT_PLAYER);


    if (mthing->type > 1)
 mobj->flags |= (mthing->type-1)<<MF_TRANSSHIFT;

    mobj->angle = 0x20000000 * (mthing->angle/45);
    mobj->player = p;
    mobj->health = p->health;

    p->mo = mobj;
    p->playerstate = PST_LIVE;
    p->refire = 0;
    p->message = ((void*)0);
    p->damagecount = 0;
    p->bonuscount = 0;
    p->extralight = 0;
    p->fixedcolormap = 0;
    p->viewheight = (41*(1<<16));


    P_SetupPsprites (p);


    if (deathmatch)
 for (i=0 ; i<NUMCARDS ; i++)
     p->cards[i] = true;

    if (mthing->type-1 == consoleplayer)
    {

 ST_Start ();

 HU_Start ();
    }
}







void P_SpawnMapThing (mapthing_t* mthing)
{
    int i;
    int bit;
    mobj_t* mobj;
    fixed_t x;
    fixed_t y;
    fixed_t z;


    if (mthing->type == 11)
    {
 if (deathmatch_p < &deathmatchstarts[10])
 {
     memcpy (deathmatch_p, mthing, sizeof(*mthing));
     deathmatch_p++;
 }
 return;
    }

    if (mthing->type <= 0)
    {



        return;
    }


    if (mthing->type <= 4)
    {

 playerstarts[mthing->type-1] = *mthing;
 if (!deathmatch)
     P_SpawnPlayer (mthing);

 return;
    }


    if (!netgame && (mthing->options & 16) )
 return;

    if (gameskill == sk_baby)
 bit = 1;
    else if (gameskill == sk_nightmare)
 bit = 4;
    else
 bit = 1<<(gameskill-1);

    if (!(mthing->options & bit) )
 return;


    for (i=0 ; i< NUMMOBJTYPES ; i++)
 if (mthing->type == mobjinfo[i].doomednum)
     break;

    if (i==NUMMOBJTYPES)
 I_Error ("P_SpawnMapThing: Unknown type %i at (%i, %i)",
   mthing->type,
   mthing->x, mthing->y);


    if (deathmatch && mobjinfo[i].flags & MF_NOTDMATCH)
 return;


    if (nomonsters
 && ( i == MT_SKULL
      || (mobjinfo[i].flags & MF_COUNTKILL)) )
    {
 return;
    }


    x = mthing->x << 16;
    y = mthing->y << 16;

    if (mobjinfo[i].flags & MF_SPAWNCEILING)
 z = 2147483647;
    else
 z = (-2147483647-1);

    mobj = P_SpawnMobj (x,y,z, i);
    mobj->spawnpoint = *mthing;

    if (mobj->tics > 0)
 mobj->tics = 1 + (P_Random () % mobj->tics);
    if (mobj->flags & MF_COUNTKILL)
 totalkills++;
    if (mobj->flags & MF_COUNTITEM)
 totalitems++;

    mobj->angle = 0x20000000 * (mthing->angle/45);
    if (mthing->options & 8)
 mobj->flags |= MF_AMBUSH;
}
extern fixed_t attackrange;

void
P_SpawnPuff
( fixed_t x,
  fixed_t y,
  fixed_t z )
{
    mobj_t* th;

    z += ((P_Random()-P_Random())<<10);

    th = P_SpawnMobj (x,y,z, MT_PUFF);
    th->momz = (1<<16);
    th->tics -= P_Random()&3;

    if (th->tics < 1)
 th->tics = 1;


    if (attackrange == (64*(1<<16)))
 P_SetMobjState (th, S_PUFF3);
}






void
P_SpawnBlood
( fixed_t x,
  fixed_t y,
  fixed_t z,
  int damage )
{
    mobj_t* th;

    z += ((P_Random()-P_Random())<<10);
    th = P_SpawnMobj (x,y,z, MT_BLOOD);
    th->momz = (1<<16)*2;
    th->tics -= P_Random()&3;

    if (th->tics < 1)
 th->tics = 1;

    if (damage <= 12 && damage >= 9)
 P_SetMobjState (th,S_BLOOD2);
    else if (damage < 9)
 P_SetMobjState (th,S_BLOOD3);
}
void P_CheckMissileSpawn (mobj_t* th)
{
    th->tics -= P_Random()&3;
    if (th->tics < 1)
 th->tics = 1;



    th->x += (th->momx>>1);
    th->y += (th->momy>>1);
    th->z += (th->momz>>1);

    if (!P_TryMove (th, th->x, th->y))
 P_ExplodeMissile (th);
}







mobj_t *P_SubstNullMobj(mobj_t *mobj)
{
    if (mobj == ((void*)0))
    {
        static mobj_t dummy_mobj;

        dummy_mobj.x = 0;
        dummy_mobj.y = 0;
        dummy_mobj.z = 0;
        dummy_mobj.flags = 0;

        mobj = &dummy_mobj;
    }

    return mobj;
}




mobj_t*
P_SpawnMissile
( mobj_t* source,
  mobj_t* dest,
  mobjtype_t type )
{
    mobj_t* th;
    angle_t an;
    int dist;

    th = P_SpawnMobj (source->x,
        source->y,
        source->z + 4*8*(1<<16), type);

    if (th->info->seesound)
 S_StartSound (th, th->info->seesound);

    th->target = source;
    an = R_PointToAngle2 (source->x, source->y, dest->x, dest->y);


    if (dest->flags & MF_SHADOW)
 an += (P_Random()-P_Random())<<20;

    th->angle = an;
    an >>= 19;
    th->momx = FixedMul (th->info->speed, finecosine[an]);
    th->momy = FixedMul (th->info->speed, finesine[an]);

    dist = P_AproxDistance (dest->x - source->x, dest->y - source->y);
    dist = dist / th->info->speed;

    if (dist < 1)
 dist = 1;

    th->momz = (dest->z - source->z) / dist;
    P_CheckMissileSpawn (th);

    return th;
}






void
P_SpawnPlayerMissile
( mobj_t* source,
  mobjtype_t type )
{
    mobj_t* th;
    angle_t an;

    fixed_t x;
    fixed_t y;
    fixed_t z;
    fixed_t slope;


    an = source->angle;
    slope = P_AimLineAttack (source, an, 16*64*(1<<16));

    if (!linetarget)
    {
 an += 1<<26;
 slope = P_AimLineAttack (source, an, 16*64*(1<<16));

 if (!linetarget)
 {
     an -= 2<<26;
     slope = P_AimLineAttack (source, an, 16*64*(1<<16));
 }

 if (!linetarget)
 {
     an = source->angle;
     slope = 0;
 }
    }

    x = source->x;
    y = source->y;
    z = source->z + 4*8*(1<<16);

    th = P_SpawnMobj (x,y,z, type);

    if (th->info->seesound)
 S_StartSound (th, th->info->seesound);

    th->target = source;
    th->angle = an;
    th->momx = FixedMul( th->info->speed,
    finecosine[an>>19]);
    th->momy = FixedMul( th->info->speed,
    finesine[an>>19]);
    th->momz = FixedMul( th->info->speed, slope);

    P_CheckMissileSpawn (th);
}
plat_t* activeplats[30];






void T_PlatRaise(plat_t* plat)
{
    result_e res;

    switch(plat->status)
    {
      case up:
 res = T_MovePlane(plat->sector,
     plat->speed,
     plat->high,
     plat->crush,0,1);

 if (plat->type == raiseAndChange
     || plat->type == raiseToNearestAndChange)
 {
     if (!(leveltime&7))
  S_StartSound(&plat->sector->soundorg, sfx_stnmov);
 }


 if (res == crushed && (!plat->crush))
 {
     plat->count = plat->wait;
     plat->status = down;
     S_StartSound(&plat->sector->soundorg, sfx_pstart);
 }
 else
 {
     if (res == pastdest)
     {
  plat->count = plat->wait;
  plat->status = waiting;
  S_StartSound(&plat->sector->soundorg, sfx_pstop);

  switch(plat->type)
  {
    case blazeDWUS:
    case downWaitUpStay:
      P_RemoveActivePlat(plat);
      break;

    case raiseAndChange:
    case raiseToNearestAndChange:
      P_RemoveActivePlat(plat);
      break;

    default:
      break;
  }
     }
 }
 break;

      case down:
 res = T_MovePlane(plat->sector,plat->speed,plat->low,false,0,-1);

 if (res == pastdest)
 {
     plat->count = plat->wait;
     plat->status = waiting;
     S_StartSound(&plat->sector->soundorg,sfx_pstop);
 }
 break;

      case waiting:
 if (!--plat->count)
 {
     if (plat->sector->floorheight == plat->low)
  plat->status = up;
     else
  plat->status = down;
     S_StartSound(&plat->sector->soundorg,sfx_pstart);
 }
      case in_stasis:
 break;
    }
}






int
EV_DoPlat
( line_t* line,
  plattype_e type,
  int amount )
{
    plat_t* plat;
    int secnum;
    int rtn;
    sector_t* sec;

    secnum = -1;
    rtn = 0;



    switch(type)
    {
      case perpetualRaise:
 P_ActivateInStasis(line->tag);
 break;

      default:
 break;
    }

    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
 sec = &sectors[secnum];

 if (sec->specialdata)
     continue;


 rtn = 1;
 plat = Z_Malloc( sizeof(*plat), PU_LEVSPEC, 0);
 P_AddThinker(&plat->thinker);

 plat->type = type;
 plat->sector = sec;
 plat->sector->specialdata = plat;
 plat->thinker.function.acp1 = (actionf_p1) T_PlatRaise;
 plat->crush = false;
 plat->tag = line->tag;

 switch(type)
 {
   case raiseToNearestAndChange:
     plat->speed = (1<<16)/2;
     sec->floorpic = sides[line->sidenum[0]].sector->floorpic;
     plat->high = P_FindNextHighestFloor(sec,sec->floorheight);
     plat->wait = 0;
     plat->status = up;

     sec->special = 0;

     S_StartSound(&sec->soundorg,sfx_stnmov);
     break;

   case raiseAndChange:
     plat->speed = (1<<16)/2;
     sec->floorpic = sides[line->sidenum[0]].sector->floorpic;
     plat->high = sec->floorheight + amount*(1<<16);
     plat->wait = 0;
     plat->status = up;

     S_StartSound(&sec->soundorg,sfx_stnmov);
     break;

   case downWaitUpStay:
     plat->speed = (1<<16) * 4;
     plat->low = P_FindLowestFloorSurrounding(sec);

     if (plat->low > sec->floorheight)
  plat->low = sec->floorheight;

     plat->high = sec->floorheight;
     plat->wait = 35*3;
     plat->status = down;
     S_StartSound(&sec->soundorg,sfx_pstart);
     break;

   case blazeDWUS:
     plat->speed = (1<<16) * 8;
     plat->low = P_FindLowestFloorSurrounding(sec);

     if (plat->low > sec->floorheight)
  plat->low = sec->floorheight;

     plat->high = sec->floorheight;
     plat->wait = 35*3;
     plat->status = down;
     S_StartSound(&sec->soundorg,sfx_pstart);
     break;

   case perpetualRaise:
     plat->speed = (1<<16);
     plat->low = P_FindLowestFloorSurrounding(sec);

     if (plat->low > sec->floorheight)
  plat->low = sec->floorheight;

     plat->high = P_FindHighestFloorSurrounding(sec);

     if (plat->high < sec->floorheight)
  plat->high = sec->floorheight;

     plat->wait = 35*3;
     plat->status = P_Random()&1;

     S_StartSound(&sec->soundorg,sfx_pstart);
     break;
 }
 P_AddActivePlat(plat);
    }
    return rtn;
}



void P_ActivateInStasis(int tag)
{
    int i;

    for (i = 0;i < 30;i++)
 if (activeplats[i]
     && (activeplats[i])->tag == tag
     && (activeplats[i])->status == in_stasis)
 {
     (activeplats[i])->status = (activeplats[i])->oldstatus;
     (activeplats[i])->thinker.function.acp1
       = (actionf_p1) T_PlatRaise;
 }
}

void EV_StopPlat(line_t* line)
{
    int j;

    for (j = 0;j < 30;j++)
 if (activeplats[j]
     && ((activeplats[j])->status != in_stasis)
     && ((activeplats[j])->tag == line->tag))
 {
     (activeplats[j])->oldstatus = (activeplats[j])->status;
     (activeplats[j])->status = in_stasis;
     (activeplats[j])->thinker.function.acv = (actionf_v)((void*)0);
 }
}

void P_AddActivePlat(plat_t* plat)
{
    int i;

    for (i = 0;i < 30;i++)
 if (activeplats[i] == ((void*)0))
 {
     activeplats[i] = plat;
     return;
 }
    I_Error ("P_AddActivePlat: no more plats!");
}

void P_RemoveActivePlat(plat_t* plat)
{
    int i;
    for (i = 0;i < 30;i++)
 if (plat == activeplats[i])
 {
     (activeplats[i])->sector->specialdata = ((void*)0);
     P_RemoveThinker(&(activeplats[i])->thinker);
     activeplats[i] = ((void*)0);

     return;
 }
    I_Error ("P_RemoveActivePlat: can't find plat!");
}
void
P_SetPsprite
( player_t* player,
  int position,
  statenum_t stnum )
{
    pspdef_t* psp;
    state_t* state;

    psp = &player->psprites[position];

    do
    {
 if (!stnum)
 {

     psp->state = ((void*)0);
     break;
 }

 state = &states[stnum];
 psp->state = state;
 psp->tics = state->tics;

 if (state->misc1)
 {

     psp->sx = state->misc1 << 16;
     psp->sy = state->misc2 << 16;
 }



 if (state->action.acp2)
 {
     state->action.acp2(player, psp);
     if (!psp->state)
  break;
 }

 stnum = psp->state->nextstate;

    } while (!psp->tics);

}






fixed_t swingx;
fixed_t swingy;

void P_CalcSwing (player_t* player)
{
    fixed_t swing;
    int angle;





    swing = player->bob;

    angle = (8192/70*leveltime)&(8192 -1);
    swingx = FixedMul ( swing, finesine[angle]);

    angle = (8192/70*leveltime+8192/2)&(8192 -1);
    swingy = -FixedMul ( swingx, finesine[angle]);
}
void P_BringUpWeapon (player_t* player)
{
    statenum_t newstate;

    if (player->pendingweapon == wp_nochange)
 player->pendingweapon = player->readyweapon;

    if (player->pendingweapon == wp_chainsaw)
 S_StartSound (player->mo, sfx_sawup);

    newstate = weaponinfo[player->pendingweapon].upstate;

    player->pendingweapon = wp_nochange;
    player->psprites[ps_weapon].sy = 128*(1<<16);

    P_SetPsprite (player, ps_weapon, newstate);
}






boolean P_CheckAmmo (player_t* player)
{
    ammotype_t ammo;
    int count;

    ammo = weaponinfo[player->readyweapon].ammo;


    if (player->readyweapon == wp_bfg)
 count = 40;
    else if (player->readyweapon == wp_supershotgun)
 count = 2;
    else
 count = 1;



    if (ammo == am_noammo || player->ammo[ammo] >= count)
 return true;



    do
    {
 if (player->weaponowned[wp_plasma]
     && player->ammo[am_cell]
     && (gamemode != shareware) )
 {
     player->pendingweapon = wp_plasma;
 }
 else if (player->weaponowned[wp_supershotgun]
   && player->ammo[am_shell]>2
   && (gamemode == commercial) )
 {
     player->pendingweapon = wp_supershotgun;
 }
 else if (player->weaponowned[wp_chaingun]
   && player->ammo[am_clip])
 {
     player->pendingweapon = wp_chaingun;
 }
 else if (player->weaponowned[wp_shotgun]
   && player->ammo[am_shell])
 {
     player->pendingweapon = wp_shotgun;
 }
 else if (player->ammo[am_clip])
 {
     player->pendingweapon = wp_pistol;
 }
 else if (player->weaponowned[wp_chainsaw])
 {
     player->pendingweapon = wp_chainsaw;
 }
 else if (player->weaponowned[wp_missile]
   && player->ammo[am_misl])
 {
     player->pendingweapon = wp_missile;
 }
 else if (player->weaponowned[wp_bfg]
   && player->ammo[am_cell]>40
   && (gamemode != shareware) )
 {
     player->pendingweapon = wp_bfg;
 }
 else
 {

     player->pendingweapon = wp_fist;
 }

    } while (player->pendingweapon == wp_nochange);


    P_SetPsprite (player,
    ps_weapon,
    weaponinfo[player->readyweapon].downstate);

    return false;
}





void P_FireWeapon (player_t* player)
{
    statenum_t newstate;

    if (!P_CheckAmmo (player))
 return;

    P_SetMobjState (player->mo, S_PLAY_ATK1);
    newstate = weaponinfo[player->readyweapon].atkstate;
    P_SetPsprite (player, ps_weapon, newstate);
    P_NoiseAlert (player->mo, player->mo);
}







void P_DropWeapon (player_t* player)
{
    P_SetPsprite (player,
    ps_weapon,
    weaponinfo[player->readyweapon].downstate);
}
void
A_WeaponReady
( player_t* player,
  pspdef_t* psp )
{
    statenum_t newstate;
    int angle;


    if (player->mo->state == &states[S_PLAY_ATK1]
 || player->mo->state == &states[S_PLAY_ATK2] )
    {
 P_SetMobjState (player->mo, S_PLAY);
    }

    if (player->readyweapon == wp_chainsaw
 && psp->state == &states[S_SAW])
    {
 S_StartSound (player->mo, sfx_sawidl);
    }



    if (player->pendingweapon != wp_nochange || !player->health)
    {


 newstate = weaponinfo[player->readyweapon].downstate;
 P_SetPsprite (player, ps_weapon, newstate);
 return;
    }



    if (player->cmd.buttons & BT_ATTACK)
    {
 if ( !player->attackdown
      || (player->readyweapon != wp_missile
   && player->readyweapon != wp_bfg) )
 {
     player->attackdown = true;
     P_FireWeapon (player);
     return;
 }
    }
    else
 player->attackdown = false;


    angle = (128*leveltime)&(8192 -1);
    psp->sx = (1<<16) + FixedMul (player->bob, finecosine[angle]);
    angle &= 8192/2-1;
    psp->sy = 32*(1<<16) + FixedMul (player->bob, finesine[angle]);
}
void A_ReFire
( player_t* player,
  pspdef_t* psp )
{



    if ( (player->cmd.buttons & BT_ATTACK)
  && player->pendingweapon == wp_nochange
  && player->health)
    {
 player->refire++;
 P_FireWeapon (player);
    }
    else
    {
 player->refire = 0;
 P_CheckAmmo (player);
    }
}


void
A_CheckReload
( player_t* player,
  pspdef_t* psp )
{
    P_CheckAmmo (player);




}
void
A_Lower
( player_t* player,
  pspdef_t* psp )
{
    psp->sy += (1<<16)*6;


    if (psp->sy < 128*(1<<16) )
 return;


    if (player->playerstate == PST_DEAD)
    {
 psp->sy = 128*(1<<16);


 return;
    }



    if (!player->health)
    {

 P_SetPsprite (player, ps_weapon, S_NULL);
 return;
    }

    player->readyweapon = player->pendingweapon;

    P_BringUpWeapon (player);
}





void
A_Raise
( player_t* player,
  pspdef_t* psp )
{
    statenum_t newstate;

    psp->sy -= (1<<16)*6;

    if (psp->sy > 32*(1<<16) )
 return;

    psp->sy = 32*(1<<16);



    newstate = weaponinfo[player->readyweapon].readystate;

    P_SetPsprite (player, ps_weapon, newstate);
}






void
A_GunFlash
( player_t* player,
  pspdef_t* psp )
{
    P_SetMobjState (player->mo, S_PLAY_ATK2);
    P_SetPsprite (player,ps_flash,weaponinfo[player->readyweapon].flashstate);
}
void
A_Punch
( player_t* player,
  pspdef_t* psp )
{
    angle_t angle;
    int damage;
    int slope;

    damage = (P_Random ()%10+1)<<1;

    if (player->powers[pw_strength])
 damage *= 10;

    angle = player->mo->angle;
    angle += (P_Random()-P_Random())<<18;
    slope = P_AimLineAttack (player->mo, angle, (64*(1<<16)));
    P_LineAttack (player->mo, angle, (64*(1<<16)), slope, damage);


    if (linetarget)
    {
 S_StartSound (player->mo, sfx_punch);
 player->mo->angle = R_PointToAngle2 (player->mo->x,
          player->mo->y,
          linetarget->x,
          linetarget->y);
    }
}





void
A_Saw
( player_t* player,
  pspdef_t* psp )
{
    angle_t angle;
    int damage;
    int slope;

    damage = 2*(P_Random ()%10+1);
    angle = player->mo->angle;
    angle += (P_Random()-P_Random())<<18;


    slope = P_AimLineAttack (player->mo, angle, (64*(1<<16))+1);
    P_LineAttack (player->mo, angle, (64*(1<<16))+1, slope, damage);

    if (!linetarget)
    {
 S_StartSound (player->mo, sfx_sawful);
 return;
    }
    S_StartSound (player->mo, sfx_sawhit);


    angle = R_PointToAngle2 (player->mo->x, player->mo->y,
        linetarget->x, linetarget->y);
    if (angle - player->mo->angle > 0x80000000)
    {
 if ((signed int) (angle - player->mo->angle) < -0x40000000/20)
     player->mo->angle = angle + 0x40000000/21;
 else
     player->mo->angle -= 0x40000000/20;
    }
    else
    {
 if (angle - player->mo->angle > 0x40000000/20)
     player->mo->angle = angle - 0x40000000/21;
 else
     player->mo->angle += 0x40000000/20;
    }
    player->mo->flags |= MF_JUSTATTACKED;
}







static void DecreaseAmmo(player_t *player, int ammonum, int amount)
{
    if (ammonum < NUMAMMO)
    {
        player->ammo[ammonum] -= amount;
    }
    else
    {
        player->maxammo[ammonum - NUMAMMO] -= amount;
    }
}





void
A_FireMissile
( player_t* player,
  pspdef_t* psp )
{
    DecreaseAmmo(player, weaponinfo[player->readyweapon].ammo, 1);
    P_SpawnPlayerMissile (player->mo, MT_ROCKET);
}





void
A_FireBFG
( player_t* player,
  pspdef_t* psp )
{
    DecreaseAmmo(player, weaponinfo[player->readyweapon].ammo,
                 40);
    P_SpawnPlayerMissile (player->mo, MT_BFG);
}






void
A_FirePlasma
( player_t* player,
  pspdef_t* psp )
{
    DecreaseAmmo(player, weaponinfo[player->readyweapon].ammo, 1);

    P_SetPsprite (player,
    ps_flash,
    weaponinfo[player->readyweapon].flashstate+(P_Random ()&1) );

    P_SpawnPlayerMissile (player->mo, MT_PLASMA);
}
fixed_t bulletslope;


void P_BulletSlope (mobj_t* mo)
{
    angle_t an;


    an = mo->angle;
    bulletslope = P_AimLineAttack (mo, an, 16*64*(1<<16));

    if (!linetarget)
    {
 an += 1<<26;
 bulletslope = P_AimLineAttack (mo, an, 16*64*(1<<16));
 if (!linetarget)
 {
     an -= 2<<26;
     bulletslope = P_AimLineAttack (mo, an, 16*64*(1<<16));
 }
    }
}





void
P_GunShot
( mobj_t* mo,
  boolean accurate )
{
    angle_t angle;
    int damage;

    damage = 5*(P_Random ()%3+1);
    angle = mo->angle;

    if (!accurate)
 angle += (P_Random()-P_Random())<<18;

    P_LineAttack (mo, angle, (32*64*(1<<16)), bulletslope, damage);
}





void
A_FirePistol
( player_t* player,
  pspdef_t* psp )
{
    S_StartSound (player->mo, sfx_pistol);

    P_SetMobjState (player->mo, S_PLAY_ATK2);
    DecreaseAmmo(player, weaponinfo[player->readyweapon].ammo, 1);

    P_SetPsprite (player,
    ps_flash,
    weaponinfo[player->readyweapon].flashstate);

    P_BulletSlope (player->mo);
    P_GunShot (player->mo, !player->refire);
}





void
A_FireShotgun
( player_t* player,
  pspdef_t* psp )
{
    int i;

    S_StartSound (player->mo, sfx_shotgn);
    P_SetMobjState (player->mo, S_PLAY_ATK2);

    DecreaseAmmo(player, weaponinfo[player->readyweapon].ammo, 1);

    P_SetPsprite (player,
    ps_flash,
    weaponinfo[player->readyweapon].flashstate);

    P_BulletSlope (player->mo);

    for (i=0 ; i<7 ; i++)
 P_GunShot (player->mo, false);
}






void
A_FireShotgun2
( player_t* player,
  pspdef_t* psp )
{
    int i;
    angle_t angle;
    int damage;


    S_StartSound (player->mo, sfx_dshtgn);
    P_SetMobjState (player->mo, S_PLAY_ATK2);

    DecreaseAmmo(player, weaponinfo[player->readyweapon].ammo, 2);

    P_SetPsprite (player,
    ps_flash,
    weaponinfo[player->readyweapon].flashstate);

    P_BulletSlope (player->mo);

    for (i=0 ; i<20 ; i++)
    {
 damage = 5*(P_Random ()%3+1);
 angle = player->mo->angle;
 angle += (P_Random()-P_Random())<<19;
 P_LineAttack (player->mo,
        angle,
        (32*64*(1<<16)),
        bulletslope + ((P_Random()-P_Random())<<5), damage);
    }
}





void
A_FireCGun
( player_t* player,
  pspdef_t* psp )
{
    S_StartSound (player->mo, sfx_pistol);

    if (!player->ammo[weaponinfo[player->readyweapon].ammo])
 return;

    P_SetMobjState (player->mo, S_PLAY_ATK2);
    DecreaseAmmo(player, weaponinfo[player->readyweapon].ammo, 1);

    P_SetPsprite (player,
    ps_flash,
    weaponinfo[player->readyweapon].flashstate
    + psp->state
    - &states[S_CHAIN1] );

    P_BulletSlope (player->mo);

    P_GunShot (player->mo, !player->refire);
}






void A_Light0 (player_t *player, pspdef_t *psp)
{
    player->extralight = 0;
}

void A_Light1 (player_t *player, pspdef_t *psp)
{
    player->extralight = 1;
}

void A_Light2 (player_t *player, pspdef_t *psp)
{
    player->extralight = 2;
}






void A_BFGSpray (mobj_t* mo)
{
    int i;
    int j;
    int damage;
    angle_t an;


    for (i=0 ; i<40 ; i++)
    {
 an = mo->angle - 0x40000000/2 + 0x40000000/40*i;



 P_AimLineAttack (mo->target, an, 16*64*(1<<16));

 if (!linetarget)
     continue;

 P_SpawnMobj (linetarget->x,
       linetarget->y,
       linetarget->z + (linetarget->height>>2),
       MT_EXTRABFG);

 damage = 0;
 for (j=0;j<15;j++)
     damage += (P_Random()&7) + 1;

 P_DamageMobj (linetarget, mo->target,mo->target, damage);
    }
}





void
A_BFGsound
( player_t* player,
  pspdef_t* psp )
{
    S_StartSound (player->mo, sfx_bfg);
}







void P_SetupPsprites (player_t* player)
{
    int i;


    for (i=0 ; i<NUMPSPRITES ; i++)
 player->psprites[i].state = ((void*)0);


    player->pendingweapon = player->readyweapon;
    P_BringUpWeapon (player);
}
void P_MovePsprites (player_t* player)
{
    int i;
    pspdef_t* psp;
    state_t* state;

    psp = &player->psprites[0];
    for (i=0 ; i<NUMPSPRITES ; i++, psp++)
    {

 if ( (state = psp->state) )
 {



     if (psp->tics != -1)
     {
  psp->tics--;
  if (!psp->tics)
      P_SetPsprite (player, i, psp->state->nextstate);
     }
 }
    }

    player->psprites[ps_flash].sx = player->psprites[ps_weapon].sx;
    player->psprites[ps_flash].sy = player->psprites[ps_weapon].sy;
}
FILE *save_stream;
int savegamelength;
boolean savegame_error;





char *P_TempSaveGameFile(void)
{
    static char *filename = ((void*)0);

    if (filename == ((void*)0))
    {
        filename = M_StringJoin(savegamedir, "temp.dsg", ((void*)0));
    }

    return filename;
}



char *P_SaveGameFile(int slot)
{
    static char *filename = ((void*)0);
    static size_t filename_size = 0;
    char basename[32];

    if (filename == ((void*)0))
    {
        filename_size = strlen(savegamedir) + 32;
        filename = malloc(filename_size);
    }

    snprintf(basename, 32, "doomsav" "%d.dsg", slot);
    M_snprintf(filename, filename_size, "%s%s", savegamedir, basename);

    return filename;
}



static byte saveg_read8(void)
{
    byte result;

    if (fread(&result, 1, 1, save_stream) < 1)
    {
        if (!savegame_error)
        {
            fprintf(__stderrp, "saveg_read8: Unexpected end of file while "
                            "reading save game\n");

            savegame_error = true;
        }
    }

    return result;
}

static void saveg_write8(byte value)
{
    if (fwrite(&value, 1, 1, save_stream) < 1)
    {
        if (!savegame_error)
        {
            fprintf(__stderrp, "saveg_write8: Error while writing save game\n");

            savegame_error = true;
        }
    }
}

static short saveg_read16(void)
{
    int result;

    result = saveg_read8();
    result |= saveg_read8() << 8;

    return result;
}

static void saveg_write16(short value)
{
    saveg_write8(value & 0xff);
    saveg_write8((value >> 8) & 0xff);
}

static int saveg_read32(void)
{
    int result;

    result = saveg_read8();
    result |= saveg_read8() << 8;
    result |= saveg_read8() << 16;
    result |= saveg_read8() << 24;

    return result;
}

static void saveg_write32(int value)
{
    saveg_write8(value & 0xff);
    saveg_write8((value >> 8) & 0xff);
    saveg_write8((value >> 16) & 0xff);
    saveg_write8((value >> 24) & 0xff);
}



static void saveg_read_pad(void)
{
    unsigned long pos;
    int padding;
    int i;

    pos = ftell(save_stream);

    padding = (4 - (pos & 3)) & 3;

    for (i=0; i<padding; ++i)
    {
        saveg_read8();
    }
}

static void saveg_write_pad(void)
{
    unsigned long pos;
    int padding;
    int i;

    pos = ftell(save_stream);

    padding = (4 - (pos & 3)) & 3;

    for (i=0; i<padding; ++i)
    {
        saveg_write8(0);
    }
}




static void *saveg_readp(void)
{
    return (void *) (intptr_t) saveg_read32();
}

static void saveg_writep(void *p)
{
    saveg_write32((intptr_t) p);
}
static void saveg_read_mapthing_t(mapthing_t *str)
{

    str->x = saveg_read16();


    str->y = saveg_read16();


    str->angle = saveg_read16();


    str->type = saveg_read16();


    str->options = saveg_read16();
}

static void saveg_write_mapthing_t(mapthing_t *str)
{

    saveg_write16(str->x);


    saveg_write16(str->y);


    saveg_write16(str->angle);


    saveg_write16(str->type);


    saveg_write16(str->options);
}





static void saveg_read_actionf_t(actionf_t *str)
{

    str->acp1 = saveg_readp();
}

static void saveg_write_actionf_t(actionf_t *str)
{

    saveg_writep(str->acp1);
}
static void saveg_read_thinker_t(thinker_t *str)
{

    str->prev = saveg_readp();


    str->next = saveg_readp();


    saveg_read_actionf_t(&str->function);
}

static void saveg_write_thinker_t(thinker_t *str)
{

    saveg_writep(str->prev);


    saveg_writep(str->next);


    saveg_write_actionf_t(&str->function);
}





static void saveg_read_mobj_t(mobj_t *str)
{
    int pl;


    saveg_read_thinker_t(&str->thinker);


    str->x = saveg_read32();


    str->y = saveg_read32();


    str->z = saveg_read32();


    str->snext = saveg_readp();


    str->sprev = saveg_readp();


    str->angle = saveg_read32();


    str->sprite = saveg_read32();


    str->frame = saveg_read32();


    str->bnext = saveg_readp();


    str->bprev = saveg_readp();


    str->subsector = saveg_readp();


    str->floorz = saveg_read32();


    str->ceilingz = saveg_read32();


    str->radius = saveg_read32();


    str->height = saveg_read32();


    str->momx = saveg_read32();


    str->momy = saveg_read32();


    str->momz = saveg_read32();


    str->validcount = saveg_read32();


    str->type = saveg_read32();


    str->info = saveg_readp();


    str->tics = saveg_read32();


    str->state = &states[saveg_read32()];


    str->flags = saveg_read32();


    str->health = saveg_read32();


    str->movedir = saveg_read32();


    str->movecount = saveg_read32();


    str->target = saveg_readp();


    str->reactiontime = saveg_read32();


    str->threshold = saveg_read32();


    pl = saveg_read32();

    if (pl > 0)
    {
        str->player = &players[pl - 1];
        str->player->mo = str;
    }
    else
    {
        str->player = ((void*)0);
    }


    str->lastlook = saveg_read32();


    saveg_read_mapthing_t(&str->spawnpoint);


    str->tracer = saveg_readp();
}

static void saveg_write_mobj_t(mobj_t *str)
{

    saveg_write_thinker_t(&str->thinker);


    saveg_write32(str->x);


    saveg_write32(str->y);


    saveg_write32(str->z);


    saveg_writep(str->snext);


    saveg_writep(str->sprev);


    saveg_write32(str->angle);


    saveg_write32(str->sprite);


    saveg_write32(str->frame);


    saveg_writep(str->bnext);


    saveg_writep(str->bprev);


    saveg_writep(str->subsector);


    saveg_write32(str->floorz);


    saveg_write32(str->ceilingz);


    saveg_write32(str->radius);


    saveg_write32(str->height);


    saveg_write32(str->momx);


    saveg_write32(str->momy);


    saveg_write32(str->momz);


    saveg_write32(str->validcount);


    saveg_write32(str->type);


    saveg_writep(str->info);


    saveg_write32(str->tics);


    saveg_write32(str->state - states);


    saveg_write32(str->flags);


    saveg_write32(str->health);


    saveg_write32(str->movedir);


    saveg_write32(str->movecount);


    saveg_writep(str->target);


    saveg_write32(str->reactiontime);


    saveg_write32(str->threshold);


    if (str->player)
    {
        saveg_write32(str->player - players + 1);
    }
    else
    {
        saveg_write32(0);
    }


    saveg_write32(str->lastlook);


    saveg_write_mapthing_t(&str->spawnpoint);


    saveg_writep(str->tracer);
}






static void saveg_read_ticcmd_t(ticcmd_t *str)
{


    str->forwardmove = saveg_read8();


    str->sidemove = saveg_read8();


    str->angleturn = saveg_read16();


    str->consistancy = saveg_read16();


    str->chatchar = saveg_read8();


    str->buttons = saveg_read8();
}

static void saveg_write_ticcmd_t(ticcmd_t *str)
{


    saveg_write8(str->forwardmove);


    saveg_write8(str->sidemove);


    saveg_write16(str->angleturn);


    saveg_write16(str->consistancy);


    saveg_write8(str->chatchar);


    saveg_write8(str->buttons);
}





static void saveg_read_pspdef_t(pspdef_t *str)
{
    int state;


    state = saveg_read32();

    if (state > 0)
    {
        str->state = &states[state];
    }
    else
    {
        str->state = ((void*)0);
    }


    str->tics = saveg_read32();


    str->sx = saveg_read32();


    str->sy = saveg_read32();
}

static void saveg_write_pspdef_t(pspdef_t *str)
{

    if (str->state)
    {
        saveg_write32(str->state - states);
    }
    else
    {
        saveg_write32(0);
    }


    saveg_write32(str->tics);


    saveg_write32(str->sx);


    saveg_write32(str->sy);
}





static void saveg_read_player_t(player_t *str)
{
    int i;


    str->mo = saveg_readp();


    str->playerstate = saveg_read32();


    saveg_read_ticcmd_t(&str->cmd);


    str->viewz = saveg_read32();


    str->viewheight = saveg_read32();


    str->deltaviewheight = saveg_read32();


    str->bob = saveg_read32();


    str->health = saveg_read32();


    str->armorpoints = saveg_read32();


    str->armortype = saveg_read32();


    for (i=0; i<NUMPOWERS; ++i)
    {
        str->powers[i] = saveg_read32();
    }


    for (i=0; i<NUMCARDS; ++i)
    {
        str->cards[i] = saveg_read32();
    }


    str->backpack = saveg_read32();


    for (i=0; i<4; ++i)
    {
        str->frags[i] = saveg_read32();
    }


    str->readyweapon = saveg_read32();


    str->pendingweapon = saveg_read32();


    for (i=0; i<NUMWEAPONS; ++i)
    {
        str->weaponowned[i] = saveg_read32();
    }


    for (i=0; i<NUMAMMO; ++i)
    {
        str->ammo[i] = saveg_read32();
    }


    for (i=0; i<NUMAMMO; ++i)
    {
        str->maxammo[i] = saveg_read32();
    }


    str->attackdown = saveg_read32();


    str->usedown = saveg_read32();


    str->cheats = saveg_read32();


    str->refire = saveg_read32();


    str->killcount = saveg_read32();


    str->itemcount = saveg_read32();


    str->secretcount = saveg_read32();


    str->message = saveg_readp();


    str->damagecount = saveg_read32();


    str->bonuscount = saveg_read32();


    str->attacker = saveg_readp();


    str->extralight = saveg_read32();


    str->fixedcolormap = saveg_read32();


    str->colormap = saveg_read32();


    for (i=0; i<NUMPSPRITES; ++i)
    {
        saveg_read_pspdef_t(&str->psprites[i]);
    }


    str->didsecret = saveg_read32();
}

static void saveg_write_player_t(player_t *str)
{
    int i;


    saveg_writep(str->mo);


    saveg_write32(str->playerstate);


    saveg_write_ticcmd_t(&str->cmd);


    saveg_write32(str->viewz);


    saveg_write32(str->viewheight);


    saveg_write32(str->deltaviewheight);


    saveg_write32(str->bob);


    saveg_write32(str->health);


    saveg_write32(str->armorpoints);


    saveg_write32(str->armortype);


    for (i=0; i<NUMPOWERS; ++i)
    {
        saveg_write32(str->powers[i]);
    }


    for (i=0; i<NUMCARDS; ++i)
    {
        saveg_write32(str->cards[i]);
    }


    saveg_write32(str->backpack);


    for (i=0; i<4; ++i)
    {
        saveg_write32(str->frags[i]);
    }


    saveg_write32(str->readyweapon);


    saveg_write32(str->pendingweapon);


    for (i=0; i<NUMWEAPONS; ++i)
    {
        saveg_write32(str->weaponowned[i]);
    }


    for (i=0; i<NUMAMMO; ++i)
    {
        saveg_write32(str->ammo[i]);
    }


    for (i=0; i<NUMAMMO; ++i)
    {
        saveg_write32(str->maxammo[i]);
    }


    saveg_write32(str->attackdown);


    saveg_write32(str->usedown);


    saveg_write32(str->cheats);


    saveg_write32(str->refire);


    saveg_write32(str->killcount);


    saveg_write32(str->itemcount);


    saveg_write32(str->secretcount);


    saveg_writep(str->message);


    saveg_write32(str->damagecount);


    saveg_write32(str->bonuscount);


    saveg_writep(str->attacker);


    saveg_write32(str->extralight);


    saveg_write32(str->fixedcolormap);


    saveg_write32(str->colormap);


    for (i=0; i<NUMPSPRITES; ++i)
    {
        saveg_write_pspdef_t(&str->psprites[i]);
    }


    saveg_write32(str->didsecret);
}






static void saveg_read_ceiling_t(ceiling_t *str)
{
    int sector;


    saveg_read_thinker_t(&str->thinker);


    str->type = saveg_read32();


    sector = saveg_read32();
    str->sector = &sectors[sector];


    str->bottomheight = saveg_read32();


    str->topheight = saveg_read32();


    str->speed = saveg_read32();


    str->crush = saveg_read32();


    str->direction = saveg_read32();


    str->tag = saveg_read32();


    str->olddirection = saveg_read32();
}

static void saveg_write_ceiling_t(ceiling_t *str)
{

    saveg_write_thinker_t(&str->thinker);


    saveg_write32(str->type);


    saveg_write32(str->sector - sectors);


    saveg_write32(str->bottomheight);


    saveg_write32(str->topheight);


    saveg_write32(str->speed);


    saveg_write32(str->crush);


    saveg_write32(str->direction);


    saveg_write32(str->tag);


    saveg_write32(str->olddirection);
}





static void saveg_read_vldoor_t(vldoor_t *str)
{
    int sector;


    saveg_read_thinker_t(&str->thinker);


    str->type = saveg_read32();


    sector = saveg_read32();
    str->sector = &sectors[sector];


    str->topheight = saveg_read32();


    str->speed = saveg_read32();


    str->direction = saveg_read32();


    str->topwait = saveg_read32();


    str->topcountdown = saveg_read32();
}

static void saveg_write_vldoor_t(vldoor_t *str)
{

    saveg_write_thinker_t(&str->thinker);


    saveg_write32(str->type);


    saveg_write32(str->sector - sectors);


    saveg_write32(str->topheight);


    saveg_write32(str->speed);


    saveg_write32(str->direction);


    saveg_write32(str->topwait);


    saveg_write32(str->topcountdown);
}





static void saveg_read_floormove_t(floormove_t *str)
{
    int sector;


    saveg_read_thinker_t(&str->thinker);


    str->type = saveg_read32();


    str->crush = saveg_read32();


    sector = saveg_read32();
    str->sector = &sectors[sector];


    str->direction = saveg_read32();


    str->newspecial = saveg_read32();


    str->texture = saveg_read16();


    str->floordestheight = saveg_read32();


    str->speed = saveg_read32();
}

static void saveg_write_floormove_t(floormove_t *str)
{

    saveg_write_thinker_t(&str->thinker);


    saveg_write32(str->type);


    saveg_write32(str->crush);


    saveg_write32(str->sector - sectors);


    saveg_write32(str->direction);


    saveg_write32(str->newspecial);


    saveg_write16(str->texture);


    saveg_write32(str->floordestheight);


    saveg_write32(str->speed);
}





static void saveg_read_plat_t(plat_t *str)
{
    int sector;


    saveg_read_thinker_t(&str->thinker);


    sector = saveg_read32();
    str->sector = &sectors[sector];


    str->speed = saveg_read32();


    str->low = saveg_read32();


    str->high = saveg_read32();


    str->wait = saveg_read32();


    str->count = saveg_read32();


    str->status = saveg_read32();


    str->oldstatus = saveg_read32();


    str->crush = saveg_read32();


    str->tag = saveg_read32();


    str->type = saveg_read32();
}

static void saveg_write_plat_t(plat_t *str)
{

    saveg_write_thinker_t(&str->thinker);


    saveg_write32(str->sector - sectors);


    saveg_write32(str->speed);


    saveg_write32(str->low);


    saveg_write32(str->high);


    saveg_write32(str->wait);


    saveg_write32(str->count);


    saveg_write32(str->status);


    saveg_write32(str->oldstatus);


    saveg_write32(str->crush);


    saveg_write32(str->tag);


    saveg_write32(str->type);
}





static void saveg_read_lightflash_t(lightflash_t *str)
{
    int sector;


    saveg_read_thinker_t(&str->thinker);


    sector = saveg_read32();
    str->sector = &sectors[sector];


    str->count = saveg_read32();


    str->maxlight = saveg_read32();


    str->minlight = saveg_read32();


    str->maxtime = saveg_read32();


    str->mintime = saveg_read32();
}

static void saveg_write_lightflash_t(lightflash_t *str)
{

    saveg_write_thinker_t(&str->thinker);


    saveg_write32(str->sector - sectors);


    saveg_write32(str->count);


    saveg_write32(str->maxlight);


    saveg_write32(str->minlight);


    saveg_write32(str->maxtime);


    saveg_write32(str->mintime);
}





static void saveg_read_strobe_t(strobe_t *str)
{
    int sector;


    saveg_read_thinker_t(&str->thinker);


    sector = saveg_read32();
    str->sector = &sectors[sector];


    str->count = saveg_read32();


    str->minlight = saveg_read32();


    str->maxlight = saveg_read32();


    str->darktime = saveg_read32();


    str->brighttime = saveg_read32();
}

static void saveg_write_strobe_t(strobe_t *str)
{

    saveg_write_thinker_t(&str->thinker);


    saveg_write32(str->sector - sectors);


    saveg_write32(str->count);


    saveg_write32(str->minlight);


    saveg_write32(str->maxlight);


    saveg_write32(str->darktime);


    saveg_write32(str->brighttime);
}





static void saveg_read_glow_t(glow_t *str)
{
    int sector;


    saveg_read_thinker_t(&str->thinker);


    sector = saveg_read32();
    str->sector = &sectors[sector];


    str->minlight = saveg_read32();


    str->maxlight = saveg_read32();


    str->direction = saveg_read32();
}

static void saveg_write_glow_t(glow_t *str)
{

    saveg_write_thinker_t(&str->thinker);


    saveg_write32(str->sector - sectors);


    saveg_write32(str->minlight);


    saveg_write32(str->maxlight);


    saveg_write32(str->direction);
}





void P_WriteSaveGameHeader(char *description)
{
    char name[16];
    int i;

    for (i=0; description[i] != '\0'; ++i)
        saveg_write8(description[i]);
    for (; i<24; ++i)
        saveg_write8(0);

    memset(name, 0, sizeof(name));
    M_snprintf(name, sizeof(name), "version %i", G_VanillaVersionCode());

    for (i=0; i<16; ++i)
        saveg_write8(name[i]);

    saveg_write8(gameskill);
    saveg_write8(gameepisode);
    saveg_write8(gamemap);

    for (i=0 ; i<4 ; i++)
        saveg_write8(playeringame[i]);

    saveg_write8((leveltime >> 16) & 0xff);
    saveg_write8((leveltime >> 8) & 0xff);
    saveg_write8(leveltime & 0xff);
}





boolean P_ReadSaveGameHeader(void)
{
    int i;
    byte a, b, c;
    char vcheck[16];
    char read_vcheck[16];



    for (i=0; i<24; ++i)
        saveg_read8();

    for (i=0; i<16; ++i)
        read_vcheck[i] = saveg_read8();

    memset(vcheck, 0, sizeof(vcheck));
    M_snprintf(vcheck, sizeof(vcheck), "version %i", G_VanillaVersionCode());
    if (strcmp(read_vcheck, vcheck) != 0)
 return false;

    gameskill = saveg_read8();
    gameepisode = saveg_read8();
    gamemap = saveg_read8();

    for (i=0 ; i<4 ; i++)
 playeringame[i] = saveg_read8();


    a = saveg_read8();
    b = saveg_read8();
    c = saveg_read8();
    leveltime = (a<<16) + (b<<8) + c;

    return true;
}





boolean P_ReadSaveGameEOF(void)
{
    int value;

    value = saveg_read8();

    return value == 0x1d;
}





void P_WriteSaveGameEOF(void)
{
    saveg_write8(0x1d);
}




void P_ArchivePlayers (void)
{
    int i;

    for (i=0 ; i<4 ; i++)
    {
 if (!playeringame[i])
     continue;

 saveg_write_pad();

        saveg_write_player_t(&players[i]);
    }
}






void P_UnArchivePlayers (void)
{
    int i;

    for (i=0 ; i<4 ; i++)
    {
 if (!playeringame[i])
     continue;

 saveg_read_pad();

        saveg_read_player_t(&players[i]);


 players[i].mo = ((void*)0);
 players[i].message = ((void*)0);
 players[i].attacker = ((void*)0);
    }
}





void P_ArchiveWorld (void)
{
    int i;
    int j;
    sector_t* sec;
    line_t* li;
    side_t* si;


    for (i=0, sec = sectors ; i<numsectors ; i++,sec++)
    {
 saveg_write16(sec->floorheight >> 16);
 saveg_write16(sec->ceilingheight >> 16);
 saveg_write16(sec->floorpic);
 saveg_write16(sec->ceilingpic);
 saveg_write16(sec->lightlevel);
 saveg_write16(sec->special);
 saveg_write16(sec->tag);
    }



    for (i=0, li = lines ; i<numlines ; i++,li++)
    {
 saveg_write16(li->flags);
 saveg_write16(li->special);
 saveg_write16(li->tag);
 for (j=0 ; j<2 ; j++)
 {
     if (li->sidenum[j] == -1)
  continue;

     si = &sides[li->sidenum[j]];

     saveg_write16(si->textureoffset >> 16);
     saveg_write16(si->rowoffset >> 16);
     saveg_write16(si->toptexture);
     saveg_write16(si->bottomtexture);
     saveg_write16(si->midtexture);
 }
    }
}






void P_UnArchiveWorld (void)
{
    int i;
    int j;
    sector_t* sec;
    line_t* li;
    side_t* si;


    for (i=0, sec = sectors ; i<numsectors ; i++,sec++)
    {
 sec->floorheight = saveg_read16() << 16;
 sec->ceilingheight = saveg_read16() << 16;
 sec->floorpic = saveg_read16();
 sec->ceilingpic = saveg_read16();
 sec->lightlevel = saveg_read16();
 sec->special = saveg_read16();
 sec->tag = saveg_read16();
 sec->specialdata = 0;
 sec->soundtarget = 0;
    }


    for (i=0, li = lines ; i<numlines ; i++,li++)
    {
 li->flags = saveg_read16();
 li->special = saveg_read16();
 li->tag = saveg_read16();
 for (j=0 ; j<2 ; j++)
 {
     if (li->sidenum[j] == -1)
  continue;
     si = &sides[li->sidenum[j]];
     si->textureoffset = saveg_read16() << 16;
     si->rowoffset = saveg_read16() << 16;
     si->toptexture = saveg_read16();
     si->bottomtexture = saveg_read16();
     si->midtexture = saveg_read16();
 }
    }
}
typedef enum
{
    tc_end,
    tc_mobj

} thinkerclass_t;





void P_ArchiveThinkers (void)
{
    thinker_t* th;


    for (th = thinkercap.next ; th != &thinkercap ; th=th->next)
    {
 if (th->function.acp1 == (actionf_p1)P_MobjThinker)
 {
            saveg_write8(tc_mobj);
     saveg_write_pad();
            saveg_write_mobj_t((mobj_t *) th);

     continue;
 }


    }


    saveg_write8(tc_end);
}






void P_UnArchiveThinkers (void)
{
    byte tclass;
    thinker_t* currentthinker;
    thinker_t* next;
    mobj_t* mobj;


    currentthinker = thinkercap.next;
    while (currentthinker != &thinkercap)
    {
 next = currentthinker->next;

 if (currentthinker->function.acp1 == (actionf_p1)P_MobjThinker)
     P_RemoveMobj ((mobj_t *)currentthinker);
 else
     Z_Free (currentthinker);

 currentthinker = next;
    }
    P_InitThinkers ();


    while (1)
    {
 tclass = saveg_read8();
 switch (tclass)
 {
   case tc_end:
     return;

   case tc_mobj:
     saveg_read_pad();
     mobj = Z_Malloc (sizeof(*mobj), PU_LEVEL, ((void*)0));
            saveg_read_mobj_t(mobj);

     mobj->target = ((void*)0);
            mobj->tracer = ((void*)0);
     P_SetThingPosition (mobj);
     mobj->info = &mobjinfo[mobj->type];
     mobj->floorz = mobj->subsector->sector->floorheight;
     mobj->ceilingz = mobj->subsector->sector->ceilingheight;
     mobj->thinker.function.acp1 = (actionf_p1)P_MobjThinker;
     P_AddThinker (&mobj->thinker);
     break;

   default:
     I_Error ("Unknown tclass %i in savegame",tclass);
 }

    }

}





enum
{
    tc_ceiling,
    tc_door,
    tc_floor,
    tc_plat,
    tc_flash,
    tc_strobe,
    tc_glow,
    tc_endspecials

} specials_e;
void P_ArchiveSpecials (void)
{
    thinker_t* th;
    int i;


    for (th = thinkercap.next ; th != &thinkercap ; th=th->next)
    {
 if (th->function.acv == (actionf_v)((void*)0))
 {
     for (i = 0; i < 30;i++)
  if (activeceilings[i] == (ceiling_t *)th)
      break;

     if (i<30)
     {
                saveg_write8(tc_ceiling);
  saveg_write_pad();
                saveg_write_ceiling_t((ceiling_t *) th);
     }
     continue;
 }

 if (th->function.acp1 == (actionf_p1)T_MoveCeiling)
 {
            saveg_write8(tc_ceiling);
     saveg_write_pad();
            saveg_write_ceiling_t((ceiling_t *) th);
     continue;
 }

 if (th->function.acp1 == (actionf_p1)T_VerticalDoor)
 {
            saveg_write8(tc_door);
     saveg_write_pad();
            saveg_write_vldoor_t((vldoor_t *) th);
     continue;
 }

 if (th->function.acp1 == (actionf_p1)T_MoveFloor)
 {
            saveg_write8(tc_floor);
     saveg_write_pad();
            saveg_write_floormove_t((floormove_t *) th);
     continue;
 }

 if (th->function.acp1 == (actionf_p1)T_PlatRaise)
 {
            saveg_write8(tc_plat);
     saveg_write_pad();
            saveg_write_plat_t((plat_t *) th);
     continue;
 }

 if (th->function.acp1 == (actionf_p1)T_LightFlash)
 {
            saveg_write8(tc_flash);
     saveg_write_pad();
            saveg_write_lightflash_t((lightflash_t *) th);
     continue;
 }

 if (th->function.acp1 == (actionf_p1)T_StrobeFlash)
 {
            saveg_write8(tc_strobe);
     saveg_write_pad();
            saveg_write_strobe_t((strobe_t *) th);
     continue;
 }

 if (th->function.acp1 == (actionf_p1)T_Glow)
 {
            saveg_write8(tc_glow);
     saveg_write_pad();
            saveg_write_glow_t((glow_t *) th);
     continue;
 }
    }


    saveg_write8(tc_endspecials);

}





void P_UnArchiveSpecials (void)
{
    byte tclass;
    ceiling_t* ceiling;
    vldoor_t* door;
    floormove_t* floor;
    plat_t* plat;
    lightflash_t* flash;
    strobe_t* strobe;
    glow_t* glow;



    while (1)
    {
 tclass = saveg_read8();

 switch (tclass)
 {
   case tc_endspecials:
     return;

   case tc_ceiling:
     saveg_read_pad();
     ceiling = Z_Malloc (sizeof(*ceiling), PU_LEVEL, ((void*)0));
            saveg_read_ceiling_t(ceiling);
     ceiling->sector->specialdata = ceiling;

     if (ceiling->thinker.function.acp1)
  ceiling->thinker.function.acp1 = (actionf_p1)T_MoveCeiling;

     P_AddThinker (&ceiling->thinker);
     P_AddActiveCeiling(ceiling);
     break;

   case tc_door:
     saveg_read_pad();
     door = Z_Malloc (sizeof(*door), PU_LEVEL, ((void*)0));
            saveg_read_vldoor_t(door);
     door->sector->specialdata = door;
     door->thinker.function.acp1 = (actionf_p1)T_VerticalDoor;
     P_AddThinker (&door->thinker);
     break;

   case tc_floor:
     saveg_read_pad();
     floor = Z_Malloc (sizeof(*floor), PU_LEVEL, ((void*)0));
            saveg_read_floormove_t(floor);
     floor->sector->specialdata = floor;
     floor->thinker.function.acp1 = (actionf_p1)T_MoveFloor;
     P_AddThinker (&floor->thinker);
     break;

   case tc_plat:
     saveg_read_pad();
     plat = Z_Malloc (sizeof(*plat), PU_LEVEL, ((void*)0));
            saveg_read_plat_t(plat);
     plat->sector->specialdata = plat;

     if (plat->thinker.function.acp1)
  plat->thinker.function.acp1 = (actionf_p1)T_PlatRaise;

     P_AddThinker (&plat->thinker);
     P_AddActivePlat(plat);
     break;

   case tc_flash:
     saveg_read_pad();
     flash = Z_Malloc (sizeof(*flash), PU_LEVEL, ((void*)0));
            saveg_read_lightflash_t(flash);
     flash->thinker.function.acp1 = (actionf_p1)T_LightFlash;
     P_AddThinker (&flash->thinker);
     break;

   case tc_strobe:
     saveg_read_pad();
     strobe = Z_Malloc (sizeof(*strobe), PU_LEVEL, ((void*)0));
            saveg_read_strobe_t(strobe);
     strobe->thinker.function.acp1 = (actionf_p1)T_StrobeFlash;
     P_AddThinker (&strobe->thinker);
     break;

   case tc_glow:
     saveg_read_pad();
     glow = Z_Malloc (sizeof(*glow), PU_LEVEL, ((void*)0));
            saveg_read_glow_t(glow);
     glow->thinker.function.acp1 = (actionf_p1)T_Glow;
     P_AddThinker (&glow->thinker);
     break;

   default:
     I_Error ("P_UnarchiveSpecials:Unknown tclass %i "
       "in savegame",tclass);
 }

    }

}
void P_SpawnMapThing (mapthing_t* mthing);






int numvertexes;
vertex_t* vertexes;

int numsegs;
seg_t* segs;

int numsectors;
sector_t* sectors;

int numsubsectors;
subsector_t* subsectors;

int numnodes;
node_t* nodes;

int numlines;
line_t* lines;

int numsides;
side_t* sides;

static int totallines;
int bmapwidth;
int bmapheight;
short* blockmap;

short* blockmaplump;

fixed_t bmaporgx;
fixed_t bmaporgy;

mobj_t** blocklinks;
byte* rejectmatrix;





mapthing_t deathmatchstarts[10];
mapthing_t* deathmatch_p;
mapthing_t playerstarts[4];
void P_LoadVertexes (int lump)
{
    byte* data;
    int i;
    mapvertex_t* ml;
    vertex_t* li;



    numvertexes = W_LumpLength (lump) / sizeof(mapvertex_t);


    vertexes = Z_Malloc (numvertexes*sizeof(vertex_t),PU_LEVEL,0);


    data = W_CacheLumpNum (lump, PU_STATIC);

    ml = (mapvertex_t *)data;
    li = vertexes;



    for (i=0 ; i<numvertexes ; i++, li++, ml++)
    {
 li->x = ((signed short) (ml->x))<<16;
 li->y = ((signed short) (ml->y))<<16;
    }


    W_ReleaseLumpNum(lump);
}




sector_t* GetSectorAtNullAddress(void)
{
    static boolean null_sector_is_initialized = false;
    static sector_t null_sector;

    if (!null_sector_is_initialized)
    {
        memset(&null_sector, 0, sizeof(null_sector));
        I_GetMemoryValue(0, &null_sector.floorheight, 4);
        I_GetMemoryValue(4, &null_sector.ceilingheight, 4);
        null_sector_is_initialized = true;
    }

    return &null_sector;
}




void P_LoadSegs (int lump)
{
    byte* data;
    int i;
    mapseg_t* ml;
    seg_t* li;
    line_t* ldef;
    int linedef;
    int side;
    int sidenum;

    numsegs = W_LumpLength (lump) / sizeof(mapseg_t);
    segs = Z_Malloc (numsegs*sizeof(seg_t),PU_LEVEL,0);
    memset (segs, 0, numsegs*sizeof(seg_t));
    data = W_CacheLumpNum (lump,PU_STATIC);

    ml = (mapseg_t *)data;
    li = segs;
    for (i=0 ; i<numsegs ; i++, li++, ml++)
    {
 li->v1 = &vertexes[((signed short) (ml->v1))];
 li->v2 = &vertexes[((signed short) (ml->v2))];

 li->angle = (((signed short) (ml->angle)))<<16;
 li->offset = (((signed short) (ml->offset)))<<16;
 linedef = ((signed short) (ml->linedef));
 ldef = &lines[linedef];
 li->linedef = ldef;
 side = ((signed short) (ml->side));
 li->sidedef = &sides[ldef->sidenum[side]];
 li->frontsector = sides[ldef->sidenum[side]].sector;

        if (ldef-> flags & 4)
        {
            sidenum = ldef->sidenum[side ^ 1];







            if (sidenum < 0 || sidenum >= numsides)
            {
                li->backsector = GetSectorAtNullAddress();
            }
            else
            {
                li->backsector = sides[sidenum].sector;
            }
        }
        else
        {
     li->backsector = 0;
        }
    }

    W_ReleaseLumpNum(lump);
}





void P_LoadSubsectors (int lump)
{
    byte* data;
    int i;
    mapsubsector_t* ms;
    subsector_t* ss;

    numsubsectors = W_LumpLength (lump) / sizeof(mapsubsector_t);
    subsectors = Z_Malloc (numsubsectors*sizeof(subsector_t),PU_LEVEL,0);
    data = W_CacheLumpNum (lump,PU_STATIC);

    ms = (mapsubsector_t *)data;
    memset (subsectors,0, numsubsectors*sizeof(subsector_t));
    ss = subsectors;

    for (i=0 ; i<numsubsectors ; i++, ss++, ms++)
    {
 ss->numlines = ((signed short) (ms->numsegs));
 ss->firstline = ((signed short) (ms->firstseg));
    }

    W_ReleaseLumpNum(lump);
}






void P_LoadSectors (int lump)
{
    byte* data;
    int i;
    mapsector_t* ms;
    sector_t* ss;

    numsectors = W_LumpLength (lump) / sizeof(mapsector_t);
    sectors = Z_Malloc (numsectors*sizeof(sector_t),PU_LEVEL,0);
    memset (sectors, 0, numsectors*sizeof(sector_t));
    data = W_CacheLumpNum (lump,PU_STATIC);

    ms = (mapsector_t *)data;
    ss = sectors;
    for (i=0 ; i<numsectors ; i++, ss++, ms++)
    {
 ss->floorheight = ((signed short) (ms->floorheight))<<16;
 ss->ceilingheight = ((signed short) (ms->ceilingheight))<<16;
 ss->floorpic = R_FlatNumForName(ms->floorpic);
 ss->ceilingpic = R_FlatNumForName(ms->ceilingpic);
 ss->lightlevel = ((signed short) (ms->lightlevel));
 ss->special = ((signed short) (ms->special));
 ss->tag = ((signed short) (ms->tag));
 ss->thinglist = ((void*)0);
    }

    W_ReleaseLumpNum(lump);
}





void P_LoadNodes (int lump)
{
    byte* data;
    int i;
    int j;
    int k;
    mapnode_t* mn;
    node_t* no;

    numnodes = W_LumpLength (lump) / sizeof(mapnode_t);
    nodes = Z_Malloc (numnodes*sizeof(node_t),PU_LEVEL,0);
    data = W_CacheLumpNum (lump,PU_STATIC);

    mn = (mapnode_t *)data;
    no = nodes;

    for (i=0 ; i<numnodes ; i++, no++, mn++)
    {
 no->x = ((signed short) (mn->x))<<16;
 no->y = ((signed short) (mn->y))<<16;
 no->dx = ((signed short) (mn->dx))<<16;
 no->dy = ((signed short) (mn->dy))<<16;
 for (j=0 ; j<2 ; j++)
 {
     no->children[j] = ((signed short) (mn->children[j]));
     for (k=0 ; k<4 ; k++)
  no->bbox[j][k] = ((signed short) (mn->bbox[j][k]))<<16;
 }
    }

    W_ReleaseLumpNum(lump);
}





void P_LoadThings (int lump)
{
    byte *data;
    int i;
    mapthing_t *mt;
    mapthing_t spawnthing;
    int numthings;
    boolean spawn;

    data = W_CacheLumpNum (lump,PU_STATIC);
    numthings = W_LumpLength (lump) / sizeof(mapthing_t);

    mt = (mapthing_t *)data;
    for (i=0 ; i<numthings ; i++, mt++)
    {
 spawn = true;


 if (gamemode != commercial)
 {
     switch (((signed short) (mt->type)))
     {
       case 68:
       case 64:
       case 88:
       case 89:
       case 69:
       case 67:
       case 71:
       case 65:
       case 66:
       case 84:
  spawn = false;
  break;
     }
 }
 if (spawn == false)
     break;


 spawnthing.x = ((signed short) (mt->x));
 spawnthing.y = ((signed short) (mt->y));
 spawnthing.angle = ((signed short) (mt->angle));
 spawnthing.type = ((signed short) (mt->type));
 spawnthing.options = ((signed short) (mt->options));

 P_SpawnMapThing(&spawnthing);
    }

    W_ReleaseLumpNum(lump);
}






void P_LoadLineDefs (int lump)
{
    byte* data;
    int i;
    maplinedef_t* mld;
    line_t* ld;
    vertex_t* v1;
    vertex_t* v2;

    numlines = W_LumpLength (lump) / sizeof(maplinedef_t);
    lines = Z_Malloc (numlines*sizeof(line_t),PU_LEVEL,0);
    memset (lines, 0, numlines*sizeof(line_t));
    data = W_CacheLumpNum (lump,PU_STATIC);

    mld = (maplinedef_t *)data;
    ld = lines;
    for (i=0 ; i<numlines ; i++, mld++, ld++)
    {
 ld->flags = ((signed short) (mld->flags));
 ld->special = ((signed short) (mld->special));
 ld->tag = ((signed short) (mld->tag));
 v1 = ld->v1 = &vertexes[((signed short) (mld->v1))];
 v2 = ld->v2 = &vertexes[((signed short) (mld->v2))];
 ld->dx = v2->x - v1->x;
 ld->dy = v2->y - v1->y;

 if (!ld->dx)
     ld->slopetype = ST_VERTICAL;
 else if (!ld->dy)
     ld->slopetype = ST_HORIZONTAL;
 else
 {
     if (FixedDiv (ld->dy , ld->dx) > 0)
  ld->slopetype = ST_POSITIVE;
     else
  ld->slopetype = ST_NEGATIVE;
 }

 if (v1->x < v2->x)
 {
     ld->bbox[BOXLEFT] = v1->x;
     ld->bbox[BOXRIGHT] = v2->x;
 }
 else
 {
     ld->bbox[BOXLEFT] = v2->x;
     ld->bbox[BOXRIGHT] = v1->x;
 }

 if (v1->y < v2->y)
 {
     ld->bbox[BOXBOTTOM] = v1->y;
     ld->bbox[BOXTOP] = v2->y;
 }
 else
 {
     ld->bbox[BOXBOTTOM] = v2->y;
     ld->bbox[BOXTOP] = v1->y;
 }

 ld->sidenum[0] = ((signed short) (mld->sidenum[0]));
 ld->sidenum[1] = ((signed short) (mld->sidenum[1]));

 if (ld->sidenum[0] != -1)
     ld->frontsector = sides[ld->sidenum[0]].sector;
 else
     ld->frontsector = 0;

 if (ld->sidenum[1] != -1)
     ld->backsector = sides[ld->sidenum[1]].sector;
 else
     ld->backsector = 0;
    }

    W_ReleaseLumpNum(lump);
}





void P_LoadSideDefs (int lump)
{
    byte* data;
    int i;
    mapsidedef_t* msd;
    side_t* sd;

    numsides = W_LumpLength (lump) / sizeof(mapsidedef_t);
    sides = Z_Malloc (numsides*sizeof(side_t),PU_LEVEL,0);
    memset (sides, 0, numsides*sizeof(side_t));
    data = W_CacheLumpNum (lump,PU_STATIC);

    msd = (mapsidedef_t *)data;
    sd = sides;
    for (i=0 ; i<numsides ; i++, msd++, sd++)
    {
 sd->textureoffset = ((signed short) (msd->textureoffset))<<16;
 sd->rowoffset = ((signed short) (msd->rowoffset))<<16;
 sd->toptexture = R_TextureNumForName(msd->toptexture);
 sd->bottomtexture = R_TextureNumForName(msd->bottomtexture);
 sd->midtexture = R_TextureNumForName(msd->midtexture);
 sd->sector = &sectors[((signed short) (msd->sector))];
    }

    W_ReleaseLumpNum(lump);
}





void P_LoadBlockMap (int lump)
{
    int i;
    int count;
    int lumplen;

    lumplen = W_LumpLength(lump);
    count = lumplen / 2;

    blockmaplump = Z_Malloc(lumplen, PU_LEVEL, ((void*)0));
    W_ReadLump(lump, blockmaplump);
    blockmap = blockmaplump + 4;



    for (i=0; i<count; i++)
    {
 blockmaplump[i] = ((signed short) (blockmaplump[i]));
    }



    bmaporgx = blockmaplump[0]<<16;
    bmaporgy = blockmaplump[1]<<16;
    bmapwidth = blockmaplump[2];
    bmapheight = blockmaplump[3];



    count = sizeof(*blocklinks) * bmapwidth * bmapheight;
    blocklinks = Z_Malloc(count, PU_LEVEL, 0);
    memset(blocklinks, 0, count);
}
void P_GroupLines (void)
{
    line_t** linebuffer;
    int i;
    int j;
    line_t* li;
    sector_t* sector;
    subsector_t* ss;
    seg_t* seg;
    fixed_t bbox[4];
    int block;


    ss = subsectors;
    for (i=0 ; i<numsubsectors ; i++, ss++)
    {
 seg = &segs[ss->firstline];
 ss->sector = seg->sidedef->sector;
    }


    li = lines;
    totallines = 0;
    for (i=0 ; i<numlines ; i++, li++)
    {
 totallines++;
 li->frontsector->linecount++;

 if (li->backsector && li->backsector != li->frontsector)
 {
     li->backsector->linecount++;
     totallines++;
 }
    }


    linebuffer = Z_Malloc (totallines*sizeof(line_t *), PU_LEVEL, 0);

    for (i=0; i<numsectors; ++i)
    {


        sectors[i].lines = linebuffer;
        linebuffer += sectors[i].linecount;




        sectors[i].linecount = 0;
    }



    for (i=0; i<numlines; ++i)
    {
        li = &lines[i];

        if (li->frontsector != ((void*)0))
        {
            sector = li->frontsector;

            sector->lines[sector->linecount] = li;
            ++sector->linecount;
        }

        if (li->backsector != ((void*)0) && li->frontsector != li->backsector)
        {
            sector = li->backsector;

            sector->lines[sector->linecount] = li;
            ++sector->linecount;
        }
    }



    sector = sectors;
    for (i=0 ; i<numsectors ; i++, sector++)
    {
 M_ClearBox (bbox);

 for (j=0 ; j<sector->linecount; j++)
 {
            li = sector->lines[j];

            M_AddToBox (bbox, li->v1->x, li->v1->y);
            M_AddToBox (bbox, li->v2->x, li->v2->y);
 }


 sector->soundorg.x = (bbox[BOXRIGHT]+bbox[BOXLEFT])/2;
 sector->soundorg.y = (bbox[BOXTOP]+bbox[BOXBOTTOM])/2;


 block = (bbox[BOXTOP]-bmaporgy+32*(1<<16))>>(16 +7);
 block = block >= bmapheight ? bmapheight-1 : block;
 sector->blockbox[BOXTOP]=block;

 block = (bbox[BOXBOTTOM]-bmaporgy-32*(1<<16))>>(16 +7);
 block = block < 0 ? 0 : block;
 sector->blockbox[BOXBOTTOM]=block;

 block = (bbox[BOXRIGHT]-bmaporgx+32*(1<<16))>>(16 +7);
 block = block >= bmapwidth ? bmapwidth-1 : block;
 sector->blockbox[BOXRIGHT]=block;

 block = (bbox[BOXLEFT]-bmaporgx-32*(1<<16))>>(16 +7);
 block = block < 0 ? 0 : block;
 sector->blockbox[BOXLEFT]=block;
    }

}




static void PadRejectArray(byte *array, unsigned int len)
{
    unsigned int i;
    unsigned int byte_num;
    byte *dest;
    unsigned int padvalue;



    unsigned int rejectpad[4] =
    {
        ((totallines * 4 + 3) & ~3) + 24,
        0,
        50,
        0x1d4a11
    };



    dest = array;

    for (i=0; i<len && i<sizeof(rejectpad); ++i)
    {
        byte_num = i % 4;
        *dest = (rejectpad[i / 4] >> (byte_num * 8)) & 0xff;
        ++dest;
    }




    if (len > sizeof(rejectpad))
    {
        fprintf(__stderrp, "PadRejectArray: REJECT lump too short to pad! (%i > %i)\n",
                        len, (int) sizeof(rejectpad));



        if (M_CheckParm("-reject_pad_with_ff"))
        {
            padvalue = 0xff;
        }
        else
        {
            padvalue = 0xf00;
        }

        memset(array + sizeof(rejectpad), padvalue, len - sizeof(rejectpad));
    }
}

static void P_LoadReject(int lumpnum)
{
    int minlength;
    int lumplen;



    minlength = (numsectors * numsectors + 7) / 8;





    lumplen = W_LumpLength(lumpnum);

    if (lumplen >= minlength)
    {
        rejectmatrix = W_CacheLumpNum(lumpnum, PU_LEVEL);
    }
    else
    {
        rejectmatrix = Z_Malloc(minlength, PU_LEVEL, &rejectmatrix);
        W_ReadLump(lumpnum, rejectmatrix);

        PadRejectArray(rejectmatrix + lumplen, minlength - lumplen);
    }
}




void
P_SetupLevel
( int episode,
  int map,
  int playermask,
  skill_t skill)
{
    int i;
    char lumpname[9];
    int lumpnum;

    totalkills = totalitems = totalsecret = wminfo.maxfrags = 0;
    wminfo.partime = 180;
    for (i=0 ; i<4 ; i++)
    {
 players[i].killcount = players[i].secretcount
     = players[i].itemcount = 0;
    }



    players[consoleplayer].viewz = 1;


    S_Start ();

    Z_FreeTags (PU_LEVEL, PU_PURGELEVEL-1);


    P_InitThinkers ();


    if ( gamemode == commercial)
    {
 if (map<10)
     snprintf(lumpname, 9, "map0%i", map);
 else
     snprintf(lumpname, 9, "map%i", map);
    }
    else
    {
 lumpname[0] = 'E';
 lumpname[1] = '0' + episode;
 lumpname[2] = 'M';
 lumpname[3] = '0' + map;
 lumpname[4] = 0;
    }

    lumpnum = W_GetNumForName (lumpname);

    leveltime = 0;


    P_LoadBlockMap (lumpnum+ML_BLOCKMAP);
    P_LoadVertexes (lumpnum+ML_VERTEXES);
    P_LoadSectors (lumpnum+ML_SECTORS);
    P_LoadSideDefs (lumpnum+ML_SIDEDEFS);

    P_LoadLineDefs (lumpnum+ML_LINEDEFS);
    P_LoadSubsectors (lumpnum+ML_SSECTORS);
    P_LoadNodes (lumpnum+ML_NODES);
    P_LoadSegs (lumpnum+ML_SEGS);

    P_GroupLines ();
    P_LoadReject (lumpnum+ML_REJECT);

    bodyqueslot = 0;
    deathmatch_p = deathmatchstarts;
    P_LoadThings (lumpnum+ML_THINGS);


    if (deathmatch)
    {
 for (i=0 ; i<4 ; i++)
     if (playeringame[i])
     {
  players[i].mo = ((void*)0);
  G_DeathMatchSpawnPlayer (i);
     }

    }


    iquehead = iquetail = 0;


    P_SpawnSpecials ();





    if (precache)
 R_PrecacheLevel ();



}






void P_Init (void)
{
    P_InitSwitchList ();
    P_InitPicAnims ();
    R_InitSprites (sprnames);
}
fixed_t sightzstart;
fixed_t topslope;
fixed_t bottomslope;

divline_t strace;
fixed_t t2x;
fixed_t t2y;

int sightcounts[2];






int
P_DivlineSide
( fixed_t x,
  fixed_t y,
  divline_t* node )
{
    fixed_t dx;
    fixed_t dy;
    fixed_t left;
    fixed_t right;

    if (!node->dx)
    {
 if (x==node->x)
     return 2;

 if (x <= node->x)
     return node->dy > 0;

 return node->dy < 0;
    }

    if (!node->dy)
    {
 if (x==node->y)
     return 2;

 if (y <= node->y)
     return node->dx < 0;

 return node->dx > 0;
    }

    dx = (x - node->x);
    dy = (y - node->y);

    left = (node->dy>>16) * (dx>>16);
    right = (dy>>16) * (node->dx>>16);

    if (right < left)
 return 0;

    if (left == right)
 return 2;
    return 1;
}
fixed_t
P_InterceptVector2
( divline_t* v2,
  divline_t* v1 )
{
    fixed_t frac;
    fixed_t num;
    fixed_t den;

    den = FixedMul (v1->dy>>8,v2->dx) - FixedMul(v1->dx>>8,v2->dy);

    if (den == 0)
 return 0;


    num = FixedMul ( (v1->x - v2->x)>>8 ,v1->dy) +
 FixedMul ( (v2->y - v1->y)>>8 , v1->dx);
    frac = FixedDiv (num , den);

    return frac;
}






boolean P_CrossSubsector (int num)
{
    seg_t* seg;
    line_t* line;
    int s1;
    int s2;
    int count;
    subsector_t* sub;
    sector_t* front;
    sector_t* back;
    fixed_t opentop;
    fixed_t openbottom;
    divline_t divl;
    vertex_t* v1;
    vertex_t* v2;
    fixed_t frac;
    fixed_t slope;


    if (num>=numsubsectors)
 I_Error ("P_CrossSubsector: ss %i with numss = %i",
   num,
   numsubsectors);


    sub = &subsectors[num];


    count = sub->numlines;
    seg = &segs[sub->firstline];

    for ( ; count ; seg++, count--)
    {
 line = seg->linedef;


 if (line->validcount == validcount)
     continue;

 line->validcount = validcount;

 v1 = line->v1;
 v2 = line->v2;
 s1 = P_DivlineSide (v1->x,v1->y, &strace);
 s2 = P_DivlineSide (v2->x, v2->y, &strace);


 if (s1 == s2)
     continue;

 divl.x = v1->x;
 divl.y = v1->y;
 divl.dx = v2->x - v1->x;
 divl.dy = v2->y - v1->y;
 s1 = P_DivlineSide (strace.x, strace.y, &divl);
 s2 = P_DivlineSide (t2x, t2y, &divl);


 if (s1 == s2)
     continue;




        if (line->backsector == ((void*)0))
        {
            return false;
        }



 if ( !(line->flags & 4) )
     return false;


 front = seg->frontsector;
 back = seg->backsector;


 if (front->floorheight == back->floorheight
     && front->ceilingheight == back->ceilingheight)
     continue;



 if (front->ceilingheight < back->ceilingheight)
     opentop = front->ceilingheight;
 else
     opentop = back->ceilingheight;


 if (front->floorheight > back->floorheight)
     openbottom = front->floorheight;
 else
     openbottom = back->floorheight;


 if (openbottom >= opentop)
     return false;

 frac = P_InterceptVector2 (&strace, &divl);

 if (front->floorheight != back->floorheight)
 {
     slope = FixedDiv (openbottom - sightzstart , frac);
     if (slope > bottomslope)
  bottomslope = slope;
 }

 if (front->ceilingheight != back->ceilingheight)
 {
     slope = FixedDiv (opentop - sightzstart , frac);
     if (slope < topslope)
  topslope = slope;
 }

 if (topslope <= bottomslope)
     return false;
    }

    return true;
}
boolean P_CrossBSPNode (int bspnum)
{
    node_t* bsp;
    int side;

    if (bspnum & 0x8000)
    {
 if (bspnum == -1)
     return P_CrossSubsector (0);
 else
     return P_CrossSubsector (bspnum&(~0x8000));
    }

    bsp = &nodes[bspnum];


    side = P_DivlineSide (strace.x, strace.y, (divline_t *)bsp);
    if (side == 2)
 side = 0;


    if (!P_CrossBSPNode (bsp->children[side]) )
 return false;


    if (side == P_DivlineSide (t2x, t2y,(divline_t *)bsp))
    {

 return true;
    }


    return P_CrossBSPNode (bsp->children[side^1]);
}
boolean
P_CheckSight
( mobj_t* t1,
  mobj_t* t2 )
{
    int s1;
    int s2;
    int pnum;
    int bytenum;
    int bitnum;




    s1 = (t1->subsector->sector - sectors);
    s2 = (t2->subsector->sector - sectors);
    pnum = s1*numsectors + s2;
    bytenum = pnum>>3;
    bitnum = 1 << (pnum&7);


    if (rejectmatrix[bytenum]&bitnum)
    {
 sightcounts[0]++;


 return false;
    }



    sightcounts[1]++;

    validcount++;

    sightzstart = t1->z + t1->height - (t1->height>>2);
    topslope = (t2->z+t2->height) - sightzstart;
    bottomslope = (t2->z) - sightzstart;

    strace.x = t1->x;
    strace.y = t1->y;
    t2x = t2->x;
    t2y = t2->y;
    strace.dx = t2->x - t1->x;
    strace.dy = t2->y - t1->y;


    return P_CrossBSPNode (numnodes-1);
}
typedef struct
{
    boolean istexture;
    int picnum;
    int basepic;
    int numpics;
    int speed;

} anim_t;




typedef struct
{
    int istexture;
    char endname[9];
    char startname[9];
    int speed;
} animdef_t;





extern anim_t anims[32];
extern anim_t* lastanim;
animdef_t animdefs[] =
{
    {false, "NUKAGE3", "NUKAGE1", 8},
    {false, "FWATER4", "FWATER1", 8},
    {false, "SWATER4", "SWATER1", 8},
    {false, "LAVA4", "LAVA1", 8},
    {false, "BLOOD3", "BLOOD1", 8},


    {false, "RROCK08", "RROCK05", 8},
    {false, "SLIME04", "SLIME01", 8},
    {false, "SLIME08", "SLIME05", 8},
    {false, "SLIME12", "SLIME09", 8},

    {true, "BLODGR4", "BLODGR1", 8},
    {true, "SLADRIP3", "SLADRIP1", 8},

    {true, "BLODRIP4", "BLODRIP1", 8},
    {true, "FIREWALL", "FIREWALA", 8},
    {true, "GSTFONT3", "GSTFONT1", 8},
    {true, "FIRELAVA", "FIRELAV3", 8},
    {true, "FIREMAG3", "FIREMAG1", 8},
    {true, "FIREBLU2", "FIREBLU1", 8},
    {true, "ROCKRED3", "ROCKRED1", 8},

    {true, "BFALL4", "BFALL1", 8},
    {true, "SFALL4", "SFALL1", 8},
    {true, "WFALL4", "WFALL1", 8},
    {true, "DBRAIN4", "DBRAIN1", 8},

    {-1, "", "", 0},
};

anim_t anims[32];
anim_t* lastanim;







extern short numlinespecials;
extern line_t* linespeciallist[64];



void P_InitPicAnims (void)
{
    int i;



    lastanim = anims;
    for (i=0 ; animdefs[i].istexture != -1 ; i++)
    {
        char *startname, *endname;

        startname = (animdefs[i].startname);
        endname = (animdefs[i].endname);

 if (animdefs[i].istexture)
 {

     if (R_CheckTextureNumForName(startname) == -1)
  continue;

     lastanim->picnum = R_TextureNumForName(endname);
     lastanim->basepic = R_TextureNumForName(startname);
 }
 else
 {
     if (W_CheckNumForName(startname) == -1)
  continue;

     lastanim->picnum = R_FlatNumForName(endname);
     lastanim->basepic = R_FlatNumForName(startname);
 }

 lastanim->istexture = animdefs[i].istexture;
 lastanim->numpics = lastanim->picnum - lastanim->basepic + 1;

 if (lastanim->numpics < 2)
     I_Error ("P_InitPicAnims: bad cycle from %s to %s",
       startname, endname);

 lastanim->speed = animdefs[i].speed;
 lastanim++;
    }

}
side_t*
getSide
( int currentSector,
  int line,
  int side )
{
    return &sides[ (sectors[currentSector].lines[line])->sidenum[side] ];
}
sector_t*
getSector
( int currentSector,
  int line,
  int side )
{
    return sides[ (sectors[currentSector].lines[line])->sidenum[side] ].sector;
}







int
twoSided
( int sector,
  int line )
{
    return (sectors[sector].lines[line])->flags & 4;
}
sector_t*
getNextSector
( line_t* line,
  sector_t* sec )
{
    if (!(line->flags & 4))
 return ((void*)0);

    if (line->frontsector == sec)
 return line->backsector;

    return line->frontsector;
}







fixed_t P_FindLowestFloorSurrounding(sector_t* sec)
{
    int i;
    line_t* check;
    sector_t* other;
    fixed_t floor = sec->floorheight;

    for (i=0 ;i < sec->linecount ; i++)
    {
 check = sec->lines[i];
 other = getNextSector(check,sec);

 if (!other)
     continue;

 if (other->floorheight < floor)
     floor = other->floorheight;
    }
    return floor;
}







fixed_t P_FindHighestFloorSurrounding(sector_t *sec)
{
    int i;
    line_t* check;
    sector_t* other;
    fixed_t floor = -500*(1<<16);

    for (i=0 ;i < sec->linecount ; i++)
    {
 check = sec->lines[i];
 other = getNextSector(check,sec);

 if (!other)
     continue;

 if (other->floorheight > floor)
     floor = other->floorheight;
    }
    return floor;
}
fixed_t
P_FindNextHighestFloor
( sector_t* sec,
  int currentheight )
{
    int i;
    int h;
    int min;
    line_t* check;
    sector_t* other;
    fixed_t height = currentheight;
    fixed_t heightlist[20 + 2];

    for (i=0, h=0; i < sec->linecount; i++)
    {
        check = sec->lines[i];
        other = getNextSector(check,sec);

        if (!other)
            continue;

        if (other->floorheight > height)
        {

            if (h == 20 + 1)
            {
                height = other->floorheight;
            }
            else if (h == 20 + 2)
            {

                I_Error("Sector with more than 22 adjoining sectors. "
                        "Vanilla will crash here");
            }

            heightlist[h++] = other->floorheight;
        }
    }


    if (!h)
    {
        return currentheight;
    }

    min = heightlist[0];


    for (i = 1; i < h; i++)
    {
        if (heightlist[i] < min)
        {
            min = heightlist[i];
        }
    }

    return min;
}




fixed_t
P_FindLowestCeilingSurrounding(sector_t* sec)
{
    int i;
    line_t* check;
    sector_t* other;
    fixed_t height = 2147483647;

    for (i=0 ;i < sec->linecount ; i++)
    {
 check = sec->lines[i];
 other = getNextSector(check,sec);

 if (!other)
     continue;

 if (other->ceilingheight < height)
     height = other->ceilingheight;
    }
    return height;
}





fixed_t P_FindHighestCeilingSurrounding(sector_t* sec)
{
    int i;
    line_t* check;
    sector_t* other;
    fixed_t height = 0;

    for (i=0 ;i < sec->linecount ; i++)
    {
 check = sec->lines[i];
 other = getNextSector(check,sec);

 if (!other)
     continue;

 if (other->ceilingheight > height)
     height = other->ceilingheight;
    }
    return height;
}






int
P_FindSectorFromLineTag
( line_t* line,
  int start )
{
    int i;

    for (i=start+1;i<numsectors;i++)
 if (sectors[i].tag == line->tag)
     return i;

    return -1;
}







int
P_FindMinSurroundingLight
( sector_t* sector,
  int max )
{
    int i;
    int min;
    line_t* line;
    sector_t* check;

    min = max;
    for (i=0 ; i < sector->linecount ; i++)
    {
 line = sector->lines[i];
 check = getNextSector(line,sector);

 if (!check)
     continue;

 if (check->lightlevel < min)
     min = check->lightlevel;
    }
    return min;
}
void
P_CrossSpecialLine
( int linenum,
  int side,
  mobj_t* thing )
{
    line_t* line;
    int ok;

    line = &lines[linenum];


    if (!thing->player)
    {

 switch(thing->type)
 {
   case MT_ROCKET:
   case MT_PLASMA:
   case MT_BFG:
   case MT_TROOPSHOT:
   case MT_HEADSHOT:
   case MT_BRUISERSHOT:
     return;
     break;

   default: break;
 }

 ok = 0;
 switch(line->special)
 {
   case 39:
   case 97:
   case 125:
   case 126:
   case 4:
   case 10:
   case 88:
     ok = 1;
     break;
 }
 if (!ok)
     return;
    }



    switch (line->special)
    {


      case 2:

 EV_DoDoor(line,vld_open);
 line->special = 0;
 break;

      case 3:

 EV_DoDoor(line,vld_close);
 line->special = 0;
 break;

      case 4:

 EV_DoDoor(line,vld_normal);
 line->special = 0;
 break;

      case 5:

 EV_DoFloor(line,raiseFloor);
 line->special = 0;
 break;

      case 6:

 EV_DoCeiling(line,fastCrushAndRaise);
 line->special = 0;
 break;

      case 8:

 EV_BuildStairs(line,build8);
 line->special = 0;
 break;

      case 10:

 EV_DoPlat(line,downWaitUpStay,0);
 line->special = 0;
 break;

      case 12:

 EV_LightTurnOn(line,0);
 line->special = 0;
 break;

      case 13:

 EV_LightTurnOn(line,255);
 line->special = 0;
 break;

      case 16:

 EV_DoDoor(line,vld_close30ThenOpen);
 line->special = 0;
 break;

      case 17:

 EV_StartLightStrobing(line);
 line->special = 0;
 break;

      case 19:

 EV_DoFloor(line,lowerFloor);
 line->special = 0;
 break;

      case 22:

 EV_DoPlat(line,raiseToNearestAndChange,0);
 line->special = 0;
 break;

      case 25:

 EV_DoCeiling(line,crushAndRaise);
 line->special = 0;
 break;

      case 30:


 EV_DoFloor(line,raiseToTexture);
 line->special = 0;
 break;

      case 35:

 EV_LightTurnOn(line,35);
 line->special = 0;
 break;

      case 36:

 EV_DoFloor(line,turboLower);
 line->special = 0;
 break;

      case 37:

 EV_DoFloor(line,lowerAndChange);
 line->special = 0;
 break;

      case 38:

 EV_DoFloor( line, lowerFloorToLowest );
 line->special = 0;
 break;

      case 39:

 EV_Teleport( line, side, thing );
 line->special = 0;
 break;

      case 40:

 EV_DoCeiling( line, raiseToHighest );
 EV_DoFloor( line, lowerFloorToLowest );
 line->special = 0;
 break;

      case 44:

 EV_DoCeiling( line, lowerAndCrush );
 line->special = 0;
 break;

      case 52:

 G_ExitLevel ();
 break;

      case 53:

 EV_DoPlat(line,perpetualRaise,0);
 line->special = 0;
 break;

      case 54:

 EV_StopPlat(line);
 line->special = 0;
 break;

      case 56:

 EV_DoFloor(line,raiseFloorCrush);
 line->special = 0;
 break;

      case 57:

 EV_CeilingCrushStop(line);
 line->special = 0;
 break;

      case 58:

 EV_DoFloor(line,raiseFloor24);
 line->special = 0;
 break;

      case 59:

 EV_DoFloor(line,raiseFloor24AndChange);
 line->special = 0;
 break;

      case 104:

 EV_TurnTagLightsOff(line);
 line->special = 0;
 break;

      case 108:

 EV_DoDoor (line,vld_blazeRaise);
 line->special = 0;
 break;

      case 109:

 EV_DoDoor (line,vld_blazeOpen);
 line->special = 0;
 break;

      case 100:

 EV_BuildStairs(line,turbo16);
 line->special = 0;
 break;

      case 110:

 EV_DoDoor (line,vld_blazeClose);
 line->special = 0;
 break;

      case 119:

 EV_DoFloor(line,raiseFloorToNearest);
 line->special = 0;
 break;

      case 121:

 EV_DoPlat(line,blazeDWUS,0);
 line->special = 0;
 break;

      case 124:

 G_SecretExitLevel ();
 break;

      case 125:

 if (!thing->player)
 {
     EV_Teleport( line, side, thing );
     line->special = 0;
 }
 break;

      case 130:

 EV_DoFloor(line,raiseFloorTurbo);
 line->special = 0;
 break;

      case 141:

 EV_DoCeiling(line,silentCrushAndRaise);
 line->special = 0;
 break;


      case 72:

 EV_DoCeiling( line, lowerAndCrush );
 break;

      case 73:

 EV_DoCeiling(line,crushAndRaise);
 break;

      case 74:

 EV_CeilingCrushStop(line);
 break;

      case 75:

 EV_DoDoor(line,vld_close);
 break;

      case 76:

 EV_DoDoor(line,vld_close30ThenOpen);
 break;

      case 77:

 EV_DoCeiling(line,fastCrushAndRaise);
 break;

      case 79:

 EV_LightTurnOn(line,35);
 break;

      case 80:

 EV_LightTurnOn(line,0);
 break;

      case 81:

 EV_LightTurnOn(line,255);
 break;

      case 82:

 EV_DoFloor( line, lowerFloorToLowest );
 break;

      case 83:

 EV_DoFloor(line,lowerFloor);
 break;

      case 84:

 EV_DoFloor(line,lowerAndChange);
 break;

      case 86:

 EV_DoDoor(line,vld_open);
 break;

      case 87:

 EV_DoPlat(line,perpetualRaise,0);
 break;

      case 88:

 EV_DoPlat(line,downWaitUpStay,0);
 break;

      case 89:

 EV_StopPlat(line);
 break;

      case 90:

 EV_DoDoor(line,vld_normal);
 break;

      case 91:

 EV_DoFloor(line,raiseFloor);
 break;

      case 92:

 EV_DoFloor(line,raiseFloor24);
 break;

      case 93:

 EV_DoFloor(line,raiseFloor24AndChange);
 break;

      case 94:

 EV_DoFloor(line,raiseFloorCrush);
 break;

      case 95:


 EV_DoPlat(line,raiseToNearestAndChange,0);
 break;

      case 96:


 EV_DoFloor(line,raiseToTexture);
 break;

      case 97:

 EV_Teleport( line, side, thing );
 break;

      case 98:

 EV_DoFloor(line,turboLower);
 break;

      case 105:

 EV_DoDoor (line,vld_blazeRaise);
 break;

      case 106:

 EV_DoDoor (line,vld_blazeOpen);
 break;

      case 107:

 EV_DoDoor (line,vld_blazeClose);
 break;

      case 120:

 EV_DoPlat(line,blazeDWUS,0);
 break;

      case 126:

 if (!thing->player)
     EV_Teleport( line, side, thing );
 break;

      case 128:

 EV_DoFloor(line,raiseFloorToNearest);
 break;

      case 129:

 EV_DoFloor(line,raiseFloorTurbo);
 break;
    }
}







void
P_ShootSpecialLine
( mobj_t* thing,
  line_t* line )
{
    int ok;


    if (!thing->player)
    {
 ok = 0;
 switch(line->special)
 {
   case 46:

     ok = 1;
     break;
 }
 if (!ok)
     return;
    }

    switch(line->special)
    {
      case 24:

 EV_DoFloor(line,raiseFloor);
 P_ChangeSwitchTexture(line,0);
 break;

      case 46:

 EV_DoDoor(line,vld_open);
 P_ChangeSwitchTexture(line,1);
 break;

      case 47:

 EV_DoPlat(line,raiseToNearestAndChange,0);
 P_ChangeSwitchTexture(line,0);
 break;
    }
}
void P_PlayerInSpecialSector (player_t* player)
{
    sector_t* sector;

    sector = player->mo->subsector->sector;


    if (player->mo->z != sector->floorheight)
 return;


    switch (sector->special)
    {
      case 5:

 if (!player->powers[pw_ironfeet])
     if (!(leveltime&0x1f))
  P_DamageMobj (player->mo, ((void*)0), ((void*)0), 10);
 break;

      case 7:

 if (!player->powers[pw_ironfeet])
     if (!(leveltime&0x1f))
  P_DamageMobj (player->mo, ((void*)0), ((void*)0), 5);
 break;

      case 16:

      case 4:

 if (!player->powers[pw_ironfeet]
     || (P_Random()<5) )
 {
     if (!(leveltime&0x1f))
  P_DamageMobj (player->mo, ((void*)0), ((void*)0), 20);
 }
 break;

      case 9:

 player->secretcount++;
 sector->special = 0;
 break;

      case 11:

 player->cheats &= ~CF_GODMODE;

 if (!(leveltime&0x1f))
     P_DamageMobj (player->mo, ((void*)0), ((void*)0), 20);

 if (player->health <= 10)
     G_ExitLevel();
 break;

      default:
 I_Error ("P_PlayerInSpecialSector: "
   "unknown special %i",
   sector->special);
 break;
    };
}
boolean levelTimer;
int levelTimeCount;

void P_UpdateSpecials (void)
{
    anim_t* anim;
    int pic;
    int i;
    line_t* line;



    if (levelTimer == true)
    {
 levelTimeCount--;
 if (!levelTimeCount)
     G_ExitLevel();
    }


    for (anim = anims ; anim < lastanim ; anim++)
    {
 for (i=anim->basepic ; i<anim->basepic+anim->numpics ; i++)
 {
     pic = anim->basepic + ( (leveltime/anim->speed + i)%anim->numpics );
     if (anim->istexture)
  texturetranslation[i] = pic;
     else
  flattranslation[i] = pic;
 }
    }



    for (i = 0; i < numlinespecials; i++)
    {
 line = linespeciallist[i];
 switch(line->special)
 {
   case 48:

     sides[line->sidenum[0]].textureoffset += (1<<16);
     break;
 }
    }



    for (i = 0; i < 16; i++)
 if (buttonlist[i].btimer)
 {
     buttonlist[i].btimer--;
     if (!buttonlist[i].btimer)
     {
  switch(buttonlist[i].where)
  {
    case top:
      sides[buttonlist[i].line->sidenum[0]].toptexture =
   buttonlist[i].btexture;
      break;

    case middle:
      sides[buttonlist[i].line->sidenum[0]].midtexture =
   buttonlist[i].btexture;
      break;

    case bottom:
      sides[buttonlist[i].line->sidenum[0]].bottomtexture =
   buttonlist[i].btexture;
      break;
  }
  S_StartSound(&buttonlist[i].soundorg,sfx_swtchn);
  memset(&buttonlist[i],0,sizeof(button_t));
     }
 }
}
static void DonutOverrun(fixed_t *s3_floorheight, short *s3_floorpic,
                         line_t *line, sector_t *pillar_sector)
{
    static int first = 1;
    static int tmp_s3_floorheight;
    static int tmp_s3_floorpic;

    extern int numflats;

    if (first)
    {
        int p;


        first = 0;


        tmp_s3_floorheight = 0x00000000;
        tmp_s3_floorpic = 0x16;
        p = M_CheckParmWithArgs("-donut", 2);

        if (p > 0)
        {
            M_StrToInt(myargv[p + 1], &tmp_s3_floorheight);
            M_StrToInt(myargv[p + 2], &tmp_s3_floorpic);

            if (tmp_s3_floorpic >= numflats)
            {
                fprintf(__stderrp,
                        "DonutOverrun: The second parameter for \"-donut\" "
                        "switch should be greater than 0 and less than number "
                        "of flats (%d). Using default value (%d) instead. \n",
                        numflats, 0x16);
                tmp_s3_floorpic = 0x16;
            }
        }
    }
    *s3_floorheight = (fixed_t) tmp_s3_floorheight;
    *s3_floorpic = (short) tmp_s3_floorpic;
}





int EV_DoDonut(line_t* line)
{
    sector_t* s1;
    sector_t* s2;
    sector_t* s3;
    int secnum;
    int rtn;
    int i;
    floormove_t* floor;
    fixed_t s3_floorheight;
    short s3_floorpic;

    secnum = -1;
    rtn = 0;
    while ((secnum = P_FindSectorFromLineTag(line,secnum)) >= 0)
    {
 s1 = &sectors[secnum];


 if (s1->specialdata)
     continue;

 rtn = 1;
 s2 = getNextSector(s1->lines[0],s1);
        if (s2 == ((void*)0))
        {
            fprintf(__stderrp,
                    "EV_DoDonut: linedef had no second sidedef! "
                    "Unexpected behavior may occur in Vanilla Doom. \n");
     break;
        }

 for (i = 0; i < s2->linecount; i++)
 {
     s3 = s2->lines[i]->backsector;

     if (s3 == s1)
  continue;

            if (s3 == ((void*)0))
            {






                fprintf(__stderrp,
                        "EV_DoDonut: WARNING: emulating buffer overrun due to "
                        "NULL back sector. "
                        "Unexpected behavior may occur in Vanilla Doom.\n");

                DonutOverrun(&s3_floorheight, &s3_floorpic, line, s1);
            }
            else
            {
                s3_floorheight = s3->floorheight;
                s3_floorpic = s3->floorpic;
            }


     floor = Z_Malloc (sizeof(*floor), PU_LEVSPEC, 0);
     P_AddThinker (&floor->thinker);
     s2->specialdata = floor;
     floor->thinker.function.acp1 = (actionf_p1) T_MoveFloor;
     floor->type = donutRaise;
     floor->crush = false;
     floor->direction = 1;
     floor->sector = s2;
     floor->speed = (1<<16) / 2;
     floor->texture = s3_floorpic;
     floor->newspecial = 0;
     floor->floordestheight = s3_floorheight;


     floor = Z_Malloc (sizeof(*floor), PU_LEVSPEC, 0);
     P_AddThinker (&floor->thinker);
     s1->specialdata = floor;
     floor->thinker.function.acp1 = (actionf_p1) T_MoveFloor;
     floor->type = lowerFloor;
     floor->crush = false;
     floor->direction = -1;
     floor->sector = s1;
     floor->speed = (1<<16) / 2;
     floor->floordestheight = s3_floorheight;
     break;
 }
    }
    return rtn;
}
short numlinespecials;
line_t* linespeciallist[64];



void P_SpawnSpecials (void)
{
    sector_t* sector;
    int i;



    if (timelimit > 0 && deathmatch)
    {
        levelTimer = true;
        levelTimeCount = timelimit * 60 * 35;
    }
    else
    {
 levelTimer = false;
    }


    sector = sectors;
    for (i=0 ; i<numsectors ; i++, sector++)
    {
 if (!sector->special)
     continue;

 switch (sector->special)
 {
   case 1:

     P_SpawnLightFlash (sector);
     break;

   case 2:

     P_SpawnStrobeFlash(sector,15,0);
     break;

   case 3:

     P_SpawnStrobeFlash(sector,35,0);
     break;

   case 4:

     P_SpawnStrobeFlash(sector,15,0);
     sector->special = 4;
     break;

   case 8:

     P_SpawnGlowingLight(sector);
     break;
   case 9:

     totalsecret++;
     break;

   case 10:

     P_SpawnDoorCloseIn30 (sector);
     break;

   case 12:

     P_SpawnStrobeFlash (sector, 35, 1);
     break;

   case 13:

     P_SpawnStrobeFlash (sector, 15, 1);
     break;

   case 14:

     P_SpawnDoorRaiseIn5Mins (sector, i);
     break;

   case 17:
     P_SpawnFireFlicker(sector);
     break;
 }
    }



    numlinespecials = 0;
    for (i = 0;i < numlines; i++)
    {
 switch(lines[i].special)
 {
   case 48:
            if (numlinespecials >= 64)
            {
                I_Error("Too many scrolling wall linedefs! "
                        "(Vanilla limit is 64)");
            }

     linespeciallist[numlinespecials] = &lines[i];
     numlinespecials++;
     break;
 }
    }



    for (i = 0;i < 30;i++)
 activeceilings[i] = ((void*)0);

    for (i = 0;i < 30;i++)
 activeplats[i] = ((void*)0);

    for (i = 0;i < 16;i++)
 memset(&buttonlist[i],0,sizeof(button_t));



}
switchlist_t alphSwitchList[] =
{

    {"SW1BRCOM", "SW2BRCOM", 1},
    {"SW1BRN1", "SW2BRN1", 1},
    {"SW1BRN2", "SW2BRN2", 1},
    {"SW1BRNGN", "SW2BRNGN", 1},
    {"SW1BROWN", "SW2BROWN", 1},
    {"SW1COMM", "SW2COMM", 1},
    {"SW1COMP", "SW2COMP", 1},
    {"SW1DIRT", "SW2DIRT", 1},
    {"SW1EXIT", "SW2EXIT", 1},
    {"SW1GRAY", "SW2GRAY", 1},
    {"SW1GRAY1", "SW2GRAY1", 1},
    {"SW1METAL", "SW2METAL", 1},
    {"SW1PIPE", "SW2PIPE", 1},
    {"SW1SLAD", "SW2SLAD", 1},
    {"SW1STARG", "SW2STARG", 1},
    {"SW1STON1", "SW2STON1", 1},
    {"SW1STON2", "SW2STON2", 1},
    {"SW1STONE", "SW2STONE", 1},
    {"SW1STRTN", "SW2STRTN", 1},


    {"SW1BLUE", "SW2BLUE", 2},
    {"SW1CMT", "SW2CMT", 2},
    {"SW1GARG", "SW2GARG", 2},
    {"SW1GSTON", "SW2GSTON", 2},
    {"SW1HOT", "SW2HOT", 2},
    {"SW1LION", "SW2LION", 2},
    {"SW1SATYR", "SW2SATYR", 2},
    {"SW1SKIN", "SW2SKIN", 2},
    {"SW1VINE", "SW2VINE", 2},
    {"SW1WOOD", "SW2WOOD", 2},


    {"SW1PANEL", "SW2PANEL", 3},
    {"SW1ROCK", "SW2ROCK", 3},
    {"SW1MET2", "SW2MET2", 3},
    {"SW1WDMET", "SW2WDMET", 3},
    {"SW1BRIK", "SW2BRIK", 3},
    {"SW1MOD1", "SW2MOD1", 3},
    {"SW1ZIM", "SW2ZIM", 3},
    {"SW1STON6", "SW2STON6", 3},
    {"SW1TEK", "SW2TEK", 3},
    {"SW1MARB", "SW2MARB", 3},
    {"SW1SKULL", "SW2SKULL", 3},

    {"\0", "\0", 0}
};

int switchlist[50 * 2];
int numswitches;
button_t buttonlist[16];





void P_InitSwitchList(void)
{
    int i;
    int index;
    int episode;

    episode = 1;

    if (gamemode == registered || gamemode == retail)
 episode = 2;
    else
 if ( gamemode == commercial )
     episode = 3;

    for (index = 0,i = 0;i < 50;i++)
    {
 if (!alphSwitchList[i].episode)
 {
     numswitches = index/2;
     switchlist[index] = -1;
     break;
 }

 if (alphSwitchList[i].episode <= episode)
 {
     switchlist[index++] = R_TextureNumForName((alphSwitchList[i].name1));
     switchlist[index++] = R_TextureNumForName((alphSwitchList[i].name2));
 }
    }
}





void
P_StartButton
( line_t* line,
  bwhere_e w,
  int texture,
  int time )
{
    int i;


    for (i = 0;i < 16;i++)
    {
 if (buttonlist[i].btimer
     && buttonlist[i].line == line)
 {

     return;
 }
    }



    for (i = 0;i < 16;i++)
    {
 if (!buttonlist[i].btimer)
 {
     buttonlist[i].line = line;
     buttonlist[i].where = w;
     buttonlist[i].btexture = texture;
     buttonlist[i].btimer = time;
     buttonlist[i].soundorg = &line->frontsector->soundorg;
     return;
 }
    }

    I_Error("P_StartButton: no button slots left!");
}
void
P_ChangeSwitchTexture
( line_t* line,
  int useAgain )
{
    int texTop;
    int texMid;
    int texBot;
    int i;
    int sound;

    if (!useAgain)
 line->special = 0;

    texTop = sides[line->sidenum[0]].toptexture;
    texMid = sides[line->sidenum[0]].midtexture;
    texBot = sides[line->sidenum[0]].bottomtexture;

    sound = sfx_swtchn;


    if (line->special == 11)
 sound = sfx_swtchx;

    for (i = 0;i < numswitches*2;i++)
    {
 if (switchlist[i] == texTop)
 {
     S_StartSound(buttonlist->soundorg,sound);
     sides[line->sidenum[0]].toptexture = switchlist[i^1];

     if (useAgain)
  P_StartButton(line,top,switchlist[i],35);

     return;
 }
 else
 {
     if (switchlist[i] == texMid)
     {
  S_StartSound(buttonlist->soundorg,sound);
  sides[line->sidenum[0]].midtexture = switchlist[i^1];

  if (useAgain)
      P_StartButton(line, middle,switchlist[i],35);

  return;
     }
     else
     {
  if (switchlist[i] == texBot)
  {
      S_StartSound(buttonlist->soundorg,sound);
      sides[line->sidenum[0]].bottomtexture = switchlist[i^1];

      if (useAgain)
   P_StartButton(line, bottom,switchlist[i],35);

      return;
  }
     }
 }
    }
}
boolean
P_UseSpecialLine
( mobj_t* thing,
  line_t* line,
  int side )
{



    if (side)
    {
 switch(line->special)
 {
   case 124:


     break;

   default:
     return false;
     break;
 }
    }



    if (!thing->player)
    {

 if (line->flags & 32)
     return false;

 switch(line->special)
 {
   case 1:
   case 32:
   case 33:
   case 34:
     break;

   default:
     return false;
     break;
 }
    }



    switch (line->special)
    {

      case 1:
      case 26:
      case 27:
      case 28:

      case 31:
      case 32:
      case 33:
      case 34:

      case 117:
      case 118:
 EV_VerticalDoor (line, thing);
 break;







      case 7:

 if (EV_BuildStairs(line,build8))
     P_ChangeSwitchTexture(line,0);
 break;

      case 9:

 if (EV_DoDonut(line))
     P_ChangeSwitchTexture(line,0);
 break;

      case 11:

 P_ChangeSwitchTexture(line,0);
 G_ExitLevel ();
 break;

      case 14:

 if (EV_DoPlat(line,raiseAndChange,32))
     P_ChangeSwitchTexture(line,0);
 break;

      case 15:

 if (EV_DoPlat(line,raiseAndChange,24))
     P_ChangeSwitchTexture(line,0);
 break;

      case 18:

 if (EV_DoFloor(line, raiseFloorToNearest))
     P_ChangeSwitchTexture(line,0);
 break;

      case 20:

 if (EV_DoPlat(line,raiseToNearestAndChange,0))
     P_ChangeSwitchTexture(line,0);
 break;

      case 21:

 if (EV_DoPlat(line,downWaitUpStay,0))
     P_ChangeSwitchTexture(line,0);
 break;

      case 23:

 if (EV_DoFloor(line,lowerFloorToLowest))
     P_ChangeSwitchTexture(line,0);
 break;

      case 29:

 if (EV_DoDoor(line,vld_normal))
     P_ChangeSwitchTexture(line,0);
 break;

      case 41:

 if (EV_DoCeiling(line,lowerToFloor))
     P_ChangeSwitchTexture(line,0);
 break;

      case 71:

 if (EV_DoFloor(line,turboLower))
     P_ChangeSwitchTexture(line,0);
 break;

      case 49:

 if (EV_DoCeiling(line,crushAndRaise))
     P_ChangeSwitchTexture(line,0);
 break;

      case 50:

 if (EV_DoDoor(line,vld_close))
     P_ChangeSwitchTexture(line,0);
 break;

      case 51:

 P_ChangeSwitchTexture(line,0);
 G_SecretExitLevel ();
 break;

      case 55:

 if (EV_DoFloor(line,raiseFloorCrush))
     P_ChangeSwitchTexture(line,0);
 break;

      case 101:

 if (EV_DoFloor(line,raiseFloor))
     P_ChangeSwitchTexture(line,0);
 break;

      case 102:

 if (EV_DoFloor(line,lowerFloor))
     P_ChangeSwitchTexture(line,0);
 break;

      case 103:

 if (EV_DoDoor(line,vld_open))
     P_ChangeSwitchTexture(line,0);
 break;

      case 111:

 if (EV_DoDoor (line,vld_blazeRaise))
     P_ChangeSwitchTexture(line,0);
 break;

      case 112:

 if (EV_DoDoor (line,vld_blazeOpen))
     P_ChangeSwitchTexture(line,0);
 break;

      case 113:

 if (EV_DoDoor (line,vld_blazeClose))
     P_ChangeSwitchTexture(line,0);
 break;

      case 122:

 if (EV_DoPlat(line,blazeDWUS,0))
     P_ChangeSwitchTexture(line,0);
 break;

      case 127:

 if (EV_BuildStairs(line,turbo16))
     P_ChangeSwitchTexture(line,0);
 break;

      case 131:

 if (EV_DoFloor(line,raiseFloorTurbo))
     P_ChangeSwitchTexture(line,0);
 break;

      case 133:

      case 135:

      case 137:

 if (EV_DoLockedDoor (line,vld_blazeOpen,thing))
     P_ChangeSwitchTexture(line,0);
 break;

      case 140:

 if (EV_DoFloor(line,raiseFloor512))
     P_ChangeSwitchTexture(line,0);
 break;


      case 42:

 if (EV_DoDoor(line,vld_close))
     P_ChangeSwitchTexture(line,1);
 break;

      case 43:

 if (EV_DoCeiling(line,lowerToFloor))
     P_ChangeSwitchTexture(line,1);
 break;

      case 45:

 if (EV_DoFloor(line,lowerFloor))
     P_ChangeSwitchTexture(line,1);
 break;

      case 60:

 if (EV_DoFloor(line,lowerFloorToLowest))
     P_ChangeSwitchTexture(line,1);
 break;

      case 61:

 if (EV_DoDoor(line,vld_open))
     P_ChangeSwitchTexture(line,1);
 break;

      case 62:

 if (EV_DoPlat(line,downWaitUpStay,1))
     P_ChangeSwitchTexture(line,1);
 break;

      case 63:

 if (EV_DoDoor(line,vld_normal))
     P_ChangeSwitchTexture(line,1);
 break;

      case 64:

 if (EV_DoFloor(line,raiseFloor))
     P_ChangeSwitchTexture(line,1);
 break;

      case 66:

 if (EV_DoPlat(line,raiseAndChange,24))
     P_ChangeSwitchTexture(line,1);
 break;

      case 67:

 if (EV_DoPlat(line,raiseAndChange,32))
     P_ChangeSwitchTexture(line,1);
 break;

      case 65:

 if (EV_DoFloor(line,raiseFloorCrush))
     P_ChangeSwitchTexture(line,1);
 break;

      case 68:

 if (EV_DoPlat(line,raiseToNearestAndChange,0))
     P_ChangeSwitchTexture(line,1);
 break;

      case 69:

 if (EV_DoFloor(line, raiseFloorToNearest))
     P_ChangeSwitchTexture(line,1);
 break;

      case 70:

 if (EV_DoFloor(line,turboLower))
     P_ChangeSwitchTexture(line,1);
 break;

      case 114:

 if (EV_DoDoor (line,vld_blazeRaise))
     P_ChangeSwitchTexture(line,1);
 break;

      case 115:

 if (EV_DoDoor (line,vld_blazeOpen))
     P_ChangeSwitchTexture(line,1);
 break;

      case 116:

 if (EV_DoDoor (line,vld_blazeClose))
     P_ChangeSwitchTexture(line,1);
 break;

      case 123:

 if (EV_DoPlat(line,blazeDWUS,0))
     P_ChangeSwitchTexture(line,1);
 break;

      case 132:

 if (EV_DoFloor(line,raiseFloorTurbo))
     P_ChangeSwitchTexture(line,1);
 break;

      case 99:

      case 134:

      case 136:

 if (EV_DoLockedDoor (line,vld_blazeOpen,thing))
     P_ChangeSwitchTexture(line,1);
 break;

      case 138:

 EV_LightTurnOn(line,255);
 P_ChangeSwitchTexture(line,1);
 break;

      case 139:

 EV_LightTurnOn(line,35);
 P_ChangeSwitchTexture(line,1);
 break;

    }

    return true;
}
int
EV_Teleport
( line_t* line,
  int side,
  mobj_t* thing )
{
    int i;
    int tag;
    mobj_t* m;
    mobj_t* fog;
    unsigned an;
    thinker_t* thinker;
    sector_t* sector;
    fixed_t oldx;
    fixed_t oldy;
    fixed_t oldz;


    if (thing->flags & MF_MISSILE)
 return 0;



    if (side == 1)
 return 0;


    tag = line->tag;
    for (i = 0; i < numsectors; i++)
    {
 if (sectors[ i ].tag == tag )
 {
     thinker = thinkercap.next;
     for (thinker = thinkercap.next;
   thinker != &thinkercap;
   thinker = thinker->next)
     {

  if (thinker->function.acp1 != (actionf_p1)P_MobjThinker)
      continue;

  m = (mobj_t *)thinker;


  if (m->type != MT_TELEPORTMAN )
      continue;

  sector = m->subsector->sector;

  if (sector-sectors != i )
      continue;

  oldx = thing->x;
  oldy = thing->y;
  oldz = thing->z;

  if (!P_TeleportMove (thing, m->x, m->y))
      return 0;






                if (gameversion != exe_final)
      thing->z = thing->floorz;

  if (thing->player)
      thing->player->viewz = thing->z+thing->player->viewheight;


  fog = P_SpawnMobj (oldx, oldy, oldz, MT_TFOG);
  S_StartSound (fog, sfx_telept);
  an = m->angle >> 19;
  fog = P_SpawnMobj (m->x+20*finecosine[an], m->y+20*finesine[an]
       , thing->z, MT_TFOG);


  S_StartSound (fog, sfx_telept);


  if (thing->player)
      thing->reactiontime = 18;

  thing->angle = m->angle;
  thing->momx = thing->momy = thing->momz = 0;
  return 1;
     }
 }
    }
    return 0;
}
int leveltime;
thinker_t thinkercap;





void P_InitThinkers (void)
{
    thinkercap.prev = thinkercap.next = &thinkercap;
}
void P_AddThinker (thinker_t* thinker)
{
    thinkercap.prev->next = thinker;
    thinker->next = &thinkercap;
    thinker->prev = thinkercap.prev;
    thinkercap.prev = thinker;
}
void P_RemoveThinker (thinker_t* thinker)
{

  thinker->function.acv = (actionf_v)(-1);
}







void P_AllocateThinker (thinker_t* thinker)
{
}






void P_RunThinkers (void)
{
    thinker_t* currentthinker;

    currentthinker = thinkercap.next;
    while (currentthinker != &thinkercap)
    {
 if ( currentthinker->function.acv == (actionf_v)(-1) )
 {

     currentthinker->next->prev = currentthinker->prev;
     currentthinker->prev->next = currentthinker->next;
     Z_Free (currentthinker);
 }
 else
 {
     if (currentthinker->function.acp1)
  currentthinker->function.acp1 (currentthinker);
 }
 currentthinker = currentthinker->next;
    }
}







void P_Ticker (void)
{
    int i;


    if (paused)
 return;


    if ( !netgame
  && menuactive
  && !demoplayback
  && players[consoleplayer].viewz != 1)
    {
 return;
    }


    for (i=0 ; i<4 ; i++)
 if (playeringame[i])
     P_PlayerThink (&players[i]);

    P_RunThinkers ();
    P_UpdateSpecials ();
    P_RespawnSpecials ();


    leveltime++;
}
boolean onground;






void
P_Thrust
( player_t* player,
  angle_t angle,
  fixed_t move )
{
    angle >>= 19;

    player->mo->momx += FixedMul(move,finecosine[angle]);
    player->mo->momy += FixedMul(move,finesine[angle]);
}
void P_CalcHeight (player_t* player)
{
    int angle;
    fixed_t bob;







    player->bob =
 FixedMul (player->mo->momx, player->mo->momx)
 + FixedMul (player->mo->momy,player->mo->momy);

    player->bob >>= 2;

    if (player->bob>0x100000)
 player->bob = 0x100000;

    if ((player->cheats & CF_NOMOMENTUM) || !onground)
    {
 player->viewz = player->mo->z + (41*(1<<16));

 if (player->viewz > player->mo->ceilingz-4*(1<<16))
     player->viewz = player->mo->ceilingz-4*(1<<16);

 player->viewz = player->mo->z + player->viewheight;
 return;
    }

    angle = (8192/20*leveltime)&(8192 -1);
    bob = FixedMul ( player->bob/2, finesine[angle]);



    if (player->playerstate == PST_LIVE)
    {
 player->viewheight += player->deltaviewheight;

 if (player->viewheight > (41*(1<<16)))
 {
     player->viewheight = (41*(1<<16));
     player->deltaviewheight = 0;
 }

 if (player->viewheight < (41*(1<<16))/2)
 {
     player->viewheight = (41*(1<<16))/2;
     if (player->deltaviewheight <= 0)
  player->deltaviewheight = 1;
 }

 if (player->deltaviewheight)
 {
     player->deltaviewheight += (1<<16)/4;
     if (!player->deltaviewheight)
  player->deltaviewheight = 1;
 }
    }
    player->viewz = player->mo->z + player->viewheight + bob;

    if (player->viewz > player->mo->ceilingz-4*(1<<16))
 player->viewz = player->mo->ceilingz-4*(1<<16);
}






void P_MovePlayer (player_t* player)
{
    ticcmd_t* cmd;

    cmd = &player->cmd;

    player->mo->angle += (cmd->angleturn<<16);



    onground = (player->mo->z <= player->mo->floorz);

    if (cmd->forwardmove && onground)
 P_Thrust (player, player->mo->angle, cmd->forwardmove*2048);

    if (cmd->sidemove && onground)
 P_Thrust (player, player->mo->angle-0x40000000, cmd->sidemove*2048);

    if ( (cmd->forwardmove || cmd->sidemove)
  && player->mo->state == &states[S_PLAY] )
    {
 P_SetMobjState (player->mo, S_PLAY_RUN1);
    }
}
void P_DeathThink (player_t* player)
{
    angle_t angle;
    angle_t delta;

    P_MovePsprites (player);


    if (player->viewheight > 6*(1<<16))
 player->viewheight -= (1<<16);

    if (player->viewheight < 6*(1<<16))
 player->viewheight = 6*(1<<16);

    player->deltaviewheight = 0;
    onground = (player->mo->z <= player->mo->floorz);
    P_CalcHeight (player);

    if (player->attacker && player->attacker != player->mo)
    {
 angle = R_PointToAngle2 (player->mo->x,
     player->mo->y,
     player->attacker->x,
     player->attacker->y);

 delta = angle - player->mo->angle;

 if (delta < (0x40000000/18) || delta > (unsigned)-(0x40000000/18))
 {


     player->mo->angle = angle;

     if (player->damagecount)
  player->damagecount--;
 }
 else if (delta < 0x80000000)
     player->mo->angle += (0x40000000/18);
 else
     player->mo->angle -= (0x40000000/18);
    }
    else if (player->damagecount)
 player->damagecount--;


    if (player->cmd.buttons & BT_USE)
 player->playerstate = PST_REBORN;
}






void P_PlayerThink (player_t* player)
{
    ticcmd_t* cmd;
    weapontype_t newweapon;


    if (player->cheats & CF_NOCLIP)
 player->mo->flags |= MF_NOCLIP;
    else
 player->mo->flags &= ~MF_NOCLIP;


    cmd = &player->cmd;
    if (player->mo->flags & MF_JUSTATTACKED)
    {
 cmd->angleturn = 0;
 cmd->forwardmove = 0xc800/512;
 cmd->sidemove = 0;
 player->mo->flags &= ~MF_JUSTATTACKED;
    }


    if (player->playerstate == PST_DEAD)
    {
 P_DeathThink (player);
 return;
    }




    if (player->mo->reactiontime)
 player->mo->reactiontime--;
    else
 P_MovePlayer (player);

    P_CalcHeight (player);

    if (player->mo->subsector->sector->special)
 P_PlayerInSpecialSector (player);




    if (cmd->buttons & BT_SPECIAL)
 cmd->buttons = 0;

    if (cmd->buttons & BT_CHANGE)
    {



 newweapon = (cmd->buttons&BT_WEAPONMASK)>>BT_WEAPONSHIFT;

 if (newweapon == wp_fist
     && player->weaponowned[wp_chainsaw]
     && !(player->readyweapon == wp_chainsaw
   && player->powers[pw_strength]))
 {
     newweapon = wp_chainsaw;
 }

 if ( (gamemode == commercial)
     && newweapon == wp_shotgun
     && player->weaponowned[wp_supershotgun]
     && player->readyweapon != wp_supershotgun)
 {
     newweapon = wp_supershotgun;
 }


 if (player->weaponowned[newweapon]
     && newweapon != player->readyweapon)
 {


     if ((newweapon != wp_plasma
   && newweapon != wp_bfg)
  || (gamemode != shareware) )
     {
  player->pendingweapon = newweapon;
     }
 }
    }


    if (cmd->buttons & BT_USE)
    {
 if (!player->usedown)
 {
     P_UseLines (player);
     player->usedown = true;
 }
    }
    else
 player->usedown = false;


    P_MovePsprites (player);




    if (player->powers[pw_strength])
 player->powers[pw_strength]++;

    if (player->powers[pw_invulnerability])
 player->powers[pw_invulnerability]--;

    if (player->powers[pw_invisibility])
 if (! --player->powers[pw_invisibility] )
     player->mo->flags &= ~MF_SHADOW;

    if (player->powers[pw_infrared])
 player->powers[pw_infrared]--;

    if (player->powers[pw_ironfeet])
 player->powers[pw_ironfeet]--;

    if (player->damagecount)
 player->damagecount--;

    if (player->bonuscount)
 player->bonuscount--;



    if (player->powers[pw_invulnerability])
    {
 if (player->powers[pw_invulnerability] > 4*32
     || (player->powers[pw_invulnerability]&8) )
     player->fixedcolormap = 32;
 else
     player->fixedcolormap = 0;
    }
    else if (player->powers[pw_infrared])
    {
 if (player->powers[pw_infrared] > 4*32
     || (player->powers[pw_infrared]&8) )
 {

     player->fixedcolormap = 1;
 }
 else
     player->fixedcolormap = 0;
    }
    else
 player->fixedcolormap = 0;
}
seg_t* curline;
side_t* sidedef;
line_t* linedef;
sector_t* frontsector;
sector_t* backsector;

drawseg_t drawsegs[256];
drawseg_t* ds_p;


void
R_StoreWallRange
( int start,
  int stop );







void R_ClearDrawSegs (void)
{
    ds_p = drawsegs;
}
typedef struct
{
    int first;
    int last;

} cliprange_t;





cliprange_t* newend;
cliprange_t solidsegs[32];
void
R_ClipSolidWallSegment
( int first,
  int last )
{
    cliprange_t* next;
    cliprange_t* start;



    start = solidsegs;
    while (start->last < first-1)
 start++;

    if (first < start->first)
    {
 if (last < start->first-1)
 {


     R_StoreWallRange (first, last);
     next = newend;
     newend++;

     while (next != start)
     {
  *next = *(next-1);
  next--;
     }
     next->first = first;
     next->last = last;
     return;
 }


 R_StoreWallRange (first, start->first - 1);

 start->first = first;
    }


    if (last <= start->last)
 return;

    next = start;
    while (last >= (next+1)->first-1)
    {

 R_StoreWallRange (next->last + 1, (next+1)->first - 1);
 next++;

 if (last <= next->last)
 {


     start->last = next->last;
     goto crunch;
 }
    }


    R_StoreWallRange (next->last + 1, last);

    start->last = last;



  crunch:
    if (next == start)
    {

 return;
    }


    while (next++ != newend)
    {

 *++start = *next;
    }

    newend = start+1;
}
void
R_ClipPassWallSegment
( int first,
  int last )
{
    cliprange_t* start;



    start = solidsegs;
    while (start->last < first-1)
 start++;

    if (first < start->first)
    {
 if (last < start->first-1)
 {

     R_StoreWallRange (first, last);
     return;
 }


 R_StoreWallRange (first, start->first - 1);
    }


    if (last <= start->last)
 return;

    while (last >= (start+1)->first-1)
    {

 R_StoreWallRange (start->last + 1, (start+1)->first - 1);
 start++;

 if (last <= start->last)
     return;
    }


    R_StoreWallRange (start->last + 1, last);
}






void R_ClearClipSegs (void)
{
    solidsegs[0].first = -0x7fffffff;
    solidsegs[0].last = -1;
    solidsegs[1].first = viewwidth;
    solidsegs[1].last = 0x7fffffff;
    newend = solidsegs+2;
}






void R_AddLine (seg_t* line)
{
    int x1;
    int x2;
    angle_t angle1;
    angle_t angle2;
    angle_t span;
    angle_t tspan;

    curline = line;


    angle1 = R_PointToAngle (line->v1->x, line->v1->y);
    angle2 = R_PointToAngle (line->v2->x, line->v2->y);



    span = angle1 - angle2;


    if (span >= 0x80000000)
 return;


    rw_angle1 = angle1;
    angle1 -= viewangle;
    angle2 -= viewangle;

    tspan = angle1 + clipangle;
    if (tspan > 2*clipangle)
    {
 tspan -= 2*clipangle;


 if (tspan >= span)
     return;

 angle1 = clipangle;
    }
    tspan = clipangle - angle2;
    if (tspan > 2*clipangle)
    {
 tspan -= 2*clipangle;


 if (tspan >= span)
     return;
 angle2 = -clipangle;
    }



    angle1 = (angle1+0x40000000)>>19;
    angle2 = (angle2+0x40000000)>>19;
    x1 = viewangletox[angle1];
    x2 = viewangletox[angle2];


    if (x1 == x2)
 return;

    backsector = line->backsector;


    if (!backsector)
 goto clipsolid;


    if (backsector->ceilingheight <= frontsector->floorheight
 || backsector->floorheight >= frontsector->ceilingheight)
 goto clipsolid;


    if (backsector->ceilingheight != frontsector->ceilingheight
 || backsector->floorheight != frontsector->floorheight)
 goto clippass;






    if (backsector->ceilingpic == frontsector->ceilingpic
 && backsector->floorpic == frontsector->floorpic
 && backsector->lightlevel == frontsector->lightlevel
 && curline->sidedef->midtexture == 0)
    {
 return;
    }


  clippass:
    R_ClipPassWallSegment (x1, x2-1);
    return;

  clipsolid:
    R_ClipSolidWallSegment (x1, x2-1);
}
int checkcoord[12][4] =
{
    {3,0,2,1},
    {3,0,2,0},
    {3,1,2,0},
    {0},
    {2,0,2,1},
    {0,0,0,0},
    {3,1,3,0},
    {0},
    {2,0,3,1},
    {2,1,3,1},
    {2,1,3,0}
};


boolean R_CheckBBox (fixed_t* bspcoord)
{
    int boxx;
    int boxy;
    int boxpos;

    fixed_t x1;
    fixed_t y1;
    fixed_t x2;
    fixed_t y2;

    angle_t angle1;
    angle_t angle2;
    angle_t span;
    angle_t tspan;

    cliprange_t* start;

    int sx1;
    int sx2;



    if (viewx <= bspcoord[BOXLEFT])
 boxx = 0;
    else if (viewx < bspcoord[BOXRIGHT])
 boxx = 1;
    else
 boxx = 2;

    if (viewy >= bspcoord[BOXTOP])
 boxy = 0;
    else if (viewy > bspcoord[BOXBOTTOM])
 boxy = 1;
    else
 boxy = 2;

    boxpos = (boxy<<2)+boxx;
    if (boxpos == 5)
 return true;

    x1 = bspcoord[checkcoord[boxpos][0]];
    y1 = bspcoord[checkcoord[boxpos][1]];
    x2 = bspcoord[checkcoord[boxpos][2]];
    y2 = bspcoord[checkcoord[boxpos][3]];


    angle1 = R_PointToAngle (x1, y1) - viewangle;
    angle2 = R_PointToAngle (x2, y2) - viewangle;

    span = angle1 - angle2;


    if (span >= 0x80000000)
 return true;

    tspan = angle1 + clipangle;

    if (tspan > 2*clipangle)
    {
 tspan -= 2*clipangle;


 if (tspan >= span)
     return false;

 angle1 = clipangle;
    }
    tspan = clipangle - angle2;
    if (tspan > 2*clipangle)
    {
 tspan -= 2*clipangle;


 if (tspan >= span)
     return false;

 angle2 = -clipangle;
    }





    angle1 = (angle1+0x40000000)>>19;
    angle2 = (angle2+0x40000000)>>19;
    sx1 = viewangletox[angle1];
    sx2 = viewangletox[angle2];


    if (sx1 == sx2)
 return false;
    sx2--;

    start = solidsegs;
    while (start->last < sx2)
 start++;

    if (sx1 >= start->first
 && sx2 <= start->last)
    {

 return false;
    }

    return true;
}
void R_Subsector (int num)
{
    int count;
    seg_t* line;
    subsector_t* sub;


    if (num>=numsubsectors)
 I_Error ("R_Subsector: ss %i with numss = %i",
   num,
   numsubsectors);


    sscount++;
    sub = &subsectors[num];
    frontsector = sub->sector;
    count = sub->numlines;
    line = &segs[sub->firstline];

    if (frontsector->floorheight < viewz)
    {
 floorplane = R_FindPlane (frontsector->floorheight,
      frontsector->floorpic,
      frontsector->lightlevel);
    }
    else
 floorplane = ((void*)0);

    if (frontsector->ceilingheight > viewz
 || frontsector->ceilingpic == skyflatnum)
    {
 ceilingplane = R_FindPlane (frontsector->ceilingheight,
        frontsector->ceilingpic,
        frontsector->lightlevel);
    }
    else
 ceilingplane = ((void*)0);

    R_AddSprites (frontsector);

    while (count--)
    {
 R_AddLine (line);
 line++;
    }
}
void R_RenderBSPNode (int bspnum)
{
    node_t* bsp;
    int side;


    if (bspnum & 0x8000)
    {
 if (bspnum == -1)
     R_Subsector (0);
 else
     R_Subsector (bspnum&(~0x8000));
 return;
    }

    bsp = &nodes[bspnum];


    side = R_PointOnSide (viewx, viewy, bsp);


    R_RenderBSPNode (bsp->children[side]);


    if (R_CheckBBox (bsp->bbox[side^1]))
 R_RenderBSPNode (bsp->children[side^1]);
}
typedef struct
{
    short originx;
    short originy;
    short patch;
    short stepdir;
    short colormap;
} __attribute__((packed)) mappatch_t;







typedef struct
{
    char name[8];
    int masked;
    short width;
    short height;
    int obsolete;
    short patchcount;
    mappatch_t patches[1];
} __attribute__((packed)) maptexture_t;





typedef struct
{



    short originx;
    short originy;
    int patch;
} texpatch_t;






typedef struct texture_s texture_t;

struct texture_s
{

    char name[8];
    short width;
    short height;



    int index;



    texture_t *next;



    short patchcount;
    texpatch_t patches[1];
};



int firstflat;
int lastflat;
int numflats;

int firstpatch;
int lastpatch;
int numpatches;

int firstspritelump;
int lastspritelump;
int numspritelumps;

int numtextures;
texture_t** textures;
texture_t** textures_hashtable;


int* texturewidthmask;

fixed_t* textureheight;
int* texturecompositesize;
short** texturecolumnlump;
unsigned short** texturecolumnofs;
byte** texturecomposite;


int* flattranslation;
int* texturetranslation;


fixed_t* spritewidth;
fixed_t* spriteoffset;
fixed_t* spritetopoffset;

lighttable_t *colormaps;
void
R_DrawColumnInCache
( column_t* patch,
  byte* cache,
  int originy,
  int cacheheight )
{
    int count;
    int position;
    byte* source;

    while (patch->topdelta != 0xff)
    {
 source = (byte *)patch + 3;
 count = patch->length;
 position = originy + patch->topdelta;

 if (position < 0)
 {
     count += position;
     position = 0;
 }

 if (position + count > cacheheight)
     count = cacheheight - position;

 if (count > 0)
     memcpy (cache + position, source, count);

 patch = (column_t *)( (byte *)patch + patch->length + 4);
    }
}
void R_GenerateComposite (int texnum)
{
    byte* block;
    texture_t* texture;
    texpatch_t* patch;
    patch_t* realpatch;
    int x;
    int x1;
    int x2;
    int i;
    column_t* patchcol;
    short* collump;
    unsigned short* colofs;

    texture = textures[texnum];

    block = Z_Malloc (texturecompositesize[texnum],
        PU_STATIC,
        &texturecomposite[texnum]);

    collump = texturecolumnlump[texnum];
    colofs = texturecolumnofs[texnum];


    patch = texture->patches;

    for (i=0 , patch = texture->patches;
  i<texture->patchcount;
  i++, patch++)
    {
 realpatch = W_CacheLumpNum (patch->patch, PU_CACHE);
 x1 = patch->originx;
 x2 = x1 + ((signed short) (realpatch->width));

 if (x1<0)
     x = 0;
 else
     x = x1;

 if (x2 > texture->width)
     x2 = texture->width;

 for ( ; x<x2 ; x++)
 {

     if (collump[x] >= 0)
  continue;

     patchcol = (column_t *)((byte *)realpatch
        + ((signed int) (realpatch->columnofs[x-x1])));
     R_DrawColumnInCache (patchcol,
     block + colofs[x],
     patch->originy,
     texture->height);
 }

    }



    Z_ChangeTag2((block), (PU_CACHE), "../doomgeneric/r_data.c", 286);
}






void R_GenerateLookup (int texnum)
{
    texture_t* texture;
    byte* patchcount;
    texpatch_t* patch;
    patch_t* realpatch;
    int x;
    int x1;
    int x2;
    int i;
    short* collump;
    unsigned short* colofs;

    texture = textures[texnum];


    texturecomposite[texnum] = 0;

    texturecompositesize[texnum] = 0;
    collump = texturecolumnlump[texnum];
    colofs = texturecolumnofs[texnum];





    patchcount = (byte *) Z_Malloc(texture->width, PU_STATIC, &patchcount);
    memset (patchcount, 0, texture->width);
    patch = texture->patches;

    for (i=0 , patch = texture->patches;
  i<texture->patchcount;
  i++, patch++)
    {
 realpatch = W_CacheLumpNum (patch->patch, PU_CACHE);
 x1 = patch->originx;
 x2 = x1 + ((signed short) (realpatch->width));

 if (x1 < 0)
     x = 0;
 else
     x = x1;

 if (x2 > texture->width)
     x2 = texture->width;
 for ( ; x<x2 ; x++)
 {
     patchcount[x]++;
     collump[x] = patch->patch;
     colofs[x] = ((signed int) (realpatch->columnofs[x-x1]))+3;
 }
    }

    for (x=0 ; x<texture->width ; x++)
    {
 if (!patchcount[x])
 {
     printf ("R_GenerateLookup: column without a patch (%s)\n",
      texture->name);
     return;
 }


 if (patchcount[x] > 1)
 {

     collump[x] = -1;
     colofs[x] = texturecompositesize[texnum];

     if (texturecompositesize[texnum] > 0x10000-texture->height)
     {
  I_Error ("R_GenerateLookup: texture %i is >64k",
    texnum);
     }

     texturecompositesize[texnum] += texture->height;
 }
    }

    Z_Free(patchcount);
}







byte*
R_GetColumn
( int tex,
  int col )
{
    int lump;
    int ofs;

    col &= texturewidthmask[tex];
    lump = texturecolumnlump[tex][col];
    ofs = texturecolumnofs[tex][col];

    if (lump > 0)
 return (byte *)W_CacheLumpNum(lump,PU_CACHE)+ofs;

    if (!texturecomposite[tex])
 R_GenerateComposite (tex);

    return texturecomposite[tex] + ofs;
}


static void GenerateTextureHashTable(void)
{
    texture_t **rover;
    int i;
    int key;

    textures_hashtable
            = Z_Malloc(sizeof(texture_t *) * numtextures, PU_STATIC, 0);

    memset(textures_hashtable, 0, sizeof(texture_t *) * numtextures);



    for (i=0; i<numtextures; ++i)
    {


        textures[i]->index = i;







        key = W_LumpNameHash(textures[i]->name) % numtextures;

        rover = &textures_hashtable[key];

        while (*rover != ((void*)0))
        {
            rover = &(*rover)->next;
        }



        textures[i]->next = ((void*)0);
        *rover = textures[i];
    }
}







void R_InitTextures (void)
{
    maptexture_t* mtexture;
    texture_t* texture;
    mappatch_t* mpatch;
    texpatch_t* patch;

    int i;
    int j;

    int* maptex;
    int* maptex2;
    int* maptex1;

    char name[9];
    char* names;
    char* name_p;

    int* patchlookup;

    int totalwidth;
    int nummappatches;
    int offset;
    int maxoff;
    int maxoff2;
    int numtextures1;
    int numtextures2;

    int* directory;

    int temp1;
    int temp2;
    int temp3;



    name[8] = 0;
    names = W_CacheLumpName (("PNAMES"), PU_STATIC);
    nummappatches = ((signed int) (*((int *)names)));
    name_p = names + 4;
    patchlookup = Z_Malloc(nummappatches*sizeof(*patchlookup), PU_STATIC, ((void*)0));

    for (i = 0; i < nummappatches; i++)
    {
        M_StringCopy(name, name_p + i * 8, sizeof(name));
        patchlookup[i] = W_CheckNumForName(name);
    }
    W_ReleaseLumpName(("PNAMES"));




    maptex = maptex1 = W_CacheLumpName (("TEXTURE1"), PU_STATIC);
    numtextures1 = ((signed int) (*maptex));
    maxoff = W_LumpLength (W_GetNumForName (("TEXTURE1")));
    directory = maptex+1;

    if (W_CheckNumForName (("TEXTURE2")) != -1)
    {
 maptex2 = W_CacheLumpName (("TEXTURE2"), PU_STATIC);
 numtextures2 = ((signed int) (*maptex2));
 maxoff2 = W_LumpLength (W_GetNumForName (("TEXTURE2")));
    }
    else
    {
 maptex2 = ((void*)0);
 numtextures2 = 0;
 maxoff2 = 0;
    }
    numtextures = numtextures1 + numtextures2;

    textures = Z_Malloc (numtextures * sizeof(*textures), PU_STATIC, 0);
    texturecolumnlump = Z_Malloc (numtextures * sizeof(*texturecolumnlump), PU_STATIC, 0);
    texturecolumnofs = Z_Malloc (numtextures * sizeof(*texturecolumnofs), PU_STATIC, 0);
    texturecomposite = Z_Malloc (numtextures * sizeof(*texturecomposite), PU_STATIC, 0);
    texturecompositesize = Z_Malloc (numtextures * sizeof(*texturecompositesize), PU_STATIC, 0);
    texturewidthmask = Z_Malloc (numtextures * sizeof(*texturewidthmask), PU_STATIC, 0);
    textureheight = Z_Malloc (numtextures * sizeof(*textureheight), PU_STATIC, 0);

    totalwidth = 0;


    temp1 = W_GetNumForName (("S_START"));
    temp2 = W_GetNumForName (("S_END")) - 1;
    temp3 = ((temp2-temp1+63)/64) + ((numtextures+63)/64);





    if (I_ConsoleStdout())
    {
        printf("[");
        for (i = 0; i < temp3 + 9; i++)
            printf(" ");
        printf("]");
        for (i = 0; i < temp3 + 10; i++)
            printf("\b");
    }

    for (i=0 ; i<numtextures ; i++, directory++)
    {
 if (!(i&63))
     printf (".");

 if (i == numtextures1)
 {

     maptex = maptex2;
     maxoff = maxoff2;
     directory = maptex+1;
 }

 offset = ((signed int) (*directory));

 if (offset > maxoff)
     I_Error ("R_InitTextures: bad texture directory");

 mtexture = (maptexture_t *) ( (byte *)maptex + offset);

 texture = textures[i] =
     Z_Malloc (sizeof(texture_t)
        + sizeof(texpatch_t)*(((signed short) (mtexture->patchcount))-1),
        PU_STATIC, 0);

 texture->width = ((signed short) (mtexture->width));
 texture->height = ((signed short) (mtexture->height));
 texture->patchcount = ((signed short) (mtexture->patchcount));

 memcpy (texture->name, mtexture->name, sizeof(texture->name));
 mpatch = &mtexture->patches[0];
 patch = &texture->patches[0];

 for (j=0 ; j<texture->patchcount ; j++, mpatch++, patch++)
 {
     patch->originx = ((signed short) (mpatch->originx));
     patch->originy = ((signed short) (mpatch->originy));
     patch->patch = patchlookup[((signed short) (mpatch->patch))];
     if (patch->patch == -1)
     {
  I_Error ("R_InitTextures: Missing patch in texture %s",
    texture->name);
     }
 }
 texturecolumnlump[i] = Z_Malloc (texture->width*sizeof(**texturecolumnlump), PU_STATIC,0);
 texturecolumnofs[i] = Z_Malloc (texture->width*sizeof(**texturecolumnofs), PU_STATIC,0);

 j = 1;
 while (j*2 <= texture->width)
     j<<=1;

 texturewidthmask[i] = j-1;
 textureheight[i] = texture->height<<16;

 totalwidth += texture->width;
    }

    Z_Free(patchlookup);

    W_ReleaseLumpName(("TEXTURE1"));
    if (maptex2)
        W_ReleaseLumpName(("TEXTURE2"));



    for (i=0 ; i<numtextures ; i++)
 R_GenerateLookup (i);


    texturetranslation = Z_Malloc ((numtextures+1)*sizeof(*texturetranslation), PU_STATIC, 0);

    for (i=0 ; i<numtextures ; i++)
 texturetranslation[i] = i;

    GenerateTextureHashTable();
}






void R_InitFlats (void)
{
    int i;

    firstflat = W_GetNumForName (("F_START")) + 1;
    lastflat = W_GetNumForName (("F_END")) - 1;
    numflats = lastflat - firstflat + 1;


    flattranslation = Z_Malloc ((numflats+1)*sizeof(*flattranslation), PU_STATIC, 0);

    for (i=0 ; i<numflats ; i++)
 flattranslation[i] = i;
}
void R_InitSpriteLumps (void)
{
    int i;
    patch_t *patch;

    firstspritelump = W_GetNumForName (("S_START")) + 1;
    lastspritelump = W_GetNumForName (("S_END")) - 1;

    numspritelumps = lastspritelump - firstspritelump + 1;
    spritewidth = Z_Malloc (numspritelumps*sizeof(*spritewidth), PU_STATIC, 0);
    spriteoffset = Z_Malloc (numspritelumps*sizeof(*spriteoffset), PU_STATIC, 0);
    spritetopoffset = Z_Malloc (numspritelumps*sizeof(*spritetopoffset), PU_STATIC, 0);

    for (i=0 ; i< numspritelumps ; i++)
    {
 if (!(i&63))
     printf (".");

 patch = W_CacheLumpNum (firstspritelump+i, PU_CACHE);
 spritewidth[i] = ((signed short) (patch->width))<<16;
 spriteoffset[i] = ((signed short) (patch->leftoffset))<<16;
 spritetopoffset[i] = ((signed short) (patch->topoffset))<<16;
    }
}






void R_InitColormaps (void)
{
    int lump;



    lump = W_GetNumForName(("COLORMAP"));
    colormaps = W_CacheLumpNum(lump, PU_STATIC);
}
void R_InitData (void)
{
    R_InitTextures ();
    printf (".");
    R_InitFlats ();
    printf (".");
    R_InitSpriteLumps ();
    printf (".");
    R_InitColormaps ();
}







int R_FlatNumForName (char* name)
{
    int i;
    char namet[9];

    i = W_CheckNumForName (name);

    if (i == -1)
    {
 namet[8] = 0;
 memcpy (namet, name,8);
 I_Error ("R_FlatNumForName: %s not found",namet);
    }
    return i - firstflat;
}
int R_CheckTextureNumForName (char *name)
{
    texture_t *texture;
    int key;


    if (name[0] == '-')
 return 0;

    key = W_LumpNameHash(name) % numtextures;

    texture=textures_hashtable[key];

    while (texture != ((void*)0))
    {
 if (!strncasecmp (texture->name, name, 8) )
     return texture->index;

        texture = texture->next;
    }

    return -1;
}
int R_TextureNumForName (char* name)
{
    int i;

    i = R_CheckTextureNumForName (name);

    if (i==-1)
    {
 I_Error ("R_TextureNumForName: %s not found",
   name);
    }
    return i;
}
int flatmemory;
int texturememory;
int spritememory;

void R_PrecacheLevel (void)
{
    char* flatpresent;
    char* texturepresent;
    char* spritepresent;

    int i;
    int j;
    int k;
    int lump;

    texture_t* texture;
    thinker_t* th;
    spriteframe_t* sf;

    if (demoplayback)
 return;


    flatpresent = Z_Malloc(numflats, PU_STATIC, ((void*)0));
    memset (flatpresent,0,numflats);

    for (i=0 ; i<numsectors ; i++)
    {
 flatpresent[sectors[i].floorpic] = 1;
 flatpresent[sectors[i].ceilingpic] = 1;
    }

    flatmemory = 0;

    for (i=0 ; i<numflats ; i++)
    {
 if (flatpresent[i])
 {
     lump = firstflat + i;
     flatmemory += lumpinfo[lump].size;
     W_CacheLumpNum(lump, PU_CACHE);
 }
    }

    Z_Free(flatpresent);


    texturepresent = Z_Malloc(numtextures, PU_STATIC, ((void*)0));
    memset (texturepresent,0, numtextures);

    for (i=0 ; i<numsides ; i++)
    {
 texturepresent[sides[i].toptexture] = 1;
 texturepresent[sides[i].midtexture] = 1;
 texturepresent[sides[i].bottomtexture] = 1;
    }







    texturepresent[skytexture] = 1;

    texturememory = 0;
    for (i=0 ; i<numtextures ; i++)
    {
 if (!texturepresent[i])
     continue;

 texture = textures[i];

 for (j=0 ; j<texture->patchcount ; j++)
 {
     lump = texture->patches[j].patch;
     texturememory += lumpinfo[lump].size;
     W_CacheLumpNum(lump , PU_CACHE);
 }
    }

    Z_Free(texturepresent);


    spritepresent = Z_Malloc(numsprites, PU_STATIC, ((void*)0));
    memset (spritepresent,0, numsprites);

    for (th = thinkercap.next ; th != &thinkercap ; th=th->next)
    {
 if (th->function.acp1 == (actionf_p1)P_MobjThinker)
     spritepresent[((mobj_t *)th)->sprite] = 1;
    }

    spritememory = 0;
    for (i=0 ; i<numsprites ; i++)
    {
 if (!spritepresent[i])
     continue;

 for (j=0 ; j<sprites[i].numframes ; j++)
 {
     sf = &sprites[i].spriteframes[j];
     for (k=0 ; k<8 ; k++)
     {
  lump = firstspritelump + sf->lump[k];
  spritememory += lumpinfo[lump].size;
  W_CacheLumpNum(lump , PU_CACHE);
     }
 }
    }

    Z_Free(spritepresent);
}
byte* viewimage;
int viewwidth;
int scaledviewwidth;
int viewheight;
int viewwindowx;
int viewwindowy;
byte* ylookup[832];
int columnofs[1120];





byte translations[3][256];




static byte *background_buffer = ((void*)0);






lighttable_t* dc_colormap;
int dc_x;
int dc_yl;
int dc_yh;
fixed_t dc_iscale;
fixed_t dc_texturemid;


byte* dc_source;


int dccount;
void R_DrawColumn (void)
{
    int count;
    byte* dest;
    fixed_t frac;
    fixed_t fracstep;

    count = dc_yh - dc_yl;


    if (count < 0)
 return;


    if ((unsigned)dc_x >= 320
 || dc_yl < 0
 || dc_yh >= 200)
 I_Error ("R_DrawColumn: %i to %i at %i", dc_yl, dc_yh, dc_x);





    dest = ylookup[dc_yl] + columnofs[dc_x];



    fracstep = dc_iscale;
    frac = dc_texturemid + (dc_yl-centery)*fracstep;




    do
    {


 *dest = dc_colormap[dc_source[(frac>>16)&127]];

 dest += 320;
 frac += fracstep;

    } while (count--);
}
void R_DrawColumnLow (void)
{
    int count;
    byte* dest;
    byte* dest2;
    fixed_t frac;
    fixed_t fracstep;
    int x;

    count = dc_yh - dc_yl;


    if (count < 0)
 return;


    if ((unsigned)dc_x >= 320
 || dc_yl < 0
 || dc_yh >= 200)
    {

 I_Error ("R_DrawColumn: %i to %i at %i", dc_yl, dc_yh, dc_x);
    }



    x = dc_x << 1;

    dest = ylookup[dc_yl] + columnofs[x];
    dest2 = ylookup[dc_yl] + columnofs[x+1];

    fracstep = dc_iscale;
    frac = dc_texturemid + (dc_yl-centery)*fracstep;

    do
    {

 *dest2 = *dest = dc_colormap[dc_source[(frac>>16)&127]];
 dest += 320;
 dest2 += 320;
 frac += fracstep;

    } while (count--);
}
int fuzzoffset[50] =
{
    (320),-(320),(320),-(320),(320),(320),-(320),
    (320),(320),-(320),(320),(320),(320),-(320),
    (320),(320),(320),-(320),-(320),-(320),-(320),
    (320),-(320),-(320),(320),(320),(320),(320),-(320),
    (320),-(320),(320),(320),-(320),-(320),(320),
    (320),-(320),-(320),-(320),-(320),(320),(320),
    (320),(320),-(320),(320),(320),-(320),(320)
};

int fuzzpos = 0;
void R_DrawFuzzColumn (void)
{
    int count;
    byte* dest;
    fixed_t frac;
    fixed_t fracstep;


    if (!dc_yl)
 dc_yl = 1;


    if (dc_yh == viewheight-1)
 dc_yh = viewheight - 2;

    count = dc_yh - dc_yl;


    if (count < 0)
 return;


    if ((unsigned)dc_x >= 320
 || dc_yl < 0 || dc_yh >= 200)
    {
 I_Error ("R_DrawFuzzColumn: %i to %i at %i",
   dc_yl, dc_yh, dc_x);
    }


    dest = ylookup[dc_yl] + columnofs[dc_x];


    fracstep = dc_iscale;
    frac = dc_texturemid + (dc_yl-centery)*fracstep;




    do
    {




 *dest = colormaps[6*256+dest[fuzzoffset[fuzzpos]]];


 if (++fuzzpos == 50)
     fuzzpos = 0;

 dest += 320;

 frac += fracstep;
    } while (count--);
}



void R_DrawFuzzColumnLow (void)
{
    int count;
    byte* dest;
    byte* dest2;
    fixed_t frac;
    fixed_t fracstep;
    int x;


    if (!dc_yl)
 dc_yl = 1;


    if (dc_yh == viewheight-1)
 dc_yh = viewheight - 2;

    count = dc_yh - dc_yl;


    if (count < 0)
 return;



    x = dc_x << 1;


    if ((unsigned)x >= 320
 || dc_yl < 0 || dc_yh >= 200)
    {
 I_Error ("R_DrawFuzzColumn: %i to %i at %i",
   dc_yl, dc_yh, dc_x);
    }


    dest = ylookup[dc_yl] + columnofs[x];
    dest2 = ylookup[dc_yl] + columnofs[x+1];


    fracstep = dc_iscale;
    frac = dc_texturemid + (dc_yl-centery)*fracstep;




    do
    {




 *dest = colormaps[6*256+dest[fuzzoffset[fuzzpos]]];
 *dest2 = colormaps[6*256+dest2[fuzzoffset[fuzzpos]]];


 if (++fuzzpos == 50)
     fuzzpos = 0;

 dest += 320;
 dest2 += 320;

 frac += fracstep;
    } while (count--);
}
byte* dc_translation;
byte* translationtables;

void R_DrawTranslatedColumn (void)
{
    int count;
    byte* dest;
    fixed_t frac;
    fixed_t fracstep;

    count = dc_yh - dc_yl;
    if (count < 0)
 return;


    if ((unsigned)dc_x >= 320
 || dc_yl < 0
 || dc_yh >= 200)
    {
 I_Error ( "R_DrawColumn: %i to %i at %i",
    dc_yl, dc_yh, dc_x);
    }




    dest = ylookup[dc_yl] + columnofs[dc_x];


    fracstep = dc_iscale;
    frac = dc_texturemid + (dc_yl-centery)*fracstep;


    do
    {





 *dest = dc_colormap[dc_translation[dc_source[frac>>16]]];
 dest += 320;

 frac += fracstep;
    } while (count--);
}

void R_DrawTranslatedColumnLow (void)
{
    int count;
    byte* dest;
    byte* dest2;
    fixed_t frac;
    fixed_t fracstep;
    int x;

    count = dc_yh - dc_yl;
    if (count < 0)
 return;


    x = dc_x << 1;


    if ((unsigned)x >= 320
 || dc_yl < 0
 || dc_yh >= 200)
    {
 I_Error ( "R_DrawColumn: %i to %i at %i",
    dc_yl, dc_yh, x);
    }




    dest = ylookup[dc_yl] + columnofs[x];
    dest2 = ylookup[dc_yl] + columnofs[x+1];


    fracstep = dc_iscale;
    frac = dc_texturemid + (dc_yl-centery)*fracstep;


    do
    {





 *dest = dc_colormap[dc_translation[dc_source[frac>>16]]];
 *dest2 = dc_colormap[dc_translation[dc_source[frac>>16]]];
 dest += 320;
 dest2 += 320;

 frac += fracstep;
    } while (count--);
}
void R_InitTranslationTables (void)
{
    int i;

    translationtables = Z_Malloc (256*3, PU_STATIC, 0);


    for (i=0 ; i<256 ; i++)
    {
 if (i >= 0x70 && i<= 0x7f)
 {

     translationtables[i] = 0x60 + (i&0xf);
     translationtables [i+256] = 0x40 + (i&0xf);
     translationtables [i+512] = 0x20 + (i&0xf);
 }
 else
 {

     translationtables[i] = translationtables[i+256]
  = translationtables[i+512] = i;
 }
    }
}
int ds_y;
int ds_x1;
int ds_x2;

lighttable_t* ds_colormap;

fixed_t ds_xfrac;
fixed_t ds_yfrac;
fixed_t ds_xstep;
fixed_t ds_ystep;


byte* ds_source;


int dscount;




void R_DrawSpan (void)
{
    unsigned int position, step;
    byte *dest;
    int count;
    int spot;
    unsigned int xtemp, ytemp;


    if (ds_x2 < ds_x1
 || ds_x1<0
 || ds_x2>=320
 || (unsigned)ds_y>200)
    {
 I_Error( "R_DrawSpan: %i to %i at %i",
   ds_x1,ds_x2,ds_y);
    }
    position = ((ds_xfrac << 10) & 0xffff0000)
             | ((ds_yfrac >> 6) & 0x0000ffff);
    step = ((ds_xstep << 10) & 0xffff0000)
         | ((ds_ystep >> 6) & 0x0000ffff);

    dest = ylookup[ds_y] + columnofs[ds_x1];


    count = ds_x2 - ds_x1;

    do
    {

        ytemp = (position >> 4) & 0x0fc0;
        xtemp = (position >> 26);
        spot = xtemp | ytemp;



 *dest++ = ds_colormap[ds_source[spot]];

        position += step;

    } while (count--);
}
void R_DrawSpanLow (void)
{
    unsigned int position, step;
    unsigned int xtemp, ytemp;
    byte *dest;
    int count;
    int spot;


    if (ds_x2 < ds_x1
 || ds_x1<0
 || ds_x2>=320
 || (unsigned)ds_y>200)
    {
 I_Error( "R_DrawSpan: %i to %i at %i",
   ds_x1,ds_x2,ds_y);
    }



    position = ((ds_xfrac << 10) & 0xffff0000)
             | ((ds_yfrac >> 6) & 0x0000ffff);
    step = ((ds_xstep << 10) & 0xffff0000)
         | ((ds_ystep >> 6) & 0x0000ffff);

    count = (ds_x2 - ds_x1);


    ds_x1 <<= 1;
    ds_x2 <<= 1;

    dest = ylookup[ds_y] + columnofs[ds_x1];

    do
    {

        ytemp = (position >> 4) & 0x0fc0;
        xtemp = (position >> 26);
        spot = xtemp | ytemp;



 *dest++ = ds_colormap[ds_source[spot]];
 *dest++ = ds_colormap[ds_source[spot]];

 position += step;

    } while (count--);
}
void
R_InitBuffer
( int width,
  int height )
{
    int i;




    viewwindowx = (320 -width) >> 1;


    for (i=0 ; i<width ; i++)
 columnofs[i] = viewwindowx + i;


    if (width == 320)
 viewwindowy = 0;
    else
 viewwindowy = (200 -32 -height) >> 1;


    for (i=0 ; i<height ; i++)
 ylookup[i] = I_VideoBuffer + (i+viewwindowy)*320;
}
void R_FillBackScreen (void)
{
    byte* src;
    byte* dest;
    int x;
    int y;
    patch_t* patch;


    char *name1 = ("FLOOR7_2");


    char *name2 = ("GRNROCK");

    char *name;




    if (scaledviewwidth == 320)
    {
        if (background_buffer != ((void*)0))
        {
            Z_Free(background_buffer);
            background_buffer = ((void*)0);
        }

 return;
    }



    if (background_buffer == ((void*)0))
    {
        background_buffer = Z_Malloc(320 * (200 - 32),
                                     PU_STATIC, ((void*)0));
    }

    if (gamemode == commercial)
 name = name2;
    else
 name = name1;

    src = W_CacheLumpName(name, PU_CACHE);
    dest = background_buffer;

    for (y=0 ; y<200 -32 ; y++)
    {
 for (x=0 ; x<320/64 ; x++)
 {
     memcpy (dest, src+((y&63)<<6), 64);
     dest += 64;
 }

 if (320&63)
 {
     memcpy (dest, src+((y&63)<<6), 320&63);
     dest += (320&63);
 }
    }



    V_UseBuffer(background_buffer);

    patch = W_CacheLumpName(("brdr_t"),PU_CACHE);

    for (x=0 ; x<scaledviewwidth ; x+=8)
 V_DrawPatch(viewwindowx+x, viewwindowy-8, patch);
    patch = W_CacheLumpName(("brdr_b"),PU_CACHE);

    for (x=0 ; x<scaledviewwidth ; x+=8)
 V_DrawPatch(viewwindowx+x, viewwindowy+viewheight, patch);
    patch = W_CacheLumpName(("brdr_l"),PU_CACHE);

    for (y=0 ; y<viewheight ; y+=8)
 V_DrawPatch(viewwindowx-8, viewwindowy+y, patch);
    patch = W_CacheLumpName(("brdr_r"),PU_CACHE);

    for (y=0 ; y<viewheight ; y+=8)
 V_DrawPatch(viewwindowx+scaledviewwidth, viewwindowy+y, patch);


    V_DrawPatch(viewwindowx-8,
                viewwindowy-8,
                W_CacheLumpName(("brdr_tl"),PU_CACHE));

    V_DrawPatch(viewwindowx+scaledviewwidth,
                viewwindowy-8,
                W_CacheLumpName(("brdr_tr"),PU_CACHE));

    V_DrawPatch(viewwindowx-8,
                viewwindowy+viewheight,
                W_CacheLumpName(("brdr_bl"),PU_CACHE));

    V_DrawPatch(viewwindowx+scaledviewwidth,
                viewwindowy+viewheight,
                W_CacheLumpName(("brdr_br"),PU_CACHE));

    V_RestoreBuffer();
}





void
R_VideoErase
( unsigned ofs,
  int count )
{






    if (background_buffer != ((void*)0))
    {
        memcpy(I_VideoBuffer + ofs, background_buffer + ofs, count);
    }
}







void R_DrawViewBorder (void)
{
    int top;
    int side;
    int ofs;
    int i;

    if (scaledviewwidth == 320)
 return;

    top = ((200 -32)-viewheight)/2;
    side = (320 -scaledviewwidth)/2;


    R_VideoErase (0, top*320 +side);


    ofs = (viewheight+top)*320 -side;
    R_VideoErase (ofs, top*320 +side);


    ofs = top*320 + 320 -side;
    side <<= 1;

    for (i=1 ; i<viewheight ; i++)
    {
 R_VideoErase (ofs, side);
 ofs += 320;
    }


    V_MarkRect (0,0,320, 200 -32);
}
int viewangleoffset;


int validcount = 1;


lighttable_t* fixedcolormap;
extern lighttable_t** walllights;

int centerx;
int centery;

fixed_t centerxfrac;
fixed_t centeryfrac;
fixed_t projection;


int framecount;

int sscount;
int linecount;
int loopcount;

fixed_t viewx;
fixed_t viewy;
fixed_t viewz;

angle_t viewangle;

fixed_t viewcos;
fixed_t viewsin;

player_t* viewplayer;


int detailshift;




angle_t clipangle;





int viewangletox[8192/2];




angle_t xtoviewangle[320 +1];

lighttable_t* scalelight[16][48];
lighttable_t* scalelightfixed[48];
lighttable_t* zlight[16][128];


int extralight;



void (*colfunc) (void);
void (*basecolfunc) (void);
void (*fuzzcolfunc) (void);
void (*transcolfunc) (void);
void (*spanfunc) (void);
void
R_AddPointToBox
( int x,
  int y,
  fixed_t* box )
{
    if (x< box[BOXLEFT])
 box[BOXLEFT] = x;
    if (x> box[BOXRIGHT])
 box[BOXRIGHT] = x;
    if (y< box[BOXBOTTOM])
 box[BOXBOTTOM] = y;
    if (y> box[BOXTOP])
 box[BOXTOP] = y;
}
int
R_PointOnSide
( fixed_t x,
  fixed_t y,
  node_t* node )
{
    fixed_t dx;
    fixed_t dy;
    fixed_t left;
    fixed_t right;

    if (!node->dx)
    {
 if (x <= node->x)
     return node->dy > 0;

 return node->dy < 0;
    }
    if (!node->dy)
    {
 if (y <= node->y)
     return node->dx < 0;

 return node->dx > 0;
    }

    dx = (x - node->x);
    dy = (y - node->y);


    if ( (node->dy ^ node->dx ^ dx ^ dy)&0x80000000 )
    {
 if ( (node->dy ^ dx) & 0x80000000 )
 {

     return 1;
 }
 return 0;
    }

    left = FixedMul ( node->dy>>16 , dx );
    right = FixedMul ( dy , node->dx>>16 );

    if (right < left)
    {

 return 0;
    }

    return 1;
}


int
R_PointOnSegSide
( fixed_t x,
  fixed_t y,
  seg_t* line )
{
    fixed_t lx;
    fixed_t ly;
    fixed_t ldx;
    fixed_t ldy;
    fixed_t dx;
    fixed_t dy;
    fixed_t left;
    fixed_t right;

    lx = line->v1->x;
    ly = line->v1->y;

    ldx = line->v2->x - lx;
    ldy = line->v2->y - ly;

    if (!ldx)
    {
 if (x <= lx)
     return ldy > 0;

 return ldy < 0;
    }
    if (!ldy)
    {
 if (y <= ly)
     return ldx < 0;

 return ldx > 0;
    }

    dx = (x - lx);
    dy = (y - ly);


    if ( (ldy ^ ldx ^ dx ^ dy)&0x80000000 )
    {
 if ( (ldy ^ dx) & 0x80000000 )
 {

     return 1;
 }
 return 0;
    }

    left = FixedMul ( ldy>>16 , dx );
    right = FixedMul ( dy , ldx>>16 );

    if (right < left)
    {

 return 0;
    }

    return 1;
}
angle_t
R_PointToAngle
( fixed_t x,
  fixed_t y )
{
    x -= viewx;
    y -= viewy;

    if ( (!x) && (!y) )
 return 0;

    if (x>= 0)
    {

 if (y>= 0)
 {


     if (x>y)
     {

  return tantoangle[ SlopeDiv(y,x)];
     }
     else
     {

  return 0x40000000 -1-tantoangle[ SlopeDiv(x,y)];
     }
 }
 else
 {

     y = -y;

     if (x>y)
     {

  return -tantoangle[SlopeDiv(y,x)];
     }
     else
     {

  return 0xc0000000 +tantoangle[ SlopeDiv(x,y)];
     }
 }
    }
    else
    {

 x = -x;

 if (y>= 0)
 {

     if (x>y)
     {

  return 0x80000000 -1-tantoangle[ SlopeDiv(y,x)];
     }
     else
     {

  return 0x40000000 + tantoangle[ SlopeDiv(x,y)];
     }
 }
 else
 {

     y = -y;

     if (x>y)
     {

  return 0x80000000 +tantoangle[ SlopeDiv(y,x)];
     }
     else
     {

  return 0xc0000000 -1-tantoangle[ SlopeDiv(x,y)];
     }
 }
    }
    return 0;
}


angle_t
R_PointToAngle2
( fixed_t x1,
  fixed_t y1,
  fixed_t x2,
  fixed_t y2 )
{
    viewx = x1;
    viewy = y1;

    return R_PointToAngle (x2, y2);
}


fixed_t
R_PointToDist
( fixed_t x,
  fixed_t y )
{
    int angle;
    fixed_t dx;
    fixed_t dy;
    fixed_t temp;
    fixed_t dist;
    fixed_t frac;

    dx = abs(x - viewx);
    dy = abs(y - viewy);

    if (dy>dx)
    {
 temp = dx;
 dx = dy;
 dy = temp;
    }



    if (dx != 0)
    {
        frac = FixedDiv(dy, dx);
    }
    else
    {
 frac = 0;
    }

    angle = (tantoangle[frac>>(16 -11)]+0x40000000) >> 19;


    dist = FixedDiv (dx, finesine[angle] );

    return dist;
}







void R_InitPointToAngle (void)
{
}
fixed_t R_ScaleFromGlobalAngle (angle_t visangle)
{
    fixed_t scale;
    angle_t anglea;
    angle_t angleb;
    int sinea;
    int sineb;
    fixed_t num;
    int den;
    anglea = 0x40000000 + (visangle-viewangle);
    angleb = 0x40000000 + (visangle-rw_normalangle);


    sinea = finesine[anglea>>19];
    sineb = finesine[angleb>>19];
    num = FixedMul(projection,sineb)<<detailshift;
    den = FixedMul(rw_distance,sinea);

    if (den > num>>16)
    {
 scale = FixedDiv (num, den);

 if (scale > 64*(1<<16))
     scale = 64*(1<<16);
 else if (scale < 256)
     scale = 256;
    }
    else
 scale = 64*(1<<16);

    return scale;
}






void R_InitTables (void)
{
}






void R_InitTextureMapping (void)
{
    int i;
    int x;
    int t;
    fixed_t focallength;







    focallength = FixedDiv (centerxfrac,
       finetangent[8192/4+2048/2] );

    for (i=0 ; i<8192/2 ; i++)
    {
 if (finetangent[i] > (1<<16)*2)
     t = -1;
 else if (finetangent[i] < -(1<<16)*2)
     t = viewwidth+1;
 else
 {
     t = FixedMul (finetangent[i], focallength);
     t = (centerxfrac - t+(1<<16)-1)>>16;

     if (t < -1)
  t = -1;
     else if (t>viewwidth+1)
  t = viewwidth+1;
 }
 viewangletox[i] = t;
    }




    for (x=0;x<=viewwidth;x++)
    {
 i = 0;
 while (viewangletox[i]>x)
     i++;
 xtoviewangle[x] = (i<<19)-0x40000000;
    }


    for (i=0 ; i<8192/2 ; i++)
    {
 t = FixedMul (finetangent[i], focallength);
 t = centerx - t;

 if (viewangletox[i] == -1)
     viewangletox[i] = 0;
 else if (viewangletox[i] == viewwidth+1)
     viewangletox[i] = viewwidth;
    }

    clipangle = xtoviewangle[0];
}
void R_InitLightTables (void)
{
    int i;
    int j;
    int level;
    int startmap;
    int scale;



    for (i=0 ; i< 16 ; i++)
    {
 startmap = ((16 -1-i)*2)*32/16;
 for (j=0 ; j<128 ; j++)
 {
     scale = FixedDiv ((320/2*(1<<16)), (j+1)<<20);
     scale >>= 12;
     level = startmap - scale/2;

     if (level < 0)
  level = 0;

     if (level >= 32)
  level = 32 -1;

     zlight[i][j] = colormaps + level*256;
 }
    }
}
boolean setsizeneeded;
int setblocks;
int setdetail;


void
R_SetViewSize
( int blocks,
  int detail )
{
    setsizeneeded = true;
    setblocks = blocks;
    setdetail = detail;
}





void R_ExecuteSetViewSize (void)
{
    fixed_t cosadj;
    fixed_t dy;
    int i;
    int j;
    int level;
    int startmap;

    setsizeneeded = false;

    if (setblocks == 11)
    {
 scaledviewwidth = 320;
 viewheight = 200;
    }
    else
    {
 scaledviewwidth = setblocks*32;
 viewheight = (setblocks*168/10)&~7;
    }

    detailshift = setdetail;
    viewwidth = scaledviewwidth>>detailshift;

    centery = viewheight/2;
    centerx = viewwidth/2;
    centerxfrac = centerx<<16;
    centeryfrac = centery<<16;
    projection = centerxfrac;

    if (!detailshift)
    {
 colfunc = basecolfunc = R_DrawColumn;
 fuzzcolfunc = R_DrawFuzzColumn;
 transcolfunc = R_DrawTranslatedColumn;
 spanfunc = R_DrawSpan;
    }
    else
    {
 colfunc = basecolfunc = R_DrawColumnLow;
 fuzzcolfunc = R_DrawFuzzColumnLow;
 transcolfunc = R_DrawTranslatedColumnLow;
 spanfunc = R_DrawSpanLow;
    }

    R_InitBuffer (scaledviewwidth, viewheight);

    R_InitTextureMapping ();


    pspritescale = (1<<16)*viewwidth/320;
    pspriteiscale = (1<<16)*320/viewwidth;


    for (i=0 ; i<viewwidth ; i++)
 screenheightarray[i] = viewheight;


    for (i=0 ; i<viewheight ; i++)
    {
 dy = ((i-viewheight/2)<<16)+(1<<16)/2;
 dy = abs(dy);
 yslope[i] = FixedDiv ( (viewwidth<<detailshift)/2*(1<<16), dy);
    }

    for (i=0 ; i<viewwidth ; i++)
    {
 cosadj = abs(finecosine[xtoviewangle[i]>>19]);
 distscale[i] = FixedDiv ((1<<16),cosadj);
    }



    for (i=0 ; i< 16 ; i++)
    {
 startmap = ((16 -1-i)*2)*32/16;
 for (j=0 ; j<48 ; j++)
 {
     level = startmap - j*320/(viewwidth<<detailshift)/2;

     if (level < 0)
  level = 0;

     if (level >= 32)
  level = 32 -1;

     scalelight[i][j] = colormaps + level*256;
 }
    }
}
void R_Init (void)
{
    R_InitData ();
    printf (".");
    R_InitPointToAngle ();
    printf (".");
    R_InitTables ();

    printf (".");

    R_SetViewSize (screenblocks, detailLevel);
    R_InitPlanes ();
    printf (".");
    R_InitLightTables ();
    printf (".");
    R_InitSkyMap ();
    R_InitTranslationTables ();
    printf (".");

    framecount = 0;
}





subsector_t*
R_PointInSubsector
( fixed_t x,
  fixed_t y )
{
    node_t* node;
    int side;
    int nodenum;


    if (!numnodes)
 return subsectors;

    nodenum = numnodes-1;

    while (! (nodenum & 0x8000) )
    {
 node = &nodes[nodenum];
 side = R_PointOnSide (x, y, node);
 nodenum = node->children[side];
    }

    return &subsectors[nodenum & ~0x8000];
}






void R_SetupFrame (player_t* player)
{
    int i;

    viewplayer = player;
    viewx = player->mo->x;
    viewy = player->mo->y;
    viewangle = player->mo->angle + viewangleoffset;
    extralight = player->extralight;

    viewz = player->viewz;

    viewsin = finesine[viewangle>>19];
    viewcos = finecosine[viewangle>>19];

    sscount = 0;

    if (player->fixedcolormap)
    {
 fixedcolormap =
     colormaps
     + player->fixedcolormap*256*sizeof(lighttable_t);

 walllights = scalelightfixed;

 for (i=0 ; i<48 ; i++)
     scalelightfixed[i] = fixedcolormap;
    }
    else
 fixedcolormap = 0;

    framecount++;
    validcount++;
}






void R_RenderPlayerView (player_t* player)
{
    R_SetupFrame (player);


    R_ClearClipSegs ();
    R_ClearDrawSegs ();
    R_ClearPlanes ();
    R_ClearSprites ();


    NetUpdate ();


    R_RenderBSPNode (numnodes-1);


    NetUpdate ();

    R_DrawPlanes ();


    NetUpdate ();

    R_DrawMasked ();


    NetUpdate ();
}
planefunction_t floorfunc;
planefunction_t ceilingfunc;







visplane_t visplanes[128];
visplane_t* lastvisplane;
visplane_t* floorplane;
visplane_t* ceilingplane;



short openings[320*64];
short* lastopening;







short floorclip[320];
short ceilingclip[320];





int spanstart[200];
int spanstop[200];




lighttable_t** planezlight;
fixed_t planeheight;

fixed_t yslope[200];
fixed_t distscale[320];
fixed_t basexscale;
fixed_t baseyscale;

fixed_t cachedheight[200];
fixed_t cacheddistance[200];
fixed_t cachedxstep[200];
fixed_t cachedystep[200];







void R_InitPlanes (void)
{

}
void
R_MapPlane
( int y,
  int x1,
  int x2 )
{
    angle_t angle;
    fixed_t distance;
    fixed_t length;
    unsigned index;


    if (x2 < x1
     || x1 < 0
     || x2 >= viewwidth
     || y > viewheight)
    {
 I_Error ("R_MapPlane: %i, %i at %i",x1,x2,y);
    }


    if (planeheight != cachedheight[y])
    {
 cachedheight[y] = planeheight;
 distance = cacheddistance[y] = FixedMul (planeheight, yslope[y]);
 ds_xstep = cachedxstep[y] = FixedMul (distance,basexscale);
 ds_ystep = cachedystep[y] = FixedMul (distance,baseyscale);
    }
    else
    {
 distance = cacheddistance[y];
 ds_xstep = cachedxstep[y];
 ds_ystep = cachedystep[y];
    }

    length = FixedMul (distance,distscale[x1]);
    angle = (viewangle + xtoviewangle[x1])>>19;
    ds_xfrac = viewx + FixedMul(finecosine[angle], length);
    ds_yfrac = -viewy - FixedMul(finesine[angle], length);

    if (fixedcolormap)
 ds_colormap = fixedcolormap;
    else
    {
 index = distance >> 20;

 if (index >= 128 )
     index = 128 -1;

 ds_colormap = planezlight[index];
    }

    ds_y = y;
    ds_x1 = x1;
    ds_x2 = x2;


    spanfunc ();
}






void R_ClearPlanes (void)
{
    int i;
    angle_t angle;


    for (i=0 ; i<viewwidth ; i++)
    {
 floorclip[i] = viewheight;
 ceilingclip[i] = -1;
    }

    lastvisplane = visplanes;
    lastopening = openings;


    memset (cachedheight, 0, sizeof(cachedheight));


    angle = (viewangle-0x40000000)>>19;


    basexscale = FixedDiv (finecosine[angle],centerxfrac);
    baseyscale = -FixedDiv (finesine[angle],centerxfrac);
}







visplane_t*
R_FindPlane
( fixed_t height,
  int picnum,
  int lightlevel )
{
    visplane_t* check;

    if (picnum == skyflatnum)
    {
 height = 0;
 lightlevel = 0;
    }

    for (check=visplanes; check<lastvisplane; check++)
    {
 if (height == check->height
     && picnum == check->picnum
     && lightlevel == check->lightlevel)
 {
     break;
 }
    }


    if (check < lastvisplane)
 return check;

    if (lastvisplane - visplanes == 128)
 I_Error ("R_FindPlane: no more visplanes");

    lastvisplane++;

    check->height = height;
    check->picnum = picnum;
    check->lightlevel = lightlevel;
    check->minx = 320;
    check->maxx = -1;

    memset (check->top,0xff,sizeof(check->top));

    return check;
}





visplane_t*
R_CheckPlane
( visplane_t* pl,
  int start,
  int stop )
{
    int intrl;
    int intrh;
    int unionl;
    int unionh;
    int x;

    if (start < pl->minx)
    {
 intrl = pl->minx;
 unionl = start;
    }
    else
    {
 unionl = pl->minx;
 intrl = start;
    }

    if (stop > pl->maxx)
    {
 intrh = pl->maxx;
 unionh = stop;
    }
    else
    {
 unionh = pl->maxx;
 intrh = stop;
    }

    for (x=intrl ; x<= intrh ; x++)
 if (pl->top[x] != 0xff)
     break;

    if (x > intrh)
    {
 pl->minx = unionl;
 pl->maxx = unionh;


 return pl;
    }


    lastvisplane->height = pl->height;
    lastvisplane->picnum = pl->picnum;
    lastvisplane->lightlevel = pl->lightlevel;

    pl = lastvisplane++;
    pl->minx = start;
    pl->maxx = stop;

    memset (pl->top,0xff,sizeof(pl->top));

    return pl;
}





void
R_MakeSpans
( int x,
  int t1,
  int b1,
  int t2,
  int b2 )
{
    while (t1 < t2 && t1<=b1)
    {
 R_MapPlane (t1,spanstart[t1],x-1);
 t1++;
    }
    while (b1 > b2 && b1>=t1)
    {
 R_MapPlane (b1,spanstart[b1],x-1);
 b1--;
    }

    while (t2 < t1 && t2<=b2)
    {
 spanstart[t2] = x;
 t2++;
    }
    while (b2 > b1 && b2>=t2)
    {
 spanstart[b2] = x;
 b2--;
    }
}







void R_DrawPlanes (void)
{
    visplane_t* pl;
    int light;
    int x;
    int stop;
    int angle;
    int lumpnum;


    if (ds_p - drawsegs > 256)
 I_Error ("R_DrawPlanes: drawsegs overflow (%i)",
   ds_p - drawsegs);

    if (lastvisplane - visplanes > 128)
 I_Error ("R_DrawPlanes: visplane overflow (%i)",
   lastvisplane - visplanes);

    if (lastopening - openings > 320*64)
 I_Error ("R_DrawPlanes: opening overflow (%i)",
   lastopening - openings);


    for (pl = visplanes ; pl < lastvisplane ; pl++)
    {
 if (pl->minx > pl->maxx)
     continue;



 if (pl->picnum == skyflatnum)
 {
     dc_iscale = pspriteiscale>>detailshift;





     dc_colormap = colormaps;
     dc_texturemid = skytexturemid;
     for (x=pl->minx ; x <= pl->maxx ; x++)
     {
  dc_yl = pl->top[x];
  dc_yh = pl->bottom[x];

  if (dc_yl <= dc_yh)
  {
      angle = (viewangle + xtoviewangle[x])>>22;
      dc_x = x;
      dc_source = R_GetColumn(skytexture, angle);
      colfunc ();
  }
     }
     continue;
 }


        lumpnum = firstflat + flattranslation[pl->picnum];
 ds_source = W_CacheLumpNum(lumpnum, PU_STATIC);

 planeheight = abs(pl->height-viewz);
 light = (pl->lightlevel >> 4)+extralight;

 if (light >= 16)
     light = 16 -1;

 if (light < 0)
     light = 0;

 planezlight = zlight[light];

 pl->top[pl->maxx+1] = 0xff;
 pl->top[pl->minx-1] = 0xff;

 stop = pl->maxx + 1;

 for (x=pl->minx ; x<= stop ; x++)
 {
     R_MakeSpans(x,pl->top[x-1],
   pl->bottom[x-1],
   pl->top[x],
   pl->bottom[x]);
 }

        W_ReleaseLumpNum(lumpnum);
    }
}
boolean segtextured;


boolean markfloor;
boolean markceiling;

boolean maskedtexture;
int toptexture;
int bottomtexture;
int midtexture;


angle_t rw_normalangle;

int rw_angle1;




int rw_x;
int rw_stopx;
angle_t rw_centerangle;
fixed_t rw_offset;
fixed_t rw_distance;
fixed_t rw_scale;
fixed_t rw_scalestep;
fixed_t rw_midtexturemid;
fixed_t rw_toptexturemid;
fixed_t rw_bottomtexturemid;

int worldtop;
int worldbottom;
int worldhigh;
int worldlow;

fixed_t pixhigh;
fixed_t pixlow;
fixed_t pixhighstep;
fixed_t pixlowstep;

fixed_t topfrac;
fixed_t topstep;

fixed_t bottomfrac;
fixed_t bottomstep;


lighttable_t** walllights;

short* maskedtexturecol;






void
R_RenderMaskedSegRange
( drawseg_t* ds,
  int x1,
  int x2 )
{
    unsigned index;
    column_t* col;
    int lightnum;
    int texnum;





    curline = ds->curline;
    frontsector = curline->frontsector;
    backsector = curline->backsector;
    texnum = texturetranslation[curline->sidedef->midtexture];

    lightnum = (frontsector->lightlevel >> 4)+extralight;

    if (curline->v1->y == curline->v2->y)
 lightnum--;
    else if (curline->v1->x == curline->v2->x)
 lightnum++;

    if (lightnum < 0)
 walllights = scalelight[0];
    else if (lightnum >= 16)
 walllights = scalelight[16 -1];
    else
 walllights = scalelight[lightnum];

    maskedtexturecol = ds->maskedtexturecol;

    rw_scalestep = ds->scalestep;
    spryscale = ds->scale1 + (x1 - ds->x1)*rw_scalestep;
    mfloorclip = ds->sprbottomclip;
    mceilingclip = ds->sprtopclip;


    if (curline->linedef->flags & 16)
    {
 dc_texturemid = frontsector->floorheight > backsector->floorheight
     ? frontsector->floorheight : backsector->floorheight;
 dc_texturemid = dc_texturemid + textureheight[texnum] - viewz;
    }
    else
    {
 dc_texturemid =frontsector->ceilingheight<backsector->ceilingheight
     ? frontsector->ceilingheight : backsector->ceilingheight;
 dc_texturemid = dc_texturemid - viewz;
    }
    dc_texturemid += curline->sidedef->rowoffset;

    if (fixedcolormap)
 dc_colormap = fixedcolormap;


    for (dc_x = x1 ; dc_x <= x2 ; dc_x++)
    {

 if (maskedtexturecol[dc_x] != 32767)
 {
     if (!fixedcolormap)
     {
  index = spryscale>>12;

  if (index >= 48 )
      index = 48 -1;

  dc_colormap = walllights[index];
     }

     sprtopscreen = centeryfrac - FixedMul(dc_texturemid, spryscale);
     dc_iscale = 0xffffffffu / (unsigned)spryscale;


     col = (column_t *)(
  (byte *)R_GetColumn(texnum,maskedtexturecol[dc_x]) -3);

     R_DrawMaskedColumn (col);
     maskedtexturecol[dc_x] = 32767;
 }
 spryscale += rw_scalestep;
    }

}
void R_RenderSegLoop (void)
{
    angle_t angle;
    unsigned index;
    int yl;
    int yh;
    int mid;
    fixed_t texturecolumn;
    int top;
    int bottom;

    for ( ; rw_x < rw_stopx ; rw_x++)
    {

 yl = (topfrac+(1<<12)-1)>>12;


 if (yl < ceilingclip[rw_x]+1)
     yl = ceilingclip[rw_x]+1;

 if (markceiling)
 {
     top = ceilingclip[rw_x]+1;
     bottom = yl-1;

     if (bottom >= floorclip[rw_x])
  bottom = floorclip[rw_x]-1;

     if (top <= bottom)
     {
  ceilingplane->top[rw_x] = top;
  ceilingplane->bottom[rw_x] = bottom;
     }
 }

 yh = bottomfrac>>12;

 if (yh >= floorclip[rw_x])
     yh = floorclip[rw_x]-1;

 if (markfloor)
 {
     top = yh+1;
     bottom = floorclip[rw_x]-1;
     if (top <= ceilingclip[rw_x])
  top = ceilingclip[rw_x]+1;
     if (top <= bottom)
     {
  floorplane->top[rw_x] = top;
  floorplane->bottom[rw_x] = bottom;
     }
 }


 if (segtextured)
 {

     angle = (rw_centerangle + xtoviewangle[rw_x])>>19;
     texturecolumn = rw_offset-FixedMul(finetangent[angle],rw_distance);
     texturecolumn >>= 16;

     index = rw_scale>>12;

     if (index >= 48 )
  index = 48 -1;

     dc_colormap = walllights[index];
     dc_x = rw_x;
     dc_iscale = 0xffffffffu / (unsigned)rw_scale;
 }
        else
        {


            texturecolumn = 0;
        }


 if (midtexture)
 {

     dc_yl = yl;
     dc_yh = yh;
     dc_texturemid = rw_midtexturemid;
     dc_source = R_GetColumn(midtexture,texturecolumn);
     colfunc ();
     ceilingclip[rw_x] = viewheight;
     floorclip[rw_x] = -1;
 }
 else
 {

     if (toptexture)
     {

  mid = pixhigh>>12;
  pixhigh += pixhighstep;

  if (mid >= floorclip[rw_x])
      mid = floorclip[rw_x]-1;

  if (mid >= yl)
  {
      dc_yl = yl;
      dc_yh = mid;
      dc_texturemid = rw_toptexturemid;
      dc_source = R_GetColumn(toptexture,texturecolumn);
      colfunc ();
      ceilingclip[rw_x] = mid;
  }
  else
      ceilingclip[rw_x] = yl-1;
     }
     else
     {

  if (markceiling)
      ceilingclip[rw_x] = yl-1;
     }

     if (bottomtexture)
     {

  mid = (pixlow+(1<<12)-1)>>12;
  pixlow += pixlowstep;


  if (mid <= ceilingclip[rw_x])
      mid = ceilingclip[rw_x]+1;

  if (mid <= yh)
  {
      dc_yl = mid;
      dc_yh = yh;
      dc_texturemid = rw_bottomtexturemid;
      dc_source = R_GetColumn(bottomtexture,
         texturecolumn);
      colfunc ();
      floorclip[rw_x] = mid;
  }
  else
      floorclip[rw_x] = yh+1;
     }
     else
     {

  if (markfloor)
      floorclip[rw_x] = yh+1;
     }

     if (maskedtexture)
     {


  maskedtexturecol[rw_x] = texturecolumn;
     }
 }

 rw_scale += rw_scalestep;
 topfrac += topstep;
 bottomfrac += bottomstep;
    }
}
void
R_StoreWallRange
( int start,
  int stop )
{
    fixed_t hyp;
    fixed_t sineval;
    angle_t distangle, offsetangle;
    fixed_t vtop;
    int lightnum;


    if (ds_p == &drawsegs[256])
 return;


    if (start >=viewwidth || start > stop)
 I_Error ("Bad R_RenderWallRange: %i to %i", start , stop);


    sidedef = curline->sidedef;
    linedef = curline->linedef;


    linedef->flags |= 256;


    rw_normalangle = curline->angle + 0x40000000;
    offsetangle = abs(rw_normalangle-rw_angle1);

    if (offsetangle > 0x40000000)
 offsetangle = 0x40000000;

    distangle = 0x40000000 - offsetangle;
    hyp = R_PointToDist (curline->v1->x, curline->v1->y);
    sineval = finesine[distangle>>19];
    rw_distance = FixedMul (hyp, sineval);


    ds_p->x1 = rw_x = start;
    ds_p->x2 = stop;
    ds_p->curline = curline;
    rw_stopx = stop+1;


    ds_p->scale1 = rw_scale =
 R_ScaleFromGlobalAngle (viewangle + xtoviewangle[start]);

    if (stop > start )
    {
 ds_p->scale2 = R_ScaleFromGlobalAngle (viewangle + xtoviewangle[stop]);
 ds_p->scalestep = rw_scalestep =
     (ds_p->scale2 - rw_scale) / (stop-start);
    }
    else
    {
 ds_p->scale2 = ds_p->scale1;
    }



    worldtop = frontsector->ceilingheight - viewz;
    worldbottom = frontsector->floorheight - viewz;

    midtexture = toptexture = bottomtexture = maskedtexture = 0;
    ds_p->maskedtexturecol = ((void*)0);

    if (!backsector)
    {

 midtexture = texturetranslation[sidedef->midtexture];

 markfloor = markceiling = true;
 if (linedef->flags & 16)
 {
     vtop = frontsector->floorheight +
  textureheight[sidedef->midtexture];

     rw_midtexturemid = vtop - viewz;
 }
 else
 {

     rw_midtexturemid = worldtop;
 }
 rw_midtexturemid += sidedef->rowoffset;

 ds_p->silhouette = 3;
 ds_p->sprtopclip = screenheightarray;
 ds_p->sprbottomclip = negonearray;
 ds_p->bsilheight = 2147483647;
 ds_p->tsilheight = (-2147483647-1);
    }
    else
    {

 ds_p->sprtopclip = ds_p->sprbottomclip = ((void*)0);
 ds_p->silhouette = 0;

 if (frontsector->floorheight > backsector->floorheight)
 {
     ds_p->silhouette = 1;
     ds_p->bsilheight = frontsector->floorheight;
 }
 else if (backsector->floorheight > viewz)
 {
     ds_p->silhouette = 1;
     ds_p->bsilheight = 2147483647;

 }

 if (frontsector->ceilingheight < backsector->ceilingheight)
 {
     ds_p->silhouette |= 2;
     ds_p->tsilheight = frontsector->ceilingheight;
 }
 else if (backsector->ceilingheight < viewz)
 {
     ds_p->silhouette |= 2;
     ds_p->tsilheight = (-2147483647-1);

 }

 if (backsector->ceilingheight <= frontsector->floorheight)
 {
     ds_p->sprbottomclip = negonearray;
     ds_p->bsilheight = 2147483647;
     ds_p->silhouette |= 1;
 }

 if (backsector->floorheight >= frontsector->ceilingheight)
 {
     ds_p->sprtopclip = screenheightarray;
     ds_p->tsilheight = (-2147483647-1);
     ds_p->silhouette |= 2;
 }

 worldhigh = backsector->ceilingheight - viewz;
 worldlow = backsector->floorheight - viewz;


 if (frontsector->ceilingpic == skyflatnum
     && backsector->ceilingpic == skyflatnum)
 {
     worldtop = worldhigh;
 }


 if (worldlow != worldbottom
     || backsector->floorpic != frontsector->floorpic
     || backsector->lightlevel != frontsector->lightlevel)
 {
     markfloor = true;
 }
 else
 {

     markfloor = false;
 }


 if (worldhigh != worldtop
     || backsector->ceilingpic != frontsector->ceilingpic
     || backsector->lightlevel != frontsector->lightlevel)
 {
     markceiling = true;
 }
 else
 {

     markceiling = false;
 }

 if (backsector->ceilingheight <= frontsector->floorheight
     || backsector->floorheight >= frontsector->ceilingheight)
 {

     markceiling = markfloor = true;
 }


 if (worldhigh < worldtop)
 {

     toptexture = texturetranslation[sidedef->toptexture];
     if (linedef->flags & 8)
     {

  rw_toptexturemid = worldtop;
     }
     else
     {
  vtop =
      backsector->ceilingheight
      + textureheight[sidedef->toptexture];


  rw_toptexturemid = vtop - viewz;
     }
 }
 if (worldlow > worldbottom)
 {

     bottomtexture = texturetranslation[sidedef->bottomtexture];

     if (linedef->flags & 16 )
     {


  rw_bottomtexturemid = worldtop;
     }
     else
  rw_bottomtexturemid = worldlow;
 }
 rw_toptexturemid += sidedef->rowoffset;
 rw_bottomtexturemid += sidedef->rowoffset;


 if (sidedef->midtexture)
 {

     maskedtexture = true;
     ds_p->maskedtexturecol = maskedtexturecol = lastopening - rw_x;
     lastopening += rw_stopx - rw_x;
 }
    }


    segtextured = midtexture | toptexture | bottomtexture | maskedtexture;

    if (segtextured)
    {
 offsetangle = rw_normalangle-rw_angle1;

 if (offsetangle > 0x80000000)
     offsetangle = -offsetangle;

 if (offsetangle > 0x40000000)
     offsetangle = 0x40000000;

 sineval = finesine[offsetangle >>19];
 rw_offset = FixedMul (hyp, sineval);

 if (rw_normalangle-rw_angle1 < 0x80000000)
     rw_offset = -rw_offset;

 rw_offset += sidedef->textureoffset + curline->offset;
 rw_centerangle = 0x40000000 + viewangle - rw_normalangle;





 if (!fixedcolormap)
 {
     lightnum = (frontsector->lightlevel >> 4)+extralight;

     if (curline->v1->y == curline->v2->y)
  lightnum--;
     else if (curline->v1->x == curline->v2->x)
  lightnum++;

     if (lightnum < 0)
  walllights = scalelight[0];
     else if (lightnum >= 16)
  walllights = scalelight[16 -1];
     else
  walllights = scalelight[lightnum];
 }
    }






    if (frontsector->floorheight >= viewz)
    {

 markfloor = false;
    }

    if (frontsector->ceilingheight <= viewz
 && frontsector->ceilingpic != skyflatnum)
    {

 markceiling = false;
    }



    worldtop >>= 4;
    worldbottom >>= 4;

    topstep = -FixedMul (rw_scalestep, worldtop);
    topfrac = (centeryfrac>>4) - FixedMul (worldtop, rw_scale);

    bottomstep = -FixedMul (rw_scalestep,worldbottom);
    bottomfrac = (centeryfrac>>4) - FixedMul (worldbottom, rw_scale);

    if (backsector)
    {
 worldhigh >>= 4;
 worldlow >>= 4;

 if (worldhigh < worldtop)
 {
     pixhigh = (centeryfrac>>4) - FixedMul (worldhigh, rw_scale);
     pixhighstep = -FixedMul (rw_scalestep,worldhigh);
 }

 if (worldlow > worldbottom)
 {
     pixlow = (centeryfrac>>4) - FixedMul (worldlow, rw_scale);
     pixlowstep = -FixedMul (rw_scalestep,worldlow);
 }
    }


    if (markceiling)
 ceilingplane = R_CheckPlane (ceilingplane, rw_x, rw_stopx-1);

    if (markfloor)
 floorplane = R_CheckPlane (floorplane, rw_x, rw_stopx-1);

    R_RenderSegLoop ();



    if ( ((ds_p->silhouette & 2) || maskedtexture)
  && !ds_p->sprtopclip)
    {
 memcpy (lastopening, ceilingclip+start, 2*(rw_stopx-start));
 ds_p->sprtopclip = lastopening - start;
 lastopening += rw_stopx - start;
    }

    if ( ((ds_p->silhouette & 1) || maskedtexture)
  && !ds_p->sprbottomclip)
    {
 memcpy (lastopening, floorclip+start, 2*(rw_stopx-start));
 ds_p->sprbottomclip = lastopening - start;
 lastopening += rw_stopx - start;
    }

    if (maskedtexture && !(ds_p->silhouette&2))
    {
 ds_p->silhouette |= 2;
 ds_p->tsilheight = (-2147483647-1);
    }
    if (maskedtexture && !(ds_p->silhouette&1))
    {
 ds_p->silhouette |= 1;
 ds_p->bsilheight = 2147483647;
    }
    ds_p++;
}
int skyflatnum;
int skytexture;
int skytexturemid;







void R_InitSkyMap (void)
{

    skytexturemid = 100*(1<<16);
}
typedef struct
{
    int x1;
    int x2;

    int column;
    int topclip;
    int bottomclip;

} maskdraw_t;
fixed_t pspritescale;
fixed_t pspriteiscale;

lighttable_t** spritelights;



short negonearray[320];
short screenheightarray[320];
spritedef_t* sprites;
int numsprites;

spriteframe_t sprtemp[29];
int maxframe;
char* spritename;
void
R_InstallSpriteLump
( int lump,
  unsigned frame,
  unsigned rotation,
  boolean flipped )
{
    int r;

    if (frame >= 29 || rotation > 8)
 I_Error("R_InstallSpriteLump: "
  "Bad frame characters in lump %i", lump);

    if ((int)frame > maxframe)
 maxframe = frame;

    if (rotation == 0)
    {

 if (sprtemp[frame].rotate == false)
     I_Error ("R_InitSprites: Sprite %s frame %c has "
       "multip rot=0 lump", spritename, 'A'+frame);

 if (sprtemp[frame].rotate == true)
     I_Error ("R_InitSprites: Sprite %s frame %c has rotations "
       "and a rot=0 lump", spritename, 'A'+frame);

 sprtemp[frame].rotate = false;
 for (r=0 ; r<8 ; r++)
 {
     sprtemp[frame].lump[r] = lump - firstspritelump;
     sprtemp[frame].flip[r] = (byte)flipped;
 }
 return;
    }


    if (sprtemp[frame].rotate == false)
 I_Error ("R_InitSprites: Sprite %s frame %c has rotations "
   "and a rot=0 lump", spritename, 'A'+frame);

    sprtemp[frame].rotate = true;


    rotation--;
    if (sprtemp[frame].lump[rotation] != -1)
 I_Error ("R_InitSprites: Sprite %s : %c : %c "
   "has two lumps mapped to it",
   spritename, 'A'+frame, '1'+rotation);

    sprtemp[frame].lump[rotation] = lump - firstspritelump;
    sprtemp[frame].flip[rotation] = (byte)flipped;
}
void R_InitSpriteDefs (char** namelist)
{
    char** check;
    int i;
    int l;
    int frame;
    int rotation;
    int start;
    int end;
    int patched;


    check = namelist;
    while (*check != ((void*)0))
 check++;

    numsprites = check-namelist;

    if (!numsprites)
 return;

    sprites = Z_Malloc(numsprites *sizeof(*sprites), PU_STATIC, ((void*)0));

    start = firstspritelump-1;
    end = lastspritelump+1;




    for (i=0 ; i<numsprites ; i++)
    {
 spritename = (namelist[i]);
 memset (sprtemp,-1, sizeof(sprtemp));

 maxframe = -1;



 for (l=start+1 ; l<end ; l++)
 {
     if (!strncasecmp(lumpinfo[l].name, spritename, 4))
     {
  frame = lumpinfo[l].name[4] - 'A';
  rotation = lumpinfo[l].name[5] - '0';

  if (modifiedgame)
      patched = W_GetNumForName (lumpinfo[l].name);
  else
      patched = l;

  R_InstallSpriteLump (patched, frame, rotation, false);

  if (lumpinfo[l].name[6])
  {
      frame = lumpinfo[l].name[6] - 'A';
      rotation = lumpinfo[l].name[7] - '0';
      R_InstallSpriteLump (l, frame, rotation, true);
  }
     }
 }


 if (maxframe == -1)
 {
     sprites[i].numframes = 0;
     continue;
 }

 maxframe++;

 for (frame = 0 ; frame < maxframe ; frame++)
 {
     switch ((int)sprtemp[frame].rotate)
     {
       case -1:

  I_Error ("R_InitSprites: No patches found "
    "for %s frame %c", spritename, frame+'A');
  break;

       case 0:

  break;

       case 1:

  for (rotation=0 ; rotation<8 ; rotation++)
      if (sprtemp[frame].lump[rotation] == -1)
   I_Error ("R_InitSprites: Sprite %s frame %c "
     "is missing rotations",
     spritename, frame+'A');
  break;
     }
 }


 sprites[i].numframes = maxframe;
 sprites[i].spriteframes =
     Z_Malloc (maxframe * sizeof(spriteframe_t), PU_STATIC, ((void*)0));
 memcpy (sprites[i].spriteframes, sprtemp, maxframe*sizeof(spriteframe_t));
    }

}







vissprite_t vissprites[128];
vissprite_t* vissprite_p;
int newvissprite;







void R_InitSprites (char** namelist)
{
    int i;

    for (i=0 ; i<320 ; i++)
    {
 negonearray[i] = -1;
    }

    R_InitSpriteDefs (namelist);
}







void R_ClearSprites (void)
{
    vissprite_p = vissprites;
}





vissprite_t overflowsprite;

vissprite_t* R_NewVisSprite (void)
{
    if (vissprite_p == &vissprites[128])
 return &overflowsprite;

    vissprite_p++;
    return vissprite_p-1;
}
short* mfloorclip;
short* mceilingclip;

fixed_t spryscale;
fixed_t sprtopscreen;

void R_DrawMaskedColumn (column_t* column)
{
    int topscreen;
    int bottomscreen;
    fixed_t basetexturemid;

    basetexturemid = dc_texturemid;

    for ( ; column->topdelta != 0xff ; )
    {


 topscreen = sprtopscreen + spryscale*column->topdelta;
 bottomscreen = topscreen + spryscale*column->length;

 dc_yl = (topscreen+(1<<16)-1)>>16;
 dc_yh = (bottomscreen-1)>>16;

 if (dc_yh >= mfloorclip[dc_x])
     dc_yh = mfloorclip[dc_x]-1;
 if (dc_yl <= mceilingclip[dc_x])
     dc_yl = mceilingclip[dc_x]+1;

 if (dc_yl <= dc_yh)
 {
     dc_source = (byte *)column + 3;
     dc_texturemid = basetexturemid - (column->topdelta<<16);




     colfunc ();
 }
 column = (column_t *)( (byte *)column + column->length + 4);
    }

    dc_texturemid = basetexturemid;
}







void
R_DrawVisSprite
( vissprite_t* vis,
  int x1,
  int x2 )
{
    column_t* column;
    int texturecolumn;
    fixed_t frac;
    patch_t* patch;


    patch = W_CacheLumpNum (vis->patch+firstspritelump, PU_CACHE);

    dc_colormap = vis->colormap;

    if (!dc_colormap)
    {

 colfunc = fuzzcolfunc;
    }
    else if (vis->mobjflags & MF_TRANSLATION)
    {
 colfunc = transcolfunc;
 dc_translation = translationtables - 256 +
     ( (vis->mobjflags & MF_TRANSLATION) >> (MF_TRANSSHIFT-8) );
    }

    dc_iscale = abs(vis->xiscale)>>detailshift;
    dc_texturemid = vis->texturemid;
    frac = vis->startfrac;
    spryscale = vis->scale;
    sprtopscreen = centeryfrac - FixedMul(dc_texturemid,spryscale);

    for (dc_x=vis->x1 ; dc_x<=vis->x2 ; dc_x++, frac += vis->xiscale)
    {
 texturecolumn = frac>>16;

 if (texturecolumn < 0 || texturecolumn >= ((signed short) (patch->width)))
     I_Error ("R_DrawSpriteRange: bad texturecolumn");

 column = (column_t *) ((byte *)patch +
          ((signed int) (patch->columnofs[texturecolumn])));
 R_DrawMaskedColumn (column);
    }

    colfunc = basecolfunc;
}
void R_ProjectSprite (mobj_t* thing)
{
    fixed_t tr_x;
    fixed_t tr_y;

    fixed_t gxt;
    fixed_t gyt;

    fixed_t tx;
    fixed_t tz;

    fixed_t xscale;

    int x1;
    int x2;

    spritedef_t* sprdef;
    spriteframe_t* sprframe;
    int lump;

    unsigned rot;
    boolean flip;

    int index;

    vissprite_t* vis;

    angle_t ang;
    fixed_t iscale;


    tr_x = thing->x - viewx;
    tr_y = thing->y - viewy;

    gxt = FixedMul(tr_x,viewcos);
    gyt = -FixedMul(tr_y,viewsin);

    tz = gxt-gyt;


    if (tz < ((1<<16)*4))
 return;

    xscale = FixedDiv(projection, tz);

    gxt = -FixedMul(tr_x,viewsin);
    gyt = FixedMul(tr_y,viewcos);
    tx = -(gyt+gxt);


    if (abs(tx)>(tz<<2))
 return;



    if ((unsigned int) thing->sprite >= (unsigned int) numsprites)
 I_Error ("R_ProjectSprite: invalid sprite number %i ",
   thing->sprite);

    sprdef = &sprites[thing->sprite];

    if ( (thing->frame&0x7fff) >= sprdef->numframes )
 I_Error ("R_ProjectSprite: invalid sprite frame %i : %i ",
   thing->sprite, thing->frame);

    sprframe = &sprdef->spriteframes[ thing->frame & 0x7fff];

    if (sprframe->rotate)
    {

 ang = R_PointToAngle (thing->x, thing->y);
 rot = (ang-thing->angle+(unsigned)(0x20000000/2)*9)>>29;
 lump = sprframe->lump[rot];
 flip = (boolean)sprframe->flip[rot];
    }
    else
    {

 lump = sprframe->lump[0];
 flip = (boolean)sprframe->flip[0];
    }


    tx -= spriteoffset[lump];
    x1 = (centerxfrac + FixedMul (tx,xscale) ) >>16;


    if (x1 > viewwidth)
 return;

    tx += spritewidth[lump];
    x2 = ((centerxfrac + FixedMul (tx,xscale) ) >>16) - 1;


    if (x2 < 0)
 return;


    vis = R_NewVisSprite ();
    vis->mobjflags = thing->flags;
    vis->scale = xscale<<detailshift;
    vis->gx = thing->x;
    vis->gy = thing->y;
    vis->gz = thing->z;
    vis->gzt = thing->z + spritetopoffset[lump];
    vis->texturemid = vis->gzt - viewz;
    vis->x1 = x1 < 0 ? 0 : x1;
    vis->x2 = x2 >= viewwidth ? viewwidth-1 : x2;
    iscale = FixedDiv ((1<<16), xscale);

    if (flip)
    {
 vis->startfrac = spritewidth[lump]-1;
 vis->xiscale = -iscale;
    }
    else
    {
 vis->startfrac = 0;
 vis->xiscale = iscale;
    }

    if (vis->x1 > x1)
 vis->startfrac += vis->xiscale*(vis->x1-x1);
    vis->patch = lump;


    if (thing->flags & MF_SHADOW)
    {

 vis->colormap = ((void*)0);
    }
    else if (fixedcolormap)
    {

 vis->colormap = fixedcolormap;
    }
    else if (thing->frame & 0x8000)
    {

 vis->colormap = colormaps;
    }

    else
    {

 index = xscale>>(12 -detailshift);

 if (index >= 48)
     index = 48 -1;

 vis->colormap = spritelights[index];
    }
}
void R_AddSprites (sector_t* sec)
{
    mobj_t* thing;
    int lightnum;





    if (sec->validcount == validcount)
 return;


    sec->validcount = validcount;

    lightnum = (sec->lightlevel >> 4)+extralight;

    if (lightnum < 0)
 spritelights = scalelight[0];
    else if (lightnum >= 16)
 spritelights = scalelight[16 -1];
    else
 spritelights = scalelight[lightnum];


    for (thing = sec->thinglist ; thing ; thing = thing->snext)
 R_ProjectSprite (thing);
}





void R_DrawPSprite (pspdef_t* psp)
{
    fixed_t tx;
    int x1;
    int x2;
    spritedef_t* sprdef;
    spriteframe_t* sprframe;
    int lump;
    boolean flip;
    vissprite_t* vis;
    vissprite_t avis;



    if ( (unsigned)psp->state->sprite >= (unsigned int) numsprites)
 I_Error ("R_ProjectSprite: invalid sprite number %i ",
   psp->state->sprite);

    sprdef = &sprites[psp->state->sprite];

    if ( (psp->state->frame & 0x7fff) >= sprdef->numframes)
 I_Error ("R_ProjectSprite: invalid sprite frame %i : %i ",
   psp->state->sprite, psp->state->frame);

    sprframe = &sprdef->spriteframes[ psp->state->frame & 0x7fff ];

    lump = sprframe->lump[0];
    flip = (boolean)sprframe->flip[0];


    tx = psp->sx-160*(1<<16);

    tx -= spriteoffset[lump];
    x1 = (centerxfrac + FixedMul (tx,pspritescale) ) >>16;


    if (x1 > viewwidth)
 return;

    tx += spritewidth[lump];
    x2 = ((centerxfrac + FixedMul (tx, pspritescale) ) >>16) - 1;


    if (x2 < 0)
 return;


    vis = &avis;
    vis->mobjflags = 0;
    vis->texturemid = (100<<16)+(1<<16)/2-(psp->sy-spritetopoffset[lump]);
    vis->x1 = x1 < 0 ? 0 : x1;
    vis->x2 = x2 >= viewwidth ? viewwidth-1 : x2;
    vis->scale = pspritescale<<detailshift;

    if (flip)
    {
 vis->xiscale = -pspriteiscale;
 vis->startfrac = spritewidth[lump]-1;
    }
    else
    {
 vis->xiscale = pspriteiscale;
 vis->startfrac = 0;
    }

    if (vis->x1 > x1)
 vis->startfrac += vis->xiscale*(vis->x1-x1);

    vis->patch = lump;

    if (viewplayer->powers[pw_invisibility] > 4*32
 || viewplayer->powers[pw_invisibility] & 8)
    {

 vis->colormap = ((void*)0);
    }
    else if (fixedcolormap)
    {

 vis->colormap = fixedcolormap;
    }
    else if (psp->state->frame & 0x8000)
    {

 vis->colormap = colormaps;
    }
    else
    {

 vis->colormap = spritelights[48 -1];
    }

    R_DrawVisSprite (vis, vis->x1, vis->x2);
}






void R_DrawPlayerSprites (void)
{
    int i;
    int lightnum;
    pspdef_t* psp;


    lightnum =
 (viewplayer->mo->subsector->sector->lightlevel >> 4)
 +extralight;

    if (lightnum < 0)
 spritelights = scalelight[0];
    else if (lightnum >= 16)
 spritelights = scalelight[16 -1];
    else
 spritelights = scalelight[lightnum];


    mfloorclip = screenheightarray;
    mceilingclip = negonearray;


    for (i=0, psp=viewplayer->psprites;
  i<NUMPSPRITES;
  i++,psp++)
    {
 if (psp->state)
     R_DrawPSprite (psp);
    }
}







vissprite_t vsprsortedhead;


void R_SortVisSprites (void)
{
    int i;
    int count;
    vissprite_t* ds;
    vissprite_t* best;
    vissprite_t unsorted;
    fixed_t bestscale;

    count = vissprite_p - vissprites;

    unsorted.next = unsorted.prev = &unsorted;

    if (!count)
 return;

    for (ds=vissprites ; ds<vissprite_p ; ds++)
    {
 ds->next = ds+1;
 ds->prev = ds-1;
    }

    vissprites[0].prev = &unsorted;
    unsorted.next = &vissprites[0];
    (vissprite_p-1)->next = &unsorted;
    unsorted.prev = vissprite_p-1;



    vsprsortedhead.next = vsprsortedhead.prev = &vsprsortedhead;
    for (i=0 ; i<count ; i++)
    {
 bestscale = 2147483647;
        best = unsorted.next;
 for (ds=unsorted.next ; ds!= &unsorted ; ds=ds->next)
 {
     if (ds->scale < bestscale)
     {
  bestscale = ds->scale;
  best = ds;
     }
 }
 best->next->prev = best->prev;
 best->prev->next = best->next;
 best->next = &vsprsortedhead;
 best->prev = vsprsortedhead.prev;
 vsprsortedhead.prev->next = best;
 vsprsortedhead.prev = best;
    }
}






static short clipbot[320];
static short cliptop[320];
void R_DrawSprite (vissprite_t* spr)
{
    drawseg_t* ds;
    int x;
    int r1;
    int r2;
    fixed_t scale;
    fixed_t lowscale;
    int silhouette;

    for (x = spr->x1 ; x<=spr->x2 ; x++)
 clipbot[x] = cliptop[x] = -2;




    for (ds=ds_p-1 ; ds >= drawsegs ; ds--)
    {

 if (ds->x1 > spr->x2
     || ds->x2 < spr->x1
     || (!ds->silhouette
  && !ds->maskedtexturecol) )
 {

     continue;
 }

 r1 = ds->x1 < spr->x1 ? spr->x1 : ds->x1;
 r2 = ds->x2 > spr->x2 ? spr->x2 : ds->x2;

 if (ds->scale1 > ds->scale2)
 {
     lowscale = ds->scale2;
     scale = ds->scale1;
 }
 else
 {
     lowscale = ds->scale1;
     scale = ds->scale2;
 }

 if (scale < spr->scale
     || ( lowscale < spr->scale
   && !R_PointOnSegSide (spr->gx, spr->gy, ds->curline) ) )
 {

     if (ds->maskedtexturecol)
  R_RenderMaskedSegRange (ds, r1, r2);

     continue;
 }



 silhouette = ds->silhouette;

 if (spr->gz >= ds->bsilheight)
     silhouette &= ~1;

 if (spr->gzt <= ds->tsilheight)
     silhouette &= ~2;

 if (silhouette == 1)
 {

     for (x=r1 ; x<=r2 ; x++)
  if (clipbot[x] == -2)
      clipbot[x] = ds->sprbottomclip[x];
 }
 else if (silhouette == 2)
 {

     for (x=r1 ; x<=r2 ; x++)
  if (cliptop[x] == -2)
      cliptop[x] = ds->sprtopclip[x];
 }
 else if (silhouette == 3)
 {

     for (x=r1 ; x<=r2 ; x++)
     {
  if (clipbot[x] == -2)
      clipbot[x] = ds->sprbottomclip[x];
  if (cliptop[x] == -2)
      cliptop[x] = ds->sprtopclip[x];
     }
 }

    }




    for (x = spr->x1 ; x<=spr->x2 ; x++)
    {
 if (clipbot[x] == -2)
     clipbot[x] = viewheight;

 if (cliptop[x] == -2)
     cliptop[x] = -1;
    }

    mfloorclip = clipbot;
    mceilingclip = cliptop;
    R_DrawVisSprite (spr, spr->x1, spr->x2);
}







void R_DrawMasked (void)
{
    vissprite_t* spr;
    drawseg_t* ds;

    R_SortVisSprites ();

    if (vissprite_p > vissprites)
    {

 for (spr = vsprsortedhead.next ;
      spr != &vsprsortedhead ;
      spr=spr->next)
 {

     R_DrawSprite (spr);
 }
    }


    for (ds=ds_p-1 ; ds >= drawsegs ; ds--)
 if (ds->maskedtexturecol)
     R_RenderMaskedSegRange (ds, ds->x1, ds->x2);



    if (!viewangleoffset)
 R_DrawPlayerSprites ();
}
void SHA1_Init(sha1_context_t *hd)
{
    hd->h0 = 0x67452301;
    hd->h1 = 0xefcdab89;
    hd->h2 = 0x98badcfe;
    hd->h3 = 0x10325476;
    hd->h4 = 0xc3d2e1f0;
    hd->nblocks = 0;
    hd->count = 0;
}





static void Transform(sha1_context_t *hd, byte *data)
{
    uint32_t a,b,c,d,e,tm;
    uint32_t x[16];


    a = hd->h0;
    b = hd->h1;
    c = hd->h2;
    d = hd->h3;
    e = hd->h4;




    {
        int i;
        byte *p2;
        for(i=0, p2=(byte*)x; i < 16; i++, p2 += 4 )
        {
            p2[3] = *data++;
            p2[2] = *data++;
            p2[1] = *data++;
            p2[0] = *data++;
        }
    }
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( d ^ ( b & ( c ^ d ) ) ) + 0x5A827999L + x[ 0]; b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( c ^ ( a & ( b ^ c ) ) ) + 0x5A827999L + x[ 1]; a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( b ^ ( e & ( a ^ b ) ) ) + 0x5A827999L + x[ 2]; e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( a ^ ( d & ( e ^ a ) ) ) + 0x5A827999L + x[ 3]; d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( e ^ ( c & ( d ^ e ) ) ) + 0x5A827999L + x[ 4]; c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( d ^ ( b & ( c ^ d ) ) ) + 0x5A827999L + x[ 5]; b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( c ^ ( a & ( b ^ c ) ) ) + 0x5A827999L + x[ 6]; a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( b ^ ( e & ( a ^ b ) ) ) + 0x5A827999L + x[ 7]; e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( a ^ ( d & ( e ^ a ) ) ) + 0x5A827999L + x[ 8]; d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( e ^ ( c & ( d ^ e ) ) ) + 0x5A827999L + x[ 9]; c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( d ^ ( b & ( c ^ d ) ) ) + 0x5A827999L + x[10]; b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( c ^ ( a & ( b ^ c ) ) ) + 0x5A827999L + x[11]; a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( b ^ ( e & ( a ^ b ) ) ) + 0x5A827999L + x[12]; e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( a ^ ( d & ( e ^ a ) ) ) + 0x5A827999L + x[13]; d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( e ^ ( c & ( d ^ e ) ) ) + 0x5A827999L + x[14]; c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( d ^ ( b & ( c ^ d ) ) ) + 0x5A827999L + x[15]; b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( c ^ ( a & ( b ^ c ) ) ) + 0x5A827999L + ( tm = x[16&0x0f] ^ x[(16 -14)&0x0f] ^ x[(16 -8)&0x0f] ^ x[(16 -3)&0x0f] , (x[16&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( b ^ ( e & ( a ^ b ) ) ) + 0x5A827999L + ( tm = x[17&0x0f] ^ x[(17 -14)&0x0f] ^ x[(17 -8)&0x0f] ^ x[(17 -3)&0x0f] , (x[17&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( a ^ ( d & ( e ^ a ) ) ) + 0x5A827999L + ( tm = x[18&0x0f] ^ x[(18 -14)&0x0f] ^ x[(18 -8)&0x0f] ^ x[(18 -3)&0x0f] , (x[18&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( e ^ ( c & ( d ^ e ) ) ) + 0x5A827999L + ( tm = x[19&0x0f] ^ x[(19 -14)&0x0f] ^ x[(19 -8)&0x0f] ^ x[(19 -3)&0x0f] , (x[19&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( b ^ c ^ d ) + 0x6ED9EBA1L + ( tm = x[20&0x0f] ^ x[(20 -14)&0x0f] ^ x[(20 -8)&0x0f] ^ x[(20 -3)&0x0f] , (x[20&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( a ^ b ^ c ) + 0x6ED9EBA1L + ( tm = x[21&0x0f] ^ x[(21 -14)&0x0f] ^ x[(21 -8)&0x0f] ^ x[(21 -3)&0x0f] , (x[21&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( e ^ a ^ b ) + 0x6ED9EBA1L + ( tm = x[22&0x0f] ^ x[(22 -14)&0x0f] ^ x[(22 -8)&0x0f] ^ x[(22 -3)&0x0f] , (x[22&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( d ^ e ^ a ) + 0x6ED9EBA1L + ( tm = x[23&0x0f] ^ x[(23 -14)&0x0f] ^ x[(23 -8)&0x0f] ^ x[(23 -3)&0x0f] , (x[23&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( c ^ d ^ e ) + 0x6ED9EBA1L + ( tm = x[24&0x0f] ^ x[(24 -14)&0x0f] ^ x[(24 -8)&0x0f] ^ x[(24 -3)&0x0f] , (x[24&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( b ^ c ^ d ) + 0x6ED9EBA1L + ( tm = x[25&0x0f] ^ x[(25 -14)&0x0f] ^ x[(25 -8)&0x0f] ^ x[(25 -3)&0x0f] , (x[25&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( a ^ b ^ c ) + 0x6ED9EBA1L + ( tm = x[26&0x0f] ^ x[(26 -14)&0x0f] ^ x[(26 -8)&0x0f] ^ x[(26 -3)&0x0f] , (x[26&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( e ^ a ^ b ) + 0x6ED9EBA1L + ( tm = x[27&0x0f] ^ x[(27 -14)&0x0f] ^ x[(27 -8)&0x0f] ^ x[(27 -3)&0x0f] , (x[27&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( d ^ e ^ a ) + 0x6ED9EBA1L + ( tm = x[28&0x0f] ^ x[(28 -14)&0x0f] ^ x[(28 -8)&0x0f] ^ x[(28 -3)&0x0f] , (x[28&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( c ^ d ^ e ) + 0x6ED9EBA1L + ( tm = x[29&0x0f] ^ x[(29 -14)&0x0f] ^ x[(29 -8)&0x0f] ^ x[(29 -3)&0x0f] , (x[29&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( b ^ c ^ d ) + 0x6ED9EBA1L + ( tm = x[30&0x0f] ^ x[(30 -14)&0x0f] ^ x[(30 -8)&0x0f] ^ x[(30 -3)&0x0f] , (x[30&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( a ^ b ^ c ) + 0x6ED9EBA1L + ( tm = x[31&0x0f] ^ x[(31 -14)&0x0f] ^ x[(31 -8)&0x0f] ^ x[(31 -3)&0x0f] , (x[31&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( e ^ a ^ b ) + 0x6ED9EBA1L + ( tm = x[32&0x0f] ^ x[(32 -14)&0x0f] ^ x[(32 -8)&0x0f] ^ x[(32 -3)&0x0f] , (x[32&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( d ^ e ^ a ) + 0x6ED9EBA1L + ( tm = x[33&0x0f] ^ x[(33 -14)&0x0f] ^ x[(33 -8)&0x0f] ^ x[(33 -3)&0x0f] , (x[33&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( c ^ d ^ e ) + 0x6ED9EBA1L + ( tm = x[34&0x0f] ^ x[(34 -14)&0x0f] ^ x[(34 -8)&0x0f] ^ x[(34 -3)&0x0f] , (x[34&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( b ^ c ^ d ) + 0x6ED9EBA1L + ( tm = x[35&0x0f] ^ x[(35 -14)&0x0f] ^ x[(35 -8)&0x0f] ^ x[(35 -3)&0x0f] , (x[35&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( a ^ b ^ c ) + 0x6ED9EBA1L + ( tm = x[36&0x0f] ^ x[(36 -14)&0x0f] ^ x[(36 -8)&0x0f] ^ x[(36 -3)&0x0f] , (x[36&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( e ^ a ^ b ) + 0x6ED9EBA1L + ( tm = x[37&0x0f] ^ x[(37 -14)&0x0f] ^ x[(37 -8)&0x0f] ^ x[(37 -3)&0x0f] , (x[37&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( d ^ e ^ a ) + 0x6ED9EBA1L + ( tm = x[38&0x0f] ^ x[(38 -14)&0x0f] ^ x[(38 -8)&0x0f] ^ x[(38 -3)&0x0f] , (x[38&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( c ^ d ^ e ) + 0x6ED9EBA1L + ( tm = x[39&0x0f] ^ x[(39 -14)&0x0f] ^ x[(39 -8)&0x0f] ^ x[(39 -3)&0x0f] , (x[39&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( ( b & c ) | ( d & ( b | c ) ) ) + 0x8F1BBCDCL + ( tm = x[40&0x0f] ^ x[(40 -14)&0x0f] ^ x[(40 -8)&0x0f] ^ x[(40 -3)&0x0f] , (x[40&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( ( a & b ) | ( c & ( a | b ) ) ) + 0x8F1BBCDCL + ( tm = x[41&0x0f] ^ x[(41 -14)&0x0f] ^ x[(41 -8)&0x0f] ^ x[(41 -3)&0x0f] , (x[41&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( ( e & a ) | ( b & ( e | a ) ) ) + 0x8F1BBCDCL + ( tm = x[42&0x0f] ^ x[(42 -14)&0x0f] ^ x[(42 -8)&0x0f] ^ x[(42 -3)&0x0f] , (x[42&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( ( d & e ) | ( a & ( d | e ) ) ) + 0x8F1BBCDCL + ( tm = x[43&0x0f] ^ x[(43 -14)&0x0f] ^ x[(43 -8)&0x0f] ^ x[(43 -3)&0x0f] , (x[43&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( ( c & d ) | ( e & ( c | d ) ) ) + 0x8F1BBCDCL + ( tm = x[44&0x0f] ^ x[(44 -14)&0x0f] ^ x[(44 -8)&0x0f] ^ x[(44 -3)&0x0f] , (x[44&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( ( b & c ) | ( d & ( b | c ) ) ) + 0x8F1BBCDCL + ( tm = x[45&0x0f] ^ x[(45 -14)&0x0f] ^ x[(45 -8)&0x0f] ^ x[(45 -3)&0x0f] , (x[45&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( ( a & b ) | ( c & ( a | b ) ) ) + 0x8F1BBCDCL + ( tm = x[46&0x0f] ^ x[(46 -14)&0x0f] ^ x[(46 -8)&0x0f] ^ x[(46 -3)&0x0f] , (x[46&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( ( e & a ) | ( b & ( e | a ) ) ) + 0x8F1BBCDCL + ( tm = x[47&0x0f] ^ x[(47 -14)&0x0f] ^ x[(47 -8)&0x0f] ^ x[(47 -3)&0x0f] , (x[47&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( ( d & e ) | ( a & ( d | e ) ) ) + 0x8F1BBCDCL + ( tm = x[48&0x0f] ^ x[(48 -14)&0x0f] ^ x[(48 -8)&0x0f] ^ x[(48 -3)&0x0f] , (x[48&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( ( c & d ) | ( e & ( c | d ) ) ) + 0x8F1BBCDCL + ( tm = x[49&0x0f] ^ x[(49 -14)&0x0f] ^ x[(49 -8)&0x0f] ^ x[(49 -3)&0x0f] , (x[49&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( ( b & c ) | ( d & ( b | c ) ) ) + 0x8F1BBCDCL + ( tm = x[50&0x0f] ^ x[(50 -14)&0x0f] ^ x[(50 -8)&0x0f] ^ x[(50 -3)&0x0f] , (x[50&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( ( a & b ) | ( c & ( a | b ) ) ) + 0x8F1BBCDCL + ( tm = x[51&0x0f] ^ x[(51 -14)&0x0f] ^ x[(51 -8)&0x0f] ^ x[(51 -3)&0x0f] , (x[51&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( ( e & a ) | ( b & ( e | a ) ) ) + 0x8F1BBCDCL + ( tm = x[52&0x0f] ^ x[(52 -14)&0x0f] ^ x[(52 -8)&0x0f] ^ x[(52 -3)&0x0f] , (x[52&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( ( d & e ) | ( a & ( d | e ) ) ) + 0x8F1BBCDCL + ( tm = x[53&0x0f] ^ x[(53 -14)&0x0f] ^ x[(53 -8)&0x0f] ^ x[(53 -3)&0x0f] , (x[53&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( ( c & d ) | ( e & ( c | d ) ) ) + 0x8F1BBCDCL + ( tm = x[54&0x0f] ^ x[(54 -14)&0x0f] ^ x[(54 -8)&0x0f] ^ x[(54 -3)&0x0f] , (x[54&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( ( b & c ) | ( d & ( b | c ) ) ) + 0x8F1BBCDCL + ( tm = x[55&0x0f] ^ x[(55 -14)&0x0f] ^ x[(55 -8)&0x0f] ^ x[(55 -3)&0x0f] , (x[55&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( ( a & b ) | ( c & ( a | b ) ) ) + 0x8F1BBCDCL + ( tm = x[56&0x0f] ^ x[(56 -14)&0x0f] ^ x[(56 -8)&0x0f] ^ x[(56 -3)&0x0f] , (x[56&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( ( e & a ) | ( b & ( e | a ) ) ) + 0x8F1BBCDCL + ( tm = x[57&0x0f] ^ x[(57 -14)&0x0f] ^ x[(57 -8)&0x0f] ^ x[(57 -3)&0x0f] , (x[57&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( ( d & e ) | ( a & ( d | e ) ) ) + 0x8F1BBCDCL + ( tm = x[58&0x0f] ^ x[(58 -14)&0x0f] ^ x[(58 -8)&0x0f] ^ x[(58 -3)&0x0f] , (x[58&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( ( c & d ) | ( e & ( c | d ) ) ) + 0x8F1BBCDCL + ( tm = x[59&0x0f] ^ x[(59 -14)&0x0f] ^ x[(59 -8)&0x0f] ^ x[(59 -3)&0x0f] , (x[59&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( b ^ c ^ d ) + 0xCA62C1D6L + ( tm = x[60&0x0f] ^ x[(60 -14)&0x0f] ^ x[(60 -8)&0x0f] ^ x[(60 -3)&0x0f] , (x[60&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( a ^ b ^ c ) + 0xCA62C1D6L + ( tm = x[61&0x0f] ^ x[(61 -14)&0x0f] ^ x[(61 -8)&0x0f] ^ x[(61 -3)&0x0f] , (x[61&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( e ^ a ^ b ) + 0xCA62C1D6L + ( tm = x[62&0x0f] ^ x[(62 -14)&0x0f] ^ x[(62 -8)&0x0f] ^ x[(62 -3)&0x0f] , (x[62&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( d ^ e ^ a ) + 0xCA62C1D6L + ( tm = x[63&0x0f] ^ x[(63 -14)&0x0f] ^ x[(63 -8)&0x0f] ^ x[(63 -3)&0x0f] , (x[63&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( c ^ d ^ e ) + 0xCA62C1D6L + ( tm = x[64&0x0f] ^ x[(64 -14)&0x0f] ^ x[(64 -8)&0x0f] ^ x[(64 -3)&0x0f] , (x[64&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( b ^ c ^ d ) + 0xCA62C1D6L + ( tm = x[65&0x0f] ^ x[(65 -14)&0x0f] ^ x[(65 -8)&0x0f] ^ x[(65 -3)&0x0f] , (x[65&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( a ^ b ^ c ) + 0xCA62C1D6L + ( tm = x[66&0x0f] ^ x[(66 -14)&0x0f] ^ x[(66 -8)&0x0f] ^ x[(66 -3)&0x0f] , (x[66&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( e ^ a ^ b ) + 0xCA62C1D6L + ( tm = x[67&0x0f] ^ x[(67 -14)&0x0f] ^ x[(67 -8)&0x0f] ^ x[(67 -3)&0x0f] , (x[67&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( d ^ e ^ a ) + 0xCA62C1D6L + ( tm = x[68&0x0f] ^ x[(68 -14)&0x0f] ^ x[(68 -8)&0x0f] ^ x[(68 -3)&0x0f] , (x[68&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( c ^ d ^ e ) + 0xCA62C1D6L + ( tm = x[69&0x0f] ^ x[(69 -14)&0x0f] ^ x[(69 -8)&0x0f] ^ x[(69 -3)&0x0f] , (x[69&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( b ^ c ^ d ) + 0xCA62C1D6L + ( tm = x[70&0x0f] ^ x[(70 -14)&0x0f] ^ x[(70 -8)&0x0f] ^ x[(70 -3)&0x0f] , (x[70&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( a ^ b ^ c ) + 0xCA62C1D6L + ( tm = x[71&0x0f] ^ x[(71 -14)&0x0f] ^ x[(71 -8)&0x0f] ^ x[(71 -3)&0x0f] , (x[71&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( e ^ a ^ b ) + 0xCA62C1D6L + ( tm = x[72&0x0f] ^ x[(72 -14)&0x0f] ^ x[(72 -8)&0x0f] ^ x[(72 -3)&0x0f] , (x[72&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( d ^ e ^ a ) + 0xCA62C1D6L + ( tm = x[73&0x0f] ^ x[(73 -14)&0x0f] ^ x[(73 -8)&0x0f] ^ x[(73 -3)&0x0f] , (x[73&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( c ^ d ^ e ) + 0xCA62C1D6L + ( tm = x[74&0x0f] ^ x[(74 -14)&0x0f] ^ x[(74 -8)&0x0f] ^ x[(74 -3)&0x0f] , (x[74&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);
    do { e += ( ((a) << (5)) | ((a) >> (32-(5))) ) + ( b ^ c ^ d ) + 0xCA62C1D6L + ( tm = x[75&0x0f] ^ x[(75 -14)&0x0f] ^ x[(75 -8)&0x0f] ^ x[(75 -3)&0x0f] , (x[75&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); b = ( ((b) << (30)) | ((b) >> (32-(30))) ); } while(0);
    do { d += ( ((e) << (5)) | ((e) >> (32-(5))) ) + ( a ^ b ^ c ) + 0xCA62C1D6L + ( tm = x[76&0x0f] ^ x[(76 -14)&0x0f] ^ x[(76 -8)&0x0f] ^ x[(76 -3)&0x0f] , (x[76&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); a = ( ((a) << (30)) | ((a) >> (32-(30))) ); } while(0);
    do { c += ( ((d) << (5)) | ((d) >> (32-(5))) ) + ( e ^ a ^ b ) + 0xCA62C1D6L + ( tm = x[77&0x0f] ^ x[(77 -14)&0x0f] ^ x[(77 -8)&0x0f] ^ x[(77 -3)&0x0f] , (x[77&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); e = ( ((e) << (30)) | ((e) >> (32-(30))) ); } while(0);
    do { b += ( ((c) << (5)) | ((c) >> (32-(5))) ) + ( d ^ e ^ a ) + 0xCA62C1D6L + ( tm = x[78&0x0f] ^ x[(78 -14)&0x0f] ^ x[(78 -8)&0x0f] ^ x[(78 -3)&0x0f] , (x[78&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); d = ( ((d) << (30)) | ((d) >> (32-(30))) ); } while(0);
    do { a += ( ((b) << (5)) | ((b) >> (32-(5))) ) + ( c ^ d ^ e ) + 0xCA62C1D6L + ( tm = x[79&0x0f] ^ x[(79 -14)&0x0f] ^ x[(79 -8)&0x0f] ^ x[(79 -3)&0x0f] , (x[79&0x0f] = ( ((tm) << (1)) | ((tm) >> (32-(1))) )) ); c = ( ((c) << (30)) | ((c) >> (32-(30))) ); } while(0);


    hd->h0 += a;
    hd->h1 += b;
    hd->h2 += c;
    hd->h3 += d;
    hd->h4 += e;
}





void SHA1_Update(sha1_context_t *hd, byte *inbuf, size_t inlen)
{
    if (hd->count == 64)
    {

 Transform(hd, hd->buf);
 hd->count = 0;
 hd->nblocks++;
    }
    if (!inbuf)
 return;
    if (hd->count)
    {
 for (; inlen && hd->count < 64; inlen--)
     hd->buf[hd->count++] = *inbuf++;
 SHA1_Update(hd, ((void*)0), 0);
 if (!inlen)
     return;
    }

    while (inlen >= 64)
    {
 Transform(hd, inbuf);
 hd->count = 0;
 hd->nblocks++;
 inlen -= 64;
 inbuf += 64;
    }
    for (; inlen && hd->count < 64; inlen--)
 hd->buf[hd->count++] = *inbuf++;
}
void SHA1_Final(sha1_digest_t digest, sha1_context_t *hd)
{
    uint32_t t, msb, lsb;
    byte *p;

    SHA1_Update(hd, ((void*)0), 0); ;

    t = hd->nblocks;

    lsb = t << 6;
    msb = t >> 26;

    t = lsb;
    if ((lsb += hd->count) < t)
 msb++;

    t = lsb;
    lsb <<= 3;
    msb <<= 3;
    msb |= t >> 29;

    if (hd->count < 56)
    {

 hd->buf[hd->count++] = 0x80;
 while (hd->count < 56)
     hd->buf[hd->count++] = 0;
    }
    else
    {

 hd->buf[hd->count++] = 0x80;
 while (hd->count < 64)
     hd->buf[hd->count++] = 0;
 SHA1_Update(hd, ((void*)0), 0); ;
 memset(hd->buf, 0, 56 );
    }

    hd->buf[56] = msb >> 24;
    hd->buf[57] = msb >> 16;
    hd->buf[58] = msb >> 8;
    hd->buf[59] = msb ;
    hd->buf[60] = lsb >> 24;
    hd->buf[61] = lsb >> 16;
    hd->buf[62] = lsb >> 8;
    hd->buf[63] = lsb ;
    Transform(hd, hd->buf);

    p = hd->buf;






    do { *p++ = hd->h0 >> 24; *p++ = hd->h0 >> 16; *p++ = hd->h0 >> 8; *p++ = hd->h0; } while(0);
    do { *p++ = hd->h1 >> 24; *p++ = hd->h1 >> 16; *p++ = hd->h1 >> 8; *p++ = hd->h1; } while(0);
    do { *p++ = hd->h2 >> 24; *p++ = hd->h2 >> 16; *p++ = hd->h2 >> 8; *p++ = hd->h2; } while(0);
    do { *p++ = hd->h3 >> 24; *p++ = hd->h3 >> 16; *p++ = hd->h3 >> 8; *p++ = hd->h3; } while(0);
    do { *p++ = hd->h4 >> 24; *p++ = hd->h4 >> 16; *p++ = hd->h4 >> 8; *p++ = hd->h4; } while(0);


    memcpy(digest, hd->buf, sizeof(sha1_digest_t));
}

void SHA1_UpdateInt32(sha1_context_t *context, unsigned int val)
{
    byte buf[4];

    buf[0] = (val >> 24) & 0xff;
    buf[1] = (val >> 16) & 0xff;
    buf[2] = (val >> 8) & 0xff;
    buf[3] = val & 0xff;

    SHA1_Update(context, buf, 4);
}

void SHA1_UpdateString(sha1_context_t *context, char *str)
{
    SHA1_Update(context, (byte *) str, strlen(str) + 1);
}
musicinfo_t S_music[] =
{
    { ((void*)0), 0, ((void*)0), ((void*)0) },
    { "e1m1", 0, ((void*)0), ((void*)0) },
    { "e1m2", 0, ((void*)0), ((void*)0) },
    { "e1m3", 0, ((void*)0), ((void*)0) },
    { "e1m4", 0, ((void*)0), ((void*)0) },
    { "e1m5", 0, ((void*)0), ((void*)0) },
    { "e1m6", 0, ((void*)0), ((void*)0) },
    { "e1m7", 0, ((void*)0), ((void*)0) },
    { "e1m8", 0, ((void*)0), ((void*)0) },
    { "e1m9", 0, ((void*)0), ((void*)0) },
    { "e2m1", 0, ((void*)0), ((void*)0) },
    { "e2m2", 0, ((void*)0), ((void*)0) },
    { "e2m3", 0, ((void*)0), ((void*)0) },
    { "e2m4", 0, ((void*)0), ((void*)0) },
    { "e2m5", 0, ((void*)0), ((void*)0) },
    { "e2m6", 0, ((void*)0), ((void*)0) },
    { "e2m7", 0, ((void*)0), ((void*)0) },
    { "e2m8", 0, ((void*)0), ((void*)0) },
    { "e2m9", 0, ((void*)0), ((void*)0) },
    { "e3m1", 0, ((void*)0), ((void*)0) },
    { "e3m2", 0, ((void*)0), ((void*)0) },
    { "e3m3", 0, ((void*)0), ((void*)0) },
    { "e3m4", 0, ((void*)0), ((void*)0) },
    { "e3m5", 0, ((void*)0), ((void*)0) },
    { "e3m6", 0, ((void*)0), ((void*)0) },
    { "e3m7", 0, ((void*)0), ((void*)0) },
    { "e3m8", 0, ((void*)0), ((void*)0) },
    { "e3m9", 0, ((void*)0), ((void*)0) },
    { "inter", 0, ((void*)0), ((void*)0) },
    { "intro", 0, ((void*)0), ((void*)0) },
    { "bunny", 0, ((void*)0), ((void*)0) },
    { "victor", 0, ((void*)0), ((void*)0) },
    { "introa", 0, ((void*)0), ((void*)0) },
    { "runnin", 0, ((void*)0), ((void*)0) },
    { "stalks", 0, ((void*)0), ((void*)0) },
    { "countd", 0, ((void*)0), ((void*)0) },
    { "betwee", 0, ((void*)0), ((void*)0) },
    { "doom", 0, ((void*)0), ((void*)0) },
    { "the_da", 0, ((void*)0), ((void*)0) },
    { "shawn", 0, ((void*)0), ((void*)0) },
    { "ddtblu", 0, ((void*)0), ((void*)0) },
    { "in_cit", 0, ((void*)0), ((void*)0) },
    { "dead", 0, ((void*)0), ((void*)0) },
    { "stlks2", 0, ((void*)0), ((void*)0) },
    { "theda2", 0, ((void*)0), ((void*)0) },
    { "doom2", 0, ((void*)0), ((void*)0) },
    { "ddtbl2", 0, ((void*)0), ((void*)0) },
    { "runni2", 0, ((void*)0), ((void*)0) },
    { "dead2", 0, ((void*)0), ((void*)0) },
    { "stlks3", 0, ((void*)0), ((void*)0) },
    { "romero", 0, ((void*)0), ((void*)0) },
    { "shawn2", 0, ((void*)0), ((void*)0) },
    { "messag", 0, ((void*)0), ((void*)0) },
    { "count2", 0, ((void*)0), ((void*)0) },
    { "ddtbl3", 0, ((void*)0), ((void*)0) },
    { "ampie", 0, ((void*)0), ((void*)0) },
    { "theda3", 0, ((void*)0), ((void*)0) },
    { "adrian", 0, ((void*)0), ((void*)0) },
    { "messg2", 0, ((void*)0), ((void*)0) },
    { "romer2", 0, ((void*)0), ((void*)0) },
    { "tense", 0, ((void*)0), ((void*)0) },
    { "shawn3", 0, ((void*)0), ((void*)0) },
    { "openin", 0, ((void*)0), ((void*)0) },
    { "evil", 0, ((void*)0), ((void*)0) },
    { "ultima", 0, ((void*)0), ((void*)0) },
    { "read_m", 0, ((void*)0), ((void*)0) },
    { "dm2ttl", 0, ((void*)0), ((void*)0) },
    { "dm2int", 0, ((void*)0), ((void*)0) }
};
sfxinfo_t S_sfx[] =
{

  { ((void*)0), "none", 0, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "pistol", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "shotgn", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "sgcock", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "dshtgn", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "dbopn", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "dbcls", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "dbload", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "plasma", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bfg", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "sawup", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "sawidl", 118, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "sawful", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "sawhit", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "rlaunc", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "rxplod", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "firsht", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "firxpl", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "pstart", 100, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "pstop", 100, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "doropn", 100, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "dorcls", 100, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "stnmov", 119, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "swtchn", 78, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "swtchx", 78, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "plpain", 96, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "dmpain", 96, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "popain", 96, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "vipain", 96, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "mnpain", 96, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "pepain", 96, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "slop", 78, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "itemup", 78, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "wpnup", 78, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "oof", 96, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "telept", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "posit1", 98, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "posit2", 98, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "posit3", 98, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bgsit1", 98, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bgsit2", 98, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "sgtsit", 98, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "cacsit", 98, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "brssit", 94, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "cybsit", 92, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "spisit", 90, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bspsit", 90, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "kntsit", 90, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "vilsit", 90, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "mansit", 90, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "pesit", 90, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "sklatk", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "sgtatk", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "skepch", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "vilatk", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "claw", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "skeswg", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "pldeth", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "pdiehi", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "podth1", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "podth2", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "podth3", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bgdth1", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bgdth2", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "sgtdth", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "cacdth", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "skldth", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "brsdth", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "cybdth", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "spidth", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bspdth", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "vildth", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "kntdth", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "pedth", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "skedth", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "posact", 120, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bgact", 120, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "dmact", 120, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bspact", 100, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bspwlk", 100, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "vilact", 100, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "noway", 78, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "barexp", 60, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "punch", 64, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "hoof", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "metal", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "chgun", 64, &S_sfx[sfx_pistol], 150, 0, 0, 0, -1, ((void*)0) },
  { ((void*)0), "tink", 60, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bdopn", 100, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bdcls", 100, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "itmbk", 100, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "flame", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "flamst", 32, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "getpow", 60, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bospit", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "boscub", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bossit", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bospn", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "bosdth", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "manatk", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "mandth", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "sssit", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "ssdth", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "keenpn", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "keendt", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "skeact", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "skesit", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "skeatk", 70, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
  { ((void*)0), "radio", 60, ((void*)0), -1, -1, 0, 0, -1, ((void*)0) },
};
static const int doom1_par_times[] =
{
    30, 75, 120, 90, 165, 180, 180, 30, 165,
};


static const int doom2_par_times[] =
{
    30, 90, 120, 120, 90, 150, 120, 120, 270,
};
static wbstartstruct_t captured_stats[32];
static int num_captured_stats = 0;
void StatCopy(wbstartstruct_t *stats)
{
    if (M_ParmExists("-statdump") && num_captured_stats < 32)
    {
        memcpy(&captured_stats[num_captured_stats], stats,
               sizeof(wbstartstruct_t));
        ++num_captured_stats;
    }
}

void StatDump(void)
{
}
typedef struct
{


    int x;
    int y;


    int width;


    int oldnum;


    int* num;



    boolean* on;


    patch_t** p;


    int data;

} st_number_t;





typedef struct
{

    st_number_t n;


    patch_t* p;

} st_percent_t;




typedef struct
{

    int x;
    int y;


    int oldinum;


    int* inum;



    boolean* on;


    patch_t** p;


    int data;

} st_multicon_t;






typedef struct
{

    int x;
    int y;


    boolean oldval;


    boolean* val;



    boolean* on;


    patch_t* p;
    int data;

} st_binicon_t;
void STlib_init(void);




void
STlib_initNum
( st_number_t* n,
  int x,
  int y,
  patch_t** pl,
  int* num,
  boolean* on,
  int width );

void
STlib_updateNum
( st_number_t* n,
  boolean refresh );



void
STlib_initPercent
( st_percent_t* p,
  int x,
  int y,
  patch_t** pl,
  int* num,
  boolean* on,
  patch_t* percent );


void
STlib_updatePercent
( st_percent_t* per,
  int refresh );



void
STlib_initMultIcon
( st_multicon_t* mi,
  int x,
  int y,
  patch_t** il,
  int* inum,
  boolean* on );


void
STlib_updateMultIcon
( st_multicon_t* mi,
  boolean refresh );



void
STlib_initBinIcon
( st_binicon_t* b,
  int x,
  int y,
  patch_t* i,
  boolean* val,
  boolean* on );

void
STlib_updateBinIcon
( st_binicon_t* bi,
  boolean refresh );




extern boolean automapactive;
patch_t* sttminus;

void STlib_init(void)
{
    sttminus = (patch_t *) W_CacheLumpName(("STTMINUS"), PU_STATIC);
}



void
STlib_initNum
( st_number_t* n,
  int x,
  int y,
  patch_t** pl,
  int* num,
  boolean* on,
  int width )
{
    n->x = x;
    n->y = y;
    n->oldnum = 0;
    n->width = width;
    n->num = num;
    n->on = on;
    n->p = pl;
}







void
STlib_drawNum
( st_number_t* n,
  boolean refresh )
{

    int numdigits = n->width;
    int num = *n->num;

    int w = ((signed short) (n->p[0]->width));
    int h = ((signed short) (n->p[0]->height));
    int x = n->x;

    int neg;

    n->oldnum = *n->num;

    neg = num < 0;

    if (neg)
    {
 if (numdigits == 2 && num < -9)
     num = -9;
 else if (numdigits == 3 && num < -99)
     num = -99;

 num = -num;
    }


    x = n->x - numdigits*w;

    if (n->y - (200 - 32) < 0)
 I_Error("drawNum: n->y - ST_Y < 0");

    V_CopyRect(x, n->y - (200 - 32), st_backing_screen, w*numdigits, h, x, n->y);


    if (num == 1994)
 return;

    x = n->x;


    if (!num)
 V_DrawPatch(x - w, n->y, n->p[ 0 ]);


    while (num && numdigits--)
    {
 x -= w;
 V_DrawPatch(x, n->y, n->p[ num % 10 ]);
 num /= 10;
    }


    if (neg)
 V_DrawPatch(x - 8, n->y, sttminus);
}



void
STlib_updateNum
( st_number_t* n,
  boolean refresh )
{
    if (*n->on) STlib_drawNum(n, refresh);
}



void
STlib_initPercent
( st_percent_t* p,
  int x,
  int y,
  patch_t** pl,
  int* num,
  boolean* on,
  patch_t* percent )
{
    STlib_initNum(&p->n, x, y, pl, num, on, 3);
    p->p = percent;
}




void
STlib_updatePercent
( st_percent_t* per,
  int refresh )
{
    if (refresh && *per->n.on)
 V_DrawPatch(per->n.x, per->n.y, per->p);

    STlib_updateNum(&per->n, refresh);
}



void
STlib_initMultIcon
( st_multicon_t* i,
  int x,
  int y,
  patch_t** il,
  int* inum,
  boolean* on )
{
    i->x = x;
    i->y = y;
    i->oldinum = -1;
    i->inum = inum;
    i->on = on;
    i->p = il;
}



void
STlib_updateMultIcon
( st_multicon_t* mi,
  boolean refresh )
{
    int w;
    int h;
    int x;
    int y;

    if (*mi->on && (mi->oldinum != *mi->inum || refresh) && (*mi->inum != -1))
    {
 if (mi->oldinum != -1)
 {
     x = mi->x - ((signed short) (mi->p[mi->oldinum]->leftoffset));
     y = mi->y - ((signed short) (mi->p[mi->oldinum]->topoffset));
     w = ((signed short) (mi->p[mi->oldinum]->width));
     h = ((signed short) (mi->p[mi->oldinum]->height));

     if (y - (200 - 32) < 0)
  I_Error("updateMultIcon: y - ST_Y < 0");

     V_CopyRect(x, y-(200 - 32), st_backing_screen, w, h, x, y);
 }
 V_DrawPatch(mi->x, mi->y, mi->p[*mi->inum]);
 mi->oldinum = *mi->inum;
    }
}



void
STlib_initBinIcon
( st_binicon_t* b,
  int x,
  int y,
  patch_t* i,
  boolean* val,
  boolean* on )
{
    b->x = x;
    b->y = y;
    b->oldval = false;
    b->val = val;
    b->on = on;
    b->p = i;
}



void
STlib_updateBinIcon
( st_binicon_t* bi,
  boolean refresh )
{
    int x;
    int y;
    int w;
    int h;

    if (*bi->on
     && (bi->oldval != *bi->val || refresh))
    {
 x = bi->x - ((signed short) (bi->p->leftoffset));
 y = bi->y - ((signed short) (bi->p->topoffset));
 w = ((signed short) (bi->p->width));
 h = ((signed short) (bi->p->height));

 if (y - (200 - 32) < 0)
     I_Error("updateBinIcon: y - ST_Y < 0");

 if (*bi->val)
     V_DrawPatch(bi->x, bi->y, bi->p);
 else
     V_CopyRect(x, y-(200 - 32), st_backing_screen, w, h, x, y);

 bi->oldval = *bi->val;
    }

}
byte *st_backing_screen;


static player_t* plyr;


static boolean st_firsttime;


static int lu_palette;


static unsigned int st_clock;


static int st_msgcounter=0;


static st_chatstateenum_t st_chatstate;


static st_stateenum_t st_gamestate;


static boolean st_statusbaron;


static boolean st_chat;


static boolean st_oldchat;


static boolean st_cursoron;


static boolean st_notdeathmatch;


static boolean st_armson;


static boolean st_fragson;


static patch_t* sbar;


static patch_t* tallnum[10];


static patch_t* tallpercent;


static patch_t* shortnum[10];


static patch_t* keys[NUMCARDS];


static patch_t* faces[((3 +2 +3)*5 +2)];


static patch_t* faceback;


static patch_t* armsbg;


static patch_t* arms[6][2];


static st_number_t w_ready;


static st_number_t w_frags;


static st_percent_t w_health;


static st_binicon_t w_armsbg;



static st_multicon_t w_arms[6];


static st_multicon_t w_faces;


static st_multicon_t w_keyboxes[3];


static st_percent_t w_armor;


static st_number_t w_ammo[4];


static st_number_t w_maxammo[4];




static int st_fragscount;


static int st_oldhealth = -1;


static boolean oldweaponsowned[NUMWEAPONS];


static int st_facecount = 0;


static int st_faceindex = 0;


static int keyboxes[3];


static int st_randomnumber;

cheatseq_t cheat_mus = { "idmus", sizeof("idmus") - 1, 2, 0, 0, "" };
cheatseq_t cheat_god = { "iddqd", sizeof("iddqd") - 1, 0, 0, 0, "" };
cheatseq_t cheat_ammo = { "idkfa", sizeof("idkfa") - 1, 0, 0, 0, "" };
cheatseq_t cheat_ammonokey = { "idfa", sizeof("idfa") - 1, 0, 0, 0, "" };
cheatseq_t cheat_noclip = { "idspispopd", sizeof("idspispopd") - 1, 0, 0, 0, "" };
cheatseq_t cheat_commercial_noclip = { "idclip", sizeof("idclip") - 1, 0, 0, 0, "" };

cheatseq_t cheat_powerup[7] =
{
    { "idbeholdv", sizeof("idbeholdv") - 1, 0, 0, 0, "" },
    { "idbeholds", sizeof("idbeholds") - 1, 0, 0, 0, "" },
    { "idbeholdi", sizeof("idbeholdi") - 1, 0, 0, 0, "" },
    { "idbeholdr", sizeof("idbeholdr") - 1, 0, 0, 0, "" },
    { "idbeholda", sizeof("idbeholda") - 1, 0, 0, 0, "" },
    { "idbeholdl", sizeof("idbeholdl") - 1, 0, 0, 0, "" },
    { "idbehold", sizeof("idbehold") - 1, 0, 0, 0, "" },
};

cheatseq_t cheat_choppers = { "idchoppers", sizeof("idchoppers") - 1, 0, 0, 0, "" };
cheatseq_t cheat_clev = { "idclev", sizeof("idclev") - 1, 2, 0, 0, "" };
cheatseq_t cheat_mypos = { "idmypos", sizeof("idmypos") - 1, 0, 0, 0, "" };





void ST_Stop(void);

void ST_refreshBackground(void)
{

    if (st_statusbaron)
    {
        V_UseBuffer(st_backing_screen);

 V_DrawPatch(0, 0, sbar);

 if (netgame)
     V_DrawPatch(143, 0, faceback);

        V_RestoreBuffer();

 V_CopyRect(0, 0, st_backing_screen, 320, 32, 0, (200 - 32));
    }

}




boolean
ST_Responder (event_t* ev)
{
  int i;


  if (ev->type == ev_keyup
      && ((ev->data1 & 0xffff0000) == (('a'<<24)+('m'<<16))))
  {
    switch(ev->data1)
    {
      case ((('a'<<24)+('m'<<16)) | ('e'<<8)):
 st_gamestate = AutomapState;
 st_firsttime = true;
 break;

      case ((('a'<<24)+('m'<<16)) | ('x'<<8)):

 st_gamestate = FirstPersonState;
 break;
    }
  }


  else if (ev->type == ev_keydown)
  {
    if (!netgame && gameskill != sk_nightmare)
    {

      if (cht_CheckCheat(&cheat_god, ev->data2))
      {
 plyr->cheats ^= CF_GODMODE;
 if (plyr->cheats & CF_GODMODE)
 {
   if (plyr->mo)
     plyr->mo->health = 100;

   plyr->health = 100;
   plyr->message = ("Degreelessness Mode On");
 }
 else
   plyr->message = ("Degreelessness Mode Off");
      }

      else if (cht_CheckCheat(&cheat_ammonokey, ev->data2))
      {
 plyr->armorpoints = 200;
 plyr->armortype = 2;

 for (i=0;i<NUMWEAPONS;i++)
   plyr->weaponowned[i] = true;

 for (i=0;i<NUMAMMO;i++)
   plyr->ammo[i] = plyr->maxammo[i];

 plyr->message = ("Ammo (no keys) Added");
      }

      else if (cht_CheckCheat(&cheat_ammo, ev->data2))
      {
 plyr->armorpoints = 200;
 plyr->armortype = 2;

 for (i=0;i<NUMWEAPONS;i++)
   plyr->weaponowned[i] = true;

 for (i=0;i<NUMAMMO;i++)
   plyr->ammo[i] = plyr->maxammo[i];

 for (i=0;i<NUMCARDS;i++)
   plyr->cards[i] = true;

 plyr->message = ("Very Happy Ammo Added");
      }

      else if (cht_CheckCheat(&cheat_mus, ev->data2))
      {

 char buf[3];
 int musnum;

 plyr->message = ("Music Change");
 cht_GetParam(&cheat_mus, buf);






 if (gamemode == commercial || gameversion < exe_ultimate)
 {
   musnum = mus_runnin + (buf[0]-'0')*10 + buf[1]-'0' - 1;

   if (((buf[0]-'0')*10 + buf[1]-'0') > 35)
     plyr->message = ("IMPOSSIBLE SELECTION");
   else
     S_ChangeMusic(musnum, 1);
 }
 else
 {
   musnum = mus_e1m1 + (buf[0]-'1')*9 + (buf[1]-'1');

   if (((buf[0]-'1')*9 + buf[1]-'1') > 31)
     plyr->message = ("IMPOSSIBLE SELECTION");
   else
     S_ChangeMusic(musnum, 1);
 }
      }
      else if ( ((gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) == doom
                 && cht_CheckCheat(&cheat_noclip, ev->data2))
             || ((gamemission == pack_chex ? doom : gamemission == pack_hacx ? doom2 : gamemission) != doom
                 && cht_CheckCheat(&cheat_commercial_noclip,ev->data2)))
      {




 plyr->cheats ^= CF_NOCLIP;

 if (plyr->cheats & CF_NOCLIP)
   plyr->message = ("No Clipping Mode ON");
 else
   plyr->message = ("No Clipping Mode OFF");
      }

      for (i=0;i<6;i++)
      {
 if (cht_CheckCheat(&cheat_powerup[i], ev->data2))
 {
   if (!plyr->powers[i])
     P_GivePower( plyr, i);
   else if (i!=pw_strength)
     plyr->powers[i] = 1;
   else
     plyr->powers[i] = 0;

   plyr->message = ("Power-up Toggled");
 }
      }


      if (cht_CheckCheat(&cheat_powerup[6], ev->data2))
      {
 plyr->message = ("inVuln, Str, Inviso, Rad, Allmap, or Lite-amp");
      }

      else if (cht_CheckCheat(&cheat_choppers, ev->data2))
      {
 plyr->weaponowned[wp_chainsaw] = true;
 plyr->powers[pw_invulnerability] = true;
 plyr->message = ("... doesn't suck - GM");
      }

      else if (cht_CheckCheat(&cheat_mypos, ev->data2))
      {
        static char buf[52];
        M_snprintf(buf, sizeof(buf), "ang=0x%x;x,y=(0x%x,0x%x)",
                   players[consoleplayer].mo->angle,
                   players[consoleplayer].mo->x,
                   players[consoleplayer].mo->y);
        plyr->message = buf;
      }
    }


    if (!netgame && cht_CheckCheat(&cheat_clev, ev->data2))
    {
      char buf[3];
      int epsd;
      int map;

      cht_GetParam(&cheat_clev, buf);

      if (gamemode == commercial)
      {
 epsd = 1;
 map = (buf[0] - '0')*10 + buf[1] - '0';
      }
      else
      {
 epsd = buf[0] - '0';
 map = buf[1] - '0';
      }



      if (gameversion == exe_chex)
      {
        epsd = 1;
      }


      if (epsd < 1)
 return false;

      if (map < 1)
 return false;


      if ((gamemode == retail)
   && ((epsd > 4) || (map > 9)))
 return false;

      if ((gamemode == registered)
   && ((epsd > 3) || (map > 9)))
 return false;

      if ((gamemode == shareware)
   && ((epsd > 1) || (map > 9)))
 return false;



      if ((gamemode == commercial)
 && (( epsd > 1) || (map > 40)))
 return false;


      plyr->message = ("Changing Level...");
      G_DeferedInitNew(gameskill, epsd, map);
    }
  }
  return false;
}



int ST_calcPainOffset(void)
{
    int health;
    static int lastcalc;
    static int oldhealth = -1;

    health = plyr->health > 100 ? 100 : plyr->health;

    if (health != oldhealth)
    {
 lastcalc = (3 +2 +3) * (((100 - health) * 5) / 101);
 oldhealth = health;
    }
    return lastcalc;
}
void ST_updateFaceWidget(void)
{
    int i;
    angle_t badguyangle;
    angle_t diffang;
    static int lastattackdown = -1;
    static int priority = 0;
    boolean doevilgrin;

    if (priority < 10)
    {

 if (!plyr->health)
 {
     priority = 9;
     st_faceindex = ((5*(3 +2 +3))+1);
     st_facecount = 1;
 }
    }

    if (priority < 9)
    {
 if (plyr->bonuscount)
 {

     doevilgrin = false;

     for (i=0;i<NUMWEAPONS;i++)
     {
  if (oldweaponsowned[i] != plyr->weaponowned[i])
  {
      doevilgrin = true;
      oldweaponsowned[i] = plyr->weaponowned[i];
  }
     }
     if (doevilgrin)
     {

  priority = 8;
  st_facecount = (2*35);
  st_faceindex = ST_calcPainOffset() + (((3) + 2) + 1);
     }
 }

    }

    if (priority < 8)
    {
 if (plyr->damagecount
     && plyr->attacker
     && plyr->attacker != plyr->mo)
 {

     priority = 7;

     if (plyr->health - st_oldhealth > 20)
     {
  st_facecount = (1*35);
  st_faceindex = ST_calcPainOffset() + ((3) + 2);
     }
     else
     {
  badguyangle = R_PointToAngle2(plyr->mo->x,
           plyr->mo->y,
           plyr->attacker->x,
           plyr->attacker->y);

  if (badguyangle > plyr->mo->angle)
  {

      diffang = badguyangle - plyr->mo->angle;
      i = diffang > 0x80000000;
  }
  else
  {

      diffang = plyr->mo->angle - badguyangle;
      i = diffang <= 0x80000000;
  }


  st_facecount = (1*35);
  st_faceindex = ST_calcPainOffset();

  if (diffang < 0x20000000)
  {

      st_faceindex += ((((3) + 2) + 1) + 1);
  }
  else if (i)
  {

      st_faceindex += (3);
  }
  else
  {

      st_faceindex += (3)+1;
  }
     }
 }
    }

    if (priority < 7)
    {

 if (plyr->damagecount)
 {
     if (plyr->health - st_oldhealth > 20)
     {
  priority = 7;
  st_facecount = (1*35);
  st_faceindex = ST_calcPainOffset() + ((3) + 2);
     }
     else
     {
  priority = 6;
  st_facecount = (1*35);
  st_faceindex = ST_calcPainOffset() + ((((3) + 2) + 1) + 1);
     }

 }

    }

    if (priority < 6)
    {

 if (plyr->attackdown)
 {
     if (lastattackdown==-1)
  lastattackdown = (2*35);
     else if (!--lastattackdown)
     {
  priority = 5;
  st_faceindex = ST_calcPainOffset() + ((((3) + 2) + 1) + 1);
  st_facecount = 1;
  lastattackdown = 1;
     }
 }
 else
     lastattackdown = -1;

    }

    if (priority < 5)
    {

 if ((plyr->cheats & CF_GODMODE)
     || plyr->powers[pw_invulnerability])
 {
     priority = 4;

     st_faceindex = (5*(3 +2 +3));
     st_facecount = 1;

 }

    }


    if (!st_facecount)
    {
 st_faceindex = ST_calcPainOffset() + (st_randomnumber % 3);
 st_facecount = (35/2);
 priority = 0;
    }

    st_facecount--;

}

void ST_updateWidgets(void)
{
    static int largeammo = 1994;
    int i;




    if (weaponinfo[plyr->readyweapon].ammo == am_noammo)
 w_ready.num = &largeammo;
    else
 w_ready.num = &plyr->ammo[weaponinfo[plyr->readyweapon].ammo];
    w_ready.data = plyr->readyweapon;







    for (i=0;i<3;i++)
    {
 keyboxes[i] = plyr->cards[i] ? i : -1;

 if (plyr->cards[i+3])
     keyboxes[i] = i+3;
    }


    ST_updateFaceWidget();


    st_notdeathmatch = !deathmatch;


    st_armson = st_statusbaron && !deathmatch;


    st_fragson = deathmatch && st_statusbaron;
    st_fragscount = 0;

    for (i=0 ; i<4 ; i++)
    {
 if (i != consoleplayer)
     st_fragscount += plyr->frags[i];
 else
     st_fragscount -= plyr->frags[i];
    }


    if (!--st_msgcounter)
 st_chat = st_oldchat;

}

void ST_Ticker (void)
{

    st_clock++;
    st_randomnumber = M_Random();
    ST_updateWidgets();
    st_oldhealth = plyr->health;

}

static int st_palette = 0;

void ST_doPaletteStuff(void)
{

    int palette;
    byte* pal;
    int cnt;
    int bzc;

    cnt = plyr->damagecount;

    if (plyr->powers[pw_strength])
    {

   bzc = 12 - (plyr->powers[pw_strength]>>6);

 if (bzc > cnt)
     cnt = bzc;
    }

    if (cnt)
    {
 palette = (cnt+7)>>3;

 if (palette >= 8)
     palette = 8 -1;

 palette += 1;
    }

    else if (plyr->bonuscount)
    {
 palette = (plyr->bonuscount+7)>>3;

 if (palette >= 4)
     palette = 4 -1;

 palette += 9;
    }

    else if ( plyr->powers[pw_ironfeet] > 4*32
       || plyr->powers[pw_ironfeet]&8)
 palette = 13;
    else
 palette = 0;






    if (gameversion == exe_chex
     && palette >= 1 && palette < 1 + 8)
    {
        palette = 13;
    }

    if (palette != st_palette)
    {
 st_palette = palette;
 pal = (byte *) W_CacheLumpNum (lu_palette, PU_CACHE)+palette*768;
 I_SetPalette (pal);
    }

}

void ST_drawWidgets(boolean refresh)
{
    int i;


    st_armson = st_statusbaron && !deathmatch;


    st_fragson = deathmatch && st_statusbaron;

    STlib_updateNum(&w_ready, refresh);

    for (i=0;i<4;i++)
    {
 STlib_updateNum(&w_ammo[i], refresh);
 STlib_updateNum(&w_maxammo[i], refresh);
    }

    STlib_updatePercent(&w_health, refresh);
    STlib_updatePercent(&w_armor, refresh);

    STlib_updateBinIcon(&w_armsbg, refresh);

    for (i=0;i<6;i++)
 STlib_updateMultIcon(&w_arms[i], refresh);

    STlib_updateMultIcon(&w_faces, refresh);

    for (i=0;i<3;i++)
 STlib_updateMultIcon(&w_keyboxes[i], refresh);

    STlib_updateNum(&w_frags, refresh);

}

void ST_doRefresh(void)
{

    st_firsttime = false;


    ST_refreshBackground();


    ST_drawWidgets(true);

}

void ST_diffDraw(void)
{

    ST_drawWidgets(false);
}

void ST_Drawer (boolean fullscreen, boolean refresh)
{

    st_statusbaron = (!fullscreen) || automapactive;
    st_firsttime = st_firsttime || refresh;


    ST_doPaletteStuff();


    if (st_firsttime) ST_doRefresh();

    else ST_diffDraw();

}

typedef void (*load_callback_t)(char *lumpname, patch_t **variable);




static void ST_loadUnloadGraphics(load_callback_t callback)
{

    int i;
    int j;
    int facenum;

    char namebuf[9];


    for (i=0;i<10;i++)
    {
 snprintf(namebuf, 9, "STTNUM%d", i);
        callback(namebuf, &tallnum[i]);

 snprintf(namebuf, 9, "STYSNUM%d", i);
        callback(namebuf, &shortnum[i]);
    }




    callback(("STTPRCNT"), &tallpercent);


    for (i=0;i<NUMCARDS;i++)
    {
     snprintf(namebuf, 9, "STKEYS%d", i);
        callback(namebuf, &keys[i]);
    }


    callback(("STARMS"), &armsbg);


    for (i=0; i<6; i++)
    {
     snprintf(namebuf, 9, "STGNUM%d", i+2);


        callback(namebuf, &arms[i][0]);


        arms[i][1] = shortnum[i+2];
    }


    snprintf(namebuf, 9, "STFB%d", consoleplayer);
    callback(namebuf, &faceback);


    callback(("STBAR"), &sbar);


    facenum = 0;
    for (i=0; i<5; i++)
    {
 for (j=0; j<3; j++)
 {
     snprintf(namebuf, 9, "STFST%d%d", i, j);
            callback(namebuf, &faces[facenum]);
            ++facenum;
 }
 snprintf(namebuf, 9, "STFTR%d0", i);
        callback(namebuf, &faces[facenum]);
        ++facenum;
 snprintf(namebuf, 9, "STFTL%d0", i);
        callback(namebuf, &faces[facenum]);
        ++facenum;
 snprintf(namebuf, 9, "STFOUCH%d", i);
        callback(namebuf, &faces[facenum]);
        ++facenum;
 snprintf(namebuf, 9, "STFEVL%d", i);
        callback(namebuf, &faces[facenum]);
        ++facenum;
 snprintf(namebuf, 9, "STFKILL%d", i);
        callback(namebuf, &faces[facenum]);
        ++facenum;
    }

    callback(("STFGOD0"), &faces[facenum]);
    ++facenum;
    callback(("STFDEAD0"), &faces[facenum]);
    ++facenum;
}

static void ST_loadCallback(char *lumpname, patch_t **variable)
{
    *variable = W_CacheLumpName(lumpname, PU_STATIC);
}

void ST_loadGraphics(void)
{
    ST_loadUnloadGraphics(ST_loadCallback);
}

void ST_loadData(void)
{
    lu_palette = W_GetNumForName (("PLAYPAL"));
    ST_loadGraphics();
}

static void ST_unloadCallback(char *lumpname, patch_t **variable)
{
    W_ReleaseLumpName(lumpname);
    *variable = ((void*)0);
}

void ST_unloadGraphics(void)
{
    ST_loadUnloadGraphics(ST_unloadCallback);
}

void ST_unloadData(void)
{
    ST_unloadGraphics();
}

void ST_initData(void)
{

    int i;

    st_firsttime = true;
    plyr = &players[consoleplayer];

    st_clock = 0;
    st_chatstate = StartChatState;
    st_gamestate = FirstPersonState;

    st_statusbaron = true;
    st_oldchat = st_chat = false;
    st_cursoron = false;

    st_faceindex = 0;
    st_palette = -1;

    st_oldhealth = -1;

    for (i=0;i<NUMWEAPONS;i++)
 oldweaponsowned[i] = plyr->weaponowned[i];

    for (i=0;i<3;i++)
 keyboxes[i] = -1;

    STlib_init();

}



void ST_createWidgets(void)
{

    int i;


    STlib_initNum(&w_ready,
    44,
    171,
    tallnum,
    &plyr->ammo[weaponinfo[plyr->readyweapon].ammo],
    &st_statusbaron,
    3 );


    w_ready.data = plyr->readyweapon;


    STlib_initPercent(&w_health,
        90,
        171,
        tallnum,
        &plyr->health,
        &st_statusbaron,
        tallpercent);


    STlib_initBinIcon(&w_armsbg,
        104,
        168,
        armsbg,
        &st_notdeathmatch,
        &st_statusbaron);


    for(i=0;i<6;i++)
    {
 STlib_initMultIcon(&w_arms[i],
      111 +(i%3)*12,
      172 +(i/3)*10,
      arms[i], (int *) &plyr->weaponowned[i+1],
      &st_armson);
    }


    STlib_initNum(&w_frags,
    138,
    171,
    tallnum,
    &st_fragscount,
    &st_fragson,
    2);


    STlib_initMultIcon(&w_faces,
         143,
         168,
         faces,
         &st_faceindex,
         &st_statusbaron);


    STlib_initPercent(&w_armor,
        221,
        171,
        tallnum,
        &plyr->armorpoints,
        &st_statusbaron, tallpercent);


    STlib_initMultIcon(&w_keyboxes[0],
         239,
         171,
         keys,
         &keyboxes[0],
         &st_statusbaron);

    STlib_initMultIcon(&w_keyboxes[1],
         239,
         181,
         keys,
         &keyboxes[1],
         &st_statusbaron);

    STlib_initMultIcon(&w_keyboxes[2],
         239,
         191,
         keys,
         &keyboxes[2],
         &st_statusbaron);


    STlib_initNum(&w_ammo[0],
    288,
    173,
    shortnum,
    &plyr->ammo[0],
    &st_statusbaron,
    3);

    STlib_initNum(&w_ammo[1],
    288,
    179,
    shortnum,
    &plyr->ammo[1],
    &st_statusbaron,
    3);

    STlib_initNum(&w_ammo[2],
    288,
    191,
    shortnum,
    &plyr->ammo[2],
    &st_statusbaron,
    3);

    STlib_initNum(&w_ammo[3],
    288,
    185,
    shortnum,
    &plyr->ammo[3],
    &st_statusbaron,
    3);


    STlib_initNum(&w_maxammo[0],
    314,
    173,
    shortnum,
    &plyr->maxammo[0],
    &st_statusbaron,
    3);

    STlib_initNum(&w_maxammo[1],
    314,
    179,
    shortnum,
    &plyr->maxammo[1],
    &st_statusbaron,
    3);

    STlib_initNum(&w_maxammo[2],
    314,
    191,
    shortnum,
    &plyr->maxammo[2],
    &st_statusbaron,
    3);

    STlib_initNum(&w_maxammo[3],
    314,
    185,
    shortnum,
    &plyr->maxammo[3],
    &st_statusbaron,
    3);

}

static boolean st_stopped = true;


void ST_Start (void)
{

    if (!st_stopped)
 ST_Stop();

    ST_initData();
    ST_createWidgets();
    st_stopped = false;

}

void ST_Stop (void)
{
    if (st_stopped)
 return;

    I_SetPalette (W_CacheLumpNum (lu_palette, PU_CACHE));

    st_stopped = true;
}

void ST_Init (void)
{
    ST_loadData();
    st_backing_screen = (byte *) Z_Malloc(320 * 32, PU_STATIC, 0);
}
typedef struct
{

    sfxinfo_t *sfxinfo;


    mobj_t *origin;


    int handle;

} channel_t;



static channel_t *channels;




int sfxVolume = 8;



int musicVolume = 8;



static int snd_SfxVolume;



static boolean mus_paused;



static musicinfo_t *mus_playing = ((void*)0);



int snd_channels = 8;







void S_Init(int sfxVolume, int musicVolume)
{
    int i;

    I_PrecacheSounds(S_sfx, NUMSFX);

    S_SetSfxVolume(sfxVolume);
    S_SetMusicVolume(musicVolume);




    channels = Z_Malloc(snd_channels*sizeof(channel_t), PU_STATIC, 0);


    for (i=0 ; i<snd_channels ; i++)
    {
        channels[i].sfxinfo = 0;
    }


    mus_paused = 0;


    for (i=1 ; i<NUMSFX ; i++)
    {
        S_sfx[i].lumpnum = S_sfx[i].usefulness = -1;
    }

    I_AtExit(S_Shutdown, true);
}

void S_Shutdown(void)
{
    I_ShutdownSound();
    I_ShutdownMusic();
}

static void S_StopChannel(int cnum)
{
    int i;
    channel_t *c;

    c = &channels[cnum];

    if (c->sfxinfo)
    {


        if (I_SoundIsPlaying(c->handle))
        {
            I_StopSound(c->handle);
        }



        for (i=0; i<snd_channels; i++)
        {
            if (cnum != i && c->sfxinfo == channels[i].sfxinfo)
            {
                break;
            }
        }



        c->sfxinfo->usefulness--;
        c->sfxinfo = ((void*)0);
    }
}







void S_Start(void)
{
    int cnum;
    int mnum;



    for (cnum=0 ; cnum<snd_channels ; cnum++)
    {
        if (channels[cnum].sfxinfo)
        {
            S_StopChannel(cnum);
        }
    }


    mus_paused = 0;

    if (gamemode == commercial)
    {
        mnum = mus_runnin + gamemap - 1;
    }
    else
    {
        int spmus[]=
        {


            mus_e3m4,
            mus_e3m2,
            mus_e3m3,
            mus_e1m5,
            mus_e2m7,
            mus_e2m4,
            mus_e2m6,
            mus_e2m5,
            mus_e1m9,
        };

        if (gameepisode < 4)
        {
            mnum = mus_e1m1 + (gameepisode-1)*9 + gamemap-1;
        }
        else
        {
            mnum = spmus[gamemap-1];
        }
    }

    S_ChangeMusic(mnum, true);
}

void S_StopSound(mobj_t *origin)
{
    int cnum;

    for (cnum=0 ; cnum<snd_channels ; cnum++)
    {
        if (channels[cnum].sfxinfo && channels[cnum].origin == origin)
        {
            S_StopChannel(cnum);
            break;
        }
    }
}






static int S_GetChannel(mobj_t *origin, sfxinfo_t *sfxinfo)
{

    int cnum;

    channel_t* c;


    for (cnum=0 ; cnum<snd_channels ; cnum++)
    {
        if (!channels[cnum].sfxinfo)
        {
            break;
        }
        else if (origin && channels[cnum].origin == origin)
        {
            S_StopChannel(cnum);
            break;
        }
    }


    if (cnum == snd_channels)
    {

        for (cnum=0 ; cnum<snd_channels ; cnum++)
        {
            if (channels[cnum].sfxinfo->priority >= sfxinfo->priority)
            {
                break;
            }
        }

        if (cnum == snd_channels)
        {

            return -1;
        }
        else
        {

            S_StopChannel(cnum);
        }
    }

    c = &channels[cnum];


    c->sfxinfo = sfxinfo;
    c->origin = origin;

    return cnum;
}
static int S_AdjustSoundParams(mobj_t *listener, mobj_t *source,
                               int *vol, int *sep)
{
    fixed_t approx_dist;
    fixed_t adx;
    fixed_t ady;
    angle_t angle;



    adx = abs(listener->x - source->x);
    ady = abs(listener->y - source->y);


    approx_dist = adx + ady - ((adx < ady ? adx : ady)>>1);

    if (gamemap != 8 && approx_dist > (1200 * (1<<16)))
    {
        return 0;
    }


    angle = R_PointToAngle2(listener->x,
                            listener->y,
                            source->x,
                            source->y);

    if (angle > listener->angle)
    {
        angle = angle - listener->angle;
    }
    else
    {
        angle = angle + (0xffffffff - listener->angle);
    }

    angle >>= 19;


    *sep = 128 - (FixedMul((96 * (1<<16)), finesine[angle]) >> 16);


    if (approx_dist < (200 * (1<<16)))
    {
        *vol = snd_SfxVolume;
    }
    else if (gamemap == 8)
    {
        if (approx_dist > (1200 * (1<<16)))
        {
            approx_dist = (1200 * (1<<16));
        }

        *vol = 15+ ((snd_SfxVolume-15)
                    *(((1200 * (1<<16)) - approx_dist)>>16))
            / (((1200 * (1<<16)) - (200 * (1<<16))) >> 16);
    }
    else
    {

        *vol = (snd_SfxVolume
                * (((1200 * (1<<16)) - approx_dist)>>16))
            / (((1200 * (1<<16)) - (200 * (1<<16))) >> 16);
    }

    return (*vol > 0);
}

void S_StartSound(void *origin_p, int sfx_id)
{
    sfxinfo_t *sfx;
    mobj_t *origin;
    int rc;
    int sep;
    int cnum;
    int volume;

    origin = (mobj_t *) origin_p;
    volume = snd_SfxVolume;


    if (sfx_id < 1 || sfx_id > NUMSFX)
    {
        I_Error("Bad sfx #: %d", sfx_id);
    }

    sfx = &S_sfx[sfx_id];


    if (sfx->link)
    {
        volume += sfx->volume;

        if (volume < 1)
        {
            return;
        }

        if (volume > snd_SfxVolume)
        {
            volume = snd_SfxVolume;
        }
    }




    if (origin && origin != players[consoleplayer].mo)
    {
        rc = S_AdjustSoundParams(players[consoleplayer].mo,
                                 origin,
                                 &volume,
                                 &sep);

        if (origin->x == players[consoleplayer].mo->x
         && origin->y == players[consoleplayer].mo->y)
        {
            sep = 128;
        }

        if (!rc)
        {
            return;
        }
    }
    else
    {
        sep = 128;
    }


    S_StopSound(origin);


    cnum = S_GetChannel(origin, sfx);

    if (cnum < 0)
    {
        return;
    }


    if (sfx->usefulness++ < 0)
    {
        sfx->usefulness = 1;
    }

    if (sfx->lumpnum < 0)
    {
        sfx->lumpnum = I_GetSfxLumpNum(sfx);
    }

    channels[cnum].handle = I_StartSound(sfx, cnum, volume, sep);
}





void S_PauseSound(void)
{
    if (mus_playing && !mus_paused)
    {
        I_PauseSong();
        mus_paused = true;
    }
}

void S_ResumeSound(void)
{
    if (mus_playing && mus_paused)
    {
        I_ResumeSong();
        mus_paused = false;
    }
}





void S_UpdateSounds(mobj_t *listener)
{
    int audible;
    int cnum;
    int volume;
    int sep;
    sfxinfo_t* sfx;
    channel_t* c;

    I_UpdateSound();

    for (cnum=0; cnum<snd_channels; cnum++)
    {
        c = &channels[cnum];
        sfx = c->sfxinfo;

        if (c->sfxinfo)
        {
            if (I_SoundIsPlaying(c->handle))
            {

                volume = snd_SfxVolume;
                sep = 128;

                if (sfx->link)
                {
                    volume += sfx->volume;
                    if (volume < 1)
                    {
                        S_StopChannel(cnum);
                        continue;
                    }
                    else if (volume > snd_SfxVolume)
                    {
                        volume = snd_SfxVolume;
                    }
                }



                if (c->origin && listener != c->origin)
                {
                    audible = S_AdjustSoundParams(listener,
                                                  c->origin,
                                                  &volume,
                                                  &sep);

                    if (!audible)
                    {
                        S_StopChannel(cnum);
                    }
                    else
                    {
                        I_UpdateSoundParams(c->handle, volume, sep);
                    }
                }
            }
            else
            {


                S_StopChannel(cnum);
            }
        }
    }
}

void S_SetMusicVolume(int volume)
{
    if (volume < 0 || volume > 127)
    {
        I_Error("Attempt to set music volume at %d",
                volume);
    }

    I_SetMusicVolume(volume);
}

void S_SetSfxVolume(int volume)
{
    if (volume < 0 || volume > 127)
    {
        I_Error("Attempt to set sfx volume at %d", volume);
    }

    snd_SfxVolume = volume;
}





void S_StartMusic(int m_id)
{
    S_ChangeMusic(m_id, false);
}

void S_ChangeMusic(int musicnum, int looping)
{
    musicinfo_t *music = ((void*)0);
    char namebuf[9];
    void *handle;




    if (musicnum == mus_intro && (snd_musicdevice == SNDDEVICE_ADLIB
                               || snd_musicdevice == SNDDEVICE_SB))
    {
        musicnum = mus_introa;
    }

    if (musicnum <= mus_None || musicnum >= NUMMUSIC)
    {
        I_Error("Bad music number %d", musicnum);
    }
    else
    {
        music = &S_music[musicnum];
    }

    if (mus_playing == music)
    {
        return;
    }


    S_StopMusic();


    if (!music->lumpnum)
    {
        M_snprintf(namebuf, sizeof(namebuf), "d_%s", (music->name));
        music->lumpnum = W_GetNumForName(namebuf);
    }

    music->data = W_CacheLumpNum(music->lumpnum, PU_STATIC);

    handle = I_RegisterSong(music->data, W_LumpLength(music->lumpnum));
    music->handle = handle;
    I_PlaySong(handle, looping);

    mus_playing = music;
}

boolean S_MusicPlaying(void)
{
    return I_MusicIsPlaying();
}

void S_StopMusic(void)
{
    if (mus_playing)
    {
        if (mus_paused)
        {
            I_ResumeSong();
        }

        I_StopSong();
        I_UnRegisterSong(mus_playing->handle);
        W_ReleaseLumpNum(mus_playing->lumpnum);
        mus_playing->data = ((void*)0);
        mus_playing = ((void*)0);
    }
}
int SlopeDiv(unsigned int num, unsigned int den)
{
    unsigned ans;

    if (den < 512)
    {
        return 2048;
    }
    else
    {
        ans = (num << 3) / (den >> 8);

        if (ans <= 2048)
        {
            return ans;
        }
        else
        {
            return 2048;
        }
    }
}

const int finetangent[4096] =
{
    -170910304,-56965752,-34178904,-24413316,-18988036,-15535599,-13145455,-11392683,
    -10052327,-8994149,-8137527,-7429880,-6835455,-6329090,-5892567,-5512368,
    -5178251,-4882318,-4618375,-4381502,-4167737,-3973855,-3797206,-3635590,
    -3487165,-3350381,-3223918,-3106651,-2997613,-2895966,-2800983,-2712030,
    -2628549,-2550052,-2476104,-2406322,-2340362,-2277919,-2218719,-2162516,
    -2109087,-2058233,-2009771,-1963536,-1919378,-1877161,-1836758,-1798063,
    -1760956,-1725348,-1691149,-1658278,-1626658,-1596220,-1566898,-1538632,
    -1511367,-1485049,-1459630,-1435065,-1411312,-1388330,-1366084,-1344537,
    -1323658,-1303416,-1283783,-1264730,-1246234,-1228269,-1210813,-1193846,
    -1177345,-1161294,-1145673,-1130465,-1115654,-1101225,-1087164,-1073455,
    -1060087,-1047046,-1034322,-1021901,-1009774,-997931,-986361,-975054,
    -964003,-953199,-942633,-932298,-922186,-912289,-902602,-893117,
    -883829,-874730,-865817,-857081,-848520,-840127,-831898,-823827,
    -815910,-808143,-800521,-793041,-785699,-778490,-771411,-764460,
    -757631,-750922,-744331,-737853,-731486,-725227,-719074,-713023,
    -707072,-701219,-695462,-689797,-684223,-678737,-673338,-668024,
    -662792,-657640,-652568,-647572,-642651,-637803,-633028,-628323,
    -623686,-619117,-614613,-610174,-605798,-601483,-597229,-593033,
    -588896,-584815,-580789,-576818,-572901,-569035,-565221,-561456,
    -557741,-554074,-550455,-546881,-543354,-539870,-536431,-533034,
    -529680,-526366,-523094,-519861,-516667,-513512,-510394,-507313,
    -504269,-501261,-498287,-495348,-492443,-489571,-486732,-483925,
    -481150,-478406,-475692,-473009,-470355,-467730,-465133,-462565,
    -460024,-457511,-455024,-452564,-450129,-447720,-445337,-442978,
    -440643,-438332,-436045,-433781,-431540,-429321,-427125,-424951,
    -422798,-420666,-418555,-416465,-414395,-412344,-410314,-408303,
    -406311,-404338,-402384,-400448,-398530,-396630,-394747,-392882,
    -391034,-389202,-387387,-385589,-383807,-382040,-380290,-378555,
    -376835,-375130,-373440,-371765,-370105,-368459,-366826,-365208,
    -363604,-362013,-360436,-358872,-357321,-355783,-354257,-352744,
    -351244,-349756,-348280,-346816,-345364,-343924,-342495,-341078,
    -339671,-338276,-336892,-335519,-334157,-332805,-331464,-330133,
    -328812,-327502,-326201,-324910,-323629,-322358,-321097,-319844,
    -318601,-317368,-316143,-314928,-313721,-312524,-311335,-310154,
    -308983,-307819,-306664,-305517,-304379,-303248,-302126,-301011,
    -299904,-298805,-297714,-296630,-295554,-294485,-293423,-292369,
    -291322,-290282,-289249,-288223,-287204,-286192,-285186,-284188,
    -283195,-282210,-281231,-280258,-279292,-278332,-277378,-276430,
    -275489,-274553,-273624,-272700,-271782,-270871,-269965,-269064,
    -268169,-267280,-266397,-265519,-264646,-263779,-262917,-262060,
    -261209,-260363,-259522,-258686,-257855,-257029,-256208,-255392,
    -254581,-253774,-252973,-252176,-251384,-250596,-249813,-249035,
    -248261,-247492,-246727,-245966,-245210,-244458,-243711,-242967,
    -242228,-241493,-240763,-240036,-239314,-238595,-237881,-237170,
    -236463,-235761,-235062,-234367,-233676,-232988,-232304,-231624,
    -230948,-230275,-229606,-228941,-228279,-227621,-226966,-226314,
    -225666,-225022,-224381,-223743,-223108,-222477,-221849,-221225,
    -220603,-219985,-219370,-218758,-218149,-217544,-216941,-216341,
    -215745,-215151,-214561,-213973,-213389,-212807,-212228,-211652,
    -211079,-210509,-209941,-209376,-208815,-208255,-207699,-207145,
    -206594,-206045,-205500,-204956,-204416,-203878,-203342,-202809,
    -202279,-201751,-201226,-200703,-200182,-199664,-199149,-198636,
    -198125,-197616,-197110,-196606,-196105,-195606,-195109,-194614,
    -194122,-193631,-193143,-192658,-192174,-191693,-191213,-190736,
    -190261,-189789,-189318,-188849,-188382,-187918,-187455,-186995,
    -186536,-186080,-185625,-185173,-184722,-184274,-183827,-183382,
    -182939,-182498,-182059,-181622,-181186,-180753,-180321,-179891,
    -179463,-179037,-178612,-178190,-177769,-177349,-176932,-176516,
    -176102,-175690,-175279,-174870,-174463,-174057,-173653,-173251,
    -172850,-172451,-172053,-171657,-171263,-170870,-170479,-170089,
    -169701,-169315,-168930,-168546,-168164,-167784,-167405,-167027,
    -166651,-166277,-165904,-165532,-165162,-164793,-164426,-164060,
    -163695,-163332,-162970,-162610,-162251,-161893,-161537,-161182,
    -160828,-160476,-160125,-159775,-159427,-159079,-158734,-158389,
    -158046,-157704,-157363,-157024,-156686,-156349,-156013,-155678,
    -155345,-155013,-154682,-154352,-154024,-153697,-153370,-153045,
    -152722,-152399,-152077,-151757,-151438,-151120,-150803,-150487,
    -150172,-149859,-149546,-149235,-148924,-148615,-148307,-148000,
    -147693,-147388,-147084,-146782,-146480,-146179,-145879,-145580,
    -145282,-144986,-144690,-144395,-144101,-143808,-143517,-143226,
    -142936,-142647,-142359,-142072,-141786,-141501,-141217,-140934,
    -140651,-140370,-140090,-139810,-139532,-139254,-138977,-138701,
    -138426,-138152,-137879,-137607,-137335,-137065,-136795,-136526,
    -136258,-135991,-135725,-135459,-135195,-134931,-134668,-134406,
    -134145,-133884,-133625,-133366,-133108,-132851,-132594,-132339,
    -132084,-131830,-131576,-131324,-131072,-130821,-130571,-130322,
    -130073,-129825,-129578,-129332,-129086,-128841,-128597,-128353,
    -128111,-127869,-127627,-127387,-127147,-126908,-126669,-126432,
    -126195,-125959,-125723,-125488,-125254,-125020,-124787,-124555,
    -124324,-124093,-123863,-123633,-123404,-123176,-122949,-122722,
    -122496,-122270,-122045,-121821,-121597,-121374,-121152,-120930,
    -120709,-120489,-120269,-120050,-119831,-119613,-119396,-119179,
    -118963,-118747,-118532,-118318,-118104,-117891,-117678,-117466,
    -117254,-117044,-116833,-116623,-116414,-116206,-115998,-115790,
    -115583,-115377,-115171,-114966,-114761,-114557,-114354,-114151,
    -113948,-113746,-113545,-113344,-113143,-112944,-112744,-112546,
    -112347,-112150,-111952,-111756,-111560,-111364,-111169,-110974,
    -110780,-110586,-110393,-110200,-110008,-109817,-109626,-109435,
    -109245,-109055,-108866,-108677,-108489,-108301,-108114,-107927,
    -107741,-107555,-107369,-107184,-107000,-106816,-106632,-106449,
    -106266,-106084,-105902,-105721,-105540,-105360,-105180,-105000,
    -104821,-104643,-104465,-104287,-104109,-103933,-103756,-103580,
    -103404,-103229,-103054,-102880,-102706,-102533,-102360,-102187,
    -102015,-101843,-101671,-101500,-101330,-101159,-100990,-100820,
    -100651,-100482,-100314,-100146,-99979,-99812,-99645,-99479,
    -99313,-99148,-98982,-98818,-98653,-98489,-98326,-98163,
    -98000,-97837,-97675,-97513,-97352,-97191,-97030,-96870,
    -96710,-96551,-96391,-96233,-96074,-95916,-95758,-95601,
    -95444,-95287,-95131,-94975,-94819,-94664,-94509,-94354,
    -94200,-94046,-93892,-93739,-93586,-93434,-93281,-93129,
    -92978,-92826,-92675,-92525,-92375,-92225,-92075,-91926,
    -91777,-91628,-91480,-91332,-91184,-91036,-90889,-90742,
    -90596,-90450,-90304,-90158,-90013,-89868,-89724,-89579,
    -89435,-89292,-89148,-89005,-88862,-88720,-88577,-88435,
    -88294,-88152,-88011,-87871,-87730,-87590,-87450,-87310,
    -87171,-87032,-86893,-86755,-86616,-86479,-86341,-86204,
    -86066,-85930,-85793,-85657,-85521,-85385,-85250,-85114,
    -84980,-84845,-84710,-84576,-84443,-84309,-84176,-84043,
    -83910,-83777,-83645,-83513,-83381,-83250,-83118,-82987,
    -82857,-82726,-82596,-82466,-82336,-82207,-82078,-81949,
    -81820,-81691,-81563,-81435,-81307,-81180,-81053,-80925,
    -80799,-80672,-80546,-80420,-80294,-80168,-80043,-79918,
    -79793,-79668,-79544,-79420,-79296,-79172,-79048,-78925,
    -78802,-78679,-78557,-78434,-78312,-78190,-78068,-77947,
    -77826,-77705,-77584,-77463,-77343,-77223,-77103,-76983,
    -76864,-76744,-76625,-76506,-76388,-76269,-76151,-76033,
    -75915,-75797,-75680,-75563,-75446,-75329,-75213,-75096,
    -74980,-74864,-74748,-74633,-74517,-74402,-74287,-74172,
    -74058,-73944,-73829,-73715,-73602,-73488,-73375,-73262,
    -73149,-73036,-72923,-72811,-72699,-72587,-72475,-72363,
    -72252,-72140,-72029,-71918,-71808,-71697,-71587,-71477,
    -71367,-71257,-71147,-71038,-70929,-70820,-70711,-70602,
    -70494,-70385,-70277,-70169,-70061,-69954,-69846,-69739,
    -69632,-69525,-69418,-69312,-69205,-69099,-68993,-68887,
    -68781,-68676,-68570,-68465,-68360,-68255,-68151,-68046,
    -67942,-67837,-67733,-67629,-67526,-67422,-67319,-67216,
    -67113,-67010,-66907,-66804,-66702,-66600,-66498,-66396,
    -66294,-66192,-66091,-65989,-65888,-65787,-65686,-65586,
    -65485,-65385,-65285,-65185,-65085,-64985,-64885,-64786,
    -64687,-64587,-64488,-64389,-64291,-64192,-64094,-63996,
    -63897,-63799,-63702,-63604,-63506,-63409,-63312,-63215,
    -63118,-63021,-62924,-62828,-62731,-62635,-62539,-62443,
    -62347,-62251,-62156,-62060,-61965,-61870,-61775,-61680,
    -61585,-61491,-61396,-61302,-61208,-61114,-61020,-60926,
    -60833,-60739,-60646,-60552,-60459,-60366,-60273,-60181,
    -60088,-59996,-59903,-59811,-59719,-59627,-59535,-59444,
    -59352,-59261,-59169,-59078,-58987,-58896,-58805,-58715,
    -58624,-58534,-58443,-58353,-58263,-58173,-58083,-57994,
    -57904,-57815,-57725,-57636,-57547,-57458,-57369,-57281,
    -57192,-57104,-57015,-56927,-56839,-56751,-56663,-56575,
    -56487,-56400,-56312,-56225,-56138,-56051,-55964,-55877,
    -55790,-55704,-55617,-55531,-55444,-55358,-55272,-55186,
    -55100,-55015,-54929,-54843,-54758,-54673,-54587,-54502,
    -54417,-54333,-54248,-54163,-54079,-53994,-53910,-53826,
    -53741,-53657,-53574,-53490,-53406,-53322,-53239,-53156,
    -53072,-52989,-52906,-52823,-52740,-52657,-52575,-52492,
    -52410,-52327,-52245,-52163,-52081,-51999,-51917,-51835,
    -51754,-51672,-51591,-51509,-51428,-51347,-51266,-51185,
    -51104,-51023,-50942,-50862,-50781,-50701,-50621,-50540,
    -50460,-50380,-50300,-50221,-50141,-50061,-49982,-49902,
    -49823,-49744,-49664,-49585,-49506,-49427,-49349,-49270,
    -49191,-49113,-49034,-48956,-48878,-48799,-48721,-48643,
    -48565,-48488,-48410,-48332,-48255,-48177,-48100,-48022,
    -47945,-47868,-47791,-47714,-47637,-47560,-47484,-47407,
    -47331,-47254,-47178,-47102,-47025,-46949,-46873,-46797,
    -46721,-46646,-46570,-46494,-46419,-46343,-46268,-46193,
    -46118,-46042,-45967,-45892,-45818,-45743,-45668,-45593,
    -45519,-45444,-45370,-45296,-45221,-45147,-45073,-44999,
    -44925,-44851,-44778,-44704,-44630,-44557,-44483,-44410,
    -44337,-44263,-44190,-44117,-44044,-43971,-43898,-43826,
    -43753,-43680,-43608,-43535,-43463,-43390,-43318,-43246,
    -43174,-43102,-43030,-42958,-42886,-42814,-42743,-42671,
    -42600,-42528,-42457,-42385,-42314,-42243,-42172,-42101,
    -42030,-41959,-41888,-41817,-41747,-41676,-41605,-41535,
    -41465,-41394,-41324,-41254,-41184,-41113,-41043,-40973,
    -40904,-40834,-40764,-40694,-40625,-40555,-40486,-40416,
    -40347,-40278,-40208,-40139,-40070,-40001,-39932,-39863,
    -39794,-39726,-39657,-39588,-39520,-39451,-39383,-39314,
    -39246,-39178,-39110,-39042,-38973,-38905,-38837,-38770,
    -38702,-38634,-38566,-38499,-38431,-38364,-38296,-38229,
    -38161,-38094,-38027,-37960,-37893,-37826,-37759,-37692,
    -37625,-37558,-37491,-37425,-37358,-37291,-37225,-37158,
    -37092,-37026,-36959,-36893,-36827,-36761,-36695,-36629,
    -36563,-36497,-36431,-36365,-36300,-36234,-36168,-36103,
    -36037,-35972,-35907,-35841,-35776,-35711,-35646,-35580,
    -35515,-35450,-35385,-35321,-35256,-35191,-35126,-35062,
    -34997,-34932,-34868,-34803,-34739,-34675,-34610,-34546,
    -34482,-34418,-34354,-34289,-34225,-34162,-34098,-34034,
    -33970,-33906,-33843,-33779,-33715,-33652,-33588,-33525,
    -33461,-33398,-33335,-33272,-33208,-33145,-33082,-33019,
    -32956,-32893,-32830,-32767,-32705,-32642,-32579,-32516,
    -32454,-32391,-32329,-32266,-32204,-32141,-32079,-32017,
    -31955,-31892,-31830,-31768,-31706,-31644,-31582,-31520,
    -31458,-31396,-31335,-31273,-31211,-31150,-31088,-31026,
    -30965,-30904,-30842,-30781,-30719,-30658,-30597,-30536,
    -30474,-30413,-30352,-30291,-30230,-30169,-30108,-30048,
    -29987,-29926,-29865,-29805,-29744,-29683,-29623,-29562,
    -29502,-29441,-29381,-29321,-29260,-29200,-29140,-29080,
    -29020,-28959,-28899,-28839,-28779,-28719,-28660,-28600,
    -28540,-28480,-28420,-28361,-28301,-28241,-28182,-28122,
    -28063,-28003,-27944,-27884,-27825,-27766,-27707,-27647,
    -27588,-27529,-27470,-27411,-27352,-27293,-27234,-27175,
    -27116,-27057,-26998,-26940,-26881,-26822,-26763,-26705,
    -26646,-26588,-26529,-26471,-26412,-26354,-26295,-26237,
    -26179,-26120,-26062,-26004,-25946,-25888,-25830,-25772,
    -25714,-25656,-25598,-25540,-25482,-25424,-25366,-25308,
    -25251,-25193,-25135,-25078,-25020,-24962,-24905,-24847,
    -24790,-24732,-24675,-24618,-24560,-24503,-24446,-24389,
    -24331,-24274,-24217,-24160,-24103,-24046,-23989,-23932,
    -23875,-23818,-23761,-23704,-23647,-23591,-23534,-23477,
    -23420,-23364,-23307,-23250,-23194,-23137,-23081,-23024,
    -22968,-22911,-22855,-22799,-22742,-22686,-22630,-22573,
    -22517,-22461,-22405,-22349,-22293,-22237,-22181,-22125,
    -22069,-22013,-21957,-21901,-21845,-21789,-21733,-21678,
    -21622,-21566,-21510,-21455,-21399,-21343,-21288,-21232,
    -21177,-21121,-21066,-21010,-20955,-20900,-20844,-20789,
    -20734,-20678,-20623,-20568,-20513,-20457,-20402,-20347,
    -20292,-20237,-20182,-20127,-20072,-20017,-19962,-19907,
    -19852,-19797,-19742,-19688,-19633,-19578,-19523,-19469,
    -19414,-19359,-19305,-19250,-19195,-19141,-19086,-19032,
    -18977,-18923,-18868,-18814,-18760,-18705,-18651,-18597,
    -18542,-18488,-18434,-18380,-18325,-18271,-18217,-18163,
    -18109,-18055,-18001,-17946,-17892,-17838,-17784,-17731,
    -17677,-17623,-17569,-17515,-17461,-17407,-17353,-17300,
    -17246,-17192,-17138,-17085,-17031,-16977,-16924,-16870,
    -16817,-16763,-16710,-16656,-16603,-16549,-16496,-16442,
    -16389,-16335,-16282,-16229,-16175,-16122,-16069,-16015,
    -15962,-15909,-15856,-15802,-15749,-15696,-15643,-15590,
    -15537,-15484,-15431,-15378,-15325,-15272,-15219,-15166,
    -15113,-15060,-15007,-14954,-14901,-14848,-14795,-14743,
    -14690,-14637,-14584,-14531,-14479,-14426,-14373,-14321,
    -14268,-14215,-14163,-14110,-14057,-14005,-13952,-13900,
    -13847,-13795,-13742,-13690,-13637,-13585,-13533,-13480,
    -13428,-13375,-13323,-13271,-13218,-13166,-13114,-13062,
    -13009,-12957,-12905,-12853,-12800,-12748,-12696,-12644,
    -12592,-12540,-12488,-12436,-12383,-12331,-12279,-12227,
    -12175,-12123,-12071,-12019,-11967,-11916,-11864,-11812,
    -11760,-11708,-11656,-11604,-11552,-11501,-11449,-11397,
    -11345,-11293,-11242,-11190,-11138,-11086,-11035,-10983,
    -10931,-10880,-10828,-10777,-10725,-10673,-10622,-10570,
    -10519,-10467,-10415,-10364,-10312,-10261,-10209,-10158,
    -10106,-10055,-10004,-9952,-9901,-9849,-9798,-9747,
    -9695,-9644,-9592,-9541,-9490,-9438,-9387,-9336,
    -9285,-9233,-9182,-9131,-9080,-9028,-8977,-8926,
    -8875,-8824,-8772,-8721,-8670,-8619,-8568,-8517,
    -8466,-8414,-8363,-8312,-8261,-8210,-8159,-8108,
    -8057,-8006,-7955,-7904,-7853,-7802,-7751,-7700,
    -7649,-7598,-7547,-7496,-7445,-7395,-7344,-7293,
    -7242,-7191,-7140,-7089,-7038,-6988,-6937,-6886,
    -6835,-6784,-6733,-6683,-6632,-6581,-6530,-6480,
    -6429,-6378,-6327,-6277,-6226,-6175,-6124,-6074,
    -6023,-5972,-5922,-5871,-5820,-5770,-5719,-5668,
    -5618,-5567,-5517,-5466,-5415,-5365,-5314,-5264,
    -5213,-5162,-5112,-5061,-5011,-4960,-4910,-4859,
    -4808,-4758,-4707,-4657,-4606,-4556,-4505,-4455,
    -4404,-4354,-4303,-4253,-4202,-4152,-4101,-4051,
    -4001,-3950,-3900,-3849,-3799,-3748,-3698,-3648,
    -3597,-3547,-3496,-3446,-3395,-3345,-3295,-3244,
    -3194,-3144,-3093,-3043,-2992,-2942,-2892,-2841,
    -2791,-2741,-2690,-2640,-2590,-2539,-2489,-2439,
    -2388,-2338,-2288,-2237,-2187,-2137,-2086,-2036,
    -1986,-1935,-1885,-1835,-1784,-1734,-1684,-1633,
    -1583,-1533,-1483,-1432,-1382,-1332,-1281,-1231,
    -1181,-1131,-1080,-1030,-980,-929,-879,-829,
    -779,-728,-678,-628,-578,-527,-477,-427,
    -376,-326,-276,-226,-175,-125,-75,-25,
    25,75,125,175,226,276,326,376,
    427,477,527,578,628,678,728,779,
    829,879,929,980,1030,1080,1131,1181,
    1231,1281,1332,1382,1432,1483,1533,1583,
    1633,1684,1734,1784,1835,1885,1935,1986,
    2036,2086,2137,2187,2237,2288,2338,2388,
    2439,2489,2539,2590,2640,2690,2741,2791,
    2841,2892,2942,2992,3043,3093,3144,3194,
    3244,3295,3345,3395,3446,3496,3547,3597,
    3648,3698,3748,3799,3849,3900,3950,4001,
    4051,4101,4152,4202,4253,4303,4354,4404,
    4455,4505,4556,4606,4657,4707,4758,4808,
    4859,4910,4960,5011,5061,5112,5162,5213,
    5264,5314,5365,5415,5466,5517,5567,5618,
    5668,5719,5770,5820,5871,5922,5972,6023,
    6074,6124,6175,6226,6277,6327,6378,6429,
    6480,6530,6581,6632,6683,6733,6784,6835,
    6886,6937,6988,7038,7089,7140,7191,7242,
    7293,7344,7395,7445,7496,7547,7598,7649,
    7700,7751,7802,7853,7904,7955,8006,8057,
    8108,8159,8210,8261,8312,8363,8414,8466,
    8517,8568,8619,8670,8721,8772,8824,8875,
    8926,8977,9028,9080,9131,9182,9233,9285,
    9336,9387,9438,9490,9541,9592,9644,9695,
    9747,9798,9849,9901,9952,10004,10055,10106,
    10158,10209,10261,10312,10364,10415,10467,10519,
    10570,10622,10673,10725,10777,10828,10880,10931,
    10983,11035,11086,11138,11190,11242,11293,11345,
    11397,11449,11501,11552,11604,11656,11708,11760,
    11812,11864,11916,11967,12019,12071,12123,12175,
    12227,12279,12331,12383,12436,12488,12540,12592,
    12644,12696,12748,12800,12853,12905,12957,13009,
    13062,13114,13166,13218,13271,13323,13375,13428,
    13480,13533,13585,13637,13690,13742,13795,13847,
    13900,13952,14005,14057,14110,14163,14215,14268,
    14321,14373,14426,14479,14531,14584,14637,14690,
    14743,14795,14848,14901,14954,15007,15060,15113,
    15166,15219,15272,15325,15378,15431,15484,15537,
    15590,15643,15696,15749,15802,15856,15909,15962,
    16015,16069,16122,16175,16229,16282,16335,16389,
    16442,16496,16549,16603,16656,16710,16763,16817,
    16870,16924,16977,17031,17085,17138,17192,17246,
    17300,17353,17407,17461,17515,17569,17623,17677,
    17731,17784,17838,17892,17946,18001,18055,18109,
    18163,18217,18271,18325,18380,18434,18488,18542,
    18597,18651,18705,18760,18814,18868,18923,18977,
    19032,19086,19141,19195,19250,19305,19359,19414,
    19469,19523,19578,19633,19688,19742,19797,19852,
    19907,19962,20017,20072,20127,20182,20237,20292,
    20347,20402,20457,20513,20568,20623,20678,20734,
    20789,20844,20900,20955,21010,21066,21121,21177,
    21232,21288,21343,21399,21455,21510,21566,21622,
    21678,21733,21789,21845,21901,21957,22013,22069,
    22125,22181,22237,22293,22349,22405,22461,22517,
    22573,22630,22686,22742,22799,22855,22911,22968,
    23024,23081,23137,23194,23250,23307,23364,23420,
    23477,23534,23591,23647,23704,23761,23818,23875,
    23932,23989,24046,24103,24160,24217,24274,24331,
    24389,24446,24503,24560,24618,24675,24732,24790,
    24847,24905,24962,25020,25078,25135,25193,25251,
    25308,25366,25424,25482,25540,25598,25656,25714,
    25772,25830,25888,25946,26004,26062,26120,26179,
    26237,26295,26354,26412,26471,26529,26588,26646,
    26705,26763,26822,26881,26940,26998,27057,27116,
    27175,27234,27293,27352,27411,27470,27529,27588,
    27647,27707,27766,27825,27884,27944,28003,28063,
    28122,28182,28241,28301,28361,28420,28480,28540,
    28600,28660,28719,28779,28839,28899,28959,29020,
    29080,29140,29200,29260,29321,29381,29441,29502,
    29562,29623,29683,29744,29805,29865,29926,29987,
    30048,30108,30169,30230,30291,30352,30413,30474,
    30536,30597,30658,30719,30781,30842,30904,30965,
    31026,31088,31150,31211,31273,31335,31396,31458,
    31520,31582,31644,31706,31768,31830,31892,31955,
    32017,32079,32141,32204,32266,32329,32391,32454,
    32516,32579,32642,32705,32767,32830,32893,32956,
    33019,33082,33145,33208,33272,33335,33398,33461,
    33525,33588,33652,33715,33779,33843,33906,33970,
    34034,34098,34162,34225,34289,34354,34418,34482,
    34546,34610,34675,34739,34803,34868,34932,34997,
    35062,35126,35191,35256,35321,35385,35450,35515,
    35580,35646,35711,35776,35841,35907,35972,36037,
    36103,36168,36234,36300,36365,36431,36497,36563,
    36629,36695,36761,36827,36893,36959,37026,37092,
    37158,37225,37291,37358,37425,37491,37558,37625,
    37692,37759,37826,37893,37960,38027,38094,38161,
    38229,38296,38364,38431,38499,38566,38634,38702,
    38770,38837,38905,38973,39042,39110,39178,39246,
    39314,39383,39451,39520,39588,39657,39726,39794,
    39863,39932,40001,40070,40139,40208,40278,40347,
    40416,40486,40555,40625,40694,40764,40834,40904,
    40973,41043,41113,41184,41254,41324,41394,41465,
    41535,41605,41676,41747,41817,41888,41959,42030,
    42101,42172,42243,42314,42385,42457,42528,42600,
    42671,42743,42814,42886,42958,43030,43102,43174,
    43246,43318,43390,43463,43535,43608,43680,43753,
    43826,43898,43971,44044,44117,44190,44263,44337,
    44410,44483,44557,44630,44704,44778,44851,44925,
    44999,45073,45147,45221,45296,45370,45444,45519,
    45593,45668,45743,45818,45892,45967,46042,46118,
    46193,46268,46343,46419,46494,46570,46646,46721,
    46797,46873,46949,47025,47102,47178,47254,47331,
    47407,47484,47560,47637,47714,47791,47868,47945,
    48022,48100,48177,48255,48332,48410,48488,48565,
    48643,48721,48799,48878,48956,49034,49113,49191,
    49270,49349,49427,49506,49585,49664,49744,49823,
    49902,49982,50061,50141,50221,50300,50380,50460,
    50540,50621,50701,50781,50862,50942,51023,51104,
    51185,51266,51347,51428,51509,51591,51672,51754,
    51835,51917,51999,52081,52163,52245,52327,52410,
    52492,52575,52657,52740,52823,52906,52989,53072,
    53156,53239,53322,53406,53490,53574,53657,53741,
    53826,53910,53994,54079,54163,54248,54333,54417,
    54502,54587,54673,54758,54843,54929,55015,55100,
    55186,55272,55358,55444,55531,55617,55704,55790,
    55877,55964,56051,56138,56225,56312,56400,56487,
    56575,56663,56751,56839,56927,57015,57104,57192,
    57281,57369,57458,57547,57636,57725,57815,57904,
    57994,58083,58173,58263,58353,58443,58534,58624,
    58715,58805,58896,58987,59078,59169,59261,59352,
    59444,59535,59627,59719,59811,59903,59996,60088,
    60181,60273,60366,60459,60552,60646,60739,60833,
    60926,61020,61114,61208,61302,61396,61491,61585,
    61680,61775,61870,61965,62060,62156,62251,62347,
    62443,62539,62635,62731,62828,62924,63021,63118,
    63215,63312,63409,63506,63604,63702,63799,63897,
    63996,64094,64192,64291,64389,64488,64587,64687,
    64786,64885,64985,65085,65185,65285,65385,65485,
    65586,65686,65787,65888,65989,66091,66192,66294,
    66396,66498,66600,66702,66804,66907,67010,67113,
    67216,67319,67422,67526,67629,67733,67837,67942,
    68046,68151,68255,68360,68465,68570,68676,68781,
    68887,68993,69099,69205,69312,69418,69525,69632,
    69739,69846,69954,70061,70169,70277,70385,70494,
    70602,70711,70820,70929,71038,71147,71257,71367,
    71477,71587,71697,71808,71918,72029,72140,72252,
    72363,72475,72587,72699,72811,72923,73036,73149,
    73262,73375,73488,73602,73715,73829,73944,74058,
    74172,74287,74402,74517,74633,74748,74864,74980,
    75096,75213,75329,75446,75563,75680,75797,75915,
    76033,76151,76269,76388,76506,76625,76744,76864,
    76983,77103,77223,77343,77463,77584,77705,77826,
    77947,78068,78190,78312,78434,78557,78679,78802,
    78925,79048,79172,79296,79420,79544,79668,79793,
    79918,80043,80168,80294,80420,80546,80672,80799,
    80925,81053,81180,81307,81435,81563,81691,81820,
    81949,82078,82207,82336,82466,82596,82726,82857,
    82987,83118,83250,83381,83513,83645,83777,83910,
    84043,84176,84309,84443,84576,84710,84845,84980,
    85114,85250,85385,85521,85657,85793,85930,86066,
    86204,86341,86479,86616,86755,86893,87032,87171,
    87310,87450,87590,87730,87871,88011,88152,88294,
    88435,88577,88720,88862,89005,89148,89292,89435,
    89579,89724,89868,90013,90158,90304,90450,90596,
    90742,90889,91036,91184,91332,91480,91628,91777,
    91926,92075,92225,92375,92525,92675,92826,92978,
    93129,93281,93434,93586,93739,93892,94046,94200,
    94354,94509,94664,94819,94975,95131,95287,95444,
    95601,95758,95916,96074,96233,96391,96551,96710,
    96870,97030,97191,97352,97513,97675,97837,98000,
    98163,98326,98489,98653,98818,98982,99148,99313,
    99479,99645,99812,99979,100146,100314,100482,100651,
    100820,100990,101159,101330,101500,101671,101843,102015,
    102187,102360,102533,102706,102880,103054,103229,103404,
    103580,103756,103933,104109,104287,104465,104643,104821,
    105000,105180,105360,105540,105721,105902,106084,106266,
    106449,106632,106816,107000,107184,107369,107555,107741,
    107927,108114,108301,108489,108677,108866,109055,109245,
    109435,109626,109817,110008,110200,110393,110586,110780,
    110974,111169,111364,111560,111756,111952,112150,112347,
    112546,112744,112944,113143,113344,113545,113746,113948,
    114151,114354,114557,114761,114966,115171,115377,115583,
    115790,115998,116206,116414,116623,116833,117044,117254,
    117466,117678,117891,118104,118318,118532,118747,118963,
    119179,119396,119613,119831,120050,120269,120489,120709,
    120930,121152,121374,121597,121821,122045,122270,122496,
    122722,122949,123176,123404,123633,123863,124093,124324,
    124555,124787,125020,125254,125488,125723,125959,126195,
    126432,126669,126908,127147,127387,127627,127869,128111,
    128353,128597,128841,129086,129332,129578,129825,130073,
    130322,130571,130821,131072,131324,131576,131830,132084,
    132339,132594,132851,133108,133366,133625,133884,134145,
    134406,134668,134931,135195,135459,135725,135991,136258,
    136526,136795,137065,137335,137607,137879,138152,138426,
    138701,138977,139254,139532,139810,140090,140370,140651,
    140934,141217,141501,141786,142072,142359,142647,142936,
    143226,143517,143808,144101,144395,144690,144986,145282,
    145580,145879,146179,146480,146782,147084,147388,147693,
    148000,148307,148615,148924,149235,149546,149859,150172,
    150487,150803,151120,151438,151757,152077,152399,152722,
    153045,153370,153697,154024,154352,154682,155013,155345,
    155678,156013,156349,156686,157024,157363,157704,158046,
    158389,158734,159079,159427,159775,160125,160476,160828,
    161182,161537,161893,162251,162610,162970,163332,163695,
    164060,164426,164793,165162,165532,165904,166277,166651,
    167027,167405,167784,168164,168546,168930,169315,169701,
    170089,170479,170870,171263,171657,172053,172451,172850,
    173251,173653,174057,174463,174870,175279,175690,176102,
    176516,176932,177349,177769,178190,178612,179037,179463,
    179891,180321,180753,181186,181622,182059,182498,182939,
    183382,183827,184274,184722,185173,185625,186080,186536,
    186995,187455,187918,188382,188849,189318,189789,190261,
    190736,191213,191693,192174,192658,193143,193631,194122,
    194614,195109,195606,196105,196606,197110,197616,198125,
    198636,199149,199664,200182,200703,201226,201751,202279,
    202809,203342,203878,204416,204956,205500,206045,206594,
    207145,207699,208255,208815,209376,209941,210509,211079,
    211652,212228,212807,213389,213973,214561,215151,215745,
    216341,216941,217544,218149,218758,219370,219985,220603,
    221225,221849,222477,223108,223743,224381,225022,225666,
    226314,226966,227621,228279,228941,229606,230275,230948,
    231624,232304,232988,233676,234367,235062,235761,236463,
    237170,237881,238595,239314,240036,240763,241493,242228,
    242967,243711,244458,245210,245966,246727,247492,248261,
    249035,249813,250596,251384,252176,252973,253774,254581,
    255392,256208,257029,257855,258686,259522,260363,261209,
    262060,262917,263779,264646,265519,266397,267280,268169,
    269064,269965,270871,271782,272700,273624,274553,275489,
    276430,277378,278332,279292,280258,281231,282210,283195,
    284188,285186,286192,287204,288223,289249,290282,291322,
    292369,293423,294485,295554,296630,297714,298805,299904,
    301011,302126,303248,304379,305517,306664,307819,308983,
    310154,311335,312524,313721,314928,316143,317368,318601,
    319844,321097,322358,323629,324910,326201,327502,328812,
    330133,331464,332805,334157,335519,336892,338276,339671,
    341078,342495,343924,345364,346816,348280,349756,351244,
    352744,354257,355783,357321,358872,360436,362013,363604,
    365208,366826,368459,370105,371765,373440,375130,376835,
    378555,380290,382040,383807,385589,387387,389202,391034,
    392882,394747,396630,398530,400448,402384,404338,406311,
    408303,410314,412344,414395,416465,418555,420666,422798,
    424951,427125,429321,431540,433781,436045,438332,440643,
    442978,445337,447720,450129,452564,455024,457511,460024,
    462565,465133,467730,470355,473009,475692,478406,481150,
    483925,486732,489571,492443,495348,498287,501261,504269,
    507313,510394,513512,516667,519861,523094,526366,529680,
    533034,536431,539870,543354,546881,550455,554074,557741,
    561456,565221,569035,572901,576818,580789,584815,588896,
    593033,597229,601483,605798,610174,614613,619117,623686,
    628323,633028,637803,642651,647572,652568,657640,662792,
    668024,673338,678737,684223,689797,695462,701219,707072,
    713023,719074,725227,731486,737853,744331,750922,757631,
    764460,771411,778490,785699,793041,800521,808143,815910,
    823827,831898,840127,848520,857081,865817,874730,883829,
    893117,902602,912289,922186,932298,942633,953199,964003,
    975054,986361,997931,1009774,1021901,1034322,1047046,1060087,
    1073455,1087164,1101225,1115654,1130465,1145673,1161294,1177345,
    1193846,1210813,1228269,1246234,1264730,1283783,1303416,1323658,
    1344537,1366084,1388330,1411312,1435065,1459630,1485049,1511367,
    1538632,1566898,1596220,1626658,1658278,1691149,1725348,1760956,
    1798063,1836758,1877161,1919378,1963536,2009771,2058233,2109087,
    2162516,2218719,2277919,2340362,2406322,2476104,2550052,2628549,
    2712030,2800983,2895966,2997613,3106651,3223918,3350381,3487165,
    3635590,3797206,3973855,4167737,4381502,4618375,4882318,5178251,
    5512368,5892567,6329090,6835455,7429880,8137527,8994149,10052327,
    11392683,13145455,15535599,18988036,24413316,34178904,56965752,170910304
};


const int finesine[10240] =
{
    25,75,125,175,226,276,326,376,
    427,477,527,578,628,678,728,779,
    829,879,929,980,1030,1080,1130,1181,
    1231,1281,1331,1382,1432,1482,1532,1583,
    1633,1683,1733,1784,1834,1884,1934,1985,
    2035,2085,2135,2186,2236,2286,2336,2387,
    2437,2487,2537,2587,2638,2688,2738,2788,
    2839,2889,2939,2989,3039,3090,3140,3190,
    3240,3291,3341,3391,3441,3491,3541,3592,
    3642,3692,3742,3792,3843,3893,3943,3993,
    4043,4093,4144,4194,4244,4294,4344,4394,
    4445,4495,4545,4595,4645,4695,4745,4796,
    4846,4896,4946,4996,5046,5096,5146,5197,
    5247,5297,5347,5397,5447,5497,5547,5597,
    5647,5697,5748,5798,5848,5898,5948,5998,
    6048,6098,6148,6198,6248,6298,6348,6398,
    6448,6498,6548,6598,6648,6698,6748,6798,
    6848,6898,6948,6998,7048,7098,7148,7198,
    7248,7298,7348,7398,7448,7498,7548,7598,
    7648,7697,7747,7797,7847,7897,7947,7997,
    8047,8097,8147,8196,8246,8296,8346,8396,
    8446,8496,8545,8595,8645,8695,8745,8794,
    8844,8894,8944,8994,9043,9093,9143,9193,
    9243,9292,9342,9392,9442,9491,9541,9591,
    9640,9690,9740,9790,9839,9889,9939,9988,
    10038,10088,10137,10187,10237,10286,10336,10386,
    10435,10485,10534,10584,10634,10683,10733,10782,
    10832,10882,10931,10981,11030,11080,11129,11179,
    11228,11278,11327,11377,11426,11476,11525,11575,
    11624,11674,11723,11773,11822,11872,11921,11970,
    12020,12069,12119,12168,12218,12267,12316,12366,
    12415,12464,12514,12563,12612,12662,12711,12760,
    12810,12859,12908,12957,13007,13056,13105,13154,
    13204,13253,13302,13351,13401,13450,13499,13548,
    13597,13647,13696,13745,13794,13843,13892,13941,
    13990,14040,14089,14138,14187,14236,14285,14334,
    14383,14432,14481,14530,14579,14628,14677,14726,
    14775,14824,14873,14922,14971,15020,15069,15118,
    15167,15215,15264,15313,15362,15411,15460,15509,
    15557,15606,15655,15704,15753,15802,15850,15899,
    15948,15997,16045,16094,16143,16191,16240,16289,
    16338,16386,16435,16484,16532,16581,16629,16678,
    16727,16775,16824,16872,16921,16970,17018,17067,
    17115,17164,17212,17261,17309,17358,17406,17455,
    17503,17551,17600,17648,17697,17745,17793,17842,
    17890,17939,17987,18035,18084,18132,18180,18228,
    18277,18325,18373,18421,18470,18518,18566,18614,
    18663,18711,18759,18807,18855,18903,18951,19000,
    19048,19096,19144,19192,19240,19288,19336,19384,
    19432,19480,19528,19576,19624,19672,19720,19768,
    19816,19864,19912,19959,20007,20055,20103,20151,
    20199,20246,20294,20342,20390,20438,20485,20533,
    20581,20629,20676,20724,20772,20819,20867,20915,
    20962,21010,21057,21105,21153,21200,21248,21295,
    21343,21390,21438,21485,21533,21580,21628,21675,
    21723,21770,21817,21865,21912,21960,22007,22054,
    22102,22149,22196,22243,22291,22338,22385,22433,
    22480,22527,22574,22621,22668,22716,22763,22810,
    22857,22904,22951,22998,23045,23092,23139,23186,
    23233,23280,23327,23374,23421,23468,23515,23562,
    23609,23656,23703,23750,23796,23843,23890,23937,
    23984,24030,24077,24124,24171,24217,24264,24311,
    24357,24404,24451,24497,24544,24591,24637,24684,
    24730,24777,24823,24870,24916,24963,25009,25056,
    25102,25149,25195,25241,25288,25334,25381,25427,
    25473,25520,25566,25612,25658,25705,25751,25797,
    25843,25889,25936,25982,26028,26074,26120,26166,
    26212,26258,26304,26350,26396,26442,26488,26534,
    26580,26626,26672,26718,26764,26810,26856,26902,
    26947,26993,27039,27085,27131,27176,27222,27268,
    27313,27359,27405,27450,27496,27542,27587,27633,
    27678,27724,27770,27815,27861,27906,27952,27997,
    28042,28088,28133,28179,28224,28269,28315,28360,
    28405,28451,28496,28541,28586,28632,28677,28722,
    28767,28812,28858,28903,28948,28993,29038,29083,
    29128,29173,29218,29263,29308,29353,29398,29443,
    29488,29533,29577,29622,29667,29712,29757,29801,
    29846,29891,29936,29980,30025,30070,30114,30159,
    30204,30248,30293,30337,30382,30426,30471,30515,
    30560,30604,30649,30693,30738,30782,30826,30871,
    30915,30959,31004,31048,31092,31136,31181,31225,
    31269,31313,31357,31402,31446,31490,31534,31578,
    31622,31666,31710,31754,31798,31842,31886,31930,
    31974,32017,32061,32105,32149,32193,32236,32280,
    32324,32368,32411,32455,32499,32542,32586,32630,
    32673,32717,32760,32804,32847,32891,32934,32978,
    33021,33065,33108,33151,33195,33238,33281,33325,
    33368,33411,33454,33498,33541,33584,33627,33670,
    33713,33756,33799,33843,33886,33929,33972,34015,
    34057,34100,34143,34186,34229,34272,34315,34358,
    34400,34443,34486,34529,34571,34614,34657,34699,
    34742,34785,34827,34870,34912,34955,34997,35040,
    35082,35125,35167,35210,35252,35294,35337,35379,
    35421,35464,35506,35548,35590,35633,35675,35717,
    35759,35801,35843,35885,35927,35969,36011,36053,
    36095,36137,36179,36221,36263,36305,36347,36388,
    36430,36472,36514,36555,36597,36639,36681,36722,
    36764,36805,36847,36889,36930,36972,37013,37055,
    37096,37137,37179,37220,37262,37303,37344,37386,
    37427,37468,37509,37551,37592,37633,37674,37715,
    37756,37797,37838,37879,37920,37961,38002,38043,
    38084,38125,38166,38207,38248,38288,38329,38370,
    38411,38451,38492,38533,38573,38614,38655,38695,
    38736,38776,38817,38857,38898,38938,38979,39019,
    39059,39100,39140,39180,39221,39261,39301,39341,
    39382,39422,39462,39502,39542,39582,39622,39662,
    39702,39742,39782,39822,39862,39902,39942,39982,
    40021,40061,40101,40141,40180,40220,40260,40300,
    40339,40379,40418,40458,40497,40537,40576,40616,
    40655,40695,40734,40773,40813,40852,40891,40931,
    40970,41009,41048,41087,41127,41166,41205,41244,
    41283,41322,41361,41400,41439,41478,41517,41556,
    41595,41633,41672,41711,41750,41788,41827,41866,
    41904,41943,41982,42020,42059,42097,42136,42174,
    42213,42251,42290,42328,42366,42405,42443,42481,
    42520,42558,42596,42634,42672,42711,42749,42787,
    42825,42863,42901,42939,42977,43015,43053,43091,
    43128,43166,43204,43242,43280,43317,43355,43393,
    43430,43468,43506,43543,43581,43618,43656,43693,
    43731,43768,43806,43843,43880,43918,43955,43992,
    44029,44067,44104,44141,44178,44215,44252,44289,
    44326,44363,44400,44437,44474,44511,44548,44585,
    44622,44659,44695,44732,44769,44806,44842,44879,
    44915,44952,44989,45025,45062,45098,45135,45171,
    45207,45244,45280,45316,45353,45389,45425,45462,
    45498,45534,45570,45606,45642,45678,45714,45750,
    45786,45822,45858,45894,45930,45966,46002,46037,
    46073,46109,46145,46180,46216,46252,46287,46323,
    46358,46394,46429,46465,46500,46536,46571,46606,
    46642,46677,46712,46747,46783,46818,46853,46888,
    46923,46958,46993,47028,47063,47098,47133,47168,
    47203,47238,47273,47308,47342,47377,47412,47446,
    47481,47516,47550,47585,47619,47654,47688,47723,
    47757,47792,47826,47860,47895,47929,47963,47998,
    48032,48066,48100,48134,48168,48202,48237,48271,
    48305,48338,48372,48406,48440,48474,48508,48542,
    48575,48609,48643,48676,48710,48744,48777,48811,
    48844,48878,48911,48945,48978,49012,49045,49078,
    49112,49145,49178,49211,49244,49278,49311,49344,
    49377,49410,49443,49476,49509,49542,49575,49608,
    49640,49673,49706,49739,49771,49804,49837,49869,
    49902,49935,49967,50000,50032,50065,50097,50129,
    50162,50194,50226,50259,50291,50323,50355,50387,
    50420,50452,50484,50516,50548,50580,50612,50644,
    50675,50707,50739,50771,50803,50834,50866,50898,
    50929,50961,50993,51024,51056,51087,51119,51150,
    51182,51213,51244,51276,51307,51338,51369,51401,
    51432,51463,51494,51525,51556,51587,51618,51649,
    51680,51711,51742,51773,51803,51834,51865,51896,
    51926,51957,51988,52018,52049,52079,52110,52140,
    52171,52201,52231,52262,52292,52322,52353,52383,
    52413,52443,52473,52503,52534,52564,52594,52624,
    52653,52683,52713,52743,52773,52803,52832,52862,
    52892,52922,52951,52981,53010,53040,53069,53099,
    53128,53158,53187,53216,53246,53275,53304,53334,
    53363,53392,53421,53450,53479,53508,53537,53566,
    53595,53624,53653,53682,53711,53739,53768,53797,
    53826,53854,53883,53911,53940,53969,53997,54026,
    54054,54082,54111,54139,54167,54196,54224,54252,
    54280,54308,54337,54365,54393,54421,54449,54477,
    54505,54533,54560,54588,54616,54644,54672,54699,
    54727,54755,54782,54810,54837,54865,54892,54920,
    54947,54974,55002,55029,55056,55084,55111,55138,
    55165,55192,55219,55246,55274,55300,55327,55354,
    55381,55408,55435,55462,55489,55515,55542,55569,
    55595,55622,55648,55675,55701,55728,55754,55781,
    55807,55833,55860,55886,55912,55938,55965,55991,
    56017,56043,56069,56095,56121,56147,56173,56199,
    56225,56250,56276,56302,56328,56353,56379,56404,
    56430,56456,56481,56507,56532,56557,56583,56608,
    56633,56659,56684,56709,56734,56760,56785,56810,
    56835,56860,56885,56910,56935,56959,56984,57009,
    57034,57059,57083,57108,57133,57157,57182,57206,
    57231,57255,57280,57304,57329,57353,57377,57402,
    57426,57450,57474,57498,57522,57546,57570,57594,
    57618,57642,57666,57690,57714,57738,57762,57785,
    57809,57833,57856,57880,57903,57927,57950,57974,
    57997,58021,58044,58067,58091,58114,58137,58160,
    58183,58207,58230,58253,58276,58299,58322,58345,
    58367,58390,58413,58436,58459,58481,58504,58527,
    58549,58572,58594,58617,58639,58662,58684,58706,
    58729,58751,58773,58795,58818,58840,58862,58884,
    58906,58928,58950,58972,58994,59016,59038,59059,
    59081,59103,59125,59146,59168,59190,59211,59233,
    59254,59276,59297,59318,59340,59361,59382,59404,
    59425,59446,59467,59488,59509,59530,59551,59572,
    59593,59614,59635,59656,59677,59697,59718,59739,
    59759,59780,59801,59821,59842,59862,59883,59903,
    59923,59944,59964,59984,60004,60025,60045,60065,
    60085,60105,60125,60145,60165,60185,60205,60225,
    60244,60264,60284,60304,60323,60343,60363,60382,
    60402,60421,60441,60460,60479,60499,60518,60537,
    60556,60576,60595,60614,60633,60652,60671,60690,
    60709,60728,60747,60766,60785,60803,60822,60841,
    60859,60878,60897,60915,60934,60952,60971,60989,
    61007,61026,61044,61062,61081,61099,61117,61135,
    61153,61171,61189,61207,61225,61243,61261,61279,
    61297,61314,61332,61350,61367,61385,61403,61420,
    61438,61455,61473,61490,61507,61525,61542,61559,
    61577,61594,61611,61628,61645,61662,61679,61696,
    61713,61730,61747,61764,61780,61797,61814,61831,
    61847,61864,61880,61897,61913,61930,61946,61963,
    61979,61995,62012,62028,62044,62060,62076,62092,
    62108,62125,62141,62156,62172,62188,62204,62220,
    62236,62251,62267,62283,62298,62314,62329,62345,
    62360,62376,62391,62407,62422,62437,62453,62468,
    62483,62498,62513,62528,62543,62558,62573,62588,
    62603,62618,62633,62648,62662,62677,62692,62706,
    62721,62735,62750,62764,62779,62793,62808,62822,
    62836,62850,62865,62879,62893,62907,62921,62935,
    62949,62963,62977,62991,63005,63019,63032,63046,
    63060,63074,63087,63101,63114,63128,63141,63155,
    63168,63182,63195,63208,63221,63235,63248,63261,
    63274,63287,63300,63313,63326,63339,63352,63365,
    63378,63390,63403,63416,63429,63441,63454,63466,
    63479,63491,63504,63516,63528,63541,63553,63565,
    63578,63590,63602,63614,63626,63638,63650,63662,
    63674,63686,63698,63709,63721,63733,63745,63756,
    63768,63779,63791,63803,63814,63825,63837,63848,
    63859,63871,63882,63893,63904,63915,63927,63938,
    63949,63960,63971,63981,63992,64003,64014,64025,
    64035,64046,64057,64067,64078,64088,64099,64109,
    64120,64130,64140,64151,64161,64171,64181,64192,
    64202,64212,64222,64232,64242,64252,64261,64271,
    64281,64291,64301,64310,64320,64330,64339,64349,
    64358,64368,64377,64387,64396,64405,64414,64424,
    64433,64442,64451,64460,64469,64478,64487,64496,
    64505,64514,64523,64532,64540,64549,64558,64566,
    64575,64584,64592,64601,64609,64617,64626,64634,
    64642,64651,64659,64667,64675,64683,64691,64699,
    64707,64715,64723,64731,64739,64747,64754,64762,
    64770,64777,64785,64793,64800,64808,64815,64822,
    64830,64837,64844,64852,64859,64866,64873,64880,
    64887,64895,64902,64908,64915,64922,64929,64936,
    64943,64949,64956,64963,64969,64976,64982,64989,
    64995,65002,65008,65015,65021,65027,65033,65040,
    65046,65052,65058,65064,65070,65076,65082,65088,
    65094,65099,65105,65111,65117,65122,65128,65133,
    65139,65144,65150,65155,65161,65166,65171,65177,
    65182,65187,65192,65197,65202,65207,65212,65217,
    65222,65227,65232,65237,65242,65246,65251,65256,
    65260,65265,65270,65274,65279,65283,65287,65292,
    65296,65300,65305,65309,65313,65317,65321,65325,
    65329,65333,65337,65341,65345,65349,65352,65356,
    65360,65363,65367,65371,65374,65378,65381,65385,
    65388,65391,65395,65398,65401,65404,65408,65411,
    65414,65417,65420,65423,65426,65429,65431,65434,
    65437,65440,65442,65445,65448,65450,65453,65455,
    65458,65460,65463,65465,65467,65470,65472,65474,
    65476,65478,65480,65482,65484,65486,65488,65490,
    65492,65494,65496,65497,65499,65501,65502,65504,
    65505,65507,65508,65510,65511,65513,65514,65515,
    65516,65518,65519,65520,65521,65522,65523,65524,
    65525,65526,65527,65527,65528,65529,65530,65530,
    65531,65531,65532,65532,65533,65533,65534,65534,
    65534,65535,65535,65535,65535,65535,65535,65535,
    65535,65535,65535,65535,65535,65535,65535,65534,
    65534,65534,65533,65533,65532,65532,65531,65531,
    65530,65530,65529,65528,65527,65527,65526,65525,
    65524,65523,65522,65521,65520,65519,65518,65516,
    65515,65514,65513,65511,65510,65508,65507,65505,
    65504,65502,65501,65499,65497,65496,65494,65492,
    65490,65488,65486,65484,65482,65480,65478,65476,
    65474,65472,65470,65467,65465,65463,65460,65458,
    65455,65453,65450,65448,65445,65442,65440,65437,
    65434,65431,65429,65426,65423,65420,65417,65414,
    65411,65408,65404,65401,65398,65395,65391,65388,
    65385,65381,65378,65374,65371,65367,65363,65360,
    65356,65352,65349,65345,65341,65337,65333,65329,
    65325,65321,65317,65313,65309,65305,65300,65296,
    65292,65287,65283,65279,65274,65270,65265,65260,
    65256,65251,65246,65242,65237,65232,65227,65222,
    65217,65212,65207,65202,65197,65192,65187,65182,
    65177,65171,65166,65161,65155,65150,65144,65139,
    65133,65128,65122,65117,65111,65105,65099,65094,
    65088,65082,65076,65070,65064,65058,65052,65046,
    65040,65033,65027,65021,65015,65008,65002,64995,
    64989,64982,64976,64969,64963,64956,64949,64943,
    64936,64929,64922,64915,64908,64902,64895,64887,
    64880,64873,64866,64859,64852,64844,64837,64830,
    64822,64815,64808,64800,64793,64785,64777,64770,
    64762,64754,64747,64739,64731,64723,64715,64707,
    64699,64691,64683,64675,64667,64659,64651,64642,
    64634,64626,64617,64609,64600,64592,64584,64575,
    64566,64558,64549,64540,64532,64523,64514,64505,
    64496,64487,64478,64469,64460,64451,64442,64433,
    64424,64414,64405,64396,64387,64377,64368,64358,
    64349,64339,64330,64320,64310,64301,64291,64281,
    64271,64261,64252,64242,64232,64222,64212,64202,
    64192,64181,64171,64161,64151,64140,64130,64120,
    64109,64099,64088,64078,64067,64057,64046,64035,
    64025,64014,64003,63992,63981,63971,63960,63949,
    63938,63927,63915,63904,63893,63882,63871,63859,
    63848,63837,63825,63814,63803,63791,63779,63768,
    63756,63745,63733,63721,63709,63698,63686,63674,
    63662,63650,63638,63626,63614,63602,63590,63578,
    63565,63553,63541,63528,63516,63504,63491,63479,
    63466,63454,63441,63429,63416,63403,63390,63378,
    63365,63352,63339,63326,63313,63300,63287,63274,
    63261,63248,63235,63221,63208,63195,63182,63168,
    63155,63141,63128,63114,63101,63087,63074,63060,
    63046,63032,63019,63005,62991,62977,62963,62949,
    62935,62921,62907,62893,62879,62865,62850,62836,
    62822,62808,62793,62779,62764,62750,62735,62721,
    62706,62692,62677,62662,62648,62633,62618,62603,
    62588,62573,62558,62543,62528,62513,62498,62483,
    62468,62453,62437,62422,62407,62391,62376,62360,
    62345,62329,62314,62298,62283,62267,62251,62236,
    62220,62204,62188,62172,62156,62141,62125,62108,
    62092,62076,62060,62044,62028,62012,61995,61979,
    61963,61946,61930,61913,61897,61880,61864,61847,
    61831,61814,61797,61780,61764,61747,61730,61713,
    61696,61679,61662,61645,61628,61611,61594,61577,
    61559,61542,61525,61507,61490,61473,61455,61438,
    61420,61403,61385,61367,61350,61332,61314,61297,
    61279,61261,61243,61225,61207,61189,61171,61153,
    61135,61117,61099,61081,61062,61044,61026,61007,
    60989,60971,60952,60934,60915,60897,60878,60859,
    60841,60822,60803,60785,60766,60747,60728,60709,
    60690,60671,60652,60633,60614,60595,60576,60556,
    60537,60518,60499,60479,60460,60441,60421,60402,
    60382,60363,60343,60323,60304,60284,60264,60244,
    60225,60205,60185,60165,60145,60125,60105,60085,
    60065,60045,60025,60004,59984,59964,59944,59923,
    59903,59883,59862,59842,59821,59801,59780,59759,
    59739,59718,59697,59677,59656,59635,59614,59593,
    59572,59551,59530,59509,59488,59467,59446,59425,
    59404,59382,59361,59340,59318,59297,59276,59254,
    59233,59211,59190,59168,59146,59125,59103,59081,
    59059,59038,59016,58994,58972,58950,58928,58906,
    58884,58862,58840,58818,58795,58773,58751,58729,
    58706,58684,58662,58639,58617,58594,58572,58549,
    58527,58504,58481,58459,58436,58413,58390,58367,
    58345,58322,58299,58276,58253,58230,58207,58183,
    58160,58137,58114,58091,58067,58044,58021,57997,
    57974,57950,57927,57903,57880,57856,57833,57809,
    57785,57762,57738,57714,57690,57666,57642,57618,
    57594,57570,57546,57522,57498,57474,57450,57426,
    57402,57377,57353,57329,57304,57280,57255,57231,
    57206,57182,57157,57133,57108,57083,57059,57034,
    57009,56984,56959,56935,56910,56885,56860,56835,
    56810,56785,56760,56734,56709,56684,56659,56633,
    56608,56583,56557,56532,56507,56481,56456,56430,
    56404,56379,56353,56328,56302,56276,56250,56225,
    56199,56173,56147,56121,56095,56069,56043,56017,
    55991,55965,55938,55912,55886,55860,55833,55807,
    55781,55754,55728,55701,55675,55648,55622,55595,
    55569,55542,55515,55489,55462,55435,55408,55381,
    55354,55327,55300,55274,55246,55219,55192,55165,
    55138,55111,55084,55056,55029,55002,54974,54947,
    54920,54892,54865,54837,54810,54782,54755,54727,
    54699,54672,54644,54616,54588,54560,54533,54505,
    54477,54449,54421,54393,54365,54337,54308,54280,
    54252,54224,54196,54167,54139,54111,54082,54054,
    54026,53997,53969,53940,53911,53883,53854,53826,
    53797,53768,53739,53711,53682,53653,53624,53595,
    53566,53537,53508,53479,53450,53421,53392,53363,
    53334,53304,53275,53246,53216,53187,53158,53128,
    53099,53069,53040,53010,52981,52951,52922,52892,
    52862,52832,52803,52773,52743,52713,52683,52653,
    52624,52594,52564,52534,52503,52473,52443,52413,
    52383,52353,52322,52292,52262,52231,52201,52171,
    52140,52110,52079,52049,52018,51988,51957,51926,
    51896,51865,51834,51803,51773,51742,51711,51680,
    51649,51618,51587,51556,51525,51494,51463,51432,
    51401,51369,51338,51307,51276,51244,51213,51182,
    51150,51119,51087,51056,51024,50993,50961,50929,
    50898,50866,50834,50803,50771,50739,50707,50675,
    50644,50612,50580,50548,50516,50484,50452,50420,
    50387,50355,50323,50291,50259,50226,50194,50162,
    50129,50097,50065,50032,50000,49967,49935,49902,
    49869,49837,49804,49771,49739,49706,49673,49640,
    49608,49575,49542,49509,49476,49443,49410,49377,
    49344,49311,49278,49244,49211,49178,49145,49112,
    49078,49045,49012,48978,48945,48911,48878,48844,
    48811,48777,48744,48710,48676,48643,48609,48575,
    48542,48508,48474,48440,48406,48372,48338,48304,
    48271,48237,48202,48168,48134,48100,48066,48032,
    47998,47963,47929,47895,47860,47826,47792,47757,
    47723,47688,47654,47619,47585,47550,47516,47481,
    47446,47412,47377,47342,47308,47273,47238,47203,
    47168,47133,47098,47063,47028,46993,46958,46923,
    46888,46853,46818,46783,46747,46712,46677,46642,
    46606,46571,46536,46500,46465,46429,46394,46358,
    46323,46287,46252,46216,46180,46145,46109,46073,
    46037,46002,45966,45930,45894,45858,45822,45786,
    45750,45714,45678,45642,45606,45570,45534,45498,
    45462,45425,45389,45353,45316,45280,45244,45207,
    45171,45135,45098,45062,45025,44989,44952,44915,
    44879,44842,44806,44769,44732,44695,44659,44622,
    44585,44548,44511,44474,44437,44400,44363,44326,
    44289,44252,44215,44178,44141,44104,44067,44029,
    43992,43955,43918,43880,43843,43806,43768,43731,
    43693,43656,43618,43581,43543,43506,43468,43430,
    43393,43355,43317,43280,43242,43204,43166,43128,
    43091,43053,43015,42977,42939,42901,42863,42825,
    42787,42749,42711,42672,42634,42596,42558,42520,
    42481,42443,42405,42366,42328,42290,42251,42213,
    42174,42136,42097,42059,42020,41982,41943,41904,
    41866,41827,41788,41750,41711,41672,41633,41595,
    41556,41517,41478,41439,41400,41361,41322,41283,
    41244,41205,41166,41127,41088,41048,41009,40970,
    40931,40891,40852,40813,40773,40734,40695,40655,
    40616,40576,40537,40497,40458,40418,40379,40339,
    40300,40260,40220,40180,40141,40101,40061,40021,
    39982,39942,39902,39862,39822,39782,39742,39702,
    39662,39622,39582,39542,39502,39462,39422,39382,
    39341,39301,39261,39221,39180,39140,39100,39059,
    39019,38979,38938,38898,38857,38817,38776,38736,
    38695,38655,38614,38573,38533,38492,38451,38411,
    38370,38329,38288,38248,38207,38166,38125,38084,
    38043,38002,37961,37920,37879,37838,37797,37756,
    37715,37674,37633,37592,37551,37509,37468,37427,
    37386,37344,37303,37262,37220,37179,37137,37096,
    37055,37013,36972,36930,36889,36847,36805,36764,
    36722,36681,36639,36597,36556,36514,36472,36430,
    36388,36347,36305,36263,36221,36179,36137,36095,
    36053,36011,35969,35927,35885,35843,35801,35759,
    35717,35675,35633,35590,35548,35506,35464,35421,
    35379,35337,35294,35252,35210,35167,35125,35082,
    35040,34997,34955,34912,34870,34827,34785,34742,
    34699,34657,34614,34571,34529,34486,34443,34400,
    34358,34315,34272,34229,34186,34143,34100,34057,
    34015,33972,33929,33886,33843,33799,33756,33713,
    33670,33627,33584,33541,33498,33454,33411,33368,
    33325,33281,33238,33195,33151,33108,33065,33021,
    32978,32934,32891,32847,32804,32760,32717,32673,
    32630,32586,32542,32499,32455,32411,32368,32324,
    32280,32236,32193,32149,32105,32061,32017,31974,
    31930,31886,31842,31798,31754,31710,31666,31622,
    31578,31534,31490,31446,31402,31357,31313,31269,
    31225,31181,31136,31092,31048,31004,30959,30915,
    30871,30826,30782,30738,30693,30649,30604,30560,
    30515,30471,30426,30382,30337,30293,30248,30204,
    30159,30114,30070,30025,29980,29936,29891,29846,
    29801,29757,29712,29667,29622,29577,29533,29488,
    29443,29398,29353,29308,29263,29218,29173,29128,
    29083,29038,28993,28948,28903,28858,28812,28767,
    28722,28677,28632,28586,28541,28496,28451,28405,
    28360,28315,28269,28224,28179,28133,28088,28042,
    27997,27952,27906,27861,27815,27770,27724,27678,
    27633,27587,27542,27496,27450,27405,27359,27313,
    27268,27222,27176,27131,27085,27039,26993,26947,
    26902,26856,26810,26764,26718,26672,26626,26580,
    26534,26488,26442,26396,26350,26304,26258,26212,
    26166,26120,26074,26028,25982,25936,25889,25843,
    25797,25751,25705,25658,25612,25566,25520,25473,
    25427,25381,25334,25288,25241,25195,25149,25102,
    25056,25009,24963,24916,24870,24823,24777,24730,
    24684,24637,24591,24544,24497,24451,24404,24357,
    24311,24264,24217,24171,24124,24077,24030,23984,
    23937,23890,23843,23796,23750,23703,23656,23609,
    23562,23515,23468,23421,23374,23327,23280,23233,
    23186,23139,23092,23045,22998,22951,22904,22857,
    22810,22763,22716,22668,22621,22574,22527,22480,
    22433,22385,22338,22291,22243,22196,22149,22102,
    22054,22007,21960,21912,21865,21817,21770,21723,
    21675,21628,21580,21533,21485,21438,21390,21343,
    21295,21248,21200,21153,21105,21057,21010,20962,
    20915,20867,20819,20772,20724,20676,20629,20581,
    20533,20485,20438,20390,20342,20294,20246,20199,
    20151,20103,20055,20007,19959,19912,19864,19816,
    19768,19720,19672,19624,19576,19528,19480,19432,
    19384,19336,19288,19240,19192,19144,19096,19048,
    19000,18951,18903,18855,18807,18759,18711,18663,
    18614,18566,18518,18470,18421,18373,18325,18277,
    18228,18180,18132,18084,18035,17987,17939,17890,
    17842,17793,17745,17697,17648,17600,17551,17503,
    17455,17406,17358,17309,17261,17212,17164,17115,
    17067,17018,16970,16921,16872,16824,16775,16727,
    16678,16629,16581,16532,16484,16435,16386,16338,
    16289,16240,16191,16143,16094,16045,15997,15948,
    15899,15850,15802,15753,15704,15655,15606,15557,
    15509,15460,15411,15362,15313,15264,15215,15167,
    15118,15069,15020,14971,14922,14873,14824,14775,
    14726,14677,14628,14579,14530,14481,14432,14383,
    14334,14285,14236,14187,14138,14089,14040,13990,
    13941,13892,13843,13794,13745,13696,13646,13597,
    13548,13499,13450,13401,13351,13302,13253,13204,
    13154,13105,13056,13007,12957,12908,12859,12810,
    12760,12711,12662,12612,12563,12514,12464,12415,
    12366,12316,12267,12218,12168,12119,12069,12020,
    11970,11921,11872,11822,11773,11723,11674,11624,
    11575,11525,11476,11426,11377,11327,11278,11228,
    11179,11129,11080,11030,10981,10931,10882,10832,
    10782,10733,10683,10634,10584,10534,10485,10435,
    10386,10336,10286,10237,10187,10137,10088,10038,
    9988,9939,9889,9839,9790,9740,9690,9640,
    9591,9541,9491,9442,9392,9342,9292,9243,
    9193,9143,9093,9043,8994,8944,8894,8844,
    8794,8745,8695,8645,8595,8545,8496,8446,
    8396,8346,8296,8246,8196,8147,8097,8047,
    7997,7947,7897,7847,7797,7747,7697,7648,
    7598,7548,7498,7448,7398,7348,7298,7248,
    7198,7148,7098,7048,6998,6948,6898,6848,
    6798,6748,6698,6648,6598,6548,6498,6448,
    6398,6348,6298,6248,6198,6148,6098,6048,
    5998,5948,5898,5848,5798,5748,5697,5647,
    5597,5547,5497,5447,5397,5347,5297,5247,
    5197,5146,5096,5046,4996,4946,4896,4846,
    4796,4745,4695,4645,4595,4545,4495,4445,
    4394,4344,4294,4244,4194,4144,4093,4043,
    3993,3943,3893,3843,3792,3742,3692,3642,
    3592,3541,3491,3441,3391,3341,3291,3240,
    3190,3140,3090,3039,2989,2939,2889,2839,
    2788,2738,2688,2638,2587,2537,2487,2437,
    2387,2336,2286,2236,2186,2135,2085,2035,
    1985,1934,1884,1834,1784,1733,1683,1633,
    1583,1532,1482,1432,1382,1331,1281,1231,
    1181,1130,1080,1030,980,929,879,829,
    779,728,678,628,578,527,477,427,
    376,326,276,226,175,125,75,25,
    -25,-75,-125,-175,-226,-276,-326,-376,
    -427,-477,-527,-578,-628,-678,-728,-779,
    -829,-879,-929,-980,-1030,-1080,-1130,-1181,
    -1231,-1281,-1331,-1382,-1432,-1482,-1532,-1583,
    -1633,-1683,-1733,-1784,-1834,-1884,-1934,-1985,
    -2035,-2085,-2135,-2186,-2236,-2286,-2336,-2387,
    -2437,-2487,-2537,-2588,-2638,-2688,-2738,-2788,
    -2839,-2889,-2939,-2989,-3039,-3090,-3140,-3190,
    -3240,-3291,-3341,-3391,-3441,-3491,-3541,-3592,
    -3642,-3692,-3742,-3792,-3843,-3893,-3943,-3993,
    -4043,-4093,-4144,-4194,-4244,-4294,-4344,-4394,
    -4445,-4495,-4545,-4595,-4645,-4695,-4745,-4796,
    -4846,-4896,-4946,-4996,-5046,-5096,-5146,-5197,
    -5247,-5297,-5347,-5397,-5447,-5497,-5547,-5597,
    -5647,-5697,-5748,-5798,-5848,-5898,-5948,-5998,
    -6048,-6098,-6148,-6198,-6248,-6298,-6348,-6398,
    -6448,-6498,-6548,-6598,-6648,-6698,-6748,-6798,
    -6848,-6898,-6948,-6998,-7048,-7098,-7148,-7198,
    -7248,-7298,-7348,-7398,-7448,-7498,-7548,-7598,
    -7648,-7697,-7747,-7797,-7847,-7897,-7947,-7997,
    -8047,-8097,-8147,-8196,-8246,-8296,-8346,-8396,
    -8446,-8496,-8545,-8595,-8645,-8695,-8745,-8794,
    -8844,-8894,-8944,-8994,-9043,-9093,-9143,-9193,
    -9243,-9292,-9342,-9392,-9442,-9491,-9541,-9591,
    -9640,-9690,-9740,-9790,-9839,-9889,-9939,-9988,
    -10038,-10088,-10137,-10187,-10237,-10286,-10336,-10386,
    -10435,-10485,-10534,-10584,-10634,-10683,-10733,-10782,
    -10832,-10882,-10931,-10981,-11030,-11080,-11129,-11179,
    -11228,-11278,-11327,-11377,-11426,-11476,-11525,-11575,
    -11624,-11674,-11723,-11773,-11822,-11872,-11921,-11970,
    -12020,-12069,-12119,-12168,-12218,-12267,-12316,-12366,
    -12415,-12464,-12514,-12563,-12612,-12662,-12711,-12760,
    -12810,-12859,-12908,-12957,-13007,-13056,-13105,-13154,
    -13204,-13253,-13302,-13351,-13401,-13450,-13499,-13548,
    -13597,-13647,-13696,-13745,-13794,-13843,-13892,-13941,
    -13990,-14040,-14089,-14138,-14187,-14236,-14285,-14334,
    -14383,-14432,-14481,-14530,-14579,-14628,-14677,-14726,
    -14775,-14824,-14873,-14922,-14971,-15020,-15069,-15118,
    -15167,-15215,-15264,-15313,-15362,-15411,-15460,-15509,
    -15557,-15606,-15655,-15704,-15753,-15802,-15850,-15899,
    -15948,-15997,-16045,-16094,-16143,-16191,-16240,-16289,
    -16338,-16386,-16435,-16484,-16532,-16581,-16629,-16678,
    -16727,-16775,-16824,-16872,-16921,-16970,-17018,-17067,
    -17115,-17164,-17212,-17261,-17309,-17358,-17406,-17455,
    -17503,-17551,-17600,-17648,-17697,-17745,-17793,-17842,
    -17890,-17939,-17987,-18035,-18084,-18132,-18180,-18228,
    -18277,-18325,-18373,-18421,-18470,-18518,-18566,-18614,
    -18663,-18711,-18759,-18807,-18855,-18903,-18951,-19000,
    -19048,-19096,-19144,-19192,-19240,-19288,-19336,-19384,
    -19432,-19480,-19528,-19576,-19624,-19672,-19720,-19768,
    -19816,-19864,-19912,-19959,-20007,-20055,-20103,-20151,
    -20199,-20246,-20294,-20342,-20390,-20438,-20485,-20533,
    -20581,-20629,-20676,-20724,-20772,-20819,-20867,-20915,
    -20962,-21010,-21057,-21105,-21153,-21200,-21248,-21295,
    -21343,-21390,-21438,-21485,-21533,-21580,-21628,-21675,
    -21723,-21770,-21817,-21865,-21912,-21960,-22007,-22054,
    -22102,-22149,-22196,-22243,-22291,-22338,-22385,-22433,
    -22480,-22527,-22574,-22621,-22668,-22716,-22763,-22810,
    -22857,-22904,-22951,-22998,-23045,-23092,-23139,-23186,
    -23233,-23280,-23327,-23374,-23421,-23468,-23515,-23562,
    -23609,-23656,-23703,-23750,-23796,-23843,-23890,-23937,
    -23984,-24030,-24077,-24124,-24171,-24217,-24264,-24311,
    -24357,-24404,-24451,-24497,-24544,-24591,-24637,-24684,
    -24730,-24777,-24823,-24870,-24916,-24963,-25009,-25056,
    -25102,-25149,-25195,-25241,-25288,-25334,-25381,-25427,
    -25473,-25520,-25566,-25612,-25658,-25705,-25751,-25797,
    -25843,-25889,-25936,-25982,-26028,-26074,-26120,-26166,
    -26212,-26258,-26304,-26350,-26396,-26442,-26488,-26534,
    -26580,-26626,-26672,-26718,-26764,-26810,-26856,-26902,
    -26947,-26993,-27039,-27085,-27131,-27176,-27222,-27268,
    -27313,-27359,-27405,-27450,-27496,-27542,-27587,-27633,
    -27678,-27724,-27770,-27815,-27861,-27906,-27952,-27997,
    -28042,-28088,-28133,-28179,-28224,-28269,-28315,-28360,
    -28405,-28451,-28496,-28541,-28586,-28632,-28677,-28722,
    -28767,-28812,-28858,-28903,-28948,-28993,-29038,-29083,
    -29128,-29173,-29218,-29263,-29308,-29353,-29398,-29443,
    -29488,-29533,-29577,-29622,-29667,-29712,-29757,-29801,
    -29846,-29891,-29936,-29980,-30025,-30070,-30114,-30159,
    -30204,-30248,-30293,-30337,-30382,-30426,-30471,-30515,
    -30560,-30604,-30649,-30693,-30738,-30782,-30826,-30871,
    -30915,-30959,-31004,-31048,-31092,-31136,-31181,-31225,
    -31269,-31313,-31357,-31402,-31446,-31490,-31534,-31578,
    -31622,-31666,-31710,-31754,-31798,-31842,-31886,-31930,
    -31974,-32017,-32061,-32105,-32149,-32193,-32236,-32280,
    -32324,-32368,-32411,-32455,-32499,-32542,-32586,-32630,
    -32673,-32717,-32760,-32804,-32847,-32891,-32934,-32978,
    -33021,-33065,-33108,-33151,-33195,-33238,-33281,-33325,
    -33368,-33411,-33454,-33498,-33541,-33584,-33627,-33670,
    -33713,-33756,-33799,-33843,-33886,-33929,-33972,-34015,
    -34057,-34100,-34143,-34186,-34229,-34272,-34315,-34358,
    -34400,-34443,-34486,-34529,-34571,-34614,-34657,-34699,
    -34742,-34785,-34827,-34870,-34912,-34955,-34997,-35040,
    -35082,-35125,-35167,-35210,-35252,-35294,-35337,-35379,
    -35421,-35464,-35506,-35548,-35590,-35633,-35675,-35717,
    -35759,-35801,-35843,-35885,-35927,-35969,-36011,-36053,
    -36095,-36137,-36179,-36221,-36263,-36305,-36347,-36388,
    -36430,-36472,-36514,-36555,-36597,-36639,-36681,-36722,
    -36764,-36805,-36847,-36889,-36930,-36972,-37013,-37055,
    -37096,-37137,-37179,-37220,-37262,-37303,-37344,-37386,
    -37427,-37468,-37509,-37551,-37592,-37633,-37674,-37715,
    -37756,-37797,-37838,-37879,-37920,-37961,-38002,-38043,
    -38084,-38125,-38166,-38207,-38248,-38288,-38329,-38370,
    -38411,-38451,-38492,-38533,-38573,-38614,-38655,-38695,
    -38736,-38776,-38817,-38857,-38898,-38938,-38979,-39019,
    -39059,-39100,-39140,-39180,-39221,-39261,-39301,-39341,
    -39382,-39422,-39462,-39502,-39542,-39582,-39622,-39662,
    -39702,-39742,-39782,-39822,-39862,-39902,-39942,-39982,
    -40021,-40061,-40101,-40141,-40180,-40220,-40260,-40299,
    -40339,-40379,-40418,-40458,-40497,-40537,-40576,-40616,
    -40655,-40695,-40734,-40773,-40813,-40852,-40891,-40931,
    -40970,-41009,-41048,-41087,-41127,-41166,-41205,-41244,
    -41283,-41322,-41361,-41400,-41439,-41478,-41517,-41556,
    -41595,-41633,-41672,-41711,-41750,-41788,-41827,-41866,
    -41904,-41943,-41982,-42020,-42059,-42097,-42136,-42174,
    -42213,-42251,-42290,-42328,-42366,-42405,-42443,-42481,
    -42520,-42558,-42596,-42634,-42672,-42711,-42749,-42787,
    -42825,-42863,-42901,-42939,-42977,-43015,-43053,-43091,
    -43128,-43166,-43204,-43242,-43280,-43317,-43355,-43393,
    -43430,-43468,-43506,-43543,-43581,-43618,-43656,-43693,
    -43731,-43768,-43806,-43843,-43880,-43918,-43955,-43992,
    -44029,-44067,-44104,-44141,-44178,-44215,-44252,-44289,
    -44326,-44363,-44400,-44437,-44474,-44511,-44548,-44585,
    -44622,-44659,-44695,-44732,-44769,-44806,-44842,-44879,
    -44915,-44952,-44989,-45025,-45062,-45098,-45135,-45171,
    -45207,-45244,-45280,-45316,-45353,-45389,-45425,-45462,
    -45498,-45534,-45570,-45606,-45642,-45678,-45714,-45750,
    -45786,-45822,-45858,-45894,-45930,-45966,-46002,-46037,
    -46073,-46109,-46145,-46180,-46216,-46252,-46287,-46323,
    -46358,-46394,-46429,-46465,-46500,-46536,-46571,-46606,
    -46642,-46677,-46712,-46747,-46783,-46818,-46853,-46888,
    -46923,-46958,-46993,-47028,-47063,-47098,-47133,-47168,
    -47203,-47238,-47273,-47308,-47342,-47377,-47412,-47446,
    -47481,-47516,-47550,-47585,-47619,-47654,-47688,-47723,
    -47757,-47792,-47826,-47860,-47895,-47929,-47963,-47998,
    -48032,-48066,-48100,-48134,-48168,-48202,-48236,-48271,
    -48304,-48338,-48372,-48406,-48440,-48474,-48508,-48542,
    -48575,-48609,-48643,-48676,-48710,-48744,-48777,-48811,
    -48844,-48878,-48911,-48945,-48978,-49012,-49045,-49078,
    -49112,-49145,-49178,-49211,-49244,-49278,-49311,-49344,
    -49377,-49410,-49443,-49476,-49509,-49542,-49575,-49608,
    -49640,-49673,-49706,-49739,-49771,-49804,-49837,-49869,
    -49902,-49935,-49967,-50000,-50032,-50065,-50097,-50129,
    -50162,-50194,-50226,-50259,-50291,-50323,-50355,-50387,
    -50420,-50452,-50484,-50516,-50548,-50580,-50612,-50644,
    -50675,-50707,-50739,-50771,-50803,-50834,-50866,-50898,
    -50929,-50961,-50993,-51024,-51056,-51087,-51119,-51150,
    -51182,-51213,-51244,-51276,-51307,-51338,-51369,-51401,
    -51432,-51463,-51494,-51525,-51556,-51587,-51618,-51649,
    -51680,-51711,-51742,-51773,-51803,-51834,-51865,-51896,
    -51926,-51957,-51988,-52018,-52049,-52079,-52110,-52140,
    -52171,-52201,-52231,-52262,-52292,-52322,-52353,-52383,
    -52413,-52443,-52473,-52503,-52534,-52564,-52594,-52624,
    -52653,-52683,-52713,-52743,-52773,-52803,-52832,-52862,
    -52892,-52922,-52951,-52981,-53010,-53040,-53069,-53099,
    -53128,-53158,-53187,-53216,-53246,-53275,-53304,-53334,
    -53363,-53392,-53421,-53450,-53479,-53508,-53537,-53566,
    -53595,-53624,-53653,-53682,-53711,-53739,-53768,-53797,
    -53826,-53854,-53883,-53911,-53940,-53969,-53997,-54026,
    -54054,-54082,-54111,-54139,-54167,-54196,-54224,-54252,
    -54280,-54308,-54337,-54365,-54393,-54421,-54449,-54477,
    -54505,-54533,-54560,-54588,-54616,-54644,-54672,-54699,
    -54727,-54755,-54782,-54810,-54837,-54865,-54892,-54920,
    -54947,-54974,-55002,-55029,-55056,-55084,-55111,-55138,
    -55165,-55192,-55219,-55246,-55274,-55300,-55327,-55354,
    -55381,-55408,-55435,-55462,-55489,-55515,-55542,-55569,
    -55595,-55622,-55648,-55675,-55701,-55728,-55754,-55781,
    -55807,-55833,-55860,-55886,-55912,-55938,-55965,-55991,
    -56017,-56043,-56069,-56095,-56121,-56147,-56173,-56199,
    -56225,-56250,-56276,-56302,-56328,-56353,-56379,-56404,
    -56430,-56456,-56481,-56507,-56532,-56557,-56583,-56608,
    -56633,-56659,-56684,-56709,-56734,-56760,-56785,-56810,
    -56835,-56860,-56885,-56910,-56935,-56959,-56984,-57009,
    -57034,-57059,-57083,-57108,-57133,-57157,-57182,-57206,
    -57231,-57255,-57280,-57304,-57329,-57353,-57377,-57402,
    -57426,-57450,-57474,-57498,-57522,-57546,-57570,-57594,
    -57618,-57642,-57666,-57690,-57714,-57738,-57762,-57785,
    -57809,-57833,-57856,-57880,-57903,-57927,-57950,-57974,
    -57997,-58021,-58044,-58067,-58091,-58114,-58137,-58160,
    -58183,-58207,-58230,-58253,-58276,-58299,-58322,-58345,
    -58367,-58390,-58413,-58436,-58459,-58481,-58504,-58527,
    -58549,-58572,-58594,-58617,-58639,-58662,-58684,-58706,
    -58729,-58751,-58773,-58795,-58818,-58840,-58862,-58884,
    -58906,-58928,-58950,-58972,-58994,-59016,-59038,-59059,
    -59081,-59103,-59125,-59146,-59168,-59190,-59211,-59233,
    -59254,-59276,-59297,-59318,-59340,-59361,-59382,-59404,
    -59425,-59446,-59467,-59488,-59509,-59530,-59551,-59572,
    -59593,-59614,-59635,-59656,-59677,-59697,-59718,-59739,
    -59759,-59780,-59801,-59821,-59842,-59862,-59883,-59903,
    -59923,-59944,-59964,-59984,-60004,-60025,-60045,-60065,
    -60085,-60105,-60125,-60145,-60165,-60185,-60205,-60225,
    -60244,-60264,-60284,-60304,-60323,-60343,-60363,-60382,
    -60402,-60421,-60441,-60460,-60479,-60499,-60518,-60537,
    -60556,-60576,-60595,-60614,-60633,-60652,-60671,-60690,
    -60709,-60728,-60747,-60766,-60785,-60803,-60822,-60841,
    -60859,-60878,-60897,-60915,-60934,-60952,-60971,-60989,
    -61007,-61026,-61044,-61062,-61081,-61099,-61117,-61135,
    -61153,-61171,-61189,-61207,-61225,-61243,-61261,-61279,
    -61297,-61314,-61332,-61350,-61367,-61385,-61403,-61420,
    -61438,-61455,-61473,-61490,-61507,-61525,-61542,-61559,
    -61577,-61594,-61611,-61628,-61645,-61662,-61679,-61696,
    -61713,-61730,-61747,-61764,-61780,-61797,-61814,-61831,
    -61847,-61864,-61880,-61897,-61913,-61930,-61946,-61963,
    -61979,-61995,-62012,-62028,-62044,-62060,-62076,-62092,
    -62108,-62125,-62141,-62156,-62172,-62188,-62204,-62220,
    -62236,-62251,-62267,-62283,-62298,-62314,-62329,-62345,
    -62360,-62376,-62391,-62407,-62422,-62437,-62453,-62468,
    -62483,-62498,-62513,-62528,-62543,-62558,-62573,-62588,
    -62603,-62618,-62633,-62648,-62662,-62677,-62692,-62706,
    -62721,-62735,-62750,-62764,-62779,-62793,-62808,-62822,
    -62836,-62850,-62865,-62879,-62893,-62907,-62921,-62935,
    -62949,-62963,-62977,-62991,-63005,-63019,-63032,-63046,
    -63060,-63074,-63087,-63101,-63114,-63128,-63141,-63155,
    -63168,-63182,-63195,-63208,-63221,-63235,-63248,-63261,
    -63274,-63287,-63300,-63313,-63326,-63339,-63352,-63365,
    -63378,-63390,-63403,-63416,-63429,-63441,-63454,-63466,
    -63479,-63491,-63504,-63516,-63528,-63541,-63553,-63565,
    -63578,-63590,-63602,-63614,-63626,-63638,-63650,-63662,
    -63674,-63686,-63698,-63709,-63721,-63733,-63745,-63756,
    -63768,-63779,-63791,-63803,-63814,-63825,-63837,-63848,
    -63859,-63871,-63882,-63893,-63904,-63915,-63927,-63938,
    -63949,-63960,-63971,-63981,-63992,-64003,-64014,-64025,
    -64035,-64046,-64057,-64067,-64078,-64088,-64099,-64109,
    -64120,-64130,-64140,-64151,-64161,-64171,-64181,-64192,
    -64202,-64212,-64222,-64232,-64242,-64252,-64261,-64271,
    -64281,-64291,-64301,-64310,-64320,-64330,-64339,-64349,
    -64358,-64368,-64377,-64387,-64396,-64405,-64414,-64424,
    -64433,-64442,-64451,-64460,-64469,-64478,-64487,-64496,
    -64505,-64514,-64523,-64532,-64540,-64549,-64558,-64566,
    -64575,-64584,-64592,-64601,-64609,-64617,-64626,-64634,
    -64642,-64651,-64659,-64667,-64675,-64683,-64691,-64699,
    -64707,-64715,-64723,-64731,-64739,-64747,-64754,-64762,
    -64770,-64777,-64785,-64793,-64800,-64808,-64815,-64822,
    -64830,-64837,-64844,-64852,-64859,-64866,-64873,-64880,
    -64887,-64895,-64902,-64908,-64915,-64922,-64929,-64936,
    -64943,-64949,-64956,-64963,-64969,-64976,-64982,-64989,
    -64995,-65002,-65008,-65015,-65021,-65027,-65033,-65040,
    -65046,-65052,-65058,-65064,-65070,-65076,-65082,-65088,
    -65094,-65099,-65105,-65111,-65117,-65122,-65128,-65133,
    -65139,-65144,-65150,-65155,-65161,-65166,-65171,-65177,
    -65182,-65187,-65192,-65197,-65202,-65207,-65212,-65217,
    -65222,-65227,-65232,-65237,-65242,-65246,-65251,-65256,
    -65260,-65265,-65270,-65274,-65279,-65283,-65287,-65292,
    -65296,-65300,-65305,-65309,-65313,-65317,-65321,-65325,
    -65329,-65333,-65337,-65341,-65345,-65349,-65352,-65356,
    -65360,-65363,-65367,-65371,-65374,-65378,-65381,-65385,
    -65388,-65391,-65395,-65398,-65401,-65404,-65408,-65411,
    -65414,-65417,-65420,-65423,-65426,-65429,-65431,-65434,
    -65437,-65440,-65442,-65445,-65448,-65450,-65453,-65455,
    -65458,-65460,-65463,-65465,-65467,-65470,-65472,-65474,
    -65476,-65478,-65480,-65482,-65484,-65486,-65488,-65490,
    -65492,-65494,-65496,-65497,-65499,-65501,-65502,-65504,
    -65505,-65507,-65508,-65510,-65511,-65513,-65514,-65515,
    -65516,-65518,-65519,-65520,-65521,-65522,-65523,-65524,
    -65525,-65526,-65527,-65527,-65528,-65529,-65530,-65530,
    -65531,-65531,-65532,-65532,-65533,-65533,-65534,-65534,
    -65534,-65535,-65535,-65535,-65535,-65535,-65535,-65535,
    -65535,-65535,-65535,-65535,-65535,-65535,-65535,-65534,
    -65534,-65534,-65533,-65533,-65532,-65532,-65531,-65531,
    -65530,-65530,-65529,-65528,-65527,-65527,-65526,-65525,
    -65524,-65523,-65522,-65521,-65520,-65519,-65518,-65516,
    -65515,-65514,-65513,-65511,-65510,-65508,-65507,-65505,
    -65504,-65502,-65501,-65499,-65497,-65496,-65494,-65492,
    -65490,-65488,-65486,-65484,-65482,-65480,-65478,-65476,
    -65474,-65472,-65470,-65467,-65465,-65463,-65460,-65458,
    -65455,-65453,-65450,-65448,-65445,-65442,-65440,-65437,
    -65434,-65431,-65429,-65426,-65423,-65420,-65417,-65414,
    -65411,-65408,-65404,-65401,-65398,-65395,-65391,-65388,
    -65385,-65381,-65378,-65374,-65371,-65367,-65363,-65360,
    -65356,-65352,-65349,-65345,-65341,-65337,-65333,-65329,
    -65325,-65321,-65317,-65313,-65309,-65305,-65300,-65296,
    -65292,-65287,-65283,-65279,-65274,-65270,-65265,-65260,
    -65256,-65251,-65246,-65242,-65237,-65232,-65227,-65222,
    -65217,-65212,-65207,-65202,-65197,-65192,-65187,-65182,
    -65177,-65171,-65166,-65161,-65155,-65150,-65144,-65139,
    -65133,-65128,-65122,-65117,-65111,-65105,-65099,-65094,
    -65088,-65082,-65076,-65070,-65064,-65058,-65052,-65046,
    -65040,-65033,-65027,-65021,-65015,-65008,-65002,-64995,
    -64989,-64982,-64976,-64969,-64963,-64956,-64949,-64943,
    -64936,-64929,-64922,-64915,-64908,-64902,-64895,-64887,
    -64880,-64873,-64866,-64859,-64852,-64844,-64837,-64830,
    -64822,-64815,-64808,-64800,-64793,-64785,-64777,-64770,
    -64762,-64754,-64747,-64739,-64731,-64723,-64715,-64707,
    -64699,-64691,-64683,-64675,-64667,-64659,-64651,-64642,
    -64634,-64626,-64617,-64609,-64601,-64592,-64584,-64575,
    -64566,-64558,-64549,-64540,-64532,-64523,-64514,-64505,
    -64496,-64487,-64478,-64469,-64460,-64451,-64442,-64433,
    -64424,-64414,-64405,-64396,-64387,-64377,-64368,-64358,
    -64349,-64339,-64330,-64320,-64310,-64301,-64291,-64281,
    -64271,-64261,-64252,-64242,-64232,-64222,-64212,-64202,
    -64192,-64181,-64171,-64161,-64151,-64140,-64130,-64120,
    -64109,-64099,-64088,-64078,-64067,-64057,-64046,-64035,
    -64025,-64014,-64003,-63992,-63981,-63971,-63960,-63949,
    -63938,-63927,-63915,-63904,-63893,-63882,-63871,-63859,
    -63848,-63837,-63825,-63814,-63803,-63791,-63779,-63768,
    -63756,-63745,-63733,-63721,-63709,-63698,-63686,-63674,
    -63662,-63650,-63638,-63626,-63614,-63602,-63590,-63578,
    -63565,-63553,-63541,-63528,-63516,-63504,-63491,-63479,
    -63466,-63454,-63441,-63429,-63416,-63403,-63390,-63378,
    -63365,-63352,-63339,-63326,-63313,-63300,-63287,-63274,
    -63261,-63248,-63235,-63221,-63208,-63195,-63182,-63168,
    -63155,-63141,-63128,-63114,-63101,-63087,-63074,-63060,
    -63046,-63032,-63019,-63005,-62991,-62977,-62963,-62949,
    -62935,-62921,-62907,-62893,-62879,-62865,-62850,-62836,
    -62822,-62808,-62793,-62779,-62764,-62750,-62735,-62721,
    -62706,-62692,-62677,-62662,-62648,-62633,-62618,-62603,
    -62588,-62573,-62558,-62543,-62528,-62513,-62498,-62483,
    -62468,-62453,-62437,-62422,-62407,-62391,-62376,-62360,
    -62345,-62329,-62314,-62298,-62283,-62267,-62251,-62236,
    -62220,-62204,-62188,-62172,-62156,-62141,-62125,-62108,
    -62092,-62076,-62060,-62044,-62028,-62012,-61995,-61979,
    -61963,-61946,-61930,-61913,-61897,-61880,-61864,-61847,
    -61831,-61814,-61797,-61780,-61764,-61747,-61730,-61713,
    -61696,-61679,-61662,-61645,-61628,-61611,-61594,-61577,
    -61559,-61542,-61525,-61507,-61490,-61473,-61455,-61438,
    -61420,-61403,-61385,-61367,-61350,-61332,-61314,-61297,
    -61279,-61261,-61243,-61225,-61207,-61189,-61171,-61153,
    -61135,-61117,-61099,-61081,-61062,-61044,-61026,-61007,
    -60989,-60971,-60952,-60934,-60915,-60897,-60878,-60859,
    -60841,-60822,-60803,-60785,-60766,-60747,-60728,-60709,
    -60690,-60671,-60652,-60633,-60614,-60595,-60576,-60556,
    -60537,-60518,-60499,-60479,-60460,-60441,-60421,-60402,
    -60382,-60363,-60343,-60323,-60304,-60284,-60264,-60244,
    -60225,-60205,-60185,-60165,-60145,-60125,-60105,-60085,
    -60065,-60045,-60025,-60004,-59984,-59964,-59944,-59923,
    -59903,-59883,-59862,-59842,-59821,-59801,-59780,-59759,
    -59739,-59718,-59697,-59677,-59656,-59635,-59614,-59593,
    -59572,-59551,-59530,-59509,-59488,-59467,-59446,-59425,
    -59404,-59382,-59361,-59340,-59318,-59297,-59276,-59254,
    -59233,-59211,-59189,-59168,-59146,-59125,-59103,-59081,
    -59059,-59038,-59016,-58994,-58972,-58950,-58928,-58906,
    -58884,-58862,-58840,-58818,-58795,-58773,-58751,-58729,
    -58706,-58684,-58662,-58639,-58617,-58594,-58572,-58549,
    -58527,-58504,-58481,-58459,-58436,-58413,-58390,-58367,
    -58345,-58322,-58299,-58276,-58253,-58230,-58207,-58183,
    -58160,-58137,-58114,-58091,-58067,-58044,-58021,-57997,
    -57974,-57950,-57927,-57903,-57880,-57856,-57833,-57809,
    -57785,-57762,-57738,-57714,-57690,-57666,-57642,-57618,
    -57594,-57570,-57546,-57522,-57498,-57474,-57450,-57426,
    -57402,-57377,-57353,-57329,-57304,-57280,-57255,-57231,
    -57206,-57182,-57157,-57133,-57108,-57083,-57059,-57034,
    -57009,-56984,-56959,-56935,-56910,-56885,-56860,-56835,
    -56810,-56785,-56760,-56734,-56709,-56684,-56659,-56633,
    -56608,-56583,-56557,-56532,-56507,-56481,-56456,-56430,
    -56404,-56379,-56353,-56328,-56302,-56276,-56250,-56225,
    -56199,-56173,-56147,-56121,-56095,-56069,-56043,-56017,
    -55991,-55965,-55938,-55912,-55886,-55860,-55833,-55807,
    -55781,-55754,-55728,-55701,-55675,-55648,-55622,-55595,
    -55569,-55542,-55515,-55489,-55462,-55435,-55408,-55381,
    -55354,-55327,-55300,-55274,-55246,-55219,-55192,-55165,
    -55138,-55111,-55084,-55056,-55029,-55002,-54974,-54947,
    -54920,-54892,-54865,-54837,-54810,-54782,-54755,-54727,
    -54699,-54672,-54644,-54616,-54588,-54560,-54533,-54505,
    -54477,-54449,-54421,-54393,-54365,-54337,-54308,-54280,
    -54252,-54224,-54196,-54167,-54139,-54111,-54082,-54054,
    -54026,-53997,-53969,-53940,-53911,-53883,-53854,-53826,
    -53797,-53768,-53739,-53711,-53682,-53653,-53624,-53595,
    -53566,-53537,-53508,-53479,-53450,-53421,-53392,-53363,
    -53334,-53304,-53275,-53246,-53216,-53187,-53158,-53128,
    -53099,-53069,-53040,-53010,-52981,-52951,-52922,-52892,
    -52862,-52832,-52803,-52773,-52743,-52713,-52683,-52653,
    -52624,-52594,-52564,-52534,-52503,-52473,-52443,-52413,
    -52383,-52353,-52322,-52292,-52262,-52231,-52201,-52171,
    -52140,-52110,-52079,-52049,-52018,-51988,-51957,-51926,
    -51896,-51865,-51834,-51803,-51773,-51742,-51711,-51680,
    -51649,-51618,-51587,-51556,-51525,-51494,-51463,-51432,
    -51401,-51369,-51338,-51307,-51276,-51244,-51213,-51182,
    -51150,-51119,-51087,-51056,-51024,-50993,-50961,-50929,
    -50898,-50866,-50834,-50803,-50771,-50739,-50707,-50675,
    -50644,-50612,-50580,-50548,-50516,-50484,-50452,-50420,
    -50387,-50355,-50323,-50291,-50259,-50226,-50194,-50162,
    -50129,-50097,-50065,-50032,-50000,-49967,-49935,-49902,
    -49869,-49837,-49804,-49771,-49739,-49706,-49673,-49640,
    -49608,-49575,-49542,-49509,-49476,-49443,-49410,-49377,
    -49344,-49311,-49278,-49244,-49211,-49178,-49145,-49112,
    -49078,-49045,-49012,-48978,-48945,-48911,-48878,-48844,
    -48811,-48777,-48744,-48710,-48676,-48643,-48609,-48575,
    -48542,-48508,-48474,-48440,-48406,-48372,-48338,-48305,
    -48271,-48237,-48202,-48168,-48134,-48100,-48066,-48032,
    -47998,-47963,-47929,-47895,-47860,-47826,-47792,-47757,
    -47723,-47688,-47654,-47619,-47585,-47550,-47516,-47481,
    -47446,-47412,-47377,-47342,-47307,-47273,-47238,-47203,
    -47168,-47133,-47098,-47063,-47028,-46993,-46958,-46923,
    -46888,-46853,-46818,-46783,-46747,-46712,-46677,-46642,
    -46606,-46571,-46536,-46500,-46465,-46429,-46394,-46358,
    -46323,-46287,-46251,-46216,-46180,-46145,-46109,-46073,
    -46037,-46002,-45966,-45930,-45894,-45858,-45822,-45786,
    -45750,-45714,-45678,-45642,-45606,-45570,-45534,-45498,
    -45462,-45425,-45389,-45353,-45316,-45280,-45244,-45207,
    -45171,-45135,-45098,-45062,-45025,-44989,-44952,-44915,
    -44879,-44842,-44806,-44769,-44732,-44695,-44659,-44622,
    -44585,-44548,-44511,-44474,-44437,-44400,-44363,-44326,
    -44289,-44252,-44215,-44178,-44141,-44104,-44067,-44029,
    -43992,-43955,-43918,-43880,-43843,-43806,-43768,-43731,
    -43693,-43656,-43618,-43581,-43543,-43506,-43468,-43430,
    -43393,-43355,-43317,-43280,-43242,-43204,-43166,-43128,
    -43091,-43053,-43015,-42977,-42939,-42901,-42863,-42825,
    -42787,-42749,-42711,-42672,-42634,-42596,-42558,-42520,
    -42481,-42443,-42405,-42366,-42328,-42290,-42251,-42213,
    -42174,-42136,-42097,-42059,-42020,-41982,-41943,-41904,
    -41866,-41827,-41788,-41750,-41711,-41672,-41633,-41595,
    -41556,-41517,-41478,-41439,-41400,-41361,-41322,-41283,
    -41244,-41205,-41166,-41127,-41087,-41048,-41009,-40970,
    -40931,-40891,-40852,-40813,-40773,-40734,-40695,-40655,
    -40616,-40576,-40537,-40497,-40458,-40418,-40379,-40339,
    -40299,-40260,-40220,-40180,-40141,-40101,-40061,-40021,
    -39982,-39942,-39902,-39862,-39822,-39782,-39742,-39702,
    -39662,-39622,-39582,-39542,-39502,-39462,-39422,-39382,
    -39341,-39301,-39261,-39221,-39180,-39140,-39100,-39059,
    -39019,-38979,-38938,-38898,-38857,-38817,-38776,-38736,
    -38695,-38655,-38614,-38573,-38533,-38492,-38451,-38411,
    -38370,-38329,-38288,-38248,-38207,-38166,-38125,-38084,
    -38043,-38002,-37961,-37920,-37879,-37838,-37797,-37756,
    -37715,-37674,-37633,-37592,-37550,-37509,-37468,-37427,
    -37386,-37344,-37303,-37262,-37220,-37179,-37137,-37096,
    -37055,-37013,-36972,-36930,-36889,-36847,-36805,-36764,
    -36722,-36681,-36639,-36597,-36556,-36514,-36472,-36430,
    -36388,-36347,-36305,-36263,-36221,-36179,-36137,-36095,
    -36053,-36011,-35969,-35927,-35885,-35843,-35801,-35759,
    -35717,-35675,-35633,-35590,-35548,-35506,-35464,-35421,
    -35379,-35337,-35294,-35252,-35210,-35167,-35125,-35082,
    -35040,-34997,-34955,-34912,-34870,-34827,-34785,-34742,
    -34699,-34657,-34614,-34571,-34529,-34486,-34443,-34400,
    -34358,-34315,-34272,-34229,-34186,-34143,-34100,-34057,
    -34015,-33972,-33929,-33886,-33843,-33799,-33756,-33713,
    -33670,-33627,-33584,-33541,-33498,-33454,-33411,-33368,
    -33325,-33281,-33238,-33195,-33151,-33108,-33065,-33021,
    -32978,-32934,-32891,-32847,-32804,-32760,-32717,-32673,
    -32630,-32586,-32542,-32499,-32455,-32411,-32368,-32324,
    -32280,-32236,-32193,-32149,-32105,-32061,-32017,-31974,
    -31930,-31886,-31842,-31798,-31754,-31710,-31666,-31622,
    -31578,-31534,-31490,-31446,-31402,-31357,-31313,-31269,
    -31225,-31181,-31136,-31092,-31048,-31004,-30959,-30915,
    -30871,-30826,-30782,-30738,-30693,-30649,-30604,-30560,
    -30515,-30471,-30426,-30382,-30337,-30293,-30248,-30204,
    -30159,-30114,-30070,-30025,-29980,-29936,-29891,-29846,
    -29801,-29757,-29712,-29667,-29622,-29577,-29533,-29488,
    -29443,-29398,-29353,-29308,-29263,-29218,-29173,-29128,
    -29083,-29038,-28993,-28948,-28903,-28858,-28812,-28767,
    -28722,-28677,-28632,-28586,-28541,-28496,-28451,-28405,
    -28360,-28315,-28269,-28224,-28179,-28133,-28088,-28042,
    -27997,-27952,-27906,-27861,-27815,-27770,-27724,-27678,
    -27633,-27587,-27542,-27496,-27450,-27405,-27359,-27313,
    -27268,-27222,-27176,-27131,-27085,-27039,-26993,-26947,
    -26902,-26856,-26810,-26764,-26718,-26672,-26626,-26580,
    -26534,-26488,-26442,-26396,-26350,-26304,-26258,-26212,
    -26166,-26120,-26074,-26028,-25982,-25936,-25889,-25843,
    -25797,-25751,-25705,-25658,-25612,-25566,-25520,-25473,
    -25427,-25381,-25334,-25288,-25241,-25195,-25149,-25102,
    -25056,-25009,-24963,-24916,-24870,-24823,-24777,-24730,
    -24684,-24637,-24591,-24544,-24497,-24451,-24404,-24357,
    -24311,-24264,-24217,-24171,-24124,-24077,-24030,-23984,
    -23937,-23890,-23843,-23796,-23750,-23703,-23656,-23609,
    -23562,-23515,-23468,-23421,-23374,-23327,-23280,-23233,
    -23186,-23139,-23092,-23045,-22998,-22951,-22904,-22857,
    -22810,-22763,-22716,-22668,-22621,-22574,-22527,-22480,
    -22432,-22385,-22338,-22291,-22243,-22196,-22149,-22102,
    -22054,-22007,-21960,-21912,-21865,-21817,-21770,-21723,
    -21675,-21628,-21580,-21533,-21485,-21438,-21390,-21343,
    -21295,-21248,-21200,-21153,-21105,-21057,-21010,-20962,
    -20915,-20867,-20819,-20772,-20724,-20676,-20629,-20581,
    -20533,-20485,-20438,-20390,-20342,-20294,-20246,-20199,
    -20151,-20103,-20055,-20007,-19959,-19912,-19864,-19816,
    -19768,-19720,-19672,-19624,-19576,-19528,-19480,-19432,
    -19384,-19336,-19288,-19240,-19192,-19144,-19096,-19048,
    -19000,-18951,-18903,-18855,-18807,-18759,-18711,-18663,
    -18614,-18566,-18518,-18470,-18421,-18373,-18325,-18277,
    -18228,-18180,-18132,-18084,-18035,-17987,-17939,-17890,
    -17842,-17793,-17745,-17697,-17648,-17600,-17551,-17503,
    -17455,-17406,-17358,-17309,-17261,-17212,-17164,-17115,
    -17067,-17018,-16970,-16921,-16872,-16824,-16775,-16727,
    -16678,-16629,-16581,-16532,-16484,-16435,-16386,-16338,
    -16289,-16240,-16191,-16143,-16094,-16045,-15997,-15948,
    -15899,-15850,-15802,-15753,-15704,-15655,-15606,-15557,
    -15509,-15460,-15411,-15362,-15313,-15264,-15215,-15167,
    -15118,-15069,-15020,-14971,-14922,-14873,-14824,-14775,
    -14726,-14677,-14628,-14579,-14530,-14481,-14432,-14383,
    -14334,-14285,-14236,-14187,-14138,-14089,-14040,-13990,
    -13941,-13892,-13843,-13794,-13745,-13696,-13647,-13597,
    -13548,-13499,-13450,-13401,-13351,-13302,-13253,-13204,
    -13154,-13105,-13056,-13007,-12957,-12908,-12859,-12810,
    -12760,-12711,-12662,-12612,-12563,-12514,-12464,-12415,
    -12366,-12316,-12267,-12217,-12168,-12119,-12069,-12020,
    -11970,-11921,-11872,-11822,-11773,-11723,-11674,-11624,
    -11575,-11525,-11476,-11426,-11377,-11327,-11278,-11228,
    -11179,-11129,-11080,-11030,-10981,-10931,-10882,-10832,
    -10782,-10733,-10683,-10634,-10584,-10534,-10485,-10435,
    -10386,-10336,-10286,-10237,-10187,-10137,-10088,-10038,
    -9988,-9939,-9889,-9839,-9790,-9740,-9690,-9640,
    -9591,-9541,-9491,-9442,-9392,-9342,-9292,-9243,
    -9193,-9143,-9093,-9043,-8994,-8944,-8894,-8844,
    -8794,-8745,-8695,-8645,-8595,-8545,-8496,-8446,
    -8396,-8346,-8296,-8246,-8196,-8147,-8097,-8047,
    -7997,-7947,-7897,-7847,-7797,-7747,-7697,-7648,
    -7598,-7548,-7498,-7448,-7398,-7348,-7298,-7248,
    -7198,-7148,-7098,-7048,-6998,-6948,-6898,-6848,
    -6798,-6748,-6698,-6648,-6598,-6548,-6498,-6448,
    -6398,-6348,-6298,-6248,-6198,-6148,-6098,-6048,
    -5998,-5948,-5898,-5848,-5798,-5747,-5697,-5647,
    -5597,-5547,-5497,-5447,-5397,-5347,-5297,-5247,
    -5197,-5146,-5096,-5046,-4996,-4946,-4896,-4846,
    -4796,-4745,-4695,-4645,-4595,-4545,-4495,-4445,
    -4394,-4344,-4294,-4244,-4194,-4144,-4093,-4043,
    -3993,-3943,-3893,-3843,-3792,-3742,-3692,-3642,
    -3592,-3541,-3491,-3441,-3391,-3341,-3291,-3240,
    -3190,-3140,-3090,-3039,-2989,-2939,-2889,-2839,
    -2788,-2738,-2688,-2638,-2588,-2537,-2487,-2437,
    -2387,-2336,-2286,-2236,-2186,-2135,-2085,-2035,
    -1985,-1934,-1884,-1834,-1784,-1733,-1683,-1633,
    -1583,-1532,-1482,-1432,-1382,-1331,-1281,-1231,
    -1181,-1130,-1080,-1030,-980,-929,-879,-829,
    -779,-728,-678,-628,-578,-527,-477,-427,
    -376,-326,-276,-226,-175,-125,-75,-25,
    25,75,125,175,226,276,326,376,
    427,477,527,578,628,678,728,779,
    829,879,929,980,1030,1080,1130,1181,
    1231,1281,1331,1382,1432,1482,1532,1583,
    1633,1683,1733,1784,1834,1884,1934,1985,
    2035,2085,2135,2186,2236,2286,2336,2387,
    2437,2487,2537,2587,2638,2688,2738,2788,
    2839,2889,2939,2989,3039,3090,3140,3190,
    3240,3291,3341,3391,3441,3491,3542,3592,
    3642,3692,3742,3792,3843,3893,3943,3993,
    4043,4093,4144,4194,4244,4294,4344,4394,
    4445,4495,4545,4595,4645,4695,4745,4796,
    4846,4896,4946,4996,5046,5096,5146,5197,
    5247,5297,5347,5397,5447,5497,5547,5597,
    5647,5697,5747,5798,5848,5898,5948,5998,
    6048,6098,6148,6198,6248,6298,6348,6398,
    6448,6498,6548,6598,6648,6698,6748,6798,
    6848,6898,6948,6998,7048,7098,7148,7198,
    7248,7298,7348,7398,7448,7498,7548,7598,
    7648,7697,7747,7797,7847,7897,7947,7997,
    8047,8097,8147,8196,8246,8296,8346,8396,
    8446,8496,8545,8595,8645,8695,8745,8794,
    8844,8894,8944,8994,9043,9093,9143,9193,
    9243,9292,9342,9392,9442,9491,9541,9591,
    9640,9690,9740,9790,9839,9889,9939,9988,
    10038,10088,10137,10187,10237,10286,10336,10386,
    10435,10485,10534,10584,10634,10683,10733,10782,
    10832,10882,10931,10981,11030,11080,11129,11179,
    11228,11278,11327,11377,11426,11476,11525,11575,
    11624,11674,11723,11773,11822,11872,11921,11970,
    12020,12069,12119,12168,12218,12267,12316,12366,
    12415,12464,12514,12563,12612,12662,12711,12760,
    12810,12859,12908,12957,13007,13056,13105,13154,
    13204,13253,13302,13351,13401,13450,13499,13548,
    13597,13647,13696,13745,13794,13843,13892,13941,
    13990,14040,14089,14138,14187,14236,14285,14334,
    14383,14432,14481,14530,14579,14628,14677,14726,
    14775,14824,14873,14922,14971,15020,15069,15118,
    15167,15215,15264,15313,15362,15411,15460,15509,
    15557,15606,15655,15704,15753,15802,15850,15899,
    15948,15997,16045,16094,16143,16191,16240,16289,
    16338,16386,16435,16484,16532,16581,16629,16678,
    16727,16775,16824,16872,16921,16970,17018,17067,
    17115,17164,17212,17261,17309,17358,17406,17455,
    17503,17551,17600,17648,17697,17745,17793,17842,
    17890,17939,17987,18035,18084,18132,18180,18228,
    18277,18325,18373,18421,18470,18518,18566,18614,
    18663,18711,18759,18807,18855,18903,18951,19000,
    19048,19096,19144,19192,19240,19288,19336,19384,
    19432,19480,19528,19576,19624,19672,19720,19768,
    19816,19864,19912,19959,20007,20055,20103,20151,
    20199,20246,20294,20342,20390,20438,20485,20533,
    20581,20629,20676,20724,20772,20819,20867,20915,
    20962,21010,21057,21105,21153,21200,21248,21295,
    21343,21390,21438,21485,21533,21580,21628,21675,
    21723,21770,21817,21865,21912,21960,22007,22054,
    22102,22149,22196,22243,22291,22338,22385,22432,
    22480,22527,22574,22621,22668,22716,22763,22810,
    22857,22904,22951,22998,23045,23092,23139,23186,
    23233,23280,23327,23374,23421,23468,23515,23562,
    23609,23656,23703,23750,23796,23843,23890,23937,
    23984,24030,24077,24124,24171,24217,24264,24311,
    24357,24404,24451,24497,24544,24591,24637,24684,
    24730,24777,24823,24870,24916,24963,25009,25056,
    25102,25149,25195,25241,25288,25334,25381,25427,
    25473,25520,25566,25612,25658,25705,25751,25797,
    25843,25889,25936,25982,26028,26074,26120,26166,
    26212,26258,26304,26350,26396,26442,26488,26534,
    26580,26626,26672,26718,26764,26810,26856,26902,
    26947,26993,27039,27085,27131,27176,27222,27268,
    27313,27359,27405,27450,27496,27542,27587,27633,
    27678,27724,27770,27815,27861,27906,27952,27997,
    28042,28088,28133,28179,28224,28269,28315,28360,
    28405,28451,28496,28541,28586,28632,28677,28722,
    28767,28812,28858,28903,28948,28993,29038,29083,
    29128,29173,29218,29263,29308,29353,29398,29443,
    29488,29533,29577,29622,29667,29712,29757,29801,
    29846,29891,29936,29980,30025,30070,30114,30159,
    30204,30248,30293,30337,30382,30427,30471,30516,
    30560,30604,30649,30693,30738,30782,30826,30871,
    30915,30959,31004,31048,31092,31136,31181,31225,
    31269,31313,31357,31402,31446,31490,31534,31578,
    31622,31666,31710,31754,31798,31842,31886,31930,
    31974,32017,32061,32105,32149,32193,32236,32280,
    32324,32368,32411,32455,32499,32542,32586,32630,
    32673,32717,32760,32804,32847,32891,32934,32978,
    33021,33065,33108,33151,33195,33238,33281,33325,
    33368,33411,33454,33498,33541,33584,33627,33670,
    33713,33756,33799,33843,33886,33929,33972,34015,
    34057,34100,34143,34186,34229,34272,34315,34358,
    34400,34443,34486,34529,34571,34614,34657,34699,
    34742,34785,34827,34870,34912,34955,34997,35040,
    35082,35125,35167,35210,35252,35294,35337,35379,
    35421,35464,35506,35548,35590,35633,35675,35717,
    35759,35801,35843,35885,35927,35969,36011,36053,
    36095,36137,36179,36221,36263,36305,36347,36388,
    36430,36472,36514,36556,36597,36639,36681,36722,
    36764,36805,36847,36889,36930,36972,37013,37055,
    37096,37137,37179,37220,37262,37303,37344,37386,
    37427,37468,37509,37551,37592,37633,37674,37715,
    37756,37797,37838,37879,37920,37961,38002,38043,
    38084,38125,38166,38207,38248,38288,38329,38370,
    38411,38451,38492,38533,38573,38614,38655,38695,
    38736,38776,38817,38857,38898,38938,38979,39019,
    39059,39100,39140,39180,39221,39261,39301,39341,
    39382,39422,39462,39502,39542,39582,39622,39662,
    39702,39742,39782,39822,39862,39902,39942,39982,
    40021,40061,40101,40141,40180,40220,40260,40299,
    40339,40379,40418,40458,40497,40537,40576,40616,
    40655,40695,40734,40773,40813,40852,40891,40931,
    40970,41009,41048,41087,41127,41166,41205,41244,
    41283,41322,41361,41400,41439,41478,41517,41556,
    41595,41633,41672,41711,41750,41788,41827,41866,
    41904,41943,41982,42020,42059,42097,42136,42174,
    42213,42251,42290,42328,42366,42405,42443,42481,
    42520,42558,42596,42634,42672,42711,42749,42787,
    42825,42863,42901,42939,42977,43015,43053,43091,
    43128,43166,43204,43242,43280,43317,43355,43393,
    43430,43468,43506,43543,43581,43618,43656,43693,
    43731,43768,43806,43843,43880,43918,43955,43992,
    44029,44067,44104,44141,44178,44215,44252,44289,
    44326,44363,44400,44437,44474,44511,44548,44585,
    44622,44659,44695,44732,44769,44806,44842,44879,
    44915,44952,44989,45025,45062,45098,45135,45171,
    45207,45244,45280,45316,45353,45389,45425,45462,
    45498,45534,45570,45606,45642,45678,45714,45750,
    45786,45822,45858,45894,45930,45966,46002,46037,
    46073,46109,46145,46180,46216,46252,46287,46323,
    46358,46394,46429,46465,46500,46536,46571,46606,
    46642,46677,46712,46747,46783,46818,46853,46888,
    46923,46958,46993,47028,47063,47098,47133,47168,
    47203,47238,47273,47308,47342,47377,47412,47446,
    47481,47516,47550,47585,47619,47654,47688,47723,
    47757,47792,47826,47861,47895,47929,47963,47998,
    48032,48066,48100,48134,48168,48202,48237,48271,
    48305,48338,48372,48406,48440,48474,48508,48542,
    48575,48609,48643,48676,48710,48744,48777,48811,
    48844,48878,48911,48945,48978,49012,49045,49078,
    49112,49145,49178,49211,49244,49278,49311,49344,
    49377,49410,49443,49476,49509,49542,49575,49608,
    49640,49673,49706,49739,49771,49804,49837,49869,
    49902,49935,49967,50000,50032,50064,50097,50129,
    50162,50194,50226,50259,50291,50323,50355,50387,
    50420,50452,50484,50516,50548,50580,50612,50644,
    50675,50707,50739,50771,50803,50834,50866,50898,
    50929,50961,50993,51024,51056,51087,51119,51150,
    51182,51213,51244,51276,51307,51338,51369,51401,
    51432,51463,51494,51525,51556,51587,51618,51649,
    51680,51711,51742,51773,51803,51834,51865,51896,
    51926,51957,51988,52018,52049,52079,52110,52140,
    52171,52201,52231,52262,52292,52322,52353,52383,
    52413,52443,52473,52503,52534,52564,52594,52624,
    52653,52683,52713,52743,52773,52803,52832,52862,
    52892,52922,52951,52981,53010,53040,53069,53099,
    53128,53158,53187,53216,53246,53275,53304,53334,
    53363,53392,53421,53450,53479,53508,53537,53566,
    53595,53624,53653,53682,53711,53739,53768,53797,
    53826,53854,53883,53912,53940,53969,53997,54026,
    54054,54082,54111,54139,54167,54196,54224,54252,
    54280,54309,54337,54365,54393,54421,54449,54477,
    54505,54533,54560,54588,54616,54644,54672,54699,
    54727,54755,54782,54810,54837,54865,54892,54920,
    54947,54974,55002,55029,55056,55084,55111,55138,
    55165,55192,55219,55246,55274,55300,55327,55354,
    55381,55408,55435,55462,55489,55515,55542,55569,
    55595,55622,55648,55675,55701,55728,55754,55781,
    55807,55833,55860,55886,55912,55938,55965,55991,
    56017,56043,56069,56095,56121,56147,56173,56199,
    56225,56250,56276,56302,56328,56353,56379,56404,
    56430,56456,56481,56507,56532,56557,56583,56608,
    56633,56659,56684,56709,56734,56760,56785,56810,
    56835,56860,56885,56910,56935,56959,56984,57009,
    57034,57059,57083,57108,57133,57157,57182,57206,
    57231,57255,57280,57304,57329,57353,57377,57402,
    57426,57450,57474,57498,57522,57546,57570,57594,
    57618,57642,57666,57690,57714,57738,57762,57785,
    57809,57833,57856,57880,57903,57927,57950,57974,
    57997,58021,58044,58067,58091,58114,58137,58160,
    58183,58207,58230,58253,58276,58299,58322,58345,
    58367,58390,58413,58436,58459,58481,58504,58527,
    58549,58572,58594,58617,58639,58662,58684,58706,
    58729,58751,58773,58795,58818,58840,58862,58884,
    58906,58928,58950,58972,58994,59016,59038,59059,
    59081,59103,59125,59146,59168,59190,59211,59233,
    59254,59276,59297,59318,59340,59361,59382,59404,
    59425,59446,59467,59488,59509,59530,59551,59572,
    59593,59614,59635,59656,59677,59697,59718,59739,
    59759,59780,59801,59821,59842,59862,59883,59903,
    59923,59944,59964,59984,60004,60025,60045,60065,
    60085,60105,60125,60145,60165,60185,60205,60225,
    60244,60264,60284,60304,60323,60343,60363,60382,
    60402,60421,60441,60460,60479,60499,60518,60537,
    60556,60576,60595,60614,60633,60652,60671,60690,
    60709,60728,60747,60766,60785,60803,60822,60841,
    60859,60878,60897,60915,60934,60952,60971,60989,
    61007,61026,61044,61062,61081,61099,61117,61135,
    61153,61171,61189,61207,61225,61243,61261,61279,
    61297,61314,61332,61350,61367,61385,61403,61420,
    61438,61455,61473,61490,61507,61525,61542,61559,
    61577,61594,61611,61628,61645,61662,61679,61696,
    61713,61730,61747,61764,61780,61797,61814,61831,
    61847,61864,61880,61897,61913,61930,61946,61963,
    61979,61995,62012,62028,62044,62060,62076,62092,
    62108,62125,62141,62156,62172,62188,62204,62220,
    62236,62251,62267,62283,62298,62314,62329,62345,
    62360,62376,62391,62407,62422,62437,62453,62468,
    62483,62498,62513,62528,62543,62558,62573,62588,
    62603,62618,62633,62648,62662,62677,62692,62706,
    62721,62735,62750,62764,62779,62793,62808,62822,
    62836,62850,62865,62879,62893,62907,62921,62935,
    62949,62963,62977,62991,63005,63019,63032,63046,
    63060,63074,63087,63101,63114,63128,63141,63155,
    63168,63182,63195,63208,63221,63235,63248,63261,
    63274,63287,63300,63313,63326,63339,63352,63365,
    63378,63390,63403,63416,63429,63441,63454,63466,
    63479,63491,63504,63516,63528,63541,63553,63565,
    63578,63590,63602,63614,63626,63638,63650,63662,
    63674,63686,63698,63709,63721,63733,63745,63756,
    63768,63779,63791,63803,63814,63825,63837,63848,
    63859,63871,63882,63893,63904,63915,63927,63938,
    63949,63960,63971,63981,63992,64003,64014,64025,
    64035,64046,64057,64067,64078,64088,64099,64109,
    64120,64130,64140,64151,64161,64171,64181,64192,
    64202,64212,64222,64232,64242,64252,64261,64271,
    64281,64291,64301,64310,64320,64330,64339,64349,
    64358,64368,64377,64387,64396,64405,64414,64424,
    64433,64442,64451,64460,64469,64478,64487,64496,
    64505,64514,64523,64532,64540,64549,64558,64566,
    64575,64584,64592,64600,64609,64617,64626,64634,
    64642,64651,64659,64667,64675,64683,64691,64699,
    64707,64715,64723,64731,64739,64747,64754,64762,
    64770,64777,64785,64793,64800,64808,64815,64822,
    64830,64837,64844,64852,64859,64866,64873,64880,
    64887,64895,64902,64908,64915,64922,64929,64936,
    64943,64949,64956,64963,64969,64976,64982,64989,
    64995,65002,65008,65015,65021,65027,65033,65040,
    65046,65052,65058,65064,65070,65076,65082,65088,
    65094,65099,65105,65111,65117,65122,65128,65133,
    65139,65144,65150,65155,65161,65166,65171,65177,
    65182,65187,65192,65197,65202,65207,65212,65217,
    65222,65227,65232,65237,65242,65246,65251,65256,
    65260,65265,65270,65274,65279,65283,65287,65292,
    65296,65300,65305,65309,65313,65317,65321,65325,
    65329,65333,65337,65341,65345,65349,65352,65356,
    65360,65363,65367,65371,65374,65378,65381,65385,
    65388,65391,65395,65398,65401,65404,65408,65411,
    65414,65417,65420,65423,65426,65429,65431,65434,
    65437,65440,65442,65445,65448,65450,65453,65455,
    65458,65460,65463,65465,65467,65470,65472,65474,
    65476,65478,65480,65482,65484,65486,65488,65490,
    65492,65494,65496,65497,65499,65501,65502,65504,
    65505,65507,65508,65510,65511,65513,65514,65515,
    65516,65518,65519,65520,65521,65522,65523,65524,
    65525,65526,65527,65527,65528,65529,65530,65530,
    65531,65531,65532,65532,65533,65533,65534,65534,
    65534,65535,65535,65535,65535,65535,65535,65535
};

const fixed_t *finecosine = &finesine[8192/4];

const angle_t tantoangle[2049] =
{
    0,333772,667544,1001315,1335086,1668857,2002626,2336395,
    2670163,3003929,3337694,3671457,4005219,4338979,4672736,5006492,
    5340245,5673995,6007743,6341488,6675230,7008968,7342704,7676435,
    8010164,8343888,8677609,9011325,9345037,9678744,10012447,10346145,
    10679838,11013526,11347209,11680887,12014558,12348225,12681885,13015539,
    13349187,13682829,14016464,14350092,14683714,15017328,15350936,15684536,
    16018129,16351714,16685291,17018860,17352422,17685974,18019518,18353054,
    18686582,19020100,19353610,19687110,20020600,20354080,20687552,21021014,
    21354466,21687906,22021338,22354758,22688168,23021568,23354956,23688332,
    24021698,24355052,24688396,25021726,25355046,25688352,26021648,26354930,
    26688200,27021456,27354702,27687932,28021150,28354356,28687548,29020724,
    29353888,29687038,30020174,30353296,30686404,31019496,31352574,31685636,
    32018684,32351718,32684734,33017736,33350722,33683692,34016648,34349584,
    34682508,35015412,35348300,35681172,36014028,36346868,36679688,37012492,
    37345276,37678044,38010792,38343524,38676240,39008936,39341612,39674272,
    40006912,40339532,40672132,41004716,41337276,41669820,42002344,42334848,
    42667332,42999796,43332236,43664660,43997060,44329444,44661800,44994140,
    45326456,45658752,45991028,46323280,46655512,46987720,47319908,47652072,
    47984212,48316332,48648428,48980500,49312548,49644576,49976580,50308556,
    50640512,50972444,51304352,51636236,51968096,52299928,52631740,52963524,
    53295284,53627020,53958728,54290412,54622068,54953704,55285308,55616888,
    55948444,56279972,56611472,56942948,57274396,57605816,57937212,58268576,
    58599916,58931228,59262512,59593768,59924992,60256192,60587364,60918508,
    61249620,61580704,61911760,62242788,62573788,62904756,63235692,63566604,
    63897480,64228332,64559148,64889940,65220696,65551424,65882120,66212788,
    66543420,66874024,67204600,67535136,67865648,68196120,68526568,68856984,
    69187360,69517712,69848024,70178304,70508560,70838776,71168960,71499112,
    71829224,72159312,72489360,72819376,73149360,73479304,73809216,74139096,
    74468936,74798744,75128520,75458264,75787968,76117632,76447264,76776864,
    77106424,77435952,77765440,78094888,78424304,78753688,79083032,79412336,
    79741608,80070840,80400032,80729192,81058312,81387392,81716432,82045440,
    82374408,82703336,83032224,83361080,83689896,84018664,84347400,84676096,
    85004760,85333376,85661952,85990488,86318984,86647448,86975864,87304240,
    87632576,87960872,88289128,88617344,88945520,89273648,89601736,89929792,
    90257792,90585760,90913688,91241568,91569408,91897200,92224960,92552672,
    92880336,93207968,93535552,93863088,94190584,94518040,94845448,95172816,
    95500136,95827416,96154648,96481832,96808976,97136080,97463136,97790144,
    98117112,98444032,98770904,99097736,99424520,99751256,100077944,100404592,
    100731192,101057744,101384248,101710712,102037128,102363488,102689808,103016080,
    103342312,103668488,103994616,104320696,104646736,104972720,105298656,105624552,
    105950392,106276184,106601928,106927624,107253272,107578872,107904416,108229920,
    108555368,108880768,109206120,109531416,109856664,110181872,110507016,110832120,
    111157168,111482168,111807112,112132008,112456856,112781648,113106392,113431080,
    113755720,114080312,114404848,114729328,115053760,115378136,115702464,116026744,
    116350960,116675128,116999248,117323312,117647320,117971272,118295176,118619024,
    118942816,119266560,119590248,119913880,120237456,120560984,120884456,121207864,
    121531224,121854528,122177784,122500976,122824112,123147200,123470224,123793200,
    124116120,124438976,124761784,125084528,125407224,125729856,126052432,126374960,
    126697424,127019832,127342184,127664472,127986712,128308888,128631008,128953072,
    129275080,129597024,129918912,130240744,130562520,130884232,131205888,131527480,
    131849016,132170496,132491912,132813272,133134576,133455816,133776992,134098120,
    134419184,134740176,135061120,135382000,135702816,136023584,136344272,136664912,
    136985488,137306016,137626464,137946864,138267184,138587456,138907664,139227808,
    139547904,139867920,140187888,140507776,140827616,141147392,141467104,141786752,
    142106336,142425856,142745312,143064720,143384048,143703312,144022512,144341664,
    144660736,144979744,145298704,145617584,145936400,146255168,146573856,146892480,
    147211040,147529536,147847968,148166336,148484640,148802880,149121056,149439152,
    149757200,150075168,150393072,150710912,151028688,151346400,151664048,151981616,
    152299136,152616576,152933952,153251264,153568496,153885680,154202784,154519824,
    154836784,155153696,155470528,155787296,156104000,156420624,156737200,157053696,
    157370112,157686480,158002768,158318976,158635136,158951216,159267232,159583168,
    159899040,160214848,160530592,160846256,161161840,161477376,161792832,162108208,
    162423520,162738768,163053952,163369040,163684080,163999040,164313936,164628752,
    164943504,165258176,165572784,165887312,166201776,166516160,166830480,167144736,
    167458912,167773008,168087040,168400992,168714880,169028688,169342432,169656096,
    169969696,170283216,170596672,170910032,171223344,171536576,171849728,172162800,
    172475808,172788736,173101600,173414384,173727104,174039728,174352288,174664784,
    174977200,175289536,175601792,175913984,176226096,176538144,176850096,177161984,
    177473792,177785536,178097200,178408784,178720288,179031728,179343088,179654368,
    179965568,180276704,180587744,180898720,181209616,181520448,181831184,182141856,
    182452448,182762960,183073408,183383760,183694048,184004240,184314368,184624416,
    184934400,185244288,185554096,185863840,186173504,186483072,186792576,187102000,
    187411344,187720608,188029808,188338912,188647936,188956896,189265760,189574560,
    189883264,190191904,190500448,190808928,191117312,191425632,191733872,192042016,
    192350096,192658096,192966000,193273840,193581584,193889264,194196848,194504352,
    194811792,195119136,195426400,195733584,196040688,196347712,196654656,196961520,
    197268304,197574992,197881616,198188144,198494592,198800960,199107248,199413456,
    199719584,200025616,200331584,200637456,200943248,201248960,201554576,201860128,
    202165584,202470960,202776256,203081456,203386592,203691632,203996592,204301472,
    204606256,204910976,205215600,205520144,205824592,206128960,206433248,206737456,
    207041584,207345616,207649568,207953424,208257216,208560912,208864512,209168048,
    209471488,209774832,210078112,210381296,210684384,210987408,211290336,211593184,
    211895936,212198608,212501184,212803680,213106096,213408432,213710672,214012816,
    214314880,214616864,214918768,215220576,215522288,215823920,216125472,216426928,
    216728304,217029584,217330784,217631904,217932928,218233856,218534704,218835472,
    219136144,219436720,219737216,220037632,220337952,220638192,220938336,221238384,
    221538352,221838240,222138032,222437728,222737344,223036880,223336304,223635664,
    223934912,224234096,224533168,224832160,225131072,225429872,225728608,226027232,
    226325776,226624240,226922608,227220880,227519056,227817152,228115168,228413088,
    228710912,229008640,229306288,229603840,229901312,230198688,230495968,230793152,
    231090256,231387280,231684192,231981024,232277760,232574416,232870960,233167440,
    233463808,233760096,234056288,234352384,234648384,234944304,235240128,235535872,
    235831504,236127056,236422512,236717888,237013152,237308336,237603424,237898416,
    238193328,238488144,238782864,239077488,239372016,239666464,239960816,240255072,
    240549232,240843312,241137280,241431168,241724960,242018656,242312256,242605776,
    242899200,243192512,243485744,243778896,244071936,244364880,244657744,244950496,
    245243168,245535744,245828224,246120608,246412912,246705104,246997216,247289216,
    247581136,247872960,248164688,248456320,248747856,249039296,249330640,249621904,
    249913056,250204128,250495088,250785968,251076736,251367424,251658016,251948512,
    252238912,252529200,252819408,253109520,253399536,253689456,253979280,254269008,
    254558640,254848176,255137632,255426976,255716224,256005376,256294432,256583392,
    256872256,257161024,257449696,257738272,258026752,258315136,258603424,258891600,
    259179696,259467696,259755600,260043392,260331104,260618704,260906224,261193632,
    261480960,261768176,262055296,262342320,262629248,262916080,263202816,263489456,
    263776000,264062432,264348784,264635024,264921168,265207216,265493168,265779024,
    266064784,266350448,266636000,266921472,267206832,267492096,267777264,268062336,
    268347312,268632192,268916960,269201632,269486208,269770688,270055072,270339360,
    270623552,270907616,271191616,271475488,271759296,272042976,272326560,272610048,
    272893440,273176736,273459936,273743040,274026048,274308928,274591744,274874432,
    275157024,275439520,275721920,276004224,276286432,276568512,276850528,277132416,
    277414240,277695936,277977536,278259040,278540448,278821728,279102944,279384032,
    279665056,279945952,280226752,280507456,280788064,281068544,281348960,281629248,
    281909472,282189568,282469568,282749440,283029248,283308960,283588544,283868032,
    284147424,284426720,284705920,284985024,285264000,285542912,285821696,286100384,
    286378976,286657440,286935840,287214112,287492320,287770400,288048384,288326240,
    288604032,288881696,289159264,289436768,289714112,289991392,290268576,290545632,
    290822592,291099456,291376224,291652896,291929440,292205888,292482272,292758528,
    293034656,293310720,293586656,293862496,294138240,294413888,294689440,294964864,
    295240192,295515424,295790560,296065600,296340512,296615360,296890080,297164704,
    297439200,297713632,297987936,298262144,298536256,298810240,299084160,299357952,
    299631648,299905248,300178720,300452128,300725408,300998592,301271680,301544640,
    301817536,302090304,302362976,302635520,302908000,303180352,303452608,303724768,
    303996800,304268768,304540608,304812320,305083968,305355520,305626944,305898272,
    306169472,306440608,306711616,306982528,307253344,307524064,307794656,308065152,
    308335552,308605856,308876032,309146112,309416096,309685984,309955744,310225408,
    310494976,310764448,311033824,311303072,311572224,311841280,312110208,312379040,
    312647776,312916416,313184960,313453376,313721696,313989920,314258016,314526016,
    314793920,315061728,315329408,315597024,315864512,316131872,316399168,316666336,
    316933408,317200384,317467232,317733984,318000640,318267200,318533632,318799968,
    319066208,319332352,319598368,319864288,320130112,320395808,320661408,320926912,
    321192320,321457632,321722816,321987904,322252864,322517760,322782528,323047200,
    323311744,323576192,323840544,324104800,324368928,324632992,324896928,325160736,
    325424448,325688096,325951584,326215008,326478304,326741504,327004608,327267584,
    327530464,327793248,328055904,328318496,328580960,328843296,329105568,329367712,
    329629760,329891680,330153536,330415264,330676864,330938400,331199808,331461120,
    331722304,331983392,332244384,332505280,332766048,333026752,333287296,333547776,
    333808128,334068384,334328544,334588576,334848512,335108352,335368064,335627712,
    335887200,336146624,336405920,336665120,336924224,337183200,337442112,337700864,
    337959552,338218112,338476576,338734944,338993184,339251328,339509376,339767296,
    340025120,340282848,340540480,340797984,341055392,341312704,341569888,341826976,
    342083968,342340832,342597600,342854272,343110848,343367296,343623648,343879904,
    344136032,344392064,344648000,344903808,345159520,345415136,345670656,345926048,
    346181344,346436512,346691616,346946592,347201440,347456224,347710880,347965440,
    348219872,348474208,348728448,348982592,349236608,349490528,349744320,349998048,
    350251648,350505152,350758528,351011808,351264992,351518048,351771040,352023872,
    352276640,352529280,352781824,353034272,353286592,353538816,353790944,354042944,
    354294880,354546656,354798368,355049952,355301440,355552800,355804096,356055264,
    356306304,356557280,356808128,357058848,357309504,357560032,357810464,358060768,
    358311008,358561088,358811104,359060992,359310784,359560480,359810048,360059520,
    360308896,360558144,360807296,361056352,361305312,361554144,361802880,362051488,
    362300032,362548448,362796736,363044960,363293056,363541024,363788928,364036704,
    364284384,364531936,364779392,365026752,365274016,365521152,365768192,366015136,
    366261952,366508672,366755296,367001792,367248192,367494496,367740704,367986784,
    368232768,368478656,368724416,368970080,369215648,369461088,369706432,369951680,
    370196800,370441824,370686752,370931584,371176288,371420896,371665408,371909792,
    372154080,372398272,372642336,372886304,373130176,373373952,373617600,373861152,
    374104608,374347936,374591168,374834304,375077312,375320224,375563040,375805760,
    376048352,376290848,376533248,376775520,377017696,377259776,377501728,377743584,
    377985344,378227008,378468544,378709984,378951328,379192544,379433664,379674688,
    379915584,380156416,380397088,380637696,380878176,381118560,381358848,381599040,
    381839104,382079072,382318912,382558656,382798304,383037856,383277280,383516640,
    383755840,383994976,384233984,384472896,384711712,384950400,385188992,385427488,
    385665888,385904160,386142336,386380384,386618368,386856224,387093984,387331616,
    387569152,387806592,388043936,388281152,388518272,388755296,388992224,389229024,
    389465728,389702336,389938816,390175200,390411488,390647680,390883744,391119712,
    391355584,391591328,391826976,392062528,392297984,392533312,392768544,393003680,
    393238720,393473632,393708448,393943168,394177760,394412256,394646656,394880960,
    395115136,395349216,395583200,395817088,396050848,396284512,396518080,396751520,
    396984864,397218112,397451264,397684288,397917248,398150080,398382784,398615424,
    398847936,399080320,399312640,399544832,399776928,400008928,400240832,400472608,
    400704288,400935872,401167328,401398720,401629984,401861120,402092192,402323136,
    402553984,402784736,403015360,403245888,403476320,403706656,403936896,404167008,
    404397024,404626944,404856736,405086432,405316032,405545536,405774912,406004224,
    406233408,406462464,406691456,406920320,407149088,407377760,407606336,407834784,
    408063136,408291392,408519520,408747584,408975520,409203360,409431072,409658720,
    409886240,410113664,410340992,410568192,410795296,411022304,411249216,411476032,
    411702720,411929312,412155808,412382176,412608480,412834656,413060736,413286720,
    413512576,413738336,413964000,414189568,414415040,414640384,414865632,415090784,
    415315840,415540800,415765632,415990368,416215008,416439552,416663968,416888288,
    417112512,417336640,417560672,417784576,418008384,418232096,418455712,418679200,
    418902624,419125920,419349120,419572192,419795200,420018080,420240864,420463552,
    420686144,420908608,421130976,421353280,421575424,421797504,422019488,422241344,
    422463104,422684768,422906336,423127776,423349120,423570400,423791520,424012576,
    424233536,424454368,424675104,424895744,425116288,425336736,425557056,425777280,
    425997408,426217440,426437376,426657184,426876928,427096544,427316064,427535488,
    427754784,427974016,428193120,428412128,428631040,428849856,429068544,429287168,
    429505664,429724064,429942368,430160576,430378656,430596672,430814560,431032352,
    431250048,431467616,431685120,431902496,432119808,432336992,432554080,432771040,
    432987936,433204736,433421408,433637984,433854464,434070848,434287104,434503296,
    434719360,434935360,435151232,435367008,435582656,435798240,436013696,436229088,
    436444352,436659520,436874592,437089568,437304416,437519200,437733856,437948416,
    438162880,438377248,438591520,438805696,439019744,439233728,439447584,439661344,
    439875008,440088576,440302048,440515392,440728672,440941824,441154880,441367872,
    441580736,441793472,442006144,442218720,442431168,442643552,442855808,443067968,
    443280032,443492000,443703872,443915648,444127296,444338880,444550336,444761696,
    444972992,445184160,445395232,445606176,445817056,446027840,446238496,446449088,
    446659552,446869920,447080192,447290400,447500448,447710432,447920320,448130112,
    448339776,448549376,448758848,448968224,449177536,449386720,449595808,449804800,
    450013664,450222464,450431168,450639776,450848256,451056640,451264960,451473152,
    451681248,451889248,452097152,452304960,452512672,452720288,452927808,453135232,
    453342528,453549760,453756864,453963904,454170816,454377632,454584384,454791008,
    454997536,455203968,455410304,455616544,455822688,456028704,456234656,456440512,
    456646240,456851904,457057472,457262912,457468256,457673536,457878688,458083744,
    458288736,458493600,458698368,458903040,459107616,459312096,459516480,459720768,
    459924960,460129056,460333056,460536960,460740736,460944448,461148064,461351584,
    461554976,461758304,461961536,462164640,462367680,462570592,462773440,462976160,
    463178816,463381344,463583776,463786144,463988384,464190560,464392608,464594560,
    464796448,464998208,465199872,465401472,465602944,465804320,466005600,466206816,
    466407904,466608896,466809824,467010624,467211328,467411936,467612480,467812896,
    468013216,468213440,468413600,468613632,468813568,469013440,469213184,469412832,
    469612416,469811872,470011232,470210528,470409696,470608800,470807776,471006688,
    471205472,471404192,471602784,471801312,471999712,472198048,472396288,472594400,
    472792448,472990400,473188256,473385984,473583648,473781216,473978688,474176064,
    474373344,474570528,474767616,474964608,475161504,475358336,475555040,475751648,
    475948192,476144608,476340928,476537184,476733312,476929376,477125344,477321184,
    477516960,477712640,477908224,478103712,478299104,478494400,478689600,478884704,
    479079744,479274656,479469504,479664224,479858880,480053408,480247872,480442240,
    480636512,480830656,481024736,481218752,481412640,481606432,481800128,481993760,
    482187264,482380704,482574016,482767264,482960416,483153472,483346432,483539296,
    483732064,483924768,484117344,484309856,484502240,484694560,484886784,485078912,
    485270944,485462880,485654720,485846464,486038144,486229696,486421184,486612576,
    486803840,486995040,487186176,487377184,487568096,487758912,487949664,488140320,
    488330880,488521312,488711712,488901984,489092160,489282240,489472256,489662176,
    489851968,490041696,490231328,490420896,490610336,490799712,490988960,491178144,
    491367232,491556224,491745120,491933920,492122656,492311264,492499808,492688256,
    492876608,493064864,493253056,493441120,493629120,493817024,494004832,494192544,
    494380160,494567712,494755136,494942496,495129760,495316928,495504000,495691008,
    495877888,496064704,496251424,496438048,496624608,496811040,496997408,497183680,
    497369856,497555936,497741920,497927840,498113632,498299360,498484992,498670560,
    498856000,499041376,499226656,499411840,499596928,499781920,499966848,500151680,
    500336416,500521056,500705600,500890080,501074464,501258752,501442944,501627040,
    501811072,501995008,502178848,502362592,502546240,502729824,502913312,503096704,
    503280000,503463232,503646368,503829408,504012352,504195200,504377984,504560672,
    504743264,504925760,505108192,505290496,505472736,505654912,505836960,506018944,
    506200832,506382624,506564320,506745952,506927488,507108928,507290272,507471552,
    507652736,507833824,508014816,508195744,508376576,508557312,508737952,508918528,
    509099008,509279392,509459680,509639904,509820032,510000064,510180000,510359872,
    510539648,510719328,510898944,511078432,511257856,511437216,511616448,511795616,
    511974688,512153664,512332576,512511392,512690112,512868768,513047296,513225792,
    513404160,513582432,513760640,513938784,514116800,514294752,514472608,514650368,
    514828064,515005664,515183168,515360608,515537952,515715200,515892352,516069440,
    516246432,516423328,516600160,516776896,516953536,517130112,517306592,517482976,
    517659264,517835488,518011616,518187680,518363648,518539520,518715296,518891008,
    519066624,519242144,519417600,519592960,519768256,519943424,520118528,520293568,
    520468480,520643328,520818112,520992800,521167392,521341888,521516320,521690656,
    521864896,522039072,522213152,522387168,522561056,522734912,522908640,523082304,
    523255872,523429376,523602784,523776096,523949312,524122464,524295552,524468512,
    524641440,524814240,524986976,525159616,525332192,525504640,525677056,525849344,
    526021568,526193728,526365792,526537760,526709632,526881440,527053152,527224800,
    527396352,527567840,527739200,527910528,528081728,528252864,528423936,528594880,
    528765760,528936576,529107296,529277920,529448480,529618944,529789344,529959648,
    530129856,530300000,530470048,530640000,530809888,530979712,531149440,531319072,
    531488608,531658080,531827488,531996800,532166016,532335168,532504224,532673184,
    532842080,533010912,533179616,533348288,533516832,533685312,533853728,534022048,
    534190272,534358432,534526496,534694496,534862400,535030240,535197984,535365632,
    535533216,535700704,535868128,536035456,536202720,536369888,536536992,536704000,
    536870912
};


const byte gammatable[5][256] =
{
    {
        1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
        17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
        33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,
        49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,
        65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,
        81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,
        97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,
        113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,
        128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
        144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
        160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
        176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
        192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
        208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
        224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
        240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
    },

    {
        2,4,5,7,8,10,11,12,14,15,16,18,19,20,21,23,
        24,25,26,27,29,30,31,32,33,34,36,37,38,39,40,41,
        42,44,45,46,47,48,49,50,51,52,54,55,56,57,58,59,
        60,61,62,63,64,65,66,67,69,70,71,72,73,74,75,76,
        77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,
        93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,
        109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,
        125,126,127,128,129,129,130,131,132,133,134,135,136,137,138,139,
        140,141,142,143,144,145,146,147,148,148,149,150,151,152,153,154,
        155,156,157,158,159,160,161,162,163,163,164,165,166,167,168,169,
        170,171,172,173,174,175,175,176,177,178,179,180,181,182,183,184,
        185,186,186,187,188,189,190,191,192,193,194,195,196,196,197,198,
        199,200,201,202,203,204,205,205,206,207,208,209,210,211,212,213,
        214,214,215,216,217,218,219,220,221,222,222,223,224,225,226,227,
        228,229,230,230,231,232,233,234,235,236,237,237,238,239,240,241,
        242,243,244,245,245,246,247,248,249,250,251,252,252,253,254,255
    },

    {
        4,7,9,11,13,15,17,19,21,22,24,26,27,29,30,32,
        33,35,36,38,39,40,42,43,45,46,47,48,50,51,52,54,
        55,56,57,59,60,61,62,63,65,66,67,68,69,70,72,73,
        74,75,76,77,78,79,80,82,83,84,85,86,87,88,89,90,
        91,92,93,94,95,96,97,98,100,101,102,103,104,105,106,107,
        108,109,110,111,112,113,114,114,115,116,117,118,119,120,121,122,
        123,124,125,126,127,128,129,130,131,132,133,133,134,135,136,137,
        138,139,140,141,142,143,144,144,145,146,147,148,149,150,151,152,
        153,153,154,155,156,157,158,159,160,160,161,162,163,164,165,166,
        166,167,168,169,170,171,172,172,173,174,175,176,177,178,178,179,
        180,181,182,183,183,184,185,186,187,188,188,189,190,191,192,193,
        193,194,195,196,197,197,198,199,200,201,201,202,203,204,205,206,
        206,207,208,209,210,210,211,212,213,213,214,215,216,217,217,218,
        219,220,221,221,222,223,224,224,225,226,227,228,228,229,230,231,
        231,232,233,234,235,235,236,237,238,238,239,240,241,241,242,243,
        244,244,245,246,247,247,248,249,250,251,251,252,253,254,254,255
    },

    {
        8,12,16,19,22,24,27,29,31,34,36,38,40,41,43,45,
        47,49,50,52,53,55,57,58,60,61,63,64,65,67,68,70,
        71,72,74,75,76,77,79,80,81,82,84,85,86,87,88,90,
        91,92,93,94,95,96,98,99,100,101,102,103,104,105,106,107,
        108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,
        124,125,126,127,128,129,130,131,132,133,134,135,135,136,137,138,
        139,140,141,142,143,143,144,145,146,147,148,149,150,150,151,152,
        153,154,155,155,156,157,158,159,160,160,161,162,163,164,165,165,
        166,167,168,169,169,170,171,172,173,173,174,175,176,176,177,178,
        179,180,180,181,182,183,183,184,185,186,186,187,188,189,189,190,
        191,192,192,193,194,195,195,196,197,197,198,199,200,200,201,202,
        202,203,204,205,205,206,207,207,208,209,210,210,211,212,212,213,
        214,214,215,216,216,217,218,219,219,220,221,221,222,223,223,224,
        225,225,226,227,227,228,229,229,230,231,231,232,233,233,234,235,
        235,236,237,237,238,238,239,240,240,241,242,242,243,244,244,245,
        246,246,247,247,248,249,249,250,251,251,252,253,253,254,254,255
    },


    {
        16,23,28,32,36,39,42,45,48,50,53,55,57,60,62,64,
        66,68,69,71,73,75,76,78,80,81,83,84,86,87,89,90,
        92,93,94,96,97,98,100,101,102,103,105,106,107,108,109,110,
        112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,128,
        128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
        143,144,145,146,147,148,149,150,150,151,152,153,154,155,155,156,
        157,158,159,159,160,161,162,163,163,164,165,166,166,167,168,169,
        169,170,171,172,172,173,174,175,175,176,177,177,178,179,180,180,
        181,182,182,183,184,184,185,186,187,187,188,189,189,190,191,191,
        192,193,193,194,195,195,196,196,197,198,198,199,200,200,201,202,
        202,203,203,204,205,205,206,207,207,208,208,209,210,210,211,211,
        212,213,213,214,214,215,216,216,217,217,218,219,219,220,220,221,
        221,222,223,223,224,224,225,225,226,227,227,228,228,229,229,230,
        230,231,232,232,233,233,234,234,235,235,236,236,237,237,238,239,
        239,240,240,241,241,242,242,243,243,244,244,245,245,246,246,247,
        247,248,248,249,249,250,250,251,251,252,252,253,254,254,255,255
    }
};
byte *tinttable = ((void*)0);


byte *xlatab = ((void*)0);



static byte *dest_screen = ((void*)0);

int dirtybox[4];



static vpatchclipfunc_t patchclip_callback = ((void*)0);




void V_MarkRect(int x, int y, int width, int height)
{



    if (dest_screen == I_VideoBuffer)
    {
        M_AddToBox (dirtybox, x, y);
        M_AddToBox (dirtybox, x + width-1, y + height-1);
    }
}





void V_CopyRect(int srcx, int srcy, byte *source,
                int width, int height,
                int destx, int desty)
{
    byte *src;
    byte *dest;


    if (srcx < 0
     || srcx + width > 320
     || srcy < 0
     || srcy + height > 200
     || destx < 0
     || destx + width > 320
     || desty < 0
     || desty + height > 200)
    {
        I_Error ("Bad V_CopyRect");
    }


    V_MarkRect(destx, desty, width, height);

    src = source + 320 * srcy + srcx;
    dest = dest_screen + 320 * desty + destx;

    for ( ; height>0 ; height--)
    {
        memcpy(dest, src, width);
        src += 320;
        dest += 320;
    }
}
void V_SetPatchClipCallback(vpatchclipfunc_t func)
{
    patchclip_callback = func;
}






void V_DrawPatch(int x, int y, patch_t *patch)
{
    int count;
    int col;
    column_t *column;
    byte *desttop;
    byte *dest;
    byte *source;
    int w;

    y -= ((signed short) (patch->topoffset));
    x -= ((signed short) (patch->leftoffset));


    if(patchclip_callback)
    {
        if(!patchclip_callback(patch, x, y))
            return;
    }


    if (x < 0
     || x + ((signed short) (patch->width)) > 320
     || y < 0
     || y + ((signed short) (patch->height)) > 200)
    {
        I_Error("Bad V_DrawPatch x=%i y=%i patch.width=%i patch.height=%i topoffset=%i leftoffset=%i", x, y, patch->width, patch->height, patch->topoffset, patch->leftoffset);
    }


    V_MarkRect(x, y, ((signed short) (patch->width)), ((signed short) (patch->height)));

    col = 0;
    desttop = dest_screen + y * 320 + x;

    w = ((signed short) (patch->width));

    for ( ; col<w ; x++, col++, desttop++)
    {
        column = (column_t *)((byte *)patch + ((signed int) (patch->columnofs[col])));


        while (column->topdelta != 0xff)
        {
            source = (byte *)column + 3;
            dest = desttop + column->topdelta*320;
            count = column->length;

            while (count--)
            {
                *dest = *source++;
                dest += 320;
            }
            column = (column_t *)((byte *)column + column->length + 4);
        }
    }
}







void V_DrawPatchFlipped(int x, int y, patch_t *patch)
{
    int count;
    int col;
    column_t *column;
    byte *desttop;
    byte *dest;
    byte *source;
    int w;

    y -= ((signed short) (patch->topoffset));
    x -= ((signed short) (patch->leftoffset));


    if(patchclip_callback)
    {
        if(!patchclip_callback(patch, x, y))
            return;
    }


    if (x < 0
     || x + ((signed short) (patch->width)) > 320
     || y < 0
     || y + ((signed short) (patch->height)) > 200)
    {
        I_Error("Bad V_DrawPatchFlipped");
    }


    V_MarkRect (x, y, ((signed short) (patch->width)), ((signed short) (patch->height)));

    col = 0;
    desttop = dest_screen + y * 320 + x;

    w = ((signed short) (patch->width));

    for ( ; col<w ; x++, col++, desttop++)
    {
        column = (column_t *)((byte *)patch + ((signed int) (patch->columnofs[w-1-col])));


        while (column->topdelta != 0xff )
        {
            source = (byte *)column + 3;
            dest = desttop + column->topdelta*320;
            count = column->length;

            while (count--)
            {
                *dest = *source++;
                dest += 320;
            }
            column = (column_t *)((byte *)column + column->length + 4);
        }
    }
}
void V_DrawPatchDirect(int x, int y, patch_t *patch)
{
    V_DrawPatch(x, y, patch);
}







void V_DrawTLPatch(int x, int y, patch_t * patch)
{
    int count, col;
    column_t *column;
    byte *desttop, *dest, *source;
    int w;

    y -= ((signed short) (patch->topoffset));
    x -= ((signed short) (patch->leftoffset));

    if (x < 0
     || x + ((signed short) (patch->width)) > 320
     || y < 0
     || y + ((signed short) (patch->height)) > 200)
    {
        I_Error("Bad V_DrawTLPatch");
    }

    col = 0;
    desttop = dest_screen + y * 320 + x;

    w = ((signed short) (patch->width));
    for (; col < w; x++, col++, desttop++)
    {
        column = (column_t *) ((byte *) patch + ((signed int) (patch->columnofs[col])));



        while (column->topdelta != 0xff)
        {
            source = (byte *) column + 3;
            dest = desttop + column->topdelta * 320;
            count = column->length;

            while (count--)
            {
                *dest = tinttable[((*dest) << 8) + *source++];
                dest += 320;
            }
            column = (column_t *) ((byte *) column + column->length + 4);
        }
    }
}







void V_DrawXlaPatch(int x, int y, patch_t * patch)
{
    int count, col;
    column_t *column;
    byte *desttop, *dest, *source;
    int w;

    y -= ((signed short) (patch->topoffset));
    x -= ((signed short) (patch->leftoffset));

    if(patchclip_callback)
    {
        if(!patchclip_callback(patch, x, y))
            return;
    }

    col = 0;
    desttop = dest_screen + y * 320 + x;

    w = ((signed short) (patch->width));
    for(; col < w; x++, col++, desttop++)
    {
        column = (column_t *) ((byte *) patch + ((signed int) (patch->columnofs[col])));



        while(column->topdelta != 0xff)
        {
            source = (byte *) column + 3;
            dest = desttop + column->topdelta * 320;
            count = column->length;

            while(count--)
            {
                *dest = xlatab[*dest + ((*source) << 8)];
                source++;
                dest += 320;
            }
            column = (column_t *) ((byte *) column + column->length + 4);
        }
    }
}







void V_DrawAltTLPatch(int x, int y, patch_t * patch)
{
    int count, col;
    column_t *column;
    byte *desttop, *dest, *source;
    int w;

    y -= ((signed short) (patch->topoffset));
    x -= ((signed short) (patch->leftoffset));

    if (x < 0
     || x + ((signed short) (patch->width)) > 320
     || y < 0
     || y + ((signed short) (patch->height)) > 200)
    {
        I_Error("Bad V_DrawAltTLPatch");
    }

    col = 0;
    desttop = dest_screen + y * 320 + x;

    w = ((signed short) (patch->width));
    for (; col < w; x++, col++, desttop++)
    {
        column = (column_t *) ((byte *) patch + ((signed int) (patch->columnofs[col])));



        while (column->topdelta != 0xff)
        {
            source = (byte *) column + 3;
            dest = desttop + column->topdelta * 320;
            count = column->length;

            while (count--)
            {
                *dest = tinttable[((*dest) << 8) + *source++];
                dest += 320;
            }
            column = (column_t *) ((byte *) column + column->length + 4);
        }
    }
}







void V_DrawShadowedPatch(int x, int y, patch_t *patch)
{
    int count, col;
    column_t *column;
    byte *desttop, *dest, *source;
    byte *desttop2, *dest2;
    int w;

    y -= ((signed short) (patch->topoffset));
    x -= ((signed short) (patch->leftoffset));

    if (x < 0
     || x + ((signed short) (patch->width)) > 320
     || y < 0
     || y + ((signed short) (patch->height)) > 200)
    {
        I_Error("Bad V_DrawShadowedPatch");
    }

    col = 0;
    desttop = dest_screen + y * 320 + x;
    desttop2 = dest_screen + (y + 2) * 320 + x + 2;

    w = ((signed short) (patch->width));
    for (; col < w; x++, col++, desttop++, desttop2++)
    {
        column = (column_t *) ((byte *) patch + ((signed int) (patch->columnofs[col])));



        while (column->topdelta != 0xff)
        {
            source = (byte *) column + 3;
            dest = desttop + column->topdelta * 320;
            dest2 = desttop2 + column->topdelta * 320;
            count = column->length;

            while (count--)
            {
                *dest2 = tinttable[((*dest2) << 8)];
                dest2 += 320;
                *dest = *source++;
                dest += 320;

            }
            column = (column_t *) ((byte *) column + column->length + 4);
        }
    }
}





void V_LoadTintTable(void)
{
    tinttable = W_CacheLumpName("TINTTAB", PU_STATIC);
}







void V_LoadXlaTable(void)
{
    xlatab = W_CacheLumpName("XLATAB", PU_STATIC);
}






void V_DrawBlock(int x, int y, int width, int height, byte *src)
{
    byte *dest;


    if (x < 0
     || x + width >320
     || y < 0
     || y + height > 200)
    {
 I_Error ("Bad V_DrawBlock");
    }


    V_MarkRect (x, y, width, height);

    dest = dest_screen + y * 320 + x;

    while (height--)
    {
 memcpy (dest, src, width);
 src += width;
 dest += 320;
    }
}

void V_DrawFilledBox(int x, int y, int w, int h, int c)
{
    uint8_t *buf, *buf1;
    int x1, y1;

    buf = I_VideoBuffer + 320 * y + x;

    for (y1 = 0; y1 < h; ++y1)
    {
        buf1 = buf;

        for (x1 = 0; x1 < w; ++x1)
        {
            *buf1++ = c;
        }

        buf += 320;
    }
}

void V_DrawHorizLine(int x, int y, int w, int c)
{
    uint8_t *buf;
    int x1;

    buf = I_VideoBuffer + 320 * y + x;

    for (x1 = 0; x1 < w; ++x1)
    {
        *buf++ = c;
    }
}

void V_DrawVertLine(int x, int y, int h, int c)
{
    uint8_t *buf;
    int y1;

    buf = I_VideoBuffer + 320 * y + x;

    for (y1 = 0; y1 < h; ++y1)
    {
        *buf = c;
        buf += 320;
    }
}

void V_DrawBox(int x, int y, int w, int h, int c)
{
    V_DrawHorizLine(x, y, w, c);
    V_DrawHorizLine(x, y+h-1, w, c);
    V_DrawVertLine(x, y, h, c);
    V_DrawVertLine(x+w-1, y, h, c);
}






void V_DrawRawScreen(byte *raw)
{
    memcpy(dest_screen, raw, 320 * 200);
}




void V_Init (void)
{



}



void V_UseBuffer(byte *buffer)
{
    dest_screen = buffer;
}



void V_RestoreBuffer(void)
{
    dest_screen = I_VideoBuffer;
}





typedef struct
{
    char manufacturer;
    char version;
    char encoding;
    char bits_per_pixel;

    unsigned short xmin;
    unsigned short ymin;
    unsigned short xmax;
    unsigned short ymax;

    unsigned short hres;
    unsigned short vres;

    unsigned char palette[48];

    char reserved;
    char color_planes;
    unsigned short bytes_per_line;
    unsigned short palette_type;

    char filler[58];
    unsigned char data;
} __attribute__((packed)) pcx_t;






void WritePCXfile(char *filename, byte *data,
                  int width, int height,
                  byte *palette)
{
    int i;
    int length;
    pcx_t* pcx;
    byte* pack;

    pcx = Z_Malloc (width*height*2+1000, PU_STATIC, ((void*)0));

    pcx->manufacturer = 0x0a;
    pcx->version = 5;
    pcx->encoding = 1;
    pcx->bits_per_pixel = 8;
    pcx->xmin = 0;
    pcx->ymin = 0;
    pcx->xmax = ((signed short) (width-1));
    pcx->ymax = ((signed short) (height-1));
    pcx->hres = ((signed short) (width));
    pcx->vres = ((signed short) (height));
    memset (pcx->palette,0,sizeof(pcx->palette));
    pcx->color_planes = 1;
    pcx->bytes_per_line = ((signed short) (width));
    pcx->palette_type = ((signed short) (2));
    memset (pcx->filler,0,sizeof(pcx->filler));


    pack = &pcx->data;

    for (i=0 ; i<width*height ; i++)
    {
 if ( (*data & 0xc0) != 0xc0)
     *pack++ = *data++;
 else
 {
     *pack++ = 0xc1;
     *pack++ = *data++;
 }
    }


    *pack++ = 0x0c;
    for (i=0 ; i<768 ; i++)
 *pack++ = *palette++;


    length = pack - (byte *)pcx;
    M_WriteFile (filename, pcx, length);

    Z_Free (pcx);
}
void V_ScreenShot(char *format)
{
    int i;
    char lbmname[16];
    char *ext;
    {
        ext = "pcx";
    }

    for (i=0; i<=99; i++)
    {
        M_snprintf(lbmname, sizeof(lbmname), format, i, ext);

        if (!M_FileExists(lbmname))
        {
            break;
        }
    }

    if (i == 100)
    {
        I_Error ("V_ScreenShot: Couldn't create a PCX");
    }
    {

    WritePCXfile(lbmname, I_VideoBuffer,
                 320, 200,
                 W_CacheLumpName (("PLAYPAL"), PU_CACHE));
    }
}




void V_DrawMouseSpeedBox(int speed)
{
    extern int usemouse;
    int bgcolor, bordercolor, red, black, white, yellow;
    int box_x, box_y;
    int original_speed;
    int redline_x;
    int linelen;




    bgcolor = I_GetPaletteIndex(0x77, 0x77, 0x77);
    bordercolor = I_GetPaletteIndex(0x55, 0x55, 0x55);
    red = I_GetPaletteIndex(0xff, 0x00, 0x00);
    black = I_GetPaletteIndex(0x00, 0x00, 0x00);
    yellow = I_GetPaletteIndex(0xff, 0xff, 0x00);
    white = I_GetPaletteIndex(0xff, 0xff, 0xff);




    if (!usemouse || fabs(mouse_acceleration - 1) < 0)
    {
        return;
    }



    box_x = 320 - 120 - 10;
    box_y = 15;

    V_DrawFilledBox(box_x, box_y,
                    120, 9, bgcolor);
    V_DrawBox(box_x, box_y,
              120, 9, bordercolor);




    redline_x = 120 / 3;



    if (speed < mouse_threshold)
    {
        original_speed = speed;
    }
    else
    {
        original_speed = speed - mouse_threshold;
        original_speed = (int) (original_speed / mouse_acceleration);
        original_speed += mouse_threshold;
    }



    linelen = (original_speed * redline_x) / mouse_threshold;



    if (linelen > 120 - 1)
    {
        linelen = 120 - 1;
    }

    V_DrawHorizLine(box_x + 1, box_y + 4, 120 - 2, black);

    if (linelen < redline_x)
    {
        V_DrawHorizLine(box_x + 1, box_y + 9 / 2,
                      linelen, white);
    }
    else
    {
        V_DrawHorizLine(box_x + 1, box_y + 9 / 2,
                        redline_x, white);
        V_DrawHorizLine(box_x + redline_x, box_y + 9 / 2,
                        linelen - redline_x, yellow);
    }



    V_DrawVertLine(box_x + redline_x, box_y + 1,
                 9 - 2, red);
}
typedef enum
{
    ANIM_ALWAYS,
    ANIM_RANDOM,
    ANIM_LEVEL

} animenum_t;

typedef struct
{
    int x;
    int y;

} point_t;






typedef struct
{
    animenum_t type;


    int period;


    int nanims;


    point_t loc;




    int data1;




    int data2;


    patch_t* p[3];




    int nexttic;


    int lastdrawn;


    int ctr;


    int state;

} wi_anim_t;


static point_t lnodes[4][9] =
{

    {
 { 185, 164 },
 { 148, 143 },
 { 69, 122 },
 { 209, 102 },
 { 116, 89 },
 { 166, 55 },
 { 71, 56 },
 { 135, 29 },
 { 71, 24 }
    },


    {
 { 254, 25 },
 { 97, 50 },
 { 188, 64 },
 { 128, 78 },
 { 214, 92 },
 { 133, 130 },
 { 208, 136 },
 { 148, 140 },
 { 235, 158 }
    },


    {
 { 156, 168 },
 { 48, 154 },
 { 174, 95 },
 { 265, 75 },
 { 130, 48 },
 { 279, 23 },
 { 198, 48 },
 { 140, 25 },
 { 281, 136 }
    }

};
static wi_anim_t epsd0animinfo[] =
{
    { (ANIM_ALWAYS), (35/3), (3), { (224), (104) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (184), (160) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (112), (136) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (72), (112) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (88), (96) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (64), (48) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (192), (40) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (136), (16) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (80), (16) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (64), (24) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
};

static wi_anim_t epsd1animinfo[] =
{
    { (ANIM_LEVEL), (35/3), (1), { (128), (136) }, (1), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_LEVEL), (35/3), (1), { (128), (136) }, (2), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_LEVEL), (35/3), (1), { (128), (136) }, (3), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_LEVEL), (35/3), (1), { (128), (136) }, (4), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_LEVEL), (35/3), (1), { (128), (136) }, (5), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_LEVEL), (35/3), (1), { (128), (136) }, (6), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_LEVEL), (35/3), (1), { (128), (136) }, (7), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_LEVEL), (35/3), (3), { (192), (144) }, (8), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_LEVEL), (35/3), (1), { (128), (136) }, (8), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
};

static wi_anim_t epsd2animinfo[] =
{
    { (ANIM_ALWAYS), (35/3), (3), { (104), (168) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (40), (136) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (160), (96) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (104), (80) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/3), (3), { (120), (32) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
    { (ANIM_ALWAYS), (35/4), (3), { (40), (0) }, (0), 0, { ((void*)0), ((void*)0), ((void*)0) }, 0, 0, 0, 0 },
};

static int NUMANIMS[4] =
{
    (sizeof(epsd0animinfo) / sizeof(*epsd0animinfo)),
    (sizeof(epsd1animinfo) / sizeof(*epsd1animinfo)),
    (sizeof(epsd2animinfo) / sizeof(*epsd2animinfo)),
};

static wi_anim_t *wi_anims[4] =
{
    epsd0animinfo,
    epsd1animinfo,
    epsd2animinfo
};
static int acceleratestage;


static int me;


static stateenum_t state;


static wbstartstruct_t* wbs;

static wbplayerstruct_t* plrs;


static int cnt;


static int bcnt;


static int firstrefresh;

static int cnt_kills[4];
static int cnt_items[4];
static int cnt_secret[4];
static int cnt_time;
static int cnt_par;
static int cnt_pause;


static int NUMCMAPS;







static patch_t* yah[3] = { ((void*)0), ((void*)0), ((void*)0) };


static patch_t* splat[2] = { ((void*)0), ((void*)0) };


static patch_t* percent;
static patch_t* colon;


static patch_t* num[10];


static patch_t* wiminus;


static patch_t* finished;


static patch_t* entering;


static patch_t* sp_secret;


static patch_t* kills;
static patch_t* secret;
static patch_t* items;
static patch_t* frags;


static patch_t* timepatch;
static patch_t* par;
static patch_t* sucks;


static patch_t* killers;
static patch_t* victims;


static patch_t* total;
static patch_t* star;
static patch_t* bstar;


static patch_t* p[4];


static patch_t* bp[4];


static patch_t** lnames;


static patch_t *background;






void WI_slamBackground(void)
{
    V_DrawPatch(0, 0, background);
}



boolean WI_Responder(event_t* ev)
{
    return false;
}



void WI_drawLF(void)
{
    int y = 2;

    if (gamemode != commercial || wbs->last < NUMCMAPS)
    {

        V_DrawPatch((320 - ((signed short) (lnames[wbs->last]->width)))/2,
                    y, lnames[wbs->last]);


        y += (5*((signed short) (lnames[wbs->last]->height)))/4;

        V_DrawPatch((320 - ((signed short) (finished->width))) / 2, y, finished);
    }
    else if (wbs->last == NUMCMAPS)
    {

    }
    else if (wbs->last > NUMCMAPS)
    {





        patch_t tmp = { 320, 200, 1, 1,
                        { 0, 0, 0, 0, 0, 0, 0, 0 } };

        V_DrawPatch(0, y, &tmp);
    }
}




void WI_drawEL(void)
{
    int y = 2;


    V_DrawPatch((320 - ((signed short) (entering->width)))/2,
  y,
                entering);


    y += (5*((signed short) (lnames[wbs->next]->height)))/4;

    V_DrawPatch((320 - ((signed short) (lnames[wbs->next]->width)))/2,
  y,
                lnames[wbs->next]);

}

void
WI_drawOnLnode
( int n,
  patch_t* c[] )
{

    int i;
    int left;
    int top;
    int right;
    int bottom;
    boolean fits = false;

    i = 0;
    do
    {
 left = lnodes[wbs->epsd][n].x - ((signed short) (c[i]->leftoffset));
 top = lnodes[wbs->epsd][n].y - ((signed short) (c[i]->topoffset));
 right = left + ((signed short) (c[i]->width));
 bottom = top + ((signed short) (c[i]->height));

 if (left >= 0
     && right < 320
     && top >= 0
     && bottom < 200)
 {
     fits = true;
 }
 else
 {
     i++;
 }
    } while (!fits && i!=2 && c[i] != ((void*)0));

    if (fits && i<2)
    {
 V_DrawPatch(lnodes[wbs->epsd][n].x,
                    lnodes[wbs->epsd][n].y,
      c[i]);
    }
    else
    {

 printf("Could not place patch on level %d", n+1);
    }
}



void WI_initAnimatedBack(void)
{
    int i;
    wi_anim_t* a;

    if (gamemode == commercial)
 return;

    if (wbs->epsd > 2)
 return;

    for (i=0;i<NUMANIMS[wbs->epsd];i++)
    {
 a = &wi_anims[wbs->epsd][i];


 a->ctr = -1;


 if (a->type == ANIM_ALWAYS)
     a->nexttic = bcnt + 1 + (M_Random()%a->period);
 else if (a->type == ANIM_RANDOM)
     a->nexttic = bcnt + 1 + a->data2+(M_Random()%a->data1);
 else if (a->type == ANIM_LEVEL)
     a->nexttic = bcnt + 1;
    }

}

void WI_updateAnimatedBack(void)
{
    int i;
    wi_anim_t* a;

    if (gamemode == commercial)
 return;

    if (wbs->epsd > 2)
 return;

    for (i=0;i<NUMANIMS[wbs->epsd];i++)
    {
 a = &wi_anims[wbs->epsd][i];

 if (bcnt == a->nexttic)
 {
     switch (a->type)
     {
       case ANIM_ALWAYS:
  if (++a->ctr >= a->nanims) a->ctr = 0;
  a->nexttic = bcnt + a->period;
  break;

       case ANIM_RANDOM:
  a->ctr++;
  if (a->ctr == a->nanims)
  {
      a->ctr = -1;
      a->nexttic = bcnt+a->data2+(M_Random()%a->data1);
  }
  else a->nexttic = bcnt + a->period;
  break;

       case ANIM_LEVEL:

  if (!(state == StatCount && i == 7)
      && wbs->next == a->data1)
  {
      a->ctr++;
      if (a->ctr == a->nanims) a->ctr--;
      a->nexttic = bcnt + a->period;
  }
  break;
     }
 }

    }

}

void WI_drawAnimatedBack(void)
{
    int i;
    wi_anim_t* a;

    if (gamemode == commercial)
 return;

    if (wbs->epsd > 2)
 return;

    for (i=0 ; i<NUMANIMS[wbs->epsd] ; i++)
    {
 a = &wi_anims[wbs->epsd][i];

 if (a->ctr >= 0)
     V_DrawPatch(a->loc.x, a->loc.y, a->p[a->ctr]);
    }

}
int
WI_drawNum
( int x,
  int y,
  int n,
  int digits )
{

    int fontwidth = ((signed short) (num[0]->width));
    int neg;
    int temp;

    if (digits < 0)
    {
 if (!n)
 {

     digits = 1;
 }
 else
 {

     digits = 0;
     temp = n;

     while (temp)
     {
  temp /= 10;
  digits++;
     }
 }
    }

    neg = n < 0;
    if (neg)
 n = -n;


    if (n == 1994)
 return 0;


    while (digits--)
    {
 x -= fontwidth;
 V_DrawPatch(x, y, num[ n % 10 ]);
 n /= 10;
    }


    if (neg)
 V_DrawPatch(x-=8, y, wiminus);

    return x;

}

void
WI_drawPercent
( int x,
  int y,
  int p )
{
    if (p < 0)
 return;

    V_DrawPatch(x, y, percent);
    WI_drawNum(x, y, p, -1);
}







void
WI_drawTime
( int x,
  int y,
  int t )
{

    int div;
    int n;

    if (t<0)
 return;

    if (t <= 61*59)
    {
 div = 1;

 do
 {
     n = (t / div) % 60;
     x = WI_drawNum(x, y, n, 2) - ((signed short) (colon->width));
     div *= 60;


     if (div==60 || t / div)
  V_DrawPatch(x, y, colon);

 } while (t / div);
    }
    else
    {

 V_DrawPatch(x - ((signed short) (sucks->width)), y, sucks);
    }
}


void WI_End(void)
{
    void WI_unloadData(void);
    WI_unloadData();
}

void WI_initNoState(void)
{
    state = NoState;
    acceleratestage = 0;
    cnt = 10;
}

void WI_updateNoState(void) {

    WI_updateAnimatedBack();

    if (!--cnt)
    {





 G_WorldDone();
    }

}

static boolean snl_pointeron = false;


void WI_initShowNextLoc(void)
{
    state = ShowNextLoc;
    acceleratestage = 0;
    cnt = 4 * 35;

    WI_initAnimatedBack();
}

void WI_updateShowNextLoc(void)
{
    WI_updateAnimatedBack();

    if (!--cnt || acceleratestage)
 WI_initNoState();
    else
 snl_pointeron = (cnt & 31) < 20;
}

void WI_drawShowNextLoc(void)
{

    int i;
    int last;

    WI_slamBackground();


    WI_drawAnimatedBack();

    if ( gamemode != commercial)
    {
   if (wbs->epsd > 2)
 {
     WI_drawEL();
     return;
 }

 last = (wbs->last == 8) ? wbs->next - 1 : wbs->last;


 for (i=0 ; i<=last ; i++)
     WI_drawOnLnode(i, splat);


 if (wbs->didsecret)
     WI_drawOnLnode(8, splat);


 if (snl_pointeron)
     WI_drawOnLnode(wbs->next, yah);
    }


    if ( (gamemode != commercial)
  || wbs->next != 30)
 WI_drawEL();

}

void WI_drawNoState(void)
{
    snl_pointeron = true;
    WI_drawShowNextLoc();
}

int WI_fragSum(int playernum)
{
    int i;
    int frags = 0;

    for (i=0 ; i<4 ; i++)
    {
 if (playeringame[i]
     && i!=playernum)
 {
     frags += plrs[playernum].frags[i];
 }
    }



    frags -= plrs[playernum].frags[playernum];



    return frags;
}



static int dm_state;
static int dm_frags[4][4];
static int dm_totals[4];



void WI_initDeathmatchStats(void)
{

    int i;
    int j;

    state = StatCount;
    acceleratestage = 0;
    dm_state = 1;

    cnt_pause = 35;

    for (i=0 ; i<4 ; i++)
    {
 if (playeringame[i])
 {
     for (j=0 ; j<4 ; j++)
  if (playeringame[j])
      dm_frags[i][j] = 0;

     dm_totals[i] = 0;
 }
    }

    WI_initAnimatedBack();
}



void WI_updateDeathmatchStats(void)
{

    int i;
    int j;

    boolean stillticking;

    WI_updateAnimatedBack();

    if (acceleratestage && dm_state != 4)
    {
 acceleratestage = 0;

 for (i=0 ; i<4 ; i++)
 {
     if (playeringame[i])
     {
  for (j=0 ; j<4 ; j++)
      if (playeringame[j])
   dm_frags[i][j] = plrs[i].frags[j];

  dm_totals[i] = WI_fragSum(i);
     }
 }


 S_StartSound(0, sfx_barexp);
 dm_state = 4;
    }


    if (dm_state == 2)
    {
 if (!(bcnt&3))
     S_StartSound(0, sfx_pistol);

 stillticking = false;

 for (i=0 ; i<4 ; i++)
 {
     if (playeringame[i])
     {
  for (j=0 ; j<4 ; j++)
  {
      if (playeringame[j]
   && dm_frags[i][j] != plrs[i].frags[j])
      {
   if (plrs[i].frags[j] < 0)
       dm_frags[i][j]--;
   else
       dm_frags[i][j]++;

   if (dm_frags[i][j] > 99)
       dm_frags[i][j] = 99;

   if (dm_frags[i][j] < -99)
       dm_frags[i][j] = -99;

   stillticking = true;
      }
  }
  dm_totals[i] = WI_fragSum(i);

  if (dm_totals[i] > 99)
      dm_totals[i] = 99;

  if (dm_totals[i] < -99)
      dm_totals[i] = -99;
     }

 }
 if (!stillticking)
 {
     S_StartSound(0, sfx_barexp);
     dm_state++;
 }

    }
    else if (dm_state == 4)
    {
 if (acceleratestage)
 {
     S_StartSound(0, sfx_slop);

     if ( gamemode == commercial)
  WI_initNoState();
     else
  WI_initShowNextLoc();
 }
    }
    else if (dm_state & 1)
    {
 if (!--cnt_pause)
 {
     dm_state++;
     cnt_pause = 35;
 }
    }
}



void WI_drawDeathmatchStats(void)
{

    int i;
    int j;
    int x;
    int y;
    int w;

    WI_slamBackground();


    WI_drawAnimatedBack();
    WI_drawLF();


    V_DrawPatch(269 -((signed short) (total->width))/2,
  68 -33 +10,
  total);

    V_DrawPatch(10, 100, killers);
    V_DrawPatch(5, 50, victims);


    x = 42 + 40;
    y = 68;

    for (i=0 ; i<4 ; i++)
    {
 if (playeringame[i])
 {
     V_DrawPatch(x-((signed short) (p[i]->width))/2,
   68 - 33,
   p[i]);

     V_DrawPatch(42 -((signed short) (p[i]->width))/2,
   y,
   p[i]);

     if (i == me)
     {
  V_DrawPatch(x-((signed short) (p[i]->width))/2,
       68 - 33,
       bstar);

  V_DrawPatch(42 -((signed short) (p[i]->width))/2,
       y,
       star);
     }
 }
 else
 {




 }
 x += 40;
 y += 33;
    }


    y = 68 +10;
    w = ((signed short) (num[0]->width));

    for (i=0 ; i<4 ; i++)
    {
 x = 42 + 40;

 if (playeringame[i])
 {
     for (j=0 ; j<4 ; j++)
     {
  if (playeringame[j])
      WI_drawNum(x+w, y, dm_frags[i][j], 2);

  x += 40;
     }
     WI_drawNum(269 +w, y, dm_totals[i], 2);
 }
 y += 33;
    }
}

static int cnt_frags[4];
static int dofrags;
static int ng_state;

void WI_initNetgameStats(void)
{

    int i;

    state = StatCount;
    acceleratestage = 0;
    ng_state = 1;

    cnt_pause = 35;

    for (i=0 ; i<4 ; i++)
    {
 if (!playeringame[i])
     continue;

 cnt_kills[i] = cnt_items[i] = cnt_secret[i] = cnt_frags[i] = 0;

 dofrags += WI_fragSum(i);
    }

    dofrags = !!dofrags;

    WI_initAnimatedBack();
}



void WI_updateNetgameStats(void)
{

    int i;
    int fsum;

    boolean stillticking;

    WI_updateAnimatedBack();

    if (acceleratestage && ng_state != 10)
    {
 acceleratestage = 0;

 for (i=0 ; i<4 ; i++)
 {
     if (!playeringame[i])
  continue;

     cnt_kills[i] = (plrs[i].skills * 100) / wbs->maxkills;
     cnt_items[i] = (plrs[i].sitems * 100) / wbs->maxitems;
     cnt_secret[i] = (plrs[i].ssecret * 100) / wbs->maxsecret;

     if (dofrags)
  cnt_frags[i] = WI_fragSum(i);
 }
 S_StartSound(0, sfx_barexp);
 ng_state = 10;
    }

    if (ng_state == 2)
    {
 if (!(bcnt&3))
     S_StartSound(0, sfx_pistol);

 stillticking = false;

 for (i=0 ; i<4 ; i++)
 {
     if (!playeringame[i])
  continue;

     cnt_kills[i] += 2;

     if (cnt_kills[i] >= (plrs[i].skills * 100) / wbs->maxkills)
  cnt_kills[i] = (plrs[i].skills * 100) / wbs->maxkills;
     else
  stillticking = true;
 }

 if (!stillticking)
 {
     S_StartSound(0, sfx_barexp);
     ng_state++;
 }
    }
    else if (ng_state == 4)
    {
 if (!(bcnt&3))
     S_StartSound(0, sfx_pistol);

 stillticking = false;

 for (i=0 ; i<4 ; i++)
 {
     if (!playeringame[i])
  continue;

     cnt_items[i] += 2;
     if (cnt_items[i] >= (plrs[i].sitems * 100) / wbs->maxitems)
  cnt_items[i] = (plrs[i].sitems * 100) / wbs->maxitems;
     else
  stillticking = true;
 }
 if (!stillticking)
 {
     S_StartSound(0, sfx_barexp);
     ng_state++;
 }
    }
    else if (ng_state == 6)
    {
 if (!(bcnt&3))
     S_StartSound(0, sfx_pistol);

 stillticking = false;

 for (i=0 ; i<4 ; i++)
 {
     if (!playeringame[i])
  continue;

     cnt_secret[i] += 2;

     if (cnt_secret[i] >= (plrs[i].ssecret * 100) / wbs->maxsecret)
  cnt_secret[i] = (plrs[i].ssecret * 100) / wbs->maxsecret;
     else
  stillticking = true;
 }

 if (!stillticking)
 {
     S_StartSound(0, sfx_barexp);
     ng_state += 1 + 2*!dofrags;
 }
    }
    else if (ng_state == 8)
    {
 if (!(bcnt&3))
     S_StartSound(0, sfx_pistol);

 stillticking = false;

 for (i=0 ; i<4 ; i++)
 {
     if (!playeringame[i])
  continue;

     cnt_frags[i] += 1;

     if (cnt_frags[i] >= (fsum = WI_fragSum(i)))
  cnt_frags[i] = fsum;
     else
  stillticking = true;
 }

 if (!stillticking)
 {
     S_StartSound(0, sfx_pldeth);
     ng_state++;
 }
    }
    else if (ng_state == 10)
    {
 if (acceleratestage)
 {
     S_StartSound(0, sfx_sgcock);
     if ( gamemode == commercial )
  WI_initNoState();
     else
  WI_initShowNextLoc();
 }
    }
    else if (ng_state & 1)
    {
 if (!--cnt_pause)
 {
     ng_state++;
     cnt_pause = 35;
 }
    }
}



void WI_drawNetgameStats(void)
{
    int i;
    int x;
    int y;
    int pwidth = ((signed short) (percent->width));

    WI_slamBackground();


    WI_drawAnimatedBack();

    WI_drawLF();


    V_DrawPatch((32 + ((signed short) (star->width))/2 + 32*!dofrags)+64 -((signed short) (kills->width)),
  50, kills);

    V_DrawPatch((32 + ((signed short) (star->width))/2 + 32*!dofrags)+2*64 -((signed short) (items->width)),
  50, items);

    V_DrawPatch((32 + ((signed short) (star->width))/2 + 32*!dofrags)+3*64 -((signed short) (secret->width)),
  50, secret);

    if (dofrags)
 V_DrawPatch((32 + ((signed short) (star->width))/2 + 32*!dofrags)+4*64 -((signed short) (frags->width)),
      50, frags);


    y = 50 + ((signed short) (kills->height));

    for (i=0 ; i<4 ; i++)
    {
 if (!playeringame[i])
     continue;

 x = (32 + ((signed short) (star->width))/2 + 32*!dofrags);
 V_DrawPatch(x-((signed short) (p[i]->width)), y, p[i]);

 if (i == me)
     V_DrawPatch(x-((signed short) (p[i]->width)), y, star);

 x += 64;
 WI_drawPercent(x-pwidth, y+10, cnt_kills[i]); x += 64;
 WI_drawPercent(x-pwidth, y+10, cnt_items[i]); x += 64;
 WI_drawPercent(x-pwidth, y+10, cnt_secret[i]); x += 64;

 if (dofrags)
     WI_drawNum(x, y+10, cnt_frags[i], -1);

 y += 33;
    }

}

static int sp_state;

void WI_initStats(void)
{
    state = StatCount;
    acceleratestage = 0;
    sp_state = 1;
    cnt_kills[0] = cnt_items[0] = cnt_secret[0] = -1;
    cnt_time = cnt_par = -1;
    cnt_pause = 35;

    WI_initAnimatedBack();
}

void WI_updateStats(void)
{

    WI_updateAnimatedBack();

    if (acceleratestage && sp_state != 10)
    {
 acceleratestage = 0;
 cnt_kills[0] = (plrs[me].skills * 100) / wbs->maxkills;
 cnt_items[0] = (plrs[me].sitems * 100) / wbs->maxitems;
 cnt_secret[0] = (plrs[me].ssecret * 100) / wbs->maxsecret;
 cnt_time = plrs[me].stime / 35;
 cnt_par = wbs->partime / 35;
 S_StartSound(0, sfx_barexp);
 sp_state = 10;
    }

    if (sp_state == 2)
    {
 cnt_kills[0] += 2;

 if (!(bcnt&3))
     S_StartSound(0, sfx_pistol);

 if (cnt_kills[0] >= (plrs[me].skills * 100) / wbs->maxkills)
 {
     cnt_kills[0] = (plrs[me].skills * 100) / wbs->maxkills;
     S_StartSound(0, sfx_barexp);
     sp_state++;
 }
    }
    else if (sp_state == 4)
    {
 cnt_items[0] += 2;

 if (!(bcnt&3))
     S_StartSound(0, sfx_pistol);

 if (cnt_items[0] >= (plrs[me].sitems * 100) / wbs->maxitems)
 {
     cnt_items[0] = (plrs[me].sitems * 100) / wbs->maxitems;
     S_StartSound(0, sfx_barexp);
     sp_state++;
 }
    }
    else if (sp_state == 6)
    {
 cnt_secret[0] += 2;

 if (!(bcnt&3))
     S_StartSound(0, sfx_pistol);

 if (cnt_secret[0] >= (plrs[me].ssecret * 100) / wbs->maxsecret)
 {
     cnt_secret[0] = (plrs[me].ssecret * 100) / wbs->maxsecret;
     S_StartSound(0, sfx_barexp);
     sp_state++;
 }
    }

    else if (sp_state == 8)
    {
 if (!(bcnt&3))
     S_StartSound(0, sfx_pistol);

 cnt_time += 3;

 if (cnt_time >= plrs[me].stime / 35)
     cnt_time = plrs[me].stime / 35;

 cnt_par += 3;

 if (cnt_par >= wbs->partime / 35)
 {
     cnt_par = wbs->partime / 35;

     if (cnt_time >= plrs[me].stime / 35)
     {
  S_StartSound(0, sfx_barexp);
  sp_state++;
     }
 }
    }
    else if (sp_state == 10)
    {
 if (acceleratestage)
 {
     S_StartSound(0, sfx_sgcock);

     if (gamemode == commercial)
  WI_initNoState();
     else
  WI_initShowNextLoc();
 }
    }
    else if (sp_state & 1)
    {
 if (!--cnt_pause)
 {
     sp_state++;
     cnt_pause = 35;
 }
    }

}

void WI_drawStats(void)
{

    int lh;

    lh = (3*((signed short) (num[0]->height)))/2;

    WI_slamBackground();


    WI_drawAnimatedBack();

    WI_drawLF();

    V_DrawPatch(50, 50, kills);
    WI_drawPercent(320 - 50, 50, cnt_kills[0]);

    V_DrawPatch(50, 50 +lh, items);
    WI_drawPercent(320 - 50, 50 +lh, cnt_items[0]);

    V_DrawPatch(50, 50 +2*lh, sp_secret);
    WI_drawPercent(320 - 50, 50 +2*lh, cnt_secret[0]);

    V_DrawPatch(16, (200 -32), timepatch);
    WI_drawTime(320/2 - 16, (200 -32), cnt_time);

    if (wbs->epsd < 3)
    {
 V_DrawPatch(320/2 + 16, (200 -32), par);
 WI_drawTime(320 - 16, (200 -32), cnt_par);
    }

}

void WI_checkForAccelerate(void)
{
    int i;
    player_t *player;


    for (i=0, player = players ; i<4 ; i++, player++)
    {
 if (playeringame[i])
 {
     if (player->cmd.buttons & BT_ATTACK)
     {
  if (!player->attackdown)
      acceleratestage = 1;
  player->attackdown = true;
     }
     else
  player->attackdown = false;
     if (player->cmd.buttons & BT_USE)
     {
  if (!player->usedown)
      acceleratestage = 1;
  player->usedown = true;
     }
     else
  player->usedown = false;
 }
    }
}




void WI_Ticker(void)
{

    bcnt++;

    if (bcnt == 1)
    {

   if ( gamemode == commercial )
   S_ChangeMusic(mus_dm2int, true);
 else
   S_ChangeMusic(mus_inter, true);
    }

    WI_checkForAccelerate();

    switch (state)
    {
      case StatCount:
 if (deathmatch) WI_updateDeathmatchStats();
 else if (netgame) WI_updateNetgameStats();
 else WI_updateStats();
 break;

      case ShowNextLoc:
 WI_updateShowNextLoc();
 break;

      case NoState:
 WI_updateNoState();
 break;
    }

}

typedef void (*load_callback_t)(char *lumpname, patch_t **variable);




static void WI_loadUnloadData(load_callback_t callback)
{
    int i, j;
    char name[9];
    wi_anim_t *a;

    if (gamemode == commercial)
    {
 for (i=0 ; i<NUMCMAPS ; i++)
 {
     snprintf(name, 9, "CWILV%2.2d", i);
            callback(name, &lnames[i]);
 }
    }
    else
    {
 for (i=0 ; i<9 ; i++)
 {
     snprintf(name, 9, "WILV%d%d", wbs->epsd, i);
            callback(name, &lnames[i]);
 }


        callback(("WIURH0"), &yah[0]);


        callback(("WIURH1"), &yah[1]);


        callback(("WISPLAT"), &splat[0]);

 if (wbs->epsd < 3)
 {
     for (j=0;j<NUMANIMS[wbs->epsd];j++)
     {
  a = &wi_anims[wbs->epsd][j];
  for (i=0;i<a->nanims;i++)
  {

      if (wbs->epsd != 1 || j != 8)
      {

   snprintf(name, 9, "WIA%d%.2d%.2d", wbs->epsd, j, i);
                        callback(name, &a->p[i]);
      }
      else
      {

   a->p[i] = wi_anims[1][4].p[i];
      }
  }
     }
 }
    }


    callback(("WIMINUS"), &wiminus);

    for (i=0;i<10;i++)
    {

 snprintf(name, 9, "WINUM%d", i);
        callback(name, &num[i]);
    }


    callback(("WIPCNT"), &percent);


    callback(("WIF"), &finished);


    callback(("WIENTER"), &entering);


    callback(("WIOSTK"), &kills);


    callback(("WIOSTS"), &secret);


    callback(("WISCRT2"), &sp_secret);


    if (W_CheckNumForName(("WIOBJ")) >= 0)
    {

     if (netgame && !deathmatch)
            callback(("WIOBJ"), &items);
     else
            callback(("WIOSTI"), &items);
    } else {
        callback(("WIOSTI"), &items);
    }


    callback(("WIFRGS"), &frags);


    callback(("WICOLON"), &colon);


    callback(("WITIME"), &timepatch);


    callback(("WISUCKS"), &sucks);


    callback(("WIPAR"), &par);


    callback(("WIKILRS"), &killers);


    callback(("WIVCTMS"), &victims);


    callback(("WIMSTT"), &total);

    for (i=0 ; i<4 ; i++)
    {

 snprintf(name, 9, "STPB%d", i);
        callback(name, &p[i]);


 snprintf(name, 9, "WIBP%d", i+1);
        callback(name, &bp[i]);
    }



    if (gamemode == commercial)
    {
        M_StringCopy(name, ("INTERPIC"), sizeof(name));
    }
    else if (gamemode == retail && wbs->epsd == 3)
    {
        M_StringCopy(name, ("INTERPIC"), sizeof(name));
    }
    else
    {
 snprintf(name, sizeof(name), "WIMAP%d", wbs->epsd);
    }



    callback(name, &background);
}

static void WI_loadCallback(char *name, patch_t **variable)
{
    *variable = W_CacheLumpName(name, PU_STATIC);
}

void WI_loadData(void)
{
    if (gamemode == commercial)
    {
 NUMCMAPS = 32;
 lnames = (patch_t **) Z_Malloc(sizeof(patch_t*) * NUMCMAPS,
           PU_STATIC, ((void*)0));
    }
    else
    {
 lnames = (patch_t **) Z_Malloc(sizeof(patch_t*) * 9,
           PU_STATIC, ((void*)0));
    }

    WI_loadUnloadData(WI_loadCallback);





    star = W_CacheLumpName(("STFST01"), PU_STATIC);


    bstar = W_CacheLumpName(("STFDEAD0"), PU_STATIC);
}

static void WI_unloadCallback(char *name, patch_t **variable)
{
    W_ReleaseLumpName(name);
    *variable = ((void*)0);
}

void WI_unloadData(void)
{
    WI_loadUnloadData(WI_unloadCallback);






}

void WI_Drawer (void)
{
    switch (state)
    {
      case StatCount:
 if (deathmatch)
     WI_drawDeathmatchStats();
 else if (netgame)
     WI_drawNetgameStats();
 else
     WI_drawStats();
 break;

      case ShowNextLoc:
 WI_drawShowNextLoc();
 break;

      case NoState:
 WI_drawNoState();
 break;
    }
}


void WI_initVariables(wbstartstruct_t* wbstartstruct)
{

    wbs = wbstartstruct;
    acceleratestage = 0;
    cnt = bcnt = 0;
    firstrefresh = 1;
    me = wbs->pnum;
    plrs = wbs->plyr;

    if (!wbs->maxkills)
 wbs->maxkills = 1;

    if (!wbs->maxitems)
 wbs->maxitems = 1;

    if (!wbs->maxsecret)
 wbs->maxsecret = 1;

    if ( gamemode != retail )
      if (wbs->epsd > 2)
 wbs->epsd -= 3;
}

void WI_Start(wbstartstruct_t* wbstartstruct)
{
    WI_initVariables(wbstartstruct);
    WI_loadData();

    if (deathmatch)
 WI_initDeathmatchStats();
    else if (netgame)
 WI_initNetgameStats();
    else
 WI_initStats();
}
static wad_file_t **open_wadfiles = ((void*)0);
static int num_open_wadfiles = 0;
FILE *g_wad_fstream;

static int GetFileNumber(wad_file_t *handle)
{
    int i;
    int result;

    for (i=0; i<num_open_wadfiles; ++i)
    {
        if (open_wadfiles[i] == handle)
        {
            return i;
        }
    }




    open_wadfiles = realloc(open_wadfiles,
                            sizeof(wad_file_t *) * (num_open_wadfiles + 1));
    open_wadfiles[num_open_wadfiles] = handle;

    result = num_open_wadfiles;
    ++num_open_wadfiles;

    return result;
}

static void ChecksumAddLump(sha1_context_t *sha1_context, lumpinfo_t *lump)
{
    char buf[9];

    M_StringCopy(buf, lump->name, sizeof(buf));
    SHA1_UpdateString(sha1_context, buf);
    SHA1_UpdateInt32(sha1_context, GetFileNumber(lump->wad_file));
    SHA1_UpdateInt32(sha1_context, lump->position);
    SHA1_UpdateInt32(sha1_context, lump->size);
}

void W_Checksum(sha1_digest_t digest)
{
    /* Stub: skip SHA1 checksum */
    int wc_i;
    for (wc_i = 0; wc_i < 20; wc_i++) digest[wc_i] = 0;
}
void W_MergeFile(char *filename);



void W_NWTMergeFile(char *filename, int flags);



void W_NWTDashMerge(char *filename);



void W_PrintDirectory(void);






boolean W_ParseCommandLine(void)
{
    boolean modifiedgame = false;
    int p;
    p = M_CheckParmWithArgs ("-file", 1);
    if (p)
    {


 modifiedgame = true;
 while (++p != myargc && myargv[p][0] != '-')
        {
            char *filename;

            filename = D_TryFindWADByName(myargv[p]);

            printf(" adding %s\n", filename);
     W_AddFile(filename);
        }
    }



    return modifiedgame;
}
typedef struct
{

    char identification[4];
    int numlumps;
    int infotableofs;
} __attribute__((packed)) wadinfo_t;


typedef struct
{
    int filepos;
    int size;
    char name[8];
} __attribute__((packed)) filelump_t;







lumpinfo_t *lumpinfo;
unsigned int numlumps = 0;



static lumpinfo_t **lumphash;



unsigned int W_LumpNameHash(const char *s)
{



    unsigned int result = 5381;
    unsigned int i;

    for (i=0; i < 8 && s[i] != '\0'; ++i)
    {
        result = ((result << 5) ^ result ) ^ toupper((int)s[i]);
    }

    return result;
}


static void ExtendLumpInfo(int newnumlumps)
{
    lumpinfo_t *newlumpinfo;
    unsigned int i;

    newlumpinfo = calloc(newnumlumps, 48);

    if (newlumpinfo == ((void*)0))
    {
 I_Error ("Couldn't realloc lumpinfo");
    }




    for (i = 0; i < numlumps && i < newnumlumps; ++i)
    {
        memcpy(&newlumpinfo[i], &lumpinfo[i], 48);

        if (newlumpinfo[i].cache != ((void*)0))
        {
            Z_ChangeUser(newlumpinfo[i].cache, &newlumpinfo[i].cache);
        }



        if (lumpinfo[i].next != ((void*)0))
        {
            int nextlumpnum = lumpinfo[i].next - lumpinfo;
            newlumpinfo[i].next = &newlumpinfo[nextlumpnum];
        }
    }


    free(lumpinfo);
    lumpinfo = newlumpinfo;
    numlumps = newnumlumps;
}
/* Helper: read a little-endian int32 from a byte buffer */
static int wad_read_i32(char *buf, int offset) {
    int b0 = buf[offset] & 0xff;
    int b1 = buf[offset+1] & 0xff;
    int b2 = buf[offset+2] & 0xff;
    int b3 = buf[offset+3] & 0xff;
    return b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
}

wad_file_t *W_AddFile (char *filename)
{
    lumpinfo_t *lump_p;
    unsigned int i;
    wad_file_t *wad_file;
    int startlump;
    int newnumlumps;
    int hdr_numlumps;
    int hdr_infotableofs;
    char *raw_dir;
    char *hdr_buf;
    char *tmpname;
    int flen;
    int dir_len;
    int entry_idx;
    int entry_off;
    int ni;

    wad_file = W_OpenFile(filename);

    if (wad_file == ((void*)0))
    {
  printf (" couldn't open %s\n", filename);
  return ((void*)0);
    }

    newnumlumps = numlumps;
    hdr_numlumps = 0;
    hdr_infotableofs = 0;
    raw_dir = ((void*)0);

    if (strcasecmp(filename+strlen(filename)-3 , "wad" ) )
    {
  hdr_numlumps = 1;
  raw_dir = Z_Malloc(16, PU_STATIC, 0);
  raw_dir[0] = 0; raw_dir[1] = 0; raw_dir[2] = 0; raw_dir[3] = 0;
  flen = wad_file->length;
  raw_dir[4] = flen & 0xff;
  raw_dir[5] = (flen >> 8) & 0xff;
  raw_dir[6] = (flen >> 16) & 0xff;
  raw_dir[7] = (flen >> 24) & 0xff;
  tmpname = Z_Malloc(16, PU_STATIC, 0);
  M_ExtractFileBase(filename, tmpname);
  for (ni = 0; ni < 8; ni++) raw_dir[8+ni] = tmpname[ni];
  Z_Free(tmpname);
  newnumlumps++;
    }
    else
    {
  hdr_buf = malloc(16);
  memset(hdr_buf, 0, 16);
  W_Read(wad_file, 0, hdr_buf, 12);

  if (strncmp(hdr_buf, "IWAD", 4))
  {
   if (strncmp(hdr_buf, "PWAD", 4))
   {
   I_Error ("Wad file %s doesn't have IWAD "
     "or PWAD id\n", filename);
   }
  }

  hdr_numlumps = wad_read_i32(hdr_buf, 4);
  hdr_infotableofs = wad_read_i32(hdr_buf, 8);
  free(hdr_buf);

  dir_len = hdr_numlumps * 16;
  raw_dir = Z_Malloc(dir_len, PU_STATIC, 0);
  W_Read(wad_file, hdr_infotableofs, raw_dir, dir_len);
  newnumlumps += hdr_numlumps;
    }

    startlump = numlumps;
    ExtendLumpInfo(newnumlumps);

    for (i=startlump; i<numlumps; ++i)
    {
  lump_p = &lumpinfo[i];
  entry_idx = i - startlump;
  entry_off = entry_idx * 16;
  lump_p->wad_file = wad_file;
  lump_p->position = wad_read_i32(raw_dir, entry_off + 0);
  lump_p->size = wad_read_i32(raw_dir, entry_off + 4);
  lump_p->cache = ((void*)0);
  if (lump_p->name == ((void*)0))
      memset(lump_p->name, 0, 8);
  strncpy(lump_p->name, raw_dir + entry_off + 8, 8);
  lump_p->name[8] = 0;
    }

    Z_Free(raw_dir);

    if (lumphash != ((void*)0))
    {
        Z_Free(lumphash);
        lumphash = ((void*)0);
    }

    return wad_file;
}






int W_NumLumps (void)
{
    return numlumps;
}
int W_CheckNumForName (char* wname)
{
    lumpinfo_t *lump_p;
    int i;

    if (lumphash != ((void*)0))
    {
        int hash;

        hash = W_LumpNameHash(wname) % numlumps;

        for (lump_p = lumphash[hash]; lump_p != ((void*)0); lump_p = lump_p->next)
        {
            if (!strncasecmp(lump_p->name, wname, 8))
            {
                return lump_p - lumpinfo;
            }
        }
    }
    else
    {
        for (i=numlumps-1; i >= 0; --i)
        {
            if (!strncasecmp(lumpinfo[i].name, wname, 8))
            {
                return i;
            }
        }
    }

    return -1;
}
int W_GetNumForName (char* wname)
{
    int i;

    i = W_CheckNumForName (wname);

    if (i < 0)
    {
        I_Error ("W_GetNumForName: %s not found!", wname);
    }

    return i;
}






int W_LumpLength (unsigned int lump)
{
    if (lump >= numlumps)
    {
 I_Error ("W_LumpLength: %i >= numlumps", lump);
    }

    return lumpinfo[lump].size;
}
size_t W_StdC_Read(wad_file_t *wad, unsigned int offset, void *rdbuf, size_t rdbuf_len);
void W_ReadLump(unsigned int lump, void *rdest)
{
    int c;
    lumpinfo_t *l;

    if (lump >= numlumps)
    {
 I_Error ("W_ReadLump: %i >= numlumps", lump);
    }

    l = &lumpinfo[lump];

    I_BeginRead ();

    c = W_StdC_Read(l->wad_file, l->position, rdest, l->size);

    if (c < l->size)
    {
 I_Error ("W_ReadLump: only read %i of %i on lump %i",
   c, l->size, lump);
    }

    I_EndRead ();
}
void *W_CacheLumpNum(int lumpnum, int tag)
{
    byte *result;
    lumpinfo_t *lump;

    if ((unsigned)lumpnum >= numlumps)
    {
 I_Error ("W_CacheLumpNum: %i >= numlumps", lumpnum);
    }

    lump = &lumpinfo[lumpnum];

    if (lump->cache != ((void*)0))
    {
        result = lump->cache;
        Z_ChangeTag2((lump->cache), (tag), "../doomgeneric/w_wad.c", 410);
    }
    else
    {
        lump->cache = Z_Malloc(W_LumpLength(lumpnum), tag, &lump->cache);
 W_ReadLump (lumpnum, lump->cache);
        result = lump->cache;
    }

    return result;
}






void *W_CacheLumpName(char *wname, int tag)
{
    return W_CacheLumpNum(W_GetNumForName(wname), tag);
}
void W_ReleaseLumpNum(int lumpnum)
{
    lumpinfo_t *lump;

    if ((unsigned)lumpnum >= numlumps)
    {
 I_Error ("W_ReleaseLumpNum: %i >= numlumps", lumpnum);
    }

    lump = &lumpinfo[lumpnum];

    if (lump->wad_file->mapped != ((void*)0))
    {

    }
    else
    {
        Z_ChangeTag2((lump->cache), (PU_CACHE), "../doomgeneric/w_wad.c", 461);
    }
}

void W_ReleaseLumpName(char *wname)
{
    W_ReleaseLumpNum(W_GetNumForName(wname));
}
void W_GenerateHashTable(void)
{
    /* Stub: disable hash table - our compiler can't do struct pointer subtraction */
    /* Linear search in W_CheckNumForName will be used instead */
}




static const struct
{
    GameMission_t mission;
    char *lumpname;
} unique_lumps[] = {
    { doom, "POSSA1" },
    { heretic, "IMPXA1" },
    { hexen, "ETTNA1" },
    { strife, "AGRDA1" },
};

void W_CheckCorrectIWAD(GameMission_t mission)
{
    int i;
    int lumpnum;

    for (i = 0; i < (sizeof(unique_lumps) / sizeof(*unique_lumps)); ++i)
    {
        if (mission != unique_lumps[i].mission)
        {
            lumpnum = W_CheckNumForName(unique_lumps[i].lumpname);

            if (lumpnum >= 0)
            {
                I_Error("\nYou are trying to use a %s IWAD file with "
                        "the %s%s binary.\nThis isn't going to work.\n"
                        "You probably want to use the %s%s binary.",
                        D_SuggestGameName(unique_lumps[i].mission,
                                          indetermined),
                        "doomgeneric",
                        D_GameMissionString(mission),
                        "doomgeneric",
                        D_GameMissionString(unique_lumps[i].mission));
            }
        }
    }
}
typedef struct memblock_s
{
    int size;
    void** user;
    int tag;
    int id;
    struct memblock_s* next;
    struct memblock_s* prev;
} memblock_t;


typedef struct
{

    int size;


    memblock_t blocklist;

    memblock_t* rover;

} memzone_t;



memzone_t* mainzone;






void Z_ClearZone (memzone_t* zone)
{
    memblock_t* block;


    zone->blocklist.next =
 zone->blocklist.prev =
 block = (memblock_t *)( (byte *)zone + 56 );

    zone->blocklist.user = (void *)zone;
    zone->blocklist.tag = PU_STATIC;
    zone->rover = block;

    block->prev = block->next = &zone->blocklist;


    block->tag = PU_FREE;

    block->size = zone->size - 56;
}






void Z_Init (void)
{
    memblock_t* block;
    int size;

    mainzone = (memzone_t *)I_ZoneBase (&size);
    mainzone->size = size;


    mainzone->blocklist.next =
 mainzone->blocklist.prev =
 block = (memblock_t *)( (byte *)mainzone + 56 );

    mainzone->blocklist.user = (void *)mainzone;
    mainzone->blocklist.tag = PU_STATIC;
    mainzone->rover = block;

    block->prev = block->next = &mainzone->blocklist;


    block->tag = PU_FREE;

    block->size = mainzone->size - 56;
}





void Z_Free (void* ptr)
{
    memblock_t* block;
    memblock_t* other;

    block = (memblock_t *) ( (byte *)ptr - 40);

    if (block->id != 0x1d4a11)
 I_Error ("Z_Free: freed a pointer without ZONEID");

    if (block->tag != PU_FREE && block->user != ((void*)0))
    {

     *block->user = 0;
    }


    block->tag = PU_FREE;
    block->user = ((void*)0);
    block->id = 0;

    other = block->prev;

    if (other->tag == PU_FREE)
    {

        other->size += block->size;
        other->next = block->next;
        other->next->prev = other;

        if (block == mainzone->rover)
            mainzone->rover = other;

        block = other;
    }

    other = block->next;
    if (other->tag == PU_FREE)
    {

        block->size += other->size;
        block->next = other->next;
        block->next->prev = block;

        if (other == mainzone->rover)
            mainzone->rover = block;
    }
}
int zmalloc_count = 0;
void*
Z_Malloc
( int size,
  int tag,
  void* user )
{
    int extra;
    memblock_t* start;
    memblock_t* rover;
    memblock_t* newblock;
    memblock_t* base;
    void *result;

    zmalloc_count = zmalloc_count + 1;
    if (zmalloc_count <= 10) printf("ZM#%d sz=%d tag=%d\n", zmalloc_count, size, tag);
    size = (size + sizeof(void *) - 1) & ~(sizeof(void *) - 1);







    size += 40;



    base = mainzone->rover;

    if (base->prev->tag == PU_FREE)
        base = base->prev;

    rover = base;
    start = base->prev;

    do
    {
        if (zmalloc_count <= 5) printf("  loop: rover=%p tag=%d sz=%d base=%p btag=%d bsz=%d\n",
            rover, rover->tag, rover->size, base, base->tag, base->size);
        if (rover == start)
        {

            I_Error ("Z_Malloc: failed on allocation of %i bytes (alloc_count=%i)", size, zmalloc_count);
        }

        if (rover->tag != PU_FREE)
        {
            if (rover->tag < PU_PURGELEVEL)
            {


                base = rover = rover->next;
            }
            else
            {



                base = base->prev;
                Z_Free ((byte *)rover+48);
                base = base->next;
                rover = base->next;
            }
        }
        else
        {
            rover = rover->next;
        }

    } while (base->tag != PU_FREE || base->size < size);



    extra = base->size - size;

    if (extra > 40)
    {

        newblock = (memblock_t *) ((byte *)base + size );
        newblock->size = extra;

        newblock->tag = PU_FREE;
        newblock->user = ((void*)0);
        newblock->prev = base;
        newblock->next = base->next;
        newblock->next->prev = newblock;

        base->next = newblock;
        base->size = size;
    }

 if (user == ((void*)0) && tag >= PU_PURGELEVEL)
     I_Error ("Z_Malloc: an owner is required for purgable blocks");

    base->user = user;
    base->tag = tag;

    result = (void *) ((byte *)base + 40);

    if (base->user)
    {
        *base->user = result;
    }


    mainzone->rover = base->next;

    base->id = 0x1d4a11;

    if (zmalloc_count <= 5) printf("  done: base=%p bsz=%d btag=%d rover=%p\n",
        base, base->size, base->tag, mainzone->rover);

    return result;
}






void
Z_FreeTags
( int lowtag,
  int hightag )
{
    memblock_t* block;
    memblock_t* next;

    for (block = mainzone->blocklist.next ;
  block != &mainzone->blocklist ;
  block = next)
    {

 next = block->next;


 if (block->tag == PU_FREE)
     continue;

 if (block->tag >= lowtag && block->tag <= hightag)
     Z_Free ( (byte *)block+48);
    }
}







void
Z_DumpHeap
( int lowtag,
  int hightag )
{
    memblock_t* block;

    printf ("zone size: %i  location: %p\n",
     mainzone->size,mainzone);

    printf ("tag range: %i to %i\n",
     lowtag, hightag);

    for (block = mainzone->blocklist.next ; ; block = block->next)
    {
 if (block->tag >= lowtag && block->tag <= hightag)
     printf ("block:%p    size:%7i    user:%p    tag:%3i\n",
      block, block->size, block->user, block->tag);

 if (block->next == &mainzone->blocklist)
 {

     break;
 }

 if ( (byte *)block + block->size != (byte *)block->next)
     printf ("ERROR: block size does not touch the next block\n");

 if ( block->next->prev != block)
     printf ("ERROR: next block doesn't have proper back link\n");

 if (block->tag == PU_FREE && block->next->tag == PU_FREE)
     printf ("ERROR: two consecutive free blocks\n");
    }
}





void Z_FileDumpHeap (FILE* f)
{
    memblock_t* block;

    fprintf (f,"zone size: %i  location: %p\n",mainzone->size,mainzone);

    for (block = mainzone->blocklist.next ; ; block = block->next)
    {
 fprintf (f,"block:%p    size:%7i    user:%p    tag:%3i\n",
   block, block->size, block->user, block->tag);

 if (block->next == &mainzone->blocklist)
 {

     break;
 }

 if ( (byte *)block + block->size != (byte *)block->next)
     fprintf (f,"ERROR: block size does not touch the next block\n");

 if ( block->next->prev != block)
     fprintf (f,"ERROR: next block doesn't have proper back link\n");

 if (block->tag == PU_FREE && block->next->tag == PU_FREE)
     fprintf (f,"ERROR: two consecutive free blocks\n");
    }
}






void Z_CheckHeap (void)
{
    memblock_t* block;

    for (block = mainzone->blocklist.next ; ; block = block->next)
    {
 if (block->next == &mainzone->blocklist)
 {

     break;
 }

 if ( (byte *)block + block->size != (byte *)block->next)
     I_Error ("Z_CheckHeap: block size does not touch the next block\n");

 if ( block->next->prev != block)
     I_Error ("Z_CheckHeap: next block doesn't have proper back link\n");

 if (block->tag == PU_FREE && block->next->tag == PU_FREE)
     I_Error ("Z_CheckHeap: two consecutive free blocks\n");
    }
}







void Z_ChangeTag2(void *ptr, int tag, char *file, int line)
{
    memblock_t* block;

    block = (memblock_t *) ((byte *)ptr - 40);

    if (block->id != 0x1d4a11)
        I_Error("%s:%i: Z_ChangeTag: block without a ZONEID!",
                file, line);

    if (tag >= PU_PURGELEVEL && block->user == ((void*)0))
        I_Error("%s:%i: Z_ChangeTag: an owner is required "
                "for purgable blocks", file, line);

    block->tag = tag;
}

void Z_ChangeUser(void *ptr, void **user)
{
    memblock_t* block;

    block = (memblock_t *) ((byte *)ptr - 40);

    if (block->id != 0x1d4a11)
    {
        I_Error("Z_ChangeUser: Tried to change user for invalid block!");
    }

    block->user = user;
    *user = ptr;
}






int Z_FreeMemory (void)
{
    memblock_t* block;
    int free;

    free = 0;

    for (block = mainzone->blocklist.next ;
         block != &mainzone->blocklist;
         block = block->next)
    {
        if (block->tag == PU_FREE || block->tag >= PU_PURGELEVEL)
            free += block->size;
    }

    return free;
}

unsigned int Z_ZoneSize(void)
{
    return mainzone->size;
}






extern wad_file_class_t stdc_wad_file;
static wad_file_class_t *wad_file_classes[] =
{
    &stdc_wad_file,
};

wad_file_t *W_OpenFile(char *path)
{
    wad_file_t *result;
    int i;






    if (!M_CheckParm("-mmap"))
    {
        return stdc_wad_file.OpenFile(path);
    }



    result = ((void*)0);

    for (i = 0; i < (sizeof(wad_file_classes) / sizeof(*wad_file_classes)); ++i)
    {
        result = wad_file_classes[i]->OpenFile(path);

        if (result != ((void*)0))
        {
            break;
        }
    }

    return result;
}

void W_CloseFile(wad_file_t *wad)
{
    wad->file_class->CloseFile(wad);
}

size_t W_Read(wad_file_t *wad, unsigned int offset,
              void *rdbuf, size_t rdbuf_len)
{
    return wad->file_class->Read(wad, offset, rdbuf, rdbuf_len);
}
typedef struct
{
    wad_file_t wad;
    FILE *fstream;
} stdc_wad_file_t;

extern wad_file_class_t stdc_wad_file;

static wad_file_t *W_StdC_OpenFile(char *path)
{
    stdc_wad_file_t *result;
    FILE *fstream;

    fstream = fopen(path, "rb");

    if (fstream == ((void*)0))
    {
        return ((void*)0);
    }



    result = malloc(32);
    memset(result, 0, 32);
    result->wad.file_class = &stdc_wad_file;
    result->wad.mapped = ((void*)0);
    result->wad.length = M_FileLength(fstream);
    result->fstream = fstream;
    g_wad_fstream = fstream;

    return &result->wad;
}

static void W_StdC_CloseFile(wad_file_t *wad)
{
    stdc_wad_file_t *stdc_wad;

    stdc_wad = (stdc_wad_file_t *) wad;

    fclose(g_wad_fstream);
    Z_Free(stdc_wad);
}




size_t W_StdC_Read(wad_file_t *wad, unsigned int offset,
                   void *rdbuf, size_t rdbuf_len)
{
    size_t result;

    fseek(g_wad_fstream, offset, 0);

    result = fread(rdbuf, 1, rdbuf_len, g_wad_fstream);

    return result;
}


wad_file_class_t stdc_wad_file =
{
    W_StdC_OpenFile,
    W_StdC_CloseFile,
    W_StdC_Read,
};








void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch);
void I_ResetScaleTables(byte *palette);



extern screen_mode_t mode_scale_1x;
extern screen_mode_t mode_scale_2x;
extern screen_mode_t mode_scale_3x;
extern screen_mode_t mode_scale_4x;
extern screen_mode_t mode_scale_5x;



extern screen_mode_t mode_stretch_1x;
extern screen_mode_t mode_stretch_2x;
extern screen_mode_t mode_stretch_3x;
extern screen_mode_t mode_stretch_4x;
extern screen_mode_t mode_stretch_5x;



extern screen_mode_t mode_squash_1x;
extern screen_mode_t mode_squash_2x;
extern screen_mode_t mode_squash_3x;
extern screen_mode_t mode_squash_4x;
extern screen_mode_t mode_squash_5x;
int vanilla_keyboard_mapping = 1;



static int shiftdown = 0;


static const char at_to_doom[] =
{
               0x00,
               27,
               '1',
               '2',
               '3',
               '4',
               '5',
               '6',
               '7',
               '8',
               '9',
               '0',
               '-',
               '=',
               0x7f,
               9,
               'q',
               'w',
               'e',
               'r',
               't',
               'y',
               'u',
               'i',
               'o',
               'p',
               '[',
               ']',
               13,
               0xa3,
               'a',
               's',
               'd',
               'f',
               'g',
               'h',
               'j',
               'k',
               'l',
               ';',
               '\'',
               '`',
               (0x80+0x36),
               '\\',
               'z',
               'x',
               'c',
               'v',
               'b',
               'n',
               'm',
               ',',
               '.',
               '/',
               (0x80+0x36),
               '*',
               (0x80+0x38),
               0xa2,
               (0x80+0x3a),
               (0x80+0x3b),
               (0x80+0x3c),
               (0x80+0x3d),
               (0x80+0x3e),
               (0x80+0x3f),
               (0x80+0x40),
               (0x80+0x41),
               (0x80+0x42),
               (0x80+0x43),
               (0x80+0x44),
               (0x80+0x45),
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0xad,
               0x0,
               0xac,
               0xae,
               0x0,
               0xaf,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0x0,
               0xa3,
};



static const char shiftxform[] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
    21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    31, ' ', '!', '"', '#', '$', '%', '&',
    '"',
    '(', ')', '*', '+',
    '<',
    '_',
    '>',
    '?',
    ')',
    '!',
    '@',
    '#',
    '$',
    '%',
    '^',
    '&',
    '*',
    '(',
    ':',
    ':',
    '<',
    '+',
    '>', '?', '@',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '[',
    '!',
    ']',
    '"', '_',
    '\'',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '{', '|', '}', '~', 127
};


static unsigned char TranslateKey(unsigned char key)
{
 return key;
}



static unsigned char GetTypedChar(unsigned char key)
{
    key = TranslateKey(key);



    if (shiftdown > 0)
    {
        if (key >= 0 && key < (sizeof(shiftxform) / sizeof(*shiftxform)))
        {
            key = shiftxform[key];
        }
        else
        {
            key = 0;
        }
    }

    return key;
}

static void UpdateShiftStatus(int pressed, unsigned char key)
{
    int change;

    if (pressed) {
        change = 1;
    } else {
        change = -1;
    }

    if (key == (0x80+0x36)) {
        shiftdown += change;
    }
}


void I_GetEvent(void)
{
    event_t event;
    int pressed;
    unsigned char key;


 while (DG_GetKey(&pressed, &key))
    {
        UpdateShiftStatus(pressed, key);



        if (pressed)
        {


            event.type = ev_keydown;
            event.data1 = TranslateKey(key);
            event.data2 = GetTypedChar(key);

            if (event.data1 != 0)
            {
                D_PostEvent(&event);
            }
        }
        else
        {
            event.type = ev_keyup;
            event.data1 = TranslateKey(key);







            event.data2 = 0;

            if (event.data1 != 0)
            {
                D_PostEvent(&event);
            }
            break;
        }
    }
}

void I_InitInput(void)
{
}
static const char
rcsid[] = "$Id: i_x.c,v 0 1997/02/03 22:45:10 b1 Exp $";

struct FB_BitField
{
 uint32_t offset;
 uint32_t length;
};

struct FB_ScreenInfo
{
 uint32_t xres;
 uint32_t yres;
 uint32_t xres_virtual;
 uint32_t yres_virtual;

 uint32_t bits_per_pixel;


 struct FB_BitField red;
 struct FB_BitField green;
 struct FB_BitField blue;
 struct FB_BitField transp;
};

static struct FB_ScreenInfo s_Fb;
int fb_scaling = 1;
int usemouse = 0;
static struct color colors[256];





void I_GetEvent(void);



byte *I_VideoBuffer = ((void*)0);



boolean screensaver_mode = false;




boolean screenvisible;
float mouse_acceleration = 0;
int mouse_threshold = 10;



int usegamma = 0;

typedef struct
{
 byte r;
 byte g;
 byte b;
} col_t;



static uint16_t rgb565_palette[256];

void cmap_to_rgb565(uint16_t * out, uint8_t * in, int in_pixels)
{
    int i, j;
    struct color c;
    uint16_t r, g, b;

    for (i = 0; i < in_pixels; i++)
    {
        c = colors[*in];
        r = ((uint16_t)(c.r >> 3)) << 11;
        g = ((uint16_t)(c.g >> 2)) << 5;
        b = ((uint16_t)(c.b >> 3)) << 0;
        *out = (r | g | b);

        in++;
        for (j = 0; j < fb_scaling; j++) {
            out++;
        }
    }
}

void cmap_to_fb(uint8_t *out, uint8_t *in, int in_pixels)
{
    int i, k;
    struct color c;
    uint32_t pix;

    for (i = 0; i < in_pixels; i++)
    {
        c = colors[*in];

        if (s_Fb.bits_per_pixel == 16)
        {

            uint16_t p = ((c.r & 0xF8) << 8) |
                         ((c.g & 0xFC) << 3) |
                         (c.b >> 3);




            for (k = 0; k < fb_scaling; k++) {
                *(uint16_t *)out = p;
                out += 2;
            }
        }
        else if (s_Fb.bits_per_pixel == 32)
        {

            pix = (c.r << s_Fb.red.offset) |
                  (c.g << s_Fb.green.offset) |
                  (c.b << s_Fb.blue.offset);




            for (k = 0; k < fb_scaling; k++) {
                *(uint32_t *)out = pix;
                out += 4;
            }
        }
        else {

            I_Error("No idea how to convert %d bpp pixels", s_Fb.bits_per_pixel);
        }

        in++;
    }
}

void I_InitGraphics (void)
{
    int i, gfxmodeparm;
    char *mode;

 memset(&s_Fb, 0, sizeof(struct FB_ScreenInfo));
 s_Fb.xres = 640;
 s_Fb.yres = 400;
 s_Fb.xres_virtual = s_Fb.xres;
 s_Fb.yres_virtual = s_Fb.yres;







 gfxmodeparm = M_CheckParmWithArgs("-gfxmode", 1);

 if (gfxmodeparm) {
  mode = myargv[gfxmodeparm + 1];
 }
 else {


  mode = "rgba8888";
 }

 if (strcmp(mode, "rgba8888") == 0) {

  s_Fb.bits_per_pixel = 32;

  s_Fb.blue.length = 8;
  s_Fb.green.length = 8;
  s_Fb.red.length = 8;
  s_Fb.transp.length = 8;

  s_Fb.blue.offset = 0;
  s_Fb.green.offset = 8;
  s_Fb.red.offset = 16;
  s_Fb.transp.offset = 24;
 }

 else if (strcmp(mode, "rgb565") == 0) {
  s_Fb.bits_per_pixel = 16;

  s_Fb.blue.length = 5;
  s_Fb.green.length = 6;
  s_Fb.red.length = 5;
  s_Fb.transp.length = 0;

  s_Fb.blue.offset = 11;
  s_Fb.green.offset = 5;
  s_Fb.red.offset = 0;
  s_Fb.transp.offset = 16;
 }
 else
  I_Error("Unknown gfxmode value: %s\n", mode);




    printf("I_InitGraphics: framebuffer: x_res: %d, y_res: %d, x_virtual: %d, y_virtual: %d, bpp: %d\n",
            s_Fb.xres, s_Fb.yres, s_Fb.xres_virtual, s_Fb.yres_virtual, s_Fb.bits_per_pixel);

    printf("I_InitGraphics: framebuffer: RGBA: %d%d%d%d, red_off: %d, green_off: %d, blue_off: %d, transp_off: %d\n",
            s_Fb.red.length, s_Fb.green.length, s_Fb.blue.length, s_Fb.transp.length, s_Fb.red.offset, s_Fb.green.offset, s_Fb.blue.offset, s_Fb.transp.offset);

    printf("I_InitGraphics: DOOM screen size: w x h: %d x %d\n", 320, 200);


    i = M_CheckParmWithArgs("-scaling", 1);
    if (i > 0) {
        i = atoi(myargv[i + 1]);
        fb_scaling = i;
        printf("I_InitGraphics: Scaling factor: %d\n", fb_scaling);
    } else {
        fb_scaling = s_Fb.xres / 320;
        if (s_Fb.yres / 200 < fb_scaling)
            fb_scaling = s_Fb.yres / 200;
        printf("I_InitGraphics: Auto-scaling factor: %d\n", fb_scaling);
    }



 I_VideoBuffer = (byte*)Z_Malloc (320 * 200, PU_STATIC, ((void*)0));

 screenvisible = true;

    extern void I_InitInput(void);
    I_InitInput();
}

void I_ShutdownGraphics (void)
{
 Z_Free (I_VideoBuffer);
}

void I_StartFrame (void)
{

}

void I_StartTic (void)
{
 I_GetEvent();
}

void I_UpdateNoBlit (void)
{
}





void I_FinishUpdate (void)
{
    int y;
    int x_offset, y_offset, x_offset_end;
    unsigned char *line_in, *line_out;





    y_offset = (((s_Fb.yres - (200 * fb_scaling)) * s_Fb.bits_per_pixel/8)) / 2;
    x_offset = (((s_Fb.xres - (320 * fb_scaling)) * s_Fb.bits_per_pixel/8)) / 2;

    x_offset_end = ((s_Fb.xres - (320 * fb_scaling)) * s_Fb.bits_per_pixel/8) - x_offset;


    line_in = (unsigned char *) I_VideoBuffer;
    line_out = (unsigned char *) DG_ScreenBuffer;

    y = 200;

    while (y--)
    {
        int i;
        for (i = 0; i < fb_scaling; i++) {
            line_out += x_offset;
            cmap_to_fb((void*)line_out, (void*)line_in, 320);

            line_out += (320 * fb_scaling * (s_Fb.bits_per_pixel/8)) + x_offset_end;
        }
        line_in += 320;
    }

 DG_DrawFrame();
}




void I_ReadScreen (byte* scr)
{
    memcpy (scr, I_VideoBuffer, 320 * 200);
}
void I_SetPalette (byte* palette)
{
 int i;
    for (i=0; i<256; ++i ) {
        colors[i].a = 0;
        colors[i].r = gammatable[usegamma][*palette++];
        colors[i].g = gammatable[usegamma][*palette++];
        colors[i].b = gammatable[usegamma][*palette++];
    }






}



int I_GetPaletteIndex (int r, int g, int b)
{
    int best, best_diff, diff;
    int i;
    col_t color;

    printf("I_GetPaletteIndex\n");

    best = 0;
    best_diff = 2147483647;

    for (i = 0; i < 256; ++i)
    {
     color.r = ((0xF800 & rgb565_palette[i]) >> 11);
     color.g = ((0x07E0 & rgb565_palette[i]) >> 5);
     color.b = (0x001F & rgb565_palette[i]);

        diff = (r - color.r) * (r - color.r)
             + (g - color.g) * (g - color.g)
             + (b - color.b) * (b - color.b);

        if (diff < best_diff)
        {
            best = i;
            best_diff = diff;
        }

        if (diff == 0)
        {
            break;
        }
    }

    return best;
}

void I_BeginRead (void)
{
}

void I_EndRead (void)
{
}

void I_SetWindowTitle (char *title)
{
 DG_SetWindowTitle(title);
}

void I_GraphicsCheckCommandLine (void)
{
}

void I_SetGrabMouseCallback (grabmouse_callback_t func)
{
}

void I_EnableLoadingDisk(void)
{
}

void I_BindVideoVariables (void)
{
}

void I_DisplayFPSDots (boolean dots_on)
{
}

void I_CheckIsScreensaver (void)
{
}






pixel_t* DG_ScreenBuffer = ((void*)0);

void M_FindResponseFile(void);
void D_DoomMain (void);


void doomgeneric_Create(int argc, char **argv)
{

    myargc = argc;
    myargv = argv;

 M_FindResponseFile();

 DG_ScreenBuffer = malloc(640 * 400 * 4);

 DG_Init();

 D_DoomMain ();
}

