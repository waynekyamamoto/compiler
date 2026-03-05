#include <stdio.h>

#define HAVE_FEATURE 1

int main() {
    int result = 0;

    /* Test 1: #if 0 */
#if 0
    result = 999;
#endif
    if (result != 0) { printf("FAIL: if 0\n"); return 1; }

    /* Test 2: #if 1 */
#if 1
    result = 1;
#endif
    if (result != 1) { printf("FAIL: if 1\n"); return 1; }

    /* Test 3: #if 0 with #else */
    result = 0;
#if 0
    result = 10;
#else
    result = 20;
#endif
    if (result != 20) { printf("FAIL: if 0 else\n"); return 1; }

    /* Test 4: #if 1 with #else */
    result = 0;
#if 1
    result = 30;
#else
    result = 40;
#endif
    if (result != 30) { printf("FAIL: if 1 else\n"); return 1; }

    /* Test 5: #if defined(NAME) */
    result = 0;
#if defined(HAVE_FEATURE)
    result = 5;
#endif
    if (result != 5) { printf("FAIL: if defined\n"); return 1; }

    /* Test 6: #if defined with undefined */
    result = 0;
#if defined(NO_FEATURE)
    result = 999;
#endif
    if (result != 0) { printf("FAIL: if defined undef\n"); return 1; }

    /* Test 7: #if !defined */
    result = 0;
#if !defined(NO_FEATURE)
    result = 7;
#endif
    if (result != 7) { printf("FAIL: if !defined\n"); return 1; }

    /* Test 8: #elif chain */
    result = 0;
#if 0
    result = 10;
#elif 1
    result = 20;
#else
    result = 30;
#endif
    if (result != 20) { printf("FAIL: elif chain\n"); return 1; }

    /* Test 9: #elif — first true, skip rest */
    result = 0;
#if 1
    result = 100;
#elif 1
    result = 200;
#else
    result = 300;
#endif
    if (result != 100) { printf("FAIL: elif first true\n"); return 1; }

    /* Test 10: #elif — all false, fall to else */
    result = 0;
#if 0
    result = 10;
#elif 0
    result = 20;
#else
    result = 30;
#endif
    if (result != 30) { printf("FAIL: elif all false else\n"); return 1; }

    /* Test 11: nested #if */
    result = 0;
#if 1
#if 0
    result = 999;
#else
    result = 11;
#endif
#endif
    if (result != 11) { printf("FAIL: nested if\n"); return 1; }

    /* Test 12: #if inside #if 0 — nested skipped block */
    result = 0;
#if 0
#if 1
    result = 999;
#endif
#endif
    if (result != 0) { printf("FAIL: nested skip\n"); return 1; }

    /* Test 13: #elif with defined */
    result = 0;
#if defined(NO_FEATURE)
    result = 10;
#elif defined(HAVE_FEATURE)
    result = 20;
#else
    result = 30;
#endif
    if (result != 20) { printf("FAIL: elif defined\n"); return 1; }

    printf("All batch 20 tests passed.\n");
    return 0;
}
