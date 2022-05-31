#include <iostream>
#include <unistd.h>
#include <pthread.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

using namespace std;

const int SIZE = 10;

int buffer[SIZE];
int front = 0, rear = 0, count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void enqueue(int element) {
  buffer[rear] = element;
  rear = (rear + 1) % SIZE;
  count++;
}

int dequeue() {
  int result = buffer[front];
  front = (front + 1) % SIZE;
  count--;
  return result;
}

void printQueue() {
  for (int i = 0; i < SIZE; i++) {
    if (i >= MIN(front, rear) && i <= MAX(front, rear)) {
      cout << buffer[i] << " ";
    } else {
      cout << "X ";
    }
  }
  cout << "\n";
}

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
