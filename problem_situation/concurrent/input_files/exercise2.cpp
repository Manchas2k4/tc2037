// =================================================================
//
// File: exercise2.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code that counts the number 
//  of times a certain number appears within an array.
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

const int SIZE = 1000000000; //1e9
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
    int *array, result;
	
    array = new int[SIZE];
    random_array(array, SIZE);
    display_array("array: ", array);

    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

        // ADD CODE HERE
        
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