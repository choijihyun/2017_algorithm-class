//탐색 다시하기
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

int findElement(int key);//키값을 가지고 있는지 탐색
void insertItem(int key);//기존의 트리에 새 노드 이어붙임
Node * treeSearch(Node * tree, int key);//원하는 키값 찾았는지 출력
void removeElement(int key);//키값 찾아서 삭제
int isExternal(Node * node);//해당 노드가 외부노드인지 확인
Node * inOrderSucc(Node * node);//중위순회 후계자 찾아냄

/*
노드 삽입 - insertItem, isExternal,

노드 삭제 - treeSearch(findElement,inOrderSucc),removeElement
	=> 존재하면 삭제후 출력, 없으면 x출력

탐색	  - treeSearch(findElement,inOrderSucc)
	=> 존재하면 키 출력, 없으면 x출력

인쇄	  - inOrderSucc

종료	  - q
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
	printf("내가 찾을 키값은 %d\n", key);
	printf("w->key = %d\n", w->key);
	if (isExternal(w))
		return 1;
	else
		return w->key;
}

Node * treeSearch(Node * node, int key) {//루트 보내주면 됨
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
	right = (Node *)malloc(sizeof(Node));	//외부노드
	left = (Node *)malloc(sizeof(Node));	//외부노드

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
	if (isExternal(node)) {		//key값 없으면 x출력
		printf("X\n");
		return;
	}
	//삭제 하기
	tmp = node->rChild;
	tmp_p = tmp;
	if (node->rChild == NULL) {	//오른쪽 노드가 없을 때
		node->lChild->parent = node->parent;
		node->parent->lChild = node->lChild;
	}
	else {						//오른쪽 노드가 있을 때
		/*while (!isExternal(tmp)) {
			tmp_p = tmp;
			tmp = tmp->lChild;
		}
		if (tmp_p->rChild != NULL) {//오른쪽 자식 존재 (7)
			if (isExternal(tmp_p)) {

			}
			else {

			}
		}
		else {							//오른쪽 자식 없을때
			node->key = node->lChild->key;
			node->lChild->parent = node->parent;
			node = node->lChild;
			free(node);
		}*/

		if (isExternal(tmp) || tmp->lChild == NULL) {//tmp왼쪽 노드 없을때
			node->key = tmp->key;

			node->parent->rChild = tmp;
			tmp->parent = node->parent;
			tmp->lChild = node->lChild;
			node->lChild->parent = tmp;
		}
		else {				//tmp왼쪽 노드 있을때
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



void preOrder(Node * node) {	//전위순회
	if (node != NULL) {//쓰레기 값 나옴
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