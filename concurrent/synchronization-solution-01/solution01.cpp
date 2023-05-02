// =================================================================
//
// File: solution01.cpp
// Author: Pedro Perez
// Description: This file contains the implementation of the 
//              calculation of Pi using the Monte Carlo method. You 
//              will find the implementation using single thread and
//              multithreading. It also calculates the SpeedUp.
//
//        To compile: g++ solution01.cpp -lpthread
//
// Copyright (c) 2023 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <chrono>
#include <random>
#include <ctime>
#include <pthread.h>
#include "utils.h"

using namespace std;
using namespace std::chrono;

const int POINTS = 1000000000; //1e9
const int THREADS = 8;

// ====================== ONE THREAD IMPLEMENTATION ======================
double aproxPI() {
    int count;
    double x, y;

    srand(time(0));
    count = 0;
    for (int i = 0; i < POINTS; i++) {
        x = -1 + (2.0 * rand()) / RAND_MAX;
        y = -1 + (2.0 * rand()) / RAND_MAX;
        if ( ((x * x) + (y * y))  <= 1.0 ) {
            count++;
        }
    }

    return ((4.0 * count) / (double) POINTS);
}
// ====================== ONE THREAD IMPLEMENTATION ======================

// ===================== MULTITHREAD IMPLEMENTATION ======================
int numberOfPointsInCircle = 0;

pthread_mutex_t mutex_lock;

void* task(void *param) {
    int times, count;
    double x, y;
    mt19937 generator(clock());
    uniform_real_distribution<float> distribution(-1.0, 1.0);

    times = POINTS / THREADS;
    count = 0;
    for (int i = 0; i < times; i++) {
        x = distribution(generator);
        y = distribution(generator);
        if ( ((x * x) + (y * y))  <= 1.0 ) {
            count++;
        }
    }

    pthread_mutex_lock(&mutex_lock);
    numberOfPointsInCircle += count;
    pthread_mutex_unlock(&mutex_lock);

    pthread_exit(0);
}
// ===================== MULTITHREAD IMPLEMENTATION ======================

int main(int argc, char* argv[]) {
    double result;

	// These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double oneThread, multiThread;

	pthread_t tids[THREADS];

	// ======================= ONE THREAD EXECUTION ========================
	oneThread = 0;
	cout << "Starting one thread...\n";
	start = high_resolution_clock::now();
	result = aproxPI();
	end = high_resolution_clock::now();
	oneThread += duration<double, std::milli>(end - start).count();
	cout << "result one thread = " << fixed << setprecision(20) << result << "\n";
	cout << "one thread avg time =  " << fixed << setprecision(6) << oneThread << " ms\n";
	// ======================= ONE THREAD EXECUTION ========================

    // ======================= MULTITHREAD EXECUTION ========================
	cout << "Starting multithread...\n";
	multiThread = 0;
	start = high_resolution_clock::now();

    pthread_mutex_init(&mutex_lock, NULL);
    for (int i = 0; i < THREADS; i++) {
        pthread_create(&tids[i], NULL, task, NULL);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(tids[i], NULL);
    }
    pthread_mutex_destroy(&mutex_lock);

    result = (4.0 * numberOfPointsInCircle) / (double) POINTS;

	end = high_resolution_clock::now();
	multiThread += duration<double, std::milli>(end - start).count();
	cout << "result multithread = " << fixed << setprecision(20) << result << "\n";
	cout << "multithread avg time =  " << fixed << setprecision(6) << multiThread << " ms\n";
	// ======================= MULTITHREAD EXECUTION ========================

	cout << "SpeedUp reached: " << fixed << setprecision(2) << (oneThread / multiThread) << ".\n";
    
    return 0;
}