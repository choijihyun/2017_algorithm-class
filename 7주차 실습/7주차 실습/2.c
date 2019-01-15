//삭제를 제외한 삽입,탐색,출력 AVL트리 구현하라

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define max(a,b) (a>b)?a:b


typedef struct Node {
	struct Node * lChild;
	struct Node * rChild;
	struct Node * parent;
	int key, height;
}Node;

Node * root = NULL;


Node * getNode() {
	Node * node;
	node = (Node *)malloc(sizeof(Node));
	node->lChild = NULL;
	node->rChild = NULL;
	node->parent = NULL;
	node->key = 0;
	node->height = 0;
	return node;
}

int isExternal(Node * node) {
	if (node->lChild == NULL && node->rChild == NULL)
		return 1;
	else
		return 0;
}

void initNode(Node *node,int key) {
	node->key = key;
	node->lChild = getNode();
	node->rChild = getNode();
	node->height = 1;
}

void expandExternal(Node *w) {
	Node *l, *r;
	l = getNode();
	r = getNode();

	l->lChild = NULL;
	l->rChild = NULL;
	l->parent = w;
	l->height = 0;

	r->lChild = NULL;
	r->rChild = NULL;
	r->parent = w;
	r->height = 0;

	w->lChild = l;
	w->rChild = r;
	//w->height = 1;
}

Node * treeSearch(Node *node, int key) {
	if (isExternal(node))
		return node;

	if (node->key < key)
		return treeSearch(node->rChild, key);
	else if (node->key > key)
		return treeSearch(node->lChild, key);
	else
		return node;
}

int findElement(Node * node,int key){
	if (node->key == key)
		return 1;
	else
		return 0;
}

Node * restructure(Node * x) {
	
	Node *y, *z, *a, *b, *c;
	Node *T0, *T1, *T2, *T3;

	y = x->parent;
	z = y->parent;

	if (z->key < y->key && y->key < x->key) {
		a = z; b = y; c = x;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = c->lChild;
		T3 = c->rChild;
	}
	else if (x->key < y->key && y->key < z->key) {
		a = x; b = y;  c = z;
		T0 = a->lChild;
		T1 = a->rChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	else if (z->key < x->key && x->key < y->key) {
		a = z; b = x; c = y;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	else {
		a = y; b = x; c = z;
		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}


	if (z == root) {
		root = b;
		b->parent = NULL;
	}
	else if (z->parent->lChild == z) {
		z->parent->lChild = b;
		b->parent = z->parent;
	}
	else {
		z->parent->rChild = b;
		b->parent = z->parent;
	}


	b->lChild = a;
	a->parent = b;

	a->lChild = T0;
	T0->parent = a;
	a->rChild = T1;
	T1->parent = a;

	b->rChild = c;
	c->parent = b;

	c->lChild = T2;
	T2->parent = c;
	c->rChild = T3;
	T3->parent = c;

	return b;
}


int heightUpdateAndBalanceCheck(Node * w) {
	Node *l, *r;
	int balance;

	if (w == NULL) {
		//printf("?\n");
		return 0;
	}

	l = w->lChild;
	r = w->rChild;

	if (!isExternal(l)) {
		l->height = max(l->rChild->height, l->lChild->height);
		printf("L l_height = %d   r_height = %d\n", l->lChild->height, l->rChild->height);
	}

	if (!isExternal(r)) {
		r->height = max(r->rChild->height, r->lChild->height) + 1;
		printf("R l_height = %d   r_height = %d\n", r->lChild->height, r->rChild->height);
	}

	
	balance = r->height - l->height;
	printf("balance = %d\n", balance);
	printf("w->key = %d\n", w->key);
	if (balance < 0)balance = balance*(-1);

	if (balance < 2)
		return 1;
	else {
		//printf("호엥,,?\n");
		return 0;
	}
	//return (balance < 2);
}

void searchAndRepairAfterInsertion(Node *w) {
	Node *x, *y, *z;
	z = w;
	
	while (heightUpdateAndBalanceCheck(z)) {
		if (z == root) {
			return;
		}
		//printf("z->key = %d\n", z->key);
		z = z->parent;
		//if (z->key == root->key) {
		//	return;
		//}
		//printf("z_p->key = %d\n", z->key);
	}
	printf("key = %d\n", z->key);
	printf("개조가 필요함!\n");
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;

	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else if (y->lChild->height < y->rChild->height)
		x = y->rChild;
	else
		x = y->lChild;

	restructure(x);

	while (heightUpdateAndBalanceCheck(z)) { //조상노드로가면서 높이갱신
		if (z == root)
			return;
		z = z->parent;
	}
}
/*
void insertItem(int key) {
	Node * w;
	w = treeSearch(root, key);
	if (!isExternal(w))
		return;
	else {
		initNode(w, key);
		expandExternal(w);
		searchAndRepairAfterInsertion(w);
	}
}
*/

void insertItem(int key) {
	Node * node;

	node = treeSearch(root, key);
	//printf("root = %d\n", root->key);
	if (node == root) {
		node = getNode();
		initNode(node, key);
		node->lChild->parent = node;
		node->rChild->parent = node;
		root = node;
		return;
	}

	if (node->key == key)return;

	initNode(node, key);
	node->rChild->parent = node;
	node->lChild->parent = node;
	node->height = 1;
	//node->height = 0;
	//expandExternal(node);
	searchAndRepairAfterInsertion(node);
	//printf("key = %d parent.key = %d PARENT = %d\n", node->key, node->parent->key, PARENT->key);
}

void preOrder(Node * node) {
	if (isExternal(node))
		return;
	printf(" %d", node->key);
	preOrder(node->lChild);
	preOrder(node->rChild);
}

int main() {
	char ch;
	int num;
	Node* tmp;

	root = (Node *)malloc(sizeof(Node));
	root = getNode();

	while (1) {
		scanf("%c", &ch);
		
		if (ch == 'i') {
			scanf("%d", &num);
			getchar();
			insertItem(num);
		}
		else if (ch == 's') {
			scanf("%d", &num);
			getchar();
			tmp = treeSearch(root, num);
			if (findElement(tmp,num))
				printf("%d\n", num);
			else
				printf("X\n");
		}
		else if (ch == 'p') {
			preOrder(root);
			printf("\n");
		}
		else if (ch == 'q')
			return 0;
	}

}