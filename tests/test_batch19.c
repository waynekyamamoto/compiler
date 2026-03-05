#include <stdio.h>

#define FEATURE_A 1

int main() {
    int result = 0;

    /* Test 1: #ifdef with defined macro */
#ifdef FEATURE_A
    result = 1;
#endif
    if (result != 1) { printf("FAIL: ifdef defined\n"); return 1; }

    /* Test 2: #ifdef with undefined macro */
    result = 0;
#ifdef FEATURE_B
    result = 999;
#endif
    if (result != 0) { printf("FAIL: ifdef undefined\n"); return 1; }

    /* Test 3: #ifndef with undefined macro */
    result = 0;
#ifndef FEATURE_B
    result = 2;
#endif
    if (result != 2) { printf("FAIL: ifndef undefined\n"); return 1; }

    /* Test 4: #ifndef with defined macro */
    result = 0;
#ifndef FEATURE_A
    result = 999;
#endif
    if (result != 0) { printf("FAIL: ifndef defined\n"); return 1; }

    /* Test 5: #ifdef / #else */
    result = 0;
#ifdef FEATURE_B
    result = 10;
#else
    result = 20;
#endif
    if (result != 20) { printf("FAIL: ifdef else\n"); return 1; }

    /* Test 6: #ifdef true with else */
    result = 0;
#ifdef FEATURE_A
    result = 30;
#else
    result = 40;
#endif
    if (result != 30) { printf("FAIL: ifdef true else\n"); return 1; }

    /* Test 7: nested #ifdef */
    result = 0;
#ifdef FEATURE_A
#ifndef FEATURE_B
    result = 50;
#endif
#endif
    if (result != 50) { printf("FAIL: nested ifdef\n"); return 1; }

    /* Test 8: nested — outer false skips inner */
    result = 0;
#ifdef FEATURE_B
#ifdef FEATURE_A
    result = 999;
#endif
#endif
    if (result != 0) { printf("FAIL: nested outer false\n"); return 1; }

    /* Test 9: #define inside #ifdef */
#ifdef FEATURE_A
#define INNER_DEF 77
#endif
    if (INNER_DEF != 77) { printf("FAIL: define inside ifdef\n"); return 1; }

    /* Test 10: include guard pattern */
#ifndef MY_GUARD
#define MY_GUARD 1
    result = 100;
#endif
#ifndef MY_GUARD
    result = 999;
#endif
    if (result != 100) { printf("FAIL: include guard\n"); return 1; }

    printf("All batch 19 tests passed.\n");
    return 0;
}
