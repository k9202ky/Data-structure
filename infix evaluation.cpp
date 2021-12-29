#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct _IntStack{
	int *stackary;
	int stacksize;
	int top;
}IntStack;

typedef void (*token_handler)(const char *token, IntStack *oprtr_s, IntStack *oprnd_s);
typedef void (*finalize_parsing)(IntStack *oprtr_s, IntStack *oprnd_s);

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

int readToken(const char *s, char *token) {
    int n_blanks=0, n_chars=0;
    while (s[n_blanks]==' ') {
        n_blanks++;
    }
    if (s[n_blanks]=='\0') {
        return 0;
    }
    n_chars = n_blanks;
    if (isdigit(s[n_chars])) {
        while (isdigit(s[n_chars])) {
            token[n_chars-n_blanks] = s[n_chars];
            n_chars++;
        }
        token[n_chars-n_blanks] = '\0';
    } else if (s[n_chars]=='*' && s[n_chars+1]=='*') {
        token[0] = token[1] = '*';
        token[2] = '\0';
        n_chars += 2;
    } else {
        token[0] = s[n_chars];
        token[1] = '\0';
        n_chars += 1;
    }
    return n_chars;
}

void pop_and_eval(IntStack *oprtr_s,  IntStack *oprnd_s) {
    int op, n1, n2, i, r;
    op = popIS(oprtr_s, NULL);
    n2 = popIS(oprnd_s, NULL);
    n1 = popIS(oprnd_s, NULL);
    switch(op) {
        case '+':
            pushIS(oprnd_s, n1+n2,NULL);
            break;
        case '-':
            pushIS(oprnd_s, n1-n2,NULL);
            break;
        case '*':
            pushIS(oprnd_s, n1*n2,NULL);
            break;
        case '/':
            pushIS(oprnd_s, n1/n2,NULL);
            break;
        case '^':
            for (i=0, r=1; i<n2; i++) {
                r *= n1;
            }
            pushIS(oprnd_s, r,NULL);
    }
}

void postfix_handler(const char *token, IntStack *oprtr_s, IntStack *oprnd_s) {
    if (isdigit(token[0])) {
        int n;
        sscanf(token, "%d", &n);
        pushIS(oprnd_s, n, NULL);
    } else if (token[0]=='(') {
        pushIS(oprtr_s, '(', NULL);
    } else if (token[0]=='^' || (token[0]=='*' && token[1]=='*')) {
        while (!isEmptyIS(oprtr_s) && peekIS(oprtr_s, NULL)=='^') {
            pop_and_eval(oprtr_s, oprnd_s);
        }
        pushIS(oprtr_s, '^', NULL);
    } else if (token[0]=='*' || token[0]=='/') {
        while (!isEmptyIS(oprtr_s) && (peekIS(oprtr_s, NULL)=='*' || peekIS(oprtr_s, NULL)=='/' || peekIS(oprtr_s, NULL)=='^')) {
            pop_and_eval(oprtr_s, oprnd_s);
        }
        pushIS(oprtr_s, token[0], NULL);
    } else if (token[0]=='+' || token[0]=='-') {
        while (!isEmptyIS(oprtr_s) && peekIS(oprtr_s, NULL)!='(') {
            pop_and_eval(oprtr_s, oprnd_s);
        }
        pushIS(oprtr_s, token[0], NULL);
    } else {
        while (!isEmptyIS(oprtr_s) && peekIS(oprtr_s, NULL)!='(') {
            pop_and_eval(oprtr_s, oprnd_s);
        }
        popIS(oprtr_s, NULL);
    }
}

void postfix_end(IntStack *oprtr_s, IntStack *oprnd_s) {
    while (!isEmptyIS(oprtr_s)) {
        pop_and_eval(oprtr_s, oprnd_s);
    }
    if (isEmptyIS(oprnd_s)) {
        printf("no expression");
    } else {
        printf("%d", popIS(oprnd_s, NULL));
    }
}

void parse_infix(const char *s, token_handler handler, finalize_parsing flush_op_stack) {
    char word[100];
    int ret, n_chars, offset=0;
    IntStack *oprtr_s; /* operator stack */
    IntStack *oprnd_s; /* operand stack */

    oprtr_s = createIntStack(20);
    oprnd_s = createIntStack(20);
    while ((n_chars=readToken(s+offset, word))) {
        handler(word, oprtr_s, oprnd_s);
        offset += n_chars;
    }
    flush_op_stack(oprtr_s, oprnd_s);
    printf("\n");
}



int main(){
	parse_infix("2^3 / 4", postfix_handler, postfix_end);
	parse_infix("2+3/4", postfix_handler, postfix_end);
	parse_infix("2 / 3 + 4     ", postfix_handler, postfix_end);
	parse_infix("   (22 - 3)/4", postfix_handler, postfix_end);
	parse_infix(" 2/( 3 - 4 )", postfix_handler, postfix_end);
	parse_infix("20 ^ ( 3/4 )", postfix_handler, postfix_end);
	parse_infix("( 67 - 3 ) /4**(2 *1 )", postfix_handler, postfix_end);
	parse_infix("2", postfix_handler, postfix_end);
	parse_infix("", postfix_handler, postfix_end);
	parse_infix("2 ** ( 3 ^ 2 )", postfix_handler, postfix_end);
	return 0;
}