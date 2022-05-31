#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <cmath>
#include "utils.h"

using namespace std;

const int RECTS = 1000000000; //1e9
const double PI = 3.141592653589;

double integration(double inf, double sup, double (*fn) (double)) {
  double acum, dx;

  dx = (sup - inf) / RECTS;
  acum = 0;
  for (int i = 0; i < RECTS; i++) {
    acum += fn(inf + (i * dx));
  }
  return (acum * dx);
}

int main(int argc, char* argv[]) {
  int blockSize;
  double ms, result;
  //pthread_t tids[THREADS];
  //Block blocks[THREADS];

  /********* MONO THREAD *********/
  ms = 0;
  for (int i = 0; i < N; i++) {
    start_timer();
    result = integration(0, PI, sin);
    ms += stop_timer();
  }
  cout << "Result = " << result << "\n";
  cout << "Monothread Time = " << (ms / N) << "\n";

  return 0;
}
