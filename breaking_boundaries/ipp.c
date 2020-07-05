
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main() {
    if (execl("/sbin/ifconfig", "/sbin/ifconfig", NULL) == -1)
        if (execlp("ifconfig", "ifconfig", NULL) == -1) {
            fprintf(stderr, "Cannot run ifconfig: %s", strerror(errno));
            return 1;
        }
    return 0;
}
