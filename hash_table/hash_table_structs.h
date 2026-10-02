#pragma once
#include <stddef.h>

typedef struct entry entry_t;

struct entry
{
    elem_t key;     // holds the key
    elem_t value;   // holds the value
    entry_t *next;  // points to the next entry (possibly NULL)
};

struct hash_table
{
    size_t bucket_size;
    size_t size;
    entry_t **buckets;
    ioopm_eq_function *key_equal_function;
    ioopm_hash_function *hash_function;
    ioopm_on_destroy_entry_function *on_destroy_entry;
};
