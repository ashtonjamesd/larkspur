#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

Cache *init_cache(int max_items) {
    Cache *cache = malloc(sizeof(Cache));
    cache->max_items = max_items;
    cache->entry_count = 0;
    cache->entries = malloc(sizeof(CacheEntry) * cache->max_items);

    return cache;
}

void free_cache(Cache *cache) {
    if (!cache) return;

    free(cache);
}

int hash(char *key) {
    int n = 0;
    while (*key) {
        n += *key++;
    }
    return n;
}

LarkspurResult larkspur_set(Cache *cache, char *key, char *value) {
    int hash_num = hash(key);

    CacheEntry entry = {
        .key = hash_num,
        .value = value
    };

    cache->entries[hash_num % 16] = entry;
    
    printf("ok");
    return SET_OK;
}

LarkspurResult larkspur_get(Cache *cache, char *key) {
    int hash_key = hash(key) % 16;
    printf("%s", cache->entries[hash_key].value);
    
    return GET_OK;
}

LarkspurResult larkspur_delete(Cache *cache, char *key) {


    return DELETE_OK;
}