/* test_batch40: global structs with function pointers, indirect calls */
int printf(char *fmt, ...);
void *malloc(long n);
void free(void *p);
void *memset(void *s, int c, long n);

/* Test 1: Global struct with function pointer fields */
struct Config {
    int initialized;
    void *(*xMalloc)(long);
    void (*xFree)(void *);
    int flags;
};

struct Config globalConfig;

void *my_malloc(long n) {
    return malloc(n);
}

void my_free(void *p) {
    free(p);
}

int init_config() {
    if (globalConfig.initialized) return 0;
    globalConfig.xMalloc = my_malloc;
    globalConfig.xFree = my_free;
    globalConfig.initialized = 1;
    globalConfig.flags = 42;
    return 0;
}

/* Test 2: Function pointer parameters */
int counter;

void increment(void *p) {
    counter = counter + 1;
}

int call_through_ptr(void (*callback)(void *), void *arg) {
    if (callback) {
        callback(arg);
        return 1;
    }
    return 0;
}

/* Test 3: Struct with nested pointer access */
struct Inner {
    int x;
    int y;
};

struct Outer {
    struct Inner *inner;
    int count;
};

int test_nested() {
    struct Inner i;
    i.x = 10;
    i.y = 20;
    struct Outer o;
    o.inner = &i;
    o.count = 1;
    return o.inner->x + o.inner->y;
}

/* Test 4: Call function pointer from global struct */
int test_struct_funcptr() {
    init_config();
    void *p = globalConfig.xMalloc(64);
    if (!p) return 0;
    memset(p, 0, 64);
    globalConfig.xFree(p);
    return 1;
}

int main() {
    int fail = 0;

    /* Test 1 */
    init_config();
    if (globalConfig.initialized != 1) { printf("FAIL: not initialized\n"); fail = 1; }
    if (globalConfig.flags != 42) { printf("FAIL: flags %d\n", globalConfig.flags); fail = 1; }

    /* Test 2 */
    counter = 0;
    int r = call_through_ptr(increment, 0);
    if (r != 1) { printf("FAIL: call_through_ptr returned %d\n", r); fail = 1; }
    if (counter != 1) { printf("FAIL: counter %d\n", counter); fail = 1; }

    /* Test 3 */
    int sum = test_nested();
    if (sum != 30) { printf("FAIL: nested %d\n", sum); fail = 1; }

    /* Test 4 */
    int ok = test_struct_funcptr();
    if (ok != 1) { printf("FAIL: struct funcptr\n"); fail = 1; }

    if (!fail) printf("batch40: all tests passed\n");
    return fail;
}
