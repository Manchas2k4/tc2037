// =================================================================
//
// File: example5.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code that adds all the 
//  elements of an integer array.
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
#include "utils.h"

const int SIZE = 1000000000; //1e9
const int THREADS = 8;

using namespace std;

// =========================== SEQUENTIAL ==========================
double sumArray(int *array, int size) {
    double acum = 0;
    for (int i = 0; i < size; i++) {
        acum += array[i];
    }
    return acum;
}
// =================================================================

// =========================== CONCURRENT ==========================
typedef struct {
    int start, end, *array;
    double localResult;
} Block;

void* task(void* param) {
    Block *block;
    double acum;

    block = (Block*) param;
    acum = 0;
    for (int i = block->start; i < block->end; i++) {
        acum += block->array[i];
    }
    block->localResult = acum;
    pthread_exit(0);
}
// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent, result, blockSize;
    int *array;
    pthread_t tids[THREADS];
    Block blocks[THREADS];
	
    array = new int[SIZE];
    fill_array(array, SIZE);
    display_array("array: ", array);

    // =========================== SEQUENTIAL ==========================
    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		result = sumArray(array, SIZE);

		sequential += stop_timer();
    }
    cout << "result = " << fixed << setprecision(0) << result << endl;
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;
    // =================================================================
    // =========================== CONCURRENT ==========================
    blockSize = SIZE / THREADS;
    for (int i = 0; i < THREADS; i++) {
        blocks[i].start = i * blockSize;
        blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : SIZE;
        blocks[i].array = array;
        blocks[i].localResult = 0;
    }

    concurrent = 0;
    for (int j = 0; j < N; j++) {
        start_timer();

        for (int i = 0; i < THREADS; i++) {
            pthread_create(&tids[i], NULL, task, (void*) &blocks[i]);
        }

        result = 0;
        for (int i = 0; i < THREADS; i++) {
            pthread_join(tids[i], NULL);
            result += blocks[i].localResult;
        }

        concurrent += stop_timer();
    }
    cout << "result = " << fixed << setprecision(0) << result << endl;
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;
    // =================================================================

    cout << "speed up = " << setprecision(5) << (sequential / concurrent) << endl;
    
    delete [] array;

    return 0;
}