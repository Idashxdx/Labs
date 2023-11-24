
#include "action.h"

int main(int argc, char *argv[])
{
    // файл для записи
    FILE *file = fopen("file.txt", "w");
    if (!file)
    {
        printf("Error open file\n");
        return 1;
    }
    // 1. %Ro – запись в римские;
    overfprintf(file, "1. 21 in Roman numerals ---> %Ro\n", 21);
    // 2. %Zr –  цекендорфова представления (прездставление чисел в сумме)
    overfprintf(file, "2. 21 Zeckendorf representation ---> %Zr\n", (unsigned int)21);
    // 3. %Cv –  печать целого числа в сс с заданным основанием - нижний регистр
    overfprintf(file, "3. 175 in 16 number system ---> %Cv\n", 175, 16);
    // 4. %CV –  печать целого числа в сс с заданным основанием - верхний регистр
    overfprintf(file, "4. -175 in 16 number system ---> %CV\n", -175, 16);
    // 5. %to –  печать целого числа в сс с основанием 10 - нижний регистр
    overfprintf(file, "4. af in 10 number system ---> %to\n", "af", 16);
    // 6. %TO –  печать целого числа в сс с основанием 10 - нижний регистр
    fclose(file);
    printf("\n\nM8O-211B-22  Mashrabova  lab2 tack5\n");
    return 0;
}