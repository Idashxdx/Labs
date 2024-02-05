#include "action.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Enter file input and symbol/s\n");
        return 1;
    }
    else
    {
        FILE *input_file;
        input_file = fopen(argv[1], "r");
        if (!input_file)
        {
            printf("File 1 opening error\n");
            return 1;
        }
        // читаем файл и создаем дерево
        Node *node = NULL;
        int count = argc; // количество разделителей
        switch (create_tree(input_file, argv, count, &node))
        {
        case correct_data:
            printf("Correct\n\n");
            break;
        case memory_alloc_error:
            fclose(input_file);
            free_node(node);
            printf("Memory allocation error\n");
            return 1;
        default:
            fclose(input_file);
            free_node(node);
            printf("Incorrect data\n");
            return 1;
        }
        while (1)
        {
            int order; // для сортирвки - порядок сортировки - если 0 - то сортируем по count если !0 - то по размеру слова
            char act[10];
            printf("\nChoose an action:\n");
            printf("<find>  - find how many words\n");                  // +вводим слово - выводим сколько их
            printf("<output> - the output of the most common words\n"); // +вводим число n - выводим наиболее часто встр. слова- количество слов до n
            printf("<short> - the shortest word\n");
            printf("<long> - the longest word\n");
            printf("<depth> - a search in depth\n");
            printf("<print> - print tree in file\n"); // +вводим название файла
            printf("<exit> - exit\n\n");
            printf("ENTER ----> ");
            scanf("%s", act);
            if (strcmp(act, "find") == 0)
            {
                fgets(act, sizeof(act), stdin);
                char str_to_find[50];
                printf("Enter word: ");
                if (scanf("%s", str_to_find) != 1)
                {
                    printf("Enter a valid char.\n\n");
                    continue;
                }
                int result = 0;
                int found = 0; // для отслеживания (если не найдено - 0)
                find_str(node, &result, str_to_find, found);
                printf("The word '%s' in the text ---> %d\n", str_to_find, result);
            }
            else if (strcmp(act, "output") == 0)
            {
                fgets(act, sizeof(act), stdin);
                char input[50];
                unsigned int n;
                printf("Enter n: ");
                fgets(input, sizeof(input), stdin);
                if (sscanf(input, "%u", &n) != 1)
                {
                    printf("Enter a valid unsigned int.\n\n");
                    continue;
                }
                Node *node_sort = NULL;
                order = 0;
                switch (sort_tree(&node_sort, node, order))
                {
                case correct_data:
                    int counter_up_to_n = 0;
                    printf("The %d most common words:\n", n);
                    print_most_common(node_sort, &counter_up_to_n, n);
                    break;
                case memory_alloc_error:
                    fclose(input_file);
                    free_node(node);
                    printf("Memory allocation error\n");
                    continue;
                }
                free(node_sort);
            }
            else if (strcmp(act, "short") == 0)
            {
                fgets(act, sizeof(act), stdin);
                Node *node_sort = NULL;
                order = 1;
                switch (sort_tree(&node_sort, node, order))
                {
                case correct_data:
                    print_short(node_sort);
                    break;
                case memory_alloc_error:
                    fclose(input_file);
                    free_node(node);
                    printf("Memory allocation error\n");
                    continue;
                }
                free(node_sort);
            }
            else if (strcmp(act, "long") == 0)
            {
                fgets(act, sizeof(act), stdin);
                Node *node_sort = NULL;
                order = 1;
                switch (sort_tree(&node_sort, node, order))
                {
                case correct_data:
                    print_long(node_sort);
                    break;
                case memory_alloc_error:
                    fclose(input_file);
                    free_node(node);
                    printf("Memory allocation error\n");
                    continue;
                }
                free(node_sort);
            }
            else if (strcmp(act, "depth") == 0)
            {
                fgets(act, sizeof(act), stdin);
                int depth;
                depth = depth_calculation(node);
                printf("The depth is ---> %d\n", depth);
            }
            else if (strcmp(act, "print") == 0)
            {
                fgets(act, sizeof(act), stdin);
                char output[50];
                printf("Enter file: ");
                if (scanf("%s", output) != 1)
                {
                    printf("Enter a valid.\n\n");
                    continue;
                }
                FILE *output_file = fopen(output, "w");
                if (!output_file)
                {
                    printf("File 2 opening error\n");
                    continue;
                }
                int level = 0; // уровень узла
                print_node(output_file, node, level);
                fclose(output_file);
                FILE *output_file_2 = fopen(output, "r");
                Node *node_from_file = NULL;
                switch (read_file_tree(output_file_2, &node_from_file))
                {
                case correct_data:
                    print_node(stdout, node_from_file, level);
                    break;
                case memory_alloc_error:
                    fclose(input_file);
                    free_node(node);
                    fclose(output_file_2);
                    free(node_from_file);
                    printf("Memory allocation error\n");
                    continue;
                }
                fclose(output_file_2);
                free(node_from_file);
            }
            else if (strcmp(act, "exit") == 0)
            {
                break;
            }
            else
            {
                printf("There is no such action\n\n");
            }
        }
        fclose(input_file);
        free_node(node);
    }
    printf("M8O-211B-22  Mashrabova  lab3 tack9\n");
    return 0;
}
