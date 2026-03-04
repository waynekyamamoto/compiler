#include <stdio.h>
typedef unsigned char byte;
typedef void *patch_t;
typedef int boolean;
typedef boolean (*vpatchclipfunc_t)(patch_t *, int, int);

long pk_i16(void *base, long off) {
    unsigned char *p = (unsigned char *)base;
    long lo = p[off];
    long hi = p[off+1];
    long v = lo | (hi << 8);
    if (v >= 32768) v = v - 65536;
    return v;
}

vpatchclipfunc_t patchclip_callback = 0;
byte *screens[5];

void V_MarkRect(int x, int y, int w, int h) {}
void I_Error(char *error, ...) { printf("ERROR: %s\n", error); }

void V_DrawPatch(int x, int y, patch_t *patch)
{
    int count;
    int col;
    byte *column;
    byte *desttop;
    byte *dest;
    byte *source;
    int w;
    int coloff;

    y -= ((signed short) (pk_i16(patch, 6)));
    x -= ((signed short) (pk_i16(patch, 4)));

    if(patchclip_callback)
    {
        if(!patchclip_callback(patch, x, y))
            return;
    }

    int c4 = (y + ((signed short)(pk_i16(patch, 2))) > 200);
    printf("x=%d y=%d c4=%d sum=%d\n", x, y, c4, y + (int)((signed short)(pk_i16(patch, 2))));

    if (x < 0
     || x + ((signed short) (pk_i16(patch, 0))) > 320
     || y < 0
     || y + ((signed short) (pk_i16(patch, 2))) > 200)
    {
        printf("Bad V_DrawPatch x=%d y=%d w=%d h=%d\n", x, y, (int)pk_i16(patch, 0), (int)pk_i16(patch, 2));
        return;
    }
    printf("PASS\n");
}

int main() {
    unsigned char patchdata[8];
    patchdata[0] = 0x40; patchdata[1] = 0x01;
    patchdata[2] = 0xC8; patchdata[3] = 0x00;
    patchdata[4] = 0x00; patchdata[5] = 0x00;
    patchdata[6] = 0x00; patchdata[7] = 0x00;
    V_DrawPatch(0, 0, (patch_t *)patchdata);
    return 0;
}
