#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct Node {
	int key;
	struct Node * next;
}Node;

void delete_m(Node * A, int num,int m) {
	int n, cnt = 0,flag=0;
	Node * tmp,*tmp2;
	n = num % m;
	tmp = (A + n)->next;
	tmp2 = (A + n);
	while (tmp != NULL) {
		cnt++;
		if(tmp->key==num){
			printf("%d\n", cnt);
			flag = 1;
			break;
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
	if (!flag)
		printf("0\n");
	if(tmp!=NULL)
		tmp2->next = tmp->next;
}

void print(Node *A, int m) {
	Node * tmp;
	int i;
	for (i = 0; i < m; i++) {
		tmp = (A + i)->next;
		while (tmp != NULL) {
			printf(" %d", tmp->key);
			tmp = tmp->next;
		}
	}
	printf("\n");
}

void init_Node(Node * A,int m) {
	int i;
	for (i = 0; i < m; i++) {
		(A + i)->key = i;
		(A + i)->next = NULL;
	}
}

void insert(Node * A,int num,int m) {
	int n;
	Node * N,*tmp;
	N = (Node *)malloc(sizeof(Node));
	tmp = (Node *)malloc(sizeof(Node));
	n = num%m;
	N->key = num;
	tmp = (A + n)->next;
	(A+n)->next = N;
	N->next = tmp;
}

void search(Node * A,int key,int m) {
	int n, cnt = 0;
	Node * tmp;
	n = key % m;
	tmp = (A + n)->next;

	while (tmp != NULL) {
		cnt++;
		if (tmp->key == key) {
			printf("%d\n", cnt);
			return;
		}
		tmp = tmp->next;
	}
	printf("0\n");
}

int main() {
	int m,num;
	char ch;
	Node * A;
	scanf("%d", &m);
	A = (Node *)malloc(sizeof(Node)*m);
	init_Node(A, m);

	//printf("init success\n");
	//for (i = 0; i < m; i++) {
	//	printf(" %d", (A + i)->key);
	//}
	//printf("\n");

	while (1) {
		scanf("%c", &ch);
		if (ch == 'i') {
			scanf("%d", &num);
			getchar();
			insert(A, num,m);
		}
		else if (ch == 's') {
			scanf("%d", &num);
			getchar();
			search(A, num, m);
		}
		else if (ch == 'd') {
			scanf("%d", &num);
			getchar();
			delete_m(A, num, m);
		}
		else if (ch == 'p') {
			print(A,m);
		}
		else if (ch == 'e') {
			return 0;
		}
	}
}
