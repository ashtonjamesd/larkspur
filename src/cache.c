#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"

Cache *init_cache(int max_items) {
    Cache *cache = malloc(sizeof(Cache));
    cache->max_items = max_items;
    cache->entry_count = 0;
    cache->entries = calloc(cache->max_items, sizeof(CacheEntry));

    return cache;
}

void free_cache(Cache *cache) {
    if (!cache) return;

    free(cache);
    for (int i = 0; i < cache->entry_count; i++) {
        if (cache->entries[i].key && cache->entries[i].value) {
            free(cache->entries[i].key);
            free(cache->entries[i].value);
        }
    }
}

int hash(char *key, int mod) {
    int n = 0;
    while (*key) {
        n += *key++;
    }
    return n % mod;
}

LarkspurResult larkspur_set(Cache *cache, char *key, char *value) {
    int hash_key = hash(key, cache->max_items);

    CacheEntry entry = {
        .key = strdup(key),
        .value = strdup(value)
    };

    cache->entries[hash_key] = entry;
    
    printf("ok");
    return SET_OK;
}

LarkspurResult larkspur_get(Cache *cache, char *key) {
    int hash_key = hash(key, cache->max_items);
    if (!cache->entries[hash_key].key) {
        printf("(null)");
        return GET_NULL;
    }

    printf("\"%s\"", cache->entries[hash_key].value);
    return GET_OK;
}

LarkspurResult larkspur_delete(Cache *cache, char *key) {
    int hash_key = hash(key, cache->max_items);

    if (!cache->entries[hash_key].value) {
        printf("(null)");
        return DELETE_NULL;
    }

    free(cache->entries[hash_key].key);
    free(cache->entries[hash_key].value);

    cache->entries[hash_key].key = NULL;
    cache->entries[hash_key].value = NULL;

    cache->entry_count--;

    printf("ok");
    return DELETE_OK;
}