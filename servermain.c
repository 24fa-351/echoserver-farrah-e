#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "thisServer.h"
int main(int argc, char *argv[]) {
    int port = 0;
    int opt;
    for (int currWordIndex = 1; currWordIndex < argc; currWordIndex++) {
        if (strcmp(argv[currWordIndex], "-p") == 0 && currWordIndex + 1 < argc) {
            port = atoi(argv[currWordIndex + 1]);
            currWordIndex++; // Skip the next argument since it's the port
        }
    }
    if (port == 0) {
        printf("Please specify a port number using the -p {port num}\n");
        return 1;
    }
    initializingServer(port);
    return 0;
}