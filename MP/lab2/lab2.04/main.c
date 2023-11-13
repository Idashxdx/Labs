#include "action.h"

int main(int argc, char *argv[])
{
    // 1. Функция с переменным числом аргументов, принимающую координаты
    // вершин многоугольника и определяющая, является ли этот многоугольник выпуклым
    int count = 6;
    Point point_1 = {1.0, 2.0};
    Point point_2 = {-1.0, 1.0};
    Point point_3 = {-1.0, -0.5};
    Point point_4 = {1.0, -2.5};
    Point point_5 = {3.0, -0.5};
    Point point_6 = {3.0, 1.0};
    // 5 точек выше --> 100% выпуклый-гексагон
    //-->невыпуклый --> point_5 {3.0, -0.5} заменить на  {1.0, 1.0}
    bool convex = true;
    switch (check_convex(&convex, count, point_1, point_2, point_3, point_4, point_5, point_6))
    {
    case correct_data:
        if (convex)
        {
            printf("1. Checking for convexity ---> CONVEX\n\n");
        }
        else
        {
            printf("1. Checking for convexity ---> NONCONVEX\n\n");
        }
        break;
    case incorrect_data:
        printf("1. Calculation error\n");
        break;
    }

    // 2. Функция нахождения значение многочлена степени n в заданной точке.
    // Входными параметрами являются точка(double), в которой определяется значение многочлена
    // степень многочлена (int), и его коэффициенты (double).
    double point = 2.0;
    int degree = 2;
    double coef_1 = 3.0;
    double coef_2 = 4.0;
    double coef_3 = 5.0;
    double result;
    switch (calculating_polynomial(&result, point, degree, coef_1, coef_2, coef_3))
    {
    case correct_data:
        printf("2.Polynomial with degree %d at a point %lf with coefs:%lf %lf %lf  ---> %lf\n\n", degree, point, coef_1, coef_2, coef_3, result);
        break;
    case incorrect_data:
        printf("2. Calculation error\n");
        break;
    }
    printf("\n\nM8O-211B-22  Mashrabova  lab2 tack4\n");
    return 0;
}
