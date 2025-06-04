#include <stdlib.h>
#include <stdio.h>

#include "larkspur.h"
#include "cache.h"
#include "server.h"

Larkspur *init_larkspur(LarkspurConfig config) {
    Larkspur *larkspur = malloc(sizeof(Larkspur));
    larkspur->err = SUCCESS;
    
    larkspur->cache = init_cache();
    larkspur->server = init_server(config.port);

    larkspur->logger.log_dir = config.log_dir;

    return larkspur;
}

void free_larkspur(Larkspur *larkspur) {
    if (!larkspur) return;

    free_server(larkspur->server);
    free_cache(larkspur->cache);

    free(larkspur);
}

LarkspurResult run(Larkspur *larkspur) {
    log_info(larkspur->logger, "running larkspur service.");
    
    LarkspurResult result = start_server(larkspur->logger, larkspur->server);
    if (result != SUCCESS) return result;



    return SUCCESS;
}