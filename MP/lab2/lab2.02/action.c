#include "action.h"
// va_list a-va_start(a,b)b-к-во,va_arg(a,type),va_end(a)

check_data geometrical_mean(double *gm, int count, ...)
{
    if (count == 0)
    {
        *gm = 0.0;
        return correct_data;
    }
    else if (count < 0)
    {
        return incorrect_data;
    }
    else
    {
        *gm = 1.0;
        va_list args;
        va_start(args, count);

        for (int i = 0; i < count; i++)
        {
            double value = va_arg(args, double);
            *gm *= value;
        }
        *gm = pow(*gm, 1.0 / count);
        va_end(args);
        if (isinf(*gm) || isnan(*gm)) // проверяем на +-бес. или не число
        {
            return overflow_data;
        }
        return correct_data;
    }
}
double exponentiation(double number, int degree)
{
    if (degree == 0)
    {
        return 1.0;
    }
    else if (degree == 1)
    {
        return number;
    }
    double res = exponentiation(number, degree / 2);
    if (!(degree & 1))
    {
        return res * res;
    }
    else if (degree > 0)
    {
        return res * res * number;
    }
    else
    {
        return res * res * (1.0 / number);
    }
}
check_data check_values(double *rnd, double number, int degree)
{
    if (degree == 0 && number == 0)
    {
        return incorrect_data;
    }

    *rnd = exponentiation(number, degree);
    if (isinf(*rnd) || isnan(*rnd)) // проверяем на +-бес. или не число
    {
        return overflow_data;
    }
    return correct_data;
}