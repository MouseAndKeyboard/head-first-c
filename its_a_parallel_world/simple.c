
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void error(char *msg) {
    fprintf(stderr, "[!] %s : %s\n", msg, strerror(errno));
    exit(1);
}

void* does_not(void* data) {
    int i = 0;
    for (i=0; i<4; i++) {
        sleep(2);
        puts("does not!");
    }
    return NULL;
}

void* does_too(void* data) {
    int i = 0;
    for (i=0; i<4; i++) {
        sleep(2);
        puts("does too!");
    }
    return NULL;
}

int main() {
    pthread_t t0;
    pthread_t t1;
    if (pthread_create(&t0, NULL, does_not, NULL) == -1)
        error("Creating t0 failed");
    if (pthread_create(&t1, NULL, does_too, NULL) == -1)
        error("Creating t1 failed");

    void* dataresult;
    if (pthread_join(t0, &dataresult) == -1)
        error("Joining thread t0 failed");
    if (pthread_join(t1, &dataresult) == -1)
        error("Joining thread t1 failed");


    return 0;
}
