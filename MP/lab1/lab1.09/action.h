#ifndef action_h
#define action_h
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define SIZE 16
// 1.
// пусть размер масива для 1 действия будет 16
// проверка входного значения
enum check_input_data
{
  data_overflow,
  data_underflow,
  correct_data,
  incorrect_data,
};
// 2.Не привышает максимальное?
enum check_input_data overflow_or_not(const int value)
{
  if (value >= INT_MAX)
  {
    return data_overflow;
  }
  else if (value <= INT_MIN)
  {
    return data_underflow;
  }
  return correct_data;
}
// 1.Это число?
enum check_input_data correct_number(const char *str, int *value)
{
  char *endptr;
  *value = strtoll(str, &endptr, 10);
  if (*str != '\0' && *endptr == '\0')
  {
    return overflow_or_not(*value);
  }
  value = NULL;
  return incorrect_data;
}
// т.к размер массива 16-проверяем что бы в диапазоне было от 16 чисел
enum check_min_size_array
{
  range_small,
  range_normal
};
enum check_min_size_array check_range(int *a, int *b)
{
  int check = *b - *a;
  if (check < SIZE)
  {
    return range_small;
  }
  return range_normal;
}
void array_swap_min_and_max(int a, int b)
{
  int array[SIZE];
  int index_max = 0;
  int index_min = 0;
  // заполняем массив
  srand(time(NULL));
  for (int i = 0; i < SIZE; i++)
  {
    array[i] = a + rand() % (b - a + 1);
  }
  // печатаем его
  printf("Source array:\n");
  for (int i = 0; i < SIZE; i++)
  {
    printf("%d ", array[i]);
  }
  // меняем максимальное и минимальное местами
  for (int i = 1; i < SIZE; i++)
  {
    if (array[i] < b)
    {
      b = array[i];
      index_min = i;
    }
    if (array[i] > a)
    {
      a = array[i];
      index_max = i;
    }
  }
  int swap = array[index_min];
  array[index_min] = array[index_max];
  array[index_max] = swap;
  // печатаем результат
  printf("\nReady array:\n");
  for (int i = 0; i < SIZE; i++)
  {
    printf("%d ", array[i]);
  }
}
//---------------------------------------------------------------------------------------------

int dinamic_array()
{
  int a = -1000;
  int b = 1000;
  int bigin_size = 10;
  int end_size = 10000;
  // определяем размер массивов от 10 до 10000
  srand(time(NULL));
  int size_a = bigin_size + rand() % (end_size - bigin_size + 1);
  int size_b = bigin_size + rand() % (end_size - bigin_size + 1);
  // заполняем массивы A,B от -1000 до 1000
  int *array_a = (int *)malloc(size_a * sizeof(int));
  int *array_b = (int *)malloc(size_b * sizeof(int));

  for (int i = 0; i < size_a; i++)
  {
    array_a[i] = a + rand() % (b - a + 1);
  }
  for (int j = 0; j < size_b; j++)
  {
    array_b[j] = a + rand() % (b - a + 1);
  }
  // печатаем A,B
  printf("size A: %d, size B: %d\n", size_a, size_b);
  printf("\n A:\n");
  for (int i = 0; i < size_a; i++)
  {
    printf("%d ", array_a[i]);
  }
  printf("\n B:\n");
  for (int j = 0; j < size_b; j++)
  {
    printf("%d ", array_b[j]);
  }
  int *array_c = (int *)malloc(size_a * sizeof(int));
  // заполняем C(размер у него как у A)
  for (int i = 0; i < size_a; i++)
  {
    int most_nearest = abs(array_a[i]);
    int nearest_value = 0;
    for (int j = 0; j < size_b; j++)
    {
      int nearest = abs(array_a[i] - array_b[j]);
      if (nearest < most_nearest)
      {
        most_nearest = nearest;
        nearest_value = array_b[j];
      }
    }
    array_c[i] = array_a[i] + nearest_value;
  }
  printf("\n C:\n");
  for (int k = 0; k < size_a; k++)
  {
    printf("%d ", array_c[k]);
  }
}
void print_info()
{
  printf("Enter range ---> a b \n");
}

#endif
