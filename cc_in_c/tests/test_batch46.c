// Test batch 46: Nested macros, variadic macros, token pasting, stringify
int printf(char *fmt, ...);
int strcmp(char *a, char *b);

// Nested macro expansion
#define BASE 100
#define DERIVED BASE
#define DEEP DERIVED

// Variadic macros
#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)
#define WRAP(...) printf(__VA_ARGS__)

// Token pasting
#define PASTE(a, b) a ## b
#define MAKE_VAR(n) var_ ## n

// Stringify
#define STR(x) #x

int test_nested_macros() {
    if (DERIVED != 100) return 1;
    if (DEEP != 100) return 2;
    return 0;
}

int test_variadic_macros() {
    // Just check it compiles and runs
    LOG("log: %d\n", 42);
    WRAP("wrap: %d %d\n", 1, 2);
    return 0;
}

int test_token_pasting() {
    int xy = 42;
    if (PASTE(x, y) != 42) return 1;
    int var_1 = 10;
    int var_2 = 20;
    if (MAKE_VAR(1) != 10) return 2;
    if (MAKE_VAR(2) != 20) return 3;
    return 0;
}

int test_stringify() {
    char *s = STR(hello);
    if (strcmp(s, "hello") != 0) return 1;
    char *s2 = STR(test123);
    if (strcmp(s2, "test123") != 0) return 2;
    return 0;
}

int main() {
    int fail = 0;
    int r;

    r = test_nested_macros();
    if (r != 0) { printf("FAIL: nested_macros %d\n", r); fail = 1; }

    r = test_variadic_macros();
    if (r != 0) { printf("FAIL: variadic_macros %d\n", r); fail = 1; }

    r = test_token_pasting();
    if (r != 0) { printf("FAIL: token_pasting %d\n", r); fail = 1; }

    r = test_stringify();
    if (r != 0) { printf("FAIL: stringify %d\n", r); fail = 1; }

    if (fail == 0) printf("batch46: all tests passed\n");
    return fail;
}
