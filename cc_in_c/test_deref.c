typedef struct { long x; int *p; long y; } S;

long val = 42;
S s;

int main() {
    s.p = &val;
    s.x = 1;
    s.y = 2;

    S *sp = &s;
    long got = *sp->p;
    printf("val=%ld got=%ld p=%p\n", val, got, sp->p);
    if (got != 42) {
        printf("FAIL: *sp->p returned %ld instead of 42\n", got);
        return 1;
    }
    printf("PASS\n");
    return 0;
}
