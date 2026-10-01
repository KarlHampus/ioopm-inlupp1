#pragma once
#include <stdbool.h>
#include <stddef.h>

/**
 * @file hash_table.h
 * @author Olof Halvarsson & Hampus Thell
 * @date Tuesday the 15th of September 2026
 * @brief Simple hash table that maps string keys to integer values.
 *
 * TODO: Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 *
 */

typedef struct hash_table ioopm_hash_table_t;

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(size_t bucket_size);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht, duplicates the key
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, const char *key, int value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @param result where the looked up value will be stored if found
/// @return true if lookup was successful, otherwise false
bool ioopm_hash_table_lookup(const ioopm_hash_table_t *ht, const char *key, int *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @param result where the looked up value will be stored if found
/// @return true if the remove was successful, otherwise false
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, const char *key, int *result);

/// @brief verify whether a given hashtable has a value for a given key.
/// @param ht hash table operated upon
/// @param key key to verify
/// @return true if the key exists, false otherwise
bool ioopm_hash_table_has_key(const ioopm_hash_table_t *ht, const char *key);

/// @brief verify whether a given hashtable is empty
/// @param ht hash table to verify
/// @return true if the hashtable has no keys, otherwise false.
bool ioopm_hash_table_is_empty(const ioopm_hash_table_t *ht);

/// @brief retrieve the size of a hashtable
/// @param ht hash table to verify
/// @return the number of entries stored in the given hashtable.
size_t ioopm_hash_table_size(const ioopm_hash_table_t *ht);