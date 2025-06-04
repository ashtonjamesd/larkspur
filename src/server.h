#ifndef SERVER_H
#define SERVER_H

#include "result.h"
#include "logger.h"

typedef struct {
    int port;
} Server;

Server        *init_server(const int port);
void           free_server(Server *server);

LarkspurResult start_server(Logger logger, Server *larkspur);

#endif