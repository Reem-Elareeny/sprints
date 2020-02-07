
#include "queue.h"

void createQueue(QUEUE ** ptr,int size){
	//STACK stact
	(*ptr) = (QUEUE*)malloc(sizeof(QUEUE));
	(*ptr) ->size = size;
	(*ptr) ->last = 0;
	(*ptr) ->start = 0;
	(*ptr) ->front = (int*)malloc(size*sizeof(int));
	(*ptr) ->rear = (*ptr) ->front;
//	printf("in create\n");
}

void enqueue(QUEUE ** ptr, int data){
	//printf("%d\n",data);
	if((*ptr) ->last <= (*ptr) ->size){
		(*ptr) ->rear[(*ptr) ->last] = data;
		//printf("%d\n",(*ptr) ->rear[(*ptr) ->last]);
	}else if((*ptr) ->last > (*ptr) ->size){
		printf("size exceeded\n");
	}
	(*ptr) ->last++;

}

int dequeue(QUEUE ** ptr){
	int data = 0;
	if((*ptr)->rear <=  0){
		data = -1;
	}else if((*ptr)->rear > 0){
		data = (*ptr) ->front[(*ptr) ->start];
	}
	(*ptr) ->start ++;
	return data;
}
