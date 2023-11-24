#include "action.h"
//%Ro
char *in_roman_numerals(int number)
{

    int position = 0;
    const int regular_numbers[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *roman_numerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    char *roman = malloc(sizeof(char) * 16);
    if (roman == NULL)
    {
        return NULL;
    }
    while (number > 0)
    {
        if (number >= regular_numbers[position])
        {
            strcat(roman, roman_numerals[position]);
            number -= regular_numbers[position];
        }
        else
        {
            position++;
        }
    }
    return roman;
}
//%zr
char *Zeckendorf_representation(unsigned int number)
{
    // (0,1,1,2,3,5 ... --> position = position-1+position-2)
    // для коэф. фибоначи
    // выделяем память
    unsigned int size = 16;
    unsigned int *fibonacci = (unsigned int *)malloc(sizeof(unsigned int) * size);
    if (fibonacci == NULL)
    {
        return NULL;
    }
    // вычисляем коэф.
    fibonacci[0] = 0;
    fibonacci[1] = 1;
    int position = 1;
    while (fibonacci[position] < number)
    {
        position++;
        if (position >= size) // если выделенной памяти не хватаем-->увеличим в двое
        {
            unsigned int *tmp = (unsigned int *)realloc(fibonacci, sizeof(unsigned int) * size * 2);
            if (tmp == NULL)
            {
                free(fibonacci);
                return NULL;
            }
            fibonacci = tmp;
            size *= 2;
        }
        fibonacci[position] = fibonacci[position - 1] + fibonacci[position - 2];
    }
    //+3 для коэф и доп 1 в конце
    char *zeckendorf = (char *)malloc(sizeof(char) * (position + 3));
    if (zeckendorf == NULL)
    {
        free(fibonacci);
        return NULL;
    }
    for (int i = 0; i <= position; i++)
    {
        if (fibonacci[i] == 0)
        {
            zeckendorf[i] = '1';
        }
        else
        {
            zeckendorf[i] = '0';
        }
    }
    if (zeckendorf[position - 1] == '0')
    {
        // Если  - 0, заменяем на 1
        zeckendorf[position - 1] = '1';
        zeckendorf[position] = '\0';
    }
    else
    {
        zeckendorf[position] = '1';
        zeckendorf[position + 1] = '\0';
    }
    free(fibonacci);
    return zeckendorf;
}
// %Cv
char *representation_at_base(int number, int base)
{

    int size = 0;
    int minus = 0;
    if (number < 0)
    {
        minus = 1;
        size++;
    }
    number = abs(number);
    // ищем размер числа
    if (number == 0)
    {
        size = 2;
    }
    else
    {
        size += log(number) / log(base) + 1;
    }
    char *result = (char *)malloc(sizeof(char) * (size + 1));
    if (result == NULL)
    {
        return NULL;
    }
    if (number == 0)
    {
        result[0] = '0';
        result[1] = '\0';
        return result;
    }
    int position = size - 1;
    if (minus == 1)
    {
        result[0] = '-';
    }
    while (number > 0)
    {
        int digit = number % base;
        if (digit < 10)
        {
            result[position--] = digit + '0';
        }
        else
        {
            result[position--] = digit - 10 + 'A';
        }
        number /= base;
    }
    result[size] = '\0';

    return result;
}
//%to
char *conversion_to_decimal(char *number, int base)
{

    int decimal = 0;
    int digit;
    for (int i = 0; number[i] != '\0'; i++)
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
    // Вычисляем размер
    int size = snprintf(NULL, 0, "%d", decimal);
    char *result = (char *)malloc(sizeof(char) * (size + 1));
    if (result == NULL)
    {
        return NULL; // Обработка ошибки выделения памяти
    }
    snprintf(result, size + 1, "%d", decimal);
    return result;
}
int overfprintf(FILE *file, const char *flag, ...)
{
    va_list args;
    va_start(args, flag);
    while (*flag != '\0')
    {
        // План: ищем %, идем к следующим символам--->находим полный флаг
        // присваиваем va_arg числу, далее вызываем функцию обработки,
        // печатаем ответ в файл, переходим к следующему симвлду (ищем следующий флаг)
        if (*flag == '%')
        {
            flag++;
            //%Ro
            if (*flag == 'R' && *(flag + 1) == 'o')
            {
                int input = va_arg(args, int);
                if (input > 3999 || input < 1)
                {
                    fprintf(file, "incorrect data");
                }
                char *roman = in_roman_numerals(input);
                if (roman == NULL)
                {
                    fprintf(file, "error memory malloc");
                }
                else
                {
                    fprintf(file, "%s", roman);
                }

                flag++;
            }
            //%Zr
            else if (*flag == 'Z' && *(flag + 1) == 'r')
            {
                unsigned int input = va_arg(args, unsigned int);
                char *zeckendorf = Zeckendorf_representation(input);
                if (zeckendorf == NULL)
                {
                    fprintf(file, "error memory malloc");
                }
                else
                {
                    fprintf(file, "%s", zeckendorf);
                }
                flag++;
            }
            //%Cv
            else if (*flag == 'C' && *(flag + 1) == 'v')
            {
                int input = va_arg(args, int);
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                {
                    base = 10;
                }
                char *representation = representation_at_base(input, base);
                if (representation == NULL)
                {
                    fprintf(file, "error memory malloc");
                }
                else
                {
                    for (int i = 0; representation[i]; i++)
                    {
                        representation[i] = tolower(representation[i]); // Приводим символы к нижнему регистру
                    }
                    fprintf(file, "%s", representation);
                }
                flag++;
            }
            //%CV
            else if (*flag == 'C' && *(flag + 1) == 'V')
            {
                int input = va_arg(args, int);
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                {
                    base = 10;
                }
                char *representation = representation_at_base(input, base);
                if (representation == NULL)
                {
                    fprintf(file, "error memory malloc");
                }
                else
                {
                    fprintf(file, "%s", representation);
                }
                flag++;
            }
            //%to
            else if (*flag == 't' && *(flag + 1) == 'o')
            {
                char *input = va_arg(args, char *);
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                {
                    base = 10;
                }
                if (input == NULL)
                {
                    fprintf(file, "incorrect data");
                }
                //написать проверку на нижний регистр!!!!!!!!!!!!!!!!!
                char *decimal = conversion_to_decimal(input, base);
                if (decimal == NULL)
                {
                    fprintf(file, "error memory malloc");
                }
                else
                {
                    fprintf(file, "%s", decimal);
                }

                flag++;
            }
        }
        else
        {
            fputc(*flag, file);
        }
        flag++;
    }

    va_end(args);
}