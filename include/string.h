/* Stub string.h for cc compiler */
#ifndef _STRING_H
#define _STRING_H
typedef long size_t;
#define NULL ((void*)0)
void *memcpy(void *dest, void *src, long n);
void *memmove(void *dest, void *src, long n);
void *memset(void *s, int c, long n);
int memcmp(void *s1, void *s2, long n);
void *memchr(void *s, int c, long n);
char *strcpy(char *dest, char *src);
char *strncpy(char *dest, char *src, long n);
char *strcat(char *dest, char *src);
char *strncat(char *dest, char *src, long n);
int strcmp(char *s1, char *s2);
int strncmp(char *s1, char *s2, long n);
char *strchr(char *s, int c);
char *strrchr(char *s, int c);
char *strstr(char *haystack, char *needle);
long strlen(char *s);
char *strdup(char *s);
char *strerror(int errnum);
long strspn(char *s, char *accept);
long strcspn(char *s, char *reject);
char *strtok(char *str, char *delim);
#endif
