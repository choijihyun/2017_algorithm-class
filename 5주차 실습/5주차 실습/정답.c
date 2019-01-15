#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>

typedef struct _node *pnode;
typedef struct _node {
	int data;
	pnode next;
} node;

pnode SortedMerge(pnode a, pnode b);
//void FrontBackSplit(pnode source, pnode *frontRef, pnode *backRef);

void MergeSort(pnode *headRef) {
	pnode head = *headRef;
	pnode a;
	pnode b;

	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	FrontBackSplit(head, &a, &b);

	MergeSort(&a);
	MergeSort(&b);

	*headRef = SortedMerge(a, b);
}

pnode SortedMerge(pnode  a, pnode b) {
	pnode result = NULL;
	pnode p;

	if (a == NULL) {
		return(b);
	}
	else if (b == NULL) {
		return(a);
	}

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

	return(result);
}

void FrontBackSplit(pnode source, pnode *frontRef, pnode *backRef) {//맨앞과 맨뒤 노드 반환
	pnode fast;
	pnode slow;
	if (source == NULL || source->next == NULL) {//노드가 없을때
		*frontRef = source;
		*backRef = NULL;
	}
	else {
		slow = source;//노드
		fast = source->next;//그뒤의노드

		while (fast != NULL) {
			fast = fast->next;
			if (fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}

		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}

void printList(pnode node) {
	while (node != NULL) {
		printf("%d ", node->data);
		node = node->next;
	}
}

void push(pnode *head_ref, int new_data) {

	pnode new_node = (pnode)malloc(sizeof(node));
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

int main() {
	pnode res = NULL;
	pnode a = NULL;
	int i, n, x, y, z;

	scanf("%d", &n);
	for (i = 0; i<n; i += 1) {
		scanf("%d", &z);
		push(&a, z);
	}

	MergeSort(&a);
	printList(a);

	return 0;
}