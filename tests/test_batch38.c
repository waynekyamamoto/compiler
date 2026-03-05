// Test batch 38: sizeof for bitfield structs
int printf(char *fmt, ...);

struct Packed {
    int a : 8;
    int b : 16;
    int c : 8;
};

struct Mixed {
    int x;
    int a : 4;
    int b : 4;
};

struct Normal {
    int x;
    int y;
    int z;
};

int main() {
    int fail = 0;

    // Packed: 3 bitfields all fit in 1 int (8+16+8=32 bits <= 32)
    if (sizeof(struct Packed) != 4) {
        printf("FAIL: sizeof(Packed) = %d, expected 4\n", sizeof(struct Packed));
        fail = 1;
    }

    // Mixed: 1 int (4) + 2 bitfields in 1 int (4) = 8 bytes
    if (sizeof(struct Mixed) != 8) {
        printf("FAIL: sizeof(Mixed) = %d, expected 8\n", sizeof(struct Mixed));
        fail = 1;
    }

    // Normal: 3 ints = 12 bytes
    if (sizeof(struct Normal) != 12) {
        printf("FAIL: sizeof(Normal) = %d, expected 12\n", sizeof(struct Normal));
        fail = 1;
    }

    if (fail == 0) {
        printf("batch38: all tests passed\n");
    }
    return fail;
}
