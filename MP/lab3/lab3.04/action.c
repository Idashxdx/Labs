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
// task2
int valid_num(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0; // не цифра
        }
    }
    return 1;
}
int valid_id_6(const char *index)
{
    if (strlen(index) != 6)
    {
        return 0; // не 6
    }

    for (int i = 0; i < 6; i++)
    {
        if (!isdigit(index[i]))
        {
            return 0; // Один из символов индекса не является цифрой
        }
    }

    return 1;
}
void check_input(const char *print, char *input, int size, int valid)
{
    while (1)
    {
        printf("%s", print);
        if (fgets(input, size, stdin))
        {
            input[strcspn(input, "\n")] = 0; // т.к. fgets добавляет \n - удаляем его
            if (strlen(input) >= size - 1)
            {
                printf("large size - please re-enter.\n"); // не вмещается
            }
            else
            {
                if (strlen(input) == 0)
                {
                    printf("Incorrect data. please re-enter.\n");
                }
                else if (valid == 1 && valid_num(input) == 0) // если valid 1 - должны быть все цифры
                {
                    printf("Incorrect data. please re-enter. (INT) \n");
                }
                else if (valid == 2 && valid_id_6(input) == 0)
                {
                    printf("Incorrect data. please re-enter. (INT and 6) \n");
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            printf("Incorrect data. Please try again.\n");
            input[0] = '\0'; // Очищаем буфер и повторяем запрос ввода
        }
    }
}
check_data create_address(Address *address, char *city, char *street, char *num_house_str, char *building, char *num_apart_str, char *id_6_str)
{

    address->num_house = atoi(num_house_str);
    address->num_apart = atoi(num_apart_str);
    address->id_6 = atoi(id_6_str);
    String str_city;
    String str_street;
    String str_building;
    if (create_string(city, &str_city) == memory_alloc_error ||
        create_string(street, &str_street) == memory_alloc_error ||
        create_string(building, &str_building) == memory_alloc_error)
    {
        return memory_alloc_error;
    }
    address->city = str_city;
    address->street = str_street;
    address->building = str_building;
    return correct_data;
}