/*
 * main.c
 *
 *  Created on: Feb 3, 2020
 *      Author: Reem el-Areeny
 */
#include "stack.h"
#include "queue.h"

void evaluateEquation(void);
void testStack(void);
void testQueue(void);
void checkBalance(void);

int main(void){

	evaluateEquation();
	testStack();
	testQueue();
	checkBalance();

	return 0;
}

void checkBalance(void){
	STACK * stack;
	int data = 10, size = 10, i = 0;
	int flag = 1;

	createStack(&stack,size);
	char str[100] = {'\0'};
	scanf("%s",str);
		while(str[i] != '\0'){
			switch(str[i]){
			case '{':
			case '(':
			case '[':
				push(&stack,str[i]);
				break;
			case '}':
				if(pop(&stack) != '{'){
					flag = 0;
					break;
				}
				break;
			case ')':
				if(pop(&stack)  != '('){
					flag = 0;
					break;
				}
				break;
			case ']':
				if(pop(&stack)  != '['){
					flag = 0;
					break;
				}
				break;
			}
			i++;
	}
		if((stack) ->last > 0){
			flag = 0;
		}
		if(flag == 0){
			printf("invalid\n");
		}else if(flag == 1){
			printf("valid\n");
		}
}

void testStack(void){
	STACK * s;

	int data = 10, size = 10, i;
	createStack(&s, data);
	//push(&s, data+1);
	for(i = 0; i < size; i++){
		push(&s, data+i);
	}

	for(i = 0; i < size; i++){
		printf("%d\n",pop(&s));
	}
}

void testQueue(void){
	QUEUE * queue;

	int data = 10, size = 10, i;
	createQueue(&queue, data);
	//enqueue(&queue, data+1);
	for(i = 0; i < size; i++){
		enqueue(&queue, data+i);
	}
	printf("---------------\n");
	for(i = 0; i < size; i++){
		printf("%d\n",dequeue(&queue));
	}
}

void evaluateEquation(void){

	STACK * stack;
	QUEUE * queue;

	int size = 100, i = 0, result = 0, value = 0, v = 0;
	int flag = 1;

	createStack(&stack,size);
	createQueue(&queue,size);

	char str[100] = {'\0'};
	scanf("%s",str);
		while(str[i] != '\0'){
			switch(str[i]){
			case '{':
			case '(':
			case '[':
				push(&stack,str[i]);
				break;
			case '}':
				if(pop(&stack) != '{'){
					flag = 0;
					break;
				}
				break;
			case ')':
				if(pop(&stack)  != '('){
					flag = 0;
					break;
				}
				break;
			case ']':
				if(pop(&stack)  != '['){
					flag = 0;
					break;
				}
				break;
			default:
					enqueue(&queue, str[i]);
				break;
			}
			i++;
	}
		if((stack) ->last > 0){
			flag = 0;
		}
		if(flag == 0){
			printf("invalid\n");
		}else if(flag == 1){
			printf("valid\n");
			while(queue->rear > 0 && flag != 0){
				v = dequeue(&queue);
				switch(v){
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '7':
					case '8':
					case '9':
						value = v - '0';
						break;
					case '+':
						//printf("%d\n",result);
						result += value;
						break;
					case '-':
						//printf("%d\n",result);
						result -= value;
						break;
					case '*':
						result *= value;
						//printf("%d\n",result);
						break;
					case '/':
						result /= value;
						//printf("%d\n",result);
						break;
					default:
						flag = 0;
						printf("Invalid\n");
						break;
					}

			}
			printf("%d\n",result);
		}
}
