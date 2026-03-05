int printf(char *fmt, ...);

// Test 1: Unary plus operator
int test_unary_plus() {
    int x = +5;
    int y = +x;
    if (y != 5) { printf("FAIL test_unary_plus: expected 5, got %d\n", y); return 1; }
    if (+(-3) != -3) { printf("FAIL test_unary_plus: +(-3) != -3\n"); return 1; }
    printf("PASS test_unary_plus\n");
    return 0;
}

// Test 2: Comma operator in for-loop init and update
int test_comma_for() {
    int i;
    int j;
    int sum = 0;
    for (i = 0, j = 10; i < 5; i = i + 1, j = j - 2) {
        sum = sum + i + j;
    }
    // i: 0,1,2,3,4  j: 10,8,6,4,2  => pairs sum = 10+9+8+7+6 = 40
    if (sum != 40) { printf("FAIL test_comma_for: expected 40, got %d\n", sum); return 1; }
    printf("PASS test_comma_for\n");
    return 0;
}

// Test 3: String literal concatenation
int test_string_concat() {
    char *s = "hello" " " "world";
    // Check first 11 chars manually
    int ok = 1;
    char *expected = "hello world";
    int i = 0;
    while (i < 11) {
        if (*s != *expected) { ok = 0; }
        s = s + 1;
        expected = expected + 1;
        i = i + 1;
    }
    if (!ok) { printf("FAIL test_string_concat\n"); return 1; }
    printf("PASS test_string_concat\n");
    return 0;
}

// Test 4: Empty statement
int test_empty_stmt() {
    int x = 0;
    ;
    ;
    x = 1;
    if (x != 1) { printf("FAIL test_empty_stmt\n"); return 1; }
    printf("PASS test_empty_stmt\n");
    return 0;
}

// Test 5: Void return (return;)
int g_void_ret = 0;
void set_if_positive(int x) {
    if (x <= 0) return;
    g_void_ret = x;
}

int test_void_return() {
    g_void_ret = 0;
    set_if_positive(-5);
    if (g_void_ret != 0) { printf("FAIL test_void_return: expected 0, got %d\n", g_void_ret); return 1; }
    set_if_positive(42);
    if (g_void_ret != 42) { printf("FAIL test_void_return: expected 42, got %d\n", g_void_ret); return 1; }
    printf("PASS test_void_return\n");
    return 0;
}

// Test 6: Comma expression value
int test_comma_expr() {
    int x = (1, 2, 3);
    if (x != 3) { printf("FAIL test_comma_expr: expected 3, got %d\n", x); return 1; }
    printf("PASS test_comma_expr\n");
    return 0;
}

// Test 7: Multi-line string concat in printf
int test_string_concat_printf() {
    // Use string concat with printf format
    printf("PASS test_" "string_" "concat_printf\n");
    return 0;
}

// Test 8: Anonymous block scope
int test_anon_block() {
    int x = 1;
    {
        int y = 2;
        x = x + y;
    }
    if (x != 3) { printf("FAIL test_anon_block: expected 3, got %d\n", x); return 1; }
    // Nested blocks
    {
        {
            x = x + 10;
        }
    }
    if (x != 13) { printf("FAIL test_anon_block: expected 13, got %d\n", x); return 1; }
    printf("PASS test_anon_block\n");
    return 0;
}

// Test 9: Global string initialization
char *g_str = "global string test";
int test_global_string() {
    // Verify pointer is non-null and prints correctly
    if (g_str == 0) { printf("FAIL test_global_string: null pointer\n"); return 1; }
    printf("PASS test_global_string\n");
    return 0;
}

int main() {
    int fail = 0;
    fail = fail + test_unary_plus();
    fail = fail + test_comma_for();
    fail = fail + test_string_concat();
    fail = fail + test_empty_stmt();
    fail = fail + test_void_return();
    fail = fail + test_comma_expr();
    fail = fail + test_string_concat_printf();
    fail = fail + test_anon_block();
    fail = fail + test_global_string();
    if (fail != 0) {
        printf("FAILED %d tests\n", fail);
        return 1;
    }
    printf("All batch 45 tests passed\n");
    return 0;
}
