#include "threadcommands.h"

void* thread_insert(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    char* name = args->name;
    uint32_t salary = args->salary;
    hashListHead_t* headSpace = args->headSpace;
    //acquire locks, call functions, print
}

void* thread_delete(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    char* name = args->name;
    hashListHead_t* headSpace = args->headSpace;
}

void* thread_search(void* arg){
    thread_args_t* args = (thread_args_t*) arg;
    char* name = args->name;
    hashListHead_t* headSpace = args->headSpace;
}

void* thread_print(void* arg){
    hashListHead_t* headSpace = args->headSpace;
    
}
