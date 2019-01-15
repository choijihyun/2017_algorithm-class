//리스트로 하세요
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define INIF 999999

typedef struct Graph {
	struct Vertices * vertice;
	struct Edges * edge;
}Graph;

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
int * Q; // 큐 생성 -> 연결리스트
int	Qcnt = 0;


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
			printf("\n");
		}
	}
}

void checkQ() {
	int i;
	printf("\n=============================\n");
	for (i = 0; i < Qcnt; i++)
		printf(" %d", Q[i]);
	printf("\n=============================\n");
}
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

void init_G() { // 그래프 연결 및 초기화
	int i;
	G.edge = edges;
	G.vertice = vertices;
	for (i = 0; i < n; i++) {
		G.vertice[i].index = i + 1;
		G.vertice[i].head = (Head *)malloc(sizeof(Head));
		G.vertice[i].head->head = NULL;
	}
	Q = (int *)malloc(sizeof(int)* n);
	Qcnt = n;
	for (i = 0; i < n; i++) {
		Q[i] = i + 1; // 정점 이름을 넣는다.
	}
}

void replaceKey() { 

}

void initEdge(int i, int s, int e, int w) { // 간선 설정
	edges[i].vert_s = s;
	edges[i].vert_e = e;
	edges[i].weight = w;
}

int opposite(int u, Node * e) {
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

int element(int z) {
	int i;
	for (i = 0; i < Qcnt; i++) {
		if (Q[i] == z)
			return 1;
	}
	return 0;
}

int removeMin() {
	int num;
	num = Q[0];
	Q[0] = Q[Qcnt - 1];
	Qcnt--;
	replaceKey();
	return num;
}

void DijkstraShortestpath(int s) {
	int i, u, z;
	Node * UV;
	for (i = 0; i < n; i++)
		(vertices + i)->distance = INT_MAX;
	(vertices + s - 1)->distance = 0;

	while (Qcnt != 0) {
		u = removeMin();
		UV = (vertices + u - 1)->head->head;
		while (UV != NULL) { // 부착된 간선들 다 본다
			z = opposite(u, UV); // 반대편 정점 이름
			if (element(z)) {
				if ((vertices + u - 1)->distance + Weight(u, z) < (vertices + z - 1)->distance);
				(vertices + z - 1)->distance = (vertices + u - 1)->distance + Weight(u, z);
				checkQ();
				//여기부터 다시!!!
				replaceKey();

			}
		}
		UV = UV->link;
	}
}

int main() {
	int i;
	int vert_s, vert_e, weight;
	scanf("%d %d %d", &n, &m, &s);
	init_G();
	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &vert_s, &vert_e, &weight);
		initEdge(i, vert_s, vert_e, weight); // 간선만들어주기
		insert_Node(G, vert_s, i);
		insert_Node(G, vert_e, i);
	}

	//showGraph();
	DijkstraShortestpath(s);
	for (i = 0; i < n; i++) {
		if (i + 1 != s) {
			printf("%d %d\n", i + 1, vertices[i].distance);
		}
	}

}