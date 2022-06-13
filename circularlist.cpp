// C program to delete a given key from
// linked list.
#include <stdio.h>
#include <stdlib.h>
 
/* structure for a node */
typedef struct _Node{
    int data;
    struct _Node* next;
}Node;
 
/* Function to insert a node at the beginning of
   a Circular linked list */
void push(Node** head_ref, int data)
{
    // Create a new node and make head as next
    // of it.
    Node* ptr1 = (Node*)malloc(sizeof(Node));
    ptr1->data = data;
    ptr1->next = *head_ref;
 
    /* If linked list is not NULL then set the
       next of last node */
    if (*head_ref != NULL) {
        // Find the node before head and update
        // next of it.
      	Node* temp = *head_ref;
        while (temp->next != *head_ref)
            temp = temp->next;
        temp->next = ptr1;
    }
    else
        ptr1->next = ptr1; /*For the first node */
 
    *head_ref = ptr1;
}
 
void printNode(Node *first) {
    if(first==NULL){
        printf("\n");
        return;
    }
    Node *cur = first;
    do{
       printf("%d ",cur->data);
       cur=cur->next;
    }while(cur!=first);
    printf("\n");
}

Node *countOut(Node *first, int m) {
    int len=1;
    Node *cur = first;
    Node *prev =cur;
    if(first == NULL){
        return NULL;
    }
    if(first->next==first){
        first=NULL;
        return first;
    }
    while(prev->next != first){
            prev=prev->next;
			len++;
	}
    if(m%len>0){
        if(m%len==1){
            first=cur->next;
            prev->next=first;
            free(cur);
            return first;
        }
        Node *temp = first;
        for(int k=1;k<m%len-1;k++){
            temp=temp->next;
        }
        cur = temp->next;
        first = cur->next;
        temp->next = first;
        free(cur);
        return first;
    }
    if(m%len==0){
        Node *temp = first;
        while(temp->next->next!=first){
            temp=temp->next;
        }
        Node *lastnode = temp->next;
        temp->next = first;
        free(lastnode);
        return first;
    }
    return first;
}


int main(){
    Node *head = NULL;
  	push(&head,10);
    push(&head,1);
    push(&head,2);
    push(&head,3);
    push(&head,4);
    printf("List Before Deletion: ");
    printNode(head);
   	head = countOut(head, 1);
   	printNode(head);
   	printf("\n");
   	head = countOut(head, 3);
    printf("List After Deletion: ");
    printNode(head);
    printf("\n");
    
    return 0;
}