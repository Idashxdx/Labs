
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

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

check_data read_input(FILE *file, Student **students, size_t *count, size_t *capacity);
Student *find_student_by_id(Student *students, size_t count, unsigned int id);
Student *find_student_by_name(Student *students, size_t count,char *name);
Student *find_student_by_surname(Student *students, size_t count,char *surname);
Student *find_student_by_group(Student *students, size_t count,char *group);
void write_student_info_to_file(FILE *file, Student *student);
void write_all(FILE *file, size_t count,Student *students);
int compare_id(const void *one, const void *two);
int compare_group(const void *one, const void *two);
int compare_name(const void *one, const void *two);
int compare_surname(const void *one, const void *two);

#endif
