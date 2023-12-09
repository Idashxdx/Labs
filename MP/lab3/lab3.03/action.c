#include "action.h"

check_data read_file(FILE *input_file, employee **empl, int *size_empl)
{
    *size_empl = 0;
    int size = 32;
    (*empl) = (employee *)malloc(sizeof(employee) * size);
    if (*empl == NULL)
    {
        return memory_malloc_error;
    }
    int read_str;
    char *line = NULL;
    size_t size_line = 0;
    while ((read_str = getline(&line, &size_line, input_file)) != 1) // читаем файл
    {
        if (read_str == -1)
        {
            free(line);
            return correct_data;
        }
        employee tmp;
        if (sscanf(line, "%d %s %s %lf", &(tmp.id), tmp.name, tmp.surname, &(tmp.salary)) != 4)
        {
            free(line);
            free(*empl);
            return incorrect_data;
        }
        (*empl)[*size_empl] = tmp; // считаем количество
        (*size_empl)++;

        if (*size_empl >= size - 1)
        {
            size *= 2;
            employee *empl_res = (employee *)realloc(*empl, sizeof(employee) * size); // меняем размер выделенной памяти
            if (empl_res == NULL)
            {
                return memory_realloc_error;
            }
            *empl = empl_res;
        }
    }
    free(line);
    return correct_data;
}
int sort_ascending(const void *compare_1, const void *compare_2)
{
    employee *empl_1 = (employee *)compare_1;
    employee *empl_2 = (employee *)compare_2;
    if ((empl_1->salary - empl_2->salary) > EPSILON)
    {
        return 1;
    }
    else if ((empl_2->salary - empl_1->salary) > EPSILON)
    {
        return -1;
    }
    int surname_cmp = strcmp(empl_1->surname, empl_2->surname);
    if (surname_cmp != 0)
    {
        return surname_cmp;
    }
    int name_cmp = strcmp(empl_1->name, empl_2->name);
    if (name_cmp != 0)
    {
        return name_cmp;
    }
    return empl_1->id - empl_2->id;
}
int sort_descending(const void *compare_1, const void *compare_2)
{
    return -sort_ascending(compare_1, compare_2);
}
