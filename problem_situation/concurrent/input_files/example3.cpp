// =================================================================
//
// File: example3.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code to calculate the MAXIMUM 
//  numbers of the Fibonacci series using the Binet formula.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cmath>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

const int MAXIMUM = 100000000; //1e8
const int THREADS = 8;
const double SQ = sqrt(5.0);
const double PHI = (1.0 + SQ) / 2.0;
const double PSI = (1.0 - SQ) / SQ;

using namespace std;

// =========================== SEQUENTIAL ==========================
void fibonacciNumber(double *array, int size) {
    for (int i = 0; i < size; i++) {
       array[i] = round((pow(PHI, i) - pow(PSI, i)) / SQ);
    }
}
// =================================================================

// =========================== CONCURRENT ==========================
typedef struct {
    int start, end;
    double *array;
} Block;

void* task(void* param) {
    Block *block;

    block = (Block*) param;
    for (int i = block->start; i < block->end; i++) {
        block->array[i] = round((pow(PHI, i) - pow(PSI, i)) / SQ);
    }
    pthread_exit(0);
}
// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent, blockSize;
    double *array;
    pthread_t tids[THREADS];
    Block blocks[THREADS];
	
    array = new double[MAXIMUM];

    // =========================== SEQUENTIAL ==========================
    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		fibonacciNumber(array, MAXIMUM);

		sequential += stop_timer();
	}
    for (int i = 0; i < DISPLAY; i++) {
        cout << fixed << setprecision(0) << array[i] << " ";
    }
    cout << "\n";
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;
|   // =================================================================
    // =========================== CONCURRENT ==========================
    blockSize = MAXIMUM / THREADS;
    for (int i = 0; i < THREADS; i++) {
        blocks[i].start = i * blockSize;
        blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : MAXIMUM;
        blocks[i].array = array;
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
    for (int i = 0; i < DISPLAY; i++) {
        cout << fixed << setprecision(0) << array[i] << " ";
    }
    cout << "\n";
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;
    // =================================================================

    cout << "speed up = " << setprecision(2) << (sequential / concurrent) << endl;

    delete [] array;

    return 0;
}