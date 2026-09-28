#include "linked_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct link link_t;

struct link
{
    elem_t elem;
    link_t *next;
};

link_t *link_create(elem_t elem, link_t *next)
{
    link_t *link = calloc(1, sizeof(link_t));
    link->elem = elem;
    link->next = next;

    return link;
}

void link_destroy(link_t *link)
{
    free(link);
}

struct list
{
    link_t *first;
    link_t *last;
    size_t size;
};

ioopm_list_t *ioopm_list_create(void)
{
    ioopm_list_t *l = calloc(1, sizeof(ioopm_list_t));
    return l;
}

void ioopm_list_destroy(ioopm_list_t *list)
{
    free(list);
}

void ioopm_list_append(ioopm_list_t *list, elem_t value)
{
    link_t new = {.elem = value, .next = NULL};

    if (ioopm_list_is_empty(list))
    {
        list->first = &new;
    }
    else
    {
        list->last->next = &new;
    }

    list->last = &new;
    list->size++;
}

void ioopm_list_prepend(ioopm_list_t *list, elem_t value)
{
    link_t new = {.elem = value, .next = list->first};

    list->first = &new;
    list->size++;

    if (ioopm_list_is_empty(list))
    {
        list->last = &new;
    }
}

elem_t ioopm_list_head(ioopm_list_t *list)
{
    return list->first->elem;
}

elem_t ioopm_list_last(ioopm_list_t *list)
{
    return list->last->elem;
}

// Function get pointer to link

link_t **find_previous_link(link_t **start, int index)
{
    if (*start == NULL || index == 0)
        return start;
    return find_previous_link(&(*start)->next, index - 1);
}

void ioopm_list_insert(ioopm_list_t *list, int index, elem_t elem)
{
    assert(list->size >= index);

    if (index == 0) {
        ioopm_list_prepend(list, elem);
    }
    else if (index == list->size)
    {
        ioopm_list_append(list, elem);
    }
    else
    {
        link_t **prev_link = find_previous_link(&list->first, index);

        link_t *link_to_move = *prev_link;
        link_t *link_to_insert = link_create(elem, link_to_move);
        *prev_link = link_to_insert;
    }
}

static bool remove_last(ioopm_list_t *list, elem_t *result)
{
    return false;
}

bool ioopm_list_remove(ioopm_list_t *list, size_t index, elem_t *result)
{
    if (index == list->size - 1) return remove_last(list, result);

    link_t **previous = find_previous_link(&list->first, index);
    if (*previous == NULL) return false;

    link_t *to_remove = *previous;
    *result = to_remove->elem;
    *previous = to_remove->next;
    link_destroy(to_remove);

    return true;
}

bool ioopm_list_get(ioopm_list_t *list, size_t index, elem_t *result)
{
    link_t **previous = find_previous_link(&list->first, index);
    if (*previous == NULL) return false;

    result = (*previous)->elem;

    return true;
}

int ioopm_list_size(ioopm_list_t *list)
{
    return list->size;
}

bool ioopm_list_is_empty(ioopm_list_t *list)
{
    return ioopm_list_size(list) == 0;
}