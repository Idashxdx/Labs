#include "action.h"

int main(int argc, char *argv[])
{
    // 1. Функция с переменными числами аргументов,
    // вычисляющая среднее геометрическое чисел вещественного типа
    double geom_mean;
    switch (geometrical_mean(&geom_mean, 3, 1.0, 2.0, 3.0))
    {
    case correct_data:
        printf("1.Function that calculates the geometric mean of (1.0,2.0,3.0) ---> %f\n\n", geom_mean);
        break;
    case incorrect_data:
        printf("Calculation error\n");
        break;
    case overflow_data:
        printf("Overflow\n");
        break;
    }
    // 2. Рекурсивная функция для возведения вещественного числа в целую степень.
    double num_deg;
    double number;
    int degree;
    printf("2.  Enter a number (double): ");
    if (!scanf("%lf", &number))
    {
        printf("Calculation error\n");
        return 1;
    }
    printf("Enter a degree (int): ");
    if (!scanf("%d", &degree))
    {
        printf("Calculation error\n");
        return 1;
    }
    switch (check_values(&num_deg, number, degree))
    {
    case correct_data:
        printf("\nRaise a number %lf to a degree %d ---> %f\n\n", number, degree, num_deg);
        break;
    case incorrect_data:
        printf("Calculation error\n");
        break;
    case overflow_data:
        printf("Overflow\n");
        break;
    }

    printf("\n\nM8O-211B-22  Mashrabova  lab2 tack2\n");
    return 0;
}
