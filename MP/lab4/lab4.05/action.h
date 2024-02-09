
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum check_data
{
    correct_data,
    file_open_error,
    stack_is_empty,
    incorrect_data,
    memory_alloc_error,
    div_by_zero,
    negative_degree

} check_data;
typedef struct Node
{
    int data;
    char operator;
    struct Node *next;
} Node;

typedef struct Stack
{
    struct Node *top;
} Stack;

void free_stack(Stack *stack);
check_data push(Stack *stack, int data, char operator);
check_data pop(Stack *stack, int *data, char *operator);

int bracket_balance(char *str);
int priority_operators(char operator);

check_data conversion_to_postfix(char *str, char **postfix);
check_data calculation(char *str, int *result);
check_data read_input(int count, char *files[]);

#endif
