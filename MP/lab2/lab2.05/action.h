
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <string.h>



char *in_roman_numerals(int nember);
char *Zeckendorf_representation(unsigned int number);
char *representation_at_base(int number,int base);
char* conversion_to_decimal(char *number, int base);
char* memory_dump(void *number, int size);
int overfprintf(FILE* file, const char* flag, ...);
int oversprintf(char* str,const char *flag, ...);

#endif