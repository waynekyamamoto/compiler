// Test batch 54: __LINE__ and __FILE__
int printf(int *fmt, ...);

int main() {
    int line1 = __LINE__;
    if (line1 != 5) { printf("FAIL: __LINE__ expected 5, got %d\n", line1); return 1; }

    int line2 = __LINE__;
    if (line2 != 8) { printf("FAIL: __LINE__ expected 8, got %d\n", line2); return 1; }

    // __FILE__ should be a string
    int *file = __FILE__;
    printf("file = %s\n", file);

    printf("batch54: all tests passed\n");
    return 0;
}
