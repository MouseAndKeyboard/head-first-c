
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    char *feeds[] = { "https://www.lesswrong.com/feed.xml?view=community-rss&karmaThreshold=30",
                      "https://overreacted.io/rss.xml"};

    int times = 2;
    char *phrase = argv[1];
    for (int i = 0; i < times; i++) {
        char var[255];
        sprintf(var, "RSS_FEED=%s", feeds[i]);
        char *vars[] = {var, NULL};

        pid_t pid = fork();
        if (pid == -1) {
            fprintf(stderr, "Couldn't fork process: %s.\n", strerror(errno));
            return 1;
        }

        if (!pid) {
            if (execle("/usr/bin/python2", "usr/bin/python2", "./rssgossip.py", phrase, NULL, vars) == -1) {
                fprintf(stderr, "Can't run script: %s.\n", strerror(errno));
                return 1;
            }
        }
    }
    return 0;
}
