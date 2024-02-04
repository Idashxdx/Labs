
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node
{
    char key;
    struct Node *parent;
    struct Node *brother;
    struct Node *children;
} Node;

typedef struct
{
    Node *root;
} Tree;

typedef enum check_data
{
    correct_data,
    incorrect_data,
    memory_malloc_error
} check_data;

check_data create_node(Node **node, char key);
check_data create_tree(Tree *tree, char *str);
check_data create_children(Node *node, char key, Node **current);
void delete_tree(Node *node);
void print_tree(FILE *file, Node *node, int level);

#endif