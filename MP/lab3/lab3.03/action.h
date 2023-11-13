
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define EPSILON 1e-9
// проверка
typedef enum check_data
{
    correct_data,
    incorrect_data,
    memory_realloc_error,
    memory_malloc_error
} check_data;

typedef struct employee
{
    unsigned int id;
    char name[256];
    char surname[256];
    double salary;
} employee;

check_data read_file(FILE *input_file, employee **empl, int *size_empl);
int sort_ascending(const void *compare_1, const void *compare_2);
int sort_descending(const void *compare_1, const void *compare_2);
#endif
