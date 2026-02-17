// Test batch 36: -D command-line macro definitions
// Compile with: -DTEST_VAL=42 -DFLAG
int printf(char *fmt, ...);

#ifndef FLAG
int undefined_variable_FLAG_missing;
#endif

int main() {
    int fail = 0;

    if (TEST_VAL != 42) {
        printf("FAIL: TEST_VAL = %d, expected 42\n", TEST_VAL);
        fail = 1;
    }

#ifdef FLAG
    // FLAG is defined (good)
#else
    printf("FAIL: FLAG should be defined\n");
    fail = 1;
#endif

    if (fail == 0) {
        printf("batch36: all tests passed\n");
    }
    return fail;
}
