/* Stub stdio.h for cc compiler */
#ifndef _STDIO_H
#define _STDIO_H
typedef struct FILE FILE;
typedef long size_t;
typedef long fpos_t;
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
#define EOF (-1)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define BUFSIZ 1024
#define FILENAME_MAX 1024
int printf(char *fmt, ...);
int fprintf(FILE *stream, char *fmt, ...);
int sprintf(char *str, char *fmt, ...);
int snprintf(char *str, long size, char *fmt, ...);
int scanf(char *fmt, ...);
int sscanf(char *str, char *fmt, ...);
int fscanf(FILE *stream, char *fmt, ...);
int vprintf(char *fmt, void *ap);
int vfprintf(FILE *stream, char *fmt, void *ap);
int vsprintf(char *str, char *fmt, void *ap);
int vsnprintf(char *str, long size, char *fmt, void *ap);
int fgetc(FILE *stream);
int fputc(int c, FILE *stream);
char *fgets(char *s, int n, FILE *stream);
int fputs(char *s, FILE *stream);
int getc(FILE *stream);
int putc(int c, FILE *stream);
int getchar(void);
int putchar(int c);
int puts(char *s);
int ungetc(int c, FILE *stream);
long fread(void *ptr, long size, long nmemb, FILE *stream);
long fwrite(void *ptr, long size, long nmemb, FILE *stream);
FILE *fopen(char *path, char *mode);
FILE *fdopen(int fd, char *mode);
FILE *freopen(char *path, char *mode, FILE *stream);
int fclose(FILE *stream);
int fflush(FILE *stream);
int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
void rewind(FILE *stream);
int feof(FILE *stream);
int ferror(FILE *stream);
void clearerr(FILE *stream);
int remove(char *path);
int rename(char *oldpath, char *newpath);
FILE *tmpfile(void);
char *tmpnam(char *s);
void perror(char *s);
int fileno(FILE *stream);
int fgetpos(FILE *stream, fpos_t *pos);
int fsetpos(FILE *stream, fpos_t *pos);
#endif
