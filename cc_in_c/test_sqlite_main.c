#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

static int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3 *db;
    char *errmsg = 0;
    int rc;

    // Open in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        printf("FAIL: Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    printf("OK: opened in-memory database\n");

    // Create table
    rc = sqlite3_exec(db, "CREATE TABLE test(id INTEGER PRIMARY KEY, name TEXT, value REAL);", 0, 0, &errmsg);
    if (rc != 0) {
        printf("FAIL: CREATE TABLE: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return 1;
    }
    printf("OK: created table\n");

    // Insert rows
    rc = sqlite3_exec(db, "INSERT INTO test VALUES(1, 'hello', 3.14);", 0, 0, &errmsg);
    if (rc != 0) { printf("FAIL: INSERT 1: %s\n", errmsg); sqlite3_free(errmsg); sqlite3_close(db); return 1; }

    rc = sqlite3_exec(db, "INSERT INTO test VALUES(2, 'world', 2.72);", 0, 0, &errmsg);
    if (rc != 0) { printf("FAIL: INSERT 2: %s\n", errmsg); sqlite3_free(errmsg); sqlite3_close(db); return 1; }

    rc = sqlite3_exec(db, "INSERT INTO test VALUES(3, 'sqlite', 42.0);", 0, 0, &errmsg);
    if (rc != 0) { printf("FAIL: INSERT 3: %s\n", errmsg); sqlite3_free(errmsg); sqlite3_close(db); return 1; }
    printf("OK: inserted 3 rows\n");

    // Query
    printf("--- SELECT * FROM test ---\n");
    rc = sqlite3_exec(db, "SELECT * FROM test ORDER BY id;", callback, 0, &errmsg);
    if (rc != 0) { printf("FAIL: SELECT: %s\n", errmsg); sqlite3_free(errmsg); sqlite3_close(db); return 1; }

    // Aggregate query
    printf("--- SELECT count(*), sum(value) FROM test ---\n");
    rc = sqlite3_exec(db, "SELECT count(*) as cnt, sum(value) as total FROM test;", callback, 0, &errmsg);
    if (rc != 0) { printf("FAIL: aggregate: %s\n", errmsg); sqlite3_free(errmsg); sqlite3_close(db); return 1; }

    // Version
    printf("SQLite version: %s\n", sqlite3_libversion());

    sqlite3_close(db);
    printf("OK: all tests passed\n");
    return 0;
}
