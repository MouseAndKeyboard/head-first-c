
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>

void error(char *msg) {
    fprintf(stderr, "[!] %s : %s\n", msg, strerror(errno));
    exit(1);
}

int open_listener_socket() {
    int s = socket(PF_INET, SOCK_STREAM, 0);
    if (s == -1)
        error("Opening socket failed");
    return s;
}

void bind_to_port(int socket, int port) {
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char * )&reuse, sizeof(int)) == -1)
        error("Setting socket reuse option failed");
    int c = bind(socket, (struct sockaddr *) &name, sizeof(name));
    if (c == -1)
        error("Binding socket failed");
}

int say(int socket, char *s) {
    int result = send(socket, s, strlen(s), 0);
    if (result == -1)
        fprintf(stderr, "[-] %s : %s", "Talking to the client failed", strerror(errno));
    return result;
}

int listener_d;

void handle_shutdown(int sig) {
    if (listener_d)
        close(listener_d);

    exit(0);
}

void catch_signal(int sig, void(*handler)(int)) {
    struct sigaction action;
    action.sa_handler = handler;
    if(sigemptyset(&action.sa_mask) == -1)
        error("Masking signal failed");
    action.sa_flags = 0;
    if (sigaction(sig, &action, NULL) == -1)
        error("Overriding signal failed");
}

int read_in(int socket, char *buf, int len) {
    char *s = buf;
    int slen = len;
    int c = recv(socket, s, slen, 0);
    while((c > 0) && (s[c-1] != '\n')) {
        s += c;
        slen -= c;
        c = recv(socket, s, slen, 0);
    }

    if (c < 0)
        return c;
    else if (c == 0)
        buf[0] = '\0';
    else
        s[c-1] = '\0';
    printf("%s\n", buf);
    return len - slen;
}

int main() {
    catch_signal(SIGINT, handle_shutdown);

    listener_d = open_listener_socket();
    bind_to_port(listener_d, 30000);

    if (listen(listener_d, 10) == -1)
        error("Listener creation failed");

    puts("Waiting for a connection...");

    char buf[255];
    while(1) {
        struct sockaddr_storage client_addr;
        unsigned int address_size = sizeof(client_addr);
        int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, & address_size);
        if (connect_d == -1)
            error("Accepting connection failed");

        if(say(connect_d, "Knock! Knock!\r\n") != -1) {
            read_in(connect_d, buf, sizeof(buf));
            if (strcasecmp("Who's there?", buf))
                say(connect_d, "(you're supposed to say 'who's there?')\r\n");
            else {
                if (say(connect_d, "oscar\r\n>") != -1) {
                    read_in(connect_d, buf, sizeof(buf));
                    if (strcasecmp(buf, "oscar who?"))
                        say(connect_d, "(you're supposed to say 'oscar who?')");
                    else {
                        say(connect_d, "oscar silly question, you get a silly answer\n");
                    }
                }
            }
        }
        close(connect_d);
    }
    return 0;
}
