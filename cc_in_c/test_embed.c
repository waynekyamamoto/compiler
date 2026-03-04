typedef struct { long a; long b; long c; } Inner;
typedef struct {
    long x;
    Inner emb;
    long y;
} Outer;

Outer g;

int main() {
    g.x = 10;
    g.emb.a = 20;
    g.emb.b = 30;
    g.emb.c = 40;
    g.y = 50;

    Outer *p = &g;
    printf("x=%ld emb.a=%ld emb.b=%ld emb.c=%ld y=%ld\n",
        p->x, p->emb.a, p->emb.b, p->emb.c, p->y);

    if (p->y != 50) {
        printf("FAIL: p->y should be 50, got %ld\n", p->y);
        return 1;
    }
    if (p->x != 10) {
        printf("FAIL: p->x should be 10, got %ld\n", p->x);
        return 1;
    }
    printf("PASS\n");
    return 0;
}
