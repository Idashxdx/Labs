#include "action.h"

check_input_data check_base(int base)
{
    if (base < 2 || base > 36)
    {
        return incorrect_data;
    }
    return correct_data;
}
check_input_data check_number(char *number, int base)
{
    int start_position = (*number == '-') ? 1 : 0;
    for (int i = start_position; i < strlen(number); i++)
    {
        if (isdigit(number[i]))
        {
            if (number[i] - '0' >= base)
            {
                return incorrect_data;
            }
        }
        else
        {
            if (toupper(number[i]) - 'A' + 10 >= base)
            {
                return incorrect_data;
            }
        }
    }

    return correct_data;
}
unsigned long long conversion_to_decimal(char *number, int base)
{

    int negative = 1;
    int start_position = 0;

    if (number[0] == '-')
    {
        negative = -1;
        start_position = 1;
    }

    unsigned long long decimal = 0;
    int digit;
    for (int i = start_position; number[i] != '\0'; i++)
    {
        if (isdigit(number[i]))
        {
            digit = number[i] - '0';
        }
        else
        {
            digit = toupper(number[i]) - 'A' + 10;
        }
        decimal = decimal * base + digit;
    }
    return decimal * negative;
}

unsigned long long find_max_number(unsigned long long number_1, unsigned long long number_2)
{
    if (abs(number_1) > abs(number_2))
    {
        return number_1;
    }
    else
    {
        return number_2;
    }
}
void print_delete_zeros(unsigned long long max_number, int base)
{
    if (max_number == 0)
    {
        printf("0\n");
        return;
    }
    char result_abs[100];
    if (max_number < 0)
    {
        printf("-");
        max_number = -max_number;
    }
    int position = 0;
    while (max_number > 0)
    {
        int digit = max_number % base;
        if (digit < 10)
        {
            result_abs[position++] = digit + '0';
        }
        else
        {
            result_abs[position++] = digit - 10 + 'A';
        }
        max_number /= base;
    }
    for (int i = position - 1; i >= 0; i--)
    {
        printf("%c", result_abs[i]);
    }
    printf("\n");
}
void representation_at_base(unsigned long long max_number, int base)
{
    if (max_number == 0)
    {
        printf("\n Представление с основанием %d: 0\n", base);
        return;
    }
    char result[100];
    int position = 0;
    int is_negative = 0;

    if (max_number < 0)
    {
        max_number = -max_number;
        is_negative = 1;
    }

    while (max_number > 0)
    {
        int remainder = max_number % base;
        if (remainder < 10)
        {
            result[position] = remainder + '0';
        }
        else
        {
            result[position] = (remainder - 10) + 'A';
        }
        position++;
        max_number /= base;
    }
    printf("\n Представление с основанием %d: ", base);
    if (is_negative)
    {
        printf("-");
    }

    for (int i = position - 1; i >= 0; i--)
    {
        printf("%c", result[i]);
    }
    printf("\n");
}
