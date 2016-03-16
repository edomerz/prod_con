/*
 * circ_q.h
 *
 *  Created on: Mar 15, 2016
 *      Author: developer
 */

#ifndef INCLUDE_CIRC_Q_H_
#define INCLUDE_CIRC_Q_H_

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct circ_q_adt circ_q_t;

/* create circ_buffer capacity in bytes */
circ_q_t* CircQCreate(void);

/* destroy circ_buf_t */
void CircQDestroy(circ_q_t* circ_q);

/* – how much space left to write to */
int CircQFreeSpace(const circ_q_t* q);

/* total size of the struct in bytes */
size_t CirQCapacity(const circ_q_t* circ_q);

/* write to last location from src  return how many bytes were writen */
int CircQDequeue(circ_q_t* circ_q);

/* write to last location from src  return how many bytes were writen */
void CircQEnqueue(circ_q_t* circ_q, int data);

/* check if buffer is empty */
int CircQIsEmpty(const circ_q_t* circ_buf);


#endif /* INCLUDE_CIRC_Q_H_ */
