
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define EPSILON 1e-9
// проверка
typedef enum check_data
{
    correct_data,
    incorrect_data,
    memory_alloc_error
} check_data;

typedef struct
{
    unsigned int id;
    char name[50];
    char surname[50];
    char group[10];
    unsigned char *grades;
} Student;

check_data read_input(FILE *file, Student **students, size_t *count, size_t *capacity, double *count_grades, double *summ_grades, double *average_grades);
Student *find_student_by_id(Student *students, size_t count, unsigned int id);
Student *find_student_by_name(Student *students, size_t count,char *name);
void write_student_info_to_file(FILE *file, Student *student);
#endif
