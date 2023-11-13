
#include "action.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
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
            if ((argv[1][1] == 'l' && argc == 3) || (argv[1][1] == 'r' && argc == 3) ||
                (argv[1][1] == 'u' && argc == 3) || (argv[1][1] == 'n' && argc == 3) ||
                (argv[1][1] == 'c' && argc > 3))
            {
                char flag = argv[1][1];

                switch (flag)
                {
                case 'l':
                    //-l-подсчет длины строки
                    int str_length;
                    str_length = count_length(argv[2]);
                    printf("Length of the entered string ---> %d\n", str_length);
                    break;
                case 'r':
                    //-r-получить новую строку, явл. перевернутой
                    char *str_reverse;
                    switch (get_string_reversed(argv[2], &str_reverse))
                    {
                    case correct_data:
                        printf("Reverse ---> %s", str_reverse);
                        free(str_reverse); // освобождаем дм
                        break;
                    case incorrect_data:
                        printf("Error");
                        break;
                    case memory_allocation_error:
                        printf("Memory allocation error");
                        break;
                    }
                    break;
                case 'u':
                    //-u-получить новую строку, идентичную переданной-нечетные-->верхний регистр
                    char *str_uppercase;
                    switch (get_string_odd_uppercase(argv[2], &str_uppercase))
                    {
                    case correct_data:
                        printf("Convertion pdd to uppercase ---> %s", str_uppercase);
                        free(str_uppercase); // освобождаем дм
                        break;
                    case incorrect_data:
                        printf("Error");
                        break;
                    case memory_allocation_error:
                        printf("Memory allocation error");
                        break;
                    }
                    break;
                case 'n':
                    //-n- получить новую строку, 1.цифры 2.буквы 3.остальное
                    char *str_sort;
                    switch (get_string_sorted(argv[2], &str_sort))
                    {
                    case correct_data:
                        printf("Sorted ---> %s", str_sort);
                        free(str_sort); // освобождаем дм
                        break;
                    case incorrect_data:
                        printf("Error");
                        break;
                    case memory_allocation_error:
                        printf("Memory allocation error");
                        break;
                    }
                    break;
                case 'c':
                    //-c-получить новую строку, явл. конкатенацией 2 4 5 ..
                    char *str_concaten;
                    unsigned int seed;
                    // check seed
                    if (!sscanf(argv[3], "%u", &seed))
                    {
                        printf("enter seed in the unsigned int type value\n");
                        return 1;
                    }
                    switch (get_string_concaten(argv, argc, &str_concaten, seed))
                    {
                    case correct_data:
                        printf("Concatenation---> %s", str_concaten);
                        free(str_concaten); // освобождаем дм
                        break;
                    case incorrect_data:
                        printf("Error");
                        break;
                    case memory_allocation_error:
                        printf("Memory allocation error");
                        break;
                    }
                    break;
                }
            }
            else
                print_info();
        }
        printf("\n\nM8O-211B-22  Mashrabova  lab2 tack1\n");
        return 0;
    }
}
