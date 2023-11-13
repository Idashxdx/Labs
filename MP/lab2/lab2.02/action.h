#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>

// проверка
typedef enum check_data
{
    correct_data,
    incorrect_data,
    overflow_data
} check_data;

check_data geometrical_mean(double *gm, int count, ...); // 1.
check_data check_values(double *rnd, double number, int degree);//2
double exponentiation(double number, int degree);
#endif
