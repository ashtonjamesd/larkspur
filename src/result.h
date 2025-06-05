#ifndef RESULT_H
#define RESULT_H

typedef enum {
    SUCCESS = 0,
    SOCKET_OPENING_FAILED,
    SOCKET_BINDING_FAILED,
    ACCEPT_CLIENT_SOCKET_FAILED,
    READ_CLIENT_BUFFER_FAILED,

    SET_OK,

    GET_OK,
    GET_NULL,

    DELETE_OK,
    DELETE_NULL,
} LarkspurResult;

char *result_to_str(LarkspurResult result);

#endif