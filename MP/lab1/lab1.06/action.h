#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#define MIN_EPSILON 0.000001

// проверка входного значения
enum check_input_data
{
    correct_data,
    incorrect_data,
};
// 1.Это число?
enum check_input_data correct_number(const char *str, double *value)
{
    char *endptr;
    *value = strtold(str, &endptr);
    if (*str != '\0' && *endptr == '\0')
    {
        return correct_data;
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
// через Симпсона
double integral_a(double epsilon)
{
    double result = 0.0;
    double integral = 0.0;
    double a = 0.0;
    double b = 1.0;
    int n = 2;
    do
    {
        integral = result;
        result = (log(1.0 + a) / (a + epsilon)) + (log(1.0 + b) / b);
        double h = (b - a) / n;
        for (int i = 1; i < n; i++)
        {
            double x = i * h + a;
            double fx = log(1.0 + x) / x;
            if (i % 2 == 1)
            {
                result += 4.0 * fx;
            }
            else
            {
                result += 2.0 * fx;
            }
        }
        result = (result * h) / 3.0;
        n *= 2;
    } while (fabs(result - integral) > epsilon);

    return result;
}
// b
double integral_b(double epsilon)
{
    double result = 0.0;
    double integral = 0.0;
    double a = 0.0;
    double b = 1.0;
    int n = 2;
    do
    {
        integral = result;
        result = 1.0 + (exp(-b * b * 0.5));
        double h = (b - a) / n;
        for (int i = 1; i < n; i++)
        {
            double x = i * h + a;
            double fx = exp(-x * x * 0.5);
            if (i % 2 == 1)
            {
                result += 4.0 * fx;
            }
            else
            {
                result += 2.0 * fx;
            }
        }
        result = (result * h) / 3.0;
        n *= 2;
    } while (fabs(result - integral) > epsilon);

    return result;
}
// c
double integral_c(double epsilon)
{
    double result = 0.0;
    double integral = 0.0;
    double a = 0.0;
    double b = 1.0;
    int n = 2;
    do
    {
        integral = result;
        result = (-log(1 - a)) + (-log(1 - b + epsilon));
        double h = (b - a) / n;
        for (int i = 1; i < n; i++)
        {
            double x = i * h + a;
            double fx = -log(1 - x);
            if (i % 2 == 1)
            {
                result += 4.0 * fx;
            }
            else
            {
                result += 2.0 * fx;
            }
        }
        result = (result * h) / 3.0;
        n *= 2;
    } while (fabs(result - integral) > epsilon);

    return result;
    return integral;
}
// d
double integral_d(double epsilon)
{
    double result = 0.0;
    double integral = 0.0;
    double a = 0.0;
    double b = 1.0;
    int n = 2;
    do
    {
        integral = result;
        result = (pow(a + epsilon, a + epsilon)) + (pow(b, b));
        double h = (b - a) / n;
        for (int i = 1; i < n; i++)
        {
            double x = i * h + a;
            double fx = pow(x, x);
            if (i % 2 == 1)
            {
                result += 4.0 * fx;
            }
            else
            {
                result += 2.0 * fx;
            }
        }
        result = (result * h) / 3.0;
        n *= 2;
    } while (fabs(result - integral) > epsilon);

    return result;
}
void print_info()
{
    printf("Enter integer and epsilon\n");
    printf("Calculate the integrals with accuracy epsilon\n");
}

#endif
