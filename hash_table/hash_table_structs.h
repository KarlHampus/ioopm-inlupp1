#pragma once
#include <stddef.h>

typedef struct entry entry_t;

struct entry
{
    char *key;     // holds the key
    int value;     // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    size_t bucket_size;
    size_t size;
    entry_t **buckets;
};
