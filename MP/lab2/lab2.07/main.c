#include "action.h"

int main(int argc, char *argv[])
{
    // Функция которая находит корень уравнения одной переменной методом дихотомии.
    // Аргументы - границы интервала, на котором находится корень; точность (эпсилон),
    // указатель на функцию, связанной с уравнением от одной переменной.
    //---несколько уравнений---

    double epsilon;

    printf("  Enter a epsilon: ");
    if (!scanf("%lf", &epsilon))
    {
        printf("INCORRECT epsilon\n");
        return 1;
    }
    switch (correct_epsilon(&epsilon))
    {
    case correct:
        int input; // указатель на выбор уравнения
        printf(" Choose the equation(1/2):\n 1. 4-exp(x)-2*x^2=0\n 2. 2*x^2+3=0\n 3. tg(x)=0\nChose: ");
        if (!scanf("%d", &input))
        {
            printf("Error1\n");
            return 1;
        }
        if (input == 1 && input == 2 && input == 3)
        {
            printf("Error2\n");
            return 1;
        }
        double root;
        double a, b;
        switch (dichotomy(&root, input, epsilon, a, b))
        {
        case correct_data:
            printf("Root of equation %d ---> %lf\n", input, root);
            break;
        case incorrect_data:
            printf("Calculation error\n");
            break;
        case not_roots:
            printf("NO ROOTS\n");
            break;
        }
        break;
    case incorrect:
        printf("INCORRECT epsilon\n");
        return 1;
    }

    printf("\n\nM8O-211B-22  Mashrabova  lab2 tack7\n");
    return 0;
}
