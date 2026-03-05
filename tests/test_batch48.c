int printf(char *fmt, ...);
void *malloc(int size);

/* --- Test 1: Struct copy via initialization --- */
struct Pair { int a; int b; };

int test_struct_copy_init() {
    struct Pair p1;
    p1.a = 10;
    p1.b = 20;
    struct Pair p2 = p1;
    return p2.a + p2.b; /* 30 */
}

/* --- Test 2: sizeof on struct variable --- */
struct Triple { int x; int y; int z; };

int test_sizeof_var() {
    struct Triple t;
    return sizeof(t); /* 12 */
}

/* --- Test 3: sizeof on struct type --- */
int test_sizeof_struct() {
    return sizeof(struct Pair); /* 8 */
}

/* --- Test 4: char pointer indexing --- */
int test_char_ptr_index() {
    char *s = "ABCDE";
    return s[0] + s[4]; /* 65 + 69 = 134 */
}

/* --- Test 5: char pointer dereference --- */
int test_char_ptr_deref() {
    char *s = "Hello";
    int c = *s;
    return c; /* 72 = 'H' */
}

/* --- Test 6: char pointer arithmetic --- */
int test_char_ptr_arith() {
    char *s = "ABCDE";
    char *p = s + 2;
    return *p; /* 67 = 'C' */
}

/* --- Test 7: strlen using char* --- */
int my_strlen(char *s) {
    int n = 0;
    while (s[n]) n = n + 1;
    return n;
}

int test_strlen() {
    return my_strlen("hello world"); /* 11 */
}

/* --- Test 8: strcmp using char* --- */
int my_strcmp(char *a, char *b) {
    int i = 0;
    while (a[i] && b[i]) {
        if (a[i] != b[i]) return a[i] - b[i];
        i = i + 1;
    }
    return a[i] - b[i];
}

int test_strcmp() {
    if (my_strcmp("abc", "abc") != 0) return 0;
    if (my_strcmp("abc", "abd") >= 0) return 0;
    if (my_strcmp("abd", "abc") <= 0) return 0;
    return 1;
}

/* --- Test 9: strcpy using char* and malloc --- */
void my_strcpy(char *dst, char *src) {
    int i = 0;
    while (src[i]) {
        dst[i] = src[i];
        i = i + 1;
    }
    dst[i] = 0;
}

int test_strcpy() {
    char *buf = malloc(32);
    my_strcpy(buf, "world");
    return my_strlen(buf); /* 5 */
}

/* --- Test 10: struct vardecl with expression init (not init list) --- */
int test_struct_expr_init() {
    struct Pair p1;
    p1.a = 100;
    p1.b = 200;
    struct Pair p2;
    p2 = p1;
    struct Pair p3 = p2;
    return p3.a + p3.b; /* 300 */
}

int main() {
    int fail = 0;
    if (test_struct_copy_init() != 30) { printf("FAIL: struct_copy %d\n", test_struct_copy_init()); fail = 1; }
    if (test_sizeof_var() != 12) { printf("FAIL: sizeof_var %d\n", test_sizeof_var()); fail = 1; }
    if (test_sizeof_struct() != 8) { printf("FAIL: sizeof_struct %d\n", test_sizeof_struct()); fail = 1; }
    if (test_char_ptr_index() != 134) { printf("FAIL: char_index %d\n", test_char_ptr_index()); fail = 1; }
    if (test_char_ptr_deref() != 72) { printf("FAIL: char_deref %d\n", test_char_ptr_deref()); fail = 1; }
    if (test_char_ptr_arith() != 67) { printf("FAIL: char_arith %d\n", test_char_ptr_arith()); fail = 1; }
    if (test_strlen() != 11) { printf("FAIL: strlen %d\n", test_strlen()); fail = 1; }
    if (test_strcmp() != 1) { printf("FAIL: strcmp %d\n", test_strcmp()); fail = 1; }
    if (test_strcpy() != 5) { printf("FAIL: strcpy %d\n", test_strcpy()); fail = 1; }
    if (test_struct_expr_init() != 300) { printf("FAIL: struct_expr %d\n", test_struct_expr_init()); fail = 1; }
    if (fail == 0) printf("batch48: all tests passed\n");
    return fail;
}
