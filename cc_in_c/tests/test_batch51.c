// Test batch 51: embedded named struct definition inside another struct
int printf(int *fmt, ...);
int *malloc(int size);

// Pattern from sqlite3: struct sqlite3 { struct sqlite3InitInfo { ... } init; }
struct Outer {
    int x;
    struct Inner {
        int a;
        int b;
    } inner;
    int y;
};

int test_embedded_basic() {
    struct Outer o;
    o.x = 1;
    o.inner.a = 10;
    o.inner.b = 20;
    o.y = 2;
    if (o.x != 1) return 1;
    if (o.inner.a != 10) return 2;
    if (o.inner.b != 20) return 3;
    if (o.y != 2) return 4;
    return 0;
}

int test_embedded_ptr() {
    struct Outer *p = malloc(32);
    p->x = 5;
    p->inner.a = 50;
    p->inner.b = 60;
    p->y = 6;
    if (p->x != 5) return 1;
    if (p->inner.a != 50) return 2;
    if (p->inner.b != 60) return 3;
    if (p->y != 6) return 4;
    return 0;
}

// The embedded struct should also be usable independently
int test_embedded_standalone() {
    struct Inner i;
    i.a = 100;
    i.b = 200;
    if (i.a != 100) return 1;
    if (i.b != 200) return 2;
    return 0;
}

// Embedded struct with pointer parameter
int sum_inner(struct Inner *ip) {
    return ip->a + ip->b;
}

int test_embedded_param() {
    struct Outer o;
    o.inner.a = 3;
    o.inner.b = 7;
    if (sum_inner(&o.inner) != 10) return 1;
    return 0;
}

int main() {
    int fail = 0;
    int r;
    r = test_embedded_basic();
    if (r) { printf("FAIL: embedded_basic step %d\n", r); fail = 1; }
    r = test_embedded_ptr();
    if (r) { printf("FAIL: embedded_ptr step %d\n", r); fail = 1; }
    r = test_embedded_standalone();
    if (r) { printf("FAIL: embedded_standalone step %d\n", r); fail = 1; }
    r = test_embedded_param();
    if (r) { printf("FAIL: embedded_param step %d\n", r); fail = 1; }
    if (!fail) printf("batch51: all tests passed\n");
    return fail;
}
