// =================================================================
//
// File: exercise1.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code to brute-force all prime 
//  numbers less than MAXIMUM.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

const int SIZE = 10000000; //1e7
const int THREADS = 8;

using namespace std;

// =========================== SEQUENTIAL ==========================
// ADD CODE HERE
// =================================================================

// =========================== CONCURRENT ==========================
// ADD CODE HERE
// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent;
    int *array;
	
    array = new int[SIZE];

    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		// ADD CODE HERE
        
        sequential += stop_timer();
	}
    for (int i = 2; i < DISPLAY; i++) {
        if (array[i]) {
            cout << setw(4) << i;
        }
    }
    cout << "\n";
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;

    // ADD CODE HERE
    for (int i = 2; i < DISPLAY; i++) {
        if (array[i]) {
            cout << setw(4) << i;
        }
    }
    cout << "\n";
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;

    cout << "speed up = " << setprecision(5) << (sequential / concurrent) << " ms" << endl;

    delete [] array;

    return 0;
}