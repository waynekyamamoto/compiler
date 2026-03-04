#include <stdio.h>

long pk_i16(void *base, long off) {
    unsigned char *p = (unsigned char *)base;
    long lo = p[off];
    long hi = p[off+1];
    long v = lo | (hi << 8);
    if (v >= 32768) v = v - 65536;
    return v;
}

int main() {
    /* Simulate a patch header: w=320(0x0140), h=200(0x00C8), lo=0, to=0 */
    unsigned char patch[8];
    patch[0] = 0x40; patch[1] = 0x01;  /* width = 320 */
    patch[2] = 0xC8; patch[3] = 0x00;  /* height = 200 */
    patch[4] = 0x00; patch[5] = 0x00;  /* leftoffset = 0 */
    patch[6] = 0x00; patch[7] = 0x00;  /* topoffset = 0 */
    
    int x = 0;
    int y = 0;
    
    y -= ((signed short)(pk_i16(patch, 6)));
    x -= ((signed short)(pk_i16(patch, 4)));
    
    printf("x=%d y=%d w=%d h=%d\n", x, y, (int)pk_i16(patch, 0), (int)pk_i16(patch, 2));
    printf("x+w=%d y+h=%d\n", x + (int)((signed short)(pk_i16(patch, 0))), y + (int)((signed short)(pk_i16(patch, 2))));
    
    if (x < 0
     || x + ((signed short)(pk_i16(patch, 0))) > 320
     || y < 0
     || y + ((signed short)(pk_i16(patch, 2))) > 200)
    {
        printf("BAD: condition was true (BUG)\n");
    } else {
        printf("GOOD: condition was false\n");
    }
    
    return 0;
}
