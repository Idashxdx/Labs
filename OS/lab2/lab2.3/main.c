
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define COUNT_PHILOS 5

pthread_t philosopher[COUNT_PHILOS];
pthread_mutex_t forks[COUNT_PHILOS];

void philosopher_lunch(int id)
{
    int left_fork = id;
    int right_fork = (id + 1) % COUNT_PHILOS;

    // 1. Размышляет
    printf("Philosopher %d is thinking\n", id + 1);
    // 2. Берет левую вилку
    printf("Philosopher %d takes the left fork\n", id + 1);
    pthread_mutex_lock(&forks[left_fork]); // захватываем
    // 3. Берет правую вилку
    printf("Philosopher %d takes the right fork\n", id + 1);
    pthread_mutex_lock(&forks[right_fork]);
    // 4. Кушает
    printf("Philosopher %d eats\n", id + 1);
    // 5. Кладет левую вилку
    printf("Philosopher %d puts down the left fork\n", id + 1);
    pthread_mutex_unlock(&forks[left_fork]); // освобождаем ранее захватанный
    // 6. Кладет правую вилку
    printf("Philosopher %d puts down the right fork\n", id + 1);
    pthread_mutex_unlock(&forks[right_fork]);
    // 7. Наелся и спит
    printf("Philosopher %d has eaten and is sleeping\n", id + 1);
}
int main(void)
{
    for (int i = 1; i <= COUNT_PHILOS; i++)
    {
        pthread_mutex_init(&forks[i], NULL); // инициализация
    }
    for (int i = 1; i <= COUNT_PHILOS; i++)
    {
        pthread_create(&philosopher[i], NULL, (void *)philosopher_lunch, (void *)(intptr_t)i); // создание,запуск потока
    }
    for (int i = 1; i <= COUNT_PHILOS; i++)
    {
        pthread_join(philosopher[i], NULL); // ожидание конца
    }
    for (int i = 1; i <= COUNT_PHILOS; i++)
    {
        pthread_mutex_destroy(&forks[i]); // уничтожение
    }

    printf("All the philosophers have eaten and are sleeping");
    printf("\n\nM8O-211B-22  Mashrabova OS lab2 tack3\n");
    return 0;
}
