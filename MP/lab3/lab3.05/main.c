#include "action.h"

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("Enter file input, file output \n");
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
        FILE *output_file;
        output_file = fopen(argv[2], "w");
        if (!output_file)
        {
            fclose(input_file);
            printf("File 2 opening error\n");
            return 1;
        }

        // Читаем файл
        Student *students = NULL;
        size_t count = 0;    // сколько всего студентов
        size_t capacity = 2; // макс. к-во студентов
        // для вычисления средней оценки :
        double count_grades = 0;
        double summ_grades = 0;
        double average_grades;
        switch (read_input(input_file, &students, &count, &capacity, &count_grades, &summ_grades, &average_grades))
        {
        case correct_data:
            printf("File reading\n\n");
            break;
        case memory_alloc_error:
            fclose(input_file);
            fclose(output_file);
            printf("Memory allocation error\n");
            return 1;
        default:
            fclose(input_file);
            fclose(output_file);
            printf("Incorrect data in file\n");
            return 1;
        }
        while (1)
        {
            char act[10];
            printf("Choose an action:\n");
            printf("<find>  - find a student by ...\n");
            printf("<sort> - sort students by ...\n");
            printf("<write> - write to file: best student, student by index\n");
            printf("<exit> - exit\n\n");
            printf("ENTER ----> ");
            scanf("%s", act);

            if (strcmp(act, "find") == 0)
            {
                fgets(act, sizeof(act), stdin);

                char act2[10];
                printf("Choose. Find by:\n");
                printf("<id>  - find a student by id\n");
                printf("<name> - find a student by name\n");
                printf("<surname> - find a student by surname\n");
                printf("<group> - find a student by group \n");
                printf("<back> - back\n");
                printf("ENTER ----> ");
                scanf("%s", act2);
                if (strcmp(act2, "id") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
                    char input[50];
                    unsigned int id_to_find;
                    printf("Enter student ID: ");
                    fgets(input, sizeof(input), stdin);
                    if (sscanf(input, "%u", &id_to_find) != 1)
                    {
                        printf("Enter a valid unsigned int for ID.\n\n");
                        continue;
                    }
                    for (size_t i = 0; i < count; i++)
                    {
                        Student *found_student = find_student_by_id(students, i, id_to_find);
                        if (found_student != NULL)
                        {
                            fprintf(output_file, "Student find by id: %u ----> ", id_to_find);
                            write_student_info_to_file(output_file, found_student);
                            // сброс буфера - что бы не хранилось после записи.
                            fflush(output_file);
                            free(found_student);
                        }
                        i++;
                    }
                    printf("Result write to file\n\n");
                }
                else if (strcmp(act2, "name") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
                    char name_to_find[50];
                    printf("Enter student NAME: ");
                    if (scanf("%s", name_to_find) != 1)
                    {
                        printf("Enter a valid char for Name.\n\n");
                        continue;
                    }
                    for (size_t i = 0; i < count; i++)
                    {
                        Student *found_student = find_student_by_name(students, i, name_to_find);
                        if (found_student != NULL)
                        {
                            fprintf(output_file, "Student find by Name: %s ----> ", name_to_find);
                            write_student_info_to_file(output_file, found_student);
                            fflush(output_file);
                            free(found_student);
                        }
                        i++;
                    }
                    printf("Result write to file\n\n");
                }
                else if (strcmp(act2, "surname") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
                }
                else if (strcmp(act2, "group") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
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
            else if (strcmp(act, "sort") == 0)
            {
                fgets(act, sizeof(act), stdin);
                char act3[10];
                printf("Choose. Sort by:\n");
                printf("<id>  - sort a student by id\n");
                printf("<name> - sort a student by name\n");
                printf("<surname> - sort a student by surname\n");
                printf("<group> - sort a student by group \n");
                printf("<back> - back\n\n");
                printf("ENTER ----> ");
                scanf("%s", act3);
                if (strcmp(act3, "id") == 0)
                {
                    fgets(act3, sizeof(act3), stdin);
                }
                else if (strcmp(act3, "name") == 0)
                {
                    fgets(act3, sizeof(act3), stdin);
                }
                else if (strcmp(act3, "surname") == 0)
                {
                    fgets(act3, sizeof(act3), stdin);
                }
                else if (strcmp(act3, "group") == 0)
                {
                    fgets(act3, sizeof(act3), stdin);
                }
                else if (strcmp(act3, "back") == 0)
                {
                    continue;
                }
                else
                {
                    printf("There is no such action. Try again\n\n");
                }
            }
            else if (strcmp(act, "write") == 0)
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

        for (size_t i = 0; i < count; i++)
        {
            free(students[i].grades);
        }
        free(students);
        fflush(output_file);
        fclose(input_file);
        fclose(output_file);
    }
    printf("M8O-211B-22  Mashrabova  lab3 tack5\n");
    return 0;
}
