/* Test batch 15: function pointer declarations with proper syntax */
int printf(char *fmt, ...);

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

/* --- Local function pointer variable --- */
int test_local_funcptr() {
    int (*fp)(int, int) = add;
    return fp(3, 4);
}

/* --- Reassign function pointer --- */
int test_reassign_funcptr() {
    int (*op)(int, int) = add;
    int r1 = op(10, 5);
    op = sub;
    int r2 = op(10, 5);
    return r1 * 100 + r2;
}

/* --- Function pointer as function parameter --- */
int apply(int (*fn)(int, int), int x, int y) {
    return fn(x, y);
}

int test_funcptr_param() {
    return apply(add, 6, 7);
}

/* --- Typedef function pointer --- */
typedef int (*BinOp)(int, int);

int apply2(BinOp fn, int x, int y) {
    return fn(x, y);
}

int test_typedef_funcptr() {
    BinOp op = mul;
    return apply2(op, 3, 5);
}

/* --- Function pointer in struct --- */
struct Calculator {
    int (*op)(int, int);
    int result;
};

int test_struct_funcptr() {
    struct Calculator c;
    c.op = add;
    c.result = c.op(20, 22);
    return c.result;
}

/* --- Array of function pointers (using int* syntax, existing) --- */
int test_funcptr_array() {
    int *ops[3];
    ops[0] = add;
    ops[1] = sub;
    ops[2] = mul;
    int r0 = ((int (*)(int, int))ops[0])(10, 3);
    int r1 = ((int (*)(int, int))ops[1])(10, 3);
    int r2 = ((int (*)(int, int))ops[2])(10, 3);
    return r0 + r1 + r2;
}

/* --- Function pointer via typedef returning pointer --- */
int *identity(int *p) { return p; }
typedef int *(*PtrFn)(int *);

int test_funcptr_ret_ptr() {
    PtrFn fp = identity;
    int val = 99;
    int *result = fp(&val);
    return *result;
}

/* --- Callback pattern --- */
int transform(int *arr, int n, int (*fn)(int, int)) {
    int sum = 0;
    int i = 0;
    while (i < n) {
        sum = fn(sum, arr[i]);
        i = i + 1;
    }
    return sum;
}

int test_callback() {
    int arr[4];
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    return transform(arr, 4, add);
}

int main() {
    int fail = 0;

    if (test_local_funcptr() != 7) { printf("FAIL: local funcptr\n"); fail = 1; }
    if (test_reassign_funcptr() != 1505) { printf("FAIL: reassign funcptr\n"); fail = 1; }
    if (test_funcptr_param() != 13) { printf("FAIL: funcptr param\n"); fail = 1; }
    if (test_typedef_funcptr() != 15) { printf("FAIL: typedef funcptr\n"); fail = 1; }
    if (test_struct_funcptr() != 42) { printf("FAIL: struct funcptr\n"); fail = 1; }
    if (test_funcptr_array() != 50) { printf("FAIL: funcptr array\n"); fail = 1; }
    if (test_funcptr_ret_ptr() != 99) { printf("FAIL: funcptr ret ptr\n"); fail = 1; }
    if (test_callback() != 10) { printf("FAIL: callback\n"); fail = 1; }

    if (!fail) printf("All batch 15 tests passed.\n");
    return fail;
}
