#ifndef action_h
#define action_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#define MAX 9007199254740991.0
#define MIN_EPSILON 0.000001

// проверка входного значения
enum check_input_data
{
    data_overflow,
    correct_data,
    incorrect_data,
};
// 2.Не привышает максимальное?
enum check_input_data overflow_or_not(const double value)
{
    if (value >= MAX)
    {
        return data_overflow;
    }
    return correct_data;
}
// 1.Это число?
enum check_input_data correct_number(const char *str, double *value)
{
    char *endptr;
    *value = strtold(str, &endptr);
    if (*str != '\0' && *endptr == '\0')
    {
        return overflow_or_not(*value);
    }
    value = NULL;
    return incorrect_data;
}
// проверка эпсилона
enum check_epsilon
{
    correct,
    incorrect
};
enum check_epsilon correct_epsilon(const double *epsilon)
{
    if (*epsilon < MIN_EPSILON)
    {
        return incorrect;
    }
    else if (*epsilon >= 1.0)
    {
        return incorrect;
    }
    return correct;
}
// sum a
double sum_a(double x, double epsilon)
{
    int n = 0;
    double sum = 1.0;
    double result = 0;
    do
    {
        result += sum;
        n++;
        sum *= (x / n);
    } while (fabs(sum) >= epsilon);
    switch (overflow_or_not(result))
    {
    case correct_data:
        printf("Result of point 'a' = %lf\n", result);
        break;
    case data_overflow:
        printf("Result of point 'a' ---> Result overflow\n");
        break;
    }
}
// sum b
double sum_b(double x, double epsilon)
{
    int n = 0;
    double sum = 1.0;
    double result = 0;
    do
    {
        result += sum;
        n++;
        sum *= (-x * x) / ((2.0 * n) * (2.0 * n - 1.0));
    } while (fabs(sum) >= epsilon);
    switch (overflow_or_not(result))
    {
    case correct_data:
        printf("Result of point 'b' = %lf\n", result);
        break;
    case data_overflow:
        printf("Result of point 'b' ---> Result overflow\n");
        break;
    }
}
// sum c
double sum_c(double x, double epsilon)
{
    int n = 0;
    double sum = 1.0;
    double result = 0;
    double three = 27.0;
    do
    {
        result += sum;
        n++;
        sum *= (three * (x * x) * (n + 1.0) * (n + 1.0) * (n + 1.0)) / ((3.0 * n + 1) * (3.0 * n + 2.0) * (3.0 * n + 3.0));
    } while (fabs(sum) >= epsilon);
    switch (overflow_or_not(result))
    {
    case correct_data:
        printf("Result of point 'c' = %lf\n", result);
        break;
    case data_overflow:
        printf("Result of point 'c' ----> Result overflow\n");
        break;
    }
}
// sum d
double sum_d(double x, double epsilon)
{
    int n = 1;
    double sum = -x * x / 2;
    double result = 0;
    do
    {
        result += sum;
        n++;
        sum *= (-1.0 * (2.0 * n + 1.0) * (x * x)) / (2.0 * n);
    } while (fabs(sum) >= epsilon);
    switch (overflow_or_not(result))
    {
    case correct_data:
        printf("Result of point 'd' = %lf\n", result);
        break;
    case data_overflow:
        printf("Result of point 'd' ----> Result overflow\n");
        break;
    }
}

void print_info()
{
    printf("Enter integer and epsilon\n");
    printf("Calculate the values of sums with accuracy epsilon\n");
}

#endif
