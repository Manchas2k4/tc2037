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