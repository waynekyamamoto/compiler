// Test batch 28: Proper sizeof
int printf(char *fmt, ...);

struct Point {
    int x;
    int y;
};

struct Triple {
    int a;
    int b;
    int c;
};

int main() {
    int fail = 0;

    // sizeof(int) == 4
    if (sizeof(int) != 4) { printf("FAIL: sizeof(int) = %d, expected 4\n", sizeof(int)); fail = 1; }

    // sizeof(char) == 1
    if (sizeof(char) != 1) { printf("FAIL: sizeof(char) = %d, expected 1\n", sizeof(char)); fail = 1; }

    // sizeof(int *) == 8
    if (sizeof(int *) != 8) { printf("FAIL: sizeof(int*) = %d, expected 8\n", sizeof(int *)); fail = 1; }

    // sizeof(char *) == 8
    if (sizeof(char *) != 8) { printf("FAIL: sizeof(char*) = %d, expected 8\n", sizeof(char *)); fail = 1; }

    // sizeof(struct Point) == 8 (2 ints * 4)
    if (sizeof(struct Point) != 8) { printf("FAIL: sizeof(struct Point) = %d, expected 8\n", sizeof(struct Point)); fail = 1; }

    // sizeof(struct Triple) == 12 (3 ints * 4)
    if (sizeof(struct Triple) != 12) { printf("FAIL: sizeof(struct Triple) = %d, expected 12\n", sizeof(struct Triple)); fail = 1; }

    // sizeof(int[10]) == 40 (10 * 4)
    if (sizeof(int[10]) != 40) { printf("FAIL: sizeof(int[10]) = %d, expected 40\n", sizeof(int[10])); fail = 1; }

    // sizeof(long) == 8
    if (sizeof(long) != 8) { printf("FAIL: sizeof(long) = %d, expected 8\n", sizeof(long)); fail = 1; }

    // sizeof(void *) == 8
    if (sizeof(void *) != 8) { printf("FAIL: sizeof(void*) = %d, expected 8\n", sizeof(void *)); fail = 1; }

    if (fail == 0) {
        printf("batch28: all tests passed\n");
    }
    return fail;
}
