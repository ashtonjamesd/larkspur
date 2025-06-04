#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>

#include "server.h"

Server *init_server(const int port) {
    Server *server = malloc(sizeof(Server));
    server->port = port;

    return server;
}

void free_server(Server *server) {
    if (!server) return;

    free(server);
}

LarkspurResult start_server(Logger logger, Server *server) {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        return log_error_result(logger, SOCKET_OPENING_FAILED);
    }

    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(server->port);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        return log_error_result(logger, SOCKET_BINDING_FAILED);
    }

    listen(sockfd, SOMAXCONN);
    log_info(logger, "running server on %d", server->port);

    while (1) {
        socklen_t client_addr_len = sizeof(client_addr);
        int clientsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (clientsockfd < 0) {
            return log_error_result(logger, ACCEPT_CLIENT_SOCKET_FAILED);
        }

        log_info(logger, "client successfully connected");

        char buffer[1024];
        int has_read = read(clientsockfd, buffer, 1024);
        if (has_read < 0) {
            return log_error_result(logger, READ_CLIENT_BUFFER_FAILED);
        }

        log_info(logger, "received payload: %s", buffer);
        printf("%s", buffer);
    }

    return SUCCESS;
}