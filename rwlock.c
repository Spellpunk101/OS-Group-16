// Modified from https://github.com/remzi-arpacidusseau/ostep-code/blob/master/threads-sema/rwlock.c

#include <semaphore.h>
#include <time.h>
#include "rwlock.h"

void rwlock_init(rwlock_t *lock)
{
  lock->readers = 0;
  sem_init(&lock->lock, 0, 1);
  sem_init(&lock->writelock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *lock)
{
  sem_wait(&lock->lock);
  lock->readers++;
  if (lock->readers == 1)
    sem_wait(&lock->writelock);
  printf("%ld,READ LOCK ACQUIRED\n", time(NULL));
  sem_post(&lock->lock);
}

void rwlock_release_readlock(rwlock_t *lock)
{
  sem_wait(&lock->lock);
  lock->readers--;
  if (lock->readers == 0)
    sem_post(&lock->writelock);
  printf("%ld,READ LOCK RELEASED\n", time(NULL));
  sem_post(&lock->lock);
}

void rwlock_acquire_writelock(rwlock_t *lock)
{
  sem_wait(&lock->writelock);
  printf("%ld,WRITE LOCK ACQUIRED\n", time(NULL));
}

void rwlock_release_writelock(rwlock_t *lock)
{
  printf("%ld,WRITE LOCK RELEASED\n", time(NULL));
  sem_post(&lock->writelock);
}
