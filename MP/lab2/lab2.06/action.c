#include "action.h"
int conversion(char symbol, struct Roman numerals[])
{
    int position = 0;
    for (; position < 7; position++)
    {
        if (numerals[position].symbol == symbol)
        {
            return numerals[position].value;
        }
    }
    return 0;
}
int number_to_roman(char *roman, struct Roman numerals[])
{
    int result = 0;
    int current;
    int next;
    int position = 0;
    for (; roman[position] != '\0'; position++)
    {
        current = conversion(roman[position], numerals);
        next = conversion(roman[position + 1], numerals);
        if (current >= next)
        {
            result += current;
        }
        else
        {
            result += (next - current);
            position++;
        }
    }
    return result;
}
unsigned int zeckendorf_to_number(char *zeckendorf)
{
    unsigned int result = 0;
    unsigned int fib[100] = {0, 1};
    int position = 2;

    while (zeckendorf[position - 2] != '\0')
    {
        fib[position] = fib[position - 1] + fib[position - 2];
        position++;
    }

    for (int i = position - 2; i >= 0; i--)
    {
        if (zeckendorf[i] == '1')
        {
            result += fib[i];
        }
    }
    return result;
}
int cv_base_lower(char *input, int base)
{
    int output;
    int result = 0;
    int sign = 1;
    int position = 0;
    if (input[0] == '-')
    {
        sign = -1;
        position = 1;
    }
    for (; input[position] != '\0'; position++)
    {
        result *= base;
        char symbol = tolower(input[position]);
        if (isdigit(symbol))
        {
            result += symbol - '0';
        }
        else if (symbol >= 'a' && symbol <= 'z')
        {
            result += symbol - 'a' + 10;
        }
    }
    return output = result * sign;
}
unsigned int cv_base_upper(char *input, int base)
{
    int output;
    int result = 0;
    int sign = 1;
    int position = 0;
    if (input[0] == '-')
    {
        sign = -1;
        position = 1;
    }
    for (; input[position] != '\0'; position++)
    {
        result *= base;

        char symbol = toupper(input[position]);
        if (isdigit(symbol))
        {
            result += symbol - '0';
        }
        else if (symbol >= 'A' && symbol <= 'Z')
        {
            result += symbol - 'A' + 10;
        }
    }
    return output = result * sign;
}
int overfscanf(FILE *file, const char *format, ...)
{
    va_list arg;
    va_start(arg, format);

    int result = 0;
    struct Roman numerals[] = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}};

    const char *ptr;
    for (ptr = format; *ptr; ptr++)
    {
        if (*ptr == '%' && *(ptr + 1) == 'R' && *(ptr + 2) == 'o')
        {
            char roman[50];
            fscanf(file, "%s", roman);
            int decimal = number_to_roman(roman, numerals);
            int *input = va_arg(arg, int *);
            *input = decimal;
            ptr += 2;
            result++;
        }

        else if (*ptr == '%' && *(ptr + 1) == 'Z' && *(ptr + 2) == 'r')
        {
            char zeckendorf[50];
            fscanf(file, "%s", zeckendorf);
            unsigned int zeckendorf_number = zeckendorf_to_number(zeckendorf);
            unsigned int *input = va_arg(arg, unsigned int *);
            *input = zeckendorf_number;
            ptr += 2;
            result++;
        }
        else if (*ptr == '%' && *(ptr + 1) == 'C' && *(ptr + 2) == 'v')
        {
            char input[50];
            fscanf(file, "%s", input);
            int *number = va_arg(arg, int *);
            int base = va_arg(arg, int);
            if (base < 2 || base > 36)
            {
                base = 10;
            }
            *number = cv_base_lower(input, base);
            result++;
            ptr += 2;
        }
        else if (*ptr == '%' && *(ptr + 1) == 'C' && *(ptr + 2) == 'V')
        {
            char input[50];
            fscanf(file, "%s", input);
            unsigned int *number = va_arg(arg, unsigned int *);
            int base = va_arg(arg, int);
            if (base < 2 || base > 36)
            {
                base = 10;
            }
            *number = cv_base_upper(input, base);
            result++;
            ptr += 2;
        }
    }

    va_end(arg);
    return result;
}
int oversscanf(const char *str, const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    int result = 0;
    struct Roman numerals[] = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}};
    const char *ptr;
    const char *str_ptr = str;
    for (ptr = format; *ptr; ptr++)
    {
        if (*ptr == '%' && *(ptr + 1) == 'R' && *(ptr + 2) == 'o')
        {
            char roman[50];
            sscanf(str_ptr, "%s", roman);
            int decimal = number_to_roman(roman, numerals);
            int *input = va_arg(arg, int *);
            *input = decimal;
            ptr += 2;
            result++;
            while (*str_ptr && *str_ptr && *str_ptr != ' ')
            {
                str_ptr++;
            }
            while (*str_ptr && *str_ptr == ' ')
            {
                str_ptr++;
            }
        }
        else if (*ptr == '%' && *(ptr + 1) == 'Z' && *(ptr + 2) == 'r')
        {
            char zeckendorf[50];
            unsigned int zeckendorf_number = zeckendorf_to_number(zeckendorf);
            unsigned int *input = va_arg(arg, unsigned int *);
            *input = zeckendorf_number;
            ptr += 2;
            result++;
            while (*str_ptr && *str_ptr && *str_ptr != ' ')
            {
                str_ptr++;
            }
            while (*str_ptr && *str_ptr == ' ')
            {
                str_ptr++;
            }
        }
        else if (*ptr == '%' && *(ptr + 1) == 'C' && *(ptr + 2) == 'v')
        {
            char input2[50];
            sscanf(str_ptr, "%s", input2);
            int *number = va_arg(arg, int *);
            int base = va_arg(arg, int);
            if (base < 2 || base > 36)
            {
                base = 10;
            }
            *number = cv_base_lower(input2, base);
            result++;
            ptr += 2;
            while (*str_ptr && *str_ptr && *str_ptr != ' ')
            {
                str_ptr++;
            }
            while (*str_ptr && *str_ptr == ' ')
            {
                str_ptr++;
            }
        }
        else if (*ptr == '%' && *(ptr + 1) == 'C' && *(ptr + 2) == 'V')
        {
            char input2[50];
            sscanf(str_ptr, "%s", input2);
            unsigned int *number = va_arg(arg, unsigned int *);
            int base = va_arg(arg, int);
            if (base < 2 || base > 36)
            {
                base = 10;
            }
            *number = cv_base_upper(input2, base);
            result++;
            ptr += 2;
            while (*str_ptr && *str_ptr && *str_ptr != ' ')
            {
                str_ptr++;
            }
            while (*str_ptr && *str_ptr == ' ')
            {
                str_ptr++;
            }
        }
        else if (*format == '%')
        {
           
        }
    }
    va_end(arg);
    return result;
}
