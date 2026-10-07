#include <math.h>
#include <assert.h>
#include "hash_table_iterator.h"
#include "hash_table_structs.h"
#include "hash_table.h"
#include <stdlib.h>

// Struct

struct hash_table_iterator
{
    ioopm_hash_table_t *ht;
    size_t current_bucket;
    entry_t *current_entry;
};

// Public functions

ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht)
{
    assert(ht != NULL);
    ioopm_hash_table_iterator_t *it = calloc(1, sizeof(ioopm_hash_table_iterator_t));
    it->ht = ht;
    it->current_bucket = 0;
    it->current_entry = ht->buckets[0];

    if (it->current_entry == NULL) ioopm_hash_table_iterator_advance(it);

    return it;
}

void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it)
{
    assert(it != NULL);
    free(it);
}

bool ioopm_hash_table_iterator_at_end(const ioopm_hash_table_iterator_t *it)
{
    assert(it != NULL);
    bool at_last_bucket = it->current_bucket >= it->ht->bucket_size - 1;
    return it->current_entry == NULL && at_last_bucket;
}

void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it)
{
    assert(it != NULL);
    assert(!ioopm_hash_table_iterator_at_end(it) && "Iterator at end when advancing.");

    if (it->current_entry != NULL)
    {
        it->current_entry = it->current_entry->next;
    }

    while (it->current_entry == NULL && it->current_bucket < it->ht->bucket_size - 1)
    {
        it->current_bucket++;
        it->current_entry = it->ht->buckets[it->current_bucket];
    }
}

elem_t ioopm_hash_table_iterator_current_key(const ioopm_hash_table_iterator_t *it)
{
    assert(it != NULL);
    return it->current_entry->key;
}

elem_t ioopm_hash_table_iterator_current_value(const ioopm_hash_table_iterator_t *it)
{
    assert(it != NULL);
    return it->current_entry->value;
}