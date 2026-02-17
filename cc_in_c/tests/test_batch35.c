// Test batch 35: #error directive (dormant in untaken branches)
int printf(char *fmt, ...);

// #error inside untaken #ifdef should NOT fire
#ifdef NEVER_DEFINED
#error this should not be reached
#endif

// #error inside #if 0 should NOT fire
#if 0
#error this is also skipped
#endif

// Nested: #if 1 / #if 0 / #error should NOT fire
#if 1
#if 0
#error nested skip
#endif
#endif

int main() {
    int fail = 0;

    // If we reach here, all dormant #error directives were properly skipped
    printf("batch35: all tests passed\n");
    return fail;
}
