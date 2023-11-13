
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
typedef enum check_epsilon
{
    correct,
    incorrect
} check_epsilon;

check_epsilon correct_epsilon(const double *epsilon);
check_data re_expansion(double ** coefs_g,double epsilon, double a,int degree,...);
#endif
