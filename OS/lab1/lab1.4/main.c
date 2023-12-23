#include "action.h"

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("Enter a file and an action\n");
        return 1;
    }
    else
    {
        FILE *file1 = fopen(argv[1], "wb");
        if (!file1)
        {
            printf("File opening error\n");
            return 1;
        }
        unsigned char bytes[] = {1,1,1,1};
        fwrite(bytes, sizeof(unsigned char), sizeof(bytes), file1);
        fclose(file1);
        FILE *file = fopen(argv[1], "rb");
        if (!file)
        {
            printf("File opening error\n");
            return 1;
        }
        int result;
        switch (check(argv, argc))
        {
        case is_xor8:

            flag_xor8(file, &result);
            printf("Result: %d\n", result);
            fclose(file);
            break;
        case is_xor32:
            flag_xor32(file, &result);
            printf("Result: %d\n", result);
            fclose(file);
            break;
        case is_mask:
            flag_mask(file, argv[3], &result);
            printf("Result: %d\n", result);
            break;
        case is_error:
            printf("NO FLAG\n");
            break;
        }
        printf("M8O-211B-22  Mashrabova  lab1 tack4\n");
        return 0;
    }
}
