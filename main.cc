#include <stdlib.h>
#include <stdio.h>
#include "SyncBuf.h"
#include "3rdparty/thread.h"

using namespace std;

#define NTHREADS 300

SyncBuf syncBuf;

void putData(int);
void getData(int);

int main()
{
    thread_t workers[NTHREADS];

    for (int i = 0; i < NTHREADS; ++i) {
        if (i % 2) {
            thread_create(&workers[i], putData, i);
        } else {
            thread_create(&workers[i], getData, 0);
        }
    }

    for (int i = 0; i < NTHREADS; ++i) {
        thread_join(workers[i]);
    }

    return 0;
}

void putData(int data)
{
    syncBuf.put(data);
    printf("Sent %d.\n", data);
}

void getData(int dummy)
{
    dummy = syncBuf.get();
    printf("Got %d.\n", dummy);
}