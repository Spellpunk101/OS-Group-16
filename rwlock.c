// Modified from https://github.com/remzi-arpacidusseau/ostep-code/blob/master/threads-sema/rwlock.c

#include <semaphore.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include "rwlock.h"

extern FILE* output;

uint64_t micro_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * (uint64_t)1000000 + tv.tv_usec;
}

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
  fprintf(output, "%lu,READ LOCK ACQUIRED\n", micro_time());
  sem_post(&lock->lock);
}

void rwlock_release_readlock(rwlock_t *lock)
{
  sem_wait(&lock->lock);
  lock->readers--;
  lock->releases++;
  if (lock->readers == 0)
    sem_post(&lock->writelock);
  fprintf(output, "%lu,READ LOCK RELEASED\n", micro_time());
  sem_post(&lock->lock);
}

void rwlock_acquire_writelock(rwlock_t *lock)
{
  sem_wait(&lock->writelock);
  lock->acquires++;
  fprintf(output, "%lu,WRITE LOCK ACQUIRED\n", micro_time());
}

void rwlock_release_writelock(rwlock_t *lock)
{
  lock->releases++;
  fprintf(output, "%lu,WRITE LOCK RELEASED\n", micro_time());
  sem_post(&lock->writelock);
}
