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
        switch (read_input(input_file, &students, &count, &capacity))
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
        fprintf(output_file, "Student: \n");
        fflush(output_file);
        write_all(output_file, count, students);
        fflush(output_file);
        while (1)
        {
            char act[10];
            printf("Choose an action:\n");
            printf("<find>  - find a student by ...\n");
            printf("<sort> - sort students by ...\n");
            printf("<write> - write to file: best student, student's GPA\n"); // вывод лучшего студента или студента по индексу и его средний балл
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
                    int found = 0;
                    for (size_t i = 0; i < count; i++)
                    {
                        Student *found_student = find_student_by_id(students, i, id_to_find);
                        if (found_student != NULL)
                        {
                            fprintf(output_file, "Student find by id: %u ----> ", id_to_find);
                            write_student_info_to_file(output_file, found_student);
                            // сброс буфера - что бы не хранилось после записи.
                            fflush(output_file);
                            found = 1;
                        }
                        i++;
                    }
                    if (!found) // если студент не был найден
                    {
                        fprintf(output_file, "Student with id %u not found\n", id_to_find);
                        fflush(output_file);
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
                    int found = 0;
                    for (size_t i = 0; i < count; i++)
                    {
                        Student *found_student = find_student_by_name(students, i, name_to_find);
                        if (found_student != NULL)
                        {
                            fprintf(output_file, "Student find by Name: %s ----> ", name_to_find);
                            write_student_info_to_file(output_file, found_student);
                            fflush(output_file);
                            found = 1;
                        }
                        i++;
                    }
                    if (!found) // если студент не был найден
                    {
                        fprintf(output_file, "Student with name %s not found\n", name_to_find);
                        fflush(output_file);
                    }
                    printf("Result write to file\n\n");
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
                    int found = 0;
                    for (size_t i = 0; i < count; i++)
                    {
                        Student *found_student = find_student_by_surname(students, i, surname_to_find);
                        if (found_student != NULL)
                        {
                            fprintf(output_file, "Student find by surname: %s ----> ", surname_to_find);
                            write_student_info_to_file(output_file, found_student);
                            fflush(output_file);
                            found = 1;
                        }
                        i++;
                    }
                    if (!found)
                    {
                        fprintf(output_file, "Student with surname %s not found\n", surname_to_find);
                        fflush(output_file);
                    }
                    printf("Result write to file\n\n");
                }
                else if (strcmp(act2, "group") == 0)
                {
                    fgets(act2, sizeof(act2), stdin);
                    char group_to_find[50];
                    printf("Enter student group: ");
                    if (scanf("%s", group_to_find) != 1)
                    {
                        printf("Enter a valid char for group.\n\n");
                        continue;
                    }
                    int found = 0;
                    for (size_t i = 0; i < count; i++)
                    {
                        Student *found_student = find_student_by_group(students, i, group_to_find);
                        if (found_student != NULL)
                        {
                            fprintf(output_file, "Student find by group: %s ----> ", group_to_find);
                            write_student_info_to_file(output_file, found_student);
                            fflush(output_file);
                            found = 1;
                        }
                        i++;
                    }
                    if (!found)
                    {
                        fprintf(output_file, "Student with group %s not found\n", group_to_find);
                        fflush(output_file);
                    }
                    printf("Result write to file\n\n");
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
                    qsort(students, count, sizeof(students[0]), compare_id);
                    fprintf(output_file, "Sort by id: \n\n");
                    fflush(output_file);
                    write_all(output_file, count, students);
                    fflush(output_file);
                    printf("Students sort and write to file\n\n");
                }
                else if (strcmp(act3, "name") == 0)
                {
                    fgets(act3, sizeof(act3), stdin);
                    qsort(students, count, sizeof(students[0]), compare_name);
                    fprintf(output_file, "Sort by name: \n\n");
                    fflush(output_file);
                    write_all(output_file, count, students);
                    fflush(output_file);
                    printf("Students sort and write to file\n\n");
                }
                else if (strcmp(act3, "surname") == 0)
                {
                    fgets(act3, sizeof(act3), stdin);
                    qsort(students, count, sizeof(students[0]), compare_surname);
                    fprintf(output_file, "Sort by surname: \n\n");
                    fflush(output_file);
                    write_all(output_file, count, students);
                    fflush(output_file);
                    printf("Students sort and write to file\n\n");
                }
                else if (strcmp(act3, "group") == 0)
                {
                    fgets(act3, sizeof(act3), stdin);
                    qsort(students, count, sizeof(students[0]), compare_group);
                    fprintf(output_file, "Sort by group: \n\n");
                    fflush(output_file);
                    write_all(output_file, count, students);
                    fflush(output_file);
                    printf("Students sort and write to file\n\n");
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
                char act4[10];
                printf("Choose. Write:\n");
                printf("<best>  - write in file best student\n");
                printf("<gpa> - student's average exam score by id\n");
                printf("<gpa_all> - all student's average exam\n");
                printf("<back> - back\n\n");
                printf("ENTER ----> ");
                scanf("%s", act4);
                if (strcmp(act4, "best") == 0)
                {
                    fgets(act4, sizeof(act4), stdin);
                    double total_sum = 0;
                    size_t total_count = 0;
                    Student best_student;
                    double best_average = 0;
                    double average_grades = 0;
                    for (size_t i = 0; i < count; i++)
                    {
                        double sum = 0;
                        double count = 0;
                        for (size_t j = 0; j < 5; j++)
                        {
                            sum += students[i].grades[j];
                            count++;
                        }
                        double average = sum / count;
                        total_sum += sum;
                        total_count += count;
                        if (average > best_average)
                        {
                            best_average = average;
                            best_student = students[i];
                        }
                    }
                    average_grades = total_sum / total_count;
                    fprintf(output_file, "Best student ---> id: %u; %s %s; Group: %s; ---> %f\n", best_student.id, best_student.name, best_student.surname, best_student.group, best_average);
                    fflush(output_file);
                    printf("Result write to file\n\n");
                }
                else if (strcmp(act4, "gpa") == 0)
                {
                    fgets(act4, sizeof(act4), stdin);
                    char input[50];
                    unsigned int id_to_find;
                    printf("Enter student ID: ");
                    fgets(input, sizeof(input), stdin);
                    if (sscanf(input, "%u", &id_to_find) != 1)
                    {
                        printf("Enter a valid unsigned int for ID.\n\n");
                        continue;
                    }
                    int found = 0;
                    for (size_t i = 0; i < count; i++)
                    {
                        Student *found_student = find_student_by_id(students, i, id_to_find);
                        if (found_student != NULL)
                        {
                            double sum = 0;
                            double count = 0;
                            for (size_t j = 0; j < 5; j++)
                            {
                                sum += found_student->grades[j];
                                count++;
                            }
                            fprintf(output_file, "Average grades student by id: %u; %s; Group: %s; ---> %f\n", id_to_find, found_student->surname, found_student->group, sum / count);
                            fflush(output_file);
                            found = 1;
                        }
                        i++;
                    }
                    if (!found) // если студент не был найден
                    {
                        fprintf(output_file, "Student with id %u not found\n", id_to_find);
                        fflush(output_file);
                    }
                    printf("Result write to file\n\n");
                }
                else if (strcmp(act4, "gpa_all") == 0)
                {
                    fgets(act4, sizeof(act4), stdin);
                    double total_sum = 0;
                    size_t total_count = 0;
                    for (size_t i = 0; i < count; i++)
                    {
                        for (size_t j = 0; j < 5; j++)
                        {
                            total_sum += students[i].grades[j];
                            total_count++;
                        }
                    }
                    double average_grade_all = total_sum / total_count;

                    fprintf(output_file, "Students with above average GPA for all exams:\n");
                    fflush(output_file);
                    for (size_t i = 0; i < count; i++)
                    {
                        double sum = 0;
                        for (size_t j = 0; j < 5; j++)
                        {
                            sum += students[i].grades[j];
                        }
                        double student_average = sum / 5;

                        if (student_average > average_grade_all)
                        {
                            fprintf(output_file, "%s %s\n", students[i].surname, students[i].name);
                            fflush(output_file);
                        }
                    }
                    printf("Result write to file\n\n");
                }
                else if (strcmp(act4, "back") == 0)
                {
                    continue;
                }
                else
                {
                    printf("There is no such action. Try again\n\n");
                }
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
