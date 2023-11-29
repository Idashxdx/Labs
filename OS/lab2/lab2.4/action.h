#ifndef action_h
#define action_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_STR 256
// проверка
typedef enum check_data
{
    correct_data,
    incorrect_data,
    malloc_memory_error
} check_data;


check_data find_str(const char* list, const char* str);
#endif
