#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void crash_handler(int sig) {
    const char msg[] = "CRASH: SIGSEGV caught\n";
    write(2, msg, sizeof(msg)-1);
    _exit(1);
}

extern const char *sqlite3_libversion(void);
extern int sqlite3_open(const char *, void **);
extern int sqlite3_close(void *);

int main() {
    signal(11, crash_handler);
    fprintf(stderr, "step 1\n");
    const char *v = sqlite3_libversion();
    fprintf(stderr, "step 2: %s\n", v);
    void *db = 0;
    fprintf(stderr, "step 3\n");
    int rc = sqlite3_open(":memory:", &db);
    fprintf(stderr, "step 4: rc=%d\n", rc);
    if (rc == 0 && db) sqlite3_close(db);
    fprintf(stderr, "Done.\n");
    return 0;
}
