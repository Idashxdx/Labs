#include "action.h"

int main(int argc, char *argv[])
{
    // Функция с пер. числом арг., вычисляющую сумму переданных целых неотриц. чисел
    // в заданной сс с основанием [2..36]. Параметрами функции являются основание сс,
    // количество переданных чисел, строковые представления чисел в заданной сс.
    // также реализуйте функцию «сложения в столбик» двух чисел в заданной сс.
    char *result;
    
    switch (sum(&result,16,3,"ABC", "A9C", "F000C"))//основание-количество-числа
    {
    case correct_data:

        break;
    case incorrect_data:
        printf("Calculation error\n");
        break;
    case overflow_data:
        printf("Overflow\n");
        break;
    }

    printf("\n\nM8O-211B-22  Mashrabova  lab2 tack8\n");
    return 0;
}