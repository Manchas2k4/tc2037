// =================================================================
//
// File: example4.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code that implements the
//  enumeration sort algorithm. 
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

const int SIZE = 10000; //1e6
const int THREADS = 8;

using namespace std;

// =========================== SEQUENTIAL ==========================
void enumerationSort(int *array, int *ordered, int size) {
    int count;

    for (int i = 0; i < size; i++) {
        count = 0;
        for (int j = 0; j < size; j++) {
            if (array[j] < array[i]) {
                count++;
            } else if (array[i] == array[j] && j < i) {
                count++;
            }
        }
        ordered[count] = array[i];
    }
}
// =================================================================

// =========================== CONCURRENT ==========================
// ADD CODE HERE
// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent;
    int *array, *ordered;
    // ADD CODE HERE
	
    array = new int[SIZE];
    random_array(array, SIZE);
    display_array("before: ", array);

    ordered = new int[SIZE];

    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		enumerationSort(array, ordered, SIZE);
        
        sequential += stop_timer();
	}

    display_array("after: ", ordered);
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;

    // ADD CODE HERE
    display_array("after: ", ordered);
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;

    cout << "speed up = " << setprecision(5) << (sequential / concurrent) << " ms" << endl;
    
    delete [] array;
    delete [] ordered;

    return 0;
}