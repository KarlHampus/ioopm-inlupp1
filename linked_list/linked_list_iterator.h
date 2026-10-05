#pragma once
#include <stdbool.h>

#include "linked_list.h"

typedef struct list_iterator ioopm_list_iterator_t;

/// @brief Create a new iterator
/// @param l the list to iterate over
/// @note borrows the list
ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l);

/// @brief Destroy the iterator and return its resources
/// @param iter the iterator
/// @note does not free/destroy the list
void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter);

/// @brief Checks if there are more elements to iterate over
/// @param iter the iterator
/// @return false if there is at least one more element
bool ioopm_list_iterator_at_end(const ioopm_list_iterator_t *iter);

/// @brief Step the iterator forward one step, asserts that the
///        iterator is not already at the end.
/// @param iter the iterator
void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter);

/// @brief Return the current element from the underlying list,
///        asserts that the iterator is not already at the end.
/// @param iter the iterator
/// @return the current element
elem_t ioopm_list_iterator_current(const ioopm_list_iterator_t *iter);

/// @brief Remove the current element from the underlying list,
///        asserts that the iterator is not already at the end.
/// @param iter the iterator
/// @return the removed element
elem_t ioopm_list_iterator_remove(ioopm_list_iterator_t *iter);

/// @brief Insert a new element into the underlying list making the current element it's next
/// @param iter the iterator
/// @param element the element to be inserted
void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, elem_t element);