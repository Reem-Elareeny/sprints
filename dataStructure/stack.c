/*
 * stack.c
 *
 *  Created on: Feb 3, 2020
 *      Author: Reem el-Areeny
 */

#include "stack.h"

void createStack(STACK ** ptr,int size){
	//STACK stact
	(*ptr) = (STACK*)malloc(sizeof(STACK));
	(*ptr) ->size = size;
	(*ptr) ->last = 0;
	(*ptr) ->st_array = (int*)malloc(size*sizeof(int));
//	printf("in create\n");
}

void push (STACK ** ptr,int data){
	//printf("%d\n",data);
	(*ptr) ->last++;
	if((*ptr) ->last <= (*ptr) ->size){
		(*ptr) ->st_array[(*ptr) ->last] = data;
	}else if((*ptr) ->last > (*ptr) ->size){
		printf("size exceeded\n");
	}
}

int pop(STACK ** ptr){
	int data = 0;
	if((*ptr) ->last <= 0){
		data = -1;
	}else if((*ptr) ->last > 0){
	data = (*ptr) ->st_array[(*ptr) ->last];
	}
	(*ptr) ->last--;
	return data;
}
