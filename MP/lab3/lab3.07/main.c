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
            print_list(node);
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
        while (1)
        {
            char act[10];
            printf("Choose an action:\n");

            printf("<exit> - exit\n\n");
            printf("ENTER ----> ");
            scanf("%s", act);
            if (strcmp(act, "find") == 0)
            {
                fgets(act, sizeof(act), stdin);
                char act2[10];
                printf("Choose. Find by:\n");
                printf("<name> - find a student by name\n");
                printf("<surname> - find a student by surname\n");
                printf("<back> - back\n");
                printf("ENTER ----> ");
                scanf("%s", act2);
                if (strcmp(act2, "name") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
                    char name_to_find[50];
                    printf("Enter student NAME: ");
                    if (scanf("%s", name_to_find) != 1)
                    {
                        printf("Enter a valid char for Name.\n\n");
                        continue;
                    }
                    //
                }
                else if (strcmp(act2, "surname") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
                    char surname_to_find[50];
                    printf("Enter student surname: ");
                    if (scanf("%s", surname_to_find) != 1)
                    {
                        printf("Enter a valid char for surname.\n\n");
                        continue;
                    }
                    //
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
            else if (strcmp(act, "") == 0)
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

        fclose(input_file);
    }
    printf("M8O-211B-22  Mashrabova  lab3 tack6\n");
    return 0;
}
