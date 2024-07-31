// =================================================================
//
// File: example02.cpp
// Author: Pedro Perez
// Description: This file contains the code that looks for an element 
//		X within the array and replaces it with Y using C/C++ threads. 
//      To compile:
//		g++ -o app -pthread example02.cpp
//
// Copyright (c) 2024 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstring>
#include <thread>
#include "utils.h"

using namespace std;
using namespace std::chrono;

#define SIZE    1000000000 //1e9
#define THREADS std::thread::hardware_concurrency()

typedef struct {
    int *array, oldElement, newElement;
    int start, end;
} Block;

void replace(Block &b) {
    for (int i = b.start; i < b.end; i++) {
        if (b.array[i] == b.oldElement) {
            b.array[i] = b.newElement;
        }
    }
}

int main(int argc, char* argv[]) {
    int *array, *aux;

    // These variables are used to keep track of the execution time.
    high_resolution_clock::time_point start, end;
    double timeElapsed;

    int blockSize;
    Block blocks[THREADS];
    thread threads[THREADS];

    array = new int[SIZE];
    for (int i = 0; i < SIZE; i++) {
        array[i] = 1;
    }
    display_array("before", array);
    
    aux = new int[SIZE];

    blockSize = SIZE / THREADS;
    for (int i = 0; i < THREADS; i++) {
        blocks[i].array = aux;
        blocks[i].oldElement = 1;
        blocks[i].newElement = -1;
        blocks[i].start = (i * blockSize);
        blocks[i].end = (i != (THREADS - 1))? ((i + 1) * blockSize) : SIZE;
    }

    cout << "Starting...\n";
    timeElapsed = 0;
    for (int j = 0; j < N; j++) {
        memcpy(aux, array, sizeof(int) * SIZE);
        
        start = high_resolution_clock::now();

        for (int i = 0; i < THREADS; i++) {
            threads[i] = thread(replace, std::ref(blocks[i]));
        }

        for (int i = 0; i < THREADS; i++) {
            threads[i].join();
        }

        end = high_resolution_clock::now();
        timeElapsed += 
            duration<double, std::milli>(end - start).count();
    }
    
    display_array("after", aux);
    cout << "avg time = " << fixed << setprecision(3) 
         << (timeElapsed / N) <<  " ms\n";

    delete [] array;
    
    return 0;
}
