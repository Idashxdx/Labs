#include "action.h"
int valid_date(const char *date)
{
    if (strlen(date) != 10)
    {
        return 0;
    }
    if (date[2] != '.' || date[5] != '.')
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
                printf("4");
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
    char separator = '.';
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
        if (fscanf(file, "%s %s %s",
                   tmp_liver.name,
                   tmp_liver.surname,
                   tmp_liver.patronymic) < 3)
        {
            break;
        }

        if (isalpha(tmp_liver.patronymic[0]))
        {
            if (fscanf(file, " %d%c%d%c%d %c %lf",
                       &day, &separator, &month, &separator, &year,
                       &tmp_liver.gender,
                       &tmp_liver.income) < 7)
            {
                break;
            }
            snprintf(tmp_liver.BDate, sizeof(tmp_liver.BDate), "%02d.%02d.%04d", day, month, year);
        }
        else
        {
            if (sscanf(tmp_liver.patronymic, "%d%c%d%c%d", &day, &separator, &month, &separator, &year) == EOF)
            {
                break;
            }
            snprintf(tmp_liver.BDate, sizeof(tmp_liver.BDate), "%02d.%02d.%04d", day, month, year);
            tmp_liver.patronymic[0] = '\0';
            if (fscanf(file, " %c %lf",
                       &tmp_liver.gender,
                       &tmp_liver.income) < 2)
            {
                break;
            }
        }
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
Node *find_by_name(Node *head, char *str)
{
    Node *result_found = NULL;
    Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->liver.name, str) == 0)
        {
            Node *new_node = (Node *)malloc(sizeof(Node));
            if (!new_node)
            {
                return NULL;
            }
            new_node->liver = current->liver;
            new_node->next = result_found;
            result_found = new_node;
        }
        current = current->next;
    }
    return result_found;
}

Node *find_by_surname(Node *head, char *str)
{
    Node *result_found = NULL;
    Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->liver.surname, str) == 0)
        {
            Node *new_node = (Node *)malloc(sizeof(Node));
            if (!new_node)
            {
                return NULL;
            }
            new_node->liver = current->liver;
            new_node->next = result_found;
            result_found = new_node;
        }
        current = current->next;
    }
    return result_found;
}
Node *find_by_patronymic(Node *head, char *str)
{
    Node *result_found = NULL;
    Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->liver.patronymic, str) == 0)
        {
            Node *new_node = (Node *)malloc(sizeof(Node));
            if (!new_node)
            {
                return NULL;
            }
            new_node->liver = current->liver;
            new_node->next = result_found;
            result_found = new_node;
        }
        current = current->next;
    }
    return result_found;
}
Node *find_by_gender(Node *head, char gender)
{
    Node *result_found = NULL;
    Node *current = head;
    while (current != NULL)
    {
        if (current->liver.gender == gender)
        {
            Node *new_node = (Node *)malloc(sizeof(Node));
            if (!new_node)
            {
                return NULL;
            }
            new_node->liver = current->liver;
            new_node->next = result_found;
            result_found = new_node;
        }
        current = current->next;
    }
    return result_found;
}

Node *find_by_date(Node *head, char *str)
{
    Node *result_found = NULL;
    Node *current = head;
    while (current != NULL)
    {
        if (strcmp(current->liver.BDate, str) == 0)
        {
            Node *new_node = (Node *)malloc(sizeof(Node));
            if (!new_node)
            {
                return NULL;
            }
            new_node->liver = current->liver;
            new_node->next = result_found;
            result_found = new_node;
        }
        current = current->next;
    }
    return result_found;
}
Node *find_by_income(Node *head, double income)
{
    Node *result_found = NULL;
    Node *current = head;
    while (current != NULL)
    {
        if (current->liver.income == income)
        {
            Node *new_node = (Node *)malloc(sizeof(Node));
            if (!new_node)
            {
                return NULL;
            }
            new_node->liver = current->liver;
            new_node->next = result_found;
            result_found = new_node;
        }
        current = current->next;
    }
    return result_found;
}
void print_node(Node *node)
{
    printf("%s %s %s; Bdate: %s; Gender: %c; Average income: %lf.\n",
           node->liver.name, node->liver.surname, node->liver.patronymic,
           node->liver.BDate, node->liver.gender, node->liver.income);
}
void print_all_find(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        print_node(current);
        current = current->next;
    }
}
void free_list(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        Node *tmp = current;
        current = current->next;
        free(tmp);
    }
}
check_data add_liver(Node **head, Operation **operation, int *counter_operation)
{
    Liver new_liver;
    printf("Enter details of the new liver:\n");
    printf("Enter name: ");
    scanf("%s", new_liver.name);
    printf("Enter surname: ");
    scanf("%s", new_liver.surname);
    printf("Enter patronymic: ");
    scanf("%s", new_liver.patronymic);
    printf("Enter bdate (dd.mm.yyyy): ");
    scanf("%s", new_liver.BDate);
    printf("Enter gender (M/W): ");
    scanf(" %c", &new_liver.gender);
    printf("Enter average income: ");
    scanf("%lf", &new_liver.income);
    if (valid_data(new_liver.name, new_liver.surname, new_liver.patronymic, new_liver.BDate, new_liver.gender, new_liver.income) == incorrect_data)
    {
        return incorrect_data;
    }
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
    {
        return memory_alloc_error;
    }
    new_node->liver = new_liver;
    Node *prev = NULL;
    Node *current = *head;
    while (current != NULL && compare_bdates(current->liver.BDate, new_liver.BDate) < 0)
    {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
    {
        new_node->next = *head;
        *head = new_node;
    }
    else
    {
        new_node->next = prev->next;
        prev->next = new_node;
    }
    // Добавляем действие в стек операций
    Operation *new_operation = (Operation *)malloc(sizeof(Operation));
    if (!new_operation)
    {
        return memory_alloc_error;
    }
    new_operation->oper_liver = new_liver;
    new_operation->orig_liver = new_liver;
    // a-add;d-delete;c-change
    new_operation->type = 'A';
    new_operation->next = *operation;
    *operation = new_operation;
    (*counter_operation)++;
    return correct_data;
}
check_data delete_liver(Node **head, Operation **operation, int *counter_operation)
{
    Liver delete_liver;
    printf("Enter details of the liver to delete:\n");
    printf("Enter name: ");
    scanf("%s", delete_liver.name);
    printf("Enter surname: ");
    scanf("%s", delete_liver.surname);
    printf("Enter patronymic: ");
    scanf("%s", delete_liver.patronymic);
    printf("Enter birth date (dd.mm.yyyy): ");
    scanf("%s", delete_liver.BDate);
    printf("Enter gender (M/W): ");
    scanf(" %c", &delete_liver.gender);
    printf("Enter average income: ");
    scanf("%lf", &delete_liver.income);
    if (valid_data(delete_liver.name, delete_liver.surname, delete_liver.patronymic, delete_liver.BDate, delete_liver.gender, delete_liver.income) == incorrect_data)
    {
        printf("Liver data no valid\n\n");
        return incorrect_data;
    }
    Node *current = *head;
    Node *prev = NULL;
    while (current != NULL)
    {
        if (strcmp(current->liver.name, delete_liver.name) == 0 &&
            strcmp(current->liver.surname, delete_liver.surname) == 0 &&
            strcmp(current->liver.patronymic, delete_liver.patronymic) == 0 &&
            strcmp(current->liver.BDate, delete_liver.BDate) == 0 &&
            current->liver.gender == delete_liver.gender &&
            current->liver.income == delete_liver.income)
        {
            if (prev == NULL)
            {
                *head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            Operation *new_operation = (Operation *)malloc(sizeof(Operation));
            if (!new_operation)
            {
                return memory_alloc_error;
            }
            new_operation->oper_liver = delete_liver;
            new_operation->orig_liver = delete_liver;
            new_operation->type = 'D';
            new_operation->next = *operation;
            *operation = new_operation;
            (*counter_operation)++;
            return correct_data;
        }

        prev = current;
        current = current->next;
    }
    printf("Liver no founded\n\n");
    return incorrect_data;
}
check_data change_liver(Node *head, Operation **operation, int *counter_operation)
{
    Liver old_liver, new_liver;
    printf("Enter details of the liver you want to change:\n");
    printf("Enter name: ");
    scanf("%s", old_liver.name);
    printf("Enter surname: ");
    scanf("%s", old_liver.surname);
    printf("Enter patronymic: ");
    scanf("%s", old_liver.patronymic);
    printf("Enter birth date (dd.mm.yyyy): ");
    scanf("%s", old_liver.BDate);
    printf("Enter gender (M/W): ");
    scanf(" %c", &old_liver.gender);
    printf("Enter average income: ");
    scanf("%lf", &old_liver.income);
    if (valid_data(old_liver.name, old_liver.surname, old_liver.patronymic, old_liver.BDate, old_liver.gender, old_liver.income) == incorrect_data)
    {
        printf("Liver data not valid\n\n");
        return incorrect_data;
    }
    Node *current = head;

    while (current != NULL)
    {
        if (strcmp(current->liver.name, old_liver.name) == 0 &&
            strcmp(current->liver.surname, old_liver.surname) == 0 &&
            strcmp(current->liver.patronymic, old_liver.patronymic) == 0 &&
            strcmp(current->liver.BDate, old_liver.BDate) == 0 &&
            current->liver.gender == old_liver.gender &&
            current->liver.income == old_liver.income)
        {
            printf("Enter new name: ");
            scanf("%s", new_liver.name);
            printf("Enter new surname: ");
            scanf("%s", new_liver.surname);
            printf("Enter new patronymic: ");
            scanf("%s", new_liver.patronymic);
            printf("Enter new birth date (dd.mm.yyyy): ");
            scanf("%s", new_liver.BDate);
            printf("Enter new gender (M/W): ");
            scanf(" %c", &new_liver.gender);
            printf("Enter new average income: ");
            scanf("%lf", &new_liver.income);
            if (valid_data(new_liver.name, new_liver.surname, new_liver.patronymic, new_liver.BDate, new_liver.gender, new_liver.income) == incorrect_data)
            {
                printf("New liver data not valid\n\n");
                return incorrect_data;
            }
            Operation *new_operation = (Operation *)malloc(sizeof(Operation));
            if (!new_operation)
            {
                return memory_alloc_error;
            }
            new_operation->oper_liver = new_liver;
            new_operation->orig_liver = old_liver;
            new_operation->type = 'C';
            new_operation->next = *operation;
            *operation = new_operation;
            (*counter_operation)++;
            strcpy(current->liver.name, new_liver.name);
            strcpy(current->liver.surname, new_liver.surname);
            strcpy(current->liver.patronymic, new_liver.patronymic);
            strcpy(current->liver.BDate, new_liver.BDate);
            current->liver.gender = new_liver.gender;
            current->liver.income = new_liver.income;

            return correct_data;
        }
        current = current->next;
    }
    printf("Liver not found\n\n");
    return incorrect_data;
}
check_data undo(Node **head, Operation **operation, int *counter_operation)
{
    int num_operations_to_undo = *counter_operation / 2;
    Operation *prev_operation = NULL;

    while (num_operations_to_undo > 0 && *operation != NULL)
    {
        Operation *last_operation = *operation;
        *operation = last_operation->next;

        if (last_operation->type == 'A')
        {
            Node *current = *head;
            Node *prev = NULL;

            while (current != NULL)
            {
                if (strcmp(current->liver.name, last_operation->oper_liver.name) == 0 &&
                    strcmp(current->liver.surname, last_operation->oper_liver.surname) == 0 &&
                    strcmp(current->liver.patronymic, last_operation->oper_liver.patronymic) == 0 &&
                    strcmp(current->liver.BDate, last_operation->oper_liver.BDate) == 0 &&
                    current->liver.gender == last_operation->oper_liver.gender &&
                    current->liver.income == last_operation->oper_liver.income)
                {
                    if (prev == NULL)
                    {
                        *head = current->next;
                    }
                    else
                    {
                        prev->next = current->next;
                    }

                    free(current);
                    break;
                }

                prev = current;
                current = current->next;
            }
        }
        else if (last_operation->type == 'D')
        {
            Node *new_node = (Node *)malloc(sizeof(Node));
            if (!new_node)
            {
                return memory_alloc_error;
            }
            new_node->liver = last_operation->oper_liver;
            new_node->next = *head;
            *head = new_node;
        }
        // неправильно
        else if (last_operation->type == 'C')
        {
            Node *current = *head;
            while (current != NULL)
            {
                if (strcmp(current->liver.name, last_operation->oper_liver.name) == 0 &&
                    strcmp(current->liver.surname, last_operation->oper_liver.surname) == 0 &&
                    strcmp(current->liver.patronymic, last_operation->oper_liver.patronymic) == 0 &&
                    strcmp(current->liver.BDate, last_operation->oper_liver.BDate) == 0 &&
                    current->liver.gender == last_operation->oper_liver.gender &&
                    current->liver.income == last_operation->oper_liver.income)
                {
                    strcpy(current->liver.name, last_operation->orig_liver.name);
                    strcpy(current->liver.surname, last_operation->orig_liver.surname);
                    strcpy(current->liver.patronymic, last_operation->orig_liver.patronymic);
                    strcpy(current->liver.BDate, last_operation->orig_liver.BDate);
                    current->liver.gender = last_operation->orig_liver.gender;
                    current->liver.income = last_operation->orig_liver.income;
                    break;
                }

                current = current->next;
            }
        }

        free(last_operation);
        prev_operation = last_operation;
        num_operations_to_undo--;
        (*counter_operation)--;
    }

    if (prev_operation)
    {
        prev_operation->next = *operation;
    }

    return correct_data;
}
