#include <stdio.h>

struct Point {
    int x;
    int y;
};

/* Test 1: basic compound literal */
int test_basic() {
    struct Point *p = &(struct Point){10, 20};
    if (p->x != 10) return 1;
    if (p->y != 20) return 2;
    return 0;
}

/* Test 2: compound literal with designated init */
int test_desig() {
    struct Point *p = &(struct Point){.y = 5, .x = 3};
    if (p->x != 3) return 1;
    if (p->y != 5) return 2;
    return 0;
}

/* Test 3: compound literal passed to function */
int sum_point(struct Point *p) {
    return p->x + p->y;
}

int test_arg() {
    int s = sum_point(&(struct Point){7, 8});
    if (s != 15) return 1;
    return 0;
}

/* Test 4: multiple compound literals */
int test_multi() {
    struct Point *a = &(struct Point){1, 2};
    struct Point *b = &(struct Point){3, 4};
    if (a->x + b->x != 4) return 1;
    if (a->y + b->y != 6) return 2;
    return 0;
}

int main() {
    int fail = 0;

    int r = test_basic();
    if (r != 0) { printf("FAIL: test_basic step %d\n", r); fail = 1; }

    r = test_desig();
    if (r != 0) { printf("FAIL: test_desig step %d\n", r); fail = 1; }

    r = test_arg();
    if (r != 0) { printf("FAIL: test_arg step %d\n", r); fail = 1; }

    r = test_multi();
    if (r != 0) { printf("FAIL: test_multi step %d\n", r); fail = 1; }

    if (fail == 0) printf("test_batch24 passed\n");
    return fail;
}
