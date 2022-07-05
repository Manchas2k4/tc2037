// =================================================================
//
// File: example3.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code to calculate the MAXIMUM 
//  numbers of the Fibonacci series using the Binet formula.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cmath>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

const int MAXIMUM = 10000000; //1e7
const int THREADS = 8;

using namespace std;

// =========================== SEQUENTIAL ==========================
void fibonacciNumber(double *array, int size) {
    double sq = sqrt(5.0);
    double phi = (1.0 + sq) / 2.0;
    double psi = (1.0 - sq) / sq;
    for (int i = 0; i < size; i++) {
       array[i] = round((pow(phi, i) - pow(psi, i)) / sq);
    }
}
// =================================================================

// =========================== CONCURRENT ==========================
// ADD CODE HERE
// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent;
    double *array;
    // ADD CODE HERE
	
    array = new double[MAXIMUM];

    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		fibonacciNumber(array, MAXIMUM);

		sequential += stop_timer();
	}
    for (int i = 0; i < DISPLAY; i++) {
        cout << fixed << setprecision(0) << array[i] << " ";
    }
    cout << "\n";
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;

    // ADD CODE HERE
    for (int i = 0; i < DISPLAY; i++) {
        cout << fixed << setprecision(0) << array[i] << " ";
    }
    cout << "\n";
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;

    cout << "speed up = " << setprecision(5) << (sequential / concurrent) << " ms" << endl;

    delete [] array;

    return 0;
}