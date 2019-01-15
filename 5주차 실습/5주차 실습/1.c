#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct Node {//노드
	int data;
	struct Node * next;
}Node;

/*
typedef struct List {//리스트 이뤄진 요소
	Node * head;
	Node * tail;
	Node * current;

	int NumOfData;
}List;
*/

void mergeSort(Node * NODE);
Node * merge(Node * a, Node *b);
void partition(Node ** head, Node ** Front, Node ** Last);

/*
void Initialize(List * list) {//처음 리스트 초기화 시키기
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
	list->NumOfData = 0;
}*/

void insert_Node(Node ** head, int data) {//리스트 하나
	Node * newNode = (Node *)malloc(sizeof(Node));
	Node * HEAD = *head;
	Node * tmp = HEAD;

	newNode->next = NULL;
	newNode->data = data;

	if (HEAD == NULL) {//노드가 하나도 없을때
		HEAD = newNode;
	}
	else {
		while (tmp->next!=NULL) {
			tmp = tmp->next;
		}
		tmp->next = newNode;
	}
	
}

void mergeSort(Node ** NODE) {//합병정렬을 해냄//merge들이 합쳐져서 mergeSort
	Node * a, *b;
	Node * head = *NODE;

	if (head == NULL||head->next==NULL) {//아예 없을때 하나 있을 때
		return;
	}
	partition(NODE, &a, &b);
	mergeSort(&a);
	mergeSort(&b);
	NODE = &merge(&a, &b);

}

Node * merge(Node * a,Node * b) {//두개의 리스트 합병시키는 함수
	Node * result = NULL;
	Node * p;

	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;		//여기까지가 범위제한?

	//b가 마지막노드아닌가???????????

	if (a->data <= b->data) {
		result = a;
		a = a->next;
	}
	else {
		result = b;
		b = b->next;
	}
	p = result;

	while (a != NULL && b != NULL) {
		if (a->data <= b->data) {
			p->next = a;
			a = a->next;
			p = p->next;
		}
		else {
			p->next = b;
			b = b->next;
			p = p->next;
		}
	}
	if (a == NULL) {
		p->next = b;
	}
	else {
		p->next = a;
	}

	return result;

}

void partition(Node ** head, Node ** Front, Node ** Last) { //리스트를 두개로 나누는데 대신 할당하지 않은 상태로 두개를 반환
	Node *fast,*slow;
	Node * HEAD = *head;

	slow = HEAD;
	fast = HEAD->next;

	if (slow == NULL || fast == NULL) {
		*Front = slow;
		*Last = NULL;
	}
	else {
		while (fast != NULL) {
			fast = fast->next;
			if (fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}
		*Front = HEAD;
		*Last = slow->next;
		slow->next = NULL;
	}
}

void printList(Node * node) {
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->next;
	}
}

int main() {
	int n,i,num;
	Node ** head=(Node **)malloc(sizeof(Node *));
	(*head)->next = NULL;
	scanf("%d", &n);
	
	for (i = 0; i < n; i++) {
		scanf("%d", &num);
		insert_Node(head, num);
	}

	mergeSort(head);
	printList((*head)->next);
}