
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

struct Roman
{
    char symbol;
    int value;
};

int conversion(char symbol, struct Roman numerals[]);
int number_to_roman(char *roman, struct Roman numerals[]);
int cv_base_lower(char *input, int base);
unsigned int cv_base_upper(char *input, int base);
unsigned int zeckendorf_to_number(char *zeckendorf);
int overfscanf(FILE *stream, const char *format, ...);
int oversscanf(const char *str, const char *format, ...);
#endif