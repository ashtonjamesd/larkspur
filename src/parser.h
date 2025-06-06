#ifndef PARSER_H
#define PARSER_H

typedef enum {
    IDENTIFIER,
    NUMERIC,

    GET,
    SET,
    CACHE,
    DELETE,
    START,
    STOP,

    BAD,
    EOF_TOKEN,
} TokenType;

typedef struct {
    char     *value;
    TokenType type;
} Token;

typedef struct {
    int    current;
    char  *source;
    Token *tokens;
    int    token_count;
    int    token_capacity;
} Parser;

Parser *init_parser(char *source);
void    free_parser(Parser *parser);

void    parse_string(Parser *parser);

#endif