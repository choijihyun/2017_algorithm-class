#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct Node {
	struct Node * lChild;
	struct Node * rChild;
	struct Node * parent;
	int key, height;
}Node;

Node * root = NULL;

int isRoot(Node * node) {
	if (node == root)
		return 1;
	else
		return 0;
}


Node * getNode() {	//외부노드
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

//void initNode(Node *node, int key) {
//	node->key = key;
//	node->lChild = getNode();
//	node->rChild = getNode();
//}

void expandExternal(Node *w) {	//외부->내부로 바꿈
	Node *l, *r;
	l = (Node *)malloc(sizeof(Node));
	r = (Node *)malloc(sizeof(Node));

	l->lChild = NULL;
	l->rChild = NULL;
	l->height = 0;
	l->parent = w;
	l->key = 0;

	r->lChild = NULL;
	r->rChild = NULL;
	r->height = 0;
	r->parent = w;
	r->key = 0;

	w->lChild = l;
	w->rChild = r;
	w->height = 1;
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

int findElement(Node * node, int key) {
	if (node->key == key)
		return 1;
	else
		return 0;
}

Node * restructure(Node * x) {
	Node *y, *z, *a, *b, *c;
	Node *T0, *T1, *T2, *T3;
	//printf("restructure\n");
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

	if (w == NULL)
		return 1;

	l = w->lChild;
	r = w->rChild;

	if (!isExternal(l)) {
		if (l->rChild->height > l->lChild->height)
			l->height = l->rChild->height + 1;
		else
			l->height = l->lChild->height + 1;
	}

	if (!isExternal(r)) {
		if (r->rChild->height > r->lChild->height)
			r->height = r->rChild->height + 1;
		else
			r->height = r->lChild->height + 1;
	}

	if (w->parent == NULL) {
		if (l->height > r->height)
			w->height = l->height + 1;
		else
			w->height = r->height + 1;
	}

	balance = r->height - l->height;
	if (balance < 0)balance *= -1;
	//printf("w->height = %d ", w->height);
	//printf("w->height->l = %d ", w->lChild->height);
	//printf("w->height->r = %d\n", w->rChild->height);
	return (balance < 2);
}

void searchAndRepairAfterInsertion(Node *w) {
	Node *x, *y, *z;
	z = w;

	while (heightUpdateAndBalanceCheck(z)) {
		if (z->parent == NULL)
			return;
		z = z->parent;
	}

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
		if (z->parent == NULL)
			return;
		z = z->parent;
	}
}

void insertItem(int key) {
	Node * w;
	//w = (Node *)malloc(sizeof(Node));
	w = treeSearch(root, key);
	if (!isExternal(w))
		return;
	else {
		w->key = key;
		expandExternal(w);
		searchAndRepairAfterInsertion(w);
	}
}

/*
void insertItem(int key) {
Node * node;

node = treeSearch(root, key);
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
searchAndRepairAfterInsertion(node);
//printf("key = %d parent.key = %d PARENT = %d\n", node->key, node->parent->key, PARENT->key);
}
*/

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

	if (w->parent == NULL) {
		root = zs;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;
		if (w->key == g->lChild->key)
			g->lChild = zs;
		else
			g->rChild = zs;
	}

	free(z);
	free(w);
	return zs;
}

void searchAndRepairAfterRemoval(Node *w) {
	Node * z, *x, *y, *b;
	z = w;
	while (heightUpdateAndBalanceCheck(z)) {
		if (z->parent == NULL)
			return;
		z = z->parent;
	}

	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;

	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else if (y->lChild->height < y->rChild->height)
		x = y->rChild;
	else {
		if (z->lChild->key == y->key)
			x = y->lChild;
		else
			x = y->rChild;
	}

	b = restructure(x);
	searchAndRepairAfterRemoval(b);
}

void removeElement(int key) {
	Node * w, *z, *zs, *y;

	w = treeSearch(root, key);
	if (isExternal(w)) {
		printf("X\n");
		return;
	}

	z = w->lChild;

	if ( !isExternal(z) )
		z = w->rChild;

	if ( isExternal(z) )
		zs = reduceExternal(z);
	else {
		z = inOrderSucc(w);
		y = z->parent;
		w->key = y->key;
		zs = reduceExternal(z);
	}
	searchAndRepairAfterRemoval(zs->parent);
	printf("%d\n", key);
}

void preOrder(Node * node) {
	if (node != NULL) {
		if (node->key != 0) {
			printf(" %d", node->key);
			//	printf(" (height = %d)\n", node->height);
		}
		preOrder(node->lChild);
		preOrder(node->rChild);
	}
}

int main() {
	char ch;
	int num;
	Node* tmp;

	root = (Node *)malloc(sizeof(Node));
	root->lChild = NULL;
	root->rChild = NULL;
	root->parent = NULL;
	root->height = 0;

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
			if (findElement(tmp, num))
				printf("%d\n", num);
			else
				printf("X\n");
		}
		else if (ch == 'd') {
			scanf("%d", &num);
			getchar();
			removeElement(num);
		}
		else if (ch == 'p') {
			preOrder(root);
			printf("\n");
		}
		else if (ch == 'q')
			return 0;
	}

}