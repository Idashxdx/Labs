#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

// проверка
typedef enum check_data
{
    correct_data,
    incorrect_data,
    memory_malloc_error
} check_data;

check_data check_finite(bool **result,double** numbers, int base, int count, ...);
int gcd(int num, int den);          // Наибольший общий делитель.
bool assignment(int base, int den); // присвоение результату значения ответов
#endif
