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
    DELETE_OK,
    KEY_NOT_FOUND_ERR,
} LarkspurResult;

char *result_to_str(LarkspurResult result);

#endif