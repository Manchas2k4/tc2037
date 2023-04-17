// =================================================================
//
// File: example04.cpp
// Author: Pedro Perez
// Description: This file implements the multiplication of a matrix
//				by a vector using one thread and multiple threads. 
//              Also, it calculates the SpeedUp.
//
//              To compile: g++ example04.cpp -lpthread
//
// Copyright (c) 2023 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <climits>
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
	pthread_exit(0);
}
// ===================== MULTITHREAD IMPLEMENTATION ======================

int main(int argc, char* argv[]) {
	int *m, *b, *c;
	
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
		matrixXVector(c, m, b, RENS, COLS);
		end = high_resolution_clock::now();
		oneThread += duration<double, std::milli>(end - start).count();
	}
	oneThread /= N;
	display_array("result one thread:", c);
	cout << "one thread avg time =  " << fixed << setprecision(6) << oneThread << " ms\n";
	// ======================= ONE THREAD EXECUTION ========================

	// ======================= MULTITHREAD EXECUTION ========================
	blockSize = RENS / THREADS;
	for (int i = 0; i < THREADS; i++) {
		blocks[i].start = i * blockSize;
		blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : RENS;
		blocks[i].m = m;
		blocks[i].b = b;
		blocks[i].c = c;
		blocks[i].cols = COLS;
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
	display_array("result multithread:", c);
	cout << "multithread avg time =  " << fixed << setprecision(6) << multiThread << " ms\n";
	// ======================= MULTITHREAD EXECUTION ========================

	cout << "SpeedUp reached: " << fixed << setprecision(2) << (oneThread / multiThread) << ".\n";
	
	delete [] m;
	delete [] b;
	delete [] c;
	return 0;
}
