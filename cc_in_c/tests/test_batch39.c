/* Test struct layout with function pointer fields, similar to FuncDef */
#include <stdio.h>

struct Destr {
    int nRef;
    void (*xDestroy)(void*);
};

struct FuncLike {
    int nArg;
    int flags;
    void *pUserData;
    struct FuncLike *pNext;
    void (*xFunc1)(void*, int, void**);
    void (*xFunc2)(void*);
    void (*xFunc3)(void*);
    void (*xFunc4)(void*, int, void**);
    const char *zName;
    union {
        struct FuncLike *pHash;
        struct Destr *pDestructor;
    } u;
};

void dummy_func(void *a, int b, void **c) {}
void dummy_func2(void *a) {}

int main() {
    /* Test 1: sizeof struct with function pointer fields */
    int sz = sizeof(struct FuncLike);
    printf("sizeof(FuncLike)=%d expected=80\n", sz);

    /* Test 2: array of structs - check stride */
    struct FuncLike arr[2];
    arr[0].nArg = 1;
    arr[0].flags = 100;
    arr[0].pUserData = 0;
    arr[0].pNext = 0;
    arr[0].xFunc1 = dummy_func;
    arr[0].xFunc2 = dummy_func2;
    arr[0].xFunc3 = dummy_func2;
    arr[0].xFunc4 = dummy_func;
    arr[0].zName = "hello";
    arr[0].u.pHash = 0;

    arr[1].nArg = 2;
    arr[1].flags = 200;
    arr[1].pUserData = 0;
    arr[1].pNext = 0;
    arr[1].xFunc1 = dummy_func;
    arr[1].xFunc2 = dummy_func2;
    arr[1].xFunc3 = dummy_func2;
    arr[1].xFunc4 = dummy_func;
    arr[1].zName = "world";
    arr[1].u.pHash = 0;

    /* Test 3: access fields through array indexing */
    printf("arr[0].nArg=%d expected=1\n", arr[0].nArg);
    printf("arr[0].zName=%s expected=hello\n", arr[0].zName);
    printf("arr[1].nArg=%d expected=2\n", arr[1].nArg);
    printf("arr[1].zName=%s expected=world\n", arr[1].zName);

    /* Test 4: access through pointer */
    struct FuncLike *p = arr;
    printf("p[0].zName=%s expected=hello\n", p[0].zName);
    printf("p[1].zName=%s expected=world\n", p[1].zName);

    /* Test 5: stride check */
    long stride = (long)&arr[1] - (long)&arr[0];
    printf("stride=%ld expected=80\n", stride);

    printf("PASS\n");
    return 0;
}
