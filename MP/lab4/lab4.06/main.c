#include "action.h"
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Enter file\n");
        return 1;
    }
    switch (read_input(argv[1]))
    {
    case correct_data:
        printf("Files reading\n");
        break;
         case incorrect_data:
        printf("Incorrect data in file\n");
        break;
    case file_open_error:
        printf("File opened error\n");
        break;
    case memory_alloc_error:
        printf("Memory allocation error\n");
        break;
    case stack_is_empty:
        printf("Error when popping from stack\n");
        break;
    }
    printf("M8O-211B-22  Mashrabova  lab4 tack5\n");
    return 0;
}