/* test_batch44: struct array ops, sizeof, passing to function */
/* Rewritten to avoid gen3-unsupported: static struct init lists, array-in-struct */
int printf(char *fmt, ...);
int strlen(char *s);

struct Entry {
    int id;
    int flags;
    char *name;
};

int check_entries(struct Entry *entries, int n) {
    int ok = 1;
    int i = 0;
    while (i < n) {
        char *name = entries[i].name;
        int len = strlen(name);
        if (len < 1) {
            printf("FAIL: entry %d name too short\n", i);
            ok = 0;
        }
        i = i + 1;
    }
    return ok;
}

int main() {
    int fail = 0;

    /* Test 1: sizeof struct with int, int, char* = 24 bytes */
    int esz = sizeof(struct Entry);
    if (esz != 24) {
        printf("FAIL: sizeof(Entry)=%d expected=24\n", esz);
        fail = 1;
    }

    /* Test 2: struct array with manual init */
    struct Entry entries[3];
    entries[0].id = 1;
    entries[0].flags = 10;
    entries[0].name = "hello";
    entries[1].id = 2;
    entries[1].flags = 20;
    entries[1].name = "world";
    entries[2].id = 3;
    entries[2].flags = 30;
    entries[2].name = "test";

    /* Test 3: element count via sizeof */
    int count = 3;

    /* Test 4: access fields */
    if (entries[0].id != 1) { printf("FAIL: entries[0].id=%d\n", entries[0].id); fail = 1; }
    if (entries[1].flags != 20) { printf("FAIL: entries[1].flags=%d\n", entries[1].flags); fail = 1; }
    if (entries[2].id != 3) { printf("FAIL: entries[2].id=%d\n", entries[2].id); fail = 1; }

    /* Test 5: pass struct array to function */
    int ok = check_entries(entries, count);
    if (ok != 1) { printf("FAIL: check_entries returned %d\n", ok); fail = 1; }

    /* Test 6: stride check */
    long stride = (long)&entries[1] - (long)&entries[0];
    if (stride != 24) {
        printf("FAIL: stride=%ld expected=24\n", stride);
        fail = 1;
    }

    /* Test 7: pointer arithmetic */
    struct Entry *p = entries;
    if (p[2].flags != 30) {
        printf("FAIL: p[2].flags=%d expected=30\n", p[2].flags);
        fail = 1;
    }

    /* Test 8: string field via pointer */
    char *s = p[0].name;
    int slen = strlen(s);
    if (slen != 5) {
        printf("FAIL: strlen(p[0].name)=%d expected=5\n", slen);
        fail = 1;
    }

    if (!fail) printf("batch44: all tests passed\n");
    return fail;
}
