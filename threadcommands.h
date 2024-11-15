#ifndef THREADCOMMANDS_H_
#define THREADCOMMANDS_H_

typedef struct {
    char name[50];
    uint32_t salary;
    hashListHead_t* headSpace;
} thread_args_t;

void* thread_insert(void* arg);
void* thread_delete(void* arg);
void* thread_search(void* arg);
void* thread_print(void* arg);
void sortRecordsByHash(hashRecord** list, int numEntries);

#endif // THREADCOMMANDS_H_