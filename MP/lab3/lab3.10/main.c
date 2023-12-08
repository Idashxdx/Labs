#include "action.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Enter flag and file input, file output \n");
        return 1;
    }
    else
    {

        FILE *input_file;
        FILE *output_file;
        input_file = fopen(argv[1], "r");
        output_file = fopen(argv[2], "w+");
        if (!input_file || !output_file)
        {
            printf("File opening error\n");
            return 1;
        }
    }

    printf("\n\nM8O-211B-22  Mashrabova  lab3 tack10\n");
    return 0;
}