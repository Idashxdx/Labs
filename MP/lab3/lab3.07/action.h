
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

typedef struct Operation
{
    Liver oper_liver; 
    Liver orig_liver;
    char type; //добавление-удаление-изменение
    struct Operation *next;
} Operation;

int valid_date(const char *date);
check_data valid_data(const char *name, const char *surname, const char *patronymic, const char *BDate, char gender, double income);
int compare_bdates(const char *date1, const char *date2);
check_data read_input(FILE *file, Node **head);
Node *find_by_name(Node *head, char *str);
Node *find_by_surname(Node *head, char *str);
Node *find_by_patronymic(Node *head, char *str);
Node *find_by_gender(Node *head, char gender);
Node *find_by_date(Node *head, char *str);
Node *find_by_income(Node *head, double income);
void print_node(Node *node);
void print_all_find(Node *head);
void free_list(Node *head);
check_data add_liver(Node **head, Operation **operation, int *counter_operation);
check_data delete_liver(Node **head, Operation **operation, int *counter_operation);
check_data change_liver(Node *head, Operation **operation, int *counter_operation);
check_data undo(Node **head, Operation **operation, int *counter_operation);
#endif
