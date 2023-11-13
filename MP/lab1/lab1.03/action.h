#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#define MAX 2147483647
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
enum check_input_data correct_number_2(const char *str, int *value)
{
    char *endptr;
    *value = strtoll(str, &endptr, 10);
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
//-q кв. уравнение
// 1. проверка дискриминанта
enum check_discriminant
{
    correct_discriminant,
    incorrect_discriminant
};
enum check_discriminant discriminant(double epsilon, double a, double b, double c, double *x1, double *x2)
{
    double D = b * b - 4.0 * a * c;
    if (D < epsilon)
    {
        return incorrect_discriminant;
    }
    *x1 = (-b + sqrtl(D)) / (2.0 * a);
    *x2 = (-b - sqrtl(D)) / (2.0 * a);
    return correct_discriminant;
}
// 2. вывод (вариации в main)
void print_solution_equation(double epsilon, double a, double b, double c)
{
    double x1, x2;
    switch (discriminant(epsilon, a, b, c, &x1, &x2))
    {
    case incorrect_discriminant:
        printf("(%lf)x^2 + (%lf)x + (%lf) = 0-NO roots\n", a, b, c);
        break;
    case correct_discriminant:
        printf("(%lf)x^2 + (%lf)x + (%lf) = 0-Roots x1 = %lf, x2 = %lf\n", a, b, c, x1, x2);
        break;
    }
}
//-t являются ли длинами?
// 1.проверка прямоугольный треугольник?
enum check_right_triangle
{
    right,
    not_right
};
enum check_right_triangle right_triangle(double epsilon, double a, double b, double c)
{
    if (fabs(a) < epsilon || fabs(b) < epsilon || fabs(c) < epsilon)
    {
        return not_right;
    }
    else if (((fabs(a * a - b * b - c * c) <= epsilon) || (fabs(c * c - b * b - a * a) <= epsilon) || (fabs(a * a - c * c - b * b) <= epsilon)))
    {
        return right;
    }
    return not_right;
}
// 2. вывод
void print_result(double epsilon, double a, double b, double c)
{
    switch (right_triangle(epsilon, a, b, c))
    {
    case not_right:
        printf("%lf, %lf, %lf - the NOT sides of the right triangle\n", a, b, c);
        break;
    case right:
        printf("%lf, %lf, %lf - the sides of the right triangle\n", a, b, c);
        break;
    }
}
//-m кратное одно второму?
// проверка на кратность
enum check_multiple
{
    multiple_number,
    not_multiple_number
};
enum check_multiple multiple_or_not(int number_1, int number_2)
{
    if (number_1 < 0 || number_2 <= 0)
    {
        return not_multiple_number;
    }
    if (number_1 % number_2 == 0)
    {
        return multiple_number;
    }
    return not_multiple_number;
}

void print_multiple_or_not(int number_1, int number_2)
{
    switch (multiple_or_not(number_1, number_2))
    {
    case not_multiple_number:
        printf("%d - not a multiple of %d\n", number_1, number_2);
        break;
    case multiple_number:
        printf("%d - a multiple of %d\n", number_1, number_2);
        break;
    }
}
void print_info()
{
    printf("Enter action and numbers \n");
    printf("-q: epsilon and coefficients of the quadratic equation. Result- solutions for unique permutations\n");
    printf("-m: 2 non-zero integers. Result-is a multiple of 1 to 2\n");
    printf("-t: epsilon and the lenghts of the sides of a right traingle. Result- are they or are they not\n");
}

#endif