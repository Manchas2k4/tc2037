#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

const int MAX = 10;
int acum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* add(void *param) {
  for (int i = 0; i < MAX; i++) {
    pthread_mutex_lock(&mutex);
    acum = acum + 1;
    cout << "add acum = " << acum << "\n";
    pthread_mutex_unlock(&mutex);
    sleep((rand() % 3) + 1);
  }
  pthread_exit(0);
}

void* sub(void *param) {
  for (int i = 0; i < MAX; i++) {
    pthread_mutex_lock(&mutex);
    acum = acum - 1;
    cout << "sub acum = " << acum << "\n";
    pthread_mutex_unlock(&mutex);
    sleep((rand() % 3) + 1);
  }
  pthread_exit(0);
}

int main(int argc, char* argv[]) {
  pthread_t t1, t2;

  pthread_create(&t1, NULL, add, NULL);
  pthread_create(&t2, NULL, sub, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}
