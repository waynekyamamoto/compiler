#include <stdio.h>

// Test globals (stage0 compatible - separate declarations)
int ga;
int gb;
int gc;
int *gp;
int *gq;
int gx = 10;
int gy = 20;
int gz = 30;

int test_globals() {
    ga = 1; gb = 2; gc = 3;
    if (ga + gb + gc != 6) return 1;

    gp = &ga; gq = &gb;
    if (*gp != 1) return 2;
    if (*gq != 2) return 3;

    if (gx != 10) return 4;
    if (gy != 20) return 5;
    if (gz != 30) return 6;

    return 0;
}

int main() {
    int r;
    r = test_globals();
    if (r != 0) { printf("FAIL: test_globals %d\n", r); return 1; }

    printf("All batch98 tests passed!\n");
    return 0;
}
