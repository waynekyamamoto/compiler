/* stdarg.h for cc compiler (Apple ARM64 variadic calling convention) */
#ifndef _STDARG_H
#define _STDARG_H

/* va_list is a pointer that walks the variadic arg area on the stack.
   On our Apple ARM64 ABI, variadic args are placed by the caller
   at [x29+16], [x29+24], etc. from the callee's perspective.
   va_start sets ap to point to the first variadic arg.
   va_arg reads the current arg and advances the pointer. */
typedef char *va_list;

/* __builtin_va_start is handled specially by the codegen.
   It sets ap = x29 + 16 (address of first variadic arg). */
void __builtin_va_start(va_list *ap);
#define va_start(ap, last) __builtin_va_start(&(ap))

/* Read current variadic arg and advance pointer */
#define va_arg(ap, type) (*(type*)((ap += 8) - 8))

#define va_end(ap) ((void)0)
#define va_copy(dest, src) ((dest) = (src))

#endif
