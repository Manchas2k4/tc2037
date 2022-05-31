#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

using namespace std;

const int RENS = 30000;
const int COLS = 30000;
const int THREADS = 8;

/*--------------------- MONO THREAD ---------------------*/
// C = M x V
void matrixXVector(int *C, const int *M, const int *V) {
  double acum;

  for (int i = 0; i < RENS; i++) {
    acum = 0;
    for (int j = 0; j < COLS; j++) {
      acum += M[(i * COLS) + j] * V[i];
    }
    C[i] = acum;
  }
}
/*--------------------- MULTI THREAD ---------------------*/
typedef struct {
  int start, end; //RENS
  int *C, *M, *V;
} Block;

void* partialMult(void *param) {
  Block *block;
  double acum;

  block = (Block*) param;
  for (int i = block->start; i < block->end; i++) {
    acum = 0;
    for (int j = 0; j < COLS; j++) {
      acum += block->M[(i * COLS) + j] * block->V[i];
    }
    block->C[i] = acum;
  }
  pthread_exit(0);
}

int main(int argc, char* argv[]) {
  int *C, *M, *V, blockSize;
  double ms, acum;
  pthread_t tids[THREADS];
  Block blocks[THREADS];

  M = new int[RENS * COLS];
  V = new int[RENS];
  C = new int[RENS];

  for (int i = 0; i < RENS; i++) {
    for (int j = 0; j < COLS; j++) {
      M[(i * COLS) + j] = (j + 1);
    }
    V[i] = 1;
  }

  /*--------------------- MONO THREAD ---------------------*/
  acum = 0;
  for (int j = 0; j < N; j++) {
    start_timer();
    matrixXVector(C, M, V);
    ms += stop_timer();
  }
  cout << "Monothread\n";
  display_array("C = ", C);
  cout << "Time = " << (ms / N) << " ms\n";

  /*--------------------- MULTI THREAD ---------------------*/
  blockSize = RENS / THREADS;
  for (int i = 0; i < THREADS; i++) {
    blocks[i].start = i * blockSize;
    blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : RENS;
    blocks[i].C = C;
    blocks[i].M = M;
    blocks[i].V = V;
  }

  ms = 0;
  for (int j = 0; j < N; j++) {
    start_timer();

    for (int i = 0; i < THREADS; i++) {
      pthread_create(&tids[i], NULL, partialMult, (void*) &blocks[i]);
    }

    for (int i = 0; i < THREADS; i++) {
      pthread_join(tids[i], NULL);
    }

    ms += stop_timer();
  }
  cout << "Multithread\n";
  display_array("C = ", C);
  cout << "Time = " << (ms / N) << " ms\n";

  delete [] M;
  delete [] V;
  delete [] C;
  return 0;
}
