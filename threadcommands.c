#include "threadcommands.h"
#include "fhash.h"
#include <stdint.h>
#include <stdio.h>

void* thread_insert(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    char* name = args->name;
    uint32_t salary = args->salary;
    hashListHead_t* headSpace = args->headSpace;

    rwlock_acquire_writelock(headSpace->rwlock);

    print("%ld,INSERT,%s,%d",time(NULL),name,salary);
    headSpace->head = (headSpace->head, name, salary);
    rwlock_release_writelock(headSpace->rwlock);
    //acquire locks, call functions, print
}

void* thread_delete(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    char* name = args->name;
    hashListHead_t* headSpace = args->headSpace;


    //TODO: wait until all inserts are cleared, somehow
    while(1);
    rwlock_acquire_writelock(headSpace->rwlock);

    printf("%ld,DELETE,%s",time(NULL),name);
    headSpace->head = delete(headSpace->head, name);
    rwlock_release_writelock(headSpace->rwlock);
}

void* thread_search(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    char* name = args->name;
    hashListHead_t* headSpace = args->headSpace;
    uint32_t hash = jenkins_hash(name, strlen(name));

    rwlock_acquire_readlock(headSpace->rwlock);
    print("%ld,SEARCH,%s",time(NULL),name);
    hashRecord* found = search(headSpace->head, name);
    rwlock_release_readlock(headSpace->rwlock);


    //TODO: change to print to output file, whereever that is
    if(found == NULL){
        printf("%ld,No Record Found",time(NULL));
    }
    else{
        printf("%ld,%d,%s,%d",time(NULL),hash,found->name,found->salary);
    }
    
}

void* thread_print(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    hashListHead_t* headSpace = args->headSpace;
    
    rwlock_acquire_readlock(headSpace->rwlock);
    rwlock_release_readlock(headSpace->rwlock);
}
