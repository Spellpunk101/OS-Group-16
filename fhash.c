#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "rwlock.h"


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

// insert a hash
hashRecord* insert(hashRecord* head, char name[], uint32_t salary)
{
  uint32_t hash = jenkins_hash(name, strlen(name));

  hashRecord* index = head;

  //empty hashTable
  if(head == NULL){
    hashRecord* newHead = (hashRecord*) malloc(sizeof(hashRecord));
    newHead->hash = hash;
    strcpy(newHead->name, name);
    newHead->salary = salary;
    newHead->next = NULL;
    return newHead;
  }
  //look through list for hash
  while(1)
  {
    // if hash is found
    if(hash == index->hash)
    {
      index->salary = salary;
      return head;
    }

    if(index->next == NULL) break;
    index = index->next;
  }

  // if hash is not found
  hashRecord* newNode = (hashRecord*) malloc(sizeof(hashRecord));
  newNode->hash = hash;
  strcpy(newNode->name, name);
  newNode->salary = salary;
  newNode->next = NULL;
  index->next = newNode;

  return head;
}

// delete a hash
hashRecord* delete(hashRecord* head, char name[])
{
  uint32_t hash = jenkins_hash(name, strlen(name));

  hashRecord* index = head;
  hashRecord* backup = head;

  while(index != NULL)
  {
    // if hash is found
    if(hash == index->hash)
    {
      // first element in linkedlist
      if(index == head)
      {
        head = index->next;
        free(index);
      }
      else
      {
        backup->next = index->next;
        free(index);
      }
      return head;
    }

    backup = index;
    index = index->next;
  }

  // if hash is not found
  return head;
}

// search for a hash
hashRecord* search(hashRecord* head, char name[])
{
  uint32_t hash = jenkins_hash(name, strlen(name));
  
  hashRecord* index = head;

  while(index != NULL)
  {
    // if hash is found
    if(hash == index->hash)
    {
      return index;
    }

    index = index->next;
  }

  // if hash is not found
  return NULL;
}
