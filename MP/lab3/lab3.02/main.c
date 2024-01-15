#include "action.h"
// ... структуру веткора - функция для норм-три - функция для поиска самого длинного вектора
int main(int argc, char *argv[])
{
    Vector v1;
    switch (create_vector(&v1, 3, 1.0, 1.0, 1.0))
    {
    case correct_data:
    {
        Vector v2;
        switch (create_vector(&v2, 3, 2.0, 2.0, 2.0))
        {
        case correct_data:
        {
            Vector v3;
            switch (create_vector(&v3, 3, 3.0, 3.0, 3.0))
            {
            case correct_data:
            {
                Vector v4;
                switch (create_vector(&v4, 3, 4.0, 4.0, 4.0))
                {
                case correct_data:
                {
                    Vector **result;
                    int max_norm_s, p_norm_s, matrix_norm_s; // размеры по нормам (size)
                    switch (get_max_vector(&result, &max_norm_s, &p_norm_s, &matrix_norm_s, calc_max_norm, calc_p_norm, calc_matrix_norm, 3, 2, 4, v1, v2, v3, v4))
                    {
                    case correct_data:
                        print_result(result, max_norm_s, p_norm_s, matrix_norm_s);
                        delete_all_vector(4, v1, v2, v3, v4);
                        free(result);
                        break;
                    case incorrect_data:
                        printf("Calculation error\n");
                        break;
                    case memory_malloc_error:
                        printf("memory malloc error\n");
                        break;
                    }
                    break;
                }
                case memory_malloc_error:
                    printf("memory malloc error\n");
                    break;
                }
                break;
            }
            case memory_malloc_error:
                printf("memory malloc error\n");
                break;
            }
            break;
        }
        case memory_malloc_error:
            printf("memory malloc error\n");
            break;
        }
        break;
    }
    case memory_malloc_error:
        printf("memory malloc error\n");
        break;
    }

    return 0;
    printf("\n\nM8O-211B-22  Mashrabova  lab3 tack2\n");
    return 0;
}