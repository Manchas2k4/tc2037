#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "utils.h"

#define SIZE  1e9
#define LIMIT 10000
#define N     10

long sum(int* data, int size) {
  long acum;
  int i;

  acum = 0;
  for (i = 0; i < size; i++) {
    acum += data[i];
  }
  return acum;
}

int main(int argc, char* argv[]) {
  int *data, i;
  long result;
  double ms;

  srand(time(0));
  data = (int*) malloc(sizeof(int) * SIZE);
  for (i = 0; i < SIZE; i++) {
    data[i] = (rand() % LIMIT) + 1;
  }

  ms = 0;
  for (i = 0; i < N; i++) {
    start_timer();
    result = sum(data, SIZE);
    ms += stop_timer();
  }
  printf("avg time = %.3lf ms\n", (ms / N));
  printf("result = %li\n", result);

  return 0;
}
