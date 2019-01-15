//Ž�� �ٽ��ϱ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)

typedef struct Node {
	struct Node *lChild;
	struct Node *rChild;
	struct Node *parent;
	int key;
}Node;

Node * root = NULL;

int findElement(int key);//Ű���� ������ �ִ��� Ž��
void insertItem(int key);//������ Ʈ���� �� ��� �̾����
Node * treeSearch(Node * tree, int key);//���ϴ� Ű�� ã�Ҵ��� ���
void removeElement(int key);//Ű�� ã�Ƽ� ����
int isExternal(Node * node);//�ش� ��尡 �ܺγ������ Ȯ��
Node * inOrderSucc(Node * node);//������ȸ �İ��� ã�Ƴ�

/*
��� ���� - insertItem, isExternal,

��� ���� - treeSearch(findElement,inOrderSucc),removeElement
	=> �����ϸ� ������ ���, ������ x���

Ž��	  - treeSearch(findElement,inOrderSucc)
	=> �����ϸ� Ű ���, ������ x���

�μ�	  - inOrderSucc

����	  - q
*/

Node * inOrderSucc(Node * node) {
	node = node->rChild;

	while (node->lChild != NULL)
		node = node->lChild;
	return node;
}

int isEmpty() {
	if (root == NULL)
		return 1;
	else
		return 0;
}

void initNode() {
	root = (Node *)malloc(sizeof(Node));
	root->lChild = NULL;
	root->rChild = NULL;
	root->parent = NULL;
}

int isExternal(Node * node) {
	if (node->lChild == NULL&&node->rChild == NULL)
		return 1;
	else
		return 0;
}

int findElement(int key) {
	Node * w;
	w = treeSearch(root, key);
	printf("���� ã�� Ű���� %d\n", key);
	printf("w->key = %d\n", w->key);
	if (isExternal(w))
		return 1;
	else
		return w->key;
}

Node * treeSearch(Node * node, int key) {//��Ʈ �����ָ� ��
	if (isExternal(node))
		return node;
	if (key == node->key)
		return node;
	else if (key < node->key)
		return treeSearch(node->lChild, key);
	else
		return treeSearch(node->rChild, key);
}

void expandExternal(Node * node) {
	Node * right, *left;
	right = (Node *)malloc(sizeof(Node));	//�ܺγ��
	left = (Node *)malloc(sizeof(Node));	//�ܺγ��

	right->lChild = NULL;
	right->rChild = NULL;
	right->parent = node;
	right->key = NULL;

	left->lChild = NULL;
	left->rChild = NULL;
	left->parent = node;
	left->key = NULL;

	node->lChild = left;
	node->rChild = right;
}

void insertItem(int key) {
	Node *node;
	node = treeSearch(root, key);
	if (!isExternal(node))
		return;
	else {
		node->key = key;
		expandExternal(node);
	}
}

void removeElement(int key) {
	Node * node;
	Node * tmp, *tmp_p;
	node = treeSearch(root, key);
	if (isExternal(node)) {		//key�� ������ x���
		printf("X\n");
		return;
	}
	//���� �ϱ�
	tmp = node->rChild;
	tmp_p = tmp;
	if (node->rChild == NULL) {	//������ ��尡 ���� ��
		node->lChild->parent = node->parent;
		node->parent->lChild = node->lChild;
	}
	else {						//������ ��尡 ���� ��
		/*while (!isExternal(tmp)) {
			tmp_p = tmp;
			tmp = tmp->lChild;
		}
		if (tmp_p->rChild != NULL) {//������ �ڽ� ���� (7)
			if (isExternal(tmp_p)) {

			}
			else {

			}
		}
		else {							//������ �ڽ� ������
			node->key = node->lChild->key;
			node->lChild->parent = node->parent;
			node = node->lChild;
			free(node);
		}*/

		if (isExternal(tmp) || tmp->lChild == NULL) {//tmp���� ��� ������
			node->key = tmp->key;

			node->parent->rChild = tmp;
			tmp->parent = node->parent;
			tmp->lChild = node->lChild;
			node->lChild->parent = tmp;
		}
		else {				//tmp���� ��� ������
			while (!isExternal(tmp)) {
				tmp_p = tmp;
				tmp = tmp->lChild;
			}

			node->key = tmp_p->key;
			tmp_p->rChild->parent = tmp_p->parent;
			tmp_p->parent->lChild = tmp_p->rChild;
		}
		printf("%d\n", key);
	}
}



void preOrder(Node * node) {	//������ȸ
	if (node != NULL) {//������ �� ����
		if (node->key != NULL)
			printf(" %d", node->key);
		preOrder(node->lChild);
		preOrder(node->rChild);
	}
}

int main() {
	int key;
	char type;
	initNode();
	while (1) {
		scanf("%c", &type);
		if (type == 'i') {
			scanf("%d", &key);
			insertItem(key);
			getchar();
		}
		else if (type == 'd') {
			scanf("%d", &key);
			removeElement(key);
			getchar();
		}
		else if (type == 's') {
			scanf("%d", &key);
			getchar();
			if (findElement(key))
				printf("X\n");
			else
				printf("%d\n", key);
		}
		else if (type == 'p') {
			preOrder(root);
			printf("\n");
		}
		else if (type == 'q') {
			return 0;
		}
	}
}