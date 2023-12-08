#include "action.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Enter flag and file input, file output \n");
        return 1;
    }

    FILE *input;
    FILE *output;
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w+");
    if (!input || !output)
    {
        printf("File opening error\n");
        return 1;
    }
    size_t size = 0;
    char *str = NULL;
    while (getline(&str, &size, input) != -1)
    {
        Tree* tree;
        switch (create_tree(&tree, str))
        {
        case correct_data:

            break;
        case incorrect_data:
            printf("incorrect data\n");
            return 1;
        case memory_malloc_error:
            printf("memory malloc error\n");
            return 1;
        }

        free(str);
        str = NULL;
    }

    fclose(input);
    fclose(output);
    return 0;
}