
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

void error(char *msg) {
    fprintf(stderr, "[!] %s : %s\n", msg, strerror(errno));
    exit(1);
}

int open_socket(char *host, char *port) {
    struct addrinfo *res;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(host, port, &hints, &res) == -1)
        error("Resolving address failed");
    int d_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (d_sock == -1)
        error("Opening socket failed");
    int c = connect(d_sock, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);
    if (c == -1)
        error("Connecting to socket failed");
    return d_sock;
}

int say(int socket, char *s) {
    int result = send(socket, s, strlen(s), 0);
    if (result == -1)
        fprintf(stderr, "[!] %s : %s\n", "Talking to server failed", strerror(errno));
    return result;
}

int main(int argc, char *argv[]) {
    /* web page is passed as an argument. */
    int d_sock;
    d_sock = open_socket("en.wikipedia.org", "80");
    char buf[255];

    sprintf(buf, "GET /wiki/%s http/1.1\r\n", argv[1]);
    say(d_sock, buf);

    say(d_sock, "Host: en.wikipedia.org\r\n\r\n");
    char rec[256];
    int bytes_recvd = recv(d_sock, rec, 255, 0);
    while(bytes_recvd) {
        if (bytes_recvd == -1)
            error("Reading from server failed");

        rec[bytes_recvd] = '\0';
        printf("%s", rec);
        bytes_recvd = recv(d_sock, rec, 255, 0);
    }
    close(d_sock);
    return 0;
}