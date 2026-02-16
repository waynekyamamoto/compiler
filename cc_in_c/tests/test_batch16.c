/* Test batch 16: array initializers */
int printf(char *fmt, ...);

/* --- Global initialized arrays --- */
int garr[3] = {100, 200, 300};
int garr2[] = {5, 6, 7, 8};
int gneg[] = {-1, 0, 1};

/* --- Local array with explicit size --- */
int test_local_array() {
    int arr[3] = {10, 20, 30};
    return arr[0] + arr[1] + arr[2];
}

/* --- Local array with inferred size --- */
int test_inferred_size() {
    int arr[] = {1, 2, 3, 4, 5};
    return arr[0] + arr[1] + arr[2] + arr[3] + arr[4];
}

/* --- Global array access --- */
int test_global_array() {
    return garr[0] + garr[1] + garr[2];
}

/* --- Global inferred size array --- */
int test_global_inferred() {
    return garr2[0] * 1000 + garr2[1] * 100 + garr2[2] * 10 + garr2[3];
}

/* --- Negative values in initializer --- */
int test_negative_init() {
    int neg[] = {-5, 0, 5};
    return neg[0] + neg[1] + neg[2];
}

/* --- Global negative values --- */
int test_global_negative() {
    return gneg[0] + gneg[1] + gneg[2];
}

/* --- Expression initializers --- */
int test_expr_init() {
    int a = 3;
    int b = 7;
    int arr[] = {a + b, a * b, b - a};
    return arr[0] * 100 + arr[1] * 10 + arr[2];
}

/* --- Array init with indexing and modification --- */
int test_init_and_modify() {
    int arr[4] = {1, 2, 3, 4};
    arr[2] = 99;
    return arr[0] + arr[1] + arr[2] + arr[3];
}

/* --- Pointer array init (array of pointers) --- */
int test_ptr_array_init() {
    int a = 10;
    int b = 20;
    int *ptrs[] = {&a, &b};
    return *ptrs[0] + *ptrs[1];
}

int main() {
    int fail = 0;

    if (test_local_array() != 60) { printf("FAIL: local array init (got %d)\n", test_local_array()); fail = 1; }
    if (test_inferred_size() != 15) { printf("FAIL: inferred size (got %d)\n", test_inferred_size()); fail = 1; }
    if (test_global_array() != 600) { printf("FAIL: global array (got %d)\n", test_global_array()); fail = 1; }
    if (test_global_inferred() != 5678) { printf("FAIL: global inferred (got %d)\n", test_global_inferred()); fail = 1; }
    if (test_negative_init() != 0) { printf("FAIL: negative init (got %d)\n", test_negative_init()); fail = 1; }
    if (test_global_negative() != 0) { printf("FAIL: global negative (got %d)\n", test_global_negative()); fail = 1; }
    if (test_expr_init() != 1214) { printf("FAIL: expr init (got %d)\n", test_expr_init()); fail = 1; }
    if (test_init_and_modify() != 106) { printf("FAIL: init and modify (got %d)\n", test_init_and_modify()); fail = 1; }
    if (test_ptr_array_init() != 30) { printf("FAIL: ptr array init (got %d)\n", test_ptr_array_init()); fail = 1; }

    if (!fail) printf("All batch 16 tests passed.\n");
    return fail;
}
