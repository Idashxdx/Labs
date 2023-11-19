#include "action.h"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Enter inly epsilon\n");
        return 1;
    }
    else
    {
        double parametr[1];
        switch (correct_number(argv[1], &parametr[0]))
        {
        case correct_data:
            double epsilon = parametr[0];
            switch (correct_epsilon(&epsilon))
            {
            case correct:
                printf("\nSOLUTION THROUNGH THE LIMIT\n");
                printf("e = %.9lf\n", e_lim(epsilon));
                printf("pi = %.9lf\n", pi_lim(epsilon));
                printf("ln2 = %.9lf\n", ln2_lim(epsilon));
                printf("sqrt2 = %.9lf\n", sqrt2_lim(epsilon));
                printf("gamma = %.9lf\n", gam_lim(epsilon));
                printf("\nSOLUTION THROUNGH THE ROW/PRODUCT\n");
                printf("e = %.9lf\n", e_row(epsilon));
                printf("pi = %.9lf\n", pi_row(epsilon));
                printf("ln2 = %.9lf \n", ln2_row(epsilon));
                //     printf("sqrt2 = %.9lf\n", sqrt2_row(epsilon));
                //    printf("gamma = %.9lf\n", gam_row(epsilon));
                //    printf("\nSOLUTION THROUNGH THE EQUATION\n");
                //    printf("e = %.9lf\n", e_equat(epsilon));
                //    printf("pi = %.9lf\n", pi_equat(epsilon));
                //     printf("ln2 = %.9lf\n", ln2_equat(epsilon));
                //    printf("sqrt2 = %.9lf\n", sqrt2_equat(epsilon));
                //    printf("gamma = %.9lf\n", gam_equat(epsilon));
                break;
            case incorrect:
                printf("INCORRECT DATA\n");
                return 1;
            }
            break;
        case incorrect_data:
            printf("INCORRECT epsilon\n");
            return 1;
        }
    }

    printf("\n\nM8O-211B-22  Mashrabova  lab1 tack2\n");
    return 0;
}
