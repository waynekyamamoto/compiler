#include <stdio.h>

/* Test 1: static local retains value across calls */
int counter() {
    static int count = 0;
    count = count + 1;
    return count;
}

/* Test 2: static local with no initializer (should be zero) */
int accum(int val) {
    static int total;
    total = total + val;
    return total;
}

/* Test 3: multiple static locals in same function */
int multi_static(int which) {
    static int a = 10;
    static int b = 20;
    if (which == 0) {
        a = a + 1;
        return a;
    }
    b = b + 1;
    return b;
}

/* Test 4: static locals in different functions don't interfere */
int counter2() {
    static int count = 0;
    count = count + 1;
    return count;
}

int main() {
    int fail = 0;

    /* Test 1: counter increments */
    if (counter() != 1) { printf("FAIL: counter call 1\n"); fail = 1; }
    if (counter() != 2) { printf("FAIL: counter call 2\n"); fail = 1; }
    if (counter() != 3) { printf("FAIL: counter call 3\n"); fail = 1; }

    /* Test 2: accumulator */
    if (accum(5) != 5) { printf("FAIL: accum 5\n"); fail = 1; }
    if (accum(3) != 8) { printf("FAIL: accum 5+3\n"); fail = 1; }
    if (accum(2) != 10) { printf("FAIL: accum 5+3+2\n"); fail = 1; }

    /* Test 3: multiple statics */
    if (multi_static(0) != 11) { printf("FAIL: multi a first\n"); fail = 1; }
    if (multi_static(1) != 21) { printf("FAIL: multi b first\n"); fail = 1; }
    if (multi_static(0) != 12) { printf("FAIL: multi a second\n"); fail = 1; }

    /* Test 4: separate functions have separate statics */
    if (counter2() != 1) { printf("FAIL: counter2 call 1\n"); fail = 1; }
    if (counter() != 4) { printf("FAIL: counter still at 4\n"); fail = 1; }
    if (counter2() != 2) { printf("FAIL: counter2 call 2\n"); fail = 1; }

    if (fail == 0) printf("test_batch21 passed\n");
    return fail;
}
