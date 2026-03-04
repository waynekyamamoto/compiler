typedef struct { long a; long b; long c; } Inner;
typedef struct {
    long x;
    Inner emb;
    long arr[4];
    long y;
} Outer;

Outer g_arr[2];

int main() {
    Outer *p = &g_arr[0];
    p->x = 10;
    p->emb.a = 20;
    p->emb.b = 30;
    p->emb.c = 40;
    p->arr[0] = 100;
    p->arr[1] = 101;
    p->arr[2] = 102;
    p->arr[3] = 103;
    p->y = 50;

    // Test reading back
    printf("x=%ld arr[0]=%ld arr[1]=%ld arr[2]=%ld arr[3]=%ld y=%ld\n",
        p->x, p->arr[0], p->arr[1], p->arr[2], p->arr[3], p->y);

    if (p->arr[2] != 102) {
        printf("FAIL: arr[2] should be 102, got %ld\n", p->arr[2]);
        return 1;
    }
    if (p->y != 50) {
        printf("FAIL: y should be 50, got %ld\n", p->y);
        return 1;
    }

    // Test taking address of array element (like DOOM does)
    int *ap = (int *) &p->arr[2];
    printf("ap=%p *ap=%ld\n", ap, *ap);
    if (*ap != 102) {
        printf("FAIL: *ap should be 102, got %ld\n", *ap);
        return 1;
    }
    printf("PASS\n");
    return 0;
}
