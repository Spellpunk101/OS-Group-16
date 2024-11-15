// Modified from https://github.com/remzi-arpacidusseau/ostep-code/blob/master/threads-sema/rwlock.c

#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include "rwlock.h"

void rwlock_init(rwlock_t *lock)
{
  lock->readers = 0;
  lock->acquires = 0;
  lock->releases = 0;
  sem_init(&lock->lock, 0, 1);
  sem_init(&lock->writelock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *lock)
{
  sem_wait(&lock->lock);
  lock->readers++;
  lock->acquires++;
  if (lock->readers == 1)
    sem_wait(&lock->writelock);
  printf("%lu,READ LOCK ACQUIRED\n", time(NULL));
  sem_post(&lock->lock);
}

void rwlock_release_readlock(rwlock_t *lock)
{
  sem_wait(&lock->lock);
  lock->readers--;
  lock->releases++;
  if (lock->readers == 0)
    sem_post(&lock->writelock);
  printf("%lu,READ LOCK RELEASED\n", time(NULL));
  sem_post(&lock->lock);
}

void rwlock_acquire_writelock(rwlock_t *lock)
{
  sem_wait(&lock->writelock);
  lock->acquires++;
  printf("%lu,WRITE LOCK ACQUIRED\n", time(NULL));
}

void rwlock_release_writelock(rwlock_t *lock)
{
  lock->releases++;
  printf("%lu,WRITE LOCK RELEASED\n", time(NULL));
  sem_post(&lock->writelock);
}
