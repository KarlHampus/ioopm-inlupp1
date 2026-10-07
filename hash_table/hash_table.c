#include "hash_table.h"
#include "hash_table_structs.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>

static const size_t primes[] = {17, 31, 67, 127, 257, 509, 1021, 2053, 4099, 8191, 16381,
                                32749, 65521, 131071, 262139, 524287, 1048573};

// Static (private) functions

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
    entry_t *new = malloc(sizeof(entry_t));
    new->key = key;
    new->value = value;
    new->next = next;
    return new;
}

static void entry_destroy(entry_t *entry, ioopm_hash_table_t *ht)
{
    ht->on_destroy_entry(entry->key, entry->value);
    free(entry);
}

static entry_t **find_pointer_to_entry(const ioopm_hash_table_t *ht, const elem_t key)
{
    size_t bucket = ht->hash_function(key) % ht->bucket_size;

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

static void resize_hash_table(ioopm_hash_table_t *ht)
{
    size_t old_bucket_size = ht->bucket_size;
    ht->bucket_size = primes[++(ht->bucket_size_index)];

    entry_t **old_buckets = ht->buckets;

    ht->buckets = calloc(ht->bucket_size, sizeof(entry_t *));
    ht->size = 0;

    entry_t *next = NULL;
    for (size_t i = 0; i < old_bucket_size; i++)
    {
        for(entry_t *entry = old_buckets[i]; entry != NULL; entry = next)
        {
            ioopm_hash_table_insert(ht, entry->key, entry->value);
            next = entry->next;
            free(entry);
        }
    }

    free(old_buckets);
}

// Public functions

ioopm_hash_table_t *ioopm_hash_table_create_with_load_factor(
    ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn, float load_factor)
{
    ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
    ht->buckets = calloc(primes[0], sizeof(entry_t *));
    ht->size = 0;
    ht->bucket_size = primes[0];
    ht->key_equal_function = key_eq_fn;
    ht->hash_function = hash_fn;
    ht->on_destroy_entry = &nothing_to_destroy;
    ht->bucket_size_index = 0;
    ht->load_factor = load_factor;
    return ht;
}

ioopm_hash_table_t *ioopm_hash_table_create(
    ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn)
{
    return ioopm_hash_table_create_with_load_factor(hash_fn, key_eq_fn, 0.75);
}

void ioopm_set_on_destroy_entry(ioopm_hash_table_t *ht,
    ioopm_on_destroy_entry_function *on_destroy_entry)
{
    assert(ht != NULL);
    ht->on_destroy_entry = on_destroy_entry;
}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    assert(ht != NULL);
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

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, const elem_t key, elem_t value)
{
    assert(ht != NULL);
    entry_t **pointer_to_entry = find_pointer_to_entry(ht, key);

    // if the key exists, update the value, otherwise, add a new entry to the end of the list
    if (*pointer_to_entry != NULL)
    {
        (*pointer_to_entry)->value = value;
    }
    else
    {
        *pointer_to_entry = entry_create(key, value, NULL);
        ht->size++;

        float current_load_factor = ht->size / ht->bucket_size;
        if (current_load_factor > ht->load_factor)
        {
            resize_hash_table(ht);
        }
    }
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, const elem_t key, elem_t *result)
{
    assert(ht != NULL);
    entry_t **pointer_to_entry = find_pointer_to_entry(ht, key);

    // if the key exists, return the value, otherwise, indicate that the lookup failed.
    if ((*pointer_to_entry) != NULL)
    {
        entry_t *to_remove = *pointer_to_entry;

        // relink
        *pointer_to_entry = to_remove->next;

        // Save removed value
        *result = to_remove->value;

        // Free entry memory
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
    assert(ht != NULL);
    entry_t **pointer_to_entry = find_pointer_to_entry(ht, key);

    // if the key exists, return the value, otherwise, indicate that the lookup failed.
    if (*pointer_to_entry != NULL)
    {
        *result = (*pointer_to_entry)->value;
        return true;
    }
    else
    {
        return false;
    }
}

bool ioopm_hash_table_has_key(const ioopm_hash_table_t *ht, const elem_t key)
{
    assert(ht != NULL);
    entry_t **pointer_to_entry = find_pointer_to_entry(ht, key);
    return *pointer_to_entry != NULL;
}

bool ioopm_hash_table_is_empty(const ioopm_hash_table_t *ht)
{
    assert(ht != NULL);
    return ht->size == 0;
}

size_t ioopm_hash_table_size(const ioopm_hash_table_t *ht)
{
    assert(ht != NULL);
    return ht->size;
}

