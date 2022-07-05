// =================================================================
//
// File: example5.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code that adds all the 
//  elements of an integer array.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

const int SIZE = 1000000000; //1e9
const int THREADS = 8;

using namespace std;

// =========================== SEQUENTIAL ==========================
double sumArray(int *array, int size) {
    double acum = 0;
    for (int i = 0; i < size; i++) {
        acum += array[i];
    }
    return acum;
}
// =================================================================

// =========================== CONCURRENT ==========================
// ADD CODE HERE
// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent, result;
    int *array;
    // ADD CODE HERE
	
    array = new int[SIZE];
    fill_array(array, SIZE);
    display_array("array: ", array);

    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		result = sumArray(array, SIZE);

		sequential += stop_timer();
    }
    cout << "result = " << fixed << setprecision(0) << result << endl;
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;

    // ADD CODE HERE
    cout << "result = " << fixed << setprecision(0) << result << endl;
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;

    cout << "speed up = " << setprecision(5) << (sequential / concurrent) << " ms" << endl;

    delete [] array;

    return 0;
}