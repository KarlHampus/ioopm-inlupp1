#pragma once

typedef struct entry entry_t;

struct entry
{
    char *key;     // holds the key
    int value;     // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
    unsigned int bucket_size;
    unsigned int size;
    entry_t **buckets;
};
