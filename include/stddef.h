/* Stub stddef.h for cc compiler */
#ifndef _STDDEF_H
#define _STDDEF_H
typedef long size_t;
typedef long ptrdiff_t;
#define NULL ((void*)0)
#define offsetof(type, member) ((size_t)&((type*)0)->member)
#endif
