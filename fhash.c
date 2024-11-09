#include "fhash.h"

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

hashRecord* insert(hashRecord* head, char name[], uint32_t salary)
{
  uint32_t hash = jenkins_hash(name, strlen(name));

  hashRecord* index = head;
  hashRecord* backup = head;
  int exists = 0;

  if(head == NULL)
  {
    index = malloc(sizeof(hashRecord));
    index->hash = hash;
    strcpt(index->name, name);
    index->salary = salary;
    return index;
  }

  while(index != NULL)
  {
    if(hash == index->hash)
    {
      exists = 1;
      index->salary = salary;
      break;
    }
    backup = index;
    index = index->next;
  }

  if(!exists)
  {
    backup->next = malloc(sizeof(hashRecord));
    index = backup->next;
    index->hash = hash;
    strcpt(index->name, name);
    index->salary = salary;
  }

  return head;
}

hashRecord* delete(hashRecord* head, char name[])
{
  uint32_t hash = jenkins_hash(name, strlen(name));

  return head;
}
  
hashRecord* search(hashRecord* head, char name[])
{
  uint32_t hash = jenkins_hash(name, strlen(name));
  
  hashRecord* index = head;

  return index; // if hash is found

  return NULL; // if hash is not found
}
