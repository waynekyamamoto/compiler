/* Stub stdarg.h for cc compiler */
#ifndef _STDARG_H
#define _STDARG_H
/* va_list is just a pointer for our purposes */
typedef void *va_list;
#define va_start(ap, last) ((void)0)
#define va_end(ap) ((void)0)
#define va_arg(ap, type) (*(type*)0)
#define va_copy(dest, src) ((void)0)
#endif
