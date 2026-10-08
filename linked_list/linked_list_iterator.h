#pragma once
#include <stdbool.h>

#include "linked_list.h"

/**
* @file linked_list_iterator.h
* @author Hampus Thell, Olof Halvarsson
* @date  1st Oct 2026
* @brief Simple linked list iterator
*
* Linked list iterators provide an interface to iterate through all entries in a linked list.
* An iterator is either positioned at an entry, called the current entry, or it is positioned at-the-end, if it has already iterated through all entries.
* If the underlying linked list of an iterator is modified using any non-iterator function, the iterator is invalidated and should not be used anymore.
*
*/

typedef struct list_iterator ioopm_list_iterator_t;

/// @brief Create a new iterator
/// @param l the list to iterate over
/// @note borrows the list
/// @note asserts that the list is not null
ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l);

/// @brief Destroy the iterator and return its resources
/// @param iter the iterator
/// @note does not free/destroy the list
/// @note asserts that the iter is not null
void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter);

/// @brief Checks if there are more elements to iterate over
/// @param iter the iterator
/// @return false if there is at least one more element
/// @note asserts that the iter is not null
bool ioopm_list_iterator_at_end(const ioopm_list_iterator_t *iter);

/// @brief Step the iterator forward one step, asserts that the
///        iterator is not already at the end.
/// @param iter the iterator
/// @note asserts that the iter is not null
void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter);

/// @brief Return the current element from the underlying list,
///        asserts that the iterator is not already at the end.
/// @param iter the iterator
/// @return the current element
/// @note asserts that the iter is not null
elem_t ioopm_list_iterator_current(const ioopm_list_iterator_t *iter);

/// @brief Remove the current element from the underlying list,
///        asserts that the iterator is not already at the end.
/// @param iter the iterator
/// @return the removed element
/// @note asserts that the iter is not null
/// @note asserts that the current link is not null
elem_t ioopm_list_iterator_remove(ioopm_list_iterator_t *iter);

/// @brief Insert a new element into the underlying list making the current element it's next
/// @param iter the iterator
/// @param element the element to be inserted
/// @note asserts that the iter is not null
void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, elem_t element);