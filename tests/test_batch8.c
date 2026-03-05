/* test_batch8.c — #define macro tests */

int printf(int *fmt, ...);

#define MAX_SIZE 100
#define OFFSET 10
#define ZERO 0
#define NEG_ONE -1

int test_basic_define() {
    int x;
    x = MAX_SIZE;
    if (x != 100) { return 1; }
    return 0;
}

int test_define_in_expr() {
    int y;
    y = MAX_SIZE + OFFSET;
    if (y != 110) { return 1; }
    return 0;
}

int test_define_zero() {
    if (ZERO != 0) { return 1; }
    return 0;
}

int test_define_negative() {
    int v;
    v = NEG_ONE;
    if (v != -1) { return 1; }
    return 0;
}

#define ADD(a, b) a + b

int test_redefine() {
    int a;
    a = MAX_SIZE;
    if (a != 100) { return 1; }
    return 0;
}

int main() {
    int fail;
    fail = 0;

    if (test_basic_define()) { printf("FAIL: basic define\n"); fail = 1; }
    if (test_define_in_expr()) { printf("FAIL: define in expr\n"); fail = 1; }
    if (test_define_zero()) { printf("FAIL: define zero\n"); fail = 1; }
    if (test_define_negative()) { printf("FAIL: define negative\n"); fail = 1; }
    if (test_redefine()) { printf("FAIL: redefine\n"); fail = 1; }

    if (!fail) { printf("batch8: all tests passed\n"); }
    return fail;
}
