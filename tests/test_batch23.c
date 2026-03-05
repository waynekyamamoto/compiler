#include <stdio.h>

struct Point {
    int x;
    int y;
    int z;
};

/* Test 1: struct designated initializer - out of order */
int test_struct_desig() {
    struct Point p = {.z = 30, .x = 10, .y = 20};
    if (p.x != 10) return 1;
    if (p.y != 20) return 2;
    if (p.z != 30) return 3;
    return 0;
}

/* Test 2: array designated initializer */
int test_array_desig() {
    int arr[5] = {[2] = 20, [4] = 40};
    if (arr[2] != 20) return 1;
    if (arr[4] != 40) return 2;
    return 0;
}

/* Test 3: mixed positional and designated */
int test_mixed() {
    struct Point p = {1, .z = 3, .y = 2};
    if (p.x != 1) return 1;
    if (p.y != 2) return 2;
    if (p.z != 3) return 3;
    return 0;
}

/* Test 4: struct designated - partial init */
int test_partial() {
    struct Point p = {.y = 42};
    if (p.y != 42) return 1;
    return 0;
}

int main() {
    int fail = 0;

    int r = test_struct_desig();
    if (r != 0) { printf("FAIL: test_struct_desig step %d\n", r); fail = 1; }

    r = test_array_desig();
    if (r != 0) { printf("FAIL: test_array_desig step %d\n", r); fail = 1; }

    r = test_mixed();
    if (r != 0) { printf("FAIL: test_mixed step %d\n", r); fail = 1; }

    r = test_partial();
    if (r != 0) { printf("FAIL: test_partial step %d\n", r); fail = 1; }

    if (fail == 0) printf("test_batch23 passed\n");
    return fail;
}
