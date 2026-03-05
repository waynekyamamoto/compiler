// Test batch 37: Generic variadic function calls
int printf(char *fmt, ...);
int sprintf(char *buf, char *fmt, ...);
int strcmp(char *a, char *b);

int main() {
    int fail = 0;

    // Test sprintf (variadic with 2 named params)
    char buf[64];
    sprintf(buf, "val=%d", 42);
    if (strcmp(buf, "val=42") != 0) {
        printf("FAIL: sprintf produced '%s', expected 'val=42'\n", buf);
        fail = 1;
    }

    // Test sprintf with multiple variadic args
    sprintf(buf, "%d+%d=%d", 1, 2, 3);
    if (strcmp(buf, "1+2=3") != 0) {
        printf("FAIL: sprintf produced '%s', expected '1+2=3'\n", buf);
        fail = 1;
    }

    // Test printf with non-literal format string
    char *fmt = "result=%d\n";
    printf(fmt, 99);

    // Test printf with string format
    sprintf(buf, "hello %s", "world");
    if (strcmp(buf, "hello world") != 0) {
        printf("FAIL: sprintf produced '%s', expected 'hello world'\n", buf);
        fail = 1;
    }

    if (fail == 0) {
        printf("batch37: all tests passed\n");
    }
    return fail;
}
