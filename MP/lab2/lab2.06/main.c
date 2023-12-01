#include "action.h"

int main()
{
    
    FILE *file = fopen("file.txt", "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }
    int roman_number;
   // unsigned int Zeckendorf_number;
    overfscanf(file, "%Ro", &roman_number);
    printf("1. (Roman) Decimal Number XXI: %d\n", roman_number);
  
    fclose(file);
    return 0;
}