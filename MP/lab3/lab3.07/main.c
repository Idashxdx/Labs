#include "action.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Enter file input\n");
        return 1;
    }
    else
    {
        FILE *input_file;
        input_file = fopen(argv[1], "r");
        if (!input_file)
        {
            printf("File 1 opening error\n");
            return 1;
        }
        Node *node = NULL;

        switch (read_input(input_file, &node))
        {
        case correct_data:
            printf("File reading\n\n");
            break;
        case memory_alloc_error:
            fclose(input_file);
            printf("Memory allocation error\n");
            return 1;
        default:
            fclose(input_file);
            printf("Incorrect data in file\n");
            return 1;
        }
        int counter_operation = 0;
        Operation *operation = NULL;
        while (1)
        {
            char act[10];
            printf("\nChoose an action:\n");
            printf("<find> - find liver by ...\n");
            printf("<add> - add a liver\n");
            printf("<delete> - delete a liver\n");
            printf("<change> - change a liver\n");
            printf("<output> - print livers in file\n");
            printf("<undo> - undo actions\n");
            printf("<exit> - exit\n\n");
            printf("ENTER ----> ");
            scanf("%s", act);
            if (strcmp(act, "find") == 0)
            {
                fgets(act, sizeof(act), stdin);
                char act2[10];
                printf("Choose. Find by:\n");
                printf("<name> - find a liver by name\n");
                printf("<surname> - find a liver by surname\n");
                printf("<patronymic> - find a liver by patronymic\n");
                printf("<bday> - find a liver by Bdate\n");
                printf("<gender> - find a liver by gender\n");
                printf("<income> - find a liver by income\n");
                printf("<back> - back\n");
                printf("ENTER ----> ");
                scanf("%s", act2);
                if (strcmp(act2, "name") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
                    char name_to_find[50];
                    printf("\nEnter NAME: ");
                    if (scanf("%s", name_to_find) != 1)
                    {
                        printf("Enter a valid char for name.\n\n");
                        continue;
                    }
                    Node *find = find_by_name(node, name_to_find);
                    if (find != NULL)
                    {
                        printf("\nFOUND:\n");
                        print_all_find(find);
                    }
                    else
                    {
                        printf("\nNo livers found.\n");
                    }
                    free_list(find);
                }
                else if (strcmp(act2, "surname") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
                    char surname_to_find[50];
                    printf("\nEnter SURNAME: ");
                    if (scanf("%s", surname_to_find) != 1)
                    {
                        printf("Enter a valid char for surname.\n\n");
                        continue;
                    }
                    Node *find = find_by_surname(node, surname_to_find);
                    if (find != NULL)
                    {
                        printf("\nFOUND:\n");
                        print_all_find(find);
                    }
                    else
                    {
                        printf("\nNo livers found.\n");
                    }
                    free_list(find);
                }
                else if (strcmp(act2, "patronymic") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
                    char patronymic_to_find[50];
                    printf("\nEnter PATRONYMIC: ");
                    if (scanf("%s", patronymic_to_find) != 1)
                    {
                        printf("Enter a valid char for patronymic.\n\n");
                        continue;
                    }
                    Node *find = find_by_patronymic(node, patronymic_to_find);
                    if (find != NULL)
                    {
                        printf("\nFOUND:\n");
                        print_all_find(find);
                    }
                    else
                    {
                        printf("\nNo livers found.\n");
                    }
                    free_list(find);
                }
                else if (strcmp(act2, "bday") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
                    char BDate_to_find[11];
                    printf("\nEnter DATE (dd:mm:yyyy): ");
                    if (scanf("%10s", BDate_to_find) != 1)
                    {
                        printf("Enter a valid char for date (dd:mm:yyyy).\n\n");
                        continue;
                    }
                    if (!valid_date(BDate_to_find))
                    {
                        printf("Enter a valid char for date (dd:mm:yyyy).\n\n");
                        continue;
                    }
                    Node *find = find_by_date(node, BDate_to_find);
                    if (find != NULL)
                    {
                        printf("\nFOUND:\n");
                        print_all_find(find);
                    }
                    else
                    {
                        printf("\nNo livers found.\n");
                    }
                    free_list(find);
                }
                else if (strcmp(act2, "gender") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
                    char gender_to_find;
                    printf("\nEnter GENDER(M|W): ");
                    if (scanf("%c", &gender_to_find) != 1)
                    {
                        printf("Enter a valid char for gender.(M|W)\n\n");
                        continue;
                    }
                    if (gender_to_find != 'M' && gender_to_find != 'F')
                    {
                        printf("Enter a valid char for gender.(M|W)\n\n");
                        continue;
                    }
                    Node *find = find_by_gender(node, gender_to_find);
                    if (find != NULL)
                    {
                        printf("\nFOUND:\n");
                        print_all_find(find);
                    }
                    else
                    {
                        printf("\nNo livers found.\n");
                    }
                    free_list(find);
                }
                else if (strcmp(act2, "income") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
                    double income_to_find;
                    printf("\nEnter INCOME: ");
                    if (scanf("%lf", &income_to_find) != 1)
                    {
                        printf("Enter a valid double for income.\n\n");
                        continue;
                    }
                    if (income_to_find < 0)
                    {
                        printf("Enter a valid double for income.\n\n");
                        continue;
                    }

                    Node *find = find_by_income(node, income_to_find);
                    if (find != NULL)
                    {
                        printf("\nFOUND:\n");
                        print_all_find(find);
                    }
                    else
                    {
                        printf("\nNo livers found.\n");
                    }
                    free_list(find);
                }
                else if (strcmp(act2, "back") == 0)
                {
                    continue;
                }
                else
                {
                    printf("There is no such action. Try again\n\n");
                }
            }
            else if (strcmp(act, "add") == 0)
            {
                fgets(act, sizeof(act), stdin);
            }
            else if (strcmp(act, "delete") == 0)
            {
                fgets(act, sizeof(act), stdin);
            }
            else if (strcmp(act, "change") == 0)
            {
                fgets(act, sizeof(act), stdin);
            }
            else if (strcmp(act, "output") == 0)
            {
                fgets(act, sizeof(act), stdin);
            }
            else if (strcmp(act, "undo") == 0)
            {
                fgets(act, sizeof(act), stdin);
            }
            else if (strcmp(act, "exit") == 0)
            {
                break;
            }
            else
            {
                printf("There is no such action\n\n");
            }
        }
        free_list(node);
        fclose(input_file);
    }
    printf("M8O-211B-22  Mashrabova  lab3 tack6\n");
    return 0;
}
