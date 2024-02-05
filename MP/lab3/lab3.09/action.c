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
void find_str(Node *node, int *result, char *str, int found)
{
    if (!node)
    {
        return;
    }
    if (strcmp(node->data, str) == 0) // если нашли - присваеваем количество - нет то рекурсивно вызываем по левому и правому поддереву
    {
        (*result) = node->count;
        found = 1;
        return;
    }
    if (!found)
    {
        find_str(node->left, result, str, found);
        find_str(node->right, result, str, found);
    }
}
check_data sort_node(Node **node, char *str, int count, int order)
{
    if (!(*node))
    {
        (*node) = (Node *)malloc(sizeof(Node));
        if (!(*node))
        {
            return memory_alloc_error;
        }
        size_t size = strlen(str);
        (*node)->size = size;
        (*node)->data = (char *)malloc(sizeof(char) * size);
        if (!(*node)->data)
        {
            return memory_alloc_error;
        }
        memcpy((*node)->data, str, size);
        (*node)->data[size] = '\0';
        (*node)->count = count;
        (*node)->left = NULL;
        (*node)->right = NULL;
        return correct_data;
    }
    if (order == 0) // для поиска и вывода в зависимости от количества одинаковых слов
    {
        if (count > (*node)->count)
        {
            return sort_node(&((*node)->right), str, count, order);
        }
        else
        {
            return sort_node(&((*node)->left), str, count, order);
        }
    }
    else if (order == 1) // для поиска и вывода самого длинного и короткого слова
    {
        if (strlen(str) > (*node)->size)
        {
            return sort_node(&((*node)->right), str, count, order);
        }
        else
        {
            return sort_node(&((*node)->left), str, count, order);
        }
    }
}
check_data sort_tree(Node **node_sort, Node *node, int order)
{
    if (!node)
    {
        return correct_data;
    }
    if (sort_tree(node_sort, node->left, order) == memory_alloc_error ||
        sort_tree(node_sort, node->right, order) == memory_alloc_error)
    {
        return memory_alloc_error;
    }
    if (sort_node(node_sort, node->data, node->count, order) == memory_alloc_error)
    {
        return memory_alloc_error;
    }
    return correct_data;
}
void print_most_common(Node *node_sort, int *counter_up_to_n, unsigned int n)
{
    if (!node_sort)
    {
        return;
    }
    if (*counter_up_to_n == n)
    {
        return;
    }
    print_most_common(node_sort->right, counter_up_to_n, n);
    if (*counter_up_to_n < n)
    {
        printf("%d. The word '%s' in the text ---> %d \n", *counter_up_to_n + 1, node_sort->data, node_sort->count);
        (*counter_up_to_n)++;
    }
    print_most_common(node_sort->left, counter_up_to_n, n);
}
void print_short(Node *node_sort)
{
    while (node_sort->left)
    {
        node_sort = node_sort->left;
    }
    printf("The shortest word ---> %s\n", node_sort->data);
}
void print_long(Node *node_sort)
{
    while (node_sort->right)
    {
        node_sort = node_sort->right;
    }
    printf("The longest word ---> %s\n", node_sort->data);
}
int depth_calculation(Node *node)
{
    if (!node)
    {
        return 0;
    }
    // вычисляем глубину каждого поддерева и сравниваем - выводим большее +1(сам узел)
    int left = depth_calculation(node->left);
    int right = depth_calculation(node->right);
    if (left > right)
    {
        return left + 1;
    }
    else
    {
        return right + 1;
    }
}
void print_node(FILE *file, Node *node, int level)
{
    if (!node)
    {
        return;
    }
    for (int i = 0; i < level; i++)
    {
        fprintf(file, "   |");
    }
    fprintf(file, "-- %d %s\n", node->count, node->data);
    print_node(file, node->left, level + 1);
    print_node(file, node->right, level + 1);
}
check_data read_file_tree(FILE *file, Node **node)
{
    char *file_str = NULL;
    (*node) = NULL;
    size_t lenght = 0;
    char *str = NULL;
    while (getline(&file_str, &lenght, file) != -1)
    {
        int count = 0;
        str = (char *)malloc(strlen(file_str) + 1);
        sscanf(file_str, "%*[^0-9]%d %s", &count, str); // игнорируем до count другие символы
        for (int i = 0; i < count; i++)
        {
            if (create_node(node, str) == memory_alloc_error)
            {
                free(str);
                free(file_str);
                return memory_alloc_error;
            }
        }
        free(str);
        free(file_str);
        file_str = NULL;
    }
    return correct_data;
}