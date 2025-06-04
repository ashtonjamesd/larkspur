#include <stdlib.h>
#include "cache.h"

Cache *init_cache() {
    Cache *cache = malloc(sizeof(Cache));

    return cache;
}

void free_cache(Cache *cache) {
    if (!cache) return;

    free(cache);
}

LarkspurResult larkspur_set(Cache *cache, char *key, char *value) {


    return SET_OK;
}

LarkspurResult larkspur_get(Cache *cache, char *key) {

    return GET_OK;
}

LarkspurResult larkspur_delete(Cache *cache, char *key) {

    
    return DELETE_OK;
}