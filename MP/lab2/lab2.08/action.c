#include "action.h"

bool check_number(char *str, int base)
{
    int lenght = strlen(str);

    if (!lenght)
    {
        return false;
    }

    for (int i = 0; i < lenght; ++i)
    {
        if (!isalpha(str[i]) && !isdigit(str[i]))
        {
            return false;
        }

        else if (isalpha(str[i]))
        {
            if (toupper(str[i]) - 55 >= base)
            {
                return false;
            }
        }
        else if (isdigit(str[i]))
        {
            if (str[i] - '0' >= base)
            {
                return false;
            }
        }
    }
    return true;
}

char *sum_of_two_numbers(char *a, char *b, int base)
{
    int len_a = 0;
    while (a[len_a] != '\0') {
        len_a++;
    }
    int len_b = 0;
    while (b[len_b] != '\0') {
        len_b++;
    }
    int max_len = (len_a > len_b) ? len_a : len_b;
    char* result = (char*)malloc((max_len + 2) * sizeof(char));
    int carry = 0;
    int i = 0;
    while (len_a > 0 || len_b > 0 || carry > 0) {
        int sum = carry;
        if (len_a > 0) {
            sum += a[--len_a] - '0';
        }
        if (len_b > 0) {
            sum += b[--len_b] - '0';
        }
        result[max_len - i] = (sum % base) + '0';
        carry = sum / base;
        i++;
    }
    result[max_len + 1] = '\0';
    return &result[max_len - i + 1];
}
check_data sum(char **result, int base, int count, ...)
{
    if (base < 2 || base > 36 || count < 0)
    {
        return incorrect_data;
    }
    va_list args;
    va_start(args, count);
    char *tmp;
    (*result) = (char *)malloc(2 * sizeof(char));

    if (*result == NULL)
    {
        return malloc_memory_error;
    }
    *result = va_arg(args, char *);
     if (!check_number(*result, base))
        {
            va_end(args);
            free(*result);
            return incorrect_data;
        }
    // проверка числа
    for (int i = 0; i < count; i++)
    {
        char *number = va_arg(args, char *);
        if (!check_number(number, base))
        {
            va_end(args);
            free(*result);
            return incorrect_data;
        }
        tmp = sum_of_two_numbers(*result, number, base);
        if (tmp == NULL)
        {
            va_end(args);
            free(*result);
            return malloc_memory_error;
        }
        free(*result);
        *result = tmp;
    }
    va_end(args);
    return correct_data;
}
