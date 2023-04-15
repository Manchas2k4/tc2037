// =================================================================
//
// File: example2.cpp
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
#include <climits>
#include <unistd.h>
#include <pthread.h>
#include <chrono>
#include "utils.h"

using namespace std;
using namespace std::chrono;

const int RENS = 30000; //1e5
const int COLS = 30000;
const int THREADS = 8;

// ====================== ONE THREAD IMPLEMENTATION ======================
void matrixXVector(int* c, int *m, int *b, int rens, int cols) {
	int acum;

	for (int i = 0; i < rens; i++) {
		acum = 0;
		for (int j = 0; j < cols; j++) {
			acum += (m[(i * cols) + j] * b[i]);
		}
		c[i] = acum;
	}
}
// ====================== ONE THREAD IMPLEMENTATION ======================

// ===================== MULTITHREAD IMPLEMENTATION ======================
typedef struct {
	int start, end; // [start, end)
	int *m, *b, *c;
	int cols;
} Block;


void* task(void* param) {
	Block *block;
	int acum;

	block = (Block *) param;
	for (int i = block->start; i < block->end; i++) {
		acum = 0;
		for (int j = 0; j < block->cols; j++) {
			acum += (block->m[(i * block->cols) + j] * block->b[i]);
		}
		block->c[i] = acum;
	}
	pthread_exit(NULL);
}
// ===================== MULTITHREAD IMPLEMENTATION ======================

int main(int argc, char* argv[]) {
	int *m, *b, *c;
	double ms;

	// These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double oneThread, multiThread;

	// These variables are used by thread management.
	int blockSize;
	Block blocks[THREADS];
	pthread_t tids[THREADS];

	m = new int[RENS* COLS];
	b = new int[RENS];
	c = new int[RENS];

	for (int i = 0; i < RENS; i++) {
		for (int j = 0; j < COLS; j++) {
			m[(i * COLS) + j] = (j + 1);
		}
		b[i] = 1;
	}

	// ======================= ONE THREAD EXECUTION ========================
	oneThread = 0;
	cout << "Starting one thread...\n";
	for (int j = 0; j < N; j++) {
		start = high_resolution_clock::now();
		result = sumArray(arr, CELLS);
		end = high_resolution_clock::now();
		oneThread += duration<double, std::milli>(end - start).count();
	}
	oneThread /= N;
	cout << "result one thread = " << fixed << setprecision(0) << result << "\n";
	cout << "one thread avg time =  " << fixed << setprecision(6) << oneThread << "\n";
	// ======================= ONE THREAD EXECUTION ========================

	blockSize = RENS / THREADS;
	for (i = 0; i < THREADS; i++) {
	blocks[i].start = i * block_size;
	if (i != (THREADS - 1)) {
	blocks[i].end = (i + 1) * block_size;
	} else {
	blocks[i].end = RENS;
	}
	blocks[i].m = m;
	blocks[i].b = b;
	blocks[i].c = c;
	}

	std::cout << "Starting...\n";
	ms = 0;
	for (j = 0; j < N; j++) {
	start_timer();

	for (i = 0; i < THREADS; i++) {
	pthread_create(&tids[i], NULL, matrixXVector, (void*) &blocks[i]);
	}
	for (i = 0; i < THREADS; i++) {
	pthread_join(tids[i], NULL);
	}

	ms += stop_timer();
	}
	display_array("c:", c);
	std::cout << "avg time =  " << setprecision(5) << (ms / N) << "\n";

	delete [] m;
	delete [] b;
	delete [] c;
	return 0;
}
