// =================================================================
//
// File: example06.cpp
// Author: Pedro Perez
// Description: This file contains the code to perform the numerical
//		integration of a function within a defined interval 
//		using C/C++ threads. To compile:
//		g++ -o app -pthread example06.cpp
//
// Copyright (c) 2024 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <thread>
#include "utils.h"

using namespace std;
using namespace std::chrono;

#define PI	 	3.14159265
#define RECTS 	1000000000 //1e9
#define THREADS std::thread::hardware_concurrency()

double square(double x) {
    return x * x;
}

typedef struct {
    double x, dx, result;
    double (*fn) (double);
    int start, end;
} Block;

void integration(Block &b) {
    double acum = 0;
    for (int i = b.start; i < b.end; i++) {
        acum += b.fn(b.x + (i * b.dx));
    }
    b.result = acum;
}

int main(int argc, char* argv[]) {
    double result, x, dx, acum;

    // These variables are used to keep track of the execution time.
    high_resolution_clock::time_point start, end;
    double timeElapsed;

    int blockSize;
    Block blocks[THREADS];
    thread threads[THREADS];

    x = 0;
    dx = PI / RECTS;

    blockSize = RECTS / THREADS;
    for (int i = 0; i < THREADS; i++) {
        blocks[i].x = x;
        blocks[i].dx = dx;
        blocks[i].fn = sin;
        blocks[i].result = 0;
        blocks[i].start = (i * blockSize);
        blocks[i].end = (i != (THREADS - 1))? ((i + 1) * blockSize) : RECTS;
    }	

    cout << "Starting...\n";
    timeElapsed = 0;
    for (int j = 0; j < N; j++) {
        start = high_resolution_clock::now();

        for (int i = 0; i < THREADS; i++) {
            threads[i] = thread(integration, std::ref(blocks[i]));
        }

        acum = 0;
        for (int i = 0; i < THREADS; i++) {
            threads[i].join();
            acum += blocks[i].result;
        }

        end = high_resolution_clock::now();
        timeElapsed += 
            duration<double, std::milli>(end - start).count();
    }
    result = acum * dx;
    cout << "result = " << fixed << setprecision(20)  << result << "\n";
    cout << "avg time = " << fixed << setprecision(3) 
         << (timeElapsed / N) <<  " ms\n";

    return 0;
}
