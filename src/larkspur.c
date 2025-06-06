#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "larkspur.h"
#include "cache.h"
#include "server.h"
#include "parser.h"

Larkspur *init_larkspur(LarkspurConfig config) {
    Larkspur *larkspur = malloc(sizeof(Larkspur));
    larkspur->err = SUCCESS;
    
    larkspur->cache = init_cache(config.max_items);
    larkspur->server = init_server(config.port);

    larkspur->logger.log_directory = config.log_directory;

    return larkspur;
}

void free_larkspur(Larkspur *larkspur) {
    if (!larkspur) return;

    free_server(larkspur->server);
    free_cache(larkspur->cache);

    free(larkspur);
}

LarkspurResult run(Larkspur *larkspur) {
    log_info(larkspur->logger, "running larkspur cli.");

    printf("\n");
    while (1) {
        char command_input[128];
        printf("larkspur@127.0.0.1:%d> ", larkspur->server->port);
        if (fgets(command_input, sizeof(command_input), stdin) == NULL) {
            break;
        }

        size_t len = strlen(command_input);
        if (len > 0 && command_input[len - 1] == '\n') {
            command_input[len - 1] = '\0';
        }

        Parser *parser = init_parser(command_input);
        parse_string(parser);

        if (parser->token_count == 0) continue;
        Token command = parser->tokens[0];
        
        if (command.type == SET) {
            if (parser->token_count != 3) {
                printf("command 'set' expects two arguments: <key> <value>\n");
                continue;
            }

            Token op1 = parser->tokens[1];
            Token op2 = parser->tokens[2];
            larkspur_set(larkspur->cache, op1.value, op2.value);
            log_info(larkspur->logger, "set %s: %s", op1.value, op2.value);
        }
        else if (command.type == GET) {
            if (parser->token_count != 2) {
                printf("command 'get' expects one argument: <key>\n");
                continue;
            }

            Token op1 = parser->tokens[1];
            larkspur_get(larkspur->cache, op1.value);
            log_info(larkspur->logger, "get %s", op1.value);
        }
        else if (command.type == DELETE) {
            if (parser->token_count != 2) {
                printf("command 'delete' expects one argument: <key>\n");
                continue;
            }

            Token op1 = parser->tokens[1];
            larkspur_delete(larkspur->cache, op1.value);
            log_info(larkspur->logger, "delete %s", op1.value);
        }
        else if (command.type == CACHE) {
            if (parser->token_count != 2) {
                printf("command 'cache' expects one argument: <variable>\n");
                continue;
            }

            Token op1 = parser->tokens[1];
            larkspur_cache(larkspur->cache, op1.value);
            log_info(larkspur->logger, "cache %s", op1.value);
        }
        else if (command.type == START) {
            if (larkspur->server->running) {
                printf("server already running\n");
                continue;
            }

            pthread_t server_thread;
            ServerThreadArgs *args = malloc(sizeof(ServerThreadArgs));
            args->logger = larkspur->logger;
            args->server = larkspur->server;

            if (pthread_create(&server_thread, NULL, server_thread_func, args) != 0) {
                printf("error");
                return log_error_result(larkspur->logger, THREAD_CREATION_FAILED);
            };
            larkspur->server->running = 1;
            larkspur->server->thread = server_thread;

            log_info(larkspur->logger, "server started");

            printf("ok");
        }
        else if (command.type == STOP) {
            if (!larkspur->server->running) {
                printf("server is not running\n");
                continue;
            }

            larkspur->server->running = 0;

            log_info(larkspur->logger, "server stopped");
            printf("ok");
        }
        else if (strcmp(command.value, "q") == 0 || strcmp(command.value, "quit") == 0) {
            free_parser(parser);
            return SUCCESS;
        }
        else {
            printf("unknown command '%s'", command.value);
        }

        free_parser(parser);
        printf("\n");
    }

    return SUCCESS;
}