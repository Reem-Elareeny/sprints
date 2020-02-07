/*
 * stack.h
 *
 *  Created on: Feb 4, 2020
 *      Author: Reem el-Areeny
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
	int size;
	int last;
	int * st_array;
} STACK;


void createStack(STACK ** ptr,int size);
void push(STACK ** ptr, int data);
int pop(STACK ** ptr);

#endif /* STACK_H_ */
