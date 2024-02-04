
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

typedef struct Node
{
    size_t size;
    char *data;
    int count;
    struct Node *left;
    struct Node *right;
} Node;

void free_node(Node *node);
check_data create_node(Node **node, char *str);
check_data create_tree(FILE *file, char **separators, int count, Node **node);
#endif
