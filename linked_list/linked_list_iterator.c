#include <stdbool.h>
#include "linked_list_iterator.h"
#include "linked_list.h"

struct list_iterator
{
    ioopm_list_t *list;
};

ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l)
{
    ioopm_list_iterator_t *it = calloc(1, sizeof(ioopm_list_iterator_t)); 
    it->list = l;
    return it;
}

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);
}

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter)
{
    // Todo: STUB
    (void) iter;
    return false;
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter)
{
    // Todo: STUB
    (void) iter;
}

int ioopm_list_iterator_current(ioopm_list_iterator_t *iter)
{
    // Todo: STUB
    (void) iter;
    return -1;
}

int ioopm_list_iterator_remove(ioopm_list_iterator_t *iter)
{
    // Todo: STUB
    (void) iter;
    return -1;
}

void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, int element)
{
    // Todo: STUB
    (void) iter;
    (void) element;
}