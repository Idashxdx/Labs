#include <stdio.h>

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        printf("Enter file-to copy and file-to result\n");
        return 1;
    }
    else
    {
        FILE *input_file;
        FILE *output_file;
        input_file = fopen(argv[1], "r");
        output_file = fopen(argv[2], "w");
        if (!input_file)
        {
            printf("File opening error\n");
            return 1;
        }
        char symbol = fgetc(input_file);
        while (symbol != EOF)
        {
            fprintf(output_file, "%c", symbol);
            symbol = fgetc(input_file);
        }
        fclose(input_file);
        fclose(output_file);
    }
    printf("M8O-211B-22  Mashrabova OS lab1 tack3\n");
    return 0;
}
