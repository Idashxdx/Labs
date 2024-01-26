#include "action.h"

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("Enter file input, file output \n");
        return 1;
    }
    else
    {

        FILE *input_file;
        input_file = fopen(argv[1], "r");
        if (!input_file)
        {
            printf("File 1 opening error\n");
            return 1;
        }
        FILE *output_file;
        output_file = fopen(argv[2], "w");
        if (!output_file)
        {
            fclose(input_file);
            printf("File 2 opening error\n");
            return 1;
        }
        Student * stud = NULL;
        size_t count_stud;
        size_t capacity;
        

    }
    printf("M8O-211B-22  Mashrabova  lab3 tack5\n");
    return 0;
}
