#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"
#include "functionhash.h"

typedef struct hash_struct
{
  uint32_t hash;
  char name[50];
  uint32_t salary;
  struct hash_struct *next;
} hashRecord;

hashRecord *head;

int main()
{
  head = malloc(sizeof(hashRecord));
  
  free(head);
  return 0;
}

uint32_t jenkins_hash(const uint8_t* key, size_t length)
{
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
  return hash;
}

void insert(char name[], uint32_t salary)
{
  uint32_t hash = jenkins_hash(name, strlen(name));

  hashRecord *index = head;
  hashRecord *backup = head;
  int exists = 0;
  
  while(index != NULL)
  {
    if(hash == index->hash)
    {
      exists = 1;
      strcpt(index->name, name);
      index->salary = salary;
      break;
    }
    backup = index;
    index = index->next;
  }
  
  if(!exists)
  {
    backup = malloc(sizeof(hashRecord));
    strcpt(backup->name, name);
    backup->salary = salary;
  }
}

void delete()
{

}

void search()
{

}
