#include "action.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Enter files input\n");
        return 1;
    }
    else
    {

        RouteNode *routes = NULL;
        int count = argc;

        switch (read_input(&routes, count, argv))
        {
        case correct_data:
            printf("Files reading\n\n");
            
            break;
        case memory_alloc_error:
            printf("Memory allocation error\n");
            return 1;
        default:
            printf("Incorrect data in file\n");
            return 1;
        }
    }
    printf("M8O-211B-22  Mashrabova  lab3 tack6\n");
    return 0;
}
