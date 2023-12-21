
#include "action.h"
check_data substring_search(const char *str, int count, ...)
{
    if (count < 1)
    {
        return incorrect_data;
    }

    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++)
    {
        const char *filename = va_arg(args, const char *);
        FILE *file = fopen(filename, "r");
        if (!file)
        {
            va_end(args);
            return incorrect_file;
        }

        int symbol;
        char *result = (char *)malloc(count * sizeof(char));
        if (result == NULL)
        {
            va_end(args);
            fclose(file);
            return malloc_memory_error;
        }

        size_t size = 0;
        size_t length = 0;
        int str_number = 1;
        int position_number = 1;
        size_t substring_length = strlen(str);
        size_t current_position = 0;

        // Замена символа табуляции на 4 пробела в подстроке
        size_t len = strlen(str);
        char *formatted_str = (char *)malloc(len * 4 + 1); // +1 для нулевого символа
        size_t idx = 0;
        for (size_t i = 0; i < len; i++)
        {
            if (str[i] == '\t')
            {
                formatted_str[idx++] = ' '; // заменяем табуляцию четырьмя пробелами
                formatted_str[idx++] = ' ';
                formatted_str[idx++] = ' ';
                formatted_str[idx++] = ' ';
                substring_length +=3;
            }
            else
            {
                formatted_str[idx++] = str[i];
            }
        }
        formatted_str[idx] = '\0';

        while ((symbol = fgetc(file)) != EOF)
        {
            if (formatted_str[current_position] == symbol)
            {
                current_position++;
                if (formatted_str[current_position] == '\0')
                {
                    size_t new_size = size + 256;
                    char *new_result = (char *)realloc(result, new_size);
                    if (new_result == NULL)
                    {
                        free(formatted_str);
                        free(result);
                        va_end(args);
                        fclose(file);
                        return realloc_memory_error;
                    }
                    result = new_result;
                    int print_result = printf("Файл: %s, подстрока: %s, строка: %d, позиция: %ld\n", filename, str, str_number, position_number - substring_length+1);
                    if (print_result >= 0)
                    {
                        length += print_result;
                    }
                    current_position = 0;
                }
            }
            else
            {
                if (formatted_str[0] == symbol)
                {
                    current_position = 1;
                }
                else
                {
                    current_position = 0;
                }
            }
            if (symbol == '\n')
            {
                str_number++;
                position_number = 1;
            }
            else
            {
                position_number++;
            }
        }

        free(formatted_str);
        free(result);
        fclose(file);
    }
    va_end(args);
    return correct_data;
}