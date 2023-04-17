// =================================================================
//
// File: example03.cpp
// Author: Pedro Perez
// Description: This file contains the code to perform the numerical
//				integration of a function within a defined interval
//				using using one thread and multiple threads. Also, 
//              it calculates the SpeedUp.
//
//              To compile: g++ example03.cpp -lpthread
//
// Copyright (c) 2023 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <pthread.h>
#include <chrono>
#include "utils.h"

using namespace std;
using namespace std::chrono;

const double PI = 3.14159265;

const int RECTS = 100000000; //1e9
const double LOWER_LIMIT = 0;
const double UPPER_LIMIT = PI;

const int THREADS = 8;

// ====================== ONE THREAD IMPLEMENTATION ======================
double integration(double x, double dx, double (*fn) (double), int rects) {
	double acum;

	acum = 0;
	for (int i = 0; i < rects; i++) {
		acum += fn(x + (i * dx));
	}
	return (acum * dx);
}
// ====================== ONE THREAD IMPLEMENTATION ======================


// ===================== MULTITHREAD IMPLEMENTATION ======================
typedef struct {
	int start, end; // [start, end)
	double x, dx, result;
	double (*fn) (double);
} Block;

void* task(void* param) {
    Block *block;
	double acum;

    block = (Block *) param;
    acum = 0;
	for (int i = block->start; i < block->end; i++) {
		acum += block->fn(block->x + (i * block->dx));
	}
	block->result = (acum * block->dx);
	pthread_exit(0);
}
// ===================== MULTITHREAD IMPLEMENTATION ======================

int main(int argc, char* argv[]) {
	double result, x, dx;

	// These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double oneThread, multiThread;

	// These variables are used by thread management.
	int blockSize;
    Block blocks[THREADS];
    pthread_t tids[THREADS];

	x = LOWER_LIMIT;
	dx = (UPPER_LIMIT - LOWER_LIMIT) / RECTS;

	// ======================= ONE THREAD EXECUTION ========================
	oneThread = 0;
	cout << "Starting one thread...\n";
	for (int j = 0; j < N; j++) {
		start = high_resolution_clock::now();
		result = integration(x, dx, sin, RECTS);
		end = high_resolution_clock::now();
		oneThread += duration<double, std::milli>(end - start).count();
	}
	oneThread /= N;
	cout << "result one thread = " << fixed << setprecision(20) << result << "\n";
	cout << "one thread avg time =  " << fixed << setprecision(6) << oneThread << " ms\n";
	// ======================= ONE THREAD EXECUTION ========================

	// ======================= MULTITHREAD EXECUTION ========================
    blockSize = RECTS / THREADS;
	for (int i = 0; i < THREADS; i++) {
		blocks[i].start = i * blockSize;
		blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : RECTS;
		blocks[i].x = x;
		blocks[i].dx = dx;
		blocks[i].fn = sin;
		blocks[i].result = 0;
	}

	cout << "Starting multithread...\n";
	multiThread = 0;
	for (int j = 0; j < N; j++) {
		start = high_resolution_clock::now();

		for (int i = 0; i < THREADS; i++) {
			pthread_create(&tids[i], NULL, task, (void*) &blocks[i]);
		}

		result = 0;
		for (int i = 0; i < THREADS; i++) {
			pthread_join(tids[i], NULL);
			result += blocks[i].result;
		}

		end = high_resolution_clock::now();
		multiThread += duration<double, std::milli>(end - start).count();
	}
	multiThread /= N;
	cout << "result multithread = " << fixed << setprecision(20) << result << "\n";
	cout << "multithread avg time =  " << fixed << setprecision(6) << multiThread << " ms\n";
	// ======================= MULTITHREAD EXECUTION ========================

	cout << "SpeedUp reached: " << fixed << setprecision(2) << (oneThread / multiThread) << ".\n";

	return 0;
}
