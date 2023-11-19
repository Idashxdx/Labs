#include "action.h"
enum check_input_data overflow_or_not(const double value)
{
    if (value >= MAX)
    {
        return incorrect_data;
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
check_epsilon correct_epsilon(const double *epsilon)
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
double e_lim(double epsilon)
{
    int n = 1;
    double lim = 2;
    double result = lim;
    do
    {
        n++;
        result = lim;
        lim = pow((1 + 1.0 / n), n);

    } while (fabs(result - lim) > epsilon);
    return result;
}
double pi_lim(double epsilon)
{
    int n = 1;
    double lim = 4;
    double result = lim;
    do
    {
        result = lim;
        lim = lim * 4 * (n + 1) * n / ((2 * n + 1) * (2 * n + 1));
        n++;
    } while (fabs(result - lim) > epsilon);
    return result;
}
double ln2_lim(double epsilon)
{
    int n = 1;
    double lim = 1;
    double result = lim;
    do
    {
        n++;
        result = lim;
        lim = n * (pow(2, 1.0 / n) - 1);

    } while (fabs(result - lim) > epsilon);
    return result;
}
double e_row(double epsilon)
{
    int n = 1;
    double sum = 2;
    double result = sum;
    double factorial = 1;
    do
    {
        n++;
        result = sum;
        factorial *= n;
        sum += 1/factorial;

    } while (fabs(result - sum) > epsilon);
    return result;
}
double pi_row(double epsilon)
{
    int n = 1;
    double numerator = 1;
    double sum = numerator / (2 * n - 1);
    double result = sum;
    double fraction;
    do
    {
        n++;
        numerator *= -1;
        result = sum;
        fraction = numerator / (2 * n - 1);
        sum += fraction;
    } while (fabs(result - sum) > epsilon);
    return 4 * result;
}
double sqrt2_lim(double epsilon)
{
    double x = -0.5;
    double result = x - x * x / 2 + 1;
    do
    {
        x = result;
        result = x - x * x / 2 + 1;

    } while (fabs(result - x) > epsilon);
    return result;
}



double ln2_row(double epsilon);
double sqrt2_row(double epsilon);
double gam_row(double epsilon);
double e_equat(double epsilon);
double pi_equat(double epsilon);
double ln2_equat(double epsilon);
double sqrt2_equat(double epsilon);
double gam_equat(double epsilon);
double gam_lim(double epsilon)
{
    if (epsilon < 0.0001)
    {
        epsilon = 0.0001;
    }
    int m = 1;
    double lim = 0;
    double result = lim;
    do
    {
        m++;
        result = lim;
        lim = 0;
        double sum = 0;
        double C = m;
        double ln = 0;
        for (int k = 2; k <= m; k++)
        {
            C *= (m - k + 1.0) / k;
            ln += log(k);
            sum = C * ln / k;
            if (k & 1)
            {
                sum *= -1;
            }
            lim += sum;
        }

    } while (fabs(result - lim) > epsilon);
    return result;
}