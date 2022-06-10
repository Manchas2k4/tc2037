// =================================================================
//
// File: readers-writers.cpp
// Author: Pedro Perez
// Description: This file implements the readers-writers
//              synchronization problem using pthreads.
//              To compile: g++ readers-writers.cpp -lpthread -o app
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>

using namespace std;

const int MAX_READERS = 20;
const int MAX_WRITERS = 2;
const int MAX_SLEEP_TIME = 5;

int readers, writers, waitingReaders, waitingWriters;
pthread_cond_t canRead, canWrite;
pthread_mutex_t condLock;
/************* CODE FOR READERS *************/
void beginReading(int id) {
  pthread_mutex_lock(&condLock);
  if (writers == 1 || waitingWriters > 0) {
    waitingReaders++;
    pthread_cond_wait(&canRead, &condLock);
    waitingReaders--;

    /****** CRITICAL SECTION ******/
    readers++;
    cout << "Reader " << id << " is now reading\n";
    pthread_mutex_unlock(&condLock);
    pthread_cond_broadcast(&canRead);
    /****** CRITICAL SECTION ******/
  }
}

void endReading(int id) {
  pthread_mutex_lock(&condLock);

  readers--;
  if (readers == 0) {
    pthread_cond_signal(&canWrite);
  }
  cout << "Reader " << id << " has finished reading\n";
  pthread_mutex_unlock(&condLock);
}
/************* CODE FOR READERS *************/
/************* CODE FOR WRITERS *************/
void beginWriting(int id) {
  pthread_mutex_lock(&condLock);
  if (writers == 1 || readers > 0) {
    waitingWriters++;
    pthread_cond_wait(&canWrite, &condLock);
    waitingWriters--;
  }

  /****** CRITICAL SECTION ******/
  writers = 1;
  cout << "Writer " << id << " is writing\n";
  pthread_mutex_unlock(&condLock);
  /****** CRITICAL SECTION ******/
}

void endWriting(int id) {
  pthread_mutex_lock(&condLock);
  writers = 0;

  if (waitingReaders > 0) {
    pthread_cond_signal(&canRead);
  } else {
    pthread_cond_signal(&canWrite);
  }
  pthread_mutex_unlock(&condLock);
}
/************* CODE FOR WRITERS *************/

int main(int argc, char* argv[]) {
  readers = writers = waitingReaders = waitingWriters = 0;


}
