#include <stdlib.h>

#pragma once

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