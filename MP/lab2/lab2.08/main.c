#include "action.h"

int main(int argc, char *argv[])
{
    // Функция с пер. числом арг., вычисляющую сумму переданных целых неотриц. чисел
    // в заданной сс с основанием [2..36]. Параметрами функции являются основание сс,
    // количество переданных чисел, строковые представления чисел в заданной сс.
    // также реализуйте функцию «сложения в столбик» двух чисел в заданной сс.
    char *result = NULL;
    switch (sum(&result, 8, 3, "71", "23", "11")) // основание-количество-числа
    {
    case correct_data:
        printf("Result ---> %s\n", result);
        break;
    case incorrect_data:
        printf("Calculation error\n");
        break;
    case malloc_memory_error:
        printf("memory malloc error\n");
        break;
    }
    if (result != NULL)
    {
        free(result);
    }

    printf("\n\nM8O-211B-22  Mashrabova  lab2 tack8\n");
    return 0;
}