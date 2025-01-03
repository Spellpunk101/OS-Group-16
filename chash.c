#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "fhash.h"
#include "threadcommands.h"
#include "rwlock.h"

void readFile(int *thread_count, char ****instructions);

FILE* output;

int main()
{
  output = fopen("output.txt", "w");
  hashListHead_t* head = (hashListHead_t*) malloc(sizeof(hashListHead_t));
  head->rwlock = (rwlock_t*) malloc(sizeof(rwlock_t));
  rwlock_init(head->rwlock);
  pthread_mutex_init(&(head->insertLock), NULL);
  pthread_cond_init(&(head->insertCond), NULL);

  head->head = NULL;

  int thread_count = 0;
  char ***instructions;

  readFile(&thread_count, &instructions);

  fprintf(output, "Running %d threads\n", thread_count);

  int numInserts = 0;
  for(int i = 0; i < thread_count; i++){
    if(strcmp(instructions[i][0],"insert")==0){
      numInserts++;
    }
  }
  head->numInsertsRemaining = numInserts;
  //make thread for each command, calling functions from file
  pthread_t* pthreads = (pthread_t*) calloc(thread_count, sizeof(pthread_t));
  thread_args_t* thread_args = (thread_args_t*) calloc(thread_count, sizeof(thread_args_t));
  for(int i = 0; i < thread_count; i++){
    if(strcmp(instructions[i][0], "insert") == 0){
      strcpy(thread_args[i].name, instructions[i][1]);
      thread_args[i].salary = atoi(instructions[i][2]);
      thread_args[i].headSpace = head;
      pthread_create(&(pthreads[i]), NULL, thread_insert, &(thread_args[i]));
    }
    else if(strcmp(instructions[i][0], "delete") == 0){
      strcpy(thread_args[i].name, instructions[i][1]);
      thread_args[i].headSpace = head;
      pthread_create(&(pthreads[i]), NULL, thread_delete, &(thread_args[i]));
    }
    else if(strcmp(instructions[i][0], "search") == 0){
      strcpy(thread_args[i].name, instructions[i][1]);
      thread_args[i].headSpace = head;
      pthread_create(&(pthreads[i]), NULL, thread_search, &(thread_args[i]));
    }
    else if(strcmp(instructions[i][0], "print") == 0){
      thread_args[i].headSpace = head;
      pthread_create(&(pthreads[i]), NULL, thread_print, &(thread_args[i]));
    }
  }

  for(int i = 0; i < thread_count; i++){
    pthread_join(pthreads[i],NULL);
  }

  fprintf(output, "Finished all threads.\n");
  fprintf(output, "Number of lock acquisitions:  %d\n",(head->rwlock)->acquires+1); //this is because we will acquire/release ONE more lock
  fprintf(output, "Number of lock releases:  %d\n", (head->rwlock)->releases+1);    //with the final call to thread_print after this.

  thread_args_t printArgs;
  printArgs.headSpace = head;
  thread_print(&printArgs);

  free(pthreads);
  free(thread_args);
  free(head->rwlock);
  hashRecord* index = head->head;
  while(index != NULL){
    hashRecord* toFree = index;
    index = index->next;
    free(toFree);
  }
  free(head);
  for (int i = 0; i < thread_count; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      free(instructions[i][j]);
    }
    free(instructions[i]);
  }
  free(instructions);
  fclose(output);
  return 0;
}

void readFile(int *thread_count, char ****instructions)
{
  FILE *file = fopen("commands.txt", "r");
  if (file == NULL)
  {
    printf("Error: file not found\n");
    exit(1);
  }
  char line[70];

  int instruction_count = 0;

  while (fgets(line, sizeof(line), file))
  {
    line[strcspn(line, "\n")] = 0;

    char *token = strtok(line, ",");
    if (token == NULL)
      continue;

    if (strcmp(token, "threads") == 0)
    {
      token = strtok(NULL, ",");
      if (token != NULL)
      {
        *thread_count = atoi(token);
        *instructions = calloc(*thread_count, sizeof(char**));
        for (int i = 0; i < *thread_count; i++)
        {
          (*instructions)[i] = calloc(3, sizeof(char*));
          for (int j = 0; j < 3; j++)
          {
            (*instructions)[i][j] = calloc(50, sizeof(char));
          }
        }
      }
    }
    else
    {
      strcpy((*instructions)[instruction_count][0], token);

      token = strtok(NULL, ",");
      strcpy((*instructions)[instruction_count][1], token);

      token = strtok(NULL, ",");
      strcpy((*instructions)[instruction_count][2], token);

      instruction_count++;
    }
  }

  fclose(file);
}
