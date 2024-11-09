#ifndef __functionhash_h__
#define __functionhash_h__

typedef struct hash_struct
{
  uint32_t hash;
  char name[50];
  uint32_t salary;
  struct hash_struct *next;
} hashRecord;

void insert(char name[], uint32_t salary)
{
  size_t length = strlen(name);
  // Jenkins hash
  size_t i = 0;
  uint32_t hash = 0;
  while(i != length)
  {
    hash += key[i++];
    hash += hash << 10;
    hash += hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash <<15;
  // Jenkins hash
}

void delete()
{

}

void search()
{

}

#endif
