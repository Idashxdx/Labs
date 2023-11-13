#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>

// проверка
typedef enum check_data
{
    correct_data,
    incorrect_data,
    memory_allocation_error
} check_data;

int count_length(char *str);                                                                        //-l
check_data get_string_reversed(char *str, char **str_reverse);                                      //-r
check_data get_string_odd_uppercase(char *str, char **str_uppercase);                               //-u
check_data get_string_sorted(char *str, char **str_sort);                                           //-n
check_data get_string_concaten(char *str[], int argc_qnty, char **str_concaten, unsigned int seed); //-c
void print_info();

#endif
