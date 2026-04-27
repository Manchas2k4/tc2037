// =================================================================
//
// File: intro04.cpp
// Author: Pedro Perez
// Description: This file show how to send a block of data to a 
//              thread. To compile:
//				g++ -o app -pthread intr04.cpp
//
// Copyright (c) 2024 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <thread>

using namespace std;

#define THREADS 4

void task (int id, int start, int end) {
    cout << "id " << id << " has started.\n";
    for (int i = start; i < end; i++) {
        cout << i << " ";
    }
    cout << "\n";
    cout << "id " << id << " has ended.\n";
}

int main(int argc, char* argv[]) {
    thread threads[THREADS];

    for (int i = 0; i < THREADS; i++) {
        int id = i; 
        int start = i * 100; 
        int end = (i + 1) * 100; 
        threads[i] = thread(task, id, start, end);
    }

    for (int i = 0; i < THREADS; i++) {
        threads[i].join();
    }

    return 0;
}