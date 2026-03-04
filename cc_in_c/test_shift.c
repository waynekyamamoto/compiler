int printf(char *fmt, ...);

int main() {
    long a = 0x52;
    long b = a << 32;
    printf("a << 32 = %ld (0x%lx)\n", b, b);

    long packed = 0;
    packed = packed | (((long)0x53) << 0);
    packed = packed | (((long)0x57) << 8);
    packed = packed | (((long)0x31) << 16);
    packed = packed | (((long)0x42) << 24);
    packed = packed | (((long)0x52) << 32);
    packed = packed | (((long)0x43) << 40);
    packed = packed | (((long)0x4F) << 48);
    packed = packed | (((long)0x4D) << 56);
    printf("packed = %ld (0x%lx)\n", packed, packed);
    return 0;
}
