#include "encrypt.h"

void encrypt(char* msg, int key) {
    while(*msg) {
        *msg = *msg ^ key;
        msg++;
    }
}
