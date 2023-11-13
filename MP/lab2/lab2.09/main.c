#include "action.h"

int main(int argc, char *argv[])
{
    // Функция с пер. числом арг., определяющую для каждой из переданных десятичных дробей
    // (в виде значения вещественного типа в диапазоне (0; 1)), имеет ли она в сс с переданным
    // как параметр функции основанием конечное представление.
    //--->1/base=number?y/n
    int base;
    printf("Enter base:");
    if (!scanf("%d", &base))
    {
        printf("Error1\n");
        return 1;
    }
    if (base < 1 && base > 36)
    {
        printf("Error2\n");
        return 1;
    }
    bool *result;
    double *numbers;
    int count = 4;
    // for base=5 --> n1,n2,n4
    switch (check_finite(&result, &numbers, base, count, 0.2, 0.04, 0.125, 0.00000256))
    {
    case correct_data:
        for (int i = 0; i < count; i++)
        {
            printf("%d. %0.9lf;  ",i+1, numbers[i]);
        }
        printf("FINITE?:\n");
        for (int i = 0; i < count; i++)
        {
            if (result[i])
            {
                printf("%d.YES   ", i + 1);
            }
            else
            {
                printf("%d.NO   ", i + 1);
            }
        }
        break;
    case incorrect_data:
        printf("Calculation error\n");
        break;
    case memory_malloc_error:
        printf("Memory mallic error\n");
        break;
    }
    free(result);
    free(numbers);
    printf("\n\nM8O-211B-22  Mashrabova  lab2 tack8\n");
    return 0;
}
