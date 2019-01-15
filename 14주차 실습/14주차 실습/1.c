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

void init_G() { // 정점 생성과 지정 및 간선 생성
	int i;
	vertices = (Vertices *)malloc(sizeof(Vertices)*n); // 정점 n개 생성
	edges = (Edges *)malloc(sizeof(Edges)*m);  // 간선 m개 생성

	for (i = 0; i < n; i++) {
		(vertices + i)->head = (HEAD *)malloc(sizeof(HEAD));
		(vertices + i)->head->head = NULL; // 이어진 간선 없는 상태로 초기화
		(vertices + i)->index = i + 1; // 정점 이름 초기화
		(vertices + i)->distance = INT_MAX; // 무한대로 초기화
	}
	G.vertices = vertices;
	G.edges = edges;
}

void init_Edges(int i,int s, int e, int w) { // 간선 지정
	edges[i].start_v = s;
	edges[i].end_v = e;
	edges[i].weight = w;
}

int findEdge(int s, int e){ // 두 정점을 연결하는 간선의 인덱스를 반환함
	int i;
	for (i = 0; i < m; i++) {
		if ((edges->start_v == s && edges->end_v == e) || (edges->start_v == e && edges->end_v == s))
			return i;
	}
	return -1;
}

Node * getNode(int index) { // 간선의 인덱스를 가진 변수 index를 노드로 생성
	Node * node;
	node = (Node *)malloc(sizeof(Node));
	node->e_index = index;
	node->next = NULL;
	return node;
}

void insertNode(int i,int s) { // 정점에 간선 삽입
	Node * tmp;
	Node * node;
	int index;

	index = i; // 간선 인댁스 찾아서
	node = getNode(index); // 노드 생성
	
	tmp = (vertices + s - 1)->head->head;
	node->next = tmp;
	tmp = node;
		
}

void init_H() {
	int i;

	H = (HEAP *)malloc(sizeof(HEAP)*(n+1)); //정점들을 담을 우선순위 큐니까 정점+1만큼 생성
	for (i = 1; i <= n; i++) {
		H->index = i - 1; // 힙의 각자리에 정점들 인덱스를 넣는다
		//H->key = INT_MAX; // 키값을 무한대로 초기화 -> 힙에서는 키 필요 없을듯
	}
}

void showGraph() { // 간섬과 정점 잘 들어갔나 보는 함수
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