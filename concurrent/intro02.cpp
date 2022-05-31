#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

const int LIMIT = 20;
const int THREADS = 4;

using namespace std;

void* task(void* param) {
  for (int i = 0; i < LIMIT; i++) {
    cout << "TID = " << pthread_self()
         << " i = " << i << "\n";
  }
  pthread_exit(0);
}

int main(int argc, char* argv[]) {
  pthread_t tid[THREADS];

  for (int i = 0; i < THREADS; i++) {
    pthread_create(&tid[i], NULL, task, NULL);
  }

  for (int i = 0; i < THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  return 0;
}
