/*************************************************************
* File: problem2.c
* Author: Pedro Perez
* Description: This file contains the code to perform the
*              numerical integration of a function within a
*              defined interval using pthreads.
*
* To compile: gcc problem2.c -pthread
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
#include <math.h>
#include "utils.h"

#define PI      3.14159265358979323846
#define RECTS   1e8
#define THREADS 8

/*************************************************************
 * Sequential implementation
 *************************************************************/
double integration(double inf, double sup, double (*fn) (double)) {
  double x, dx, acum;
  int i;

  x = inf;
  dx = (sup - inf) / RECTS;
  acum = 0;
  for (i = 0; i < RECTS; i++) {
    acum += fn(x + (i * dx));
  }
  acum = (acum * dx);
}

/*************************************************************
 * Concurrent implementation
 *************************************************************/
 typedef struct {
   double start, end;
   double x, dx;
   double (*fn) (double);
 } Block;

void* partial_integration(void* param) {
  double *acum;
  Block *block;
  int i;

  block = (Block*) param;
  acum = (double*) malloc(sizeof(double));
  (*acum) = 0;
  for (i = block->start; i < block->end; i++) {
    (*acum) += block->fn(block->x + (i * block->dx));
  }
  return ( (void **) acum );
}

/*************************************************************
 * Main
 *************************************************************/
int main(int argc, char* argv[]) {
  int i, j, block_size;
  double result, seq, concur, *acum;
  Block blocks[THREADS];
  pthread_t tids[THREADS];
  double inf, sup, dx;
  double (*fn) (double);

  inf = 0; sup = PI;
  dx = (sup - inf) / RECTS;
  fn = sin;

  printf("Running sequential code..\n");
  seq = 0;
  for (i = 0; i < N; i++) {
    start_timer();
    result = integration(inf, sup, fn);
    seq += stop_timer();
  }
  printf("sum = %.0lf - time = %.4lf\n", result, (seq / N));

  block_size = RECTS / THREADS;
  for (i = 0; i < THREADS; i++) {
    blocks[i].x = inf;
    blocks[i].dx = dx;
    blocks[i].fn = fn;
    blocks[i].start = i * block_size;
    if (i != (THREADS - 1)) {
      blocks[i].end = (i + 1) * block_size;
    } else {
      blocks[i].end = RECTS;
    }
  }

  printf("Running concurrent code..\n");
  concur = 0;
  for (j = 0; j < N; j++) {
    start_timer();
    result = 0;
    for (i = 0; i < THREADS; i++) {
      pthread_create(&tids[i], NULL,
        partial_integration, (void*) &blocks[i]);
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
}
