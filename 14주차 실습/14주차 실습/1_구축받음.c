//����Ʈ�� �ϼ���
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define INIF 999999

typedef struct Graph {
	struct Vertices * vertice;
	struct Edges * edge;
}Graph;

typedef struct HEAP { //�켱����ť�� �����ϴ� ��
	int index;	//edges index
	int key; // edges weight
}HEAP;

typedef struct Queue {
	struct QNode * head;
}Queue;

typedef struct QNode { //�켱���� ť ������ ���
	struct QNode * link;
	int V_node;
}QNode;

typedef struct Node { //������ ���� �̾���
	struct Node * link;
	int EdgeNode;
}Node;

typedef struct Head {
	struct Node * head;
}Head;

typedef struct Vertices {
	struct Head * head; // ���� �����ų��
	int index;
	int distance;
}Vertices;

typedef struct Edges {
	int weight;
	int vert_s, vert_e;
}Edges;

//=============���� ������=================

Vertices vertices[100];
Edges edges[1000];
Graph G;
int n, m, s;
Queue Q; // ť ���� -> ���Ḯ��Ʈ
int sum = 0;


//============����� ���� �糪 Ȯ���ϴ� �Լ�====================

void showGraph() { // ������ ���� �� ���� ���� �Լ�
	int i, num;
	Node * tmp;

	printf("\n=========showGraph============\n");
	for (i = 0; i < n; i++) {
		printf("vertices[%d] : ", i + 1);
		tmp = vertices[i].head->head;
		while (tmp != NULL) {
			num = tmp->EdgeNode;
			printf(" %d", num);
			tmp = tmp->link;
		}
		printf("\n");
	}
}
//=================================================================
//=================================================================
Node * getNode() { // �������� ����� ���� �̾��ٶ� ��� �����
	Node * node;
	node = (Node *)malloc(sizeof(Node));
	node->link = NULL;
	return node;
}

void insert_Node(Graph Graph, int loc, int i) { //loc�� vertices��ġ i�� edge��ġ
	Node * node;
	Head * tmp;

	node = getNode();
	node->EdgeNode = i;
	tmp = Graph.vertice[loc - 1].head;
	node->link = tmp->head;
	tmp->head = node;
}

int isEmpty() {
	if (Q.head == NULL)
		return 1;
	else
		return 0;
}

int removeMin() { // �ش� �ε��� ã�� �����,,,?
	QNode * node;
	QNode * tmp;
	int num;
	node = Q.head->link;
	num = node->V_node;
	Q.head->link = Q.head->link->link;
	return num;
}

void init_G() { // �׷��� ���� �� �ʱ�ȭ
	int i;
	G.edge = edges;
	G.vertice = vertices;
	for (i = 0; i < n; i++) {
		G.vertice[i].index = i + 1;
		G.vertice[i].head = (Head *)malloc(sizeof(Head));
		G.vertice[i].head->head = NULL;
	}
}

QNode * QgetNode() { // �������� ����� ���� �̾��ٶ� ��� �����
	QNode * node;
	node = (QNode *)malloc(sizeof(QNode));
	node->link = NULL;
	return node;
}

void init_Q() {
	QNode * node;
	QNode * tmp;
	int i;
	Q.head = (QNode *)malloc(sizeof(QNode));
	tmp = Q.head;
	for (i = 0; i < n; i++) {
		node = QgetNode();
		node->V_node = i + 1;
		tmp->link = node;
		tmp = tmp->link;
	}
}

void initEdge(int i, int s, int e, int w) { // ���� ����
	edges[i].vert_s = s;
	edges[i].vert_e = e;
	edges[i].weight = w;
}

int opposite(int u, Node *e) {
	return edges[e->EdgeNode].vert_s + edges[e->EdgeNode].vert_e - u;
}

int Weight(int u, int z) { // �������� �̾��� ������ ����ġ ���ϴ� �Լ�
	int i;
	for (i = 0; i < m; i++) {
		if (edges[i].vert_s == u && edges[i].vert_e == z)
			return edges[i].weight;
		else if (edges[i].vert_s == z && edges[i].vert_e == u)
			return edges[i].weight;
	}
	return -1;
}

int element(int i) {
	QNode * node;
	node = Q.head->link;
	while (node != NULL) {
		printf("%d\n", node->V_node);
		if (node->V_node == i)
			return 1;
		node = node->link;
	}
	return 0;
}

QNode * num(int i) {
	int cnt = 1;
	QNode * node = Q.head->link;
	while (cnt != i) {
		node = node->link;
		cnt++;
	}
	return node;
}
/*
void replaceKey() { // ���� �����ָ� ������ ������-> distance�� Ű�� �ؼ�!
	int pass, min, minLoc, j;
	int num1;
	for (pass = 0; pass < n - 1; pass++) {
		minLoc = pass;
		for (j = pass + 1; j <= n; j++) {
			if (vertices[num(j)->V_node - 1].distance < vertices[num(minLoc)->V_node - 1].distance) {
				minLoc = j;
			}
		}
		num1 = vertices[num(pass)->V_node].distance;
		vertices[num(pass)->V_node-1].distance = vertices[num(minLoc)->V_node - 1].distance;
		vertices[num(minLoc)->V_node - 1].distance = num1;
	}
}
*/



void DijkstraShortestpath(int s) {
	int i, u, z;
	Node * UV;
	QNode * node;
	for (i = 0; i < n; i++)
		(vertices + i)->distance = INT_MAX;
	(vertices + s - 1)->distance = 0;
	init_Q();
	
	node = Q.head->link;
	while (node != NULL) {
		printf("%d ", node->V_node);
		node = node->link;
	}
	printf("\n");
	
	while (!isEmpty()) {
		u = removeMin();
		printf("[%d]removeMin = %d\n",u,vertices[u-1].distance);
		UV = (vertices + u - 1)->head->head;
		printf("������ ���� �̸� : %d\n", UV->EdgeNode);
		while (UV != NULL) { // ������ ������ �� ����
			z = opposite(u, UV); // �ݴ��� ���� �̸�
			printf("z = %d\n", z);
			if (element(z)) {
				if ((vertices + u - 1)->distance + Weight(u, z) < (vertices + z - 1)->distance) {
					printf("u�� D = %d  u�� z�� ����ġ = %d  z�� D = %d\n", (vertices + u - 1)->distance, Weight(u, z), (vertices + z - 1)->distance);
					(vertices + z - 1)->distance = (vertices + u - 1)->distance + Weight(u, z);
					//������� �ٽ�!!!
					//replaceKey();
				}
			}
			UV = UV->link;
		}
	}
}

int main() {
	int i;
	int vert_s, vert_e, weight;
	scanf("%d %d %d", &n, &m ,&s);
	init_G();
	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &vert_s, &vert_e, &weight);
		initEdge(i, vert_s, vert_e, weight); // ����������ֱ�
		insert_Node(G, vert_s, i);
		insert_Node(G, vert_e, i);
	}

	//showGraph();
	DijkstraShortestpath(s);

}