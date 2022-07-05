// =================================================================
//
// File: example2.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code that allows you to add 
//  two vectors, a and b.
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
void addVectors(int *c, int *a, int *b, int size) {
    for (int i = 0; i < size; i++) {
       c[i] = a[i] + b[i];
    }
}
// =================================================================

// =========================== CONCURRENT ==========================
// ADD CODE HERE
// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent;
    int *a, *b, *c;
	//ADD CODE HERE
	
    a = new int[SIZE];
    fill_array(a, SIZE);
    display_array("a: ", a);

    b = new int[SIZE];
    fill_array(b, SIZE);
    display_array("b: ", b);

    c = new int[SIZE];

    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		addVectors(c, a, b, SIZE);

		sequential += stop_timer();
	}
    display_array("c: ", c);
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;

	// ADD CODE HERE
    display_array("c: ", c);
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;

    cout << "speed up = " << setprecision(5) << (sequential / concurrent) << " ms" << endl;
    
    delete [] a;
    delete [] b;
    delete [] c;

    return 0;
}