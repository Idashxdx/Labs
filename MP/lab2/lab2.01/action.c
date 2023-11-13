#include "action.h"

//-l подсчет длины строки
int count_length(char *str)
{
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}
//-r реверс строки
check_data get_string_reversed(char *str, char **str_reverse)
{
    int length;
    length = count_length(str);
    (*str_reverse) = (char *)malloc((length + 1) * sizeof(char)); // выделяем память
    if (*str_reverse == NULL)
    {
        return  memory_allocation_error;
    }
    for (int i = 0, j = length - 1; j >= 0; i++, j--)
    {
        (*str_reverse)[i] = str[j];
    }
    (*str_reverse)[length] = '\0';
    return correct_data;
}
//-u нечетные в верхний регистр
check_data get_string_odd_uppercase(char *str, char **str_uppercase)
{
    int length;
    length = count_length(str);
    (*str_uppercase) = (char *)malloc((length + 1) * sizeof(char));
    if (*str_uppercase == NULL)
    {
        return  memory_allocation_error;
    }
    for (int i = 0; i < length; i++)
    {
        if ((i & 1) && str[i] >= 'a' && str[i] <= 'z')
        {
            (*str_uppercase)[i] = (char)((int)str[i] - 32);
        }
        else
        {
            (*str_uppercase)[i] = str[i];
        }
    }
    (*str_uppercase)[length] = '\0';
    return correct_data;
}
//-n сортировка-->цифры-буквы-символы
check_data get_string_sorted(char *str, char **str_sort)
{
    int length;
    length = count_length(str);
    (*str_sort) = (char *)malloc((length + 1) * sizeof(char));
    if (*str_sort == NULL)
    {
        return  memory_allocation_error;
    }
    int digits = 0;
    int letters = 0;
    int other = 0;
    for (int i = 0; i < length; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            digits++;
        }
        else if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
        {
            letters++;
        }
        else
        {
            other++;
        }
    }
    // sort
    int begin = 0;
    int middle = 0;
    int end = 0;
    for (int i = 0; i < length; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            (*str_sort)[begin] = str[i];
            begin++;
        }
        else if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
        {
            (*str_sort)[digits + middle] = str[i];
            middle++;
        }
        else
        {
            (*str_sort)[digits + letters + end] = str[i];
            end++;
        }
    }
    (*str_sort)[length] = '\0';
    return correct_data;
}
//-c -конкатенация строк (кроме 3 позиции - число для srand)
check_data get_string_concaten(char *str[], int argc_qnty, char **str_concaten, unsigned int seed)
{
    int length;
    length = count_length(str[2]);
    for (int i = 4; i < argc_qnty; i++)
    {
        length += count_length(str[i]);
    }
    (*str_concaten) = (char *)malloc((length + 1) * sizeof(char));
    if (*str_concaten == NULL)
    {
        return  memory_allocation_error;
    }
    int str_qnty = argc_qnty - 3; // количество строк
    char *new_str[str_qnty];
    new_str[0] = str[2]; // т.к нужны 2,4,5...
    for (int i = 4; i < argc_qnty; i++)
    {
        new_str[i - 3] = str[i];
    }
    int *array_random = (int *)calloc(str_qnty, sizeof(int));
    if (array_random == NULL)
    {
        return memory_allocation_error;
    }
    int order = 0;
    srand(seed);
    for (int i = 0; i < str_qnty; i++)
    {
        int random = rand() % str_qnty;
        while (array_random[random])
        {
            random++;
            random %= str_qnty;
        }
        array_random[random] = 1;
        for (int j = 0; new_str[random][j]; j++)
        {
            (*str_concaten)[order] = new_str[random][j];
            order++;
        }
    }
    (*str_concaten)[length] = '\0';
    free(array_random);
    return correct_data;
}
void print_info()
{
    printf("Enter action and str \n");
    printf("-l: counting the length of the passed string\n");
    printf("-r: get a new string that is reversed\n");
    printf("-u: receive a new string identical to the one passed, while every character in an odd position must be converted to uppercase\n");
    printf("-n: get a new string from the characters of the passed string\n");
    printf("-c: get a new string that is a concatenation of the second, fourth, fifth, etc.\n");
}
