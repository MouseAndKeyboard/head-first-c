#include "encrypt.h"

void xorcrypt(char* msg, int key) {
    while(*msg) {
        *msg = *msg ^ key;
        msg++;
    }
}
