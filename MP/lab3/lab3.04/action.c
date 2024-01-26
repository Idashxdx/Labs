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
    {
        if (str1.length < str2.length)
        {
            return -1; // str1 меньше str2
        }
        else if (str1.length > str2.length)
        {
            return 1; // str1 больше str2
        }
        else
        {
            int lexComparison = strcmp(str1.str, str2.str);
            if (lexComparison < 0)
            {
                return -1; // str1 меньше str2
            }
            else if (lexComparison > 0)
            {
                return 1; // str1 больше str2
            }
            else
            {
                return 0; // str1 равно str2
            }
        }
    }
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
int valid_id_14(const char *index)
{
    if (strlen(index) != 14)
    {
        return 0;
    }

    for (int i = 0; i < 14; i++)
    {
        if (!isdigit(index[i]))
        {
            return 0;
        }
    }

    return 1;
}
int valid_weight(const char *weight)
{
    int dot_count = 0; // Счетчик точек
    for (int i = 0; weight[i] != '\0'; i++)
    {
        if (!isdigit(weight[i]))
        {
            if (weight[i] == '.')
            {
                dot_count++;
                if (dot_count > 1)
                {
                    return 0;
                }
            }
            else
            {
                return 0;
            }
        }
    }

    double value = atof(weight);

    if (value < 0)
    {
        return 0;
    }

    return 1;
}
int valid_datetime(const char *datetime)
{
    if (strlen(datetime) != 19)
    {
        return 0;
    }
    if (datetime[2] != ':' || datetime[5] != ':' || datetime[10] != ' ' || datetime[13] != ':' || datetime[16] != ':')
    {
        return 0;
    }
    int day = atoi(&datetime[0]);
    int month = atoi(&datetime[3]);
    int year = atoi(&datetime[6]);
    int hour = atoi(&datetime[11]);
    int minute = atoi(&datetime[14]);
    int second = atoi(&datetime[17]);

    if (day < 1 || day > 31 || month < 1 || month > 12 || hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59)
    {
        return 0;
    }
    // високосный год
    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    switch (month)
    {
    case 2: // Февраль
        if (leap && day > 29)
        {
            return 0;
        }
        else if (!leap && day > 28)
        {
            return 0;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (day > 30)
        {
            return 0;
        }
        break;
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
            input[strcspn(input, "\n")] = '\0'; // Remove newline character
            if (strlen(input) >= size - 1)
            {
                printf("Large size - please re-enter.\n");
            }
            else if (strlen(input) == 0 && valid != 0)
            {
                printf("Incorrect data. Please re-enter. (str) \n");
            }
            else if (valid == 1 && valid_num(input) == 0)
            {
                printf("Incorrect data. Please re-enter. (INT)\n");
            }
            else if (valid == 2 && valid_id_6(input) == 0)
            {
                printf("Incorrect data. Please re-enter. (INT and 6)\n");
            }
            else if (valid == 3 && valid_weight(input) == 0)
            {
                printf("Incorrect data. Please re-enter. (DOUBLE)\n");
            }
            else if (valid == 4 && valid_id_14(input) == 0)
            {
                printf("Incorrect data. Please re-enter. (INT and 14)\n");
            }
            else if (valid == 5 && valid_datetime(input) == 0)
            {
                printf("Incorrect data. Please re-enter. (dd:MM:yyyy hh:mm:ss)\n");
            }
            else
            {
                break;
            }
        }
        else
        {
            printf("Incorrect data. Please try again.\n");
            input[0] = '\0';
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
check_data create_post(Post **post, Address *address, size_t *count, size_t *max_count)
{
    (*count) = 0;
    (*max_count) = 2;
    (*post) = (Post *)malloc(sizeof(Post));
    if (!*post)
    {
        return memory_alloc_error;
    }
    (*post)->address = address;
    (*post)->mail = (Mail *)malloc(sizeof(Mail) * (*max_count));
    if (!(*post)->mail)
    {
        free(*post);
        return memory_alloc_error;
    }
    return correct_data;
}
check_data create_mail(Mail *mail, Address address, char *weight_str, char *id_14, char *creation_time, char *delivery_time)
{
    mail->address = address;
    mail->weight = atof(weight_str);
    String str_id_14;
    String str_ctime;
    String str_dtime;
    if (create_string(creation_time, &str_ctime) == memory_alloc_error ||
        create_string(id_14, &str_id_14) == memory_alloc_error ||
        create_string(delivery_time, &str_dtime) == memory_alloc_error)
    {
        return memory_alloc_error;
    }
    mail->id_14 = str_id_14;
    mail->creation_time = str_ctime;
    mail->delivery_time = str_dtime;
    return correct_data;
}
void print_mail(Mail mail)
{
    printf("\nADDRESS: \n");
    printf("City: %s\n", mail.address.city.str);
    printf("Street: %s\n", mail.address.street.str);
    printf("House number: %d\n", mail.address.num_house);
    printf("Building: %s\n", mail.address.building.str);
    printf("Apartament number: %d\n", mail.address.num_apart);
    printf("Index: %d\n", mail.address.id_6);
    printf("Weignt: %f\n", mail.weight);
    printf("Index mail: %s\n", mail.id_14.str);
    printf("Creation time: %s\n", mail.creation_time.str);
    printf("Delivery time: %s\n\n", mail.delivery_time.str);
}
check_data search_mail(Post *post, String id_14, size_t count)
{
    {
        for (size_t i = 0; i < count; i++)
        {
            if (compare_string(post->mail[i].id_14, id_14) == 0)
            {
                return correct_data;
            }
        }
        return incorrect_data;
    }
}
check_data add_mail_in_post(Post **post, Mail mail, size_t *count, size_t *max_count)
{
    if (search_mail((*post), mail.id_14, (*count)) == correct_data) // проверка на дубликат
    {
        return incorrect_data;
    }
    (*post)->mail[(*count)] = mail;
    (*count)++;
    if ((*count) >= (*max_count))
    {
        (*max_count) *= 2;
        Mail *tmp = (Mail *)realloc((*post)->mail, sizeof(Mail) * (*max_count));
        if (!tmp)
        {
            free((*post)->mail);
            return memory_alloc_error;
        }
        (*post)->mail = tmp;
    }
    return correct_data;
}