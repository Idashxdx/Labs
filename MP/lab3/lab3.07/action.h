
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
    char name[50];
    char surname[50];
    char patronymic[50];
    char BDate[10];
    char gender;
    double income;
} Liver;
typedef struct Node
{
    Liver liver;
    struct Node *next;
} Node;

#endif
