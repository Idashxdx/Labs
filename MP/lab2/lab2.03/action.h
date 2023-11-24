
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

// проверка
typedef enum check_data
{
    correct_data,
    incorrect_data,
    realloc_memory_error,
    incorrect_file,
    malloc_memory_error
} check_data;

check_data substring_search(const char * str, int count, ...);

#endif