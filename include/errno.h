/* Stub errno.h for cc compiler */
#ifndef _ERRNO_H
#define _ERRNO_H
int *__error(void);
#define errno (*__error())
#define EINTR 4
#define ENOMEM 12
#define EACCES 13
#define EEXIST 17
#define ENOENT 2
#define ENOSYS 78
#define EPERM 1
#define EBUSY 16
#define ERANGE 34
#define EINVAL 22
#define EIO 5
#define ENOLCK 77
#define EOVERFLOW 84
#define ENODEV 19
#define EAGAIN 35
#define ETIMEDOUT 60
#define EDEADLK 11
#define ENAMETOOLONG 63
#define ENOTCONN 57
#define ENOTEMPTY 66
#define ENOSPC 28
#define EISDIR 21
#define ENXIO 6
#define EFAULT 14
#define EFBIG 27
#define EMFILE 24
#define EMLINK 31
#define ENFILE 23
#define ENOTDIR 20
#define ENOTTY 25
#define EROFS 30
#define ESPIPE 29
#define ESRCH 3
#define ETXTBSY 26
#define EXDEV 18
#define EPIPE 32
#endif
