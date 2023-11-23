
#ifndef action_h
#define action_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
// проверка

typedef enum check_input_data
{
    correct_data,
    incorrect_data,
} check_input_data;

check_input_data check_base(int base);
check_input_data check_number(char *number, int base);
int conversion_to_decimal(char *number, int base);
int find_max_number(int number_1, int number_2);
void print_delete_zeros(int max_number, int base);
void representation_at_base(int max_number, int base);
#endif
