#include "hash_table.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define No_Buckets 17

// Structs

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
    entry_t *buckets;
};

// Static (private) functions

static entry_t *entry_create(char *key, int value, entry_t *next)
{
    entry_t *new = malloc(sizeof(entry_t));
    new->key = strdup(key);
    new->value = value;
    new->next = next;
    return new;
}

static void entry_destroy(entry_t *entry)
{
    free(entry->key);
    free(entry);
}

static size_t string_knr_hash(const char *str)
{
    size_t result = 0;
    while (*str != '\0')
    {
        result = result * 31 + ((unsigned char)*str);
        str++;
    }
    return result;
}

static entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key)
{
    size_t bucket = string_knr_hash(key) % ht->bucket_size;

    // look for an entry with the key we want
    entry_t *previous = &ht->buckets[bucket]; // Start as sentinel
    while (previous->next != NULL && strcmp(previous->next->key, key) != 0)
    {
        previous = previous->next;
    }

    return previous;
}

// Public functions

ioopm_hash_table_t *ioopm_hash_table_create(unsigned int bucket_size)
{
    assert(bucket_size > 0);

    ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
    ht->buckets = calloc(bucket_size, sizeof(entry_t));
    ht->size = 0;
    ht->bucket_size = bucket_size;
    return ht;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    for (unsigned int i = 0; i < ht->bucket_size; i++)
    {
        entry_t *current_bucket = ht->buckets[i].next;

        while (current_bucket != NULL)
        {
            entry_t *next = current_bucket->next;

            entry_destroy(current_bucket);

            current_bucket = next;
        }
    }

    free(ht->buckets);
    free(ht);
    return;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value)
{
    entry_t *previous = find_previous_entry(ht, key); // find bucket.

    // if the key exists, update the value, otherwise, add a new entry to the end of the list
    if (previous->next != NULL)
    {
        previous->next->value = value;
    }
    else
    {
        previous->next = entry_create(key, value, NULL);
        ht->size++;
    }
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key, int *result)
{
    // look for an entry with the key we want
    entry_t *previous = find_previous_entry(ht, key);

    // if the key exists, return the value, otherwise, indicate that the lookup failed.
    if (previous->next != NULL)
    {
        entry_t *to_remove = previous->next;

        // relink
        previous->next = to_remove->next;

        // Save removed value
        *result = to_remove->value;

        // Free value memory
        entry_destroy(to_remove);
        ht->size--;
        return true;
    }
    else
    {
        return false;
    }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result)
{
    // look for an entry with the key we want
    entry_t *previous = find_previous_entry(ht, key);

    // if the key exists, return the value, otherwise, indicate that the lookup failed.
    if (previous->next != NULL)
    {
        *result = previous->next->value;
        return true;
    }
    else
    {
        return false;
    }
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key)
{
    // look for an entry with the key we want
    entry_t *previous = find_previous_entry(ht, key);
    return previous->next != NULL; // Key exists.
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
    return ht->size == 0;
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
    return ht->size;
}