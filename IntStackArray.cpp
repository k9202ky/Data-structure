#include <stdio.h>
#include <stdlib.h>
typedef struct _IntStackA{
	int *stackary;
	int stacksize;
	int top;
}IntStackA;

IntStackA *createIntStackA(int  size){
	IntStackA *stack = (IntStackA*)malloc(sizeof(IntStackA));
	stack->stacksize=size;
	stack->top=-1;
	stack->stackary = (int*)malloc(sizeof(int)*size);
	return stack;
}

void freeIntStackA(IntStackA *stack){
	free(stack->stackary);
	free(stack);
}

int isEmpty(IntStackA *stack){
	return stack->top == -1;
}

int isFull(IntStackA *stack){
	return stack->top == stack->stacksize-1;
}

void pushISA(IntStackA *stack, int value, int *status){
	if(isFull(stack)){
		if(status) { *status = -1; } 
		return;
	}
	stack->top++;
	stack->stackary[stack->top]=value;
	if(status) { *status = 0; }
}

int popISA(IntStackA *stack, int *status){
	int value;
	if(isEmpty(stack)){
		if(status){ *status = -2; }  
		return 0;
	}
	value = stack->stackary[stack->top];
	stack->top--;
	if(status){ *status = 0; }
	return value;
}

int peekISA(IntStackA *stack, int *status){
	int value;
	if(isEmpty){
		if(status){ *status = -2; }
	}
	value = stack->stackary[stack->top];
	if(status){ *status = 0; }
	return value;
}

int main(){
	IntStackA *stack;
	int status;
	stack=createIntStackA(5);
	pushISA(stack, 1, &status);
	pushISA(stack, 2, &status);
	pushISA(stack, 3, &status);
	pushISA(stack, 4, &status);
	pushISA(stack, 5, &status);
	
	while(!isEmpty(stack)){
		int v;
		printf("peek= %d\n",peekISA(stack, NULL));
		v = popISA(stack, NULL);
		printf("poped value: %d\n",v);
	}
	
	freeIntStackA(stack);
	return 0;
}