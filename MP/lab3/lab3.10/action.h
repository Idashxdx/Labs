
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

typedef struct Node
{
    char key;
    struct Node *parent;
    struct Node *children;
    struct Node *left;
    struct Node *right;
} Node;
typedef struct Tree
{
    Node *root;
} Tree;

typedef enum check_data
{
    correct_data,
    incorrect_data,
    memory_malloc_error
} check_data;

check_data create_tree(Tree* tree, char* str);
#endif