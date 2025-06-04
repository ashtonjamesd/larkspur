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