#include "action.h"

int main(int argc, char *argv[])
{
    int base;
    printf("Введите основание CC: ");
    if (!scanf("%d", &base))
    {
        printf("Диапазон [2..36]! ");
        return 1;
    }
    switch (check_base(base))
    {
    case correct_data:
        char number[100];
        int max_number = 0;
        int number_9 = 0;
        int number_18 = 0;
        int number_27 = 0;
        int number_36 = 0;
        int input_count = 0;
        while (1)
        {
            printf("\nВведите число в CC с основанием %d (введите 'Stop' для окончания ввода): ", base);
            scanf("%s", number);

            if (strcmp(number, "Stop") == 0)
            {
                if (input_count == 0)
                {
                    printf("Числа не были введены\n");
                    return 1;
                }
                else
                {
                    break;
                }
            }
            switch (check_number(number, base))
            {
            case correct_data:
                if (strcmp(number, "0") == 0)
                {
                    input_count++;
                    long long current = 0;
                    max_number = find_max_number(max_number, current);
                }
                else
                {
                    input_count++;
                    long long current = conversion_to_decimal(number, base);
                    max_number = find_max_number(max_number, current);
                }
                break;

            case incorrect_data:
                printf("\nЧисло должно быть в системе счисления с основанием %d\n", base);
                return 1;
            }
        }
        printf("\nМаксимальное по модулю: ");
        print_delete_zeros(max_number, base);
        representation_at_base(max_number, 9);
        representation_at_base(max_number, 18);
        representation_at_base(max_number, 27);
        representation_at_base(max_number, 36);
        break;

    case incorrect_data:
        printf("Диапазон [2..36]!");
        break;
    }
    printf("\n\nM8O-211B-22  Mashrabova  lab1 tack10\n");
    return 0;
}
