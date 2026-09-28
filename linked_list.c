#include "linked_list.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

// Structs

typedef struct link link_t;

struct link
{
    elem_t elem;
    link_t *next;
};

struct list
{
    link_t *first;
    link_t *last;
    size_t size;
};

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

static link_t **find_link_pointer(link_t **start, size_t index)
{
    if (*start == NULL || index == 0) return start;

    return find_link_pointer(&(*start)->next, index - 1);
}

static elem_t remove_elem(ioopm_list_t *list, link_t **link_pointer,
                          link_t *new_last, size_t index)
{
    link_t *to_remove = *link_pointer;
    elem_t result = to_remove->elem;
    *link_pointer = to_remove->next;

    if (to_remove->next == NULL)
    {
        list->last = new_last;
    }
    if (index == 0)
    {
        list->first = *link_pointer;
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
    link_t *new = link_create(value, list->first);

    list->first = new;

    if (ioopm_list_is_empty(list))
    {
        list->last = new;
    }

    list->size++;
}

elem_t ioopm_list_head(ioopm_list_t *list)
{
    return list->first->elem;
}

elem_t ioopm_list_last(ioopm_list_t *list)
{
    return list->last->elem;
}

void ioopm_list_insert(ioopm_list_t *list, size_t index, elem_t elem)
{
    assert(list->size >= index);

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
        link_t **link_pointer = find_link_pointer(&list->first, index);

        link_t *link_to_move = *link_pointer;
        link_t *link_to_insert = link_create(elem, link_to_move);
        *link_pointer = link_to_insert;

        list->size++;
    }
}

elem_t ioopm_list_remove(ioopm_list_t *list, size_t index)
{
    assert(list->size > index);

    if (list->size == 0) return -1;

    if (index == 0)
    {
        return remove_elem(list, &list->first, NULL, index);
    }

    link_t **previous_link_pointer = find_link_pointer(&list->first, index - 1);
    link_t **link_pointer = &(*previous_link_pointer)->next;

    return remove_elem(list, link_pointer, *previous_link_pointer, index);
}

elem_t ioopm_list_get(ioopm_list_t *list, size_t index)
{
    link_t **link_pointer = find_link_pointer(&list->first, index);
    if (*link_pointer == NULL) return -1;

    elem_t result = (*link_pointer)->elem;

    return result;
}

int ioopm_list_size(ioopm_list_t *list)
{
    return list->size;
}

bool ioopm_list_is_empty(ioopm_list_t *list)
{
    return ioopm_list_size(list) == 0;
}
