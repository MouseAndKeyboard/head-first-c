
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

void error(char *msg) {
    fprintf(stderr, "[!] %s : %s", msg, strerror(errno));
    exit(1);
}

void fork_error() {
    error("Forking failed");
}

void open_url(char *url) {
    char launch[255];
    pid_t pid = fork();
    if (pid == -1)
        fork_error();

    if (!pid) {
        sprintf(launch, "x-www-browser '%s' &", url);
        system(launch);
    }
}

int main(int argc, char *args[]) {
    char *phrase = args[1];
    char *vargs[] = { "RSS_FEED=https://overreacted.io/rss.xml", NULL };
    int fd[2];

    if (pipe(fd) == -1)
        error("Pipe creation failed");

    pid_t pid = fork();
    if (pid == -1)
        fork_error();

    if (!pid) {
        close(fd[0]);
        dup2(fd[1], 1);

        if (execle("/usr/bin/python2", "/usr/bin/python2", "./rssgossip.py", "-u", phrase, NULL, vargs) == -1)
            error("Running script failed");
    }

    close(fd[1]);
    dup2(fd[0], 0);
    char line[255];
    while(fgets(line, 255, stdin)) {
        if (line[0] == '\t')
            open_url(line + 1);
    }
    return 0;
}
