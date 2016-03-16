#include "prod_cons.h"
	
int main(int argc, char* argv[], char** envp)
{
	pthread_t t_con, t_pro;
	int s = -9;
	sem_t sem_p, sem_c;
	circ_q_t *q = 0;
	arg_t arg;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	int delay = 50000000;

	arg.mutex = &mutex;
	arg.delay = delay;

	if(sem_init(&sem_p, 0, SIZE) == -1)
	{
		printf("error: sem_init prod\n");
		return(-1);
	}

	if(sem_init(&sem_c, 0, 0) == -1)
	{
		printf("error: sem_init con\n");
		return(-2);
	}

	arg.sem[0] = sem_p;
	arg.sem[1] = sem_c;

	if(!(q = CircQCreate()))
	{
		printf("error: CircQCreate()\n");
		return(1);
	}

	arg.q = q;


	s = pthread_create(&t_pro, NULL, TProd, &arg);
	if(s)
	{
		printf("error: pthread_create pro\n");
		return(2);
	}

	s = pthread_create(&t_con, NULL, TCon, &arg);
	if(s)
	{
		printf("error: pthread_create \n");
		return(3);
	}

	/*wait for thread to terminate */
	s = pthread_join(t_con, NULL);
	if(s)
	{
		printf("error: pthread_join t_con\n");
		return(4);
	}

	s = pthread_join(t_pro, NULL);
	if(s)
	{
		printf("error: pthread_join t_pro\n");
		return(5);
	}

	CircQDestroy(q);

	if(sem_destroy(&sem_c) == -1)
	{
		printf("error: sem_destroy sem_c\n");
		return(6);
	}
	
	if(sem_destroy(&sem_p) == -1)
	{
		printf("error: sem_destroy sem_p\n");
		return(7);
	}
	
	return(0);
}
