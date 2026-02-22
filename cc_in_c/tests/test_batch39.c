/* Test struct layout with many fields including pointer fields */
/* Rewritten to avoid gen3-unsupported features: void, union, const, <includes> */
int printf(char *fmt, ...);

struct FuncLike {
    int nArg;
    int flags;
    int *pUserData;
    struct FuncLike *pNext;
    int *xFunc1;
    int *xFunc2;
    int *xFunc3;
    int *xFunc4;
    char *zName;
    int *uField;
};

int main() {
    int fail = 0;

    /* Test 1: sizeof struct with 10 pointer/int fields = 80 bytes */
    int sz = sizeof(struct FuncLike);
    if (sz != 80) {
        printf("FAIL: sizeof(FuncLike)=%d expected=80\n", sz);
        fail = 1;
    }

    /* Test 2: array of structs - field access */
    struct FuncLike arr[2];
    arr[0].nArg = 1;
    arr[0].flags = 100;
    arr[0].pUserData = 0;
    arr[0].pNext = 0;
    arr[0].xFunc1 = 0;
    arr[0].xFunc2 = 0;
    arr[0].xFunc3 = 0;
    arr[0].xFunc4 = 0;
    arr[0].zName = "hello";
    arr[0].uField = 0;

    arr[1].nArg = 2;
    arr[1].flags = 200;
    arr[1].pUserData = 0;
    arr[1].pNext = 0;
    arr[1].xFunc1 = 0;
    arr[1].xFunc2 = 0;
    arr[1].xFunc3 = 0;
    arr[1].xFunc4 = 0;
    arr[1].zName = "world";
    arr[1].uField = 0;

    /* Test 3: access fields through array indexing */
    if (arr[0].nArg != 1) {
        printf("FAIL: arr[0].nArg=%d expected=1\n", arr[0].nArg);
        fail = 1;
    }
    if (arr[1].nArg != 2) {
        printf("FAIL: arr[1].nArg=%d expected=2\n", arr[1].nArg);
        fail = 1;
    }
    if (arr[0].flags != 100) {
        printf("FAIL: arr[0].flags=%d expected=100\n", arr[0].flags);
        fail = 1;
    }
    if (arr[1].flags != 200) {
        printf("FAIL: arr[1].flags=%d expected=200\n", arr[1].flags);
        fail = 1;
    }

    /* Test 4: access through pointer */
    struct FuncLike *p = arr;
    if (p[0].nArg != 1) {
        printf("FAIL: p[0].nArg=%d expected=1\n", p[0].nArg);
        fail = 1;
    }
    if (p[1].nArg != 2) {
        printf("FAIL: p[1].nArg=%d expected=2\n", p[1].nArg);
        fail = 1;
    }

    /* Test 5: stride check */
    long stride = (long)&arr[1] - (long)&arr[0];
    if (stride != 80) {
        printf("FAIL: stride=%ld expected=80\n", stride);
        fail = 1;
    }

    if (fail == 0) {
        printf("batch39: all tests passed\n");
    }
    return fail;
}
