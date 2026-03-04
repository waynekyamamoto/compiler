#ifndef _PTHREAD_H
#define _PTHREAD_H

/* Match real macOS sizes */
typedef struct { char __opaque[64]; } pthread_mutex_t;
typedef struct { char __opaque[16]; } pthread_mutexattr_t;
typedef long pthread_t;

#define PTHREAD_MUTEX_INITIALIZER {0}
#define PTHREAD_MUTEX_RECURSIVE 1

int pthread_mutex_init(pthread_mutex_t *mutex, void *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);

int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);

pthread_t pthread_self(void);
int pthread_equal(pthread_t t1, pthread_t t2);

#endif
