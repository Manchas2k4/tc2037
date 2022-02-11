/*************************************************************
* File: problem1.c
* Author: Pedro Perez
* Description: This file contains the code that adds all the
*              elements of an integer array using pthreads.
* To compile: gcc problem1.c -pthread
*
* Copyright (c) 2021 by Tecnologico de Monterrey.
* All Rights Reserved. May be reproduced for any non-commercial
* purpose.
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "utils.h"

#define SIZE    1e9
#define THREADS 8

/*************************************************************
 * Sequential implementation
 *************************************************************/
double sum(int *arr, int size) {
  double acum = 0;
  int i;

  for (i = 0; i < size; i++) {
    acum += arr[i];
  }
  return acum;
}

/*************************************************************
 * Concurrent implementation
 *************************************************************/
 typedef struct {
   int start, end; // [start, end)
   int *arr;
 } Block;

void* partial_sum(void* param) {
  double *acum;
  Block *block;
  int i;

  block = (Block*) param;
  acum = (double*) malloc(sizeof(double));
  (*acum) = 0;
  for (i = block->start; i < block->end; i++) {
    (*acum) += block->arr[i];
  }
  return ( (void**) acum );
}

/*************************************************************
 * Main
 *************************************************************/
int main(int argc, char* argv[]) {
  int *arr, block_size, i, j;
  double result, seq, concur, *acum;
  Block blocks[THREADS];
  pthread_t tids[THREADS];

  arr = (int *) malloc(sizeof(int) * SIZE);
  fill_array(arr, SIZE);
  display_array("arr:", arr);

  printf("Running sequential code..\n");
  seq = 0;
  for (i = 0; i < N; i++) {
    start_timer();
    result = sum(arr, SIZE);
    seq += stop_timer();
  }
  printf("sum = %.0lf - time = %.4lf\n", result, (seq / N));

  block_size = SIZE / THREADS;
  for (i = 0; i < THREADS; i++) {
    blocks[i].arr = arr;
    blocks[i].start = i * block_size;
    if (i != (THREADS - 1)) {
      blocks[i].end = (i + 1) * block_size;
    } else {
      blocks[i].end = SIZE;
    }
  }

  printf("Running concurrent code..\n");
  concur = 0;
  for (j = 0; j < N; j++) {
    start_timer();
    result = 0;
    for (i = 0; i < THREADS; i++) {
      pthread_create(&tids[i], NULL, partial_sum,
        (void*) &blocks[i]);
    }
    for (i = 0; i < THREADS; i++) {
  		pthread_join(tids[i], (void*) &acum);
      result += (*acum);
      free(acum);
  	}
    concur += stop_timer();
  }
  printf("sum = %.0lf - time = %.4lf\n", result, (concur / N));

  printf("speedup = %.6lf\n", (seq / concur));

  free(arr);
}
