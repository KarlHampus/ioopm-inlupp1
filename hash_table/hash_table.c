#include "hash_table.h"
#include "hash_table_structs.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>

// Static (private) functions

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
    entry_t *new = malloc(sizeof(entry_t));
    new->key = key; // Maybe move strdup to insert
    new->value = value;
    new->next = next;
    return new;
}

static void entry_destroy(entry_t *entry, ioopm_hash_table_t *ht)
{
    ht->on_destroy_entry(entry->key, entry->value);
    free(entry);
}

static entry_t **find_previous_ptr(const ioopm_hash_table_t *ht, const elem_t key)
{
    size_t bucket = ht->hash_function(key) % ht->bucket_size;

    // look for an entry with the key we want
    entry_t **previous = &ht->buckets[bucket];

    while (*previous != NULL && !ht->key_equal_function((*previous)->key, key))
    {
        previous = &(*previous)->next;
    }

    return previous;
}

static void nothing_to_destroy(elem_t key, elem_t value)
{
    (void) key;
    (void) value;
}

// Public functions

ioopm_hash_table_t *ioopm_hash_table_create(
    size_t bucket_size, ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn)
{
    assert(bucket_size > 0);

    ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
    ht->buckets = calloc(bucket_size, sizeof(entry_t *));
    ht->size = 0;
    ht->bucket_size = bucket_size;
    ht->key_equal_function = key_eq_fn;
    ht->hash_function = hash_fn;
    ht->on_destroy_entry = &nothing_to_destroy;
    return ht;
}

void ioopm_set_on_destroy_entry(ioopm_hash_table_t *ht,
    ioopm_on_destroy_entry_function *on_destroy_entry)
{
    ht->on_destroy_entry = on_destroy_entry;
}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    for (unsigned int i = 0; i < ht->bucket_size; i++)
    {
        entry_t *current_bucket = ht->buckets[i];

        while (current_bucket != NULL)
        {
            entry_t *next = current_bucket->next;

            entry_destroy(current_bucket, ht);

            current_bucket = next;
        }
    }

    free(ht->buckets);
    free(ht);
    return;
}

// Remove const
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, const elem_t key, elem_t value)
{
    entry_t **previous = find_previous_ptr(ht, key); // find bucket.

    // if the key exists, update the value, otherwise, add a new entry to the end of the list
    if (*previous != NULL)
    {
        (*previous)->value = value;
    }
    else
    {
        *previous = entry_create(key, value, NULL);
        ht->size++;
    }
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, const elem_t key, elem_t *result)
{
    // look for an entry with the key we want
    entry_t **previous = find_previous_ptr(ht, key);

    // if the key exists, return the value, otherwise, indicate that the lookup failed.
    if ((*previous) != NULL)
    {
        entry_t *to_remove = *previous;

        // relink
        *previous = to_remove->next;

        // Save removed value
        *result = to_remove->value;

        // Free value memory
        entry_destroy(to_remove, ht);
        ht->size--;
        return true;
    }
    else
    {
        return false;
    }
}

bool ioopm_hash_table_lookup(const ioopm_hash_table_t *ht, const elem_t key, elem_t *result)
{
    // look for an entry with the key we want
    entry_t **previous = find_previous_ptr(ht, key);

    // if the key exists, return the value, otherwise, indicate that the lookup failed.
    if (*previous != NULL)
    {
        *result = (*previous)->value;
        return true;
    }
    else
    {
        return false;
    }
}

bool ioopm_hash_table_has_key(const ioopm_hash_table_t *ht, const elem_t key)
{
    // look for an entry with the key we want
    entry_t **previous = find_previous_ptr(ht, key);
    return *previous != NULL; // Key exists.
}

bool ioopm_hash_table_is_empty(const ioopm_hash_table_t *ht)
{
    return ht->size == 0;
}

size_t ioopm_hash_table_size(const ioopm_hash_table_t *ht)
{
    return ht->size;
}

