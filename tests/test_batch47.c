// Test batch 47: Constant expressions in global initializers
int printf(char *fmt, ...);

#define SIZE 10
#define HALF (SIZE / 2)

// Basic arithmetic
int g1 = 10 + 20;
int g2 = 100 - 30;
int g3 = 6 * 7;
int g4 = 100 / 4;

// With macros
int g5 = SIZE * 2;
int g6 = HALF + 3;

// Ternary
int g7 = 1 > 0 ? 42 : 0;
int g8 = 0 > 1 ? 0 : 99;

// Bitwise
int g9 = 0xFF & 0x0F;
int g10 = 0xF0 | 0x0F;

// Shifts
int g11 = 1 << 8;

// Comparison
int g12 = 5 > 3;
int g13 = 5 == 5;

// Negative
int g14 = -100;

// Parenthesized
int g15 = (10 + 20) * 2;

// Logical
int g16 = 1 && 1;
int g17 = 0 || 1;
int g18 = !0;

int main() {
    int fail = 0;
    if (g1 != 30) { printf("FAIL: g1=%d\n", g1); fail = 1; }
    if (g2 != 70) { printf("FAIL: g2=%d\n", g2); fail = 1; }
    if (g3 != 42) { printf("FAIL: g3=%d\n", g3); fail = 1; }
    if (g4 != 25) { printf("FAIL: g4=%d\n", g4); fail = 1; }
    if (g5 != 20) { printf("FAIL: g5=%d\n", g5); fail = 1; }
    if (g6 != 8) { printf("FAIL: g6=%d\n", g6); fail = 1; }
    if (g7 != 42) { printf("FAIL: g7=%d\n", g7); fail = 1; }
    if (g8 != 99) { printf("FAIL: g8=%d\n", g8); fail = 1; }
    if (g9 != 15) { printf("FAIL: g9=%d\n", g9); fail = 1; }
    if (g10 != 255) { printf("FAIL: g10=%d\n", g10); fail = 1; }
    if (g11 != 256) { printf("FAIL: g11=%d\n", g11); fail = 1; }
    if (g12 != 1) { printf("FAIL: g12=%d\n", g12); fail = 1; }
    if (g13 != 1) { printf("FAIL: g13=%d\n", g13); fail = 1; }
    if (g14 != -100) { printf("FAIL: g14=%d\n", g14); fail = 1; }
    if (g15 != 60) { printf("FAIL: g15=%d\n", g15); fail = 1; }
    if (g16 != 1) { printf("FAIL: g16=%d\n", g16); fail = 1; }
    if (g17 != 1) { printf("FAIL: g17=%d\n", g17); fail = 1; }
    if (g18 != 1) { printf("FAIL: g18=%d\n", g18); fail = 1; }
    if (fail == 0) printf("batch47: all tests passed\n");
    return fail;
}
