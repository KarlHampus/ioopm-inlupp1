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

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter)
{
    return iter->current == NULL;
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter)
{
    assert(iter->current != NULL);

    iter->current = iter->current->next;
    iter->current_index++;
}

elem_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter)
{
    assert(iter->current != NULL);
    return iter->current->elem;
}

elem_t ioopm_list_iterator_remove(ioopm_list_iterator_t *iter)
{
    assert(iter->current != NULL);

    link_t *next = iter->current->next;
    elem_t elem = ioopm_list_remove(iter->list, iter->current_index);

    iter->current = next;

    return elem;
}

void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, elem_t element)
{
    ioopm_list_t *lst = iter->list;

    ioopm_list_insert(lst, iter->current_index, element);

    iter->current_index++;
}