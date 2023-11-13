#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

// проверка
typedef enum check_data
{
    correct_data,
    incorrect_data
} check_data;
//координаты для 1 задачи
typedef struct 
{
    double x;
    double y;
} Point;

check_data check_convex(bool* convex, int count, ...); // 1.
check_data calculating_polynomial(double* result,double point,int degree, ...);
#endif
