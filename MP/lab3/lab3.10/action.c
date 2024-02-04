#include "action.h"
check_data create_node(Node **node, char key)
{
    *node = (Node *)malloc(sizeof(Node));
    if (*node == NULL)
    {
        return memory_malloc_error;
    }

    (*node)->key = key;
    (*node)->parent = NULL;
    (*node)->brother = NULL;
    (*node)->children = NULL;
    return correct_data;
}
check_data create_children(Node *node, char key, Node **current)
{

    if (node == NULL)
    {
        return incorrect_data;
    }
    check_data check = correct_data;
    Node *new_node = NULL;
    check = create_node(&new_node, key);
    if (check != correct_data && !new_node)
    {
        if (new_node)
        {
            free(new_node);
        }
        return memory_malloc_error;
    }
    new_node->parent = node;
    if (node->children == NULL)
    {
        node->children = new_node;
    }
    else
    {
        Node *tmp = node->children;
        while (tmp->brother != NULL)
        {
            tmp = tmp->brother;
        }
        tmp->brother = new_node;
    }
    if (*current != NULL)
    {
        *current = new_node;
    }
    return check;
}
check_data create_tree(Tree *tree, char *str)
{
    if (str == NULL || tree == NULL)
    {
        return incorrect_data;
    }
    Node *parent = NULL;
    Node *current = NULL;
    Node *add = NULL;
    int key = 1;
    int i = 0;
    check_data check = correct_data;
    while (str[i] != '\0' && check == correct_data)
    {
        while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        {
            i++;
        }

        if (key)
        {
            key = 0;
            if (current == NULL)
            {
                check = create_node(&(tree->root), str[i]);
                if (check != correct_data || !(tree->root))
                {
                    return memory_malloc_error;
                }
                current = tree->root;
                add = tree->root;
            }
            else
            {
                check = create_children(current, str[i], &add);
            }
        }
        else
        {
            key = 1;
            if (str[i] == '(')
            {
                current = add;
            }
            else if (str[i] == ')')
            {
                current = current->parent;
                key = 0;
            }
        }
        i++;
    }
    return check;
}
void delete_tree(Node *node)
{
    if (!node)
    {
        return;
    }
    delete_tree(node->children);
    delete_tree(node->brother);
    free(node);
}
void print_tree(FILE *file, Node *node, int level)
{
    if (node == NULL)
    {
        return;
    }
    for (int i = 0; i < level; ++i)
    {
        fprintf(file, "   ");
    }
    fprintf(file, "%c\n", node->key);
    print_tree(file, node->children, level + 1);
    print_tree(file, node->brother, level);
}