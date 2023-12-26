
#ifndef action_h
#define action_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#define MAX_INPUT 19
// проверка

typedef enum check_input_data
{
    correct_data,
    incorrect_data,
} check_input_data;

check_input_data check_base(int base);
check_input_data check_number(char *number, int base);
unsigned long long conversion_to_decimal(char *number, int base);
unsigned long long find_max_number(unsigned long long number_1, unsigned long long number_2);
void print_delete_zeros(unsigned long long max_number, int base);
void representation_at_base(unsigned long long max_number, int base);
#endif
