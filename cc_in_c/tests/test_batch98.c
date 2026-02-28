#include <stdio.h>

// Test multi-declarator globals
int ga, gb, gc;
int *gp, *gq;
int gx = 10, gy = 20, gz = 30;
long la, lb;

// Test GCC predefined type macros
typedef __SIZE_TYPE__ size_t;
typedef __INTPTR_TYPE__ intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;

int test_multi_decl() {
    ga = 1; gb = 2; gc = 3;
    if (ga + gb + gc != 6) return 1;

    gp = &ga; gq = &gb;
    if (*gp != 1) return 2;
    if (*gq != 2) return 3;

    if (gx != 10) return 4;
    if (gy != 20) return 5;
    if (gz != 30) return 6;

    la = 100; lb = 200;
    if (la + lb != 300) return 7;

    return 0;
}

int test_type_macros() {
    size_t s = sizeof(int *);
    if (s != 8) return 1;

    intptr_t ip = (intptr_t)&s;
    if (ip == 0) return 2;

    uintptr_t uip = (uintptr_t)&s;
    if (uip == 0) return 3;

    ptrdiff_t pd = 42;
    if (pd != 42) return 4;

    return 0;
}

int main() {
    int r;
    r = test_multi_decl();
    if (r != 0) { printf("FAIL: test_multi_decl %d\n", r); return 1; }

    r = test_type_macros();
    if (r != 0) { printf("FAIL: test_type_macros %d\n", r); return 1; }

    printf("All multi-decl and type macro tests passed!\n");
    return 0;
}
