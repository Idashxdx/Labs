
#include "action.h"

int main(int argc, char *argv[])
{
    // Функция с пер.числом арг., находящую переразложение многочлена со степенями
    // значения x по степеням значения (x - a).
    //---> epsilon,a-указатель на место в памяти,degree,coef... и коеф. g
    double epsilon;
    printf("Enter a epsilon: ");
    if (!scanf("%lf", &epsilon))
    {
        printf("INCORRECT epsilon\n");
        return 1;
    }
    switch (correct_epsilon(&epsilon)) 
    {
    case correct:
        double *coefs_g;
        int degree = 3;
        double a = 2;
        switch (re_expansion(&coefs_g,epsilon, a, degree, 5.0, 1.0, 3.0))
        {
        case correct_data:

            printf("initial coefs: 5.0, 1.0, 3.0 ---> coefs g(0,n):  ");
            for (int i = 0; i < 3; i++)
            {
                printf("%lf ", coefs_g[i]);
            }
            free(coefs_g);
            break;
        case incorrect_data:
            printf("Calculation error\n");
            break;
        case memory_malloc_error:
            printf("Memory malloc error\n");
            break;
        }
        break;
    case incorrect:
        printf("INCORRECT epsilon\n");
        return 1;
    }

    printf("\n\nM8O-211B-22  Mashrabova  lab2 tack10\n");
    return 0;
}
