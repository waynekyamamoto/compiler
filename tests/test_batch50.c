// Test batch 50: union inside struct
int printf(int *fmt, ...);
int *malloc(int size);

// Basic: struct containing a union field
struct Tagged {
    int tag;
    union ValU {
        int i;
        int *p;
    } val;
    int extra;
};

int test_union_in_struct_basic() {
    struct Tagged t;
    t.tag = 1;
    t.val.i = 42;
    t.extra = 99;
    if (t.tag != 1) return 1;
    if (t.val.i != 42) return 2;
    if (t.extra != 99) return 3;
    // Union semantics: writing to .p should overwrite .i since they share offset 0
    t.val.p = 0;
    if (t.val.i != 0) return 4;
    return 0;
}

int test_union_in_struct_ptr() {
    struct Tagged *p = malloc(24);
    p->tag = 2;
    p->val.i = 100;
    p->extra = 200;
    if (p->tag != 2) return 1;
    if (p->val.i != 100) return 2;
    if (p->extra != 200) return 3;
    return 0;
}

// The embedded union should be usable independently
int test_standalone_union() {
    union ValU v;
    v.i = 55;
    if (v.i != 55) return 1;
    v.p = 0;
    if (v.p != 0) return 2;
    return 0;
}

int main() {
    int fail = 0;
    int r;
    r = test_union_in_struct_basic();
    if (r) { printf("FAIL: union_in_struct_basic step %d\n", r); fail = 1; }
    r = test_union_in_struct_ptr();
    if (r) { printf("FAIL: union_in_struct_ptr step %d\n", r); fail = 1; }
    r = test_standalone_union();
    if (r) { printf("FAIL: standalone_union step %d\n", r); fail = 1; }
    if (!fail) printf("batch50: all tests passed\n");
    return fail;
}
