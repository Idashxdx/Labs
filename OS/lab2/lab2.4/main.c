#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STR 256

void search_str_in_file(const char *filename, const char *str)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Ошибка откытия файла %s\n", filename);
        return;
    }
    char line[MAX_STR];
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, str) != NULL)
        {
            printf("Строка найдена в файле %s\n", filename);
            fclose(file);
            return;
        }
    }

    printf("Строка не найдена в файле %s\n", filename);
    fclose(file);
}

int main(int argc, char *argv[])
{
    printf("M8O-211B-22  Mashrabova OS lab2 tack4\n\n");
    if (argc != 3)
    {
        printf("Enter file list and string \n");
        return 1;
    }

    const char *list_of_file = argv[1];
    const char *searchString = argv[2];

    FILE *file = fopen(list_of_file, "r");
    if (!file)
    {
        printf("Ошибка откытия файла %s\n", list_of_file);
        return 1;
    }

    char filename[MAX_STR];
    while (fgets(filename, sizeof(filename), file))
    {
        size_t length = strlen(filename);
        if (length > 0 && filename[length - 1] == '\n')
        {
            filename[length - 1] = '\0';
        }
        // список разделен ; ---> читаем первое имя до ;
        char *names;
        names = strtok(filename, ";");
        while (names != NULL)
        {
            if (access(names, F_OK) != -1) // Файл существует?
            {
                // Создаем процесс, вызываем функцию поиска и выходим с успешным завершением
                if (fork() == 0)
                {
                    search_str_in_file(names, searchString);
                    exit(0);
                }
            }
            else
            {
                printf("Файла %s не существует\n", names);
            }
            names = strtok(NULL, ";");
        }
    }
    fclose(file);
    
    return 0;
}