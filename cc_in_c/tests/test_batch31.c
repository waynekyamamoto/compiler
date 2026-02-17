// Test batch 31: Backslash line continuation
int printf(char *fmt, ...);

#define BIG (1 + \
  2 + 3)

#define ADD(a, b) \
  ((a) + (b))

#define TRIPLE(x) \
  ((x) + \
   (x) + \
   (x))

int main() {
    int fail = 0;

    // Multi-line object macro
    if (BIG != 6) { printf("FAIL: BIG = %d, expected 6\n", BIG); fail = 1; }

    // Multi-line function macro
    if (ADD(10, 20) != 30) { printf("FAIL: ADD(10,20) = %d, expected 30\n", ADD(10, 20)); fail = 1; }

    // 3-line continuation
    if (TRIPLE(5) != 15) { printf("FAIL: TRIPLE(5) = %d, expected 15\n", TRIPLE(5)); fail = 1; }

    if (fail == 0) {
        printf("batch31: all tests passed\n");
    }
    return fail;
}
