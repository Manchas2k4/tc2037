// =================================================================
//
// File: intro01.cpp
// Author: Pedro Perez                                             -
// Description: This file contains a basic example of creating 
//				threads using the pthread library. To compile: 
//				g++ intro01.cpp -lpthread
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

const int MAXIMUM = 10;
const int THREADS = 4;

using namespace std;

void* task(void* param) {
	for (int i = 1; i <= MAXIMUM; i++) {
		cout << i << " ";
	}
	cout << "\n";
	cout << "TID is going to terminate\n";
	pthread_exit(0);
}

int main(int argc, char* argv[]) {
	pthread_t tid;

	pthread_create(&tid, NULL, task, NULL);

	pthread_join(tid, NULL);

	cout << "The main pthread is going to terminate\n";

	return 0;
}
