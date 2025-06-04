#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"

#define advance() parser_advance(parser)
#define current() current_char(parser)

Parser *init_parser(char *source) {
    Parser *parser = malloc(sizeof(Parser));
    parser->current = 0;
    parser->source = strdup(source);

    parser->token_capacity = 1;
    parser->token_count = 0;
    parser->tokens = malloc(sizeof(Token) * parser->token_capacity);

    return parser;
}

void free_parser(Parser *parser) {
    for (int i = 0; i < parser->token_count; i++) {
        free(parser->tokens[i].value);
    }

    free(parser->tokens);
    free(parser->source);
    free(parser);
}

static int is_end(Parser *parser) {
    return parser->source[parser->current] == '\0';
}

static void parser_advance(Parser *parser) {
    parser->current++;
}

static char current_char(Parser *parser) {
    return parser->source[parser->current];
}


static Token new_token(char *value, TokenType type) {
    Token token = {
        .value = strdup(value),
        .type = type,
    };

    return token;
}

static Token parse_identifier(Parser *parser) {
    int start = parser->current;

    while (current() && current() != ' ') {
        advance();
    }

    int length = parser->current - start;
    char *value = malloc(length + 1);
    strncpy(value, parser->source + start, length);

    value[length] = '\0';

    TokenType type = IDENTIFIER;
    if (strcmp("set", value) == 0) {
        type = SET;
    }
    else if (strcmp("get", value) == 0) {
        type = GET;
    }
    else if (strcmp("delete", value) == 0) {
        type = DELETE;
    }

    Token token = new_token(value, type);
    free(value);

    return token;
}

static Token parse_numeric(Parser *parser) {
    int start = parser->current;

    while (current() && isdigit(current())) {
        advance();
    }

    int length = parser->current - start;
    char *value = malloc(length + 1);
    strncpy(value, parser->source + start, length);
    value[length] = '\0';

    Token token = new_token(value, NUMERIC);
    free(value);

    return token;
}

static Token parse_token(Parser *parser) {
    if (isalpha(current())) {
        return parse_identifier(parser);
    }
    else if (isdigit(current())) {
        return parse_numeric(parser);
    }
    else {
        return new_token("BAD", BAD);
    }
}

void parse_string(Parser *parser) {
    while (!is_end(parser)) {
        Token token = parse_token(parser);
        
        if (parser->token_count >= parser->token_capacity) {
            parser->token_capacity *= 2;
            parser->tokens = realloc(parser->tokens, sizeof(Token) * parser->token_capacity);
        }

        parser->tokens[parser->token_count++] = token;
        advance();
    }

    parser->tokens[parser->current] = new_token("", EOF_TOKEN);

    // for (int i = 0; i < parser->token_count; i++) {
    //     printf("%s: (%d)\n", parser->tokens[i].value, parser->tokens[i].type);
    // }
}