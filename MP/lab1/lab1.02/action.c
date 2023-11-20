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
double e_equat(double epsilon)
{
    double x = 2;
    double result = x;
    do
    {
        x = result;
        result = x - (log(x) - 1) * x;

    } while (fabs(result - x) > epsilon);
    return result;
}
double pi_equat(double epsilon)
{
    double x = 3;
    double result = x;
    do
    {
        x = result;
        result = x + (cos(x) + 1) / (sin(x));

    } while (fabs(result - x) > epsilon);
    return result;
}
double ln2_equat(double epsilon)
{
    double e = e_equat(epsilon);
    double x = 1;
    double result = x;
    do
    {
        x = result;
        result = x - ((pow(e, x) - 2) / (pow(e, x)));

    } while (fabs(result - x) > epsilon);
    return result;
}
double sqrt2_equat(double epsilon)
{
    double x = 2;
    double result = x;
    do
    {
        x = result;
        result = x - (x * x - 2) / (2 * x);

    } while (fabs(result - x) > epsilon);
    return result;
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
        sum += 1 / factorial;

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
double ln2_row(double epsilon)
{
    int n = 1;
    double numerator = 1;
    double sum = numerator / n;
    double result = sum;
    double fraction;
    do
    {
        n++;
        numerator *= -1;
        result = sum;
        fraction = numerator / n;
        sum += fraction;
    } while (fabs(result - sum) > epsilon);
    return result;
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
double sqrt2_row(double epsilon)
{
    double comp = 1;
    double result = comp;
    double degree = pow(2, 0.25);
    do
    {
        result = comp;
        comp *= degree;
        degree = pow(degree, 0.5);

    } while (fabs(result - comp) > epsilon);
    return result;
}
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
int is_prime(int t)
{
    if (t <= 0)
    {
        return -1;
    }
    if (t == 2)
    {
        return 1;
    }
    if (!(t & 1))
    {
        return 0;
    }
    for (int i = 3; i <= (int)sqrt(t); i += 2)
    {
        if (t % i == 0)
        {
            return 0;
        }
    }
    return 1;
}
bool isPrime(int t)
{
    if (t <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= t; i++)
    {
        if (t % i == 0)
        {
            return false;
        }
    }
    return true;
}
double gam_equat(double epsilon)
{
    int t = 2;
    double p = 0.5;
    double lim = -log(p * log(2)); //t=2
    double result = lim;
    do
    {
        t++;
        result = lim;
        if (is_prime(t))
        {
            p *= (t - 1.0) / t;
        }
        lim = -log(p * log(t));
    } while (fabsl(result - lim) >= epsilon);
    return result;
}
double gam_row(double epsilon)
{
    double k = 2;
    double pi = pi_row(epsilon);
    double summand = pi * pi / 6;
    double sum = (1.0 / pow(floor(sqrt(k)), 2)) - (1.0 / k);
    double result = sum;
    double staples;
    double sqrtk;
    do
    {
        k++;
        result = sum;
        staples = (1.0 / pow(floor(sqrt(k)), 2)) - (1.0 / k);
        sum += staples;
        sqrtk = sqrt(k);

    } while ((sqrtk * sqrtk == k) || fabs(result - sum) > epsilon);
    return result - summand;
}