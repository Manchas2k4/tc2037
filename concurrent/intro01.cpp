#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

const int LIMIT = 10;
const int THREADS = 4;

using namespace std;

void* task(void* param) {
  for (int i = 0; i < LIMIT; i++) {
    cout << "TID = " << pthread_self()
         << " i = " << i << "\n";
    sleep(1);
  }
  pthread_exit(0);
}

int main(int argc, char* argv[]) {
  pthread_t tid;

  pthread_create(&tid, NULL, task, NULL);

  pthread_join(tid, NULL);

  cout << "The pthread has finished\n";

  return 0;
}
