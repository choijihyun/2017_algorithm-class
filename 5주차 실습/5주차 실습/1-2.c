#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct Node {
	int data;
	struct Node * next;
}Node;

void partition(Node **Front, Node **Last,Node * node);
Node * merge(Node * a, Node * b);
void mergeSort(Node ** HEAD);
void push_Node(Node ** head, int data);

/*
Node * partition(Node * HEAD) {
	Node *head = HEAD;
	Node *slow, *fast;

	slow = head;
	fast = slow->next;

	if (slow == NULL || fast == NULL)
		return slow;
	while (fast->next != NULL) {
		fast = fast->next;
	}
	return fast;//노드의 마지막 노드 반환
}


void partition(Node ** Front, Node ** Last, Node * node) {
	Node * fast, *slow;
	
	if (node == NULL || node->next == NULL) {
		*Front = node;
		*Last = NULL;
		printf("if문안에 들어옴\n");
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
		printf("else문안에 들어옴\n");
	}
	
}*/

void partition(Node ** Front, Node ** Last, Node * node) {
	Node * fast;
	Node * slow;
	if (node == NULL || node->next == NULL) {
		*Front = node;
		*Last = NULL;
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


Node * merge(Node * a, Node * b) {
	Node * p;
	Node * result = NULL;

	if (a == NULL)
		return b;
	else if (b == NULL)
		return a;
	
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

	if (a == NULL)
		p->next = b;
	else
		p->next = a;

	return result;
}

void mergeSort(Node ** HEAD) {
	Node * head = *HEAD;
	Node *a,*b;
	if ((head == NULL) || (head->next == NULL))
		return;

	partition(&a,&b,head);

	mergeSort(&a);
	mergeSort(&b);

	*HEAD = merge(a,b);
}

void push_Node(Node ** head, int data) {
	Node * p = (Node *)malloc(sizeof(Node));
	p->data = data;
	p->next = (*head);
	(*head) = p;
}

void printList(Node * node) {
	while (node != NULL) {
		printf(" %d", node->data);
		node = node->next;
	}
}

int main() {
	int n, i, data;
	Node * head=NULL;


	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &data);
		push_Node(&head, data);
	}
	mergeSort(&head);

	printList(head);
}