#include "action.h"

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        printf("Enter flag and file input, file output \n");
        return 1;
    }
    else
    {
        if (argv[1][0] != '/' && argv[1][0] != '-')
        {
            printf("Before the action (flag) should be - or / \n");
        }
        else
        {
            if (argv[1][1] == 'a' || argv[1][1] == 'd')
            {
                char flag = argv[1][1];
                FILE *input_file;
                input_file = fopen(argv[2], "r");
                if (!input_file)
                {
                    printf("File 1 opening error\n");
                    return 1;
                }
                FILE *output_file;
                output_file = fopen(argv[3], "w+");
                if (!output_file)
                {
                    fclose(input_file);
                    printf("File 2 opening error\n");
                    return 1;
                }
                employee *empl;
                int size_empl;
                switch (read_file(input_file, &empl, &size_empl))
                {
                case correct_data:
                    switch (flag)
                    {
                    case 'a':
                        qsort(empl, size_empl, sizeof(employee), sort_ascending);
                        break;
                    case 'd':
                        qsort(empl, size_empl, sizeof(employee), sort_descending);
                        break;
                    }
                    for (int i = 0; i < size_empl; ++i)
                    {
                        fprintf(output_file, "%d %s %s %f\n", empl[i].id, empl[i].name, empl[i].surname, empl[i].salary);
                    }
                    free(empl);
                    break;
                case incorrect_data:
                    printf("incorrect data in file\n");
                    fclose(input_file);
                    fclose(output_file);
                    return 1;
                case memory_malloc_error:
                    printf("memory malloc error\n");
                    fclose(input_file);
                    fclose(output_file);
                    return 1;
                case memory_realloc_error:
                    printf("memory realloc error\n");
                    fclose(input_file);
                    fclose(output_file);
                    return 1;
                }
            }
            else
            {
                printf("INCORRECT INPUT\n");
            }
        }
    }
    printf("M8O-211B-22  Mashrabova  lab3 tack3\n");
    return 0;
}
