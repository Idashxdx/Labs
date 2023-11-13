#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Enter new file\n");
        return 1;
    }
    //записываем
    FILE *file = fopen(argv[1], "wb");
    if (!file)
    {
        printf("File opening error\n");
        return 1;
    }
    unsigned char bytes[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    fwrite(bytes, sizeof(unsigned char), sizeof(bytes), file);
    fclose(file);
    //выводим
    file = fopen(argv[1], "rb");
    if (!file)
    {
        printf("File opening error\n");
        return 1;
    }
    unsigned char output;
    while (fread(&output, sizeof(unsigned char), 1, file))
    {
        printf("Byte: %u\n", output);
        printf("Position: %lu\n",ftell(file)); //ftell-опр. текущей позиции
    }
    fclose(file);
// перемещение
    file = fopen(argv[1], "rb");
    if (!file)
    {
        printf("File opening error\n");
        return 1;
    }
    fseek(file, 3, SEEK_SET);
    unsigned char buffer[4];
    fread(buffer, sizeof(unsigned char), 4, file);
    printf("\nBuffer contents after fseek and fread: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%u ", buffer[i]);
    }
    fclose(file);
    printf("\nM8O-211B-22  Mashrabova OS lab1 tack3\n");
    return 0;
}
