#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

void error(char *msg) {
    fprintf(stderr, "[!] | %s : %s.\n", msg, strerror(errno));
    exit(1);
}

int score = 0;

void end_game(int sig) {
    printf("\nFinal score: %i\n", score);
    exit(0);
}

void time_out(int sig) {
    puts("Out of time!");
    raise(SIGINT);
}

void catch_signal(int sig, void (*handler)(int)) {
    struct sigaction action;
    action.sa_handler = handler;
    if (sigemptyset(&action.sa_mask) == -1)
        error("Masking signal failed");
    action.sa_flags = 0;
    if (sigaction(sig, &action, NULL) == -1)
        error("Overriding signal failed");
}

void display_message(char *msg) {
    printf("[*] | (%i) - %s\n", score, msg);
}

int main() {
    /* We want to set up signal hooks */
    catch_signal(SIGALRM, time_out);
    catch_signal(SIGINT, end_game);

    srandom(time(0));

    while(1) {
        int a = random() % 11;
        int b = random() % 11;

        alarm(5);

        printf("\nWhat is %i * %i?: ", a, b);
        char text[4];
        fgets(text, 4, stdin);
        int ans = atoi(text);
        if (ans == a * b) {
            score++;
            display_message("Correct!");
        }
        else {
            char msg[32];
            sprintf(msg, "Incorrect. %i * %i = %i.\n", a, b, a * b);
            display_message(msg);
        }
    }
    return 0;
}
