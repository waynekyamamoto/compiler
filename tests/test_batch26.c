#include <stdio.h>

struct Flags {
    int a : 1;
    int b : 3;
    int c : 8;
    int d : 16;
};

/* Test 1: basic bitfield set and get */
int test_basic() {
    struct Flags f;
    f.a = 1;
    f.b = 5;
    f.c = 200;
    f.d = 1000;
    if (f.a != 1) return 1;
    if (f.b != 5) return 2;
    if (f.c != 200) return 3;
    if (f.d != 1000) return 4;
    return 0;
}

/* Test 2: bitfield overwrite */
int test_overwrite() {
    struct Flags f;
    f.a = 1;
    f.b = 7;
    f.c = 255;
    f.d = 65535;
    f.a = 0;
    f.b = 3;
    if (f.a != 0) return 1;
    if (f.b != 3) return 2;
    if (f.c != 255) return 3;
    if (f.d != 65535) return 4;
    return 0;
}

/* Test 3: bitfield masking (value exceeds width) */
int test_mask() {
    struct Flags f;
    f.a = 3;  /* 3 & 1 = 1 */
    f.b = 15; /* 15 & 7 = 7 */
    if (f.a != 1) return 1;
    if (f.b != 7) return 2;
    return 0;
}

/* Test 4: mixed bitfield and regular field */
struct Mixed {
    int x : 8;
    int y : 8;
    int z;
};

int test_mixed() {
    struct Mixed m;
    m.x = 42;
    m.y = 99;
    m.z = 12345;
    if (m.x != 42) return 1;
    if (m.y != 99) return 2;
    if (m.z != 12345) return 3;
    return 0;
}

int main() {
    int fail = 0;

    int r = test_basic();
    if (r != 0) { printf("FAIL: test_basic step %d\n", r); fail = 1; }

    r = test_overwrite();
    if (r != 0) { printf("FAIL: test_overwrite step %d\n", r); fail = 1; }

    r = test_mask();
    if (r != 0) { printf("FAIL: test_mask step %d\n", r); fail = 1; }

    r = test_mixed();
    if (r != 0) { printf("FAIL: test_mixed step %d\n", r); fail = 1; }

    if (fail == 0) printf("test_batch26 passed\n");
    return fail;
}
