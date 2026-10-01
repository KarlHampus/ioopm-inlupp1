#pragma once

#include <stdbool.h>

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