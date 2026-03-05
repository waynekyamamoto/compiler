#include <stdio.h>

/* Test 1: anonymous struct as field type */
struct Container {
    struct { int x; int y; } point;
    int z;
};

int test_anon_field() {
    struct Container c;
    c.point.x = 10;
    c.point.y = 20;
    c.z = 30;
    if (c.point.x != 10) return 1;
    if (c.point.y != 20) return 2;
    if (c.z != 30) return 3;
    return 0;
}

/* Test 2: anonymous struct local variable */
int test_anon_local() {
    struct { int a; int b; } pair;
    pair.a = 42;
    pair.b = 99;
    if (pair.a != 42) return 1;
    if (pair.b != 99) return 2;
    return 0;
}

/* Test 3: anonymous struct with initializer */
int test_anon_init() {
    struct { int x; int y; int z; } v = {1, 2, 3};
    if (v.x != 1) return 1;
    if (v.y != 2) return 2;
    if (v.z != 3) return 3;
    return 0;
}

int main() {
    int fail = 0;

    int r = test_anon_field();
    if (r != 0) { printf("FAIL: test_anon_field step %d\n", r); fail = 1; }

    r = test_anon_local();
    if (r != 0) { printf("FAIL: test_anon_local step %d\n", r); fail = 1; }

    r = test_anon_init();
    if (r != 0) { printf("FAIL: test_anon_init step %d\n", r); fail = 1; }

    if (fail == 0) printf("test_batch25 passed\n");
    return fail;
}
