#include "action.h"

int main()
{
    FILE *file = fopen("file.txt", "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }

    int romanNumber, zeckendorfNumber, cv_num_lower, num;
    unsigned int cv_num_upper;
    overfscanf(file, "%Ro %Zr %Cv %CV %d", &romanNumber, &zeckendorfNumber, &cv_num_lower, 16, &cv_num_upper, 16, &num);
    printf("From file:\n");
    printf("Roman Number ---> %d\n", romanNumber);
    printf("Zeckendorf Number ---> %u\n", zeckendorfNumber);
    printf("Decimal Number 1 ---> %d\n", cv_num_lower);
    printf("Decimal Number 2 ---> %u\n", cv_num_upper);
     printf("Number ---> %d\n", num);
    fclose(file);
    char input_str[] = "XXI 11000 -af AF 21";
    int romanNumber2, zeckendorfNumber2, cv_num_lower2, number;
    unsigned int cv_num_upper2;
    oversscanf(input_str, "%Ro %Zr %Cv %CV %d", &romanNumber2, &zeckendorfNumber2, &cv_num_lower2, 16, &cv_num_upper2, 16, &number);

    printf("From string:\n");
    printf("Roman Number ---> %d\n", romanNumber2);
    printf("Zeckendorf Number ---> %u\n", zeckendorfNumber2);
    printf("Decimal Number 1 ---> %d\n", cv_num_lower2);
    printf("Decimal Number 2 ---> %u\n", cv_num_upper2);
    printf("Number ---> %d\n", number);
    return 0;
}
