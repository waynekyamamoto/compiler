/* Stub stdlib.h for cc compiler */
#ifndef _STDLIB_H
#define _STDLIB_H
typedef long size_t;
#define NULL ((void*)0)
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define RAND_MAX 2147483647
void *malloc(long size);
void *calloc(long nmemb, long size);
void *realloc(void *ptr, long size);
void free(void *ptr);
void abort(void);
void exit(int status);
int atexit(void (*func)(void));
int atoi(char *str);
long atol(char *str);
long long atoll(char *str);
long strtol(char *str, char **endptr, int base);
unsigned long strtoul(char *str, char **endptr, int base);
long long strtoll(char *str, char **endptr, int base);
unsigned long long strtoull(char *str, char **endptr, int base);
int abs(int x);
long labs(long x);
void qsort(void *base, long nmemb, long size, int (*compar)(void *, void *));
void *bsearch(void *key, void *base, long nmemb, long size, int (*compar)(void *, void *));
int rand(void);
void srand(unsigned int seed);
char *getenv(char *name);
int system(char *command);
#endif
