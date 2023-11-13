#include "action.h"

int main(int argc, char *argv[])
{

    if (argc != 3 && argc != 4)
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
            if ((argv[1][1] == 'n' && argv[1][2] == 'd' && argc == 4) || (argv[1][1] == 'n' && argv[1][2] == 'i' && argc == 4) || (argv[1][1] == 'n' && argv[1][2] == 's' && argc == 4) || (argv[1][1] == 'n' && argv[1][2] == 'a' && argc == 4) || (argv[1][1] == 'd' && argc == 3) || (argv[1][1] == 'i' && argc == 3) || (argv[1][1] == 's' && argc == 3) || (argv[1][1] == 'a' && argc == 3))
            {
                char flag = argv[1][1];
                char flag_n = argv[1][2];
                FILE *input_file;
                FILE *output_file;
                input_file = fopen(argv[2], "r");
                if (!input_file)
                {
                    printf("File opening error\n");
                    return 1;
                }
                if (argc == 3)
                {
                    char new_output_file[256];
                    strcpy(new_output_file, "out_");
                    strcat(new_output_file, argv[2]);
                    output_file = fopen(new_output_file, "w+");
                    switch (flag)
                    {
                    case 'd':
                        exclud_digit(input_file, output_file);
                        break;
                    case 'i':
                        count_letter(input_file, output_file);
                        break;
                    case 's':
                        different_symbol(input_file, output_file);
                        break;
                    case 'a':
                        replac_symbol(input_file, output_file);
                        break;
                    default:
                        printf("There is no such flag\n");
                        print_info();
                        break;
                    }
                }
                else
                {

                    output_file = fopen(argv[3], "w+");
                    switch (flag_n)
                    {
                    case 'd':
                        exclud_digit(input_file, output_file);
                        break;
                    case 'i':
                        count_letter(input_file, output_file);
                        break;
                    case 's':
                        different_symbol(input_file, output_file);
                        break;
                    case 'a':
                        replac_symbol(input_file, output_file);
                        break;
                    default:
                        printf("There is no such flag\n");
                        print_info();
                        break;
                    }
                }
                fclose(input_file);
                fclose(output_file);
            }
            else
            {
                printf("INCORRECT INPUT\n");
                print_info();
            }
        }
    }
    printf("M8O-211B-22  Mashrabova  lab1 tack4\n");
    return 0;
}
