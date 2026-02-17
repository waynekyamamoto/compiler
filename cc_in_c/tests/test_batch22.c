#include <stdio.h>

/* Test 1: function with 9 parameters */
int sum9(int a, int b, int c, int d, int e, int f, int g, int h, int i) {
    return a + b + c + d + e + f + g + h + i;
}

/* Test 2: function with 10 parameters */
int sum10(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j) {
    return a + b + c + d + e + f + g + h + i + j;
}

/* Test 3: function with 12 parameters, verifying each is correct */
int check12(int a, int b, int c, int d, int e, int f, int g, int h,
            int i, int j, int k, int l) {
    if (a != 1) return 1;
    if (b != 2) return 2;
    if (c != 3) return 3;
    if (d != 4) return 4;
    if (e != 5) return 5;
    if (f != 6) return 6;
    if (g != 7) return 7;
    if (h != 8) return 8;
    if (i != 9) return 9;
    if (j != 10) return 10;
    if (k != 11) return 11;
    if (l != 12) return 12;
    return 0;
}

/* Test 4: 9 args with pointer return */
int *identity_ptr(int *a, int b, int c, int d, int e, int f, int g, int h, int i) {
    return a;
}

int main() {
    int fail = 0;

    /* Test 1: sum of 9 */
    if (sum9(1, 2, 3, 4, 5, 6, 7, 8, 9) != 45) {
        printf("FAIL: sum9\n"); fail = 1;
    }

    /* Test 2: sum of 10 */
    if (sum10(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) != 55) {
        printf("FAIL: sum10\n"); fail = 1;
    }

    /* Test 3: each param correct */
    int r = check12(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    if (r != 0) {
        printf("FAIL: check12 param %d wrong\n", r); fail = 1;
    }

    /* Test 4: pointer return with >8 args */
    int val = 42;
    int *p = identity_ptr(&val, 2, 3, 4, 5, 6, 7, 8, 9);
    if (*p != 42) {
        printf("FAIL: identity_ptr\n"); fail = 1;
    }

    if (fail == 0) printf("test_batch22 passed\n");
    return fail;
}
