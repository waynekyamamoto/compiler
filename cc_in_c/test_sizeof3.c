typedef struct { long a; long b; long c; } Inner;
typedef struct {
    long x;
    Inner emb;
    long frags[4];
    long y;
} Outer;

Outer arr[2];

int main() {
    long s1 = sizeof(arr[0].frags);
    long s2 = sizeof(arr[0].emb);
    long s3 = sizeof(arr[0]);
    long s4 = sizeof(arr);
    printf("sizeof(arr[0].frags)=%ld sizeof(arr[0].emb)=%ld sizeof(arr[0])=%ld sizeof(arr)=%ld\n", s1, s2, s3, s4);
    // frags is long[4] = 32 bytes
    // emb is Inner = 3 fields * 8 = 24 bytes
    // arr[0] is Outer = (1+3+4+1) * 8 = 72 bytes
    // arr is 2 * 72 = 144 bytes
    if (s1 != 32) { printf("FAIL frags: got %ld expected 32\n", s1); return 1; }
    if (s2 != 24) { printf("FAIL emb: got %ld expected 24\n", s2); return 1; }
    if (s3 != 72) { printf("FAIL arr[0]: got %ld expected 72\n", s3); return 1; }
    if (s4 != 144) { printf("FAIL arr: got %ld expected 144\n", s4); return 1; }
    printf("PASS\n");
    return 0;
}
