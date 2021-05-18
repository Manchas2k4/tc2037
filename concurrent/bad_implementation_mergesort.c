/*************************************************************
* File: problem3.c
* Author: Pedro Perez
* Description: This file contains a bad implementation of
*              the merge sort algorithm.
*
* To compile: gcc bad_implementation_mergesort.c -pthread
*
* Copyright (c) 2021 by Tecnologico de Monterrey.
* All Rights Reserved. May be reproduced for any non-commercial
* purpose.
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "utils.h"

#define SIZE    1e7
#define GRAIN   1e3
#define THREADS 8

void swap(int *a, int i, int j) {
  int aux = a[i];
  a[i] = a[j];
  a[j] = aux;
}

void simpleSort(int *A, int *B, int low, int high, int size) {
  for(int i = low + 1; i < size; i++){
    for(int j = i; j > low && A[j] < A[j - 1]; j--){
      swap(A, j, j - 1);
    }
  }
}

void copy_array(int *A, int *B, int low, int high) {
	int size = high - low + 1;
	memcpy(A + low, B + low, sizeof(int) * size);
}

void merge(int *A, int *B, int low, int mid, int high) {
    int i, j, k;
    i = low;
    j = mid + 1;
    k = low;
    while(i <= mid && j <= high){
        if(A[i] < A[j]){
            B[k] = A[i];
            i++;
        }else{
            B[k] = A[j];
            j++;
        }
        k++;
    }
    for(; j <= high; j++){
        B[k++] = A[j];
    }

	for(; i <= mid; i++){
        B[k++] = A[i];
    }
}

/*************************************************************
 * Concurrent implementation
 *************************************************************/
 typedef struct {
   int low, high;
   int *A, *B;
 } Block;

void* parallel_split(void* param) {
  Block *block, *left, *right;
  int  mid, size, i, j;
  pthread_t tids[2];

  block = (Block *) param;

  size = block->high - block->low + 1;
  if (size < GRAIN) {
    simpleSort(block->A, block->B, block->low, block->high, size);
    return ( (void*) 0 );
  }

  mid = block->low + ((block->high - block->low) / 2);

  left = (Block*) malloc(sizeof(Block));
  left->A = block->A;
  left->B = block->B;
  left->low = block->low;
  left->high = mid;
  pthread_create(&tids[0], NULL, parallel_split, (void*) left);

  right = (Block*) malloc(sizeof(Block));
  right->A = block->A;
  right->B = block->B;
  right->low = mid + 1;
  right->high = block->high;
  pthread_create(&tids[1], NULL, parallel_split, (void*) right);

  for (i = 0; i < 2; i++) {
    pthread_join(tids[i], NULL);
  }

  free(left);
  free(right);

  merge(block->A, block->B, block->low, mid, block->high);
  copy_array(block->A, block->B, block->low, block->high);

  return ( (void*) 0 );
}

/*************************************************************
 * Main
 *************************************************************/
int main(int argc, char* argv[]) {
  int i, j, *a, *aux;
  double seq, concur;
  pthread_t tid;
  Block init;

  a = (int*) malloc(sizeof(int) * SIZE);
	aux = (int*) malloc(sizeof(int) * SIZE);
	random_array(a, SIZE);
	display_array("before", a);

  init.A = aux;
  init.B = (int*) malloc(sizeof(int) * SIZE);
  init.low = 0;
  init.high = SIZE - 1;

  printf("Running concurrent code..\n");
  concur = 0;
  for (j = 0; j < N; j++) {
    memcpy(aux, a, sizeof(int) * SIZE);

    start_timer();
    pthread_create(&tid, NULL, parallel_split, (void*) &init);
    pthread_join(tid, NULL);

    concur += stop_timer();
  }
  display_array("after", aux);
  printf("time = %.4lf\n", (concur / N));

  printf("speedup = %.6lf\n", (seq / concur));

  free(init.B); free(aux); free(a);
}
