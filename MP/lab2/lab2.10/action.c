#include "action.h"
#include <stdio.h>
#include <stdlib.h>

double myExp(double x, double eps)
{
    double n = 0, s = 1, a = 1;
    while (a > eps)
    {
        a = a * x / (n + 1);
        s += a;
        n++;
    }
    return s;
}

check_epsilon correct_epsilon(const double *epsilon)
{

    if (*epsilon < 0.000001)
    {
        return incorrect;
    }
    else if (*epsilon >= 1.0)
    {
        return incorrect;
    }
    return correct;
}

check_data re_expansion(double **coefs_g, double epsilon, double a, int degree, ...)
{

    if (degree < 0)
    {
        return incorrect_data;
    }
    va_list args;
    va_start(args, degree);
    *coefs_g = (double *)malloc((degree + 1) * sizeof(double));
    if (coefs_g == NULL)
    {
        return memory_malloc_error;
    }
    double coefs_f[degree + 1];
    int ind = 1;
    // если а = 0--->возвращение тех же значений.
    if ((a > -epsilon) && (a < epsilon))
    {
        for (int i = 0; i <= degree; i++)
        {
            (*coefs_g)[i] = va_arg(args, double);
        }
        return correct_data;
    }
    for (int i = 0; i <= degree + 1; i++)
    {
        coefs_f[i] = va_arg(args, double) * ind;
        (*coefs_g)[i] = epsilon;
        ind *= a;
    }
    va_end(args);
    for (int i = 0; i <= degree; i++)
    {
        (*coefs_g)[0] += coefs_f[i];
    }

    int factorial = 1;
    for (int i = 1; i <= degree; i++)
    {
        factorial *= i;

        for (int j = i; j <= degree; j++)
        {
            coefs_f[j] = coefs_f[j] * (j - i + 1) / a;
            (*coefs_g)[i] += coefs_f[j];
        }
        (*coefs_g)[i] /= factorial;
    }
    return correct_data;
}
