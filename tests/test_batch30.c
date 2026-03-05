// Test batch 30: Multi-dimensional arrays
int printf(char *fmt, ...);

int main() {
    int fail = 0;

    // Declare and fill 2D array
    int arr[3][4];
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            arr[i][j] = k;
            k++;
        }
    }

    // Read back and verify
    if (arr[0][0] != 0) { printf("FAIL: arr[0][0] = %d, expected 0\n", arr[0][0]); fail = 1; }
    if (arr[0][3] != 3) { printf("FAIL: arr[0][3] = %d, expected 3\n", arr[0][3]); fail = 1; }
    if (arr[1][0] != 4) { printf("FAIL: arr[1][0] = %d, expected 4\n", arr[1][0]); fail = 1; }
    if (arr[2][3] != 11) { printf("FAIL: arr[2][3] = %d, expected 11\n", arr[2][3]); fail = 1; }

    // Nested loop sum
    int sum = 0;
    for (int i2 = 0; i2 < 3; i2++) {
        for (int j2 = 0; j2 < 4; j2++) {
            sum = sum + arr[i2][j2];
        }
    }
    // sum should be 0+1+...+11 = 66
    if (sum != 66) { printf("FAIL: sum = %d, expected 66\n", sum); fail = 1; }

    // 2x2 array
    int m[2][2];
    m[0][0] = 10;
    m[0][1] = 20;
    m[1][0] = 30;
    m[1][1] = 40;
    if (m[0][0] + m[1][1] != 50) { printf("FAIL: m[0][0]+m[1][1] = %d, expected 50\n", m[0][0] + m[1][1]); fail = 1; }

    if (fail == 0) {
        printf("batch30: all tests passed\n");
    }
    return fail;
}
