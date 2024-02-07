
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

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
    char BDate[11];
    char gender;
    double income;
} Liver;

// одн.список
typedef struct Node
{
    Liver liver;
    struct Node *next;
} Node;

typedef struct Action
{
    Liver liver_act; 
    char type; //добавление-удаление-изменение
    struct Action *next;
} Action;

int valid_date(const char *date);
check_data valid_data(const char *name, const char *surname, const char *patronymic, const char *BDate, char gender, double income);
int compare_bdates(const char *date1, const char *date2);
check_data read_input(FILE *file, Node **head);
void print_list(Node *head);
#endif
