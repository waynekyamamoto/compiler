#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdarg.h>

/* Growable string buffer */
typedef struct {
    char *data;
    int len;
    int cap;
} Buf;

void buf_init(Buf *b);
void buf_push(Buf *b, char c);
void buf_printf(Buf *b, const char *fmt, ...);
void buf_append(Buf *b, const char *s);
char *buf_detach(Buf *b);

/* Abort-on-failure allocators */
void *xmalloc(size_t size);
char *xstrdup(const char *s);

/* Fatal error */
void fatal(const char *fmt, ...);

#endif
