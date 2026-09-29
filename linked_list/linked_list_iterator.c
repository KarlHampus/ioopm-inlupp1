#include <stdbool.h>
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
    return iter->current == NULL;
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter)
{
    // Todo: STUB
    // remember to increase the index :D
    (void)iter;
}

// Olle
elem_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter)
{
    return iter->current->elem;
}

int ioopm_list_iterator_remove(ioopm_list_iterator_t *iter)
{
    // Todo: STUB
    (void)iter;
    // remember to increase the index :D
    return -1;
}

// Olle
void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, elem_t element)
{
    ioopm_list_t *lst = iter->list;

    ioopm_list_insert(lst, iter->current_index, element);

    iter->current_index++;
}