#ifndef RWLOCK_H_
#define RWLOCK_H_

#include <semaphore.h>

typedef struct _rwlock_t
{
    sem_t writelock;
    sem_t lock;
    int readers, acquires, releases;
} rwlock_t;

uint64_t micro_time();
void rwlock_init(rwlock_t *lock);
void rwlock_acquire_readlock(rwlock_t *lock);
void rwlock_release_readlock(rwlock_t *lock);
void rwlock_acquire_writelock(rwlock_t *lock);
void rwlock_release_writelock(rwlock_t *lock);

#endif // RWLOCK_H_
