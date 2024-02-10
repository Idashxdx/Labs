#include "action.h"
void free_stack(Stack *stack)
{
    while (stack->top != NULL)
    {
        Node *tmp = stack->top;
        stack->top = tmp->next;
        free(tmp);
    }
    free(stack);
}
check_data push(Stack *stack, int data, char operator)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
    {
        return memory_alloc_error;
    }

    new_node->data = data;
    new_node->operator= operator;
    new_node->next = stack->top;
    stack->top = new_node;
    return correct_data;
}
check_data pop(Stack *stack, int *data, char *operator)
{
    if (stack->top == NULL)
    {
        return stack_is_empty;
    }
    Node *top_node = stack->top;
    *data = top_node->data;
    *operator= top_node->operator;
    stack->top = top_node->next;
    free(top_node);
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
    if (bracket == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int priority_operators(char operator)
{
    switch (operator)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}
check_data conversion_to_postfix(char *str, char **postfix)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
    {
        return memory_alloc_error;
    }
    stack->top = NULL;
    int length = strlen(str);
    int data, number;
    char operator, symbol;
    int position = 0; // postfix position
    check_data push_result, pop_result;
    for (int i = 0; i < length; i++)
    {
        symbol = str[i];
        if (isalpha(symbol) || symbol == '[' || symbol == ']' || symbol == '{' || symbol == '}')
        {
            free_stack(stack);
            return incorrect_data;
        }
        else if (isdigit(symbol) || (symbol == '-' && !isdigit(str[i - 1]) && isdigit(str[i + 1])))
        {
            if (symbol == '-')
            {
                i++;
                number = str[i] - '0';
                while (i + 1 < length && isdigit(str[i + 1]))
                {
                    i++;
                    number = number * 10 + (str[i] - '0');
                }
                number *= -1;
                position += sprintf(*postfix + position, "0 %d - ", abs(number));
            }
            else
            {
                number = str[i] - '0';
                while (i + 1 < length && isdigit(str[i + 1]))
                {
                    i++;
                    number = number * 10 + (str[i] - '0');
                }
                position += sprintf(*postfix + position, "%d ", number);
            }
        }
        else if (symbol == ' ')
        {
            continue;
        }
        else if (symbol == '(')
        {
            push_result = push(stack, 0, symbol);
            if (push_result != correct_data)
            {
                free_stack(stack);
                return push_result;
            }
        }
        else if (symbol == ')')
        {
            while (stack->top != NULL && stack->top->operator!= '(')
            {
                pop_result = pop(stack, &data, &operator);
                if (pop_result != correct_data)
                {
                    free_stack(stack);
                    return pop_result;
                }
                (*postfix)[position] = operator;
                position++;
                (*postfix)[position] = ' ';
                position++;
            }
            if (stack->top == NULL || stack->top->operator!= '(')
            {
                free_stack(stack);
                return incorrect_data;
            }
            pop_result = pop(stack, &data, &operator);
            if (pop_result != correct_data)
            {
                free_stack(stack);
                return pop_result;
            }
        }
        else
        {
            while (stack->top != NULL && priority_operators(stack->top->operator) >= priority_operators(symbol))
            {
                pop_result = pop(stack, &data, &operator);
                if (pop_result != correct_data)
                {
                    free_stack(stack);
                    return pop_result;
                }
                (*postfix)[position] = operator;
                position++;
                (*postfix)[position] = ' ';
                position++;
            }
            push_result = push(stack, 0, symbol);
            if (push_result != correct_data)
            {
                free_stack(stack);
                return push_result;
            }
        }
    }
    while (stack->top != NULL)
    {
        pop(stack, &data, &operator);
        (*postfix)[position] = operator;
        position++;
        (*postfix)[position] = ' ';
        position++;
    }
    (*postfix)[position] = '\0';
    free_stack(stack);
    return correct_data;
}
check_data calculation(char *str, int *result)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (!stack)
    {
        return memory_alloc_error;
    }
    stack->top = NULL;
    int length = strlen(str);
    int number, data1, data2, tmp_result;
    char operator, symbol;
    check_data push_result, pop_result;
    for (int i = 0; i < length; i++)
    {
        symbol = str[i];
        if (isdigit(symbol))
        {
            number = 0;
            while (i < length && isdigit(str[i]))
            {
                number = number * 10 + (str[i] - '0');
                i++;
            }
            i--;
            push_result = push(stack, number, '\0');
            if (push_result != correct_data)
            {
                free_stack(stack);
                return push_result;
            }
        }
        else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '%' || symbol == '^')
        {
            if (stack->top == NULL)
            {
                free_stack(stack);
                return incorrect_data;
            }
            pop_result = pop(stack, &data2, &operator);
            if (pop_result != correct_data)
            {
                free_stack(stack);
                return pop_result;
            }
            if (stack->top == NULL)
            {
                free_stack(stack);
                return incorrect_data; // Не хватает операндов
            }
            pop_result = pop(stack, &data1, &operator);
            if (pop_result != correct_data)
            {
                free_stack(stack);
                return pop_result;
            }
            switch (symbol)
            {
            case '+':
                tmp_result = data1 + data2;
                break;
            case '-':
                tmp_result = data1 - data2;
                break;
            case '*':
                tmp_result = data1 * data2;
                break;
            case '/':
                if (data2 == 0)
                {
                    free_stack(stack);
                    return div_by_zero; // Деление на ноль
                }
                tmp_result = data1 / data2;
                break;
            case '%':
                if (data2 == 0)
                {
                    free_stack(stack);
                    return div_by_zero;
                }
                tmp_result = data1 % data2;
                break;
            case '^':
                if (data2 < 0)
                {
                    free_stack(stack);
                    return negative_degree; // Отрицательная степень
                }
                tmp_result = pow(data1, data2);
                break;
            default:
                free_stack(stack);
                return incorrect_data;
            }
            push_result = push(stack, tmp_result, '\0');
            if (push_result != correct_data)
            {
                free_stack(stack);
                return push_result;
            }
        }
    }
    if (stack->top == NULL)
    {
        free_stack(stack);
        return incorrect_data; // Не хватает операндов
    }
    pop_result = pop(stack, result, &operator);
    if (pop_result != correct_data)
    {
        free_stack(stack);
        return pop_result;
    }
    free_stack(stack);
    return correct_data;
}
check_data read_input(int count, char *files[])
{
    int count_file_output = 0;
    for (int i = 0; i < count; i++)
    {
        char *file_input_name = files[i];
        FILE *file_input = fopen(file_input_name, "r");
        if (!file_input)
        {
            return file_open_error;
        }
        // Создаем файл для вывода
        count_file_output++;
        char *name_file_output = (char *)malloc(12 * sizeof(char));
        if (!name_file_output)
        {
            fclose(file_input);
            return memory_alloc_error;
        }
        sprintf(name_file_output, "file%d.txt", count_file_output);
        FILE *file_output = fopen(name_file_output, "a");
        if (!file_output)
        {
            fclose(file_input);
            free(name_file_output);
            return file_open_error;
        }
        char *str = NULL;
        size_t size = 0;
        int count_str = 0;
        char *postfix = NULL;
        int result_calculation;

        while (getline(&str, &size, file_input) != -1)
        {
            int str_length = strlen(str);
            for (int j = 0; j < str_length; j++)
            {
                if (str[j] == '\n')
                {
                    str[j] = '\0';
                }
            }
            // Баланс скобок
            if (bracket_balance(str) == 0)
            {
                fprintf(file_output, "String %s; Number:%d ---> The balance of the brackets is broken.\n", str, count_str);
                count_str++;
                free(str);
                continue;
            }
            postfix = (char *)malloc(size * 2 * sizeof(char));
            if (!postfix)
            {
                free(str);
                free(name_file_output);
                fclose(file_input);
                fclose(file_output);
                return memory_alloc_error;
            }
            switch (conversion_to_postfix(str, &postfix))
            {
            case memory_alloc_error:
                free(str);
                free(postfix);
                free(name_file_output);
                fclose(file_input);
                fclose(file_output);
                return memory_alloc_error;
            case incorrect_data:
                fprintf(file_output, "String %s; Number:%d ---> Not a correct symbol.\n", str, count_str);
                free(postfix);
                free(str);
                count_str++;
                continue;
            case stack_is_empty:
                free(str);
                free(postfix);
                free(name_file_output);
                fclose(file_input);
                fclose(file_output);
                return stack_is_empty; // Ошибка при извлечении со стека
            }
            switch (calculation(postfix, &result_calculation))
            {
            case memory_alloc_error:
                free(postfix);
                free(name_file_output);
                fclose(file_input);
                fclose(file_output);
                return memory_alloc_error;
            case incorrect_data: // Не хватает операндов
                fprintf(file_output, "String %s; Number:%d ---> Not a correct expression.\n", str, count_str);
                free(postfix);
                free(str);
                count_str++;
                continue;
            case div_by_zero:
                fprintf(file_output, "String %s; Number:%d ---> div by zero.\n", str, count_str);
                free(postfix);
                free(str);
                count_str++;
                continue;
            case negative_degree:
                fprintf(file_output, "String %s; Number:%d ---> negative degree.\n", str, count_str);
                free(postfix);
                free(str);
                count_str++;
                continue;
            case stack_is_empty:
                free(str);
                free(postfix);
                free(name_file_output);
                fclose(file_input);
                fclose(file_output);
                return stack_is_empty;
            }
            printf("File name: %s; expression: %s; postfix: %s; calculated result = %d\n", file_input_name, str, postfix, result_calculation);
            free(postfix);
            count_str++;
        }

        free(str);
        free(name_file_output);
        fclose(file_input);
        fclose(file_output);
    }
    return correct_data;
}