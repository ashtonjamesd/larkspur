#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>

#include "result.h"
#include "logger.h"

typedef struct {
    int       port;
    pthread_t thread;
    int       running;
} Server;

typedef struct {
    Logger  logger;
    Server *server;
} ServerThreadArgs;

Server        *init_server(const int port);
void           free_server(Server *server);

void          *server_thread_func(void *args);
LarkspurResult start_server(Logger logger, Server *server);

#endif