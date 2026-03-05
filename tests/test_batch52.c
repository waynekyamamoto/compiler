// Test batch 52: typedef union used as local variable type
int printf(int *fmt, ...);
int *malloc(int size);

typedef union {
    int ival;
    int *pval;
} MyVal;

typedef union {
    int tag;
    int data;
} SimpleU;

int test_typedef_union_local() {
    MyVal v;
    v.ival = 42;
    if (v.ival != 42) return 1;
    v.pval = 0;
    if (v.pval != 0) return 2;
    return 0;
}

int test_typedef_union_ptr() {
    MyVal *p = malloc(8);
    p->ival = 77;
    if (p->ival != 77) return 1;
    return 0;
}

int sum_val(MyVal a, MyVal b) {
    return a.ival + b.ival;
}

int test_typedef_union_param() {
    MyVal a;
    MyVal b;
    a.ival = 10;
    b.ival = 20;
    if (sum_val(a, b) != 30) return 1;
    return 0;
}

int test_multiple_typedef_unions() {
    MyVal v;
    SimpleU s;
    v.ival = 5;
    s.tag = 1;
    s.data = 99;
    if (v.ival != 5) return 1;
    // union semantics: tag and data share offset
    if (s.data != 99) return 2;
    return 0;
}

int main() {
    int fail = 0;
    int r;
    r = test_typedef_union_local();
    if (r) { printf("FAIL: typedef_union_local step %d\n", r); fail = 1; }
    r = test_typedef_union_ptr();
    if (r) { printf("FAIL: typedef_union_ptr step %d\n", r); fail = 1; }
    r = test_typedef_union_param();
    if (r) { printf("FAIL: typedef_union_param step %d\n", r); fail = 1; }
    r = test_multiple_typedef_unions();
    if (r) { printf("FAIL: multiple_typedef_unions step %d\n", r); fail = 1; }
    if (!fail) printf("batch52: all tests passed\n");
    return fail;
}
