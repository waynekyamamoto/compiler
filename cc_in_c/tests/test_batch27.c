// Test batch 27: Function-like macros
#define DOUBLE(x) ((x) * 2)
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define ADD3(a,b,c) ((a) + (b) + (c))
#define EMPTY() 42
#define IDENTITY(x) (x)
#define SQUARE(x) ((x) * (x))

int printf(char *fmt, ...);

int add(int a, int b) {
    return a + b;
}

int main() {
    int fail = 0;

    // Basic single-param
    if (DOUBLE(5) != 10) { printf("FAIL: DOUBLE(5) = %d, expected 10\n", DOUBLE(5)); fail = 1; }

    // Two params
    if (MAX(3, 7) != 7) { printf("FAIL: MAX(3,7) = %d, expected 7\n", MAX(3, 7)); fail = 1; }
    if (MAX(10, 2) != 10) { printf("FAIL: MAX(10,2) = %d, expected 10\n", MAX(10, 2)); fail = 1; }

    // Three params
    if (ADD3(1, 2, 3) != 6) { printf("FAIL: ADD3(1,2,3) = %d, expected 6\n", ADD3(1, 2, 3)); fail = 1; }

    // Zero params
    if (EMPTY() != 42) { printf("FAIL: EMPTY() = %d, expected 42\n", EMPTY()); fail = 1; }

    // Nested macro: macro in argument
    if (MAX(DOUBLE(2), 3) != 4) { printf("FAIL: MAX(DOUBLE(2),3) = %d, expected 4\n", MAX(DOUBLE(2), 3)); fail = 1; }

    // Identity with function call containing commas in parens
    if (IDENTITY(add(1, 2)) != 3) { printf("FAIL: IDENTITY(add(1,2)) = %d, expected 3\n", IDENTITY(add(1, 2))); fail = 1; }

    // Square
    if (SQUARE(4) != 16) { printf("FAIL: SQUARE(4) = %d, expected 16\n", SQUARE(4)); fail = 1; }

    // Nested: DOUBLE(DOUBLE(3))
    if (DOUBLE(DOUBLE(3)) != 12) { printf("FAIL: DOUBLE(DOUBLE(3)) = %d, expected 12\n", DOUBLE(DOUBLE(3))); fail = 1; }

    if (fail == 0) {
        printf("batch27: all tests passed\n");
    }
    return fail;
}
