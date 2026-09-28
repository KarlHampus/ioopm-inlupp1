#include "linked_list.h"
#include <stdlib.h>
#include <stdbool.h>

typedef int elem_t;

typedef struct link
{
    elem_t elem;
    link_t *next;
} link_t;

struct list
{
    link_t *first;
    link_t *last;
    size_t size;
};

ioopm_list_t *ioopm_list_create(void)
{
    // TODO: Stub
    ioopm_list_t *l = calloc(1, sizeof(ioopm_list_t));
    return l;
}

void ioopm_list_destroy(ioopm_list_t *list)
{
    // TODO: Stub
    free(list);
}

void ioopm_list_append(ioopm_list_t *list, int value)
{
    // TODO: Stub
    (void) list;
    (void) value;
}

void ioopm_list_prepend(ioopm_list_t *list, int value)
{
    // TODO: Stub
    (void) list;
    (void) value;
}

int ioopm_list_head(ioopm_list_t *list)
{
    // TODO: Stub
    (void) list;
    return -1;
}

int ioopm_list_last(ioopm_list_t *list)
{
    // TODO: Stub
    (void) list;
    return -1;
}

// Function get pointer to link

void ioopm_list_insert(ioopm_list_t *list, int index, int value)
{
    // TODO: Stub
    (void) list;
    (void) index;
    (void) value;
}

int ioopm_list_remove(ioopm_list_t *list, int index)
{
    // TODO: Stub
    (void) list;
    (void) index;
    return -1;
}

int ioopm_list_get(ioopm_list_t *list, int index)
{
    // TODO: Stub
    (void) list;
    (void) index;
    return -1;
}

int ioopm_list_size(ioopm_list_t *list)
{
    // TODO: Stub
    (void) list;
    return -1;
}

bool ioopm_list_is_empty(ioopm_list_t *list)
{
    return ioopm_list_size(list) == 0;
}