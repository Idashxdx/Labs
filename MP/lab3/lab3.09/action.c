#include "action.h"
void free_node(Node *node)
{
    if (!node)
    {
        return;
    }
    free_node(node->left);
    free_node(node->right);
    free(node->data);
    free(node);
}
check_data create_node(Node **node, char *str)
{
    if (!(*node))
    {
        (*node) = (Node *)malloc(sizeof(Node));
        if (!(*node))
        {
            return memory_alloc_error;
        }
        size_t size_str = strlen(str);
        (*node)->size = size_str;
        (*node)->data = (char *)malloc(sizeof(char) * size_str);
        if (!(*node)->data)
        {
            return memory_alloc_error;
        }
        memcpy((*node)->data, str, size_str);
        (*node)->data[size_str] = '\0';
        (*node)->count = 1;
        (*node)->left = NULL;
        (*node)->right = NULL;
        return correct_data;
    }
    // если уже существует слово - добавляем к нему
    if ((strcmp((*node)->data, str)) == 0)
    {
        (*node)->count++;
    }
    else if ((strcmp((*node)->data, str)) > 0)
    {
        return create_node(&(*node)->left, str);
    }
    else if ((strcmp((*node)->data, str)) < 0)
    {
        return create_node(&(*node)->right, str);
    }
}
check_data create_tree(FILE *file, char **separators, int count, Node **node)
{

    for (int i = 2; i < count; i++)
    {
        if (strlen(separators[i]) > 1) // сепаратор - 1 символ.
        {
            return incorrect_data;
        }
    }
    size_t size = 0;
    size_t capacity = 2;
    char symbol = fgetc(file);
    char current_sep;    // текущий символ-разделитель
    int counter_sep = 0; // счетчик разделителей
    char *str = (char *)malloc(sizeof(char) * capacity);
    if (!str)
    {
        return memory_alloc_error;
    }
    while (symbol != EOF)
    {
        for (int i = 2; i < count; i++)
        {
            if (symbol == separators[i][0])
            {
                counter_sep = 1;
                current_sep = separators[i][0];
                while (current_sep == symbol && symbol != EOF)
                {
                    symbol = fgetc(file);
                }
            }
        }
        if (symbol == EOF)
        {
            return correct_data;
        }
        if (strlen(str) && counter_sep)
        {
            fseek(file, -1, SEEK_CUR);
            str[size] = '\0';
            if (create_node(node, str) == memory_alloc_error)
            {
                return memory_alloc_error;
            }
            free(str);
            str = NULL;
            size = 0;
            capacity = 2;
            str = (char *)malloc(sizeof(char) * capacity);
            if (!str)
            {
                free_node(*node);
                return memory_alloc_error;
            }
            symbol = fgetc(file);
            counter_sep = 0;
            continue;
        }
        str[size] = symbol;
        size++;
        if (size >= capacity)
        {
            capacity *= 2;
            char *tmp = NULL;
            if (!(tmp = (char *)realloc(str, sizeof(char) * capacity)))
            {
                free(str);
                free_node(*node);
                return memory_alloc_error;
            }
            str = tmp;
        }
        symbol = fgetc(file);
    }
    if (strlen(str))
    {
        str[size] = '\0';
        if (create_node(node, str) == memory_alloc_error)
        {
            return memory_alloc_error;
        }
    }
    free(str);
    return correct_data;
}
