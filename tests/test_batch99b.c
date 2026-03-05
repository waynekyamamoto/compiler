#include <stdio.h>
#include <string.h>

int main() {
    /* Test *char_ptr++ = value generates strb (byte store, not 8-byte store) */
    char buf[32];
    char *dst;
    char *src;
    int i;

    /* Clear buffer with known pattern */
    for (i = 0; i < 32; i++) buf[i] = 0xFF;

    /* Test 1: *dst++ = value */
    dst = buf;
    *dst++ = 'A';
    *dst++ = 'B';
    *dst++ = 'C';
    *dst++ = 0;

    /* If strb is used correctly, only bytes 0-3 are modified */
    /* If str (8-byte) is used, bytes 4-7 would be zeroed by the 0 write */
    if (buf[0] != 'A') { printf("FAIL: buf[0] = %d, expected 'A'\n", buf[0]); return 1; }
    if (buf[1] != 'B') { printf("FAIL: buf[1] = %d, expected 'B'\n", buf[1]); return 1; }
    if (buf[2] != 'C') { printf("FAIL: buf[2] = %d, expected 'C'\n", buf[2]); return 1; }
    if (buf[3] != 0)   { printf("FAIL: buf[3] = %d, expected 0\n", buf[3]); return 1; }
    /* Critical check: bytes after the null should still be 0xFF */
    if ((buf[4] & 0xFF) != 0xFF) { printf("FAIL: buf[4] = 0x%02x, expected 0xFF (8-byte store corruption)\n", buf[4] & 0xFF); return 1; }
    if ((buf[5] & 0xFF) != 0xFF) { printf("FAIL: buf[5] = 0x%02x, expected 0xFF (8-byte store corruption)\n", buf[5] & 0xFF); return 1; }
    if ((buf[6] & 0xFF) != 0xFF) { printf("FAIL: buf[6] = 0x%02x, expected 0xFF (8-byte store corruption)\n", buf[6] & 0xFF); return 1; }
    if ((buf[7] & 0xFF) != 0xFF) { printf("FAIL: buf[7] = 0x%02x, expected 0xFF (8-byte store corruption)\n", buf[7] & 0xFF); return 1; }

    /* Test 2: *dst++ = *src++ (both read and write with postinc) */
    for (i = 0; i < 32; i++) buf[i] = 0xFF;
    src = "Hello";
    dst = buf;
    while (*src != 0) {
        *dst++ = *src++;
    }
    *dst++ = 0;

    if (strcmp(buf, "Hello") != 0) { printf("FAIL: buf = '%s', expected 'Hello'\n", buf); return 1; }
    /* Check no corruption past null */
    if ((buf[6] & 0xFF) != 0xFF) { printf("FAIL: buf[6] = 0x%02x after copy, expected 0xFF\n", buf[6] & 0xFF); return 1; }

    printf("All *char_ptr++ tests passed.\n");
    return 0;
}
