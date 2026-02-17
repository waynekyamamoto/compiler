// Test batch 33: if arithmetic expressions
int printf(char *fmt, ...);

#define VER 3
#define FEAT_A 1
#define FEAT_B 1

int main() {
    int fail = 0;
    int val = 0;

    // Macro comparison
#if VER > 2
    val = 1;
#else
    val = 0;
#endif
    if (val != 1) { printf("FAIL: VER > 2 should be true\n"); fail = 1; }

    // Logical AND with defined
#if defined(FEAT_A) && defined(FEAT_B)
    val = 1;
#else
    val = 0;
#endif
    if (val != 1) { printf("FAIL: defined(FEAT_A) && defined(FEAT_B) should be true\n"); fail = 1; }

    // Logical OR with defined
#if defined(FEAT_A) || defined(NOPE)
    val = 1;
#else
    val = 0;
#endif
    if (val != 1) { printf("FAIL: defined(FEAT_A) || defined(NOPE) should be true\n"); fail = 1; }

    // Arithmetic equality
#if (1 + 2) == 3
    val = 1;
#else
    val = 0;
#endif
    if (val != 1) { printf("FAIL: (1 + 2) == 3 should be true\n"); fail = 1; }

    // Hex literal comparison
#if 0x10 > 15
    val = 1;
#else
    val = 0;
#endif
    if (val != 1) { printf("FAIL: 0x10 > 15 should be true\n"); fail = 1; }

    // Negation
#if !0
    val = 1;
#else
    val = 0;
#endif
    if (val != 1) { printf("FAIL: !0 should be true\n"); fail = 1; }

    // Inequality
#if VER != 2
    val = 1;
#else
    val = 0;
#endif
    if (val != 1) { printf("FAIL: VER != 2 should be true\n"); fail = 1; }

    if (fail == 0) {
        printf("batch33: all tests passed\n");
    }
    return fail;
}
