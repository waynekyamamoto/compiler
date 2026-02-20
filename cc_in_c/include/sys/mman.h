#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H

#define PROT_NONE   0x00
#define PROT_READ   0x01
#define PROT_WRITE  0x02
#define PROT_EXEC   0x04

#define MAP_SHARED  0x01
#define MAP_PRIVATE 0x02
#define MAP_FIXED   0x10
#define MAP_FAILED  ((void *)-1)

void *mmap(void *addr, long length, int prot, int flags, int fd, long offset);
int munmap(void *addr, long length);
int msync(void *addr, long length, int flags);

#endif
