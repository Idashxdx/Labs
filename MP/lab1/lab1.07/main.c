#include "action.h"

int main(int argc, char *argv[])
{

    if (argc != 4 && argc != 5)
    {
        print_info();
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
            if ((argv[1][1] == 'r' && argc == 5) || (argv[1][1] == 'a' && argc == 4))
            {
                char flag = argv[1][1];

                FILE *input_file_1;
                FILE *input_file_2;
                FILE *output_file;
                switch (flag)
                {
                case 'a':
                    input_file_1 = fopen(argv[2], "r");
                    output_file = fopen(argv[3], "w+");
                    if (!input_file_1 || !output_file)
                    {
                        printf("File opening error\n");
                        return 1;
                    }
                    record_change(input_file_1, output_file);
                    fclose(input_file_1);
                    fclose(output_file);
                    break;
                case 'r':
                    input_file_1 = fopen(argv[2], "r");
                    input_file_2 = fopen(argv[3], "r");
                    output_file = fopen(argv[4], "w+");
                    if (!input_file_1 || !input_file_2 || !output_file)
                    {
                        printf("File opening error\n");
                        return 1;
                    }
                    record_even_odd(input_file_1, input_file_2, output_file);
                    fclose(input_file_1);
                    fclose(input_file_2);
                    fclose(output_file);
                    break;
                default:
                    printf("There is no such flag\n");
                    print_info();
                    break;
                }
            }
            else
            {
                printf("INCORRECT INPUT\n");
                print_info();
            }
        }
    }
    printf("M8O-211B-22  Mashrabova  lab1 tack7\n");
    return 0;
}
