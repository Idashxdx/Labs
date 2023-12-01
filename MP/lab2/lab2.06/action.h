
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
int overfscanf(FILE *stream, const char *format, ...);
#endif