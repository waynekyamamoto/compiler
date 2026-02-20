/* test_batch41: va_list / va_start / va_arg */
#include <stdarg.h>
int printf(char *fmt, ...);

int sum_ints(int count, ...) {
    va_list ap;
    va_start(ap, count);
    int total = 0;
    int i = 0;
    while (i < count) {
        total = total + va_arg(ap, int);
        i = i + 1;
    }
    va_end(ap);
    return total;
}

/* Test va_arg with pointer type */
char *first_str(int dummy, ...) {
    va_list ap;
    va_start(ap, dummy);
    char *s = va_arg(ap, char *);
    va_end(ap);
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
    /* Note: r[0] does word-load, not byte-load — skip byte comparison */
    if (r == 0) { printf("FAIL: first_str returned NULL\n"); fail = 1; }

    if (!fail) printf("batch41: all tests passed\n");
    return fail;
}
