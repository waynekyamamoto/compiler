int printf(char *fmt, ...);

struct texture_s {
    char name[8];
    long width;
    long height;
    long index;
};
typedef struct texture_s texture_t;

int main() {
    texture_t t;
    texture_t *tp;
    printf("sizeof(t) = %ld\n", (long)sizeof(t));
    printf("sizeof(tp) = %ld\n", (long)sizeof(tp));
    printf("sizeof(t.name) = %ld\n", (long)sizeof(t.name));
    printf("sizeof(tp->name) = %ld\n", (long)sizeof(tp->name));
    printf("sizeof(t.width) = %ld\n", (long)sizeof(t.width));
    return 0;
}
