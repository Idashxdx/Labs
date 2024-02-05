
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
void find_str(Node *node, int *result, char *str, int found);
check_data sort_node(Node **node,char *str, int count, int order);
check_data sort_tree(Node **node_sort, Node *node, int order);
void print_most_common(Node *node_sort, int *counter_up_to_n,unsigned int n);
void print_short(Node *node_sort);
void print_long(Node *node_sort);
int depth_calculation(Node *node);
void print_node(FILE *file, Node *node, int level);
check_data read_file_tree(FILE *file,Node **node);
#endif
