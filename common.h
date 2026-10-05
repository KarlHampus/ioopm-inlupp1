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

/// @brief simple hash function for strings
/// @param elem the string elem to be hashed
/// @return the hash as a size_t
size_t ioopm_string_hash(const elem_t elem);

/// @brief compares two elem_t strings
/// @param elem1 first elem
/// @param elem2 second elem
/// @return true if the elem_t strings are equal
bool ioopm_string_equal(const elem_t elem1, const elem_t elem2);

/// @brief frees the elem key as a string
/// @param key the elem key
/// @param value the elem value
void ioopm_string_key_destroy(elem_t key, elem_t value);
