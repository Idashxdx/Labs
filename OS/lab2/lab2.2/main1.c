
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    int pid;
    pid = fork();
    printf("%d\n", pid);
    printf("\n\nM8O-211B-22  Mashrabova OS lab2 tack2.1\n");
    return 0;
}
//создается дочерний процесс
//fork выводит индикатор - =0-->дочерний, >0-->род.