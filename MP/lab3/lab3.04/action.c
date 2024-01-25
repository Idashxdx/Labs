#include "action.h"
// TASK 1
check_data create_string(const char *input, String *str)
{
    if (input == NULL)
    {
        str->length = 0;
        str->str = NULL;
        return correct_data;
    }
    else
    {
        str->length = strlen(input);
        str->str = (char *)malloc((str->length + 1) * sizeof(char)); //+1 для '\0'
        if (str->str == NULL)
        {
            return memory_alloc_error;
        }
        else
        {
            strcpy(str->str, input);
            return correct_data;
        }
    }
}
int equality(const String str1, const String str2)
{
    if (str1.length != str2.length)
    {
        return 0;
    }
    else
    {
        if (strcmp(str1.str, str2.str) == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
check_data copy_string(String *new_str1, const String str2)
{

    if (new_str1->length < str2.length)
    {
        char *tmp = (char *)realloc(new_str1->str, sizeof(char) * (str2.length + 1));
        if (tmp == NULL)
        {
            return memory_alloc_error;
        }
        new_str1->str = tmp;
    }
    strcpy(new_str1->str, str2.str);
    new_str1->length = str2.length;
    return correct_data;
}
check_data copy_to_dinamic_string(const String str1, String *str2)
{

    str2->str = (char *)malloc((str1.length + 1) * sizeof(char));
    if (str2->str == NULL)
    {
        return memory_alloc_error;
    }
    strcpy(str2->str, str1.str);
    str2->length = str1.length;
    return correct_data;
}
int compare_string(const String str1, const String str2)
{
    if (str1.length != str2.length)
    {
        return str1.length - str2.length;
    }
    return strcmp(str1.str, str2.str);
}
check_data concatenation_string(String *new_str1, const String str2)
{
    char *tmp = (char *)realloc(new_str1->str, sizeof(char) * (new_str1->length + str2.length + 1));
    if (tmp == NULL)
    {
        return memory_alloc_error;
    }
    new_str1->length = new_str1->length + str2.length;
    new_str1->str = tmp;
    strcat(new_str1->str, str2.str);
    return correct_data;
}
void clear_string(String *str)
{
    free(str->str);
    str->str = NULL;
    str->length = 0;
}
