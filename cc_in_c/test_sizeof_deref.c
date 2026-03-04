typedef struct { long a; long b; long c; long d; long e; } Big;
Big arr[2];

int main() {
    Big *p = &arr[0];
    long s1 = sizeof(*p);
    long s2 = sizeof(Big);
    long s3 = sizeof(arr[0]);
    printf("sizeof(*p)=%ld sizeof(Big)=%ld sizeof(arr[0])=%ld\n", s1, s2, s3);
    if (s1 != 40) {
        printf("FAIL: sizeof(*p) should be 40, got %ld\n", s1);
        return 1;
    }
    printf("PASS\n");
    return 0;
}
