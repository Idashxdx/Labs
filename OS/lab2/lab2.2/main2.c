
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    fork();
    printf("Hi\n");
    fork();
    printf("Hi\n");
    printf("\n\nM8O-211B-22  Mashrabova OS lab2 tack2.2\n");
    return 0;
}
//создается дочерний процесс
//код после fork выполняется дважды (в дочернем и родительском процессе)
//вывод 6 Hi ибо после 1 раза выполняется 2 вывода и после второго - один --> 6) 