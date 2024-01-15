
#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

typedef struct Vector
{
    int dim;
    double *elements; // Массив координат
} Vector;

typedef enum check_data
{
    correct_data,
    incorrect_data,
    memory_malloc_error,
} check_data;

check_data create_vector(Vector *vector, const int dim, ...);
double calc_max_norm(Vector vector, const int dim);
check_data calc_p_norm(Vector vector, const int dim, const int p, double *result);
check_data calc_matrix_norm(Vector vector, const int dim, double *result);
check_data get_max_vector(Vector ***result, int *max_norm_s, int *p_norm_s, int *matrix_norm_s,
                          double (*max_norm)(Vector, const int), check_data (*p_norm)(Vector, const int, const int, double *),
                          check_data (*matrix_norm)(Vector, const int, double *), const int dim, const int p, const int number_vector, ...);
void delete_vector(Vector vector);
void delete_all_vector(const int number_vector, ...);
void print_vector(Vector vector);
void print_result(Vector** result, const int max_norm_s, const int p_norm_s, const int matrix_norm_s);


#endif