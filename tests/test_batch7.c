/* test_batch7.c — Union tests */

int printf(int *fmt, ...);

union IntOrPtr {
    int val;
    int *ptr;
};

union Single {
    int x;
};

int test_union_basic() {
    union IntOrPtr u;
    u.val = 42;
    if (u.val != 42) { return 1; }
    return 0;
}

int test_union_ptr() {
    union IntOrPtr u;
    int x;
    x = 99;
    u.ptr = &x;
    if (*u.ptr != 99) { return 1; }
    return 0;
}

int test_union_overwrite() {
    union IntOrPtr u;
    u.val = 123;
    u.val = 456;
    if (u.val != 456) { return 1; }
    return 0;
}

int test_union_single() {
    union Single s;
    s.x = 77;
    if (s.x != 77) { return 1; }
    return 0;
}

int test_union_arrow() {
    union IntOrPtr u;
    union IntOrPtr *p;
    u.val = 55;
    p = &u;
    if (p->val != 55) { return 1; }
    p->val = 66;
    if (u.val != 66) { return 1; }
    return 0;
}

int main() {
    int fail;
    fail = 0;

    if (test_union_basic()) { printf("FAIL: union basic\n"); fail = 1; }
    if (test_union_ptr()) { printf("FAIL: union ptr\n"); fail = 1; }
    if (test_union_overwrite()) { printf("FAIL: union overwrite\n"); fail = 1; }
    if (test_union_single()) { printf("FAIL: union single\n"); fail = 1; }
    if (test_union_arrow()) { printf("FAIL: union arrow\n"); fail = 1; }

    if (!fail) { printf("batch7: all tests passed\n"); }
    return fail;
}
