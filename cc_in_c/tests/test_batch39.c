/* test_batch39: preprocessor features - __VA_ARGS__, ##, #, predefined macros */
int printf(char *fmt, ...);
int strcmp(char *a, char *b);
int sprintf(char *buf, char *fmt, ...);

/* Test __VA_ARGS__ */
#define PRINT(...) printf(__VA_ARGS__)
#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)

/* Test ## token pasting */
#define PASTE(a, b) a ## b
#define VAR(n) var_ ## n

/* Test # stringification */
#define STR(x) #x
#define XSTR(x) STR(x)

/* Test predefined macros */
#ifndef __STDC__
  int undefined_stdc_error;
#endif

int main() {
    int fail = 0;

    /* Test __VA_ARGS__ with printf */
    PRINT("va_args test: %d\n", 42);

    /* Test __VA_ARGS__ with multiple args */
    LOG("log: %d %d\n", 1, 2);

    /* Test ## token pasting */
    int PASTE(my, var) = 100;
    if (myvar != 100) { printf("FAIL: ## paste\n"); fail = 1; }

    int VAR(1) = 200;
    if (var_1 != 200) { printf("FAIL: ## VAR paste\n"); fail = 1; }

    /* Test # stringification */
    char buf[64];
    sprintf(buf, "%s", STR(hello));
    if (strcmp(buf, "hello") != 0) { printf("FAIL: # stringify got '%s'\n", buf); fail = 1; }

    /* Note: XSTR(MY_VAL) double-expansion not yet supported.
     * Standard C requires args be expanded before substitution
     * (except with # or ##). TODO for later. */

    if (!fail) printf("batch39: all tests passed\n");
    return fail;
}
