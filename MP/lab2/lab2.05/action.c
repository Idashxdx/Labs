#include "action.h"
//%Ro
char *in_roman_numerals(int number)
{
    int position = 0;
    const int regular_numbers[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char *roman_numerals[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    char *roman = (char *)malloc(sizeof(char) * 16);
    if (roman == NULL)
    {
        return NULL;
    }
    roman[0] = '\0';
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
        return NULL;
    }
    snprintf(result, size + 1, "%d", decimal);

    return result;
}
//%m... - план - извлекаем каждый бит - преобразуем бит в 0 или 1- записываем в результат добавляем пробел и переходим к следующему байту
char *memory_dump_int(int number, int size)
{
    size_t binary_size = size * 8 + size;
    char *result = (char *)malloc(sizeof(char) * (binary_size + 1));
    if (result == NULL)
    {
        return NULL;
    }

    char *byte = (char *)&number; // указатель на байт

    int position = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            char bit = ((*byte) >> j) & 1;
            result[position] = '0' + bit; // Чтобы получить символ '0' или '1'
            position++;
        }
        result[position] = ' ';
        position++;
        byte++;
    }
    result[position] = '\0';

    return result;
}
char *memory_dump_unsigned(unsigned int number, int size)
{
    size_t binary_size = size * 8 + size;
    char *result = (char *)malloc(sizeof(char) * (binary_size + 1)); // +1 для завершающего нуля
    if (result == NULL)
    {
        return NULL;
    }

    int position = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            char bit = (number >> j) & 1;
            result[position] = '0' + bit;
            position++;
        }
        result[position] = ' ';
        position++;
        number = number >> 8;
    }
    result[position] = '\0';

    return result;
}
char *memory_dump_double(double number, int size)
{
    unsigned char *bytePtr = (unsigned char *)&number;
    size_t binary_size = size * 8 + size;
    char *result = (char *)malloc(sizeof(char) * (binary_size + 1));
    if (result == NULL)
    {
        return NULL;
    }

    int position = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            char bit = (bytePtr[i] >> j) & 1;
            result[position] = '0' + bit; // Чтобы получить символ '0' или '1'
            position++;
        }
        result[position] = ' ';
        position++;
    }
    result[position] = '\0';
    return result;
}
char *memory_dump_float(float number, int size)
{
    unsigned char *bytePtr = (unsigned char *)&number;
    size_t binary_size = size * 8 + size;
    char *result = (char *)malloc(sizeof(char) * (binary_size + 1)); // +1 для завершающего нуля
    if (result == NULL)
    {
        return NULL;
    }

    int position = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            char bit = (bytePtr[i] >> j) & 1;
            result[position] = '0' + bit; // Чтобы получить символ '0' или '1'
            position++;
        }
        result[position] = ' ';
        position++;
    }
    result[position] = '\0'; // Добавляем завершающий нуль

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
                    free(roman);
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
                    free(zeckendorf);
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
                    free(representation);
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
                    free(representation);
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
                if (islower(*input))
                {

                    char *decimal = conversion_to_decimal(input, base);
                    if (decimal == NULL)
                    {
                        fprintf(file, "error memory malloc");
                    }
                    else
                    {
                        fprintf(file, "%s", decimal);
                        free(decimal);
                    }
                }
                else
                {
                    fprintf(file, "incorrect data");
                }
                flag++;
            }

            else if (*flag == 'T' && *(flag + 1) == 'O')
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

                if (!islower(*input))
                {

                    char *decimal = conversion_to_decimal(input, base);
                    if (decimal == NULL)
                    {
                        fprintf(file, "error memory malloc");
                    }
                    else
                    {
                        fprintf(file, "%s", decimal);
                        free(decimal);
                    }
                }
                else
                {
                    fprintf(file, "incorrect data");
                }
                flag++;
            }
            //%mi,mu,md,mf
            else if (*flag == 'm' && *(flag + 1) == 'i')
            {
                int input = va_arg(args, int);
                char *result = memory_dump_int(input, sizeof(int));
                if (result == NULL)
                {
                    fprintf(file, "error memory malloc");
                }
                else
                {
                    fprintf(file, "%s", result);
                    free(result);
                }
                flag++;
            }
            else if (*flag == 'm' && *(flag + 1) == 'u')
            {
                unsigned int input = va_arg(args, unsigned int);
                char *result = memory_dump_unsigned(input, sizeof(unsigned int));
                if (result == NULL)
                {
                    fprintf(file, "error memory malloc");
                }
                else
                {
                    fprintf(file, "%s", result);
                    free(result);
                }
                flag++;
            }
            else if (*flag == 'm' && *(flag + 1) == 'f')
            {
                float input = (float)va_arg(args, double);
                char *result = memory_dump_float(input, sizeof(float));
                if (result == NULL)
                {
                    fprintf(file, "error memory malloc");
                }
                else
                {
                    fprintf(file, "%s", result);
                    free(result);
                }
                flag++;
            }
            else if (*flag == 'm' && *(flag + 1) == 'd')
            {
                double input = va_arg(args, double);
                char *result = memory_dump_double(input, sizeof(double));
                if (result == NULL)
                {
                    fprintf(file, "error memory malloc");
                }
                else
                {
                    fprintf(file, "%s", result);
                    free(result);
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
char *oversprintf(char *str, size_t size, const char *flag, ...)
{
    va_list args;
    va_start(args, flag);
    size_t used = 0;

    if (used >= size)
    {
        va_end(args);
        return NULL;
    }

    while (*flag != '\0')
    {
        if (*flag == '%')
        {
            flag++;
            if (*flag == 'R' && *(flag + 1) == 'o')
            {
                int input = va_arg(args, int);
                if (input > 3999 || input < 1)
                {
                    if (used < size - 1)
                    {
                        strncat(str, "incorrect data", size - used - 1);
                        used += strlen("incorrect data");
                    }
                    else
                    {
                        va_end(args);
                        return NULL;
                    }
                }
                else
                {
                    char *roman = in_roman_numerals(input);
                    if (roman == NULL)
                    {
                        if (used < size - 1)
                        {
                            strncat(str, "error memory malloc", size - used - 1);
                            used += strlen("error memory malloc");
                        }
                        else
                        {
                            va_end(args);
                            return NULL;
                        }
                    }
                    else
                    {
                        strncat(str, roman, size - used - 1);
                        used += strlen(roman);
                        free(roman);
                    }
                }
            }
            else if (*flag == 'Z' && *(flag + 1) == 'r')
            {
                unsigned int input = va_arg(args, unsigned int);
                char *zeckendorf = Zeckendorf_representation(input);
                if (zeckendorf == NULL)
                {
                    if (used < size - 1)
                    {
                        strncat(str, "error memory malloc", size - used - 1);
                        used += strlen("error memory malloc");
                    }
                    else
                    {
                        va_end(args);
                        return NULL;
                    }
                }
                else
                {
                    strncat(str, zeckendorf, size - used - 1);
                    used += strlen(zeckendorf);
                    free(zeckendorf);
                }
            }
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
                    if (used < size - 1)
                    {
                        strncat(str, "error memory malloc", size - used - 1);
                        used += strlen("error memory malloc");
                    }
                    else
                    {
                        va_end(args);
                        return NULL;
                    }
                }
                else
                {
                    for (int i = 0; representation[i]; i++)
                    {
                        representation[i] = tolower(representation[i]); // Приводим символы к нижнему регистру
                    }
                    strncat(str, representation, size - used - 1);
                    used += strlen(representation);
                    free(representation);
                }
            }
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
                    if (used < size - 1)
                    {
                        strncat(str, "error memory malloc", size - used - 1);
                        used += strlen("error memory malloc");
                    }
                    else
                    {
                        va_end(args);
                        return NULL;
                    }
                }
                else
                {
                    strncat(str, representation, size - used - 1);
                    used += strlen(representation);
                    free(representation);
                }
            }
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
                    if (used < size - 1)
                    {
                        strncat(str, "incorrect data", size - used - 1);
                        used += strlen("incorrect data");
                    }
                    else
                    {
                        va_end(args);
                        return NULL;
                    }
                }

                if (islower(*input))
                {
                    char *decimal = conversion_to_decimal(input, base);
                    if (decimal == NULL)
                    {
                        if (used < size - 1)
                        {
                            strncat(str, "error memory malloc", size - used - 1);
                            used += strlen("error memory malloc");
                        }
                        else
                        {
                            va_end(args);
                            return NULL;
                        }
                    }
                    else
                    {
                        strncat(str, decimal, size - used - 1);
                        used += strlen(decimal);
                        free(decimal);
                    }
                }

                else
                {
                    if (used < size - 1)
                    {
                        strncat(str, "incorrect data", size - used - 1);
                        used += strlen("incorrect data");
                    }
                    else
                    {
                        va_end(args);
                        return NULL;
                    }
                }
            }
            else if (*flag == 'T' && *(flag + 1) == 'O')
            {
                char *input = va_arg(args, char *);
                int base = va_arg(args, int);
                if (base < 2 || base > 36)
                {
                    base = 10;
                }
                if (input == NULL)
                {
                    if (used < size - 1)
                    {
                        strncat(str, "incorrect data", size - used - 1);
                        used += strlen("incorrect data");
                    }
                    else
                    {
                        va_end(args);
                        return NULL;
                    }
                }

                if (!islower(*input))
                {
                    char *decimal = conversion_to_decimal(input, base);
                    if (decimal == NULL)
                    {
                        if (used < size - 1)
                        {
                            strncat(str, "error memory malloc", size - used - 1);
                            used += strlen("error memory malloc");
                        }
                        else
                        {
                            va_end(args);
                            return NULL;
                        }
                    }
                    else
                    {
                        strncat(str, decimal, size - used - 1);
                        used += strlen(decimal);
                        free(decimal);
                    }
                }
                else
                {
                    if (used < size - 1)
                    {
                        strncat(str, "incorrect data", size - used - 1);
                        used += strlen("incorrect data");
                    }
                    else
                    {
                        va_end(args);
                        return NULL;
                    }
                }
            }
            else if (*flag == 'm' && *(flag + 1) == 'i')
            {
                int input = va_arg(args, int);
                char *result = memory_dump_int(input, sizeof(int));
                if (result == NULL)
                {
                    if (used < size - 1)
                    {
                        strncat(str, "error memory malloc", size - used - 1);
                        used += strlen("error memory malloc");
                    }
                    else
                    {
                        va_end(args);
                        return NULL;
                    }
                }
                else
                {
                    strncat(str, result, size - used - 1);
                    used += strlen(result);
                    free(result);
                }
            }
            else if (*flag == 'm' && *(flag + 1) == 'u')
            {
                unsigned int input = va_arg(args, unsigned int);
                char *result = memory_dump_unsigned(input, sizeof(unsigned int));
                if (result == NULL)
                {
                    if (used < size - 1)
                    {
                        strncat(str, "error memory malloc", size - used - 1);
                        used += strlen("error memory malloc");
                    }
                    else
                    {
                        va_end(args);
                        return NULL;
                    }
                }
                else
                {
                    strncat(str, result, size - used - 1);
                    used += strlen(result);
                    free(result);
                }
            }
            else if (*flag == 'm' && *(flag + 1) == 'f')
            {
                float input = (float)va_arg(args, double);
                char *result = memory_dump_float(input, sizeof(float));
                if (result == NULL)
                {
                    if (used < size - 1)
                    {
                        strncat(str, "error memory malloc", size - used - 1);
                        used += strlen("error memory malloc");
                    }
                    else
                    {
                        va_end(args);
                        return NULL;
                    }
                }
                else
                {
                    strncat(str, result, size - used - 1);
                    used += strlen(result);
                    free(result);
                }
            }
            else if (*flag == 'm' && *(flag + 1) == 'd')
            {
                double input = va_arg(args, double);
                char *result = memory_dump_double(input, sizeof(double));
                if (result == NULL)
                {
                    if (used < size - 1)
                    {
                        strncat(str, "error memory malloc", size - used - 1);
                        used += strlen("error memory malloc");
                    }
                    else
                    {
                        va_end(args);
                        return NULL;
                    }
                }
                else
                {
                    strncat(str, result, size - used - 1);
                    used += strlen(result);
                    free(result);
                }
            }

            flag += 2;
        }
        else
        {
            if (used < size - 1)
            {
                str[used] = *flag;
                str[used + 1] = '\0';
                used++;
            }
            else
            {
                va_end(args);
                return NULL;
            }
            flag++;
        }
    }
    va_end(args);
    return str;
}