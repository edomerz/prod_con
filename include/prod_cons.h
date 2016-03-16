/*
	prod_cons
*/
#ifndef __PROD_CONS_H__
#define __PROD_CONS_H__

#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h> /* nanosleep() */


#include "circ_q.h"

typedef struct arg_t
{
	int delay;
	circ_q_t *q;
	sem_t sem[2];
	pthread_mutex_t *mutex;
}arg_t;

void *TProd(void *arg);

void *TCon(void *arg);
	
#endif /* ifndef __PROD_CONS_H__*/
