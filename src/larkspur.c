#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "larkspur.h"
#include "cache.h"
#include "server.h"
#include "parser.h"

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

LarkspurResult run_cli(Larkspur *larkspur) {
    log_info(larkspur->logger, "running larkspur cli.");

    while (1) {
        char command_input[128];
        printf("\nlarkspur@127.0.0.1:%d> ", larkspur->server->port);
        if (fgets(command_input, sizeof(command_input), stdin) == NULL) {
            break;
        }

        size_t len = strlen(command_input);
        if (len > 0 && command_input[len - 1] == '\n') {
            command_input[len - 1] = '\0';
        }

        Parser *parser = init_parser(command_input);
        parse_string(parser);

        Token command = parser->tokens[0];
        
        if (command.type == SET) {
            if (parser->token_count != 3) {
                printf("command 'set' expects two arguments: <key> <value>\n");
                continue;
            }

            Token op1 = parser->tokens[1];
            Token op2 = parser->tokens[2];
            larkspur_set(larkspur->cache, op1.value, op2.value);
        }
        else if (command.type == GET) {
            if (parser->token_count != 2) {
                printf("command 'get' expects one argument: <key>\n");
                continue;
            }

            Token op1 = parser->tokens[1];
            larkspur_get(larkspur->cache, op1.value);
        }
        else if (command.type == DELETE) {
            if (parser->token_count != 2) {
                printf("command 'delete' expects one argument: <key>\n");
                continue;
            }

            Token op1 = parser->tokens[1];
            larkspur_delete(larkspur->cache, op1.value);
        }
        else if (strcmp(command.value, "q") == 0) {
            free_parser(parser);
            return SUCCESS;
        }
        else {
            printf("unknown command '%s'", command.value);
        }
        printf("\n");
    }

    return SUCCESS;
}