/* test_batch41: va_list / va_start / va_arg */
int printf(char *fmt, ...);

int sum_ints(int count, ...) {
    char *ap;
    __builtin_va_start(&ap);
    int total = 0;
    int i = 0;
    while (i < count) {
        total = total + *(int*)((ap = ap + 8) - 8);
        i = i + 1;
    }
    return total;
}

/* Test va_arg with pointer type */
char *first_str(int dummy, ...) {
    char *ap;
    __builtin_va_start(&ap);
    char *s = *(char**)((ap = ap + 8) - 8);
    return s;
}

int main() {
    int fail = 0;

    int s1 = sum_ints(3, 10, 20, 30);
    if (s1 != 60) { printf("FAIL: sum_ints(3, 10,20,30) = %d\n", s1); fail = 1; }

    int s2 = sum_ints(1, 42);
    if (s2 != 42) { printf("FAIL: sum_ints(1, 42) = %d\n", s2); fail = 1; }

    int s3 = sum_ints(0);
    if (s3 != 0) { printf("FAIL: sum_ints(0) = %d\n", s3); fail = 1; }

    char *r = first_str(0, "hello");
    if (r == 0) { printf("FAIL: first_str returned NULL\n"); fail = 1; }

    if (!fail) printf("batch41: all tests passed\n");
    return fail;
}
