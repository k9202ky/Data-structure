#include <stdio.h>
#include <stdlib.h>
typedef struct _Intnode{
		int value;
		struct _Intnode *next;
}Intnode;

Intnode *createnode(int value){
	Intnode *n = (Intnode*)malloc(sizeof(Intnode));
	n->value = value;
	n->next = NULL;
	return n;
}

int length(Intnode *head){
	int count=0;
	Intnode *cur_node = head;
	while(cur_node!=NULL){
		cur_node=cur_node->next;
		count++;
	}
	return count;
}

int containsvalue(Intnode *head, int target){
	Intnode *cur_node= head;
	while(cur_node!=NULL){
		if(cur_node->value==target){
			return 1;
		}
		else{
			cur_node=cur_node->next;
		}	
	}
	return 0;
}
void printvalue(Intnode *head){
	Intnode *cur_node = head;
	while(cur_node!=NULL){
		printf("%d ",cur_node->value);
		cur_node=cur_node->next;
	}
	printf("\n");
}
	
void findtailnode(Intnode *head){
	Intnode *cur_node = head;
	while(cur_node!=NULL){
		if(cur_node->next==NULL){
			printf("The last ndoe is %d\n",cur_node->value);
		}
		cur_node=cur_node->next;
	}
}

int main(){
	Intnode *n1, *n2, *n3, *n4;
	n1=createnode(10);
	n2=createnode(20);
	n3=createnode(30);
	n4=createnode(40);
	n1->next = n2; n2->next = n3; n3->next = n4;
	printvalue(n1);
	findtailnode(n1);
	printf("Length of list = %d\n", length(n1));
	printf("20 in the list? %d\n", containsvalue(n1, 20));
	printf("50 in the list? %d\n", containsvalue(n1, 50));
	return 0;
}