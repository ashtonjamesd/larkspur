#include "result.h"

char *result_to_str(LarkspurResult result) {
    switch (result) {
        case SUCCESS: return "success";
        case SOCKET_OPENING_FAILED: return "unable to open socket for larkspur server";
        case SOCKET_BINDING_FAILED: return "unable to bind socket for larkspur server";
        case ACCEPT_CLIENT_SOCKET_FAILED: return "an error occurred while accepting the client socket";
        case READ_CLIENT_BUFFER_FAILED: return "an error occurred while reading client buffer";
        case SET_OK: return "set ok";
        case GET_OK: return "get ok";
        case GET_NULL: return "get null";
        case DELETE_OK: return "delete ok";
        case DELETE_NULL: return "delete null";
        case THREAD_CREATION_FAILED: return "a thread could not be created";
        default: return "unknown result";
    }
}