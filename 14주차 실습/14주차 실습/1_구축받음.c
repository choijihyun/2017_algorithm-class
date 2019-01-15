//리스트로 하세요
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define INIF 999999

typedef struct Graph {
	struct Vertices * vertice;
	struct Edges * edge;
}Graph;

typedef struct HEAP { //우선순위큐를 구성하는 힙
	int index;	//edges index
	int key; // edges weight
}HEAP;

typedef struct Queue {
	struct QNode * head;
}Queue;

typedef struct QNode { //우선순위 큐 만들어내는 노드
	struct QNode * link;
	int V_node;
}QNode;

typedef struct Node { //정점에 간선 이어줌
	struct Node * link;
	int EdgeNode;
}Node;

typedef struct Head {
	struct Node * head;
}Head;

typedef struct Vertices {
	struct Head * head; // 간선 연결시킬거
	int index;
	int distance;
}Vertices;

typedef struct Edges {
	int weight;
	int vert_s, vert_e;
}Edges;

//=============전역 변수들=================

Vertices vertices[100];
Edges edges[1000];
Graph G;
int n, m, s;
Queue Q; // 큐 생성 -> 연결리스트
int sum = 0;


//============제대로 생성 됬나 확인하는 함수====================

void showGraph() { // 간섬과 정점 잘 들어갔나 보는 함수
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
Node * getNode() { // 한정점에 연결된 간선 이어줄때 노드 만들기
	Node * node;
	node = (Node *)malloc(sizeof(Node));
	node->link = NULL;
	return node;
}

void insert_Node(Graph Graph, int loc, int i) { //loc은 vertices위치 i는 edge위치
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

int removeMin() { // 해당 인덱스 찾고 지우기,,,?
	QNode * node;
	QNode * tmp;
	int num;
	node = Q.head->link;
	num = node->V_node;
	Q.head->link = Q.head->link->link;
	return num;
}

void init_G() { // 그래프 연결 및 초기화
	int i;
	G.edge = edges;
	G.vertice = vertices;
	for (i = 0; i < n; i++) {
		G.vertice[i].index = i + 1;
		G.vertice[i].head = (Head *)malloc(sizeof(Head));
		G.vertice[i].head->head = NULL;
	}
}

QNode * QgetNode() { // 한정점에 연결된 간선 이어줄때 노드 만들기
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

void initEdge(int i, int s, int e, int w) { // 간선 설정
	edges[i].vert_s = s;
	edges[i].vert_e = e;
	edges[i].weight = w;
}

int opposite(int u, Node *e) {
	return edges[e->EdgeNode].vert_s + edges[e->EdgeNode].vert_e - u;
}

int Weight(int u, int z) { // 두정점에 이어진 간선의 가중치 구하는 함수
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
void replaceKey() { // 제일 작은애를 앞으로 보내기-> distance를 키로 해서!
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
		printf("부착된 간선 이름 : %d\n", UV->EdgeNode);
		while (UV != NULL) { // 부착된 간선들 다 본다
			z = opposite(u, UV); // 반대편 정점 이름
			printf("z = %d\n", z);
			if (element(z)) {
				if ((vertices + u - 1)->distance + Weight(u, z) < (vertices + z - 1)->distance) {
					printf("u의 D = %d  u와 z의 가중치 = %d  z의 D = %d\n", (vertices + u - 1)->distance, Weight(u, z), (vertices + z - 1)->distance);
					(vertices + z - 1)->distance = (vertices + u - 1)->distance + Weight(u, z);
					//여기부터 다시!!!
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
		initEdge(i, vert_s, vert_e, weight); // 간선만들어주기
		insert_Node(G, vert_s, i);
		insert_Node(G, vert_e, i);
	}

	//showGraph();
	DijkstraShortestpath(s);

}