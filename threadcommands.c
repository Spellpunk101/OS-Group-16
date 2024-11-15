#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "fhash.h"

#include "threadcommands.h"

void* thread_insert(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    char* name = args->name;
    uint32_t salary = args->salary;
    hashListHead_t* headSpace = args->headSpace;

    rwlock_acquire_writelock(headSpace->rwlock);

    printf("%ld,INSERT,%s,%d\n",time(NULL),name,salary);
    headSpace->head = insert(headSpace->head, name, salary);
    rwlock_release_writelock(headSpace->rwlock);
    //acquire locks, call functions, print
    
    pthread_mutex_lock(&(headSpace->insertLock));
    headSpace->numInsertsRemaining -= 1;
    if(headSpace->numInsertsRemaining == 0){
        pthread_cond_broadcast(&(headSpace->insertCond));
    }
    pthread_mutex_unlock(&(headSpace->insertLock));

    return NULL;
}

void* thread_delete(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    char* name = args->name;
    hashListHead_t* headSpace = args->headSpace;


    pthread_mutex_lock(&(headSpace->insertLock));
    while(headSpace->numInsertsRemaining != 0){
        printf("%ld,WAITING ON INSERTS\n", time(NULL));
        pthread_cond_wait(&(headSpace->insertCond), &(headSpace->insertLock));
    }
    pthread_mutex_unlock(&(headSpace->insertLock));
    
    rwlock_acquire_writelock(headSpace->rwlock);

    printf("%ld,DELETE,%s\n",time(NULL),name);
    headSpace->head = delete(headSpace->head, name);
    rwlock_release_writelock(headSpace->rwlock);

    return NULL;
}

void* thread_search(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    char* name = args->name;
    hashListHead_t* headSpace = args->headSpace;

    rwlock_acquire_readlock(headSpace->rwlock);
    printf("%ld,SEARCH,%s\n",time(NULL),name);
    hashRecord* found = search(headSpace->head, name);
    
    //TODO: change to print to output file, whereever that is
    if(found == NULL){
        printf("%ld,No Record Found\n",time(NULL));
    }
    else{
        printf("%ld,%d,%s,%d\n",time(NULL),found->hash,found->name,found->salary);
    }
    rwlock_release_readlock(headSpace->rwlock);

    return NULL;
}

void* thread_print(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    hashListHead_t* headSpace = args->headSpace;
    

    //assuming can only handle 50 instructions
    rwlock_acquire_readlock(headSpace->rwlock);
    hashRecord** list = (hashRecord**) calloc(50, sizeof(hashRecord*));
    int numRecords = 0;
    hashRecord* index = headSpace->head;
    while(index != NULL){
        list[numRecords] = index;
        numRecords++;
        index = index->next;
    }
    sortRecordsByHash(list, numRecords);
    for(int i = 0; i < numRecords; i++){
        printf("%d,%s,%d\n", list[i]->hash, list[i]->name, list[i]->salary);
    }
    rwlock_release_readlock(headSpace->rwlock);
    
    return NULL;
}

void sortRecordsByHash(hashRecord** list, int numEntries){
    for(int i = 0; i < numEntries-1; i++){
        for(int j = i; j < numEntries-1; j++){
            if(list[j]->hash > list[j+1]->hash){
                hashRecord* tmp = list[j];
                list[j] = list[j+1];
                list[j+1] = tmp;
            }
        }
    }
}
