
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void error(char *msg) {
    fprintf(stderr, "[!] %s : %s", msg, strerror(errno));
    exit(1);
}

void cheating_death(int sig) {
    puts("Not today!\n");
    while(1) {
        printf("nice try\n");
    }
}

int main() {
    struct sigaction action;
    action.sa_handler = cheating_death;
    if (sigemptyset(&action.sa_mask) == -1)
        error("Signal setting failed");
    action.sa_flags = 0;
    if (sigaction(SIGINT, &action, NULL) == -1)
        error("Overridinng signal action failed");

    char name[30];
    printf("Enter your name: ");
    fgets(name, 30, stdin);
    printf("Hello %s", name);

    return 0;
}
