
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
        char *result = NULL;
        // размер и длина результата
        size_t size = 0;
        size_t length = 0;
        // позиция и строка результата
        int str_number = 1;
        int position_number = 1;
        // пдлина подстроки и текущей
        size_t substring_length = strlen(str);
        size_t current_position = 0;
        while ((symbol = fgetc(file)) != EOF) //читаем по символу из файла
        {
            if (symbol == '\n')
            {
                // следующая строка ---> увеличиваем количество строк, позиция в строке опять 1
                str_number++;
                position_number = 1;
            }
            else
            {
                position_number++;
            }
            // сравниваем символ с подстрокой,
            if (symbol == str[current_position])
            {
                current_position++; 
                if (current_position == substring_length)//длина подстроки = длина вхождения ---> вхождение найдено
                {
                    size_t new_size = size + 256;
                    char *new_result = (char *)realloc(result, new_size);
                    if (new_result == NULL)
                    {
                        free(result);
                        va_end(args);
                        fclose(file);
                        return realloc_memory_error;
                    }
                    result = new_result;
                    size = new_size;
                    int print_resilt = printf("Файл: %s, подстрока: %s, строка: %d, позиция: %ld\n", filename, str, str_number, position_number-substring_length);
                    if (print_resilt >= 0)
                    {
                        length += print_resilt;
                    }
                    current_position = 0;
                     
                }
            }
            else
            {
                current_position = 0;
            }
        }
        fclose(file);
        free(result);
       
    }
    va_end(args);
    return correct_data;
}
