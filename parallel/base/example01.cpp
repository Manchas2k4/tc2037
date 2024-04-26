#include <iostream>
#include <iomanip>
#include <chrono>
#include "utils.h"

using namespace std;
using namespace std::chrono;

const int SIZE = 100000000; // 1e8

void add_vector(int *C, int *A, int *B, int size) {
    for (int i = 0; i < size; i++) {
        C[i] = A[i] + B[i];
    }
}

int main(int argc, char* argv[]) {
    int *A, *B, *C;

    // These variable are used to keep track of the execution time
    high_resolution_clock::time_point start, end;
    double timeElapsed;

    A = new int[SIZE];
    B = new int[SIZE];
    C = new int[SIZE];

    fill_array(A, SIZE);
    display_array("A:", A);
    fill_array(B, SIZE);
    display_array("B:", B);

    cout << "Starting...\n";
    timeElapsed = 0;
    for (int j = 0; j < N; j++) {
        start = high_resolution_clock::now();

        add_vector(C, A, B, SIZE);

        end = high_resolution_clock::now();

        timeElapsed += duration<double, std::milli>(end - start).count();
    }
    display_array("C:", C);
    cout << "avg time = " << fixed << setprecision(3) << (timeElapsed/N) << " ms\n";

    delete [] A;
    delete [] B;
    delete [] C;

    return 0;
}