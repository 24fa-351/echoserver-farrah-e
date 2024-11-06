#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "thisServer.h"

#define buffer_size 10000

void initializingServer(int port){
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_size;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        fprintf(stderr, "Error creating socket\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created\n");
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);
    printf("Binding socket\n");
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        fprintf(stderr, "Error binding socket\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket bound\n");
    if (listen(server_socket, 1) < 0) {
        fprintf(stderr, "Error listening on socket\n");
        close(server_socket);
        exit(EXIT_FAILURE);
    }
    printf("Server is now on port:  %d", port);
    while (1) {
        client_address_size = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_size);
        if (client_socket < 0) {
            fprintf(stderr, "Error accepting client\n");
            exit(EXIT_FAILURE);
        }
        printf("Client connected\n");
        client(client_socket);
        printf("Client disconnected\n");
        close(client_socket);
    }

}

void client(int client_socket){
    char buffer[buffer_size];
    ssize_t bytesreceived;
    while ((bytesreceived = recv(client_socket, buffer, buffer_size - 1, 0)) > 0) {
        buffer[bytesreceived] = '\0';
        send(client_socket, buffer, bytesreceived, 0);
    }
    close (client_socket);
}