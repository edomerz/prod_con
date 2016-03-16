
#include "prod_cons.h"

#define PROD 0
#define CON 1

void *TProd(void *arg)
{
	int cap = -1;
	struct timespec ts;
	int data = 0;
	int semval = -9;

	ts.tv_sec = 0;
	ts.tv_nsec = ((arg_t*)arg)->delay;
	sem_getvalue(&((arg_t*)arg)->sem[PROD], &semval);
	printf("sem value: %d\n", semval);
	printf("\n[%s %s %d]%s\n", __FILE__, __func__, __LINE__, (" "));

	while(1)
	{
		nanosleep(&ts, NULL);

		if(sem_wait(&((arg_t*)arg)->sem[PROD]) == -1)
		{
			printf("error: sem_wait\n");
			return(NULL);
		}

		pthread_mutex_lock(((arg_t*)arg)->mutex);

		CircQEnqueue(((arg_t*)arg)->q, data);
		cap = CircQFreeSpace(((arg_t*)arg)->q);
		printf("pro> cap %d\n", cap);

		pthread_mutex_unlock(((arg_t*)arg)->mutex);

		if(sem_post(&((arg_t*)arg)->sem[CON]) == -1)
		{
			printf("error: sem_post con\n");
			return(NULL);
		}
		++data;
		/*nanosleep(&ts, NULL);*/
	}
}

void *TCon(void *arg)
{
	int cap = -1;
	int data = 0;
	int semval = -9;
	struct timespec ts;

	ts.tv_sec = 0;
	ts.tv_nsec = ((arg_t*)arg)->delay;
	sem_getvalue(&((arg_t*)arg)->sem[CON], &semval);
	printf("sem value: %d\n", semval);
	printf("\n[%s %s %d]%s\n", __FILE__, __func__, __LINE__, (" "));

	while(1)
	{
		nanosleep(&ts, NULL);
		nanosleep(&ts, NULL);

		if(sem_wait(&((arg_t*)arg)->sem[CON]) == -1)
		{
			printf("error: sem_wait\n");
			return(NULL);
		}

		pthread_mutex_lock(((arg_t*)arg)->mutex);

		data = CircQDequeue(((arg_t*)arg)->q);
		cap = CircQFreeSpace(((arg_t*)arg)->q);
		printf("\t\t\t\t\t\t\t\t con> cap %d, data removed: %d\n", cap, data);

		pthread_mutex_unlock(((arg_t*)arg)->mutex);

		if(sem_post(&((arg_t*)arg)->sem[PROD]) == -1)
		{
			printf("error: sem_post pro\n");
			return(NULL);
		}
}
}
