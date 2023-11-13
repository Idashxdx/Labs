#include "action.h"

int main(int argc, char *argv[])
{

    if (argc != 4 && argc != 6)
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
            if ((argv[1][1] == 'q' && argc == 6) || (argv[1][1] == 'm' && argc == 4) ||
                (argv[1][1] == 't' && argc == 6))
            {
                char flag = argv[1][1];
                if (argc == 4)
                {
                    int parametrs_2[2];
                    switch (correct_number_2(argv[2], &parametrs_2[0]))
                    {
                    case correct_data:
                        int number_1 = parametrs_2[0];
                        switch (correct_number_2(argv[3], &parametrs_2[1]))
                        {
                        case correct_data:
                            int number_2 = parametrs_2[1];
                            switch (flag)
                            {
                            case 'm':
                                print_multiple_or_not(number_1, number_2);
                                break;
                            default:
                                printf("There is no such flag\n");
                                print_info();
                                break;
                            }
                            break;
                        case incorrect_data:
                            printf("INCORRECT INPUT\n");
                            printf("parametr not number\n");
                            return 1;
                        case data_overflow:
                            printf("OVERFLOW parametr\n");
                            return 1;
                        }
                        break;
                    case incorrect_data:
                        printf("INCORRECT INPUT\n");
                        printf("parametr not number\n");
                        return 1;
                    case data_overflow:
                        printf("OVERFLOW parametr\n");
                        return 1;
                    }
                }
                else
                {
                    double parametrs[4];
                    switch (correct_number(argv[2], &parametrs[0]))
                    {
                    case correct_data:
                        double epsilon = parametrs[0];
                        switch (correct_epsilon(&epsilon))
                        {
                        case correct:
                            switch (correct_number(argv[3], &parametrs[1]))
                            {
                            case correct_data:
                                double koef_a = parametrs[1];
                                switch (correct_number(argv[4], &parametrs[2]))
                                {
                                case correct_data:
                                    double koef_b = parametrs[2];
                                    switch (correct_number(argv[5], &parametrs[3]))
                                    {
                                    case correct_data:
                                        double koef_c = parametrs[3];
                                        switch (flag)
                                        {
                                        case 'q':
                                            if ((fabs(koef_a - koef_b) < epsilon && fabs(koef_a - koef_c) >= epsilon) ||
                                                (fabs(koef_a - koef_c) < epsilon && fabs(koef_c - koef_b) >= epsilon) ||
                                                (fabs(koef_c - koef_b) < epsilon && fabs(koef_a - koef_c) >= epsilon))
                                            {
                                                print_solution_equation(epsilon, koef_a, koef_b, koef_c);
                                                print_solution_equation(epsilon, koef_b, koef_c, koef_a);
                                                print_solution_equation(epsilon, koef_c, koef_a, koef_b);
                                            }
                                            else
                                            {
                                                print_solution_equation(epsilon, koef_a, koef_b, koef_c);
                                                print_solution_equation(epsilon, koef_a, koef_c, koef_b);
                                                print_solution_equation(epsilon, koef_b, koef_a, koef_c);
                                                print_solution_equation(epsilon, koef_b, koef_c, koef_a);
                                                print_solution_equation(epsilon, koef_c, koef_a, koef_b);
                                                print_solution_equation(epsilon, koef_c, koef_b, koef_a);
                                            }
                                            break;
                                        case 't':
                                            print_result(epsilon, koef_a, koef_b, koef_c);
                                            break;
                                        default:
                                            printf("There is no such flag\n");
                                            print_info();

                                            break;
                                        }
                                        break;
                                    case incorrect_data:
                                        printf("INCORRECT INPUT\n");
                                        printf("parametr not number\n");
                                        return 1;
                                    case data_overflow:
                                        printf("OVERFLOW parametr\n");
                                        return 1;
                                    }
                                    break;
                                case incorrect_data:
                                    printf("INCORRECT INPUT\n");
                                    printf("parametr not number\n");
                                    return 1;
                                case data_overflow:
                                    printf("OVERFLOW parametr\n");
                                    return 1;
                                }
                                break;
                            case incorrect_data:
                                printf("INCORRECT INPUT\n");
                                printf("parametr not number\n");
                                return 1;
                            case data_overflow:
                                printf("OVERFLOW parametr\n");
                                return 1;
                            }
                            break;
                        case incorrect:
                            printf("INCORRECT epsilon\n");
                            return 1;
                        }
                        break;
                    case incorrect_data:
                        printf("INCORRECT INPUT\n");
                        printf("parametr not number\n");
                        return 1;
                    case data_overflow:
                        printf("OVERFLOW parametr\n");
                        return 1;
                    }
                }
            }
            else
                print_info();
        }
    }
    printf("\n\nM8O-211B-22  Mashrabova  lab1 tack3\n");
    return 0;
}
