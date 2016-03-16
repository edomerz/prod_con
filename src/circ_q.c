/*
 * circ_q.c

 *
 *  Created on: Mar 15, 2016
 *      Author: developer
 */

#include <assert.h>

#include "circ_q.h"



typedef struct circ_q_adt
{
	int capacity;
	int read_i; 		/* read index */
	int write_i; 	/* write index */
	int arr[SIZE];

}circ_q_adt;

/* create circ_buffer capacity in bytes */
circ_q_t* CircQCreate(void)
{
	circ_q_t *circ_q = (circ_q_t*)calloc(sizeof(circ_q_t), 1);
	if(!circ_q)
	{
		printf("\n[%s %s %d]%s\n", __FILE__, __func__, __LINE__, ("error malloc cric q "));
		return(NULL);

	}

	circ_q->capacity = 0;
	circ_q->read_i = 0;
	circ_q->write_i = 0;


	return(circ_q);
}

/* destroy circ_buf_t */
void CircQDestroy(circ_q_t* circ_q)
{
	assert(circ_q);
	free(circ_q);

	return;
}

/* – how capacity left to write to */
int CircQFreeSpace(const circ_q_t* q)
{
	return(q->capacity);
}

/* enqueue  */
void CircQEnqueue(circ_q_t* circ_q, int data)
{
	assert(circ_q);

	if(circ_q->capacity < SIZE)
	{
		circ_q->arr[circ_q->write_i] = data;
		++circ_q->capacity;
		circ_q->write_i = (circ_q->write_i + 1) % SIZE;
	}

	return;
}


 /*dequeue */
int CircQDequeue(circ_q_t* q)
{
	int ret = (assert(q), 0);

	ret = q->arr[q->read_i];
	--q->capacity;
	q->read_i = (q->read_i + 1) % SIZE;

	return(ret);
}

/* check if buffer is empty return 1 if empty or 0 if not */
int CircQIsEmpty(const circ_q_t* q)
{
	return(q->capacity == 0);
}

