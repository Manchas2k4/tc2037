#include <iostream>
#include <iomanip>
#include "utils.h"
#include <pthread.h>

using namespace std;

const int SIZE = 10000;
const int THREADS = 8;

void enumerationSort(int *arr, int *temp, int size) {
    int count;

    for (int i = 0; i < size; i++) {
        count = 0;
        for (int j = 0; j < size; j++) {
            if (arr[j] < arr[i]) {
                count++;
            } else if (arr[j] == arr[i] && j < i) {
                count++;
            }
        }

        temp[count] = arr[i];
    }
}

typedef struct {
    int start, end, size;
    int *arr, *temp;
} Block;

void* task(void* param) {
    Block* b;
    int count;

    b = (Block*) param;
    for (int i = b->start; i < b->end; i++) {
        count = 0;
        for (int j = 0; j < b->size; j++) {
            if (b->arr[j] < b->arr[i]) {
                count++;
            } else if (b->arr[j] == b->arr[i] && j < i) {
                count++;
            }
        }

        b->temp[count] = b->arr[i];
    }
    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    int *arr, *temp;
    double ms;
    Block blocks[THREADS];
    pthread_t tids[THREADS];
    int blockSize;

    arr = new int[SIZE];
    random_array(arr, SIZE);

    temp = new int[SIZE];

    display_array("before: ", arr);

    ms = 0;
    for (int j = 0; j < N; j++) {
        start_timer();
        enumerationSort(arr, temp, SIZE);
        ms += stop_timer();
    }

    display_array("after: ", temp);
    cout << "one thread - avg time = " << fixed << setprecision(5) << (ms / N) << " ms.\n";

    blockSize = SIZE / THREADS;
    for (int i = 0; i < THREADS; i++) {
        blocks[i].start = i * blockSize;
        blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : SIZE;
        blocks[i].arr = arr;
        blocks[i].temp = temp;
        blocks[i].size = SIZE;
    }

    ms = 0;
    for (int j = 0; j < N; j++) {
        start_timer();
        for (int i = 0; i < THREADS; i++) {
            pthread_create(&tids[i], NULL, task, &blocks[i]);
        }
        for (int i = 0; i < THREADS; i++) {
            pthread_join(tids[i], NULL);
        }
        ms += stop_timer();
    }

    display_array("after: ", temp);
    cout << "parallel - avg time = " << fixed << setprecision(5) << (ms / N) << " ms.\n";

    delete [] arr;
    delete [] temp;

    return 0;
}