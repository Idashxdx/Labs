#include "action.h"

int main(int argc, char *argv[])
{
    char flag;
    int number;
    char *str_number;
    if (argc != 3)
    {
        printf("Enter a number and an action\n");
        return 1;
    }
    else
    {
        if (argv[2][0] != '/' && argv[2][0] != '-')
        {
            printf("Before the action (flag) should be - or / \n");
        }
        else
        {
            flag = argv[2][1];
            switch (correct_number(argv[1], &number))
            {
            case correct_data:
                str_number = argv[1];
                switch (flag)
                {
                case 'h':
                    print_multiples(number);
                    break;
                case 'p':
                    print_simple_or_composite(number);
                    break;
                case 's':
                    separation_number(str_number);
                    break;
                case 'e':
                    print_table(number);
                    break;
                case 'a':
                    print_sum(number);
                    break;
                case 'f':
                    print_factorial(number);
                    break;
                default:
                    printf("There is no such flag\n");
                    print_info();
                    break;
                }
                break;
            case incorrect_data:
                printf("INCORRECT INPUT\n");
                printf("Enter a number and an action\n");
                return 1;
            case data_overflow:
                printf("OVERFLOW\n");
                return 1;
            }
        }
    }
    printf("\n\nM8O-211B-22  Mashrabova  lab1 tack1\n");
    return 0;
}