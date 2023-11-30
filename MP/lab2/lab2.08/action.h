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
    overflow_data
} check_data;



check_data sum(char** result, int base, int count, ...);
#endif