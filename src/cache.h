#ifndef CACHE_H
#define CACHE_H

#include "result.h"

typedef struct {
    char *key;
    char *value;
} CacheEntry;

typedef struct {
    CacheEntry *entries;
    int         entry_count;
    int         max_items;
} Cache;

Cache         *init_cache(int max_items);
void           free_cache(Cache *cache);

LarkspurResult larkspur_set(Cache *cache, char *key, char *value);
LarkspurResult larkspur_get(Cache *cache, char *key);
LarkspurResult larkspur_delete(Cache *cache, char *key);

#endif