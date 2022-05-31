#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <algorithm>
#include "utils.h"

using namespace std;

const int SIZE = 1000000000; //1e9
const int THREADS = 8;

/********* MONO THREAD *********/
int minimum(int *arr, int size) {
  int result = arr[0];
  for (int i = 1; i < size; i++) {
    //result = (arr[i] < result)? arr[i] : result;
    result = MIN(result, arr[i]);
  }
  return result;
}

/********* MULTI THREAD *********/
typedef struct {
  int start, end; //[start, end)
  int *arr;
  int result;
} Block;

void* partialMinimum(void *param) {
  Block *block;
  int result = 0;

  block = (Block*) param;
  result = block->arr[block->start];
  for (int i = block->start + 1; i < block->end; i++) {
    //result = (block->arr[i] < result)? block->arr[i] : result;
    result = MIN(result, block->arr[i]);
  }
  block->result = result;
  pthread_exit(0);
}

int main(int argc, char* argv[]) {
  int *arr, blockSize, result;
  double ms;
  pthread_t tids[THREADS];
  Block blocks[THREADS];

  arr = new int[SIZE];
  fill_array(arr, SIZE);
  display_array("arr = ", arr);

  arr[123456] = 0;

  /********* MONO THREAD *********/
  ms = 0;
  for (int i = 0; i < N; i++) {
    start_timer();
    result = minimum(arr, SIZE);
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
      pthread_create(&tids[i], NULL, partialMinimum, (void*) &blocks[i]);
    }

    result = arr[0];
    for (int i = 0; i < THREADS; i++) {
      pthread_join(tids[i], NULL);
      result = min(result, blocks[i].result);
    }

    ms += stop_timer();
  }
  cout << "Result = " << result << "\n";
  cout << "Multithread Time = " << (ms / N) << "\n";

  delete [] arr;
  return 0;
}
