//트리구축

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct Node {
	struct Node * left;
	struct Node * right;
	int id;
	int data;
}Node;

Node * tree;

void init_NULL(Node * tmp) {
	tmp->right = NULL;
	tmp->left = NULL;
}

void init() {
	Node * tmp;
	tree = (Node*)malloc(sizeof(Node));
	tree->right->data = 20;
	tree->right->id = 1;
	
	tmp = tree->right;
	tmp->left->data = 30;
	tmp->left->id = 2;
	tmp->right->data = 50;
	tmp->right->id = 3;

	tmp = tree->right->left;
	tmp->left->data = 70;
	tmp->left->id = 4;
	tmp->right->data = 90;
	tmp->right->id = 5;
	init_NULL(tmp->left);
	init_NULL(tmp->right);

	tmp = tree->right->right;
	init_NULL(tmp->left);
	tmp->right->data = 120;
	tmp->right->id = 6;

	tmp = tree->right->right->right;
	tmp->left->data = 130;
	tmp->left->id = 7;
	init_NULL(tmp->left);
	tmp->right->data = 80;
	tmp->right->id = 8;
	init_NULL(tmp->right);
}

int is_internal(Node * tmp) {//1=내부노드 0=외부노드
	if (tmp->right != NULL&&tmp->left != NULL)
		return 1;
	else
		return 0;
}

void preOrder(Node * tmp) {//선위수식
	if (is_internal(tmp->left))
		preOrder(tmp->left);

}

void inOrder(Node * tmp) {//중위수식

}

void postOrder(Node * tmp) {//후위수식

}

int main() {
	int way, n_id;

	scanf("%d %d", &way, &n_id);
}
