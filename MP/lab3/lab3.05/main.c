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

        // на консоли: 1) выбор действия - найти студента, сортировка по, печать инфрмации о студенте.
        // найти лучшего- печать всего
        // после этого выбора - следующий выбор по чему искать/сортировать
        while (1)
        {
            char act[10];
            printf("Choose an action:\n");
            printf("<add>  - ADD a mail to the post office\n");
            printf("<delete> - DELETE a mail to the post office\n");
            printf("<search> - SEARCH by id Mail\n");
            printf("<sort> - SORT a mail to the post office\n");
            printf("<time> - SEARCH for mails where delivery time has expired\n");
            printf("<print> - printing of all delivered\n");
            printf("<exit> - exit\n\n");
            printf("ENTER ----> ");
            scanf("%s", act);

            if (strcmp(act, "add") == 0)
            {
                fgets(act, sizeof(act), stdin);
            }

            else if (strcmp(act, "delete") == 0)
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
        fclose(input_file);
        fclose(output_file);
    }
    printf("M8O-211B-22  Mashrabova  lab3 tack5\n");
    return 0;
}
