int printf(int *fmt, ...);
int strcmp(int *s1, int *s2);

// ============ Stringify tests ============
#define STR(x) #x

// ============ Token paste tests ============
#define CONCAT(a, b) a ## b
#define CONCAT3(a, b, c) a ## b ## c
#define PASTE_VAR(prefix, num) prefix ## num
#define MAKE_FUNC(name) test_ ## name
#define TYPE_NAME(t, n) t ## _ ## n

// ============ Combined tests ============
#define STR_PASTE(a, b) #a "_" #b

int PASTE_VAR(global, 1) = 100;
int PASTE_VAR(global, 2) = 200;
int TYPE_NAME(my, var) = 333;

int MAKE_FUNC(add)(int a, int b) { return a + b; }

int main() {
    int fail = 0;

    // --- Stringify basic identifier ---
    int *s1 = STR(hello);
    if (strcmp(s1, "hello") != 0) { printf("FAIL: STR(hello) = '%s'\n", s1); fail = 1; }

    // --- Stringify with expression (spaces/operators) ---
    int *s2 = STR(1 + 2);
    if (strcmp(s2, "1 + 2") != 0) { printf("FAIL: STR(1 + 2) = '%s'\n", s2); fail = 1; }

    // --- Stringify with underscore ---
    int *s3 = STR(a_b);
    if (strcmp(s3, "a_b") != 0) { printf("FAIL: STR(a_b) = '%s'\n", s3); fail = 1; }

    // --- Token paste: two identifiers ---
    int xy = 42;
    if (CONCAT(x, y) != 42) { printf("FAIL: CONCAT(x,y) = %d\n", CONCAT(x, y)); fail = 1; }

    // --- Token paste: identifier + number ---
    int var3 = 99;
    if (PASTE_VAR(var, 3) != 99) { printf("FAIL: PASTE_VAR(var,3)\n"); fail = 1; }

    // --- Token paste: global vars ---
    if (global1 != 100) { printf("FAIL: global1 = %d\n", global1); fail = 1; }
    if (global2 != 200) { printf("FAIL: global2 = %d\n", global2); fail = 1; }

    // --- Token paste: function name ---
    if (test_add(3, 4) != 7) { printf("FAIL: test_add(3,4) = %d\n", test_add(3, 4)); fail = 1; }

    // --- Triple paste ---
    int abc = 55;
    if (CONCAT3(a, b, c) != 55) { printf("FAIL: CONCAT3(a,b,c)\n"); fail = 1; }

    // --- Paste with underscore separator ---
    if (my_var != 333) { printf("FAIL: my_var = %d\n", my_var); fail = 1; }

    // --- Stringify + paste combined (adjacent string literals) ---
    int *sp = STR_PASTE(hello, world);
    if (strcmp(sp, "hello" "_" "world") != 0) { printf("FAIL: STR_PASTE = '%s'\n", sp); fail = 1; }

    // --- Token paste in local var ---
    int CONCAT(local, Var) = 77;
    if (localVar != 77) { printf("FAIL: localVar = %d\n", localVar); fail = 1; }

    if (fail == 0) {
        printf("All stringify/paste tests passed!\n");
    }
    return fail;
}
