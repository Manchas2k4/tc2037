// =================================================================
//
// File: intro04.cpp
// Author: Pedro Perez                                             -
// Description: This file contains a basic example of creating 
//				threads using the pthread library. To compile: 
//				g++ intro04.cpp -lpthread
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

const int THREADS = 4;

typedef struct {
	int id, start, end;
} Block;

using namespace std;

void* task(void* param) {
	Block *block;

    block = (Block *) param;
    cout << "TID " << block->id << " = ";
    for (int i = block->start; i < block->end; i++) {
        cout << i << " ";
    }
    cout << "\n";
    cout << "TID " << block->id << " is going to terminate\n";
    pthread_exit(0);
}

int main(int argc, char* argv[]) {
	pthread_t tid[THREADS];
    Block blocks[THREADS];

    for (int i = 0; i < THREADS; i++) {
        blocks[i].id = i;
        blocks[i].start = i * 10;
        blocks[i].end = (i + 1) * 10;
        pthread_create(&tid[i], NULL, task, &blocks[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(tid[i], NULL);
    }
	
	cout << "The main pthread is going to terminate\n";

	return 0;
}
