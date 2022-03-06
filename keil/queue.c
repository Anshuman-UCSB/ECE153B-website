#include "queue.h"
#include <stdlib.h>

struct Queue* createQueue(void){
	struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
	q->head = 0;
	q->tail = 0;
	q->size = 0;
	return q;
}

void push(struct Queue* q, int val){
	q->arr[q->tail] = val;
	q->tail++;
	q->tail%=10;
	q->size++;
}

int pop(struct Queue* q){
	int val = q->arr[q->head];
	q->head = (q->head+1)%10;
	q->size--;
	return val;
}

int front(struct Queue* q){
	return q->arr[q->head];
}

int isEmpty(struct Queue* q){
	return (q->size == 0);
}

void clear(struct Queue* q){
	q->head = 0;
	q->tail = 0;
	q->size = 0;
}
