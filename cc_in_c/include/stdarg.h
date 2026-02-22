#ifndef _STDARG_H
#define _STDARG_H

typedef char *va_list;

void __builtin_va_start(va_list *ap);
#define va_start(ap, last) __builtin_va_start(&(ap))

#define va_arg(ap, type) (*(type*)((ap += 8) - 8))

#define va_end(ap) ((void)0)
#define va_copy(dest, src) ((dest) = (src))

#endif
