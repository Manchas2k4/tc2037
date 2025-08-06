// =================================================================
//
// File: intro05.cpp
// Author: Pedro Perez
// Description: This file implements a synchronization strategy where
//              a group of threads must wait for all of them to reach 
//              a common point before they can continue their 
//              execution.
//
//              To compile: g++ intro05.cpp -pthread -o app
//
// Copyright (c) 2024 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================
#include <iostream>
#include <iomanip>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

const int MAX_THREADS = 4;
const int MAX_ITERATIONS = 5;

int counter = 0;
mutex semaphore;
condition_variable cv;

void task(int id) {
    cout << "id=" << id << " before the barrier.\n";

    unique_lock<mutex> barrier(semaphore);

    counter++;
    if (counter == MAX_THREADS) {
        cv.notify_all();
    } else {
        cv.wait(barrier, [] { return counter >= MAX_THREADS; });
    }

    cout << "id=" << id << " after the barrier.\n";
}

int main(int argc, char* argv[]) {
    thread tids[MAX_THREADS];

    for (int i = 0; i < MAX_THREADS; i++) {
        tids[i] = thread(task, i);
    }

    for (int i = 0; i < MAX_THREADS; i++) {
        tids[i].join();
    }

    return 0;
}
