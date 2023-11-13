#include "action.h"
#include <time.h>

int main(int argc, char *argv[])
{

  if (argc != 3)
  {
    print_info();
    return 1;
  }
  else
  {
    int parametrs[2];
    switch (correct_number(argv[1], &parametrs[0]))
    {
    case correct_data:
      int a = parametrs[0];
      switch (correct_number(argv[2], &parametrs[1]))
      {
      case correct_data:
        int b = parametrs[1];
        switch (check_range(&a, &b))
        {
        case range_small:
          printf("Small range\n");
          return 1;
        case range_normal:
          printf("1. Array %d,%d - swap min and max element\n", a, b);
          array_swap_min_and_max(a, b);

          printf("\n\n2. Array A,B -1000,1000 - C \n");
          dinamic_array();
          break;
        }
        break;
      case incorrect_data:
        printf("INCORRECT INPUT\n");
        printf("Second parametr not number\n");
        return 1;
      case data_overflow:
        printf("OVERFLOW second parametr\n");
        return 1;
      case data_underflow:
        printf("UNDERFLOW second parametr\n");
        return 1;
      }
      break;
    case incorrect_data:
      printf("INCORRECT INPUT\n");
      printf("First parametr not number\n");
      return 1;
    case data_overflow:
      printf("OVERFLOW first parametr\n");
      return 1;
    case data_underflow:
      printf("UNDERFLOW second parametr\n");
      return 1;
    }
  }

  printf("\n\nM8O-211B-22  Mashrabova  lab1 tack9\n");
  return 0;
}
