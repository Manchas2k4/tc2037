// =================================================================
//
// File: example05.cpp
// Author: Pedro Perez
// Description: This file implements the multiplication of a matrix
//				by a vector using one thread and multiple threads. 
//              Also, it calculates the SpeedUp.
//
//              To compile: g++ example2.cpp -lpthread
//
// Copyright (c) 2023 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <pthread.h>
#include <chrono>
#include "utils.h"

using namespace std;
using namespace std::chrono;

const int CELLS = 10000;
const int THREADS = 8;

// ====================== ONE THREAD IMPLEMENTATION ======================
void enumerationSort(int *arr, int *temp, int size) {
    int count;

    for (int i = 0; i < size; i++) {
        count = 0;
        for (int j = 0; j < size; j++) {
            if (arr[j] < arr[i]) {
                count++;
            } else if (arr[j] == arr[i] && j < i) {
                count++;
            }
        }

        temp[count] = arr[i];
    }
}
// ====================== ONE THREAD IMPLEMENTATION ======================


// ===================== MULTITHREAD IMPLEMENTATION ======================
typedef struct {
    int start, end, size;
    int *arr, *temp;
} Block;

void* task(void* param) {
    Block* b;
    int count;

    b = (Block*) param;
    for (int i = b->start; i < b->end; i++) {
        count = 0;
        for (int j = 0; j < b->size; j++) {
            if (b->arr[j] < b->arr[i]) {
                count++;
            } else if (b->arr[j] == b->arr[i] && j < i) {
                count++;
            }
        }

        b->temp[count] = b->arr[i];
    }
    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    int *arr, *temp;
    
    // These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double oneThread, multiThread;

	// These variables are used by thread management.
	int blockSize;
    Block blocks[THREADS];
    pthread_t tids[THREADS];

    arr = new int[CELLS];
    random_array(arr, CELLS);

    temp = new int[CELLS];

    display_array("before: ", arr);

    // ======================= ONE THREAD EXECUTION ========================
	oneThread = 0;
	cout << "Starting one thread...\n";
	for (int j = 0; j < N; j++) {
		start = high_resolution_clock::now();
		enumerationSort(arr, temp, CELLS);
		end = high_resolution_clock::now();
		oneThread += duration<double, std::milli>(end - start).count();
	}
	oneThread /= N;
	display_array("after one thread: ", temp);
	cout << "one thread avg time =  " << fixed << setprecision(6) << oneThread << " ms\n";
	// ======================= ONE THREAD EXECUTION ========================

    
    // ======================= MULTITHREAD EXECUTION ========================
	blockSize = CELLS / THREADS;
	for (int i = 0; i < THREADS; i++) {
		blocks[i].start = i * blockSize;
		blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : CELLS;
        blocks[i].arr = arr;
        blocks[i].temp = temp;
        blocks[i].size = CELLS;
    }

    cout << "Starting multithread...\n";
	multiThread = 0;
	for (int j = 0; j < N; j++) {
		start = high_resolution_clock::now();

		for (int i = 0; i < THREADS; i++) {
			pthread_create(&tids[i], NULL, task, (void*) &blocks[i]);
		}

		for (int i = 0; i < THREADS; i++) {
			pthread_join(tids[i], NULL);
		}

		end = high_resolution_clock::now();
		multiThread += duration<double, std::milli>(end - start).count();
	}
	multiThread /= N;
	display_array("after multithread:", temp);
	cout << "multithread avg time =  " << fixed << setprecision(6) << multiThread << " ms\n";
	// ======================= MULTITHREAD EXECUTION ========================

	cout << "SpeedUp reached: " << fixed << setprecision(2) << (oneThread / multiThread) << ".\n";

    delete [] arr;
    delete [] temp;

    return 0;
}