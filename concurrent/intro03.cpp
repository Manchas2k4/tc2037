#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

const int LIMIT = 5;
const int THREADS = 4;

using namespace std;

void* task(void* param) {
  int *id;

  id = (int*) param;
  for (int i = 0; i < LIMIT; i++) {
    cout << "TID = " << (*id)
         << " i = " << i << "\n";
  }
  delete id;
  pthread_exit(0);
}

int main(int argc, char* argv[]) {
  pthread_t tid[THREADS];
  int *j;

  for (int i = 0; i < THREADS; i++) {
    j = new int;
    *j = i;
    pthread_create(&tid[i], NULL, task, (void*) j);
  }

  for (int i = 0; i < THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  return 0;
}
