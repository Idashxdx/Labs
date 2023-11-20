
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define MAX 9007199254740991.0
#define MIN_EPSILON 0.000000001
// проверка

typedef enum check_input_data
{
    correct_data,
    incorrect_data,
} check_input_data;
typedef enum check_epsilon
{
    correct,
    incorrect
} check_epsilon;

enum check_input_data overflow_or_not(const double value);
enum check_input_data correct_number(const char *str, double *value);
check_epsilon correct_epsilon(const double *epsilon);
double e_lim(double epsilon);
double pi_lim(double epsilon);
double ln2_lim(double epsilon);
double sqrt2_lim(double epsilon);
double gam_lim(double epsilon);
double e_row(double epsilon);
double pi_row(double epsilon);
double ln2_row(double epsilon);
double sqrt2_row(double epsilon);
double gam_row(double epsilon);
double e_equat(double epsilon);
double pi_equat(double epsilon);
double ln2_equat(double epsilon);
double sqrt2_equat(double epsilon);
bool isPrime(int t);
double gam_equat(double epsilon);

#endif
