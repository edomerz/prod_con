/*

 * circ_q_test.c
 *
 *  Created on: Mar 15, 2016
 *      Author: developer
 */

#include "circ_q.h"

int main(int argc, char* argv[], char** envp)
{
	int i = 0;
	circ_q_t* q = NULL;
	int isEmpty = -1;

	q = CircQCreate();

	isEmpty =  CircQIsEmpty(q);
	printf("\nis empty:%d\n", isEmpty);

	CircQEnqueue(q, -1);

	isEmpty =  CircQIsEmpty(q);
	printf("\nis empty:%d\n", isEmpty);

	printf("CircQDequeue(q): %d\n", CircQDequeue(q));

	isEmpty =  CircQIsEmpty(q);
	printf("\nis empty:%d\n", isEmpty);

	for(; i < SIZE; ++i)
	{
		CircQEnqueue(q, i);
	}

	printf("capacity: %d\n", CircQFreeSpace(q));

	printf("CircQDequeue(q): %d\n", CircQDequeue(q));
	printf("capacity: %d\n", CircQFreeSpace(q));

	CircQEnqueue(q, 101);

	for(; i > 0; --i)
	{
		printf("CircQDequeue(q): %d\n", CircQDequeue(q));
		printf("\t\t capacity: %d\n", CircQFreeSpace(q));
	}

	/*CircBufDestroy -  destroy circ_buf_t */
	CircQDestroy(q);

	return(0);
}
