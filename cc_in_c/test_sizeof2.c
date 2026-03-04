typedef struct { long a; long b; long c; } Inner;
typedef struct {
    long x;
    Inner emb;
    long y;
    long arr[4];
    long z;
} Outer;

Outer g;

int main() {
    Outer *p = &g;
    long si = sizeof(Inner);
    long so = sizeof(Outer);
    long sd = sizeof(*p);
    printf("sizeof(Inner)=%ld sizeof(Outer)=%ld sizeof(*p)=%ld\n", si, so, sd);
    // Inner = 3 fields * 8 = 24
    // Outer = 1 + 3(emb) + 1 + 4(arr) + 1 = 10 fields * 8 = 80
    if (si != 24) { printf("FAIL Inner: %ld\n", si); return 1; }
    if (so != 80) { printf("FAIL Outer: %ld\n", so); return 1; }
    if (sd != 80) { printf("FAIL *p: %ld\n", sd); return 1; }

    // Test memset zeroing
    g.x = 99; g.y = 99; g.z = 99; g.arr[0] = 99; g.arr[3] = 99;
    memset(p, 0, sizeof(*p));
    if (g.x != 0 || g.y != 0 || g.z != 0 || g.arr[0] != 0 || g.arr[3] != 0) {
        printf("FAIL memset didn't zero all fields\n");
        printf("x=%ld y=%ld z=%ld a0=%ld a3=%ld\n", g.x, g.y, g.z, g.arr[0], g.arr[3]);
        return 1;
    }
    printf("PASS\n");
    return 0;
}
