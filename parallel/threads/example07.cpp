// =================================================================
//
// File: example04.cpp
// Author: Pedro Perez
// Description: This file implements the merge sort algorithm. The
//				time this implementation takes will be used as the
//				basis to calculate the improvement obtained with
//				parallel technologies.
//
// Copyright (c) 2024 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "utils.h"

using namespace std;
using namespace std::chrono;

#define SIZE 	10000000 //1e7
#define THREADS	8

typedef struct {
	int *A, *B, size, index, blockSize, threadsRequired;
} Block;

void* merge(void *param) {
	Block *block;
	int start, mid, end, left, right, i, numberOfThreads;

	block = (Block*) param;
	while (block->index < block->size) {
		start = block->blockSize * block->index;
		mid = start + (block->blockSize / 2) - 1;
		end = start + block->blockSize - 1;
		
		left = start;
		right = mid + 1;
		i = start;
		
		if (end > (block->size - 1)) {
			end = block->size - 1;
		}
		
		if (start == end || end <= mid) {
			return 0;
		}
		
		while (left <= mid && right <= end) {
			if (block->A[left] <= block->A[right]) {
				block->B[i++] = block->A[left++];
			} else {
				block->B[i++] = block->A[right++];
			}
		}
		
		while (left <= mid) {
			block->B[i++] = block->A[left++];
		}
		
		while (right <= end) {
			block->B[i++] = block->A[right++];
		}

		block->index += block->threadsRequired;
	}
	return 0;
}

void parallel_merge_sort(int *array, int size) {
	int *temp, *A, *B, threadsRequired;
	Block *blocks;
	pthread_t *threads; 

	temp = new int[size];
	memcpy(temp, array, sizeof(int) * size);
	
	A = array;
	B = temp;

	for (int blockSize = 2; blockSize < (2 * size); blockSize *= 2) {
		threadsRequired = min(THREADS, size / blockSize);
		if (size % blockSize > 0) {
			threadsRequired++;
		}
		
		blocks = new Block[threadsRequired];
		threads = new pthread_t[threadsRequired];
		for (int i = 0; i < threadsRequired; i++) {
			blocks[i].A = A;
			blocks[i].B = B;
			blocks[i].size = size;
			blocks[i].index = i;
			blocks[i].blockSize = blockSize;
			blocks[i].threadsRequired = threadsRequired;
			pthread_create(&threads[i], NULL, merge, &blocks[i]);
		}

		for (int i = 0; i < threadsRequired; i++) {
			pthread_join(threads[i], NULL);
		}
		delete [] blocks;
		delete [] threads;
		
		A = (A == array)? temp : array;
		B = (B == array)? temp : array;
	}
	
	delete [] temp;
}

int main(int argc, char* argv[]) {
	int *array, *aux;

	// These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double timeElapsed;

	array = new int[SIZE];
	random_array(array, SIZE);
	display_array("before", array);

	aux = new int[SIZE];

	cout << "Starting...\n";
	timeElapsed = 0;
	for (int j = 0; j < N; j++) {
		memcpy(aux, array, sizeof(int) * SIZE);

		start = high_resolution_clock::now();

		parallel_merge_sort(aux, SIZE);

		end = high_resolution_clock::now();
		timeElapsed += 
			duration<double, std::milli>(end - start).count();
	}

	memcpy(array, aux, sizeof(int) * SIZE);
	display_array("after", array);
	cout << "avg time = " << fixed << setprecision(3) 
		 << (timeElapsed / N) <<  " ms\n";

	delete [] array;
	delete [] aux;
	return 0;
}
