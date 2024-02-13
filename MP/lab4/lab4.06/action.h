
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

typedef enum check_data
{
    correct_data,
    file_open_error,
    stack_is_empty,
    no_brackets,
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
    void *current;
    struct Stack *next;
} Stack;

void free_stack(Stack *stack);
void free_tree(Node *node);                 //+
check_data push(Stack **stack, void *data); //+
check_data pop(Stack **stack, void **data); //+
check_data create_node(Node **node, const char data, Node *left, Node *right);
void print_tree(Node *node, int level);
int bracket_balance(char *str);        //+
int priority_operators(char operator); //+
check_data conversion_to_postfix(char *str, char **postfix);
check_data create_tree(Node **root, char *postfix);
check_data read_input(char *file);

#endif
