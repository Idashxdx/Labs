#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

// проверка
typedef enum check_data
{
    correct_data,
    incorrect_data,
    malloc_memory_error
} check_data;

bool check_number(const char *str, int base);
char *sum_of_two_numbers(const char *a,const char *b, int base);
check_data sum(char** result, int base, int count, ...);
#endif