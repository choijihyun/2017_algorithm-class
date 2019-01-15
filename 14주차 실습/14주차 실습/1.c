#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#pragma warning(disable: 4996)

typedef struct Graph{
	struct Vertices * vertices;
	struct Edges * edges;
}Graph;

typedef struct Heap {
	int index;
	//int key;
}HEAP;

typedef struct Vertices{
	struct Head * head;
	int index;
	int distance;
}Vertices;

typedef struct Edges {
	int start_v;
	int end_v;
	int weight;
}Edges;

typedef struct Head {
	struct Node * head;
}HEAD;

typedef struct Node {
	int e_index;
	struct Node * next;
}Node;

//==================================

Vertices * vertices;
Edges * edges;
Graph G;
HEAP * H;
int n, m, s;

//====================================

void init_G() { // ���� ������ ���� �� ���� ����
	int i;
	vertices = (Vertices *)malloc(sizeof(Vertices)*n); // ���� n�� ����
	edges = (Edges *)malloc(sizeof(Edges)*m);  // ���� m�� ����

	for (i = 0; i < n; i++) {
		(vertices + i)->head = (HEAD *)malloc(sizeof(HEAD));
		(vertices + i)->head->head = NULL; // �̾��� ���� ���� ���·� �ʱ�ȭ
		(vertices + i)->index = i + 1; // ���� �̸� �ʱ�ȭ
		(vertices + i)->distance = INT_MAX; // ���Ѵ�� �ʱ�ȭ
	}
	G.vertices = vertices;
	G.edges = edges;
}

void init_Edges(int i,int s, int e, int w) { // ���� ����
	edges[i].start_v = s;
	edges[i].end_v = e;
	edges[i].weight = w;
}

int findEdge(int s, int e){ // �� ������ �����ϴ� ������ �ε����� ��ȯ��
	int i;
	for (i = 0; i < m; i++) {
		if ((edges->start_v == s && edges->end_v == e) || (edges->start_v == e && edges->end_v == s))
			return i;
	}
	return -1;
}

Node * getNode(int index) { // ������ �ε����� ���� ���� index�� ���� ����
	Node * node;
	node = (Node *)malloc(sizeof(Node));
	node->e_index = index;
	node->next = NULL;
	return node;
}

void insertNode(int i,int s) { // ������ ���� ����
	Node * tmp;
	Node * node;
	int index;

	index = i; // ���� �δ콺 ã�Ƽ�
	node = getNode(index); // ��� ����
	
	tmp = (vertices + s - 1)->head->head;
	node->next = tmp;
	tmp = node;
		
}

void init_H() {
	int i;

	H = (HEAP *)malloc(sizeof(HEAP)*(n+1)); //�������� ���� �켱���� ť�ϱ� ����+1��ŭ ����
	for (i = 1; i <= n; i++) {
		H->index = i - 1; // ���� ���ڸ��� ������ �ε����� �ִ´�
		//H->key = INT_MAX; // Ű���� ���Ѵ�� �ʱ�ȭ -> �������� Ű �ʿ� ������
	}
}

void showGraph() { // ������ ���� �� ���� ���� �Լ�
	int i, num;
	Node * tmp;

	printf("\n=========showGraph============\n");
	for (i = 0; i < n; i++) {
		printf("vertices[%d] : ", i + 1);
		tmp = vertices[i].head->head;
		while (tmp != NULL) {
			num = tmp->e_index;
			printf(" %d", num);
			tmp = tmp->next;
		}
		printf("\n");
	}
}

int main() {
	int i;
	int s, e, w;
	scanf("%d %d %d", &n, &m, &s);
	init_G();
	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &s, &e, &w);
		init_Edges(i, s, e, w);
		insertNode(i, s);
		insertNode(i, e);
	}
	showGraph();
}