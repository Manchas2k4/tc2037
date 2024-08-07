// =================================================================
//
// File: example04.cpp
// Author: Pedro Perez
// Description: This file implements the algorithm to find the 
//		minimum value in an array using C/C++ threads. To 
//		compile:
//		g++ -o app -pthread example04.cpp
//
// Copyright (c) 2024 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "utils.h"

using namespace std;
using namespace std::chrono;

#define SIZE 	1000000000 // 1e9
#define THREADS std::thread::hardware_concurrency()

typedef struct {
    int *array, result;
    int start, end;
} Block;

void minimum(Block &b) {
    int local = b.array[b.start];
    for (int i = b.start + 1; i < b.end; i++) {
        if (b.array[i] < local) {
            local = b.array[i];
        }
    }
    b.result = local;
}

int main(int argc, char* argv[]) {
    int *array, result;

    // These variables are used to keep track of the execution time.
    high_resolution_clock::time_point start, end;
    double timeElapsed;

    int blockSize;
    Block blocks[THREADS];
    thread threads[THREADS];

    array = new int [SIZE];
    
    random_array(array, SIZE);
    display_array("array:", array);

    blockSize = SIZE / THREADS;
    for (int i = 0; i < THREADS; i++) {
        blocks[i].array = array;
        blocks[i].result = 0;
        blocks[i].start = (i * blockSize);
        blocks[i].end = (i != (THREADS - 1))? ((i + 1) * blockSize) : SIZE;
    }

    cout << "Starting...\n";
    timeElapsed = 0;
    for (int j = 0; j < N; j++) {
        start = high_resolution_clock::now();

        for (int i = 0; i < THREADS; i++) {
            threads[i] = thread(minimum, std::ref(blocks[i]));
        }

        result = array[0];
        for (int i = 0; i < THREADS; i++) {
            threads[i].join();
            if (blocks[i].result < result) {
                result = blocks[i].result;
            }
        }

        end = high_resolution_clock::now();
        timeElapsed += 
            duration<double, std::milli>(end - start).count();
    }
    cout << "result = " << result << "\n";
    cout << "avg time = " << fixed << setprecision(3) 
         << (timeElapsed / N) <<  " ms\n";

    delete [] array;

    return 0;
}
