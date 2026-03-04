#include <stdio.h>

long pk_i16(void *base, long off) {
    unsigned char *p = (unsigned char *)base;
    long lo = p[off];
    long hi = p[off+1];
    long v = lo | (hi << 8);
    if (v >= 32768) v = v - 65536;
    return v;
}

void test(int x, int y, void *patch) {
    /* Mimic exactly V_DrawPatch's c4 check */
    int c4 = (y + ((signed short)(pk_i16(patch, 2))) > 200);
    printf("y=%d pk=%ld cast=%d sum=%d c4=%d\n", y, pk_i16(patch,2), (int)(signed short)(pk_i16(patch,2)), y + (int)(signed short)(pk_i16(patch,2)), c4);
}

int main() {
    unsigned char patch[8];
    patch[0] = 0x40; patch[1] = 0x01;
    patch[2] = 0xC8; patch[3] = 0x00;
    patch[4] = 0x00; patch[5] = 0x00;
    patch[6] = 0x00; patch[7] = 0x00;
    test(0, 0, patch);
    return 0;
}
