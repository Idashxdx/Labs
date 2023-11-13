#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum check_flag
{
    is_xor8,
    is_xor32,
    is_mask,
    is_error
};
enum check_flag check(char *argv[], int argc)
{
    char *flag = argv[2];
    if (!strcmp(flag, "xor8"))
    {
        return is_xor8;
    }
    else if (!strcmp(flag, "xor32"))
    {
        return is_xor32;
    }
    else if (!strcmp(flag, "mask"))
    {
        return is_mask;
    }
    else
    {
        return is_error;
    }
}

int flag_xor8(FILE *file, int *result)
{
    *result = 0;
    char byte;
    while (fread(&byte, sizeof(char), 1, file))
    {
        *result ^= (int)byte;
    }
}
int flag_xor32(FILE *file, int *result)
{
    *result = 0;
    char byte[4];
    int count;
    while ((count = fread(byte, sizeof(char), 4, file)))
    {
        int number = 0;
        for (int i = 0; i < count; i++)
        {
            number += byte[i] << 8 * (3 - i);
        }
        *result ^= number;
    }
}
int flag_mask(FILE *file, char *hex, int *result)
{
    int byte;
    int number;
    sscanf(hex, "%x", &number);
    printf("HEX=%d\n", number);
    *result = 0;

    while (fread(&byte, sizeof(int), 1, file))
    {
        printf("Byte:\n");
        printf("%d\n", byte);
        if (number == byte)
        {
            (*result)++;
        }
    }
}
#endif
