#include "action.h"

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        print_info();
        return 1;
    }
    else
    {
        double parametrs[2];
        switch (correct_number(argv[1], &parametrs[0]))
        {
        case correct_data:
            double x = parametrs[0];
            switch (correct_number(argv[2], &parametrs[1]))
            {
            case correct_data:
                double epsilon = parametrs[1];
                switch (correct_epsilon(&epsilon))
                {
                case correct:
                    printf("x = %lf; epsilon = %lf\n", x, epsilon);
                    sum_a(x, epsilon);
                    sum_b(x, epsilon);
                    if (x >= 1)
                    {
                        printf("For the point 'c' and 'd' ---> |x| <1\n");
                    }
                    else
                    {
                        sum_c(x, epsilon);
                        sum_d(x, epsilon);
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

    printf("\n\nM8O-211B-22  Mashrabova  lab1 tack5\n");
    return 0;
}
