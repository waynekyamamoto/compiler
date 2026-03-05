// Test batch 34: undef support
int printf(char *fmt, ...);

#define FOO 42

#undef FOO

#define BAR 10

#undef BAR
#define BAR 99

// undef on undefined macro - should be no-op
#undef NOPE

int main() {
    int fail = 0;

#ifdef FOO
    printf("FAIL: FOO should be undefined\n");
    fail = 1;
#endif

    if (BAR != 99) { printf("FAIL: BAR = %d, expected 99\n", BAR); fail = 1; }

    if (fail == 0) {
        printf("batch34: all tests passed\n");
    }
    return fail;
}
