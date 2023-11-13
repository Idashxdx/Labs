#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#define MAX_A 65536

// натуральное число?
enum check_natural
{
    natural_number,
    not_natural_number
};
enum check_natural natural_or_not(const int value)
{
    if (value >= 1)
    {
        return natural_number;
    }
    return not_natural_number;
}
// простое или составное?
enum check_simple_or_composite
{
    simple_number,
    composite_number
};
enum check_simple_or_composite simple_or_composite(const int value)
{
    if (value <= 1)
    {
        return composite_number;
    }
    for (int i = 2; i * i <= value; i++)
    {
        if (value % i == 0)
        {
            return composite_number;
        }
    }
    return simple_number;
}
// проверка входного значения
enum check_input_data
{
    data_overflow,
    correct_data,
    incorrect_data,
};
// 2.Не привышает максимальное инта?
enum check_input_data overflow_or_not(const int value)
{
    if (value >= INT_MAX)
    {
        return data_overflow;
    }
    return correct_data;
}
// 1.Это число?
enum check_input_data correct_number(const char *str, int *value)
{
    char *endptr;
    *value = strtoll(str, &endptr, 10);
    if (*str != '\0' && *endptr == '\0')
    {
        return overflow_or_not(*value);
    }
    value = NULL;
    return incorrect_data;
}
//-h (вывести от 1 до 100 кратные указанному
void print_multiples(const int number)
{
    switch (natural_or_not(number)) // натуральное?
    {
    case not_natural_number:
        printf("The number is not natural\n");
        break;
    case natural_number:
        for (int i = number; i <= 100; i += number)
        {
            printf("%d  ", i);
        }
        printf("\n");
        break;
    }
}
//-p  простое или составное
void print_simple_or_composite(const int number)
{
    switch (natural_or_not(number)) // натуральное?
    {
    case not_natural_number:
        printf("The number is not natural\n");
        break;
    case natural_number:
        switch (simple_or_composite(number)) // финал
        {
        case composite_number:
            printf("The number %d is composite\n", number);
            break;
        case simple_number:
            printf("The number %d is simple\n", number);
            break;
        }
        break;
    }
}
//-s  разделить на цифры
void separation_number(const char *number)
{
    int number_of_digits = strlen(number);
    if (number_of_digits == 1)
    {
        printf("%s\n", number);
        return;
    }
    int last_digit = number_of_digits - 1;
    while (last_digit >= 0 && number[last_digit] == '0')
    {
        last_digit--;
    }
    for (int i = 0; i <= last_digit; i++)
    {
        printf("%c", number[i]);
        if (i != last_digit)
        {
            printf(" ");
        }
    }
    printf("\n");
}
//-e  степени
void print_table(const int number)
{
    if (number >= 1 && number <= 10)
    {
        for (int i = 1; i <= 10; i++)
        {
            int result = i;
            printf("\n %d:  \t ", i);
            for (int j = 1; j <= number; j++)
            {
                printf("%d; ", result);
                result *= i;
            }
        }
        printf("\n");
    }
    else
    {
        printf("LIMIT: the number from 1 to 10\n");
        return;
    }
}
//-a  сумма чисел от 1 до указанного (указанное максимальное-65536(дальше overflow))
//(2 + (n - 1)) * (n / 2)
void print_sum(int number)
{
    int left_acton = 2 + number - 1;
    int right_acton = number / 2;
    int sum;
    switch (natural_or_not(number))
    {
    case natural_number:
        if (number > MAX_A)
        {
            printf("OVERFLOW\n");
        }
        else
        {
            sum = left_acton * right_acton;
            printf("Sum of natural numbers from 1 to %d is %d \n", number, sum);
        }
        break;
    case not_natural_number:
        printf("Number not natural \n");
        break;
    }
}
//-f  факториал(максимум 12(дальше overflow))
void print_factorial(int number)
{
    int factorial;
    switch (natural_or_not(number))
    {
    case natural_number:
        if (number > 13)
        {
            printf("OVERFLOW\n");
        }
        else if (number == 0 || number == 1)
        {
            factorial = 1;
        }
        else
        {
            factorial = 1;
            for (int i = 2; i <= number; i++)
            {
                factorial *= i;
            }
            printf("Factorial %d = %d \n", number, factorial);
        }
        break;
    case not_natural_number:
        printf("Number not natural \n");
        break;
    }
}
void print_info()
{
    printf("Actions:\n");
    printf("-h:output natural numbers up to 100, multiples of the specified.\n");
    printf("-p:definition of a simple or composite number.\n");
    printf("-s:Divide a number into digits.\n");
    printf("-e:Output a table of degrees.\n");
    printf("-a:calculate the sum of natural numbers.\n");
    printf("-f:calculate the factorial.\n");
}

#endif
