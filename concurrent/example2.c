/*************************************************************
* File: example2.c
* Author: Pedro Perez
* Description: This file creates 5 threads and forces to the
*              main thread to wait for all created threads
*              (fork-join).
*
* To compile: gcc example2.c -pthread
*
* Copyright (c) 2021 by Tecnologico de Monterrey.
* All Rights Reserved. May be reproduced for any non-commercial
* purpose.
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS 5
#define LIMIT   5

void* task(void* param) {
  int i;

  for (i = 0; i < LIMIT; i++) {
    printf("PID = %i, TID = %li <=> i = %i\n", getpid(),
            pthread_self(), i);
  }
  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  pthread_t tid[THREADS];
  int i;

  for (i = 0; i < THREADS; i++) {
    pthread_create(&tid[i], NULL, task, (void*) i);
  }

  for (i = 0; i < THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  return 0;
}
