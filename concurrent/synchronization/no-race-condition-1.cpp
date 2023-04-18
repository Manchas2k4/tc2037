// =================================================================
//
// File: no-race-condition-1.cpp
// Author: Pedro Perez
// Description: This file implements a synchronization strategy on
//              a shared variable using pthreads. In this example, 
//              the different threads (decrement and increment) 
//              compete to work with the shared variable.
//
//              To compile: g++ no-race-condition-1.cpp -lpthread -o app
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>

using namespace std;

int counter = 0;

const int MAX_SLEEP_TIME = 3;
const int MAX_THREADS = 4;
const int MAX_ITERATIONS = 5;

pthread_mutex_t mutex_lock;

void* increment(void *param) {
    int id, sleepTime;

    id = *((int*) param);
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex_lock);
        cout << "incrementing " << id << " - counter initial value = " << counter << "\n";
        counter++;
        sleepTime = (rand() % MAX_SLEEP_TIME) + 1;
        sleep(sleepTime);
        cout << "incrementing " << id << " - incrementing, counter = " << counter << "\n";
        pthread_mutex_unlock(&mutex_lock);
    }
    pthread_exit(NULL);
}

void* decrement(void *param) {
    int id, sleepTime;

    id = *((int*) param);
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex_lock);
        cout << "decrementing " << id << " - counter initial value = " << counter << "\n";
        counter--;
        sleepTime = (rand() % MAX_SLEEP_TIME) + 1;
        sleep(sleepTime);
        cout << "decrementing " << id << " - decrementing, counter = " << counter << "\n";
        pthread_mutex_unlock(&mutex_lock);
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    pthread_t tids[MAX_THREADS];
    int id[MAX_THREADS];

    srand(1234);

    for (int i = 0; i < MAX_THREADS; i++) {
        id[i] = i;
    }
    pthread_mutex_init(&mutex_lock, NULL);

    for (int i = 0; i < MAX_THREADS; i++) {
        if (rand() % 2 == 0) {
            pthread_create(&tids[i], NULL, increment, (void*) &id[i]);
        } else {
            pthread_create(&tids[i], NULL, decrement, (void*) &id[i]);
        }
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        pthread_join(tids[i], NULL);
    }

    return 0;
}
