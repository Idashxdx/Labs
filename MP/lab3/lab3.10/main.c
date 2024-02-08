#include "action.h"
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Enter input_file output_file\n");
        return 1;
    }
    FILE *input;
    FILE *output;
    input = fopen(argv[1], "r");
    if (!input)
    {
        printf("Error opening input file\n");
        return 1;
    }
    output = fopen(argv[2], "w+");
    if (!output)
    {
        fclose(input);
        printf("Error opening output file\n");
        return 1;
    }
    size_t size = 0;
    char *str = NULL;

    while (getline(&str, &size, input) != -1)
    {
        if (str[strcspn(str, "\n")] != 0)
        {
            Tree tree;
            switch (create_tree(&tree, str))
            {
            case correct_data:
                print_tree(output, tree.root, 0);
                break;
            case incorrect_data:
                fprintf(output, "Incorrect data \n");
                break;
            case memory_malloc_error:
                fprintf(output, "Memory malloc error\n");
                break;
            }
            delete_tree(tree.root);
        }
    }
    free(str);
    fclose(input);
    fclose(output);
    printf("M8O-211B-22  Mashrabova  lab3 tack10\n");
    return 0;
}