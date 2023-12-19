#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

typedef enum
{
	WOMAN,
	MAN,
	NO_ONE
} gender;

typedef struct
{
	int woman_count;
	int man_count;
	int people_inside;			// отслеживание количества людей внутри
	int max_people;				// макс. количество внутри
	gender human;				// пол человека
	pthread_cond_t woman_wants; // условные переменные
	pthread_cond_t man_wants;
	pthread_mutex_t mutex; // для доступа к общим данным выше
} bathroom;

void woman_wants_to_enter(bathroom *data)
{
	// план - берем мьюнтекс для доступа,
	// проверяем что ванная доступна и там нет женщин, ЕСЛИ есть -  man_wants;,
	// нет - входим, обновляем данные что внутри мужчина - увеличиваем счетчик людей
	// - выводим что он внутри, освобождаем мьюнтекс для других функций.
	pthread_mutex_lock(&data->mutex);

	while (data->people_inside == data->max_people || data->human == MAN)
	{
		pthread_cond_wait(&data->woman_wants, &data->mutex);
	}
	data->human = WOMAN;
	data->people_inside++;

	printf("A WOMAN entered the bathroom ---> %d people inside\n", data->people_inside);
	pthread_mutex_unlock(&data->mutex);
}
void man_wants_to_enter(bathroom *data)
{
	pthread_mutex_lock(&data->mutex);

	while (data->people_inside == data->max_people || data->human == WOMAN)
	{
		pthread_cond_wait(&data->man_wants, &data->mutex);
	}
	data->human = MAN;
	data->people_inside++;

	printf("A MAN entered the bathroom ---> %d people inside\n",  data->people_inside);
	pthread_mutex_unlock(&data->mutex);
}

void woman_leaves(bathroom *data)
{
	// наобоборт уменьшаем счетчик - проверяем если еще кто то в ванной -
	// если нет - присваеваем соответствующее значение. УВЕДОМЛЯЕМ другие потомки о возможности входа --->pthread_cond_broadcast
	pthread_mutex_lock(&data->mutex);

	data->people_inside--;
	if (data->people_inside == 0)
	{
		data->human = NO_ONE;
	}

	printf("A WOMAN leaving the bathroom ---> %d people inside\n", data->people_inside);
	pthread_mutex_unlock(&data->mutex);

	pthread_cond_broadcast(&data->woman_wants);
	pthread_cond_broadcast(&data->man_wants);
}
void man_leaves(bathroom *data)
{
	pthread_mutex_lock(&data->mutex);

	data->people_inside--;
	if (data->people_inside == 0)
	{
		data->human = NO_ONE;
	}

	printf("A MAN leaving the bathroom ---> %d people inside\n",  data->people_inside);
	pthread_mutex_unlock(&data->mutex);

	pthread_cond_broadcast(&data->woman_wants);
	pthread_cond_broadcast(&data->man_wants);
}

// цикл (ждем-входим-ждем-выходим-возвращаем ноль-т к процесс закончился)
void *man_in_the_bathroom(void *data)
{
	sleep(rand() % 2 + 1); // Пара секунд
	man_wants_to_enter((bathroom *)data);
	sleep(rand() % 2 + 1);
	man_leaves((bathroom *)data);
	return NULL;
}
void *woman_in_the_bathroom(void *data)
{
	sleep(rand() % 2 + 1);
	woman_wants_to_enter((bathroom *)data);
	sleep(rand() % 2 + 1);
	woman_leaves((bathroom *)data);
	return NULL;
}

int main(int argc, char *argv[])
{
	bathroom data;
	data.woman_count = 5;
	data.man_count = 5;
	data.people_inside = 0;

	if (argc != 2)
	{
		printf("Enter max people inside\n");
		return 1;
	}

	data.max_people = atoi(argv[1]);
	data.human = NO_ONE;

	// инициализируем условные переменные и мьюнтекс для управления доступом к ванной
	// создаем массив (pthread_t) потоков для представления мужчин и женщин,
	// сами потомки(pthread_create и функции для запуска функций входа и выхода),
	// пока потомки не заверщатся - ждем (pthread_create) и после ужаляем условные переменные (cond_destroy)
	pthread_cond_init(&data.woman_wants, NULL);
	pthread_cond_init(&data.man_wants, NULL);
	pthread_mutex_init(&data.mutex, NULL);
	srand(time(NULL));
	pthread_t people[data.woman_count + data.man_count];
	for (int i = 0; i < data.woman_count + data.man_count; ++i)
	{
		if (i < data.woman_count)
		{
			pthread_create(&(people[i]), NULL, woman_in_the_bathroom, &data);
		}
		else
		{
			pthread_create(&(people[i]), NULL, man_in_the_bathroom, &data);
		}
	}

	for (int i = 0; i < data.woman_count + data.man_count; ++i)
	{
		pthread_join(people[i], NULL);
	}
	pthread_cond_destroy(&data.woman_wants);
	pthread_cond_destroy(&data.man_wants);
	pthread_mutex_destroy(&data.mutex);

	printf("M8O-211B-22  Mashrabova OS lab2 tack5\n\n");
	return 0;
}