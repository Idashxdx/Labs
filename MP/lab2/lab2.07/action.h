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
    not_roots
} check_data;

typedef enum check_epsilon
{
    correct,
    incorrect
} check_epsilon;

check_epsilon correct_epsilon(const double *epsilon);
check_data dichotomy(double *root, int input, double epsilon, double a, double b);
double equation1(double x);
double equation2(double x);
#endif
