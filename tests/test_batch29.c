// Test batch 29: Unsigned comparisons
int printf(char *fmt, ...);

int main() {
    int fail = 0;

    // 0xFFFFFFFF as unsigned should be > 0
    unsigned int a = 0xFFFFFFFF;
    if (a > 0) {
        // good: unsigned comparison treats as large positive
    } else {
        printf("FAIL: unsigned 0xFFFFFFFF should be > 0\n");
        fail = 1;
    }

    // Unsigned comparison between two large values
    unsigned int b = 0xFFFFFFFE;
    if (a > b) {
        // good: 0xFFFFFFFF > 0xFFFFFFFE
    } else {
        printf("FAIL: 0xFFFFFFFF should be > 0xFFFFFFFE (unsigned)\n");
        fail = 1;
    }

    // Unsigned >= test
    unsigned int c = 100;
    unsigned int d = 100;
    if (c >= d) {
        // good
    } else {
        printf("FAIL: 100 >= 100 (unsigned) should be true\n");
        fail = 1;
    }

    // Unsigned < test
    unsigned int e = 5;
    unsigned int f = 10;
    if (e < f) {
        // good
    } else {
        printf("FAIL: 5 < 10 (unsigned) should be true\n");
        fail = 1;
    }

    // Unsigned <= test
    if (e <= f) {
        // good
    } else {
        printf("FAIL: 5 <= 10 (unsigned) should be true\n");
        fail = 1;
    }

    // Verify signed int treats 0xFFFFFFFF as -1
    int sa = 0xFFFFFFFF;
    if (sa < 0) {
        // good: signed interpretation, -1 < 0
    } else {
        printf("FAIL: signed 0xFFFFFFFF should be < 0 (is -1)\n");
        fail = 1;
    }

    if (fail == 0) {
        printf("batch29: all tests passed\n");
    }
    return fail;
}
