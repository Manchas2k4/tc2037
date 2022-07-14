#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

const int THREADS = 4;
const int BLOCK_SIZE = 10;

// [start, end)
typedef struct {
  int id, start, end;
} Block;

using namespace std;

void* task(void* param) {
  Block *b;

  b = (Block*) param;
  for (int i = b->start; i < b->end; i++) {
    cout << "TID = " << b->id << " i = " << i << "\n";
  }
  pthread_exit(0);
}

int main(int argc, char* argv[]) {
  pthread_t tid[THREADS];
  Block blocks[THREADS];

  for (int i = 0; i < THREADS; i++) {
    blocks[i].id = i;
    blocks[i].start = i * BLOCK_SIZE;
    blocks[i].end = (i + 1) * BLOCK_SIZE;
  }

  for (int i = 0; i < THREADS; i++) {
    pthread_create(&tid[i], NULL, task, (void*) &blocks[i]);
  }

  for (int i = 0; i < THREADS; i++) {
    pthread_join(tid[i], NULL);
  }

  return 0;
}
