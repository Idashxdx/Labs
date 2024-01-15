#include "action.h"
check_data create_vector(Vector *vector, const int dim, ...)
{
    vector->elements = (double *)malloc(sizeof(double) * dim); // Выделение памяти под координаты
    if (vector->elements == NULL)
    {
        return memory_malloc_error;
    }
    vector->dim = dim;
    va_list ptr;
    va_start(ptr, dim);
    for (int i = 0; i < dim; ++i)
    {
        vector->elements[i] = va_arg(ptr, double); // Заполнение координат вектора
    }
    return correct_data;
}

double calc_max_norm(Vector vector, const int dim)
{
    double result = 0;
    for (int i = 0; i < dim; ++i)
    {
        result = fmax(result, fabs(vector.elements[i])); // Вычисление максимальной нормы
    }
    return result;
}

check_data calc_p_norm(Vector vector, const int dim, const int p, double *result)
{
    if (p < 1)
    {
        return incorrect_data;
    }
    *result = 0;
    for (int i = 0; i < dim; ++i)
    {
        *result += pow(fabs(vector.elements[i]), p); // Вычисление p-нормы
    }
    *result = pow(*result, 1 / (double)p);
    return correct_data;
}

check_data calc_matrix_norm(Vector vector, const int dim, double *result)
{
    double **matrix = (double **)malloc(sizeof(double *) * dim); // Выделение памяти под матрицу
    // Проверка на ошибку выделения памяти
    if (matrix == NULL)
    {
        return memory_malloc_error;
    }

    for (int i = 0; i < dim; ++i)
    {
        matrix[i] = (double *)malloc(sizeof(double) * dim); // Выделение памяти под строки матрицы
        if (matrix[i] == NULL)
        {
            for (int k = 0; k < i; ++k)
                free(matrix[i]);
            free(matrix);
            return memory_malloc_error;
        }
        for (int j = 0; j < dim; ++j)
        {
            matrix[i][j] = (i == j) ? 1 : 0; // Заполнение матрицы
        }
    }

    double *multipliedResult = (double *)malloc(sizeof(double) * dim);
    if (multipliedResult == NULL)
    {
        for (int i = 0; i < dim; ++i)
            free(matrix[i]);
        free(matrix);
        return memory_malloc_error;
    }

    for (int i = 0; i < dim; ++i)
    {
        multipliedResult[i] = 0;
        for (int j = 0; j < dim; ++j)
        {
            multipliedResult[i] += matrix[i][j] * vector.elements[i];
        }
    }

    *result = 0;
    for (int i = 0; i < dim; ++i)
    {
        *result += multipliedResult[i] * vector.elements[i];
    }
    *result = sqrt(*result);

    for (int i = 0; i < dim; ++i)
        free(matrix[i]);
    free(matrix);
    free(multipliedResult);

    return correct_data;
}

check_data get_max_vector(Vector ***result, int *max_norm_s, int *p_norm_s, int *matrix_norm_s,
                          double (*max_norm)(Vector, const int), check_data (*p_norm)(Vector, const int, const int, double *),
                          check_data (*matrix_norm)(Vector, const int, double *), const int dim, const int p, const int number_vector, ...)
{
    *result = (Vector **)malloc(sizeof(Vector *) * 3);
    if (*result == NULL)
    {
        return memory_malloc_error;
    }

    va_list ptr;
    va_start(ptr, number_vector);

    double maxNormForAll[number_vector];
    double pNormForAll[number_vector];
    double matrixNormForAll[number_vector];
    Vector vectors[number_vector];
    double maxMaxNorm = -1, maxPNorm = -1, maxMatrixNorm = -1;

    for (int i = 0; i < number_vector; ++i)
    {
        Vector v = va_arg(ptr, Vector);
        if (v.dim != dim)
        {
            free(*result);
            return incorrect_data;
        }
        check_data status;

        const double curMaxNorm = calc_max_norm(v, dim);
        maxMaxNorm = fmax(maxMaxNorm, curMaxNorm);

        double curPNorm;
        status = calc_p_norm(v, dim, p, &curPNorm);
        if (status == incorrect_data)
            return incorrect_data;
        maxPNorm = fmax(maxPNorm, curPNorm);

        double curMatrixNorm;
        status = calc_matrix_norm(v, dim, &curMatrixNorm);
        if (status == memory_malloc_error)
            return memory_malloc_error;
        maxMatrixNorm = fmax(maxMatrixNorm, curMatrixNorm);

        maxNormForAll[i] = curMaxNorm;
        pNormForAll[i] = curPNorm;
        matrixNormForAll[i] = curMatrixNorm;
        vectors[i] = v;
    }

    int maxNormResCapacity = 1, pNormResCapacity = 1, matrixNormResCapacity = 1;
    (*result)[0] = (Vector *)malloc(sizeof(Vector) * number_vector);
    (*result)[1] = (Vector *)malloc(sizeof(Vector) * number_vector);
    (*result)[2] = (Vector *)malloc(sizeof(Vector) * number_vector);
    if ((*result)[0] == NULL || (*result)[1] == NULL || (*result)[2] == NULL)
        return memory_malloc_error;
    *max_norm_s = 0, *p_norm_s = 0, *matrix_norm_s = 0;

    for (int i = 0; i < number_vector; ++i)
    {
        if (maxNormForAll[i] == maxMaxNorm)
        {
            (*result)[0][*max_norm_s] = vectors[i];
            ++(*max_norm_s);
        }
        if (pNormForAll[i] == maxPNorm)
        {
            (*result)[1][*p_norm_s] = vectors[i];
            ++(*p_norm_s);
        }
        if (matrixNormForAll[i] == maxMatrixNorm)
        {
            (*result)[2][*matrix_norm_s] = vectors[i];
            ++(*matrix_norm_s);
        }
    }

    return correct_data;
}

void delete_vector(Vector vector)
{
    free(vector.elements);
}

void delete_all_vector(const int number_vector, ...)
{
    va_list ptr;
    va_start(ptr, number_vector);
    for (int i = 0; i < number_vector; ++i)
    {
        delete_vector(va_arg(ptr, Vector)); // Удаление каждого вектора
    }
}

void print_vector(Vector vector)
{
    if (!vector.dim)
    {
        return; // Проверка на наличие координат
    }
    for (int i = 0; i < vector.dim; ++i)
    {
        printf("%f ", vector.elements[i]); // Вывод координат
    }
    printf("\n");
}
void print_result(Vector **result, const int max_norm_s, const int p_norm_s, const int matrix_norm_s)
{
    printf("max norm\n");
    for (int i = 0; i < max_norm_s; ++i)
    {
        print_vector(result[0][i]);
        printf("\n");
    }
    printf("p norm\n");
    for (int i = 0; i < p_norm_s; ++i)
    {
        print_vector(result[1][i]);
        printf("\n");
    }
    printf("matrix norm\n");
    for (int i = 0; i < matrix_norm_s; ++i)
    {
        print_vector(result[2][i]);
        printf("\n");
    }
}
