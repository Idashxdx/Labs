#include "action.h"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        print_info();
        return 1;
    }
    else
    {
        double parametrs[1];
        switch (correct_number(argv[1], &parametrs[0]))
        {
        case correct_data:
            double epsilon = parametrs[0];
            switch (correct_epsilon(&epsilon))
            {
            case correct:
                printf("epsilon = %lf\n", epsilon);
                printf("Integral a = %lf\n", integral_a(epsilon));
                printf("Integral b = %lf\n", integral_b(epsilon));
                printf("Integral c = %lf\n", integral_c(epsilon));
                printf("Integral d = %lf\n", integral_d(epsilon));
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
        }
    }

    printf("\n\nM8O-211B-22  Mashrabova  lab1 tack6\n");
    return 0;
}
