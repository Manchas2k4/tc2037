/*************************************************************
* File: problem3.c
* Author: Pedro Perez
* Description: This file contains the implementation of
*              the merge sort algorithm.
*
* To compile: gcc mergesort.c
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
 * Sequential implementation
 *************************************************************/
void split(int *A, int *B, int low, int high) {
  int  mid, size, i, j;

  size = high - low + 1;
  if (size < GRAIN) {
    simpleSort(A, B, low, high, size);
    return;
  }
  //if (high - low == 0) return;

  mid = low + ((high - low) / 2);
  split(A, B, low, mid);
  split(A, B, mid +1, high);
  merge(A, B,low, mid, high);
  copy_array(A,B, low, high);
}

void merge_sort(int *A, int size) {
  int *B = (int*) malloc(sizeof(int) * size);
  split(A, B, 0, size - 1);
  free(B);
}

/*************************************************************
 * Main
 *************************************************************/
int main(int argc, char* argv[]) {
  int i, j, *a, *aux;
  double seq;

  a = (int*) malloc(sizeof(int) * SIZE);
	aux = (int*) malloc(sizeof(int) * SIZE);
	random_array(a, SIZE);
	display_array("before", a);

  printf("Running sequential code..\n");
  seq = 0;
  for (i = 0; i < N; i++) {
    memcpy(aux, a, sizeof(int) * SIZE);

    start_timer();
    merge_sort(aux, SIZE);
    seq += stop_timer();

  }
  display_array("after", aux);
  printf("time = %.4lf\n", (seq / N));

  free(aux); free(a);
}
