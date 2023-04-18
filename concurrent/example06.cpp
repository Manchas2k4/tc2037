// =================================================================
// File: example06.cpp
// Author: Pedro Perez
// Description: This file contains a parallel implementation of
//              the merge sort algorithm.
//
//        To compile: g++ example06.cpp -lpthread
//
// Copyright (c) 2023 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstring>
#include <pthread.h>
#include "utils.h"
#include "merge.h"

using namespace std;
using namespace std::chrono;

const int CELLS = 67108864; // 2^25
const int GRAIN = 1048576; // 2^20
const int NUMBLOCKS = CELLS / GRAIN;

// ===================== MULTITHREAD IMPLEMENTATION ======================
typedef struct {
    int start, mid, end;
    int *arr, *temp;
} Block;

void* taskSplit(void *param) {
    //T *A, T *B, int low, int high
	int  mid;
    Block *b;

    b = (Block*) param;
    split(b->arr, b->temp, b->start, b->end - 1);
    pthread_exit(0);
}

void* taskMerge(void *param) {
    //void merge(T *A, T *B, int low, int mid, int high) {
	int  mid;
    Block *b;

    b = (Block*) param;
    merge(b->arr, b->temp, b->start, b->mid, b->end - 1);
    pthread_exit(0);
}
// ===================== MULTITHREAD IMPLEMENTATION ======================

int main (int argc, char* argv[]) {
    int *arr, *A, *B;
	double result;

    // These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double oneThread, multiThread;

    // These variables are used by thread management.
    int numBlocks;
    Block *b1, *b2;
    pthread_t tids[NUMBLOCKS];

	arr = new int[CELLS];
    A = new int[CELLS];
    B = new int[CELLS];
	random_array(arr, CELLS);
	display_array("before:", arr);

    memcpy(A, arr, sizeof(int) * CELLS);
    // ======================= ONE THREAD EXECUTION ========================
	oneThread = 0;
	cout << "Starting one thread...\n";
	start = high_resolution_clock::now();
	split(A, B, 0, CELLS - 1);
	end = high_resolution_clock::now();
	oneThread += duration<double, std::milli>(end - start).count();
	oneThread /= N;
	display_array("after - one thread:", A);
	cout << "one thread avg time =  " << fixed << setprecision(6) << oneThread << " ms\n";
	// ======================= ONE THREAD EXECUTION ========================
    

    // ======================= MULTITHREAD EXECUTION ========================
    cout << "Starting multithread...\n";
	multiThread = 0;
    start = high_resolution_clock::now();
    b1 = new Block[NUMBLOCKS];
    for (int i = 0; i < NUMBLOCKS; i++) {
		b1[i].start = i * GRAIN;
        b1[i].mid = 0;
		b1[i].end = (i != (NUMBLOCKS - 1))? (i + 1) * GRAIN : CELLS;
        b1[i].arr = A; 
        b1[i].temp = B;
    }
    
    memcpy(A, arr, sizeof(int) * CELLS);
    for (int i = 0; i < NUMBLOCKS; i++) {
        pthread_create(&tids[i], NULL, taskSplit, (void*) &b1[i]);
    }
    for (int i = 0; i < NUMBLOCKS; i++) {
        pthread_join(tids[i], NULL);
    }

    numBlocks = NUMBLOCKS;
    while (numBlocks > 1) {
        b2 = new Block[numBlocks / 2];
        for (int i = 0; i < (numBlocks / 2); i++) {
            b2[i].start = b1[(2 * i)].start;
            b2[i].mid = b1[(2 * i) + 1].start;
            b2[i].end = b1[(2 * i) + 1].end;
            b2[i].arr = A;
            b2[i].temp = B;
        }
        delete [] b1;
        b1 = b2;
        numBlocks /= 2;
        for (int i = 0; i < numBlocks; i++) {
            pthread_create(&tids[i], NULL, taskMerge, (void*) &b1[i]);
        }
        for (int i = 0; i < numBlocks; i++) {
            pthread_join(tids[i], NULL);
        }
    }
    end = high_resolution_clock::now();
	multiThread += duration<double, std::milli>(end - start).count();
    
    display_array("after - multithread:", A);
    cout << "multithread avg time =  " << fixed << setprecision(6) << multiThread << " ms\n";

    cout << "SpeedUp reached: " << fixed << setprecision(2) << (oneThread / multiThread) << ".\n";

    delete [] arr;
    delete [] A;
    delete [] B;

    return 0;
}