#ifndef FHASH_H_
#define FHASH_H_

typedef struct hash_struct
{
  uint32_t hash;
  char name[50];
  uint32_t salary;
  struct hash_struct *next;
} hashRecord;

typedef struct{
  hashRecord* head;
  rwlock_t* rwlock;
  int numInsertsRemaining;
  pthread_cond_t insertCond;
  pthread_mutex_t insertLock;
} hashListHead_t;

uint32_t jenkins_hash(const uint8_t* key, size_t length);
hashRecord* insert(hashRecord* head, char name[], uint32_t salary);
hashRecord* delete(hashRecord* head, char name[]);
hashRecord* search(hashRecord* head, char name[]);

#endif // FHASH_H_
