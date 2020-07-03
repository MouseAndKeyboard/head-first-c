
#include <stdio.h>
#include "encrypt.h"

int KEY = 17;

int main() {
    char msg[80];
    while(fgets(msg, 79, stdin)) {
        xorcrypt(msg, KEY);
        printf("%s", msg);
    }
}
