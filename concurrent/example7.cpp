// =================================================================
//
// File: example7.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code to perform the numerical
//  integration of a function within a defined interval.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

const double PI = 3.14159265;
const int RECTS = 10000000; //1e8
const int THREADS = 128;

using namespace std;

// =========================== SEQUENTIAL ==========================
double integration(double start, double end, double (*fn) (double)) {
	double dx, acum, x;
	int i;

	x = start;
	dx = (end - start) / RECTS;
	acum = 0;
	for (i = 0; i < RECTS; i++) {
		acum += fn(x + (i * dx));
	}
	acum = acum * dx;
    return acum;
}
// =================================================================

// =========================== CONCURRENT ==========================
typedef struct {
	int start, end;
	double x, dx, localResult;
	double (*fn) (double);
} Block;

void* task(void* param) {
	Block *block;
	double acum;

	block = (Block*) param;
	acum = 0;
	for (int i = block->start; i < block->end; i++) {
		acum += block->fn(block->x + (i * block->dx));
	}
	block->localResult = acum;
	pthread_exit(0);
}
// =================================================================
int main(int argc, char* argv[]) {
	double sequential, concurrent, result, x, dx;
    int blockSize;
	pthread_t tids[THREADS];
	Block blocks[THREADS];

	// =========================== SEQUENTIAL ==========================
    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		result = integration(0, PI, sin);

		sequential += stop_timer();
    }
    cout << "result = " << fixed << setprecision(5) << result << endl;
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;
	// =================================================================
    // =========================== CONCURRENT ==========================
	x = 0;
	dx = (PI - 0) / RECTS;
	blockSize = RECTS / THREADS;

	for (int i = 0; i < THREADS; i++) {
		blocks[i].start = i * blockSize;
		blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : RECTS;
		blocks[i].x = x;
		blocks[i].dx = dx;
		blocks[i].fn = sin;
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
		result *= dx;
		concurrent += stop_timer();
	}
    cout << "result = " << fixed << setprecision(5) << result << endl;
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;
	// =================================================================
    cout << "speed up = " << setprecision(5) << (sequential / concurrent) << endl;
    return 0;
}