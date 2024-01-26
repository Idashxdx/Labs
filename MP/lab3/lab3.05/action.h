
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
    char group[11];
    unsigned char *marks;
} Student;

#endif
