
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void error(char *msg) {
    fprintf(stderr, "[!] %s : %s\n", msg, strerror(errno));
    exit(1);
}

int drinks = 2000000;

void* drink(void* data) {
    int i;
    for (i=0; i<100000; i++) {
        drinks -= 1;
    }
    return NULL;
}

int main() {
    pthread_t threads[20];
    int t;
    printf("%i drinks\n", drinks);
    for (t=0; t<20; t++)
        pthread_create(&threads[t], NULL, drink, NULL);


    void* result;
    for (t=0; t<20; t++)
        pthread_join(threads[t], &result);


    printf("%i drinks\n", drinks);
    return 0;
}
