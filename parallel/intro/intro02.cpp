#include <iostream>
#include <iomanip>
#include <pthread.h>

using namespace std;

void* task (void* param) {
    int limit = *((int*) param);

    for (int i = 1; i <= limit; i++) {
        cout << i << " ";
    }
    cout << "\n";
    return 0; //pthread_exit(0);
}

int main(int argc, char* argv[]) {
    pthread_t tid;
    int limit = 100;

    pthread_create(&tid, NULL, task, &limit);

    pthread_join(tid, NULL);

    return 0;
}