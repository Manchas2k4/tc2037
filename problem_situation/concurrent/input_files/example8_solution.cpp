// =================================================================
//
// File: example5.cpp
// Author: Pedro Perez
// Description: This file contains the code that implements the
//				enumeration sort algorithm. The time this implementation
//				takes ill be used as the basis to calculate the
//				improvement obtained with parallel technologies.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cstring>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include "utils.h"

const int SIZE = 100000; //1e5

using namespace std;
using namespace tbb;

class EnumerationSort {
private:
	int *array, *temp, size;

public:
	EnumerationSort(int *a, int *t, int s)
		: array(a), temp(t), size(s) {}

	void operator() (const blocked_range<int> &r) const {
		int i, j, count;

		for (int i = r.begin(); i != r.end(); i++) {
			count = 0;
			for (j = 0; j < size; j++) {
				if (array[j] < array[i]) {
					count++;
				} else if (array[i] == array[j] && j < i) {
					count++;
				}
			}
			temp[count] = array[i];
		}
	}
};

int main(int argc, char* argv[]) {
	int *a, *aux;
	double ms;

	a = new int[SIZE];
	random_array(a, SIZE);
	display_array("before", a);

	aux = new int[SIZE];

	cout << "Starting..." << endl;
	ms = 0;
	for (int i = 0; i < N; i++) {
		start_timer();

		parallel_for(blocked_range<int>(0, SIZE),
									EnumerationSort(a, aux, SIZE));

		ms += stop_timer();
	}

	display_array("after", aux);
	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;

	delete [] a;
	delete [] aux;
	return 0;
}
