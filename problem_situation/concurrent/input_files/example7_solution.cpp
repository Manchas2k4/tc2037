// =================================================================
//
// File: example7.cpp
// Author: Pedro Perez
// Description: This file contains the code to brute-force all
//				prime numbers less than MAXIMUM using Intel's TBB.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include "utils.h"

#define MAXIMUM 1000000 //1e6

using namespace std;
using namespace tbb;

class PrimeNumbers {
private:
	int *array, size;

	int isPrime(int n) const {
		int i;
		for (int i = 2; i < ((int) sqrt(n)); i++) {
			if (n % i == 0) {
				return 0;
			}
		}
		return 1;
	}

public:
	PrimeNumbers(int *a, int s) : array(a), size(s) {}

	void operator() (const blocked_range<int> &r) const {
		for (int i = r.begin(); i != r.end(); i++) {
			array[i] = isPrime(i);
		}
	}
};

int main(int argc, char* argv[]) {
	int i, *a;
	double ms;

	a = new int[MAXIMUM + 1];
	cout << "At first, neither is a prime. We will display to TOP_VALUE:\n";
	for (i = 2; i < TOP_VALUE; i++) {
		cout << i << " ";
	}
	cout << "\n";

	cout << "Starting..." << endl;
	ms = 0;
	for (int i = 0; i < N; i++) {
		start_timer();

		memset(a, 0, sizeof(int) * (MAXIMUM + 1));
		parallel_for(blocked_range<int>(0, MAXIMUM),  PrimeNumbers (a, MAXIMUM));

		ms += stop_timer();
	}
	cout << "Expanding the numbers that are prime to TOP_VALUE:\n";
	for (i = 2; i < TOP_VALUE; i++) {
		if (a[i] == 1) {
			printf("%i ", i);
		}
	}
	cout << "\n";
	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;

	delete [] a;
	return 0;
}
