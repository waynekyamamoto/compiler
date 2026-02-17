// Test batch 32: Enum value expressions
int printf(char *fmt, ...);

enum Flags {
    FLAG_A = 1 << 0,
    FLAG_B = 1 << 1,
    FLAG_C = 1 << 2,
    ALL_FLAGS = FLAG_A | FLAG_B | FLAG_C
};

enum Calc {
    MASK = ~0 & 0xFF,
    PRODUCT = (2 + 3) * 4,
    NEGATIVE = -10,
    COMPLEX = (1 << 4) | (1 << 2)
};

int main() {
    int fail = 0;

    if (FLAG_A != 1) { printf("FAIL: FLAG_A = %d, expected 1\n", FLAG_A); fail = 1; }
    if (FLAG_B != 2) { printf("FAIL: FLAG_B = %d, expected 2\n", FLAG_B); fail = 1; }
    if (FLAG_C != 4) { printf("FAIL: FLAG_C = %d, expected 4\n", FLAG_C); fail = 1; }
    if (ALL_FLAGS != 7) { printf("FAIL: ALL_FLAGS = %d, expected 7\n", ALL_FLAGS); fail = 1; }

    if (MASK != 255) { printf("FAIL: MASK = %d, expected 255\n", MASK); fail = 1; }
    if (PRODUCT != 20) { printf("FAIL: PRODUCT = %d, expected 20\n", PRODUCT); fail = 1; }
    if (NEGATIVE != -10) { printf("FAIL: NEGATIVE = %d, expected -10\n", NEGATIVE); fail = 1; }
    if (COMPLEX != 20) { printf("FAIL: COMPLEX = %d, expected 20\n", COMPLEX); fail = 1; }

    if (fail == 0) {
        printf("batch32: all tests passed\n");
    }
    return fail;
}
