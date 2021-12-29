#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct _IntStack{
	int *stackary;
	int stacksize;
	int top;
}IntStack;

typedef void (*token_handler)(const char *token, IntStack *s);
typedef void (*finalize_parsing)(IntStack *s);

IntStack *createIntStack(int size){
	IntStack *stack = (IntStack*)malloc(sizeof(IntStack));
	stack->stacksize=size;
	stack->top=-1;
	stack->stackary = (int*)malloc(sizeof(int)*size);
	return stack;
}

int isEmptyIS(IntStack *stack){
	return stack->top == -1;
}

int isFull(IntStack *stack){
	return stack->top == stack->stacksize-1;
}

void pushIS(IntStack *stack, int value, int *status){
	if(isFull(stack)){
		if(status) { *status = -1; } 
		return;
	}
	stack->top++;
	stack->stackary[stack->top]=value;
	if(status) { *status = 0; }
}

int popIS(IntStack *stack, int *status){
	int value;
	if(isEmptyIS(stack)){
		if(status){ *status = -2; }  
		return 0;
	}
	value = stack->stackary[stack->top];
	stack->top--;
	if(status){ *status = 0; }
	return value;
}

int peekIS(IntStack *stack, int *status){
	int value;
	if(isEmptyIS){
		if(status){ *status = -2; }
	}
	value = stack->stackary[stack->top];
	if(status){ *status = 0; }
	return value;
}

void parse_infix(const char *s, token_handler handler, finalize_parsing flush_op_stack) {
    char word[100];
    int n_chars, offset=0;
    IntStack *opst;

    opst = createIntStack(20); //先設定10看需要多大的空間
    while (1==sscanf(s+offset, "%s%n", word, &n_chars)) {
        handler(word, opst);
        offset += n_chars;
    }
    flush_op_stack(opst);
    printf("\n");
}

void postfix_handler(const char *token, IntStack *s) {
    if(isdigit(token[0])) {
        printf("%s ", token);
    }else if(token[0]=='(') {
        pushIS(s, '(',NULL);
    }
    else if(token[0]=='*' && token[1]=='*'){
        while(!isEmptyIS(s) && peekIS(s,NULL)!='('){
            printf("%c ",(char)popIS(s,NULL));
        }
        pushIS(s,'^',NULL);
    }
    else if(token[0]=='^'){
        while(!isEmptyIS(s) && (peekIS(s,NULL)!='(' && peekIS(s,NULL)!='*' && peekIS(s,NULL)!='/')){
            printf("%c ",(char)popIS(s,NULL));
        }
        pushIS(s,token[0],NULL);
    }
    else if (token[0]=='*' || token[0]=='/') {
        while (!isEmptyIS(s) && (peekIS(s, NULL)=='*' || peekIS(s, NULL)=='/' || peekIS(s,NULL)=='^')) {
            printf("%c ", (char)popIS(s, NULL));
        }
        pushIS(s, token[0],NULL);
        
    }else if (token[0]=='+' || token[0]=='-') {
        while (!isEmptyIS(s) && peekIS(s, NULL)!='(') {
            printf("%c ", (char)popIS(s, NULL));
        }
        pushIS(s, token[0],NULL);
    }else {
        while (!isEmptyIS(s) && peekIS(s, NULL)!='(') {
            printf("%c ", (char)popIS(s, NULL));
        }
        popIS(s, NULL);
    }
}

void postfix_end(IntStack *s) {
    while(!isEmptyIS(s)){
        printf("%c ",(char)popIS(s,NULL));
    }
}

int main(){
	parse_infix("2 ^ 3 / 4", postfix_handler, postfix_end);
	parse_infix("2 + 3 / 4", postfix_handler, postfix_end);
	parse_infix("2 / 3 + 4", postfix_handler, postfix_end);
	parse_infix("( 2 - 3 ) / 4", postfix_handler, postfix_end);
	parse_infix("2 / ( 3 - 4 )", postfix_handler, postfix_end);
	parse_infix("20 ^ ( 3 / 4 )", postfix_handler, postfix_end);
	parse_infix("( 2 - 3 ) / 4 ^ ( 5 * 6 )", postfix_handler, postfix_end);
	parse_infix("2", postfix_handler, postfix_end);
	parse_infix("20 ** ( 3 ^ 4 )", postfix_handler, postfix_end);
	return 0;
}