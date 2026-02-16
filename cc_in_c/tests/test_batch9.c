/* test_batch9.c — Function pointer tests */

int printf(int *fmt, ...);

int add(int a, int b) {
    return a + b;
}

int mul(int a, int b) {
    return a * b;
}

int negate(int x) {
    return 0 - x;
}

int apply2(int *fp, int a, int b) {
    return fp(a, b);
}

int test_basic_fptr() {
    int *fp;
    fp = add;
    int result;
    result = fp(3, 4);
    if (result != 7) { return 1; }
    return 0;
}

int test_fptr_reassign() {
    int *fp;
    fp = add;
    int r1;
    r1 = fp(10, 20);
    if (r1 != 30) { return 1; }
    fp = mul;
    int r2;
    r2 = fp(10, 20);
    if (r2 != 200) { return 1; }
    return 0;
}

int test_fptr_as_arg() {
    int result;
    result = apply2(add, 5, 6);
    if (result != 11) { return 1; }
    result = apply2(mul, 5, 6);
    if (result != 30) { return 1; }
    return 0;
}

int test_fptr_one_arg() {
    int *fp;
    fp = negate;
    int result;
    result = fp(42);
    if (result != -42) { return 1; }
    return 0;
}

int main() {
    int fail;
    fail = 0;

    if (test_basic_fptr()) { printf("FAIL: basic fptr\n"); fail = 1; }
    if (test_fptr_reassign()) { printf("FAIL: fptr reassign\n"); fail = 1; }
    if (test_fptr_as_arg()) { printf("FAIL: fptr as arg\n"); fail = 1; }
    if (test_fptr_one_arg()) { printf("FAIL: fptr one arg\n"); fail = 1; }

    if (!fail) { printf("batch9: all tests passed\n"); }
    return fail;
}
