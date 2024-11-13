#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"
#include "fhash.h"

void readFile(int *thread_count, char instructions[50][3][50], int *instruction_count);

int main()
{
  hashRecord *head = NULL;

  int thread_count = 0;
  char instructions[50][3][50];
  int instruction_count = 0;

  readFile(&thread_count, instructions, &instruction_count);
  printf("Thread Count: %d\n", thread_count);
  printf("Instructions:\n");
  for (int i = 0; i < instruction_count; i++)
  {
    printf("[%s, %s, %s]\n", instructions[i][0], instructions[i][1], instructions[i][2]);
  }

  free(head);
  return 0;
}

void readFile(int *thread_count, char instructions[50][3][50], int *instruction_count)
{
  FILE *file = fopen("commands.txt", "r");
  if (file == NULL)
  {
    printf("Error: file not found\n");
    exit(1);
  }
  char line[50];

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
      }
    }
    else
    {
      strcpy(instructions[*instruction_count][0], token);

      token = strtok(NULL, ",");
      strcpy(instructions[*instruction_count][1], token);

      token = strtok(NULL, ",");
      strcpy(instructions[*instruction_count][2], token);

      (*instruction_count)++;
    }
  }

  fclose(file);
}
