#include "common.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

size_t ioopm_string_hash(const elem_t elem)
{
    char *str = elem.s;
    size_t result = 0;
    while (*str != '\0')
    {
        result = result * 31 + ((unsigned char)*str);
        str++;
    }
    return result;
}

bool ioopm_string_equal(const elem_t elem1, const elem_t elem2)
{
    return strcmp(elem1.s, elem2.s) == 0;
}

void ioopm_string_key_destroy(elem_t key, elem_t value)
{
    free(key.s);
    (void) value;
}
