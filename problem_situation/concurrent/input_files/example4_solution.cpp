// =================================================================
//
// File: Example3.cpp
// Authors:
// Description: This file contains the code to count the number of
//				even numbers within an array using Intel's TBB.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cmath>
#include <tbb/parallel_reduce.h>
#include <tbb/blocked_range.h>
#include "utils.h"

#define SIZE 1000000000 //1e9

using namespace std;
using namespace tbb;

class EvenCount {
private:
	int *array, result;

public:
	EvenCount(int *a) : array(a), result(0) {}

  EvenCount(EvenCount &obj, split)
		: array(obj.array), result(0) {}

	int getResult() const {
		return result;
	}

  void operator() (const blocked_range<int> &r) {
    for (int i = r.begin(); i != r.end(); i++) {
			if (array[i] % 2 == 0) {
        result++;
      }
		}
	}

	void join(const EvenCount &x) {
		result += x.result;
	}
};

int main(int argc, char* argv[]) {
	int *a;
	long int result = 0;
	double ms;

	a = new int[SIZE];
	fill_array(a, SIZE);
	display_array("a", a);

	cout << "Starting..." << endl;
	ms = 0;
	for (int i = 1; i <= N; i++) {
		start_timer();

		EvenCount obj(a);
		parallel_reduce(blocked_range<int>(0, SIZE), obj);
		result = obj.getResult();

		ms += stop_timer();
	}
	cout << "count = " << result << endl;
	cout << "avg time = " << setprecision(15) << (ms / N) << " ms" << endl;

	delete [] a;
	return 0;
}
