// =================================================================
//
// File: intro04.cpp
// Author: Pedro Perez
// Description: This file show how to send a block of data to a 
//              thread. To compile:
//				g++ -o app -pthread intr04.cpp
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

typedef struct {
    int id, start, end;
} Block;

void* task (void* param) {
    Block *b = (Block*) param;

    cout << "tid " << b->id << " has started.\n";
    for (int i = b->start; i < b->end; i++) {
        //cout << i << " ";
    }
    //cout << "\n";
    cout << "tid " << b->id << " has ended.\n";
    return 0; //pthread_exit(0);
}

int main(int argc, char* argv[]) {
    pthread_t tid[THREADS];
    Block blocks[THREADS];

    for (int i = 0; i < THREADS; i++) {
        blocks[i].id = i; blocks[i].start = i * 100; blocks[i].end = (i + 1) * 100; 
        pthread_create(&tid[i], NULL, task, &blocks[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}
