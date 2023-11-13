#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// isdigit - диапазон 0-9
// isalpha - диапазон A-Z

void exclud_digit(FILE *input, FILE *output)
{
    char symbol = fgetc(input);
    while (symbol != EOF)
    {
        if (!isdigit(symbol))
        {
            fputc(symbol, output);
        }
        symbol = fgetc(input);
    }
}
void count_letter(FILE *input, FILE *output)
{
    char symbol = fgetc(input);
    char line[100];
    int number_letter = 0;
    while (symbol != EOF)
    {
        if (symbol == '\n')
        {
            sprintf(line, " |NUMBER OF LETTERS--> %d|\n", number_letter);
            fputs(line, output);
            symbol = fgetc(input);
            number_letter = 0;
            continue;
        }
        if (isalpha(symbol))
        {
            number_letter++;
        }
        fputc(symbol, output);
        symbol = fgetc(input);
    }
    sprintf(line, " |NUMBER OF LETTERS--> %d|\n", number_letter);
    fputs(line, output);
}
void different_symbol(FILE *input, FILE *output)
{
    char symbol = fgetc(input);
    char line[100];
    int number_different = 0;
    while (symbol != EOF)
    {
        if (symbol == '\n')
        {
            sprintf(line, " |DIFFERENT SYMBOLS--> %d|\n", number_different);
            fputs(line, output);
            symbol = fgetc(input);
            number_different = 0;
            continue;
        }
        if (!isalpha(symbol) && !isdigit(symbol) && symbol != ' ')
        {
            number_different++;
        }
        fputc(symbol, output);
        symbol = fgetc(input);
    }
    sprintf(line, " |DIFFERENT SYMBOLS--> %d|\n", number_different);
    fputs(line, output);
}
void replac_symbol(FILE *input, FILE *output)
{
    char symbol = fgetc(input);
    char full[100];
    while (symbol != EOF)
    {
        if (!isdigit(symbol))
        {
            sprintf(full, "%X", (int)symbol);
            fputs(full, output);
            symbol = fgetc(input);
            continue;
        }
        fputc(symbol, output);
        symbol = fgetc(input);
    }
}
void print_info()
{
    printf("Enter action and file \n");
    printf("-d -file: excluding digits--->result avto new file, -nd -file -file2-->result in file2\n");
    printf("-i -file: number of letters--->result avto new file, -ni -file -file2-->result in file2\n");
    printf("-s -file: counting other characters--->result avto new file, -ns -file -file2-->result in file2\n");
    printf("-a -file: replacement with ascii code--->result avto new file, -na -file -file2-->result in file2\n");
}

#endif
