#include "action.h"
int gcd(int num, int den)
{
    if (num == 0)
    {
        return den;
    }
    else
    {
        return gcd(den % num, num);
    }
}
bool assignment(int base, int den)
{
    for (int i = 2; i <= den; i++)
    {
        if (den % i == 0)
        {
            if (base % i != 0)
            {
                return false;
            }
        }
        while (den % i == 0)
        {
            den /= i;
        }
    }
    return true;
}

check_data check_finite(bool **result, double **numbers, int base, int count, ...)
{
    if (count < 1)
    {
        return incorrect_data;
    }
    double epsilon = 1e-9;
    *numbers = (double *)malloc(sizeof(double) * count);
    if (*numbers == NULL)
    {
        return memory_malloc_error;
    }
    *result = (bool *)malloc(sizeof(bool) * count);
    if (*result == NULL)
    {
        free(numbers);
        return memory_malloc_error;
    }
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++)
    {
        int num;     // числитель
        int den = 1; // знаменатель
        double decimal = va_arg(args, double);
        if (decimal <= 0 || decimal >= 1)
        {
            return incorrect_data;
        }

        (*numbers)[i] = decimal;
        while (fabs(decimal - floor(decimal)) > epsilon)
        {
            decimal *= 10;
            den *= 10;
        }
        num = (int)decimal;

        int divider = gcd(num, den);
        num /= divider;
        den /= divider;

        (*result)[i] = assignment(base, den);
    }

    va_end(args);
    return correct_data;
}
