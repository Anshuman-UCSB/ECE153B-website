#ifndef __STM32L476R_NUCLEO_QUEUE_H
#define __STM32L476R_NUCLEO_QUEUE_H

struct Queue{
	int head;
	int tail;
	int size;
	int arr[10];
};

struct Queue* createQueue(void);
void push(struct Queue* q, int val);
int pop(struct Queue* q);
int front(struct Queue* q);
int isEmpty(struct Queue* q);
void clear(struct Queue* q);

#endif
