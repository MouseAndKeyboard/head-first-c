
#include <stdio.h>
#include "encrypt.h"
#include "checksum.h"

int KEY = 17;

int main() {
    char s[] = "Speak friend and enter";
    encrypt(s, 17);
    printf("Encrypted to '%s'\n", s);
    printf("Checksum is: '%i'\n", checksum(s));
    encrypt(s, 17);
    printf("Decrypted back to '%s'\n", s);
    printf("Checksum is: '%i'\n", checksum(s));
    return 0;
}
