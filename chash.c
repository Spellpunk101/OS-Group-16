#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "common.h"
#include "common_threads.h"
#include "fhash.h"

int main()
{
  hashRecord* head = malloc(sizeof(hashRecord));
  
  free(head);
  return 0;
}
