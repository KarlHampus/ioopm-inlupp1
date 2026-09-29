#include <stdbool.h>
#include <assert.h>
#include "linked_list_iterator.h"
#include "linked_list.h"
#include "linked_list_structs.h"

struct list_iterator
{
    ioopm_list_t *list;
    link_t *current;
    size_t current_index;
};

ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l)
{
    ioopm_list_iterator_t *it = calloc(1, sizeof(ioopm_list_iterator_t));
    it->list = l;
    it->current = l->first;
    it->current_index = 0;
    return it;
}

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);
}

// Olle
bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter)
{
    // Todo: STUB
    (void)iter;
    return false;
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter)
{
    assert(iter->current != NULL);

    iter->current = iter->current->next;
    iter->current_index++;
}

// Olle
int ioopm_list_iterator_current(ioopm_list_iterator_t *iter)
{
    // Todo: STUB
    (void)iter;
    return -1;
}

elem_t ioopm_list_iterator_remove(ioopm_list_iterator_t *iter)
{
    assert(iter->current != NULL);

    link_t *next = iter->current->next;
    elem_t elem = ioopm_list_remove(iter->list, iter->current_index);

    iter->current = next;

    return elem;
}

// Olle
void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, int element)
{
    // Todo: STUB
    (void)iter;
    // remember to increase the index :D
    (void)element;
}