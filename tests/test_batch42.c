/* test_batch42: struct assignment */
int printf(char *fmt, ...);

struct Methods {
    void *(*xAlloc)(long);
    void (*xFree)(void *);
    int flags;
};

struct Config {
    int id;
    struct Methods m;
    int count;
};

struct Config globalCfg;

void *my_alloc(long n);
void my_free(void *p);

/* Set config from methods pointer */
void set_methods(struct Methods *src) {
    globalCfg.m = *src;
}

int main() {
    int fail = 0;

    /* Test 1: struct assignment via pointer dereference */
    struct Methods methods;
    methods.xAlloc = my_alloc;
    methods.xFree = my_free;
    methods.flags = 99;

    set_methods(&methods);

    if (globalCfg.m.flags != 99) { printf("FAIL: flags %d\n", globalCfg.m.flags); fail = 1; }

    /* Test 2: direct struct assignment */
    struct Methods m2;
    m2.xAlloc = 0;
    m2.xFree = 0;
    m2.flags = 42;

    struct Methods m3;
    m3 = m2;
    if (m3.flags != 42) { printf("FAIL: m3.flags %d\n", m3.flags); fail = 1; }

    if (!fail) printf("batch42: all tests passed\n");
    return fail;
}

void *my_alloc(long n) { return 0; }
void my_free(void *p) { }
