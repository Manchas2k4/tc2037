// =================================================================
//
// File: intro01.cpp
// Author: Pedro Perez
// Description: This file show how to create a simple thread.
//              To compile:
//				g++ -o app -pthread intr01.cpp
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

void* task (void* param) {
    for (int i = 1; i <= 10; i++) {
        cout << i << " ";
    }
    cout << "\n";
    return 0; //pthread_exit(0);
}

int main(int argc, char* argv[]) {
    pthread_t tid;

    pthread_create(&tid, NULL, task, NULL);

    pthread_join(tid, NULL);

    return 0;
}
