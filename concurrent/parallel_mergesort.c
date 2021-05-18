/*************************************************************
* File: problem3.c
* Author: Pedro Perez
* Description: This file contains a parallel implementation of
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

#define SIZE    1e8
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

 void split(int *A, int *B, int low, int high) {
   int  mid, size, i, j;

   /*
   size = high - low + 1;
   if (size < GRAIN) {
     simpleSort(A, B, low, high, size);
     return;
   }
   */
   if (high - low == 0) return;

   mid = low + ((high - low) / 2);
   split(A, B, low, mid);
   split(A, B, mid + 1, high);
   merge(A, B,low, mid, high);
   copy_array(A,B, low, high);
 }


void* parrallel_sort(void* param) {
  Block *block;

  block = (Block *) param;
  split(block->A, block->B, block->low, block->high);
  return ( (void*) 0 );
}

void redux() {
  int i, inc, gap;

  inc = 2;
  gap = 1;
  while (inc <= THREADS) {
    for (i = 0; i < THREADS; i += inc) {
      printf("merge %i with %i\n", i, (i + gap));
    }
    inc *= 2;
    gap *= 2;
    printf("\n");
  }
}


/*************************************************************
 * Main
 *************************************************************/
int main(int argc, char* argv[]) {
  int i, j, block_size;
  double concur;
  Block blocks[THREADS];
  pthread_t tids[THREADS];
  int *a, *aux, *b, inc, gap;

  a = (int*) malloc(sizeof(int) * SIZE);
	aux = (int*) malloc(sizeof(int) * SIZE);
  b = (int*) malloc(sizeof(int) * SIZE);
	random_array(a, SIZE);
	display_array("before", a);

  block_size = SIZE / THREADS;
  for (i = 0; i < THREADS; i++) {
    blocks[i].A = aux;
    blocks[i].B = b;
    blocks[i].low = i * block_size;
    if (i != (THREADS - 1)) {
      blocks[i].high = ((i + 1) * block_size) - 1;
    } else {
      blocks[i].high = (SIZE - 1);
    }
  }

  printf("Running concurrent code..\n");
  concur = 0;
  for (j = 0; j < N; j++) {
    memcpy(aux, a, sizeof(int) * SIZE);

    start_timer();
    for (i = 0; i < THREADS; i++) {
      pthread_create(&tids[i], NULL, parrallel_sort,
        (void*) &blocks[i]);
    }
    for (i = 0; i < THREADS; i++) {
  		pthread_join(tids[i], NULL);
  	}

    inc = 2;
    gap = 1;
    while (inc <= THREADS) {
      for (i = 0; i < THREADS; i += inc) {
        merge(aux, b, blocks[i].low, blocks[i].high,
              blocks[i + gap].high);
      }
      memcpy(b, aux, sizeof(int) * SIZE);
      inc *= 2;
      gap *= 2;
    }

    concur += stop_timer();
  }
  display_array("after", aux);
  printf("time = %.4lf\n", (concur / N));

  free(b); free(aux); free(a);

  return 0;
}
