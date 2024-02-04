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
            printf("Memory allocation error\n");
            return 1;
        default:
            fclose(input_file);
            printf("Incorrect data\n");
            return 1;
        }
        while (1)
        {
            char act[10];
            printf("Choose an action:\n");
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
            }
            else if (strcmp(act, "output") == 0)
            {
                fgets(act, sizeof(act), stdin);
            }
              else if (strcmp(act, "short") == 0)
            {
                fgets(act, sizeof(act), stdin);
            }
              else if (strcmp(act, "long") == 0)
            {
                fgets(act, sizeof(act), stdin);
            }
              else if (strcmp(act, "depth") == 0)
            {
                fgets(act, sizeof(act), stdin);
            }
              else if (strcmp(act, "print") == 0)
            {
                fgets(act, sizeof(act), stdin);
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
    }
    printf("M8O-211B-22  Mashrabova  lab3 tack9\n");
    return 0;
}
