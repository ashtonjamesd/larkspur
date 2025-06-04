#ifndef CACHE_H
#define CACHE_H

typedef struct {
    char *test;
} Cache;

Cache *init_cache();
void   free_cache(Cache *cache);

#endif