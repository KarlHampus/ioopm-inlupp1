#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "../common.h"

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

/// @brief Create a new hash table with the default on_destroy_entry function as nothing
///        to destroy, which doesn't free anything.
/// @return A new empty hash table
/// @param bucket_size the number of buckets
/// @param hash_fn the hash function for hashing the keys
/// @param key_eq_fn the equal function for comparing keys
/// @note asserts that bucket size is greater than 0
ioopm_hash_table_t *ioopm_hash_table_create(size_t bucket_size, ioopm_hash_function *hash_fn,
                                            ioopm_eq_function *key_eq_fn);

/// @brief sets the on_destroy_entry function in the hashtable which will be called
//         each time an entry is destroyed
/// @param ht the hash table
/// @param on_destroy_entry the on destroy function
/// @note Passing a destroy function gives the hashtable ownership of its entries.
/// @note asserts that ht is not null
void ioopm_set_on_destroy_entry(ioopm_hash_table_t *ht,
                                ioopm_on_destroy_entry_function *on_destroy_entry);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
/// @note asserts that ht is not null
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht, duplicates the key
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
/// @note The hashtable borrows the key and value UNLESS a destroy function
///       is passed with ioopm_set_on_destroy_entry, then it takes ownership.
/// @note asserts that ht is not null
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, const elem_t key, const elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @param result where the looked up value will be stored if found
/// @return true if lookup was successful, otherwise false
/// @note asserts that ht is not null
bool ioopm_hash_table_lookup(const ioopm_hash_table_t *ht, const elem_t key, elem_t *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @param result where the looked up value will be stored if found
/// @return true if the remove was successful, otherwise false
/// @note asserts that ht is not null
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, const elem_t key, elem_t *result);

/// @brief verify whether a given hashtable has a value for a given key.
/// @param ht hash table operated upon
/// @param key key to verify
/// @return true if the key exists, false otherwise
/// @note asserts that ht is not null
bool ioopm_hash_table_has_key(const ioopm_hash_table_t *ht, const elem_t key);

/// @brief verify whether a given hashtable is empty
/// @param ht hash table to verify
/// @return true if the hashtable has no keys, otherwise false.
/// @note asserts that ht is not null
bool ioopm_hash_table_is_empty(const ioopm_hash_table_t *ht);

/// @brief retrieve the size of a hashtable
/// @param ht hash table to verify
/// @return the number of entries stored in the given hashtable.
/// @note asserts that ht is not null
size_t ioopm_hash_table_size(const ioopm_hash_table_t *ht);
