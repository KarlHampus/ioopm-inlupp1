#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "../common.h"

/**
 * @file linked_list.h
 * @author Olof Halvarsson & Hampus Thell
 * @date Monday the 28th of September 2026
 * @brief Simple linked list that stores values linked to the next entry.
 */

typedef struct list ioopm_list_t; /// Meta: struct definition goes in C file

/// @brief Creates a new empty list
/// @return an empty linked list
ioopm_list_t *ioopm_list_create(void);

/// @brief Tear down the linked list and return all its memory (but not the memory of the elements)
/// @param list the list to be destroyed
/// @note asserts that list is not null
void ioopm_list_destroy(ioopm_list_t *list);

/// @brief Insert at the end of a linked list in O(1) time
/// @param list the linked list that will be appended
/// @param elem the elem to be appended
/// @note borows elem
/// @note asserts that list is not null
void ioopm_list_append(ioopm_list_t *list, elem_t elem);

/// @brief Insert at the front of a linked list in O(1) time
/// @param list the linked list that will be prepended to
/// @param elem the elem to be prepended
/// @note borows elem
/// @note asserts that list is not null
void ioopm_list_prepend(ioopm_list_t *list, elem_t elem);

/// @brief Return the first element of a linked list in O(1) time
/// @pre the list is non-empty
/// @param list the linked list to take the head of
/// @note asserts that list is not null
elem_t ioopm_list_head(const ioopm_list_t *list);

/// @brief Return the last element of a linked list in O(1) time
/// @pre the list is non-empty
/// @param list the linked list to take the last element of
/// @note asserts that list is not null
elem_t ioopm_list_last(const ioopm_list_t *list);

/// @brief Insert an element into a linked list in O(n) time.
/// The valid values of index are [0,n] for a list of n elements,
/// where 0 means before the first element and n means after
/// the last element.
/// @pre 0 <= index <= length(list)
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @param elem the elem to be inserted
/// @note borows elem
/// @note asserts that list is not null
/// @note asserts that index is less than or equal to the size of the list
void ioopm_list_insert(ioopm_list_t *list, size_t index, elem_t elem);

/// @brief Remove an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @pre 0 <= index < length(list)
/// @param list the linked list
/// @param index the position in the list
/// @return the elem removed
/// @note asserts that list is not null
/// @note asserts that index is less than the size of the list
elem_t ioopm_list_remove(ioopm_list_t *list, size_t index);

/// @brief Retrieve an element from a linked list in O(n) time.
/// The valid values of index are [0,n-1] for a list of n elements,
/// where 0 means the first element and n-1 means the last element.
/// @pre 0 <= index < length(list)
/// @param list the linked list that will be extended
/// @param index the position in the list
/// @return the elem at the given position
/// @note asserts that list is not null
/// @note asserts that index is less than the size of the list
elem_t ioopm_list_get(ioopm_list_t *list, size_t index);

/// @brief Lookup the number of elements in the linked list in O(1) time
/// @param list the linked list
/// @return the number of elements in the list
/// @note asserts that list is not null

size_t ioopm_list_size(const ioopm_list_t *list);

/// @brief Test whether a list is empty or not
/// @param list the linked list
/// @return true if the number of elements int the list is 0, else false
/// @note asserts that list is not null
bool ioopm_list_is_empty(const ioopm_list_t *list);