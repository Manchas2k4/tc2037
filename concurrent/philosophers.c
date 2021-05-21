/**
* To compile: gcc philosophers.c -pthread
**/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define PHILOSOPHERS      5
#define EATING_TIME       3
#define MAX_TIMES         3

typedef enum {USED, FREE} Status;

typedef struct {
	int id;
	int waiting_times;
} Philosopher;

int sticks[PHILOSOPHERS];
pthread_cond_t cond[PHILOSOPHERS];
Philosopher* philosophers[PHILOSOPHERS];
pthread_t tids[PHILOSOPHERS];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int left_stick(int id) {
  return id;
}

int right_stick(int id) {
  return (id + 1) % PHILOSOPHERS;
}

int left_philosopher(int id) {
  return ((id == 0)? PHILOSOPHERS - 1 : id - 1);
}

int right_philosopher(int id) {
  return ((id == PHILOSOPHERS - 1)? 0 : id + 1);
}

void print_status() {
	printf("S1\tS2\tS3\tS4\ts5\n");
	printf("%c\t%c\t%c\t%c\t%c\n",
      sticks[0] == 0 ? 'U' : 'F',
      sticks[1] == 0 ? 'U' : 'F',
      sticks[2] == 0 ? 'U' : 'F',
      sticks[3] == 0 ? 'U' : 'F',
      sticks[4] == 0 ? 'U' : 'F');
}

void think(Philosopher *philosopher) {
	int thinking_time = (rand() % 5) + 3;
	printf("P: %d thinking for %d seconds.\n",
      philosopher->id + 1, thinking_time);
	sleep(thinking_time);
}

void take_chopsticks(Philosopher *philosopher) {
	pthread_mutex_lock(&mutex);

	print_status();

	while (sticks[left_stick(philosopher->id)] == USED ||
         sticks[right_stick(philosopher->id)] == USED) {
		philosopher->waiting_times++;
		printf("P: %d waiting - Total: %d\n",
        philosopher->id + 1, philosopher->waiting_times);
		pthread_cond_wait(&cond[philosopher->id], &mutex);
	}

	printf("P: %d taking the chopsticks.\n", philosopher->id + 1);
	sticks[left_stick(philosopher->id)] = USED;
	sticks[right_stick(philosopher->id)] = USED;

	pthread_mutex_unlock(&mutex);
}

void eat(Philosopher *philosopher) {
	sleep(EATING_TIME);
	philosopher->waiting_times = 0;
	printf("P: %d eating for %d seconds.\n",
    philosopher->id + 1, EATING_TIME);
}

void leave_chopsticks(Philosopher *philosopher) {
	pthread_mutex_lock(&mutex);

	sticks[left_stick(philosopher->id)] = FREE;
	sticks[right_stick(philosopher->id)] = FREE;

	pthread_cond_signal(&cond[right_philosopher(philosopher->id)]);
	pthread_cond_signal(&cond[left_philosopher(philosopher->id)]);

	pthread_mutex_unlock(&mutex);
}

void* task(void *param) {
  int i = 0;

	Philosopher *philosopher = (Philosopher *) param;
	srand(philosopher->id);
	while(i < MAX_TIMES) {
		think(philosopher);
		take_chopsticks(philosopher);
		eat(philosopher);
		leave_chopsticks(philosopher);
    i++;
	}

	return ( (void *) 0 );
}

int main(int argc, char* argv[]) {
  int i;

  for (i = 0; i < PHILOSOPHERS; i++) {
    sticks[i] = FREE;
  }

  for (i = 0; i < PHILOSOPHERS; i++) {
    philosophers[i] = (Philosopher*) malloc(sizeof(Philosopher));
    philosophers[i]->id = i;
    philosophers[i]->waiting_times = 0;
    pthread_create(&tids[i], NULL, task, philosophers[i]);
  }

  for (i = 0; i < PHILOSOPHERS; i++) {
    pthread_join(tids[i], NULL);
    free(philosophers[i]);
  }

  return 0;
}
