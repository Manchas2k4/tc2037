// =================================================================
//
// File: example02.cpp
// Author: Pedro Perez
// Description: This file contains the code that searches for the
// 				smallest value stored in an array using one thread 
//              and  multiple threads. Also, it calculates the 
//              SpeedUp.
//
//              To compile: g++ example02.cpp -lpthread
//
// Copyright (c) 2023 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>
#include <pthread.h>
#include <chrono>
#include "utils.h"

using namespace std;
using namespace std::chrono;

const int CELLS = 1000000000; //1e9
const int THREADS = 8;

// ====================== ONE THREAD IMPLEMENTATION ======================
int minimumValue(int *arr, int size) {
	int result;

	result = INT_MAX;
	for (int i = 0; i< size; i++) {
		result = min(arr[i], result); 
	}
	return result;
}
// ====================== ONE THREAD IMPLEMENTATION ======================


// ===================== MULTITHREAD IMPLEMENTATION ======================
typedef struct {
	int start, end; // [start, end)
	int *arr;
	int result;
} Block;

void* task(void* param) {
	Block *block;
	int value;

	block = (Block *) param;
	value = INT_MAX;
	for (int i = block->start; i < block->end; i++) {
		value = min(value, block->arr[i]);
	}
	block->result = value;
	pthread_exit(0);
}
// ===================== MULTITHREAD IMPLEMENTATION ======================

int main(int argc, char* argv[]) {
	int *arr, pos, result;

	// These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double oneThread, multiThread;

	// These variables are used by thread management.
	int blockSize;
	Block blocks[THREADS];
	pthread_t tids[THREADS];

	arr = new int[CELLS];
	fill_array(arr, CELLS);
	display_array("arr: ", arr);

	srand(time(0));
	pos = rand() % CELLS;
	printf("Setting value 0 at %i\n", pos);
	arr[pos] = 0;

	// ======================= ONE THREAD EXECUTION ========================
	oneThread = 0;
	cout << "Starting one thread...\n";
	for (int j = 0; j < N; j++) {
		start = high_resolution_clock::now();
		result = minimumValue(arr, CELLS);
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

		result = INT_MAX;
		for (int i = 0; i < THREADS; i++) {
			pthread_join(tids[i], NULL);
			result = min(blocks[i].result, result);
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
