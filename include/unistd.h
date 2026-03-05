#ifndef _UNISTD_H
#define _UNISTD_H

#include <sys/types.h>

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define _SC_PAGESIZE 29

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#define F_OK 0
#define R_OK 4
#define W_OK 2
#define X_OK 1

long sysconf(int name);
int close(int fd);
long read(int fd, void *buf, long count);
long write(int fd, const void *buf, long count);
long lseek(int fd, long offset, int whence);
int unlink(const char *path);
int rmdir(const char *path);
int access(const char *path, int mode);
int fsync(int fd);
int ftruncate(int fd, long length);
unsigned int sleep(unsigned int seconds);
int usleep(unsigned int usec);
int getcwd(char *buf, long size);
int getpid(void);
int fchown(int fd, int owner, int group);
long pread(int fd, void *buf, long count, long offset);
long pwrite(int fd, const void *buf, long count, long offset);
int fchmod(int fd, int mode);

#endif
