// Test batch 55: statement expressions ({...})
int printf(int *fmt, ...);

int main() {
    int x = ({ 1 + 2; });
    if (x != 3) { printf("FAIL: stmt expr got %d expected 3\n", x); return 1; }

    int y = ({
        int a = 10;
        int b = 20;
        a + b;
    });
    if (y != 30) { printf("FAIL: stmt expr got %d expected 30\n", y); return 1; }

    // Statement expression with side effects
    int z = 0;
    int w = ({ z = 42; z * 2; });
    if (z != 42) { printf("FAIL: side effect z=%d expected 42\n", z); return 1; }
    if (w != 84) { printf("FAIL: stmt expr w=%d expected 84\n", w); return 1; }

    printf("batch55: all tests passed\n");
    return 0;
}
