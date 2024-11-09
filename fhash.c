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

  if(index == NULL)
  {
    index = malloc(sizeof(hashRecord));
    index->hash = hash;
    strcpt(index->name, name);
    index->salary = salary;
    index->next = NULL;
    return index;
  }

  while(index != NULL)
  {
    if(hash == index->hash)
    {
      index->salary = salary;
      break;
    }
    if(index->next == NULL)
    {
      index->next = malloc(sizeof(hashRecord));
      index = index->next;
      index->hash = hash;
      strcpt(index->name, name);
      index->salary = salary;
      index->next = NULL;
      break;
    }
    index = index->next;
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

  while(index != NULL)
  {
    if(hash == index->hash)
    {
      return index; // if hash is found
    }
    index = index->next;
  }

  return NULL; // if hash is not found
}
