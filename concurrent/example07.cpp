// =================================================================
// File: example06.cpp
// Author: Pedro Perez
// Description: This file contains a parallel implementation of
//              the merge sort algorithm using one thread and 
//				multiple threads. Also, it calculates the SpeedUp.
//              This version uses a pool of threads which has a better 
//              speed up. If you want to use a good implementation 
//              of a pool of threads, we recommend you check the 
//              following link:
//              https://www.cnblogs.com/sinkinben/p/16064857.html
//
//              To compile: g++ example07.cpp -lpthread
//
// Copyright (c) 2023 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================
#include <iostream>
#include <iomanip>
#include <chrono>
#include <pthread.h>
#include "utils.h"
#include <queue>
#include <vector>
#include "merge.h"

using namespace std;
using namespace std::chrono;

const int CELLS = 67108864; // 2^25
const int GRAIN = 64; //1048576; // 2^20 //32768
const int THREADS = 8;

// ===================== MULTITHREAD IMPLEMENTATION ======================
class Task {
public:
    virtual void execute() = 0;
};

class Split : public Task {
private:
    int start, end;
    int *arr, *temp;

public: 
    Split(int s, int e, int *a, int *t) : start(s), end(e), arr(a), temp(t) {}

    void execute() {
        split(arr, temp, start, end);
    }
};

class Merge : public Task {
private:
    int start, mid, end;
    int *arr, *temp;

public: 
    Merge(int s, int m, int e, int *a, int *t) : start(s), mid(m), end(e), arr(a), temp(t) {}

    void execute() {
        merge(arr, temp, start, mid, end);
    }
};

bool finish = false;
pthread_t *tids;
queue<Task*> tasks;
pthread_mutex_t mutexQueue;
pthread_cond_t conditionQueue;

void* threadLoop(void *param) {
    Task* task;

    while (true) {
        pthread_mutex_lock(&mutexQueue);
        while  (tasks.empty() && !finish) {
            pthread_cond_wait(&conditionQueue, & mutexQueue);
        }  

        if (finish) {
            pthread_mutex_unlock(&mutexQueue);
            pthread_exit(0);
        }

        task = tasks.front();
        tasks.pop();
        pthread_mutex_unlock(&mutexQueue);
        task->execute();        
    }
}

double executeParallelMergeSort(int *arr, int *temp) {
    int start, mid, end;
    int blockSize, numBlocks, numberOfTask;

    high_resolution_clock::time_point startTime, endTime;
	double multiThread;

    startTime = high_resolution_clock::now();
    pthread_mutex_init(&mutexQueue, NULL);
    pthread_cond_init(&conditionQueue, NULL);

    // Initializes the set of threads to use
    finish = false;
    tids = new pthread_t[THREADS];
    for (int i = 0; i < THREADS; i++) {
        pthread_create(&tids[i], NULL, threadLoop, NULL);
    }

    // Initializes the tasks to be performed.
    // We will start with the splits.
    numBlocks = CELLS / GRAIN;
    for (int i = 0; i < numBlocks; i++) {
		start = i * GRAIN;
		end = (i != (numBlocks - 1))? ((i + 1) * GRAIN  - 1): (CELLS - 1);

        pthread_mutex_lock(&mutexQueue);
        tasks.push(new Split(start, end, arr, temp));
        pthread_mutex_unlock(&mutexQueue);
        pthread_cond_signal(&conditionQueue);
    }

    numberOfTask = THREADS / 2;
    blockSize = GRAIN * 2;
    while (numberOfTask > 0) {
        for (int i = 0; i < numberOfTask; i++) {
            start = i * blockSize;
            mid = (i * blockSize) + (blockSize / 2) - 1;
            end = ((i + 1) * blockSize) - 1;

            pthread_mutex_lock(&mutexQueue);
            tasks.push(new Merge(start, mid, end, arr, temp));
            pthread_mutex_unlock(&mutexQueue);
            pthread_cond_signal(&conditionQueue);
        }
        numberOfTask /= 2;
        blockSize *= 2;
    }

    while (1) {
        if (tasks.empty()) {
            break;
        }
    }
    finish = true;
    for (int i = 0; i < THREADS; i++) {
        pthread_join(tids[i], NULL);
    }

    pthread_mutex_destroy(&mutexQueue);
    pthread_cond_destroy(&conditionQueue);
    endTime = high_resolution_clock::now();

    delete [] tids;

    return (duration<double, std::milli>(end - start).count());
}
// ===================== MULTITHREAD IMPLEMENTATION ======================

int main (int argc, char* argv[]) {
    int *arr, *A, *B;
	double result;

    // These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double oneThread, multiThread;

    // These variables are used by thread management.
    int numBlocks;

	arr = new int[CELLS];
    A = new int[CELLS];
    B = new int[CELLS];
	random_array(arr, CELLS);
	display_array("before:", arr);

    // ======================= ONE THREAD EXECUTION ========================
    memcpy(A, arr, sizeof(int) * CELLS);
	oneThread = 0;
	cout << "Starting one thread...\n";
	start = high_resolution_clock::now();
	split(A, B, 0, CELLS - 1);
	end = high_resolution_clock::now();
	oneThread += duration<double, std::milli>(end - start).count();
	oneThread /= N;
	display_array("after - one thread:", A);
	cout << "one thread avg time =  " << fixed << setprecision(6) << oneThread << " ms\n";
	// ======================= ONE THREAD EXECUTION ========================

    // ======================= MULTITHREAD EXECUTION ========================
    memcpy(A, arr, sizeof(int) * CELLS);
    cout << "Starting multithread...\n";
    multiThread = executeParallelMergeSort(A, B);
    display_array("after - multithread:", A);
    cout << "multithread avg time =  " << fixed << setprecision(6) << multiThread << " ms\n";

    cout << "SpeedUp reached: " << fixed << setprecision(2) << (oneThread / multiThread) << ".\n";

    delete [] arr;
    delete [] A;
    delete [] B;

    return 0;
}