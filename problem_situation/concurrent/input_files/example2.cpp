// =================================================================
//
// File: example2.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code that allows you to add 
//  two vectors, a and b.
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
void addVectors(int *c, int *a, int *b, int size) {
    for (int i = 0; i < size; i++) {
       c[i] = a[i] + b[i];
    }
}
// =================================================================

// =========================== CONCURRENT ==========================
typedef struct {
    int start, end, *a, *b, *c;
} Block;

void* task(void* param) {
    Block *block;

    block = (Block*) param;
    for (int i = block->start; i < block->end; i++) {
        block->c[i] = block->a[i] + block->b[i];
    }
    pthread_exit(0);
}
// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent;
    int *a, *b, *c, blockSize;
	pthread_t tids[THREADS];
    Block blocks[THREADS];
	
    a = new int[SIZE];
    fill_array(a, SIZE);
    display_array("a: ", a);

    b = new int[SIZE];
    fill_array(b, SIZE);
    display_array("b: ", b);

    c = new int[SIZE];

    // =========================== SEQUENTIAL ==========================
    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		addVectors(c, a, b, SIZE);

		sequential += stop_timer();
	}
    display_array("c: ", c);
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;
    // =================================================================
    // =========================== CONCURRENT ==========================
    blockSize = SIZE / THREADS;
	for (int i = 0; i < THREADS; i++) {
        blocks[i].start = i * blockSize;
        blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : SIZE;
        blocks[i].a = a;
        blocks[i].b = b;
        blocks[i].c = c;
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
    display_array("c: ", c);
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;
    // =================================================================

    cout << "speed up = " << setprecision(2) << (sequential / concurrent) << endl;
    
    delete [] a;
    delete [] b;
    delete [] c;

    return 0;
}