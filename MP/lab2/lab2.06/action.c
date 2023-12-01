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
            i++;
        }
    }
    return result;
}

int overfscanf(FILE *stream, const char *format, ...)
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
            fscanf(stream, "%s", roman);
            int decimal = number_to_roman(roman, numerals);
            int *input = va_arg(arg, int *);
            *input = decimal;
            ptr += 2;
            result++;
        }
    }
    va_end(arg);
    return result;
}
