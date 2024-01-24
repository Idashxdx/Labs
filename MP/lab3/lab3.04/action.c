#include "action.h"
// TASK 1
String create_string(const char *input, check_data *status)
{
    String string;
    if (input == NULL)
    {
        string.length = 0;
        string.str = NULL;
        *status = correct_data;
    }
    else
    {
        string.length = strlen(input);
        string.str = (char *)malloc((string.length + 1) * sizeof(char)); //+1 для \0
        if (string.str == NULL)
        {
            *status = memory_alloc_error;
        }
        else
        {
            strcpy(string.str, input);
            *status = correct_data;
        }
    }
    return string;
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
String copy_string(String *new_str1, const String str2, check_data *status)
{

    if (new_str1->length < str2.length)
    {
        char *tmp = (char *)realloc(new_str1->str, sizeof(char) * (str2.length + 1));
        if (tmp == NULL)
        {
            *status = memory_alloc_error;
        }
        new_str1->str = tmp;
    }
    *status = correct_data;

    strcpy(new_str1->str, str2.str);
    new_str1->length = str2.length;
}
String copy_to_dinamic_string(const String str1, check_data *status)
{

    String string;
    string.str = (char *)malloc((str1.length + 1) * sizeof(char));
    if (string.str == NULL)
    {
        *status = memory_alloc_error;
        return string;
    }
    strcpy(string.str, str1.str);
    string.length = str1.length;

    *status = correct_data;
    return string;
}
int compare_string(const String str1, const String str2)
{
    if (str1.length != str2.length)
    {
        return str1.length - str2.length;
    }
    return strcmp(str1.str, str2.str);
}
String concatenation_string(String *new_str1, const String str2, check_data *status)
{
    char *tmp = (char *)realloc(new_str1->str, sizeof(char) * (new_str1->length + str2.length + 1));
    if (tmp == NULL)
    {
        *status = memory_alloc_error;
    }
     *status = correct_data;
    new_str1->length = new_str1->length + str2.length;
    new_str1->str = tmp;
    strcat(new_str1->str, str2.str);
    
}
void clear_string(String *str)
{
    free(str->str);
    str->str = NULL;
    str->length = 0;
}
