#include "action.h"
check_data read_input(FILE *file, Student **students, size_t *count, size_t *capacity, double *count_grades, double *summ_grades, double *average_grades)
{

    *students = (Student *)malloc(sizeof(Student) * (*capacity));
    if (!(*students))
    {
        return memory_alloc_error;
    }

    for (size_t i = 0; i < *capacity; i++)
    {
        (*students)[i].grades = (unsigned char *)malloc(5 * sizeof(unsigned char));
        if (!(*students)[i].grades)
        {
            for (size_t j = 0; j < i; j++)
            {
                free((*students)[j].grades);
            }
            free(*students);
            return memory_alloc_error;
        }
    }

    size_t i = 0;

    while (fscanf(file, "%u %s %s %s %hhu %hhu %hhu %hhu %hhu",
                  &((*students)[i].id),
                  (*students)[i].name,
                  (*students)[i].surname,
                  (*students)[i].group,
                  &((*students)[i].grades[0]),
                  &((*students)[i].grades[1]),
                  &((*students)[i].grades[2]),
                  &((*students)[i].grades[3]),
                  &((*students)[i].grades[4])) == 9)
    {
        double sum = 0; // средняя оценка 1 студента
        for (size_t j = 0; j < 5; j++)
        {
            sum += (*students)[i].grades[j];
        }
        *summ_grades += sum;
        *count_grades += 5;

        i++;

        if (i >= *capacity)
        {
            *capacity *= 2;
            Student *temp = (Student *)realloc(*students, sizeof(Student) * (*capacity));
            if (!temp)
            {
                for (size_t j = 0; j < i; j++)
                {
                    free((*students)[j].grades);
                }
                free(*students);
                return memory_alloc_error;
            }
            *students = temp;

            for (size_t k = i; k < *capacity; k++)
            {
                (*students)[k].grades = (unsigned char *)malloc(5 * sizeof(unsigned char));
                if (!(*students)[k].grades)
                {
                    for (size_t j = 0; j < k; j++)
                    {
                        free((*students)[j].grades);
                    }
                    free(*students);
                    return memory_alloc_error;
                }
            }
        }
    }

    if (i == 0) // если не удалось корректно считать из файла
    {
        return incorrect_data;
    }

    *count = i;
    *average_grades = (*summ_grades) / (*count_grades);

    return correct_data;
}
Student *find_student_by_id(Student *students, size_t count, unsigned int id)
{

    if (students[count].id == id)
    {
        return &students[count];
    }
    else
    {
        return NULL; // Студент не найден
    }
}
Student *find_student_by_name(Student *students, size_t count, char *name)
{
    if (strcmp(students[count].name, name) == 0)
    {
        return &students[count];
    }
    else
    {
        return NULL; // Студент не найден
    }
}
Student *find_student_by_surname(Student *students, size_t count, char *surname)
{
    if (strcmp(students[count].surname, surname) == 0)
    {
        return &students[count];
    }
    else
    {
        return NULL; // Студент не найден
    }
}
Student *find_student_by_group(Student *students, size_t count, char *group)
{

    if (strcmp(students[count].group, group) == 0)
    {
        return &students[count];
    }
    else
    {
        return NULL; // Студент не найден
    }
}
void write_student_info_to_file(FILE *file, Student *student)
{
    fprintf(file, "ID: %u; Name: %s; Surname: %s; Group: %s; Grades: %hhu %hhu %hhu %hhu %hhu; \n\n",
            student->id, student->name, student->surname, student->group,
            student->grades[0], student->grades[1], student->grades[2], student->grades[3], student->grades[4]);
}