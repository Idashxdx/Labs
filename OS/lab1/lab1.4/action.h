#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
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
    uint32_t value = (uint32_t)strtoul(hex, NULL, 16);
    uint32_t byte;
    *result = 0;

    while (fread(&byte, sizeof(byte), 1, file) == 1)
    {
        unsigned char *maskBytes = (unsigned char *)&value; 
        unsigned char *valueBytes = (unsigned char *)&byte;
         int match = 1;

            for (int i = 0; i < sizeof(byte); i++)
            {
                if (maskBytes[i] != (valueBytes[i] & maskBytes[i]))
                {
                    match = 0;  // Не соответствует маске
                    break;
                }
            }

            if (match)
            {
                result++;
            }
    }
}
#endif
