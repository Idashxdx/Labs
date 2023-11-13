#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/wait.h>

#define COUNT_PHILOS 5

sem_t forks[COUNT_PHILOS];

void philosopher_lunch(int id)
{
    int left_fork = id;
    int right_fork = (id + 1) % COUNT_PHILOS;

    // 1. Размышляет
    printf("Philosopher %d is thinking\n", id + 1);
    // 2. Берет левую вилку
    sem_wait(&forks[left_fork]); // блокирует семафор
    // 3. Берет правую вилку
    sem_wait(&forks[right_fork]);
    // 4. Кушает
    printf("Philosopher %d eats\n", id + 1);
    // 5. Кладет левую вилку
    sem_post(&forks[left_fork]);
    // 6. Кладет правую вилку
    sem_post(&forks[right_fork]);
    // 7. Наелся и спит
    printf("Philosopher %d has eaten and is sleeping\n", id + 1);
}
int main(void)
{
    pid_t getpid; // для fork
    for (int i = 0; i < COUNT_PHILOS; i++)
    {
        sem_init(&forks[i], 1, 1); // инициализация
    }
    for (int i = 0; i < COUNT_PHILOS; i++)
    {
        getpid = fork(); // создаем процесс
        if (getpid == 0)
        {
            philosopher_lunch(i); // запускаем
            return 0;
        }
    }

    for (int i = 0; i < COUNT_PHILOS; i++)
    {
        wait(NULL); // ожидание конца
    }

    printf("All the philosophers have eaten and are sleeping");
    printf("\n\nM8O-211B-22  Mashrabova OS lab2 tack3\n");
    return 0;
}