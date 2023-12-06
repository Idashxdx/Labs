#include "action.h"
// сдвиг влево и вправо (<< и >>), дополнения до единицы: ~
// возвращаем символ указанной позиции в заданной сс(отстаток от деления и база)
char get_symbols_for_base(int value, int base) 
{
    if (value >= 0 && value < base)
    {
        if (value < 10)
        {
            return '0' + value;
        }
        else
        {
            return 'A' + (value - 10);
        }
    }
    return '\0';
}
// двоичное сложение план: пока второе !=0 выполняем К b исключающее или и присваемаем второму результат побитового сдвига влево на 1 побит для с
int increase(int a, int b)
{
    int c;
    while (b != 0)
    {
        c = a & b;
        a = a ^ b;
        b = c << 1;
    }
    return a;
}
// для увеличение значения по адресу на 1
void increment(int *a)
{
    *a = increase(*a, 1);
}
// инвентируем число план: побитовое отрицание числа (~a - дополнение до еденицы) и добавляем к отрецательному 1
int negative(int a)
{
    int b = ~a;
    increment(&b);
    return b;
}
check_data truns_number(char **result, int number, int r)
{
    int base = 1 << r; // вычисляем основания для преобразования
    int valume = 32;
    int size = 0;
    bool negative_number = false;

    (*result) = (char *)malloc(sizeof(char) * valume);
    if (*result == NULL)
    {
        return memory_malloc_error;
    }
    if (number < 0) // если отрицательное число - инвентируем его
    {
        number = negative(number);
        (*result)[0] = '-';
        increment(&size);
        negative_number = true;
    }
    while (number > 0)
    {
        int remainder = number & (base - 1);
        char symbol = get_symbols_for_base(remainder, base);
        if (size >= (valume - 1))
        {
            valume = valume << 1;
            char *tmp = (char *)realloc(*result, valume);
            if (tmp == NULL)
            {
                free(*result);
                return memory_realloc_error;
            }
            *result = tmp;
        }
        (*result)[size++] = symbol;
        number = number >> r;
    }

    (*result)[size] = '\0';
    char *tmp = (char *)realloc(*result, size + 1); //обрезаем размер буфера до необходимого
    if (tmp == NULL)
    {
        free(*result);
        return memory_realloc_error;
    }
    *result = tmp;
    // меняем порядок цифр в строке (в другую строну)
    int first = (negative_number) ? 1 : 0;
    int second = (negative_number) ? 1 : 2;
    for (int i = first; i < (size >> 1); increment(&i))
    {
        int j = (size - i - second);
        char tmp = (*result)[i];
        (*result)[i] = (*result)[j];
        (*result)[j] = tmp;
    }
    return correct_data;
}
