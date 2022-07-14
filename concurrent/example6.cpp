// =================================================================
//
// File: example1.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code that searches for the
//  smallest value stored in an array.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

const int SIZE = 1000000000; //1e9
const int THREADS = 8;

using namespace std;

// =========================== SEQUENTIAL ==========================
int minimumValue(int *array, int size) {
    int val = INT_MAX;
    for (int i = 0; i < size; i++) {
        val = min(val, array[i]);
    }
    return val;
}
// =================================================================

// =========================== CONCURRENT ==========================
typedef struct {
    int start, end, *array, minLocal;
} Block;

void* task(void* param) {
    Block *block;
    int aux;

    block = (Block*) param;
    aux = INT_MAX;
    for (int i = block->start; i < block->end; i++) {
        aux = min(aux, block->array[i]);
    }
    block->minLocal = aux;
    pthread_exit(0);
}
// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent, blockSize;
    int *array, result;
    pthread_t tids[THREADS];
    Block blocks[THREADS];
	
    array = new int[SIZE];
    random_array(array, SIZE);
    display_array("array: ", array);

    array[74836] = 0;

    // =========================== SEQUENTIAL ==========================
    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		result = minimumValue(array, SIZE);

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
        blocks[i].minLocal = INT_MAX;
    }

    concurrent = 0;
    for (int j = 0; j < N; j++) {
        start_timer();
        for (int i = 0; i < THREADS; i++) {
            pthread_create(&tids[i], NULL, task, (void*) &blocks[i]);
        }

        result = INT_MAX;
        for (int i = 0; i < THREADS; i++) {
            pthread_join(tids[i], NULL);
            result = min(result, blocks[i].minLocal);
        }
        concurrent += stop_timer();
    }
    cout << "result = " << fixed << setprecision(0) << result << endl;
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;

    cout << "speed up = " << setprecision(5) << (sequential / concurrent) << endl;
    // =================================================================
    delete [] array;

    return 0;
}