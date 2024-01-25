
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

check_data create_string(const char *input, String* str);
int equality(const String str1, const String str2);
check_data copy_string(String *new_str1, const String str2);
check_data copy_to_dinamic_string(const String str1, String* str2);
int compare_string(const String str1, const String str2);
check_data concatenation_string(String *new_str1, const String str2);
void clear_string(String *str);

#endif
