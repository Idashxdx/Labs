#include "action.h"

void free_stack(Stack *stack)
{
    if (!stack)
    {
        return;
    }
    free_stack(stack->next);
    free(stack);
}
void free_tree(Node *node)
{
    if (!node)
    {
        return;
    }
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}
check_data push(Stack **stack, void *data)
{
    Stack *new_node = (Stack *)malloc(sizeof(Stack));
    if (!new_node)
    {
        return memory_alloc_error;
    }

    new_node->current = data;
    new_node->next = (*stack);
    (*stack) = new_node;
    return correct_data;
}
check_data pop(Stack **stack, void **data)
{
    if ((*stack) == NULL)
    {
        return stack_is_empty;
    }

    Stack *top_node = (*stack);
    (*stack) = top_node->next;
    (*data) = top_node->current;
    free(top_node);
    return correct_data;
}
check_data create_node(Node **node, const char data, Node *left, Node *right)
{
    if (*node)
    {
        return stack_is_empty;
    }
    *node = (Node *)malloc(sizeof(Node));
    if (!(*node))
    {
        return memory_alloc_error;
    }
    (*node)->data = data;
    (*node)->left = left;
    (*node)->right = right;
    return correct_data;
}
int bracket_balance(char *str)
{
    int length = strlen(str);
    int bracket = 0;
    for (int i = 0; i < length; i++)
    {
        if (str[i] == '(')
        {
            bracket++;
        }
        else if (str[i] == ')')
        {
            bracket--;
            if (bracket < 0)
            {
                return 0;
            }
        }
    }
    return bracket == 0;
}
int priority_operators(char operator)
{
    switch (operator)
    {
    case '|':
    case '>':
    case '<':
    case '=':
        return 1;
    case '?':
    case '!':
    case '+':
    case '&':
        return 2;
    case '~':
        return 3;
    default:
        return -1;
    }
}
check_data conversion_to_postfix(char *str, char **postfix)
{
    int length = strlen(str);
    char *result = (char *)malloc(sizeof(char) * (length + 1));
    if (!result)
    {
        return memory_alloc_error;
    }
    Stack *stack = NULL;
    int p = 0;
    check_data push_result, pop_result;
    for (int i = 0; i < length; i++)
    {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t')
        {
            continue;
        }
        if (isalpha(str[i]) || str[i] == '0' || str[i] == '1')
        {
            result[p] = str[i];
            p++;
        }
        else
        {
            if (str[i] == ')')
            {
                while (1)
                {
                    void *current = NULL;
                    pop_result = pop(&stack, &current);
                    if (pop_result != correct_data)
                    {
                        free(result);
                        free_stack(stack);
                        return pop_result;
                    }
                    char current_char = *(char *)current;
                    if (current_char == '(')
                    {
                        break;
                    }
                    result[p] = current_char;
                    p++;
                }
            }
            else if (str[i] == '(')
            {
                push_result = push(&stack, &str[i]);
                if (push_result != correct_data)
                {
                    free(result);
                    free_stack(stack);
                    return push_result;
                }
            }
            else
            {
                if (str[i] == '+' || str[i] == '-' || str[i] == '<')
                {
                    if (str[i + 1] != '>')
                    {
                        return incorrect_data;
                    }
                }
                if (str[i] == '>')
                {
                    if (str[i - 1] != '+' && str[i - 1] != '-' && str[i - 1] != '<')
                    {
                        return incorrect_data;
                    }
                    continue;
                }
                int priority = priority_operators(str[i]);
                if (priority == -1)
                {
                    free_stack(stack);
                    free(result);
                    return incorrect_data;
                }
                while (stack && priority_operators(*(char *)(stack->current)) > priority)
                {
                    void *current = NULL;
                    if (pop(&stack, &current) == stack_is_empty)
                    {
                        break;
                    }
                    char current_char = *(char *)current;
                    result[p] = current_char;
                    p++;
                }
                push_result = push(&stack, &str[i]);
                if (push_result != correct_data)
                {
                    free(result);
                    free_stack(stack);
                    return push_result;
                }
            }
        }
    }
    void *current = NULL;
    while (pop(&stack, &current) != stack_is_empty)
    {
        char current_char = *(char *)current;
        if (current_char == '(')
        {
            free_stack(stack);
            free(result);
            return incorrect_data;
        }
        result[p] = current_char;
        p++;
    }

    result[p] = '\0';
    free_stack(stack);
    *postfix = result;
    return correct_data;
}
check_data create_tree(Node **root, char *postfix)
{
    int length = strlen(postfix);
    Stack *stack = NULL;
    check_data push_result, pop_result;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(postfix[i]) || postfix[i] == '0' || postfix[i] == '1')
        {
            Node *new_node = NULL;
            if (create_node(&new_node, postfix[i], NULL, NULL) != correct_data)
            {
                free_stack(stack);
                return memory_alloc_error;
            }
            push_result = push(&stack, new_node);
            if (push_result != correct_data)
            {
                free_stack(stack);
                return push_result;
            }
        }
        else
        {
            Node *result_node = NULL;
            Node *data1, *data2;
            check_data result;
            if (postfix[i] == '~')
            {
                result = create_node(&result_node, postfix[i], data1, NULL);
            }
            else
            {
                pop_result = pop(&stack, (void **)&data2);
                if (pop_result != correct_data)
                {
                    free_stack(stack);
                    return pop_result;
                }

                pop_result = pop(&stack, (void **)&data1);
                if (pop_result != correct_data)
                {
                    free_stack(stack);
                    return pop_result;
                }
                result = create_node(&result_node, postfix[i], data2, data1);
            }
            if (result != correct_data)
            {
                free_stack(stack);
                return result;
            }
            push_result = push(&stack, &result_node);
            if (push_result != correct_data)
            {
                free_stack(stack);
                return push_result;
            }
        }
    }
    void *current = NULL;
    if (pop(&stack, &current) == stack_is_empty)
    {
        free_stack(stack);
        return stack_is_empty;
    }
    *root = (Node *)current;
    if (stack)
    {
        free_stack(stack);
        return incorrect_data;
    }
    return correct_data;
}
// Функция для вычисления значения булевой переменной по ее имени и позиции в таблице
bool eval_variable(char name, int index)
{
    return (index >> (name - 'A')) & 1;
}

// Функция для вычисления значения булевой формулы с использованием построенного дерева
bool evaluate_expression(Node *node, int index)
{
    if (node->data == '1')
    {
        return true;
    }
    if (node->data == '0')
    {
        return false;
    }
    if (isalpha(node->data))
    {
        return eval_variable(node->data, index);
    }
    bool left_value = evaluate_expression(node->left, index);
    bool right_value = evaluate_expression(node->right, index);

    switch (node->data)
    {
    case '&':
        return left_value && right_value;
    case '|':
        return left_value || right_value;
    case '~':
        return !right_value;
        // Добавь обработку остальных операторов по аналогии
    }

    return false;
}

// Функция для печати таблицы истинности
void print_truth_table(Node *root, int num_variables)
{
    printf("Truth Table:\n");

    // Вывод заголовка таблицы с переменными
    for (char c = 'A'; c < 'A' + num_variables; c++)
    {
        printf("%c ", c);
    }
    printf("| Result\n");

    // Вывод значений переменных и результат для каждой комбинации
    int total_combinations = 1 << num_variables; // 2^num_variables
    for (int i = 0; i < total_combinations; i++)
    {
        for (int j = num_variables - 1; j >= 0; j--)
        {
            printf("%d ", eval_variable('A' + j, i));
        }
        printf("| %d\n", evaluate_expression(root, i));
    }
}
check_data read_input(char *file)
{
    FILE *file_input = fopen(file, "r");
    if (!file_input)
    {
        return file_open_error;
    }

    char *str = NULL;
    size_t size = 0;
    check_data postfix_res, tree_res;

    if (getline(&str, &size, file_input) == -1)
    {
        fclose(file_input);
        return incorrect_data;
    }
    int str_length = strlen(str);
    for (int j = 0; j < str_length; j++)
    {
        if (str[j] == '\n')
        {
            str[j] = '\0';
        }
    }
    if (bracket_balance(str) == 0)
    {
        free(str);
        fclose(file_input);
        return no_brackets;
    }
    char *postfix = NULL;
    postfix_res = conversion_to_postfix(str, &postfix);
    if (postfix_res != correct_data)
    {
        free(str);
        free(postfix);
        fclose(file_input);
        return postfix_res;
    }
    Node *root = NULL;
    tree_res = create_tree(&root, postfix);
    if (tree_res != correct_data)
    {
        free(str);
        free(postfix);
        fclose(file_input);
        return tree_res;
    }
    // здесь надо сделать печать
    // Определение количества уникальных переменных в выражении
    int num_variables = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (isalpha(str[i]) && strchr(str, str[i]) == &str[i])
        {
            num_variables++;
        }
    }

    // Печать таблицы истинности
    print_truth_table(root, num_variables);

    free(str);
    free_tree(root);
    free(postfix);
    fclose(file_input);
    return correct_data;
}
