#include "action.h"

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
double equation(double x, int input)
{
    if (input == 1)
    {
        return 4 - exp(x) - 2 * pow(x, 2);
    }
    if (input == 3)
    {
        return tan(x);
    }
    else
    {
        return pow(x, 2) + 0.3; // no
    }
}
check_data dichotomy(double *root, int input, double epsilon, double a, double b)
{
    if (input == 1)
    {
        a = 0.0;
        b = 1.0;
    }
    if (input == 3)
    {
        a = 0.7;
        b = 2.0;
    }
    else
    {
        a = 0.1;
        b = 0.2;
    }
    if (b - a <= epsilon)
    {
        return incorrect_data;
    }
    double fun_a = equation(a, input);
    double fun_b = equation(b, input);
    if (fun_a * fun_b > epsilon)
    {
        return not_roots;
    }
    double c;
    while ((b - a) / 2 > epsilon)
    {
        c = (a + b) / 2;
        if (fabs(equation(c, input)) < epsilon)
        {
            *root = c;
            return correct_data;
        }
        else if (equation(a, input) * equation(c, input) < epsilon)
        {
            b = c;
        }
        else
        {
            a = c;
        }
    }
    *root = (a + b) / 2;
    return correct_data;
}