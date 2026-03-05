#include <stdio.h>
#include <stdlib.h>

extern const char *sqlite3_libversion(void);
extern int sqlite3_open(const char *, void **);
extern int sqlite3_close(void *);

extern int sqlite3_exec(void *db, const char *sql, void *callback, void *arg, char **errmsg);

int main() {
    printf("step 1\n");
    const char *v = sqlite3_libversion();
    printf("step 2: %s\n", v);
    printf("step 3: calling sqlite3_open\n");
    void *db = 0;
    int rc = sqlite3_open(":memory:", &db);
    printf("step 4: rc=%d\n", rc);
    if (rc == 0 && db) {
        char *errmsg = 0;
        rc = sqlite3_exec(db, "CREATE TABLE t1(a, b)", 0, 0, &errmsg);
        printf("step 5: CREATE TABLE rc=%d errmsg=%s\n", rc, errmsg ? errmsg : "(null)");
        rc = sqlite3_exec(db, "INSERT INTO t1 VALUES(1, 'hello')", 0, 0, &errmsg);
        printf("step 6: INSERT rc=%d\n", rc);
    }
    printf("Done.\n");
    return 0;
}
