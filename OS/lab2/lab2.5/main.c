#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

typedef enum
{
	woman,
    man,
    no_one
} gender;
typedef struct
{
	int woman_count;
	int man_count;
	int people_inside_count;
	int max_people_inside_count;
	gender human;
	pthread_cond_t woman_wants;
	pthread_cond_t man_wants;
	pthread_mutex_t mutex;
} bathroom;

