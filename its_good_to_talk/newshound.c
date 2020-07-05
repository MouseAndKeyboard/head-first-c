
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void error(char *msg) {
    fprintf(stderr, "%s: %s.\n", msg, strerror(errno));
    exit(1);
}

int main(int argc, char *args[]) {
    char *phrase = args[1];
    char *vargs[] = {"RSS_FEED=https://overreacted.io/rss.xml", NULL};
    FILE *f = fopen("stories.txt", "w");
    if (!f)
        error("Couldn't open file");

    pid_t pid = fork();
    if (pid == -1)
        error("Couldn't fork");

    if (!pid) {
        if (dup2(fileno(f), 1) == -1)
            error("Can't redirect standard output");

        if (execle("/usr/bin/python2", "/usr/bin/python2", "./rssgossip.py", phrase, NULL, vargs) == -1)
            error("Can't run script");
    }

    int pid_status;
    if (waitpid(pid, &pid_status, 0) == 1)
        error("Error waiting for child");

    if (WEXITSTATUS(pid_status))
        puts("Non-zero return status from child");

    return 0;
}
