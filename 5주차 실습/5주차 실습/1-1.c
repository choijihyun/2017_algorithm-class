#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct Node {//Node ����ü ����
	int data;
	struct Node * next;
}Node;

void push_Node(Node ** head, int num);
Node * merge(Node *a, Node *b);
void mergeSort(Node ** head);
void partition(Node **Front, Node **Last,Node * node);


void push_Node(Node ** head, int num) {//head�� ����Ű�� ��� ����
	Node * newnode = (Node *)malloc(sizeof(Node));
	newnode->data = num;
	newnode->next = (*head);
	(*head) = newnode;
}

void mergeSort(Node ** head) {
	Node * Node_Head = *head;//�Ǿճ��
	Node * a, *b;//�׳� ���

	if ((Node_Head == NULL) || (Node_Head->next == NULL))
		return;//��尡 �ϳ�(�Ǵ� ������)�� �����ʿ� ���� ����

	partition(&a, &b, Node_Head);

	mergeSort(&a);//���������͸� ����Ѱ�(����� �ּҸ� ����
	mergeSort(&b);

	*head = merge(a, b);//head�� ���ĵ� ����� ��带 ������
}

Node * merge(Node * a, Node * b) {
	Node * result = NULL;//���ĵ� ��带 ���⿡ �����Ұ���
	Node * p;//�ӽ÷� �����Ϸ��� �������� ���

	if (a == NULL)//�ϳ��� ������� �ϳ��� �� �����ִ°Ŵϱ�!!
		return b;
	else if (b == NULL)
		return a;

	if (a->data <= b->data) {//�����ϴ°Ŵϱ� ũ�� ���ϱ�
		result = a;
		a = a->next;
	}
	else {
		result = b;
		b = b->next;
	}
	p = result;//�� ������ ã�Ƽ� p�� ���������� ��ƹ���

	while (a != NULL && b != NULL) {//�Ѵ� �Ⱥ�������
		if (a->data <= b->data) {//�� ������ ã������
			p->next = a;//p�� �����Ű��
			a = a->next;//����Ȱ� �ϳ��� �ٳѱ��
			p = p->next;
		}
		else {
			p->next = b;
			b = b->next;
			p = p->next;
		}
	}
	if (a == NULL)//�� ������� �׳� ������ �̾������
		p->next = b;
	else
		p->next = a;


	return result;
}

void partition(Node ** Front, Node ** Last, Node * node) {
	Node * fast;//Ư�����
	Node * slow;//Ư������� ���� ���
	if (node == NULL || node->next == NULL) {
		*Front = node;
		*Last = NULL;//��尡 �ϳ��ۿ� �����ϱ�!
	}
	else {
		slow = node;
		fast = node->next;

		while (fast != NULL) {
			fast = fast->next;
			if (fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}

		*Front = node;
		*Last = slow->next;
		slow->next = NULL;
	}
}

void printList(Node * node) {
	while (node != NULL) {
		printf(" %d", node->data);
		node = node->next;
	}
}

void print_Node(Node ** head) {
	Node * tmp = *head;
	while (tmp != NULL) {
		printf(" %d", tmp->data);
		tmp = tmp->next;
	}
}

int main() {
	Node * a = NULL;
	int n,i,num;

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &num);
		push_Node(&a, num);
	}

	mergeSort(&a);
	printList(a);
}