#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "fhash.h"
#include "rwlock.h"

#include "threadcommands.h"

extern FILE* output;

void* thread_insert(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    char* name = args->name;
    uint32_t salary = args->salary;
    hashListHead_t* headSpace = args->headSpace;
    uint32_t hash = jenkins_hash(name, strlen(name));

    rwlock_acquire_writelock(headSpace->rwlock);

    fprintf(output, "%lu: INSERT,%u,%s,%u\n", micro_time(), hash, name, salary);
    headSpace->head = insert(headSpace->head, name, salary);
    rwlock_release_writelock(headSpace->rwlock);
    //acquire locks, call functions, print

    pthread_mutex_lock(&(headSpace->insertLock));
    headSpace->numInsertsRemaining -= 1;
    if(headSpace->numInsertsRemaining == 0){
        fprintf(output, "%lu: DELETE AWAKENED\n", micro_time());
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
        fprintf(output, "%lu: WAITING ON INSERTS\n", micro_time());
        pthread_cond_wait(&(headSpace->insertCond), &(headSpace->insertLock));
    }
    pthread_mutex_unlock(&(headSpace->insertLock));

    rwlock_acquire_writelock(headSpace->rwlock);

    fprintf(output, "%lu: DELETE,%s\n",micro_time(),name);
    headSpace->head = delete(headSpace->head, name);
    rwlock_release_writelock(headSpace->rwlock);

    return NULL;
}

void* thread_search(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    char* name = args->name;
    hashListHead_t* headSpace = args->headSpace;

    rwlock_acquire_readlock(headSpace->rwlock);
    fprintf(output, "%lu: SEARCH,%s\n",micro_time(),name);
    hashRecord* found = search(headSpace->head, name);

    if(found == NULL){
        fprintf(output, "%lu: No Record Found\n",micro_time());
    }
    else{
        fprintf(output, "%lu: %u,%s,%u\n",micro_time(),found->hash,found->name,found->salary);
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
        fprintf(output, "%u,%s,%u\n", list[i]->hash, list[i]->name, list[i]->salary);
    }
    rwlock_release_readlock(headSpace->rwlock);

    free(list);

    return NULL;
}

void sortRecordsByHash(hashRecord** list, int numEntries){
    for(int i = 0; i < numEntries-1; i++){
        for(int j = 0; j < numEntries-1-i; j++){
            if(list[j]->hash > list[j+1]->hash){
                hashRecord* tmp = list[j];
                list[j] = list[j+1];
                list[j+1] = tmp;
            }
        }
    }
}
