#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

using namespace std;

const int SIZE = 1000000000; //1e9
const int THREADS = 8;

/********* MONO THREAD *********/
double sum(int *arr, int size) {
  double acum = 0;
  for (int i = 0; i < size; i++) {
    acum += arr[i];
  }
  return acum;
}

/********* MULTI THREAD *********/
typedef struct {
  int start, end; //[start, end)
  int *arr;
  double result;
} Block;

void* partialSum(void *param) {
  Block *block;
  double acum = 0;

  block = (Block*) param;
  for (int i = block->start; i < block->end; i++) {
    acum += block->arr[i];
  }
  block->result = acum;
  pthread_exit(0);
}

int main(int argc, char* argv[]) {
  int *arr, blockSize;
  double result, ms;
  pthread_t tids[THREADS];
  Block blocks[THREADS];

  arr = new int[SIZE];
  fill_array(arr, SIZE);
  display_array("arr = ", arr);

  /********* MONO THREAD *********/
  ms = 0;
  for (int i = 0; i < N; i++) {
    start_timer();
    result = sum(arr, SIZE);
    ms += stop_timer();
  }
  cout << "Result = " << result << "\n";
  cout << "Monothread Time = " << (ms / N) << "\n";

  /********* MULTI THREAD *********/
  blockSize = SIZE / THREADS;
  for (int i = 0; i < THREADS; i++) {
    blocks[i].start = i * blockSize;
    blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : SIZE;
    blocks[i].arr = arr;
    blocks[i].result = 0;
  }

  ms = 0;
  for (int j = 0; j < N; j++) {
    start_timer();

    for (int i = 0; i < THREADS; i++) {
      pthread_create(&tids[i], NULL, partialSum, (void*) &blocks[i]);
    }

    result = 0;
    for (int i = 0; i < THREADS; i++) {
      pthread_join(tids[i], NULL);
      result += blocks[i].result;
    }

    ms += stop_timer();
  }
  cout << "Result = " << result << "\n";
  cout << "Multithread Time = " << (ms / N) << "\n";

  delete [] arr;
  return 0;
}
