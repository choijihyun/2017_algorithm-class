#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct Graph {
	struct Vertices * vertice;
	struct Edges * edge;
}Graph;

typedef struct Vertices {
	int index;
	struct Head * head;
}Vertices;

typedef struct Head {
	struct Node * link;
}Head;

typedef struct Node {
	struct Node * link;
	int EdgeNode;
}Node;

typedef struct Edges {
	int weight;
	int vert_s, vert_e;
}Edges;

Vertices vertices[100];
Edges edges[1000];
Graph G;
int n, m;
int *Queue;
int *distance;
int *parent;
int Qcnt;

void init_G() {
	int i;
	G.edge = edges;
	G.vertice = vertices;
	for (i = 0; i < n; i++) {
		G.vertice[i].index = i + 1;
		G.vertice[i].head = (Head *)malloc(sizeof(Head));
		G.vertice[i].head->link = NULL;
	}
}

void setVertices(int s) {
	vertices[s - 1].index = s;
}

void initEdge(int i,int s, int e, int w) {
	edges[i].vert_s = s;
	edges[i].vert_e = e;
	edges[i].weight = w;
}

Node * getNode() {
	Node * node;
	node = (Node *)malloc(sizeof(Node));
	node->link = NULL;
	return node;
}

void insert_Node(int loc,int i) { //loc은 vertices위치 i는 edge위치
	Node * node, *tmp;
	
	node = getNode();
	node->EdgeNode = i;
	tmp = vertices[loc - 1].head;
	node->link = tmp->link;
	tmp->link = node;
}

void showGraph() {
	int i, num;
	Node * tmp;
	for (i = 0; i < n; i++) {
		tmp = vertices[i].head;
		while (tmp->link != NULL) {
			tmp = tmp->link;
			num = tmp->EdgeNode;
			printf("  %d :", num);
		}
		printf("\n");
	}
}

void Qinit() {
	Qcnt = 0;
}

int Qinsert(int a) {
	Queue[a] = 0;
	Qcnt++;
}

int removeMin() {
	int i, min = 9999, saveindex = -1;
	for (i = 0; i < n; i++) {
		if (Queue[i] == -1)continue;
		if (distance[i] < min) {
			saveindex = i;
			min = distance[i];
		}
	}
	if (saveindex == -1)return -1;
	Queue[saveindex] = -1;
	Qcnt--;
	return saveindex;
}

void PrimJarnikMST(Graph * G) {
	int i, s;
	distance = (int *)malloc(sizeof(int)*n);
	parent = (int *)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++) {
		distance[i] = -1; //거리를 무한대로
		parent[i] = 0; // 부모 null로 잡음
	}

}

int main() {
	int i;
	int vert_s, vert_e, weight;
	scanf("%d %d", &n, &m);
	init_G();
	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &vert_s, &vert_e, &weight);
		setVertices(vert_s); //정점생성
		setVertices(vert_e); //정점생성
		initEdge(i, vert_s, vert_e, weight); //간선만들어주기
		insert_Node(vert_s, i);
		insert_Node(vert_e, i);
	}
	//showGraph();


}