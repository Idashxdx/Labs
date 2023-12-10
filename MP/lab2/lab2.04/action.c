#include "action.h"
// va_list a-va_start(a,b)b-к-во,va_arg(a,type),va_end(a)
check_data check_convex(bool *convex, int count, ...)
{
    if (count < 3)
    {
        return incorrect_data;
    }
    va_list args;
    va_start(args, count);
    // два вектора-три точки, обозначаем точки, ищем вектора, ищем ВП
    Point one = va_arg(args, Point);
    Point two = va_arg(args, Point);
    Point three = va_arg(args, Point);
    double cross_product = (two.x - one.x) * (three.y - one.y) - (three.x - one.x) * (two.y - one.y);
    bool is_collinear = (cross_product == 0); // добавим проверку на коллинеарность

    if (is_collinear) // если точки коллинеарны, значит многоугольник невыпуклый
    {
        va_end(args);
        *convex = false;
        return correct_data;
    }
    Point vector_1;
    Point vector_2;
    int first_product = 0;
    for (int i = 3; i <= count; i++)
    {
        vector_1.x = two.x - one.x;
        vector_1.y = two.y - one.y;
        vector_2.x = three.x - two.x;
        vector_2.y = three.y - two.y;
        double vector_product = vector_1.x * vector_2.y - vector_1.y * vector_2.x;
        if (vector_product != 0) // если равно --> ||
        {
            if (first_product == 0)
            {
                if (vector_product > 0)
                {
                    first_product = 1;
                }
                else
                {
                    first_product = -1;
                }
            }
            else if ((first_product == 1 && vector_product < 0) ||
                     (first_product == -1 && vector_product > 0))
            {
                va_end(args);
                *convex = false;
                return correct_data;
            }
            one = two;
            two = three;
            three = va_arg(args, Point);
        }
    }
    va_end(args);
    return correct_data;
}

check_data calculating_polynomial(double *result, double point, int degree, ...)
{
    if (degree < 0)
    {
        return incorrect_data;
    }
    va_list args;
    va_start(args, degree);
    *result = va_arg(args, double);
    for (int i = 0; i < degree; i++)
    {
        *result *= point;
        *result += va_arg(args, double);
    }
    va_end(args);
    return correct_data;
}
