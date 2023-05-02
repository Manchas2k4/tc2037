// =================================================================
//
// File: solution02.cpp
// Author: Pedro Perez
// Description: This file contains the solution to the pizzeria 
//              synchronization problem using pthreads.
//
//              To compile: g++ solution02.cpp -lpthread
//
// Copyright (c) 2023 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <chrono>
#include <random>
#include <ctime>
#include <unistd.h>
#include <pthread.h>

using namespace std;
using namespace std::chrono;

const int SLICE_TO_EAT = 3;
const int SLICES_PER_PIZZA = 8;
const int AMOUNT_OF_STUDENTS = 4;

int slices = SLICES_PER_PIZZA;
bool first;
pthread_mutex_t mutexLock, orderPizza;
pthread_cond_t deliverPizza;

void* student(void *param) {
    int id;
    mt19937 generator(clock());
    uniform_int_distribution<int> distribution(2, 3);

    id = *((int*) param);
    for (int i = 0; i < SLICE_TO_EAT; i++) {
        cout << "Student " << id << ": I'm hungry, I'll have a slice of pizza.\n";
        pthread_mutex_lock(&mutexLock);
        if (slices == 0) {
            cout << "Student " << id << ": Whoops, no pizza.\n";
            if (first) {
                cout << "Student " << id << ": I'll order another one and wait.\n";
                pthread_mutex_unlock(&orderPizza);
                first = false;
            }
            pthread_cond_wait(&deliverPizza, &mutexLock);
        }

        slices--;
        cout << "Student " << id << ": Ready! I already took my slice, to study.\n";
        pthread_mutex_unlock(&mutexLock);
        sleep( distribution(generator) );
    }
    cout << "Student " << id << ": I'm done, rest.\n";
    pthread_exit(0);
}

void* pizzaShop(void* param) {
    mt19937 generator(clock());
    uniform_int_distribution<int> distribution(3, 5);

    while(1) {
        pthread_mutex_lock(&orderPizza);
        pthread_mutex_lock(&mutexLock);
        cout << "Pizza Shop: An order arrived, to prepare a new pizza.\n";
        sleep( distribution(generator) );
        cout << "Pizza Shop: Ok, now to deliver it.\n";
        slices = SLICES_PER_PIZZA;
        first = true;
        cout << "Pizza Shop: The pizza has arrived.\n";
        pthread_cond_signal(&deliverPizza);
        pthread_mutex_unlock(&mutexLock);
    }
    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    pthread_t students[AMOUNT_OF_STUDENTS];
    pthread_t shop;
    int ids[AMOUNT_OF_STUDENTS];

    pthread_mutex_init(&mutexLock, NULL);
    pthread_mutex_init(&orderPizza, NULL);
    pthread_cond_init(&deliverPizza, NULL);

    pthread_mutex_lock(&orderPizza);

    first = true;

    for (int i = 0; i < AMOUNT_OF_STUDENTS; i++) {
        ids[i] = i;
        pthread_create(&students[i], NULL, student, (void*) &ids[i]);
    }
    pthread_create(&shop, NULL, pizzaShop, NULL);

    for (int i = 0; i < AMOUNT_OF_STUDENTS; i++) {
        pthread_join(students[i], NULL);
    }

    pthread_mutex_destroy(&mutexLock);
    pthread_mutex_destroy(&orderPizza);
    pthread_cond_destroy(&deliverPizza);
    return 0;
}