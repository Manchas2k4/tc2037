#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <algorithm>
#include "utils.h"

const int SIZE = 1000000000; //1e9
const int THREADS = 8;

using namespace std;

/*--------------------- MONO THREAD ---------------------*/
int minimum(int *arr, int size) {
  int result = arr[0];
  for (int i = 1; i < size; i++) {
    result = min(result, arr[i]);
  }
  return result;
}

/*--------------------- MULTI THREAD ---------------------*/
typedef struct {
  int start, end; // [start, end)
  int *arr;
  int result;
} Block;

void* partialMinimum(void* param) {
  Block *block;
  int result;

  block = (Block*) param;
  result = block->arr[block->start];
  for (int i = block->start + 1; i < block->end; i++) {
    result = min(result, block->arr[i]);
  }
  block->result = result;
  pthread_exit(0);
}

int main(int argc, char* argv[] ) {
  int *data, blockSize, result;
  double ms;
  pthread_t tids[THREADS];
  Block blocks[THREADS];

  data = new int[SIZE];
  fill_array(data, SIZE);
  display_array("data = ", data);

  data[999999] = 0;

  /*--------------------- MONO THREAD ---------------------*/
  ms = 0;
  for (int i = 0; i < N; i++) {
    start_timer();
    result = minimum(data, SIZE);
    ms += stop_timer();
  }
  cout << "---- Serial ----\n";
  cout << "Result = " << result << "\n";
  cout << "Time = " << (ms / N) << "ms\n";

  /*--------------------- MULTI THREAD ---------------------*/
  blockSize = SIZE / THREADS;
  for (int i = 0; i < THREADS; i++) {
    blocks[i].start = i * blockSize;
    blocks[i].end = (i != (THREADS - 1))? ((i + 1) * blockSize) : SIZE;
    blocks[i].arr = data;
    blocks[i].result = -1;
  }

  ms = 0;
  for (int i = 0; i < N; i++) {
    start_timer();

    for (int j = 0; j < THREADS; j++) {
      pthread_create(&tids[j], NULL, partialMinimum, (void*) &blocks[j]);
    }

    result = 0;
    for (int j = 0; j < THREADS; j++) {
      pthread_join(tids[j], NULL);
      result = min(result, blocks[j].result);
    }

    ms += stop_timer();
  }
  cout << "---- Multithread ----\n";
  cout << "Result = " << result << "\n";
  cout << "Time = " << (ms / N) << "ms\n";

  delete [] data;
  return 0;
}
