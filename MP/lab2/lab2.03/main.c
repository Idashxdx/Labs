
#include "action.h"

int main(int argc, char *argv[])
{
    // Функция с пер.числом арг., входные--> подстрока и пути к файлам.
    // поиск всех вхождений переданной подстроки в содержимом этого файла.
    //+вывести местонахождение вхождения

    switch (substring_search("\t", 2, "file1.txt", "file2.txt"))
    {
    case correct_data:
        break;
    case incorrect_data:
        printf("Search error\n");
        break;
    case realloc_memory_error:
        printf("realloc memory error\n");
        break;
    case incorrect_file:
        printf("rerror open file\n");
        break;
    case malloc_memory_error:
        printf("malloc memory error\n");
        break;
        }

    printf("\n\nM8O-211B-22  Mashrabova  lab2 tack3\n");
    return 0;
}