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
    int number;
    *result = 0;
    sscanf(hex, "%x", &number);
    printf("HEX=%d\n", number);

    int buffer;
    while (fread(&buffer, sizeof(int), 1, file) == 1)
    {
        unsigned char *bytes = (unsigned char *)&buffer;
        for (int i = 0; i < sizeof(int); i++)
        {
            printf("Byte: %02x\n", bytes[i]);
            if (bytes[i] == (number & 0xFF))
            {
                (*result)++;
            }
            number >>= 8; // сдвигаем маску на 8 бит для сравнения следующего байта
        }
    }
    return (*result);
}

#endif
