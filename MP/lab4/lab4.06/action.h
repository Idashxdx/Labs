
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
    memory_alloc_error

} check_data;

typedef struct Node
{
    char data;
    struct Node *left;
    struct Node *right;

} Node;
typedef struct Stack
{
    char operator;
    struct Stack *next;
} Stack;

void free_stack(Stack *stack);//+
check_data push(Stack **stack, char operator); //+
check_data pop(Stack **stack, char *operator); //+

int bracket_balance(char *str);//+
int priority_operators(char operator);//+


Node *create_node(char data);//+
Node *create_tree(char *postfix);

check_data conversion_to_postfix(char *str, char **postfix);
int evaluate(Node *node, int values);
void print_table(Node *root, int variables_count, char *variables);
check_data read_input(char *file);

#endif
