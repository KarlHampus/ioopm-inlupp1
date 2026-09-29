#pragma once
#include <stdbool.h>

#include "linked_list.h"

typedef struct list_iterator ioopm_list_iterator_t;

ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l);

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter);

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter);

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter);

int ioopm_list_iterator_current(ioopm_list_iterator_t *iter);

int ioopm_list_iterator_remove(ioopm_list_iterator_t *iter);

void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, int element);