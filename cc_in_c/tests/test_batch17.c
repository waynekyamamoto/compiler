/* Test batch 17: struct initializers and string initializers for char arrays */
int printf(char *fmt, ...);
int strlen(char *s);

/* --- Struct definitions --- */
struct Point { int x; int y; };
struct Color { int r; int g; int b; };

/* --- Basic struct initializer --- */
int test_struct_init() {
    struct Point p = {10, 20};
    return p.x * 100 + p.y;
}

/* --- Struct init with expressions --- */
int test_struct_init_expr() {
    int a = 5;
    int b = 7;
    struct Point p = {a + b, a * b};
    return p.x * 100 + p.y;
}

/* --- Three-field struct --- */
int test_struct_init_3() {
    struct Color c = {255, 128, 64};
    return c.r + c.g + c.b;
}

/* --- Modify after init --- */
int test_struct_modify() {
    struct Point p = {1, 2};
    p.x = 99;
    return p.x + p.y;
}

/* --- Local char array with string init --- */
int test_char_array_local() {
    char s[] = "hello";
    return s[0]; /* 'h' = 104 */
}

/* --- Char array indexing --- */
int test_char_array_index() {
    char msg[] = "ABCD";
    return msg[0] + msg[1] + msg[2] + msg[3]; /* 65+66+67+68 = 266 */
}

/* --- Char array null terminator --- */
int test_char_null_term() {
    char s[] = "hi";
    return s[2]; /* null terminator = 0 */
}

/* --- Global char array --- */
char gstr[] = "xyz";

int test_global_char() {
    return gstr[0] + gstr[1] + gstr[2]; /* 120+121+122 = 363 */
}

/* --- Escape sequences in string init --- */
int test_escape_seq() {
    char s[] = "a\nb";
    return s[0] * 100 + s[1]; /* 'a'=97 * 100 + '\n'=10 = 9710 */
}

int main() {
    int fail = 0;

    if (test_struct_init() != 1020) { printf("FAIL: struct init (got %d)\n", test_struct_init()); fail = 1; }
    if (test_struct_init_expr() != 1235) { printf("FAIL: struct init expr (got %d)\n", test_struct_init_expr()); fail = 1; }
    if (test_struct_init_3() != 447) { printf("FAIL: struct init 3 (got %d)\n", test_struct_init_3()); fail = 1; }
    if (test_struct_modify() != 101) { printf("FAIL: struct modify (got %d)\n", test_struct_modify()); fail = 1; }
    if (test_char_array_local() != 104) { printf("FAIL: char array local (got %d)\n", test_char_array_local()); fail = 1; }
    if (test_char_array_index() != 266) { printf("FAIL: char array index (got %d)\n", test_char_array_index()); fail = 1; }
    if (test_char_null_term() != 0) { printf("FAIL: char null term (got %d)\n", test_char_null_term()); fail = 1; }
    if (test_global_char() != 363) { printf("FAIL: global char (got %d)\n", test_global_char()); fail = 1; }
    if (test_escape_seq() != 9710) { printf("FAIL: escape seq (got %d)\n", test_escape_seq()); fail = 1; }

    if (!fail) printf("All batch 17 tests passed.\n");
    return fail;
}
