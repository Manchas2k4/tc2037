#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <algorithm>
#include <cmath>
#include "utils.h"

const int RECTS = 100000000; //1e9
const double PI = 3.141592653589793238;
const int THREADS = 8;

using namespace std;

/*--------------------- MONO THREAD ---------------------*/
double integration(double inf, double sup, double (*fn) (double)) {
  double acum, dx;

  acum = 0;
  dx = (sup - inf) / RECTS;
  for (int i = 0; i < RECTS; i++) {
    acum += fn(inf + (i * dx));
  }
  return (acum * dx);
}

/*--------------------- MULTI THREAD ---------------------*/
typedef struct {
  int start, end; // [start, end)
  double (*fn) (double);
  double dx;
  double acum;
} Block;

void* partialIntegration(void* param) {
  Block *block;
  double acum;

  block = (Block*) param;
  acum = 0;
  for (int i = block->start; i < block->end; i++) {
    acum += block->fn(block->start + (i * block->dx));
  }
  block->acum = acum;
  pthread_exit(0);
}

int main(int argc, char* argv[] ) {
  double ms, result;
  int blockSize;
  pthread_t tids[THREADS];
  Block blocks[THREADS];

  /*--------------------- MONO THREAD ---------------------*/
  ms = 0;
  for (int i = 0; i < N; i++) {
    start_timer();
    result = integration(0, PI, sin);
    ms += stop_timer();
  }
  cout << "---- Serial ----\n";
  cout << "Result = " << result << "\n";
  cout << "Time = " << (ms / N) << "ms\n";

  /*--------------------- MULTI THREAD ---------------------*/
  blockSize = RECTS / THREADS;
  for (int i = 0; i < THREADS; i++) {
    blocks[i].start = i * blockSize;
    blocks[i].end = (i != (THREADS - 1))? ((i + 1) * blockSize) : RECTS;
    blocks[i].fn = sin;
    blocks[i].dx = PI / RECTS;
    blocks[i].acum = 0;
  }

  ms = 0;
  for (int i = 0; i < N; i++) {
    start_timer();

    for (int j = 0; j < THREADS; j++) {
      pthread_create(&tids[j], NULL, partialIntegration, (void*) &blocks[j]);
    }

    result = 0;
    for (int j = 0; j < THREADS; j++) {
      pthread_join(tids[j], NULL);
      result += (blocks[j].acum * blocks[j].dx);
    }

    ms += stop_timer();
  }
  cout << "---- Multithread ----\n";
  cout << "Result = " << result << "\n";
  cout << "Time = " << (ms / N) << "ms\n";

  return 0;
}
