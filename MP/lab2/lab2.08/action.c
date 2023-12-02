#include "action.h"
bool check_number(const char *str, int base)
{
    size_t length = strlen(str);

    if (length == 0)
    {
        return false;
    }

    for (size_t i = 0; i < length; ++i)
    {
        if (!isalnum(str[i]))
        {
            return false;
        }

        if (isalpha(str[i]))
        {
            if (toupper(str[i]) - 'A' + 10 >= base)
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

char *sum_of_two_numbers(const char *number1, const char *number2, int base)
{
    size_t length1 = strlen(number1);
    size_t length2 = strlen(number2);
    size_t max_lenght = (length1 > length2) ? length1 : length2;
    char *result = (char *)malloc((max_lenght + 2) * sizeof(char));
    if (result == NULL)
    {
        return NULL;
    }
    // план - значение для переноса, с конца идем к первому, записываем остаток от деления на основание, преобразуем в char
    int carry = 0;
    for (size_t i = 0; i <= max_lenght; i++)
    {
        int sum = carry;
        if (length1 > 0)
        {
            sum += number1[length1 - 1] - '0'; // Преобразуем символ --> значение
            length1--;
        }
        if (length2 > 0)
        {
            sum += number2[length2 - 1] - '0';
            length2--;
        }
        result[max_lenght - i] = (sum % base) + '0';
        carry = sum / base;
    }
    result[max_lenght + 1] = '\0';
    // удаляем ведущие нули если есть
    char *final_result = result;
    while (*final_result == '0' && *(final_result + 1) != '\0')
    {
        final_result++;
    }
    //
    char *copy_final_result = (char *)malloc((strlen(final_result) + 1) * sizeof(char));
    if (copy_final_result == NULL)
    {
        free(result);
        return NULL;
    }
    strcpy(copy_final_result, final_result);
    free(result);
    return copy_final_result;
}
check_data sum(char **result, int base, int count, ...)
{
    if (base < 2 || base > 36 || count < 0)
    {
        return incorrect_data;
    }
    va_list args;
    va_start(args, count);

    const char *tmp = va_arg(args, const char *);
    if (!check_number(tmp, base))
    {
        va_end(args);
        return incorrect_data;
    }

    *result = (char *)malloc((strlen(tmp) + 1) * sizeof(char));
    if (*result == NULL)
    {
        va_end(args);
        return malloc_memory_error;
    }
    strcpy(*result, tmp);

    for (int i = 1; i < count; i++)
    {
        const char *number = va_arg(args, const char *);
        if (!check_number(number, base))
        {
            va_end(args);
            free(*result);
            return incorrect_data;
        }
        char *tmp_result = sum_of_two_numbers(*result, number, base);
        if (tmp_result == NULL)
        {
            va_end(args);
            free(*result);
            return malloc_memory_error;
        }
        free(*result);
        *result = tmp_result;
    }
    va_end(args);
    return correct_data;
}