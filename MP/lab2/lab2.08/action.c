#include "action.h"

bool check_number(char *input_str, int base)
{
 
}

check_data sum(char **result, int base, int count, ...)
{
    if (base < 2 || base > 36 || count < 0)
    {
        return incorrect_data;
    }
    va_list args;
    va_start(args, const);
    (*result) = (char *)malloc(2 * sizeof(char));
    if (*result == NULL)
    {
        return incorrect_data;
    }
    // проверка числа
    for (int i = 0; i < count; i++)
    {
        char *number = va_arg(args, char *);
        if (!check_number(number, base))
        {
            free(*result);
            return incorrect_data;
        }
    }
}