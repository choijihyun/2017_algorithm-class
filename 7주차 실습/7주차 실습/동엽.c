#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct tn {
	int key;
	struct tn *LChild, *RChild, *Parent;
}TreeNode;

typedef struct tree {
	TreeNode *root;
}TREE;
typedef char BOOL;

void inOrderTraverse(TREE *);
int findElement(TREE *, int);
void insertItem(TREE *, int);
TreeNode* treeSearch(TREE *, int);
void removeElement(TREE *, int);
BOOL isExternal(TreeNode *);
TreeNode* inOrderSucc(TreeNode *);
TreeNode* sibling(TreeNode *);
TreeNode* reduceExternal(TREE *, TreeNode *);
void rFreeTree(TreeNode * root);
void freeTree(TREE * T);
void initTree(TREE *);
TreeNode* getNode();
void initNode(TreeNode*, int);
void visit(TreeNode *);

void main()
{
	char cmd;
	int key;
	int data;
	TREE T;
	initTree(&T);

	while (1)
	{
		scanf("%c", &cmd);
		switch (cmd)
		{
		case 'i':
			scanf("%d", &key);
			insertItem(&T, key);
			break;
		case 'd':
			scanf("%d", &key);
			removeElement(&T, key);
			break;
		case 's':
			scanf("%d", &key);
			data = findElement(&T, key);
			if (!data) printf("X\n");
			else printf("%d\n", data);
			break;
		case 'p':
			inOrderTraverse(&T);
			printf("\n");
			break;
		case 'q':
			return;
		default:
			break;

		}
	}

	freeTree(&T);
}

void initTree(TREE *T)
{
	T->root = NULL;
}


TreeNode * getNode()
{
	TreeNode *node;

	node = (TreeNode *)malloc(sizeof(TreeNode));
	node->LChild = NULL;
	node->RChild = NULL;
	node->Parent = NULL;
	node->key = 0;
	return node;
}
void initNode(TreeNode* t, int key)
{
	t->key = key;
	t->LChild = getNode();
	t->RChild = getNode();
}

void visit(TreeNode* t)
{
	printf(" %d", t->key);
}
void RinOrderTraverse(TreeNode *root)
{
	if (isExternal(root)) return;
	visit(root);
	RinOrderTraverse(root->LChild);
	RinOrderTraverse(root->RChild);
}
void inOrderTraverse(TREE *T)
{
	RinOrderTraverse(T->root);
}

int findElement(TREE *T, int key)
{
	if (T->root == NULL) return FALSE;
	TreeNode *target = treeSearch(T, key);

	if (target->key == key) return key;
	else return FALSE;
}


void insertItem(TREE *T, int key)
{
	TreeNode *root = T->root;
	TreeNode *par;

	if (root == NULL)
	{
		root = getNode();
		initNode(root, key);
		root->LChild->Parent = root;
		root->RChild->Parent = root;
		T->root = root;
		return;
	}
	par = treeSearch(T, key);
	if (par->key == key) return;
	//printf("%p %p %p\n", par, root->LChild, root->RChild);
	initNode(par, key);
	par->LChild->Parent = par;
	par->RChild->Parent = par;
}

TreeNode *rTreeSearch(TreeNode *root, int key)
{
	TreeNode *t = root;

	if (root->key == key) return t;

	if (!isExternal(t) || (t->key != key && !isExternal(t)))
	{
		if (t->key > key) return rTreeSearch(t->LChild, key);
		else return rTreeSearch(t->RChild, key);
	}

	return t;

}
TreeNode * treeSearch(TREE *T, int key)
{
	TreeNode *root = T->root;
	return rTreeSearch(root, key);
}
void removeElement(TREE *T, int key)
{
	if (T->root == NULL || key == 0)
	{
		printf("X\n");
		return;
	}
	TreeNode *t = treeSearch(T, key);
	if (t->key != key)
	{
		printf("X\n");
		return;
	}
	printf("%d\n", t->key);
	TreeNode *z = t->LChild;
	TreeNode *y = t->RChild;
	if (isExternal(z) || isExternal(y))
	{
		if (isExternal(z)) reduceExternal(T, z);
		else if (isExternal(y)) reduceExternal(T, y);
		return;
	}

	y = inOrderSucc(t);
	t->key = y->key;
	z = y->LChild;

	reduceExternal(T, z);

}

BOOL isExternal(TreeNode *w)
{
	if (w->LChild == NULL && w->RChild == NULL) return TRUE;
	else return FALSE;
	return 0;
}

TreeNode * inOrderSucc(TreeNode *w)
{
	w = w->RChild;
	while (!isExternal(w->LChild))
	{
		w = w->LChild;
	}
	return w;
}

TreeNode* sibling(TreeNode* w)
{
	if (w->Parent->LChild == w)
		return w->Parent->RChild;
	else
		return w->Parent->LChild;
}
void freeNode(TreeNode **t)
{
	TreeNode *temp = *t;
	if (temp == NULL) return;
	if (temp->LChild != NULL) free(temp->LChild);
	if (temp->RChild != NULL) free(temp->RChild);
	free(temp);
}
TreeNode * reduceExternal(TREE *T, TreeNode *z)
{
	TreeNode* w = z->Parent;
	TreeNode* zs = sibling(z);
	TreeNode *g;

	if (w->Parent == NULL)
	{
		T->root = zs;
		zs->Parent = NULL;

	}
	else
	{
		g = w->Parent;
		zs->Parent = g;
		if (w == g->LChild) g->LChild = zs;
		else g->RChild = zs;
	}


	freeNode(&z);
	free(w);
	return zs;
}

void rFreeTree(TreeNode *root)
{
	if (root == NULL) return;
	rFreeTree(root->LChild);
	rFreeTree(root->RChild);
	free(root);
}
void freeTree(TREE * T)
{
	rFreeTree(T->root);
}