#ifndef FHASH_H_
#define FHASH_H_

typedef struct hash_struct
{
  uint32_t hash;
  char name[50];
  uint32_t salary;
  struct hash_struct *next;
} hashRecord;

uint32_t jenkins_hash(const uint8_t* key, size_t length);
hashRecord* insert(char name[], uint32_t salary);
hashRecord* delete(char name[]);
hashRecord* search(char name[]);

#endif // FHASH_H_
