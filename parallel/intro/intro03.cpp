// =================================================================
//
// File: intro03.cpp
// Author: Pedro Perez
// Description: This file show how the problem with shared variable.
//              To compile:
//				g++ -o app -pthread intr03.cpp
//
// Copyright (c) 2023 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <pthread.h>

using namespace std;

#define THREADS 4

void* task (void* param) {
    int limit = *((int*) param);

    cout << "tid " << (pthread_self()  % 10000) << " has started.\n";
    for (int i = 1; i <= limit; i++) {
        //cout << i << " ";
    }
    //cout << "\n";
    cout << "tid " << (pthread_self()  % 10000) << " has ended.\n";
    return 0; //pthread_exit(0);
}

int main(int argc, char* argv[]) {
    pthread_t tid[THREADS];
    int limit = 100;

    for (int i = 0; i < THREADS; i++) {
        pthread_create(&tid[i], NULL, task, &limit);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}
