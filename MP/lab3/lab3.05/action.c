#include "action.h"
check_data read_input(FILE *file, Student **students, size_t *count, size_t *capacity)
{
    *students = (Student *)malloc(sizeof(Student) * (*capacity));
    if (!(*students))
    {
        return memory_alloc_error;
    }

    for (size_t i = 0; i < (*capacity); i++)
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

    while (fscanf(file, "%u %s %s %s %hhu %hhu %hhu %hhu %hhu",
                  &((*students)[*count].id),
                  (*students)[*count].name,
                  (*students)[*count].surname,
                  (*students)[*count].group,
                  &((*students)[*count].grades[0]),
                  &((*students)[*count].grades[1]),
                  &((*students)[*count].grades[2]),
                  &((*students)[*count].grades[3]),
                  &((*students)[*count].grades[4])) == 9)
    {
        for (size_t j = 0; j < 5; j++)
        {
            if ((*students)[*count].grades[j] < 2 || (*students)[*count].grades[j] > 5)
            {
                free(*students);
                return incorrect_data;
            }
        }

        (*count)++;

        if ((*count) >= *capacity)
        {
            *capacity *= 2;
            Student *temp = (Student *)realloc(*students, sizeof(Student) * (*capacity));
            if (!temp)
            {
                for (size_t j = 0; j < (*count); j++)
                {
                    free((*students)[j].grades);
                }
                free(*students);
                return memory_alloc_error;
            }
            *students = temp;
            for (size_t k = (*count); k < *capacity; k++)
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

    if ((*count) == 0)
    {
        free(*students);
        return incorrect_data;
    }

    return correct_data;
}

Student *find_student_by_id(Student *students, size_t count, unsigned int id)
{
    for (size_t i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            return &students[i];
        }
    }
    return NULL;
}
Student *find_student_by_name(Student *students, size_t count, char *name)
{
    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(students[i].name, name) == 0)
        {
            return &students[i];
        }
    }
    return NULL;
}
Student *find_student_by_surname(Student *students, size_t count, char *surname)
{
    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(students[i].surname, surname) == 0)
        {
            return &students[i];
        }
    }
    return NULL;
}
Student *find_student_by_group(Student *students, size_t count, char *group)
{
    for (size_t i = 0; i < count; i++)
    {
        if (strcmp(students[i].group, group) == 0)
        {
            return &students[i];
        }
    }
    return NULL;
}
void write_student_info_to_file(FILE *file, Student *student)
{
    fprintf(file, "ID: %u; Name: %s; Surname: %s; Group: %s; Grades: %hhu %hhu %hhu %hhu %hhu\n\n",
            student->id, student->name, student->surname, student->group,
            student->grades[0], student->grades[1], student->grades[2], student->grades[3], student->grades[4]);
}
void write_all(FILE *file, size_t count, Student *students)
{
   for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d --> %u; %s; %s; %s; Grades: %hhu %hhu %hhu %hhu %hhu\n\n",
                i + 1, students[i].id, students[i].name, students[i].surname, students[i].group,
                students[i].grades[0], students[i].grades[1], students[i].grades[2], students[i].grades[3], students[i].grades[4]);
    }
}
int compare_id(const void *one, const void *two)
{
    return ((Student *)one)->id - ((Student *)two)->id;
}
int compare_group(const void *one, const void *two)
{
    return strcmp(((Student *)one)->group, ((Student *)two)->group);
}
int compare_name(const void *one, const void *two)
{
    return strcmp(((Student *)one)->name, ((Student *)two)->name);
}
int compare_surname(const void *one, const void *two)
{
    return strcmp(((Student *)one)->surname, ((Student *)two)->surname);
}