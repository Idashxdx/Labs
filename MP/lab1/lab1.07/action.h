#ifndef action_h
#define action_h

#include <stdio.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// разделители лексем в входном файле
int separator(char symbol)
{
    return (symbol == ' ' || symbol == '\t' || symbol == '\n');
}
// преобразование - base-основа - для 10-4, для 5-8
int conversion_ascii_four(int symbol)
{
    int result = 0;
    int ten = 1;
    while (symbol > 0)
    {
        int trans = symbol % 4;
        result += trans * ten;
        symbol /= 4;
        ten *= 10;
    }
    return result;
}
int conversion_ascii_eight(int symbol)
{
    int result = 0;
    int ten = 1;
    while (symbol > 0)
    {
        int trans = symbol % 8;
        result += trans * ten;
        symbol /= 8;
        ten *= 10;
    }
    return result;
}
//-a
void record_change(FILE *input, FILE *output)
{
    int order = 1; // для нумерации лексем
    char symbol = fgetc(input);
    while (symbol != EOF)
    {

        while (separator(symbol))
        {
            symbol = fgetc(input);
        }
        if (order % 10 == 0)
        {
            while (!separator(symbol) && symbol != EOF)
            {
                if (isalpha(symbol))
                {
                    symbol = tolower(symbol); // замена прописных на строчные
                    fprintf(output, "%d", conversion_ascii_four((int)symbol));
                }
                symbol = fgetc(input);
            }
        }
        else if (order % 2 == 0 && order % 10 != 0)
        {
            while (!separator(symbol) && symbol != EOF)
            {
                if (isalpha(symbol))
                {
                    fprintf(output, "%c", tolower(symbol));
                }
                symbol = fgetc(input);
            }
        }
        else if (order % 5 == 0 && order % 10 != 0)
        {
            while (!separator(symbol) && symbol != EOF)
            {
                if (isalpha(symbol))
                {
                    fprintf(output, "%d", conversion_ascii_eight((int)symbol));
                }
                symbol = fgetc(input);
            }
        }
        // пробел между лексемами в выходном файле.
        while (!separator(symbol) && symbol != EOF)
        {
            putc(symbol, output);
            symbol = fgetc(input);
        }
        fputc(' ', output);
        order++;
    }
}
//-r запись лексемы из 1 файла, потом из 2 и так до конца
void record_even_odd(FILE *input1, FILE *input2, FILE *output)
{
    char lexeme1 = fgetc(input1);
    char lexeme2 = fgetc(input2);
    while (lexeme1 != EOF || lexeme2 != EOF)
    {
        while (separator(lexeme1))
        {
            lexeme1 = fgetc(input1);
        }
        while (separator(lexeme2))
        {
            lexeme2 = fgetc(input2);
        }
        while (!separator(lexeme1) && lexeme1 != EOF)
        {
            fprintf(output, "%c", lexeme1);
            lexeme1 = fgetc(input1);
        }
        if (lexeme1 != EOF)
        {
            fputc(' ', output);
        }
        while (!separator(lexeme2) && lexeme2 != EOF)
        {
            fprintf(output, "%c", lexeme2);
            lexeme2 = fgetc(input2);
        }
        if (lexeme2 != EOF)
        {
            fputc(' ', output);
        }
        if (lexeme1 == EOF && lexeme2 == EOF)
        {
            break;
        }
    }
}

void print_info()
{
    printf("Enter action and file \n");
    printf("-r -file1 -file2 -fileresult\n");
    printf("-a -file -fileresult\n");
}

#endif
