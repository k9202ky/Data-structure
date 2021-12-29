#include <stdio.h>
#include <stdlib.h>
typedef struct _IntQueueA{
	int *queuearray;
	int tail;
	int head;
	int queuesize;
}IntQueueA;

IntQueueA *createIntQueueA(int size){
	IntQueueA *queue = (IntQueueA*)malloc(sizeof(IntQueueA));
	queue->head = -1;
	queue->tail = -1;
	queue->queuesize = size;
	queue->queuearray = (int*)malloc(sizeof(int)*size);
	return queue;
}

void FreeIntQueueA(IntQueueA *queue){
	free(queue->queuearray);
	free(queue);
}

int isEmpty(IntQueueA *queue){
	return queue->head == -1;
}

int isFull(IntQueueA *queue){
	return (queue->tail+1)%queue->queuesize == queue->head;
}

int peek(IntQueueA *queue){
	int value;
	if(isEmpty(queue)){
		return  0;
	}
	value = queue->queuearray[queue->head];
	return value;
}

int Dequeue(IntQueueA *queue){
	int value;
	if(isEmpty(queue)){
		return  0;
	}
	value = queue->queuearray[queue->head];
	if(queue->head == queue->tail){
		queue->head = queue->tail = -1;
	}
	else{
		queue->head = (queue->head+1)%queue->queuesize;
	}
	return value;
} 

void Enqueue(IntQueueA *queue, int value){
	if(isFull(queue)){
		return;
	}
	if(isEmpty(queue)){
		queue->head = queue->tail = 0;
	}
	else{
	queue->tail = (queue->tail+1)%queue->queuesize;
	}
	queue->queuearray[queue->tail] = value;
}

int main(){
	IntQueueA *queue;
	queue=createIntQueueA(5);
	Enqueue(queue, 1);
	Enqueue(queue, 2);
	Enqueue(queue, 3);
	Enqueue(queue, 4);
	Enqueue(queue, 5);
	while(!isEmpty(queue)){
		int v;
		printf("peek: %d\n",peek(queue));
		v=Dequeue(queue);
		printf("Dequeue value: %d\n",v);
	}
	free(queue);
	return 0;
}