#include "hash_table_iterator.h"
#include "hash_table_structs.h"
#include "hash_table.h"
#include <stdlib.h>

// Struct

struct hash_table_iterator
{
    ioopm_hash_table_t *ht;
    unsigned int current_bucket;
    entry_t *current_entry;
};

// Public functions

ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht)
{
    ioopm_hash_table_iterator_t *it = calloc(1, sizeof(ioopm_hash_table_iterator_t));
    it->ht = ht;
    it->current_bucket = 0;
    it->current_entry = ht->buckets[0];

    while (it->current_entry == NULL && it->current_bucket < it->ht->bucket_size)
    {
        it->current_bucket++;
        it->current_entry = it->ht->buckets[it->current_bucket];
    }

    return it;
}

void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it)
{
    // Todo: stub
    (void) it;
}

bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it)
{
    // Todo: stub
    (void) it;

    return false;
}

void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it)
{
    // Todo: stub
    (void) it;
}

char *ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it)
{
    // Todo: stub
    (void) it;

    return "SOMETHING IS WRONG :DDDDDDD";
}

int ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it)
{
    // Todo: stub
    (void) it;

    return -1;
}