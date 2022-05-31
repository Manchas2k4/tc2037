#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

const int SIZE = 1000000000; //1e9
const int THREADS = 8;

using namespace std;

/*--------------------- MONO HILO ---------------------*/
double sum(int *arr, int size) {
  double acum = 0;
  for (int i = 0; i < size; i++) {
    acum += arr[i];
  }
  return acum;
}

/*--------------------- MULTI HILO ---------------------*/
typedef struct {
  int start, end; // [start, end)
  int *arr;
  double acum;
} Block;

void* partialSum(void* param) {
  Block *block;
  double acum;

  block = (Block*) param;
  acum = 0;
  for (int i = block->start; i < block->end; i++) {
    acum += block->arr[i];
  }
  block->acum = acum;
  pthread_exit(0);
}

int main(int argc, char* argv[] ) {
  int *data, blockSize;
  double ms, result;
  pthread_t tids[THREADS];
  Block blocks[THREADS];

  data = new int[SIZE];
  fill_array(data, SIZE);
  display_array("data = ", data);

  /*--------------------- MONO HILO ---------------------*/
  ms = 0;
  for (int i = 0; i < N; i++) {
    start_timer();
    result = sum(data, SIZE);
    ms += stop_timer();
  }
  cout << "---- Serial ----\n";
  cout << "Result = " << result << "\n";
  cout << "Time = " << (ms / N) << "ms\n";

  /*--------------------- MULTI HILO ---------------------*/
  blockSize = SIZE / THREADS;
  for (int i = 0; i < THREADS; i++) {
    blocks[i].start = i * blockSize;
    blocks[i].end = (i != (THREADS - 1))? ((i + 1) * blockSize) : SIZE;
    blocks[i].arr = data;
    blocks[i].acum = 0;
  }

  ms = 0;
  for (int i = 0; i < N; i++) {
    start_timer();

    for (int j = 0; j < THREADS; j++) {
      pthread_create(&tids[j], NULL, partialSum, (void*) &blocks[j]);
    }

    result = 0;
    for (int j = 0; j < THREADS; j++) {
      pthread_join(tids[j], NULL);
      result += blocks[j].acum;
    }

    ms += stop_timer();
  }
  cout << "---- Multithread ----\n";
  cout << "Result = " << result << "\n";
  cout << "Time = " << (ms / N) << "ms\n";

  delete [] data;
  return 0;
}
