#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Treenode{
	char word[101];
	struct _Treenode *left, *right;
}Treenode, *Treenodeptr;

typedef void (*visit_fuc) (Treenodeptr node);

Treenodeptr buildTree(FILE *in){
	char word[101];
	fscanf(in, "%s", word);
	if(strcmp(word,"@")==0){
		return NULL;
	}
	else{
		Treenodeptr root = (Treenodeptr)malloc(sizeof(Treenode));
		strcpy(root->word,word);
		root->left = buildTree(in);
		root->right = buildTree(in);
		return root;
	}
}

void preOrder(Treenodeptr root, visit_fuc v){
	if(root==NULL){
		return;
	}
	v(root);
	preOrder(root->left, v);
	preOrder(root->right, v);
}

void inOrder(Treenodeptr root, visit_fuc v){
	if(root==NULL){
		return;
	}
	inOrder(root->left, v);
	v(root);
	inOrder(root->right, v);
}

void postOrder(Treenodeptr root, visit_fuc v){
	if(root==NULL){
		return;
	}
	postOrder(root->left, v);
	postOrder(root->right, v);
	v(root);
}

void printnode2(Treenodeptr node){
	printf("%s::",node->word);
}

void printnode(Treenodeptr node){
	printf("%s ",node->word);
}

int getnumnode(Treenodeptr node){
	if(node==NULL){
		return 0;
	}
	else{
		return getnumnode(node->left)+getnumnode(node->right)+1;
	}
}

int getnumleaves(Treenodeptr node){
	if(node==NULL){
		return 0;
	}
	if(node->left || node->right){
		return getnumleaves(node->left)+getnumleaves(node->right);
	}
	else{
		return 1;
	}
}

int getHeight(Treenodeptr node){
	int h_l,h_r;
	if(node==NULL){
		return 0;
	}
	h_l = getHeight(node->left);
	h_r = getHeight(node->right);
	return (h_l>h_r)?h_l+1:h_r+1;
}

int getDepth(Treenodeptr node){
	int h_l,h_r;
	if(node==NULL){
		return -1;
	}
	h_l = getDepth(node->left);
	h_r = getDepth(node->right);
	return (h_l>h_r)?h_l+1:h_r+1;
}

int main(){
	FILE *in;
	Treenodeptr root;
	in = fopen("tree.in", "r");
	root=buildTree(in);
	fclose(in);
	printf("Preorder way:");
	printf("\n");
	preOrder(root, printnode);
	printf("\n");
	preOrder(root, printnode2);
	printf("\n");
	printf("Inorder way:");
	printf("\n");
	inOrder(root, printnode);
	printf("\n");
	inOrder(root, printnode2);
	printf("\n");
	printf("Postorder way:");
	printf("\n");
	postOrder(root, printnode);
	printf("\n");
	postOrder(root, printnode2);
	printf("\n");
	printf("Number of nodes: %d",getnumnode(root));
	printf("\n");
	printf("Number of leaves: %d",getnumleaves(root));
	printf("\n");
	printf("Height: %d",getHeight(root));
	printf("\n");
	printf("Depth: %d",getDepth(root));
	return 0;
}