// =================================================================
//
// File: example01.cpp
// Author: Pedro Perez
// Description: This file contains the code that adds all the
//				elements of an integer array using one thread and 
//				multiple threads. Also, it calculates the SpeedUp.
//
//        To compile: g++ example01.cpp -lpthread
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

const int CELLS = 1000000000; //1e9
const int THREADS = 8;

// ====================== ONE THREAD IMPLEMENTATION ======================
double sumArray(int *arr, int size) {
	double acum;

	acum = 0;
	for (int i = 0; i< size; i++) {
		acum += arr[i];
	}
	return acum;
}
// ====================== ONE THREAD IMPLEMENTATION ======================


// ===================== MULTITHREAD IMPLEMENTATION ======================
typedef struct {
	int start, end; // [start, end)
	int *arr;
	double result;
} Block;

void* task(void* param) {
	double acum;
	Block *block;

	block = (Block *) param;
	acum = 0;
	for (int i = block->start; i < block->end; i++) {
		acum += block->arr[i];
	}
	block->result = acum;
	pthread_exit(0);
}
// ===================== MULTITHREAD IMPLEMENTATION ======================

int main(int argc, char* argv[]) {
	int *arr;
	double result;

	// These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double oneThread, multiThread;

	// These variables are used by thread management.
	int blockSize;
	Block blocks[THREADS];
	pthread_t tids[THREADS];

	arr = new int[CELLS];
	fill_array(arr, CELLS);
	display_array("arr:", arr);

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
	cout << "one thread avg time =  " << fixed << setprecision(6) << oneThread << " ms\n";
	// ======================= ONE THREAD EXECUTION ========================

	// ======================= MULTITHREAD EXECUTION ========================
	blockSize = CELLS / THREADS;
	for (int i = 0; i < THREADS; i++) {
		blocks[i].start = i * blockSize;
		blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : CELLS;
		blocks[i].arr = arr;
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
	cout << "result multithread = " << fixed << setprecision(0) << result << "\n";
	cout << "multithread avg time =  " << fixed << setprecision(6) << multiThread << " ms\n";
	// ======================= MULTITHREAD EXECUTION ========================

	cout << "SpeedUp reached: " << fixed << setprecision(2) << (oneThread / multiThread) << ".\n";

	delete [] arr;
	return 0;
}
