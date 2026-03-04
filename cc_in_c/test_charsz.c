int printf(char *fmt, ...);
void *memcpy(void *dst, void *src, long n);

int main() {
    char name[9];
    char src[9];
    int sz = sizeof(name);
    printf("sizeof(name) = %d\n", sz);
    memcpy(name, src, sizeof(name));
    return 0;
}
