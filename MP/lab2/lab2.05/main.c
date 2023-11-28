
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
    overfprintf(file, "5. af in 10 number system ---> %to\n", "af", 16);
    // 6. %TO –  печать целого числа в сс с основанием 10 - верхний регистр
    overfprintf(file, "6. AB in 10 number system ---> %TO\n", "AB", 16);
    // 7. %mi –  печать дампа значений в системе счисления с основанием 2 для int
    overfprintf(file, "7. memory dump int ---> %mi\n", -40);
    // 8. %mu –  печать дампа значений в системе счисления с основанием 2 для unsigned int
    overfprintf(file, "8. memory dump unsigned int ---> %mu\n", (unsigned int)40);
    // 9. %mf –  печать дампа значений в системе счисления с основанием 2 для double
    overfprintf(file, "9. memory dump float ---> %mf\n", 4.2);
    // 10. %md –  печать дампа значений в системе счисления с основанием 2 для float
    overfprintf(file, "10. memory dump double ---> %md\n", 4.2);
    fclose(file);
    // 2.
    size_t size = 1024;
    char *str = (char *)malloc(size * sizeof(char));

    if (str == NULL)
    {
        printf("malloc memory error\n");
        return 1;
    }
    char *result = oversprintf(str, size, "1. 21 in Roman numerals ---> %Ro\n", 21);

    if (result == NULL)
    {
        printf("String formatting error or buffer full\n");
    }
    else
    {
        printf("%s\n", result);
    }
    result = oversprintf(str, size, "2. 21 Zeckendorf representation ---> %Zr\n", (unsigned int)21);

    if (result == NULL)
    {
        printf("String formatting error or buffer full\n");
    }
    else
    {
        printf("%s\n", result);
    }
    result = oversprintf(str, size, "3. 175 in 16 number system ---> %Cv\n", 175, 16);
    if (result == NULL)
    {
        printf("String formatting error or buffer full\n");
    }
    else
    {
        printf("%s\n", result);
    }
    result = oversprintf(str, size, "4. -175 in 16 number system ---> %CV\n", -175, 16);
    if (result == NULL)
    {
        printf("String formatting error or buffer full\n");
    }
    else
    {
        printf("%s\n", result);
    }
    result = oversprintf(str, size, "5. af in 10 number system ---> %to\n", "af", 16);
    if (result == NULL)
    {
        printf("String formatting error or buffer full\n");
    }
    else
    {
        printf("%s\n", result);
    }
    result = oversprintf(str, size,  "6. AB in 10 number system ---> %TO\n", "AB", 16);
    if (result == NULL)
    {
        printf("String formatting error or buffer full\n");
    }
    else
    {
        printf("%s\n", result);
    }
    result = oversprintf(str, size, "7. memory dump int ---> %mi\n", -40);
    if (result == NULL)
    {
        printf("String formatting error or buffer full\n");
    }
    else
    {
        printf("%s\n", result);
    }
    result = oversprintf(str, size, "8. memory dump unsigned int ---> %mu\n", (unsigned int)40);
    if (result == NULL)
    {
        printf("String formatting error or buffer full\n");
    }
    else
    {
        printf("%s\n", result);
    }
    result = oversprintf(str, size, "9. memory dump float ---> %mf\n", 4.2);
    if (result == NULL)
    {
        printf("String formatting error or buffer full\n");
    }
    else
    {
        printf("%s\n", result);
    }
    result = oversprintf(str, size, "10. memory dump double ---> %md\n", 4.2);
    if (result == NULL)
    {
        printf("String formatting error or buffer full\n");
    }
    else
    {
        printf("%s\n", result);
    }
    free(str);

    printf("\n\nM8O-211B-22  Mashrabova  lab2 tack5\n");
    return 0;
}