#include "action.h"
int valid_date(const char *date)
{
    if (strlen(date) != 10)
    {
        return 0;
    }
    if (date[2] != ':' || date[5] != ':')
    {
        return 0;
    }
    int day = atoi(&date[0]);
    int month = atoi(&date[3]);
    int year = atoi(&date[6]);
    if (day < 1 || day > 31 || month < 1 || month > 12)
    {
        return 0;
    }
    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    switch (month)
    {
    case 2:
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
check_data valid_data(const char *name, const char *surname, const char *patronymic, const char *BDate, char gender, double income)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) || isspace(name[i]))
        {
            return incorrect_data;
        }
    }
    if (strlen(name) == 0)
    {
        return incorrect_data;
    }
    for (int i = 0; surname[i] != '\0'; i++)
    {
        if (!isalpha(surname[i]) || isspace(surname[i]))
        {
            return incorrect_data;
        }
    }
    if (strlen(surname) == 0)
    {
        return incorrect_data;
    }
    if (strlen(patronymic) != 0)
    {
        for (int i = 0; patronymic[i] != '\0'; i++)
        {
            if (!isalpha(patronymic[i]) || isspace(patronymic[i]))
            {
                return incorrect_data;
            }
        }
    }
    if (valid_date(BDate) == 0)
    {
        return incorrect_data;
    }
    if (gender != 'M' && gender != 'W')
{
    return incorrect_data;
}
    if (income < 0)
    {
        return incorrect_data;
    }
    return correct_data;
}
int compare_bdates(const char *date1, const char *date2)
{
    char separator = ':';
    int day1, month1, year1;
    int day2, month2, year2;
    sscanf(date1, "%d%c%d%c%d", &day1, &separator, &month1, &separator, &year1);
    sscanf(date2, "%d%c%d%c%d", &day2, &separator, &month2, &separator, &year2);
    if (year1 != year2)
    {
        return year1 - year2;
    }
    if (month1 != month2)
    {
        return month1 - month2;
    }
    return day1 - day2;
}
check_data read_input(FILE *file, Node **head)
{
    *head = NULL; 
    while (1)
    {
        Liver tmp_liver;
        int day, month, year;
        char separator;
        if (fscanf(file, "%s %s %s %d%c%d%c%d %c %lf",
                   tmp_liver.name,
                   tmp_liver.surname,
                   tmp_liver.patronymic,
                   &day, &separator, &month, &separator, &year,
                   &tmp_liver.gender,
                   &tmp_liver.income) != 10)
        {
            break;
        }
        snprintf(tmp_liver.BDate, sizeof(tmp_liver.BDate), "%02d:%02d:%04d", day, month, year);
        if (valid_data(tmp_liver.name,
                       tmp_liver.surname,
                       tmp_liver.patronymic,
                       tmp_liver.BDate,
                       tmp_liver.gender,
                       tmp_liver.income) == incorrect_data)
        {
            return incorrect_data;
        }

        Node *new_node = (Node *)malloc(sizeof(Node));
        if (!new_node)
        {
            return memory_alloc_error;
        }

        new_node->liver = tmp_liver;
        new_node->next = NULL;

        if (*head == NULL || compare_bdates((*head)->liver.BDate, tmp_liver.BDate) > 0)
        {
            new_node->next = *head;
            *head = new_node;
        }
        else
        {
            Node *current = *head;
            while (current->next != NULL && compare_bdates(current->next->liver.BDate, tmp_liver.BDate) < 0)
            {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }
    }
    return correct_data;
}
void print_list(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("Имя: %s\n", current->liver.name);
        printf("Фамилия: %s\n", current->liver.surname);

        // Проверка на пустое отчество
        if (strlen(current->liver.patronymic) > 0)
        {
            printf("Отчество: %s\n", current->liver.patronymic);
        }
        else
        {
            printf("Отчество: нет\n");
        }

        printf("Дата рождения: %s\n", current->liver.BDate);
        printf("Пол: %c\n", current->liver.gender);
        printf("Средний доход: %lf\n", current->liver.income);
        printf("\n");

        current = current->next;
    }
}

