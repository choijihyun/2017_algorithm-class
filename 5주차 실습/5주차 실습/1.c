#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct Node {//���
	int data;
	struct Node * next;
}Node;

/*
typedef struct List {//����Ʈ �̷��� ���
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
void Initialize(List * list) {//ó�� ����Ʈ �ʱ�ȭ ��Ű��
	list->head = NULL;
	list->tail = NULL;
	list->current = NULL;
	list->NumOfData = 0;
}*/

void insert_Node(Node ** head, int data) {//����Ʈ �ϳ�
	Node * newNode = (Node *)malloc(sizeof(Node));
	Node * HEAD = *head;
	Node * tmp = HEAD;

	newNode->next = NULL;
	newNode->data = data;

	if (HEAD == NULL) {//��尡 �ϳ��� ������
		HEAD = newNode;
	}
	else {
		while (tmp->next!=NULL) {
			tmp = tmp->next;
		}
		tmp->next = newNode;
	}
	
}

void mergeSort(Node ** NODE) {//�պ������� �س�//merge���� �������� mergeSort
	Node * a, *b;
	Node * head = *NODE;

	if (head == NULL||head->next==NULL) {//�ƿ� ������ �ϳ� ���� ��
		return;
	}
	partition(NODE, &a, &b);
	mergeSort(&a);
	mergeSort(&b);
	NODE = &merge(&a, &b);

}

Node * merge(Node * a,Node * b) {//�ΰ��� ����Ʈ �պ���Ű�� �Լ�
	Node * result = NULL;
	Node * p;

	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;		//��������� ��������?

	//b�� ���������ƴѰ�???????????

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

void partition(Node ** head, Node ** Front, Node ** Last) { //����Ʈ�� �ΰ��� �����µ� ��� �Ҵ����� ���� ���·� �ΰ��� ��ȯ
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