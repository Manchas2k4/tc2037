// =================================================================
//
// File: bridge.cpp
// Author: Pedro Perez
// Description: This file contains the solution to the pizzeria 
//              synchronization problem using pthreads.
//
//              To compile: g++ solution02.cpp -lpthread
//
// Copyright (c) 2023 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>
#include <unistd.h>
#include <pthread.h>

using namespace std;

const int MAX_CARS = 3;
const int MAX_RUNS = 3;
const int THREADS = 8;
const int NORTH = 0;
const int SOUTH = 1;

int currentDirection;
int pasingCars;
int waitingCars[2];

pthread_mutex_t screen;
pthread_mutex_t mutex;
pthread_cond_t lockPerSide[2];

bool isSafe(int direction) {
    if (pasingCars == 0) {
        return true;
    } else if ((pasingCars < MAX_CARS) && (currentDirection == direction)) {
        return true;
    } else {
        return false;
    }
}

void arriveBrige(int direction) {
    pthread_mutex_lock(&mutex);
    if (!isSafe(direction)) {
        waitingCars[direction]++;
        while (!isSafe(direction)) {
            pthread_cond_wait(&lockPerSide[direction], &mutex);
        }
        waitingCars[direction]--;
    }
    pasingCars++;
    currentDirection = direction;
    pthread_mutex_unlock(&mutex);
}

void exitBrige(int direction) {
    pthread_mutex_lock(&mutex);
    pasingCars--;
    if (pasingCars > 0) {
        pthread_cond_signal(&lockPerSide[direction]);
    } else {
        if (waitingCars[1 - direction] != 0) {
            pthread_cond_signal(&lockPerSide[1 - direction]);
        } else {
            pthread_cond_signal(&lockPerSide[direction]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void* oneVehicle(void* param) {
    int id, direction;

    id = *((int*) param);
    mt19937 generator(clock() + id);
    uniform_real_distribution<float> random1(0.0, 1.0);
    uniform_int_distribution<int> random2(1, 3);

    pthread_mutex_lock(&screen);
    cout << "Vehicle " << id << " has started...\n";
    pthread_mutex_unlock(&screen);
    for (int i = 0; i < MAX_RUNS; i++) {
        direction = (random1(generator) <= 0.5)? NORTH : SOUTH;

        pthread_mutex_lock(&screen);
        cout << "Vehicle " << id << " arrives at the bridge in direction to " 
            << ((direction == NORTH)? "north" : "south") << " ...\n";
        pthread_mutex_unlock(&screen);

        arriveBrige(direction);

        pthread_mutex_lock(&screen);
        cout << "Vehicle " << id << " is crossing the bridge to " 
            << ((direction == NORTH)? "north" : "south") << " ...\n";
        pthread_mutex_unlock(&screen);

        sleep(random2(generator));

        exitBrige(direction);

        pthread_mutex_lock(&screen);
        cout << "Vehicle " << id << " is done...\n";
        pthread_mutex_unlock(&screen);
    }

    pthread_mutex_lock(&screen);
    cout << "Vehicle " << id << " has finished all its runs...\n";
    pthread_mutex_unlock(&screen);

    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    pthread_t tids[THREADS];
    int ids[THREADS];

    currentDirection = NORTH;
    pasingCars = 0;
    waitingCars[NORTH] = waitingCars[SOUTH] = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&screen, NULL);
    pthread_cond_init(&lockPerSide[NORTH], NULL);
    pthread_cond_init(&lockPerSide[SOUTH], NULL);

    for (int i = 0; i < THREADS; i++) {
        ids[i] = i;
        pthread_create(&tids[i], NULL, oneVehicle, &ids[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(tids[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&screen);
    pthread_cond_destroy(&lockPerSide[NORTH]);
    pthread_cond_destroy(&lockPerSide[SOUTH]);

    return 0;
}
