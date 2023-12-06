#include "action.h"

int main(int argc, char *argv[])
{
    // перевод числа из десятичной cc в cc с основанием 2^r. нельзя станд. арифм. операции

    int number;
    int r;
    char *result;
    printf("Enter a r (r=1...5) (int): ");
    if (!scanf("%d", &r))
    {
        printf("Input error\n");
        return 1;
    }
    if (r < 1 || r > 5)
    {
        printf("Calculation error\n");
        return 1;
    }
    printf("Enter a number to convert (int): ");
    if (!scanf("%d", &number))
    {
        printf("Input error\n");
        return 1;
    }
    switch (truns_number(&result, number, r))
    {
    case correct_data:
        printf("\nDecimal number = %d; transformation in base 2^%d  --->  %s", number, r, result);
        break;
    case incorrect_data:
        printf("Calculation error\n");
        break;
    case memory_malloc_error:
        printf("memory malloc error\n");
        break;
    case memory_realloc_error:
        printf("memory realloc error\n");
        break;
    }

    printf("\n\nM8O-211B-22  Mashrabova  lab3 tack1\n");
    return 0;
}