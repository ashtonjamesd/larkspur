#ifndef LARKSPUR_H
#define LARKSPUR_H

#include "cache.h"
#include "server.h"
#include "result.h"
#include "logger.h"

typedef struct {
    Server        *server;
    Cache         *cache;
    LarkspurResult err;
    Logger         logger;
} Larkspur;

typedef struct {
    int   port;
    char *log_dir;
} LarkspurConfig;

Larkspur      *init_larkspur(LarkspurConfig config);
void           free_larkspur(Larkspur *larkspur);

LarkspurResult run(Larkspur *larkspur);
LarkspurResult run_cli(Larkspur *larkspur);

#endif