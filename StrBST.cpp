#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _StrBSTNode {
    char *s;
    struct _StrBSTNode *left, *right;
} StrBSTNode;

typedef struct _StrBST {
    StrBSTNode *root;
} StrBST;

typedef void (*value_handler)(const char *value, int depth);

StrBST *createStrBST() {
    StrBST *bst;
    bst = (StrBST*)malloc(sizeof(StrBST));
    bst->root = NULL;
    return bst;
}

StrBSTNode *createStrBSTNode(const char *value) {
    StrBSTNode *n = (StrBSTNode*)malloc(sizeof(StrBSTNode));
    n->left = n->right = NULL;
    n->s = (char*)malloc(strlen(value)+1);
    strcpy(n->s, value);
    return n;
}

void print(const char *value, int depth){
	printf("%s[%d] ",value,depth);
}

StrBSTNode *_addValueSB(StrBSTNode *root, const char *value) {
    int cmp;
    if (root==NULL) {
        return createStrBSTNode(value);
    }
    cmp = strcmp(value, root->s);
    if (cmp<0) {
        root->left = _addValueSB(root->left, value);
    } else if (cmp>0) {
        root->right = _addValueSB(root->right, value);
    }
    return root;
}
void addValueSB(StrBST *bst, const char *value) {
    if (value==NULL) { return; }
    bst->root = _addValueSB(bst->root, value);
}

void _toSortedList(StrBSTNode *root, value_handler handler, int depth) {
    if (root==NULL) { return; }
    _toSortedList(root->left, handler, depth+1);
    handler(root->s, depth);
    _toSortedList(root->right, handler, depth+1);
}

void toSortedList(StrBST *bst, value_handler handler) {
    _toSortedList(bst->root, handler, 0);
}

StrBSTNode *minvalue(StrBSTNode *bst){
    StrBSTNode *cur_node = bst;
    while(cur_node->left!=NULL){
        cur_node = cur_node->left;
    }
    return cur_node;
}
StrBSTNode *_delValueSB(StrBSTNode *bst, const char *value){
    if(bst == NULL){
        return bst;
    }
    int cmp = strcmp(value,bst->s);
    if(cmp<0){
        bst->left = _delValueSB(bst->left, value);
    }
    else if(cmp>0){
        bst->right = _delValueSB(bst->right, value);
    }
    else{
        if(bst->left == NULL && bst->right == NULL){
            free(bst);
            return NULL;
        }
        else if(bst->left == NULL){
            StrBSTNode *temp = bst->right;
	    free(bst);
            return temp;
        }
        else if(bst->right == NULL){
            StrBSTNode *temp = bst->left;
	    free(bst);
            return temp;
        }
        StrBSTNode *temp = minvalue(bst->right);
        bst->s = temp->s;
        bst->right = _delValueSB(bst->right, temp->s);
    }
    return bst;
}
void delValueSB(StrBST *bst, const char *value) {
    if(bst == NULL){
		return;
	}
	if(value == NULL){
		return;
	}
    if(bst->root==NULL){
        return;
    }
    bst->root = _delValueSB(bst->root, value);
}
int main(){
	StrBST *bst = createStrBST();
	addValueSB(bst, "egg");
	addValueSB(bst, "hi");
	addValueSB(bst, "cat");
	addValueSB(bst, "apple");
	addValueSB(bst, "bell");
	delValueSB(bst, "bell");
	delValueSB(bst, "cat");
	addValueSB(bst, "bell");
	addValueSB(bst, "cat");
	addValueSB(bst, "123");
	delValueSB(bst, "apple");
	delValueSB(bst, "egg");
	delValueSB(bst, "app");
	delValueSB(bst, NULL);
	toSortedList(bst, print); printf("\n");

	return 0;
}
