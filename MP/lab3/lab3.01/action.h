
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

 
// проверка
typedef enum check_data
{
    correct_data,
    incorrect_data,
    memory_malloc_error,
    memory_realloc_error
} check_data;

char get_symbols_for_base(int value, int base);
check_data truns_number(char ** result, int number, int r);
int negative(int a);
void increment(int *a);
int increase(int a, int b);
#endif