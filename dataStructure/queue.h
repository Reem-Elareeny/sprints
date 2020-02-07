/*
 * queue.h
 *
 *  Created on: Feb 5, 2020
 *      Author: Reem el-Areeny
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct queue{
	int size;
	int last;
	int start;
	int * front;
	int * rear;
}QUEUE;

void createQueue(QUEUE ** ptr,int size);
void enqueue(QUEUE ** ptr, int data);
int dequeue(QUEUE ** ptr);

#endif /* QUEUE_H_ */
