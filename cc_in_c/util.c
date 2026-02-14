#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void buf_init(Buf *b) {
    b->data = NULL;
    b->len = 0;
    b->cap = 0;
}

static void buf_grow(Buf *b, int need) {
    if (b->len + need <= b->cap)
        return;
    int newcap = b->cap ? b->cap * 2 : 256;
    while (newcap < b->len + need)
        newcap *= 2;
    b->data = realloc(b->data, newcap);
    if (!b->data) {
        fprintf(stderr, "out of memory\n");
        abort();
    }
    b->cap = newcap;
}

void buf_push(Buf *b, char c) {
    buf_grow(b, 1);
    b->data[b->len++] = c;
}

void buf_append(Buf *b, const char *s) {
    int n = strlen(s);
    buf_grow(b, n);
    memcpy(b->data + b->len, s, n);
    b->len += n;
}

void buf_printf(Buf *b, const char *fmt, ...) {
    char tmp[1024];
    va_list ap;
    va_start(ap, fmt);
    int n = vsnprintf(tmp, sizeof(tmp), fmt, ap);
    va_end(ap);
    buf_grow(b, n);
    memcpy(b->data + b->len, tmp, n);
    b->len += n;
}

char *buf_detach(Buf *b) {
    buf_push(b, '\0');
    char *s = b->data;
    b->data = NULL;
    b->len = b->cap = 0;
    return s;
}

void *xmalloc(size_t size) {
    void *p = malloc(size);
    if (!p) {
        fprintf(stderr, "out of memory\n");
        abort();
    }
    return p;
}

char *xstrdup(const char *s) {
    char *p = strdup(s);
    if (!p) {
        fprintf(stderr, "out of memory\n");
        abort();
    }
    return p;
}

void fatal(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "cc: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(1);
}
