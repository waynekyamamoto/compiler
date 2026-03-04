int printf(char *fmt, ...);
void *memcpy(void *dst, void *src, long n);
typedef unsigned char uint8_t;
typedef uint8_t byte;

void test(void) {
    byte *maptex;
    byte *maptex2;
    byte *maptex1;
    char name[9];
    char *names;
    char *name_p;
    long *patchlookup;
    int totalwidth;
    int nummappatches;
    int sz = sizeof(name);
    printf("sizeof(name) = %d\n", sz);
}

int main() {
    test();
    return 0;
}
