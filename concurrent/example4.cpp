// =================================================================
//
// File: example4.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code that implements the
//  enumeration sort algorithm. 
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

const int SIZE = 10000; //1e4
const int THREADS = 8;

using namespace std;

// =========================== SEQUENTIAL ==========================
void enumerationSort(int *array, int *ordered, int size) {
    int count;

    for (int i = 0; i < size; i++) {
        count = 0;
        for (int j = 0; j < size; j++) {
            if (array[j] < array[i]) {
                count++;
            } else if (array[i] == array[j] && j < i) {
                count++;
            }
        }
        ordered[count] = array[i];
    }
}
// =================================================================

// =========================== CONCURRENT ==========================
typedef struct {
    int start, end, size, *array, *ordered;
} Block;

void* task(void* param) {
    Block *block;
    int count;

    block = (Block*) param;
    for (int i = block->start; i < block->end; i++) {
        count = 0;
        for (int j = 0; j < block->size; j++) {
            if (block->array[j] < block->array[i]) {
                count++;
            } else if (block->array[i] == block->array[j] && j < i) {
                count++;
            }
        }
        block->ordered[count] = block->array[i];
    }
    pthread_exit(0);
}
// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent;
    int *array, *ordered, blockSize;
    pthread_t tids[THREADS];
    Block blocks[THREADS];
	
    array = new int[SIZE];
    random_array(array, SIZE);
    display_array("before: ", array);

    ordered = new int[SIZE];

    // =========================== SEQUENTIAL ==========================
    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		enumerationSort(array, ordered, SIZE);
        
        sequential += stop_timer();
	}

    display_array("after: ", ordered);
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;
    // =================================================================
    // =========================== CONCURRENT ==========================
    blockSize = SIZE / THREADS;
    for (int i = 0; i < THREADS; i++) {
        blocks[i].start = i * blockSize;
        blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : SIZE;
        blocks[i].array = array;
        blocks[i].ordered = ordered;
        blocks[i].size = SIZE;
    }

    concurrent = 0;
    for (int j = 0; j < N; j++) {
        start_timer();
        for (int i = 0; i < THREADS; i++) {
            pthread_create(&tids[i], NULL, task, (void*) &blocks[i]);
        }

        for (int i = 0; i < THREADS; i++) {
            pthread_join(tids[i], NULL);
        }
        concurrent += stop_timer();
    }
    display_array("after: ", ordered);
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;

    cout << "speed up = " << setprecision(5) << (sequential / concurrent) << endl;
    // =================================================================

    delete [] array;
    delete [] ordered;

    return 0;
}