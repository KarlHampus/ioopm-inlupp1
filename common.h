#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef union elem elem_t;

#define int_elem(x)     ((elem_t) { .i = (x) })
#define u_int_elem(x)   ((elem_t) { .u = (x) })
#define bool_elem(x)    ((elem_t) { .b = (x) })
#define float_elem(x)   ((elem_t) { .f = (x) })
#define ptr_elem(x)     ((elem_t) { .p = (x) })
#define string_elem(x)  ((elem_t) { .s = (x) })

union elem
{
  int i;
  unsigned int u;
  bool b;
  float f;
  void *p;
  char *s;
};

typedef bool ioopm_eq_function(elem_t a, elem_t b);
typedef size_t ioopm_hash_function(elem_t key);
typedef void ioopm_on_destroy_entry_function(elem_t key, elem_t value);

size_t string_hash(const elem_t elem);
bool string_equal(const elem_t elem1, const elem_t elem2);
void string_key_destroy(elem_t key, elem_t value);
