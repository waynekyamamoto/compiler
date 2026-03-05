// Test batch 49: typedef union
int printf(int *fmt, ...);
int *malloc(int size);

typedef union {
    int i;
    int *p;
} Val;

int test_typedef_union_basic() {
    Val v;
    v.i = 42;
    if (v.i != 42) return 1;
    return 0;
}

int test_typedef_union_ptr_field() {
    Val v;
    int x = 99;
    v.p = &x;
    if (*v.p != 99) return 1;
    return 0;
}

int test_typedef_union_pointer() {
    Val *vp = malloc(8);
    vp->i = 77;
    if (vp->i != 77) return 1;
    return 0;
}

typedef union {
    int tag;
    int val;
} Simple;

int test_typedef_union_overwrite() {
    Simple s;
    s.tag = 1;
    s.val = 2;
    // Both fields share same memory, so val overwrites tag
    if (s.val != 2) return 1;
    if (s.tag != 2) return 2;
    return 0;
}

int get_val(Val v) {
    return v.i;
}

int test_typedef_union_param() {
    Val v;
    v.i = 55;
    if (get_val(v) != 55) return 1;
    return 0;
}

int main() {
    int fail = 0;
    if (test_typedef_union_basic()) { printf("FAIL: typedef_union_basic\n"); fail = 1; }
    if (test_typedef_union_ptr_field()) { printf("FAIL: typedef_union_ptr_field\n"); fail = 1; }
    if (test_typedef_union_pointer()) { printf("FAIL: typedef_union_pointer\n"); fail = 1; }
    if (test_typedef_union_overwrite()) { printf("FAIL: typedef_union_overwrite\n"); fail = 1; }
    if (test_typedef_union_param()) { printf("FAIL: typedef_union_param\n"); fail = 1; }
    if (!fail) printf("batch49: all tests passed\n");
    return fail;
}
