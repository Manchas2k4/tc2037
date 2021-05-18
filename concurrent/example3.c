/*************************************************************
* File: example3.c
* Author: Pedro Perez
* Description: This file creates 5 threads, sends a parameter
*              to each of them.
*
* To compile: gcc example3.c -pthread
*
* Copyright (c) 2021 by Tecnologico de Monterrey.
* All Rights Reserved. May be reproduced for any non-commercial
* purpose.
*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS 4
#define LIMIT   5

void* task(void* param) {
  int i, id;

  id = *((int*) param);
  for (i = 0; i < LIMIT; i++) {
    printf("PID = %i, TID = %i <=> i = %i\n", getpid(),
            id, i);
  }
  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  pthread_t tid[THREADS];
  int i;

  for (i = 0; i < THREADS; i++) {
    pthread_create(&tid[i], NULL, task, (void*) &i);
  }

  for (i = 0; i < THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  return 0;
}
