#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Node {
	struct Node * lChild;
	struct Node * rChild;
	struct Node * parent;
	int key;
}Node;

typedef struct Tree {
	Node * root;
}Tree;

void initTree(Tree * tree) {
	tree->root = NULL;
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

void initNode(Node * node,int key) {
	node->lChild = getNode();
	node->rChild = getNode();
	node->key = key;
}

int isExternal(Node * node) {
	if (node->rChild == NULL&&node->lChild == NULL)
		return 1;
	else
		return 0;
}

//Æ®¸®Å½»ö

Node * treeSearch(Tree * tree, int key) {
	Node * root = tree->root;
	return rTreeSearch(root, key);
}

int rTreeSearch(Node * tree, int key) {
	Node * t = tree;
	/*if (isExternal(tree))
		return 0;
	else {
		if (key == tree->key)
			return 1;
		else if (key < tree->key)
			return treeSearch(tree->lChild, key);
		else
			return treeSearch(tree->rChild, key);
	}*/
	if (tree->key == key)return t;
	if (!isExternal(t) || (t->key != key && !isExternal(t))) {
		if (t->key > key)return rTreeSearch(t->lChild, key);
		else return rTreeSearch(t->rChild, key);
	}
	return t;
}

//Å½»ö
int findElement(Tree * tree,int key) {
	if (tree->root == NULL) {
		printf("X\n");
		return;
	}
	Node * w = treeSearch(tree, key);
	if (w->key == key)printf("%d\n", key);
	else printf("X\n");
}

//»ğÀÔ
void insertItem(Tree * t, int key) {
	Node * root = t->root;
	Node * par;

	if (root == NULL) {
		root = getNode();
		initNode(root, key);
		root->lChild->parent = root;
		root->rChild->parent = root;
		t->root = root;
		return;
	}
	par = treeSearch(t, key);
	if (par->key == key)return;
	initNode(par, key);
	par->lChild->parent = par;
	par->rChild->parent = par;
}

Node * sibling(Node * w)
{
	if (w->parent->lChild == w)
		return w->parent->rChild;
	else
		return w->parent->lChild;
}

//³ëµåÁÙÀÌ±â
Node * reduceExternal(Tree * t, Node * z) {
	Node * w = z->parent;
	Node * zs = sibling(z);
	Node * g;

	if (w->parent == NULL) {
		t->root = zs;
		zs->parent = NULL;
	}
	else {
		g = w->parent;
		zs->parent = g;
		if (w == g->lChild)g->lChild = zs;
		else g->rChild = zs;
	}
	return zs;
}


//»èÁ¦
void removeElement(Tree * t, int key) {
	if (t->root == NULL || key == 0) {
		printf("X\n");
		return;
	}
	Node * node = treeSearch(t, key);
	if (node->key != key) {
		printf("X\n");
		return;
	}

	printf("%d\n", key);
	Node * z = node->lChild;
	Node * y = node->rChild;
	if (isExternal(z) || isExternal(y)) {
		if (isExternal(z))reduceExternal(t, z);
		else if (isExternal(y))reduceExternal(t, y);
		return;
	}
	
}

Node * inOrderSucc(Node * w) {
	w = w->rChild;
	while (!isExternal(w->lChild))
		w = w->lChild;
	return w;
}