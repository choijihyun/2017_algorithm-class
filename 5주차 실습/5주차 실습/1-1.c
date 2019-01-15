#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct Node {//Node 구조체 선언
	int data;
	struct Node * next;
}Node;

void push_Node(Node ** head, int num);
Node * merge(Node *a, Node *b);
void mergeSort(Node ** head);
void partition(Node **Front, Node **Last,Node * node);


void push_Node(Node ** head, int num) {//head가 가르키게 노드 생성
	Node * newnode = (Node *)malloc(sizeof(Node));
	newnode->data = num;
	newnode->next = (*head);
	(*head) = newnode;
}

void mergeSort(Node ** head) {
	Node * Node_Head = *head;//맨앞노드
	Node * a, *b;//그냥 노드

	if ((Node_Head == NULL) || (Node_Head->next == NULL))
		return;//노드가 하나(또는 없으면)면 정렬필요 없기 때문

	partition(&a, &b, Node_Head);

	mergeSort(&a);//이중포인터를 사용한거(노드의 주소를 보냄
	mergeSort(&b);

	*head = merge(a, b);//head에 정렬된 노드의 헤드를 저장함
}

Node * merge(Node * a, Node * b) {
	Node * result = NULL;//정렬된 노드를 여기에 연결할거임
	Node * p;//임시로 저정하려고 만들어놓은 노드

	if (a == NULL)//하나가 비었으면 하나에 다 몰려있는거니까!!
		return b;
	else if (b == NULL)
		return a;

	if (a->data <= b->data) {//정렬하는거니까 크기 비교하기
		result = a;
		a = a->next;
	}
	else {
		result = b;
		b = b->next;
	}
	p = result;//더 작은거 찾아서 p에 시작점으로 잡아버림

	while (a != NULL && b != NULL) {//둘다 안빌때까지
		if (a->data <= b->data) {//더 작은거 찾았으면
			p->next = a;//p에 저장시키고
			a = a->next;//저장된거 하나씩 다넘기고
			p = p->next;
		}
		else {
			p->next = b;
			b = b->next;
			p = p->next;
		}
	}
	if (a == NULL)//다 비었으면 그냥 나머지 이어버리기
		p->next = b;
	else
		p->next = a;


	return result;
}

void partition(Node ** Front, Node ** Last, Node * node) {
	Node * fast;//특정노드
	Node * slow;//특정노드의 뒤의 노드
	if (node == NULL || node->next == NULL) {
		*Front = node;
		*Last = NULL;//노드가 하나밖에 없으니까!
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