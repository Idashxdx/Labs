#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
// strtol() преобразует начальную часть строки в длинное целое число согласно системе счисления, значение от 2 до 36
int conversion_to_decimal(char *number, int base)
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
            digit = toupper(number[i]) - 'A' + 10; // переобразование в прописные
        }
        decimal = decimal * base + digit;
    }
    return decimal;
}
void action_file(char *number, FILE *output)
{
    int str_lenght = strlen(number);
    int base = 2;
    for (; base <= 36; base++)
    {
        char *endptr;
        strtol(number, &endptr, base);
        if (endptr - number == str_lenght)
        {
            // убираем нули
            int zero = 0;
            bool is_zero = true;
            int not_zero_position = 0;

            for (int i = 0; number[i] && not_zero_position == 0; ++i)
            {
                if (number[i] != '0' && number[i] != '-')
                {
                    is_zero = false;
                    not_zero_position = i;
                }
            }
            if (is_zero == true)
            {
                number[0] = '0';
                number[1] = '\0';
                return;
            }
            if (number[0] == '-' && number[1] == '0')
            {
                zero = 1;
            }
            if (not_zero_position <= zero)
            {
                return;
            }
            for (int i = 0; number[i + not_zero_position]; ++i)
            {
                number[i + zero] = number[i + not_zero_position];
                number[i + zero + 1] = '\0';
            }
            fprintf(output, "%s %d %d\n", number, base, conversion_to_decimal(number, base));
            break;
        }
    }
}
int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("Enter input and output files\n");
        return 1;
    }
    else
    {
        FILE *input_file = fopen(argv[1], "r");
        if (!input_file)
        {
            printf("File 1 opening error\n");
            return 1;
        }
        FILE *output_file = fopen(argv[2], "w");
        if (!output_file)
        {
            fclose(input_file);
            printf("File 2 opening error\n");
            return 1;
        }
        char number[100];
        while (fscanf(input_file, "%s", number) == 1)
        {
            action_file(number, output_file);
        }
        fclose(input_file);
        fclose(output_file);
    }
    printf("\n\nM8O-211B-22  Mashrabova  lab1 tack8\n");
    return 0;
}
