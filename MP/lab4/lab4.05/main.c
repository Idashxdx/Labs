#include "action.h"
#include "stack.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Enter files\n");
        return 1;
    }
    int count = argc;
    switch (read_input(count, argv))
    {
    case correct_data:
        break;
    case incorrect_data:
        printf("Incorrect data in file\n");
        break;
    case memory_malloc_error:
        printf("Memory allocation error\n");
        break;
    }
    printf("M8O-211B-22  Mashrabova  lab4 tack5\n");
    return 0;
}