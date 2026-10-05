#include "linked_list.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "linked_list_structs.h"

// Static functions

static link_t *link_create(elem_t elem, link_t *next)
{
    link_t *link = calloc(1, sizeof(link_t));
    link->elem = elem;
    link->next = next;

    return link;
}

static void link_destroy(link_t *link)
{
    free(link);
}

static link_t **find_pointer_to_link_iterative(link_t **start, size_t index)
{
    while (*start != NULL && index != 0)
    {
        start = &(*start)->next;
        index--;
    }

    return start;
}

static link_t **find_pointer_to_link(link_t **start, size_t index)
{
    if (*start == NULL || index == 0)
        return start;

    return find_pointer_to_link(&(*start)->next, index - 1);
}

static elem_t remove_elem(ioopm_list_t *list, link_t **to_remove_pointer, link_t *new_last)
{
    link_t *to_remove = *to_remove_pointer;
    elem_t result = to_remove->elem;
    *to_remove_pointer = to_remove->next;

    if (to_remove->next == NULL)
    {
        list->last = new_last;
    }

    list->size--;
    link_destroy(to_remove);

    return result;
}

// Public functions

ioopm_list_t *ioopm_list_create(void)
{
    ioopm_list_t *l = calloc(1, sizeof(ioopm_list_t));
    return l;
}

void ioopm_list_destroy(ioopm_list_t *list)
{
    assert(list != NULL);
    if (list->first != NULL)
    {
        ioopm_list_remove(list, 0);
        ioopm_list_destroy(list);
    }
    else
    {
        free(list);
    }
}

void ioopm_list_append(ioopm_list_t *list, elem_t value)
{
    assert(list != NULL);
    link_t *new = link_create(value, NULL);

    if (ioopm_list_is_empty(list))
    {
        list->first = new;
    }
    else
    {
        list->last->next = new;
    }

    list->last = new;
    list->size++;
}

void ioopm_list_prepend(ioopm_list_t *list, elem_t value)
{
    assert(list != NULL);
    link_t *new = link_create(value, list->first);

    list->first = new;

    if (ioopm_list_is_empty(list))
    {
        list->last = new;
    }

    list->size++;
}

elem_t ioopm_list_head(const ioopm_list_t *list)
{
    assert(list != NULL);
    return list->first->elem;
}

elem_t ioopm_list_last(const ioopm_list_t *list)
{
    assert(list != NULL);
    return list->last->elem;
}

void ioopm_list_insert(ioopm_list_t *list, size_t index, elem_t elem)
{
    assert(list != NULL && list->size >= index);

    if (index == 0)
    {
        ioopm_list_prepend(list, elem);
    }
    else if (index == list->size)
    {
        ioopm_list_append(list, elem);
    }
    else
    {
        link_t **pointer_to_link = find_pointer_to_link(&list->first, index);

        link_t *link_to_move = *pointer_to_link;
        link_t *link_to_insert = link_create(elem, link_to_move);
        *pointer_to_link = link_to_insert;

        list->size++;
    }
}

elem_t ioopm_list_remove(ioopm_list_t *list, size_t index)
{
    assert(list != NULL && list->size > index);

    if (index == 0)
    {
        return remove_elem(list, &list->first, NULL);
    }

    link_t **before_to_remove_pointer = find_pointer_to_link(&list->first, index - 1);
    link_t **to_remove_pointer = &(*before_to_remove_pointer)->next;

    return remove_elem(list, to_remove_pointer, *before_to_remove_pointer);
}

elem_t ioopm_list_get(ioopm_list_t *list, size_t index)
{
    assert(list != NULL && index >= 0 && index < list->size);

    link_t **pointer_to_link = find_pointer_to_link(&list->first, index);

    elem_t result = (*pointer_to_link)->elem;

    return result;
}

size_t ioopm_list_size(const ioopm_list_t *list)
{
    assert(list != NULL);
    return list->size;
}

bool ioopm_list_is_empty(const ioopm_list_t *list)
{
    assert(list != NULL);
    return ioopm_list_size(list) == 0;
}