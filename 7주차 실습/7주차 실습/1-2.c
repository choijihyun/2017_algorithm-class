//부모 이어줘야함

#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable :4996 )

typedef struct Node {
	struct Node *lChild, *rChild, *parent;
	int key;
}Node;

Node * root = NULL;
Node * PARENT = NULL;

int isRoot(Node * node) {
	if (node == root)
		return 1;
	else
		return 0;
}

Node * getNode() {
	Node * node;
	node = (Node *)malloc(sizeof(Node));
	node->rChild = NULL;
	node->lChild = NULL;
	node->parent = NULL;
	node->key = 0;
	return node;
}

void initNode(Node * node, int key) {
	node->key = key;
	node->lChild = getNode();
	node->rChild = getNode();
}

int isExternal(Node * node) {
	if (node->lChild == NULL && node->rChild == NULL)
		return 1;
	else
		return 0;
}

Node * treeSearch(Node * node, int key) {

	if (isExternal(node)) {
		return node;
	}

	if (node->key > key) {
		PARENT = node;
		return treeSearch(node->lChild, key);
	}
	else if (node->key < key) {
		PARENT = node;
		return treeSearch(node->rChild, key);
	}
	else
		return node;
}

Node * sibling(Node * node) {
	if (node->parent->lChild == node)
		return node->parent->rChild;
	else
		return node->parent->lChild;
}

Node * inOrderSucc(Node * node) {
	node = node->rChild;
	while (node->lChild != NULL)
		node = node->lChild;
	return node;
}

Node * reduceExternal(Node * z) {
	Node *w, *zs, *g;
	
	w = z->parent;
	zs = sibling(z);

	if (isRoot(w)) {
		root = zs;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;
		if (w == g->lChild)
			g->lChild = zs;
		else
			g->rChild = zs;
	}
	free(z);
	free(w);
	return zs;
}

void removeElement(int key) {
	Node * node;
	Node *l, *r,*z,*y;
	l = (Node *)malloc(sizeof(Node));
	r = (Node *)malloc(sizeof(Node));
	
	node = treeSearch(root, key);

	if (isExternal(node) || root == NULL) {
		printf("X\n");
		return;
	}

	//l = node->lChild;
	//r = node->rChild;

	z = node->lChild;
	if (!isExternal(z))
		z = node->rChild;
	if (isExternal(z))
		reduceExternal(z);
	else {
		z = inOrderSucc(node);
		y = z->parent;
		node->key = y->key;
		reduceExternal(z);
	}
	printf("%d\n", key);

	//if (isExternal(l) || isExternal(r)) {
	//	if (isExternal(l)) reduceExternal(l);
	//	else if (isExternal(r)) reduceExternal(r);
	//	return;
	//}

	//r = inOrderSucc(node);
	//node->key = r->key;
	//l = r->lChild;

	//reduceExternal(l);
}

int findElement(int key) {
	Node * tmp = treeSearch(root, key);

	if (isExternal(tmp))
		return 0;
	else
		return 1;
}

void insertItem(int key) {	//parent를 안이어줌
	Node * node;
	
	node = treeSearch(root, key);
	
	if (isRoot(node)) {
		node = getNode();
		initNode(node, key);
		node->lChild->parent = node;
		node->rChild->parent = node;
		root = node;
		return;
	}

	if (node->key == key)return;
	initNode(node, key);
	node->parent = PARENT;
	node->rChild->parent = node;
	node->lChild->parent = node;
	//printf("key = %d parent.key = %d PARENT = %d\n", node->key, node->parent->key, PARENT->key);
}

void preOrder(Node * node) {	//전위순회
	if (node != NULL) {//쓰레기 값 나옴
		if (node->key != NULL)
			printf(" %d", node->key);
		preOrder(node->lChild);
		preOrder(node->rChild);
	}
}

int main() {
	char ch;
	int num;
	root = (Node *)malloc(sizeof(Node));
	PARENT = (Node *)malloc(sizeof(Node));
	root = getNode();
	while (1) {
		scanf("%c", &ch);
		if (ch == 'i') {
			scanf("%d", &num);
			getchar();
			insertItem(num);
		}
		else if (ch == 'd') {
			scanf("%d", &num);
			getchar();
			removeElement(num);
		}
		else if (ch == 's') {
			scanf("%d", &num);
			getchar();
			if (findElement(num))
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