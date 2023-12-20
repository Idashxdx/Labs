
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    int pid;
    pid = fork();
    printf("%d\n", pid);
    return 0;
}
//создается дочерний процесс
//fork выводит индикатор - =0-->дочерний, >0-->род.