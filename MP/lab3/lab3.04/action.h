
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define EPSILON 1e-9
// проверка
typedef enum check_data
{
    correct_data,
    incorrect_data,
    memory_alloc_error
} check_data;

typedef struct
{
    char *str;
    int length;
} String;

String create_string(const char *input, check_data *status);
int equality(const String str1, const String str2);
String copy_string(String *new_str1, const String str2, check_data *status);
String copy_to_dinamic_string(const String str1, check_data *status);
int compare_string(const String str1, const String str2);
String concatenation_string(String *new_str1, const String str2, check_data *status);
void clear_string(String *str);
#endif
