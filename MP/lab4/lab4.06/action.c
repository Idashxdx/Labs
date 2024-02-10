#include "action.h"

void free_stack(Stack *stack) {
    while (stack != NULL) {
        Stack *tmp = stack;
        stack = stack->next;
        free(tmp);
    }
}

check_data push(Stack **stack, char operator) {
    Stack *new_node = (Stack *)malloc(sizeof(Stack));
    if (!new_node) {
        return memory_alloc_error;
    }

    new_node->operator = operator;
    new_node->next = *stack;
    *stack = new_node;

    return correct_data;
}

check_data pop(Stack **stack, char *operator) {
    if (*stack == NULL) {
        return stack_is_empty;
    }

    Stack *top_node = *stack;
    *operator = top_node->operator;
    *stack = top_node->next;
    free(top_node);

    return correct_data;
}

int bracket_balance(char *str) {
    int length = strlen(str);
    int bracket = 0;
    for (int i = 0; i < length; i++) {
        if (str[i] == '(') {
            bracket++;
        } else if (str[i] == ')') {
            bracket--;
            if (bracket < 0) {
                return 0;
            }
        }
    }
    return bracket == 0;
}

int priority_operators(char operator) {
    switch (operator) {
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
            return 0;
    }
}

Node *create_node(char data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node) {
        return NULL;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

check_data conversion_to_postfix(char *str, char **postfix) {
    Stack *stack = NULL;
    int length = strlen(str);
    char *output = (char *)malloc((length + 1) * sizeof(char));

    if (!output) {
        return memory_alloc_error;
    }

    output[0] = '\0';
    int output_index = 0;

    for (int i = 0; i < length; i++) {
        char symbol = str[i];

        if (symbol == ' ') {
            continue;
        }

        if (isalpha(symbol) || isdigit(symbol)) {
            output[output_index++] = symbol;
        } else if (symbol == '(') {
            push(&stack, symbol);
        } else if (symbol == ')') {
            while (stack && stack->operator != '(') {
                char top_op;
                pop(&stack, &top_op);
                output[output_index++] = top_op;
            }

            if (stack && stack->operator == '(') {
                char discard_op;
                pop(&stack, &discard_op); // Discard the '('
            }
        } else {
            while (stack && priority_operators(stack->operator) >= priority_operators(symbol)) {
                char top_op;
                pop(&stack, &top_op);
                output[output_index++] = top_op;
            }

            push(&stack, symbol);
        }
    }

    while (stack) {
        char top_op;
        pop(&stack, &top_op);
        output[output_index++] = top_op;
    }

    output[output_index] = '\0';
    *postfix = output;
    return correct_data;
}

Node *create_tree(char *postfix)
{
    Stack *stack = NULL;

    for (int i = 0; i < strlen(postfix); i++)
    {
        if (isalpha(postfix[i]) || isdigit(postfix[i]))
        {
            Node *new_node = create_node(postfix[i]);
            if (!new_node)
            {
                free_stack(stack);
                return NULL;
            }

            if (push(&stack, new_node->data) != correct_data)
            {
                free_stack(stack);
                free(new_node);
                return NULL;
            }
        }
        else
        {
            char operator = postfix[i];
            Node *new_operator = create_node(operator);
            if (!new_operator)
            {
                free_stack(stack);
                return NULL;
            }

            Node *right_node = NULL, *left_node = NULL;

            char right_data, left_data;
            if (pop(&stack, &right_data) != correct_data || pop(&stack, &left_data) != correct_data)
            {
                free_stack(stack);
                free(new_operator);
                return NULL;
            }
            
            right_node = create_node(right_data);
            left_node = create_node(left_data);

            new_operator->right = right_node;
            new_operator->left = left_node;

            if (push(&stack, new_operator->data) != correct_data)
            {
                free_stack(stack);
                free(new_operator);
                return NULL;
            }
        }
    }

    if (!stack || !stack->next) // Ошибка в количестве элементов в стеке
    {
        free_stack(stack);
        return NULL;
    }

    Node *root = create_node(stack->operator); // Предполагая, что вершина стека - это корневой оператор
    free(stack);
    return root;
}
int evaluate(Node *node, int values)
{
    if (!node)
    {
        return -1; // Maybe needs a different error value
    }

    if (isalpha(node->data) || isdigit(node->data))
    {
        return (values >> (node->data - 'A')) & 1;
    }
    else
    {
        int left = evaluate(node->left, values);
        int right = evaluate(node->right, values);

        switch (node->data)
        {
        case '~':
            return !left;
        case '&':
            return left && right;
        case '|':
            return left || right;
        case '-':
            return !left || right;
        case '+':
            return left || !right;
        case '<':
            return (left || right) && !(left && right);
        case '=':
            return left == right;
        case '!':
            return !(left && right);
        case '?':
            return !(left || right);
        default:
            return -1; // Maybe needs a different error value
        }
    }
}

void print_table(Node *root, int variables_count, char *variables)
{
    int rows = 1 << variables_count;
    printf("Truth Table:\n");

    for (int i = 0; i < variables_count; i++)
    {
        printf("%c ", variables[i]);
    }
    printf("| Result\n");

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < variables_count; j++)
        {
            printf("%d ", (i >> (variables_count - 1 - j)) & 1);
        }
        printf("| %d\n", evaluate(root, i));
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
        return incorrect_data;
    }

    int variables_count = 0;
    int variables_check[26] = {0}; // 1 - variable has occurred
    char variables[26] = {0};      // Array for storing variables

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (isalpha(str[i]) && !variables_check[toupper(str[i]) - 'A'])
        {
            if (variables_count == 26)
            {
                free(str);
                fclose(file_input);
                return incorrect_data;
            }

            variables_check[toupper(str[i]) - 'A'] = 1;
            variables[variables_count] = toupper(str[i]);
            variables_count++;
        }
    }

    char *postfix = NULL;
    switch (conversion_to_postfix(str, &postfix))
    {
    case memory_alloc_error:
    case incorrect_data:
    case stack_is_empty:
        free(str);
        fclose(file_input);
        return memory_alloc_error;
    }

    Node *root = create_tree(postfix);
    if (!root)
    {
        free(str);
        free(postfix);
        fclose(file_input);
        return memory_alloc_error;
    }

    print_table(root, variables_count, variables);

    free(str);
    free(postfix);
    fclose(file_input);
    return correct_data;
}
