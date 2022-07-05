// =================================================================
//
// File: example7.cpp
// Author: Pedro Perez                                             -
// Description: This file contains the code to perform the numerical
//  integration of a function within a defined interval.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

const double PI = 3.14159265;
const int RECTS = 100000000; //1e8
const int THREADS = 8;

using namespace std;

// =========================== SEQUENTIAL ==========================
double integration(double start, double end, double (*fn) (double)) {
	double dx, acum, x;
	int i;

	x = start;
	dx = (end - start) / RECTS;
	acum = 0;
	for (i = 0; i < RECTS; i++) {
		acum += fn(x + (i * dx));
	}
	acum = acum * dx;
    return acum;
}
// =================================================================

// =========================== CONCURRENT ==========================
// ADD CODE HERE
// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent, result;
    // ADD CODE HERE
	
    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		result = integration(0, PI, sin);

		sequential += stop_timer();
    }
    cout << "result = " << fixed << setprecision(5) << result << endl;
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;

    // ADD CODE HERE
    cout << "result = " << fixed << setprecision(5) << result << endl;
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;

    cout << "speed up = " << setprecision(5) << (sequential / concurrent) << " ms" << endl;

    return 0;
}