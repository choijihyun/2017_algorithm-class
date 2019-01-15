#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct Edge {
	int s_vertices, e_vertices;
	int label;
}Edge;

typedef struct Vertices {
	int identifier;			//처음노드는 정점이름, 다음부터는 간점인덱스
	struct Vertices *next;
	int label;
}Vertices;

Edge edge[1000];
int M = 0;

void insert_edge(int s,int e) {
	(edge + M)->s_vertices = s;
	(edge + M)->e_vertices = e;
	(edge + M)->label = 0;//fresh
	M++;
}

Vertices * findNode(Vertices * node) {
	Vertices *p;
	p = node;
	while (p->next != NULL) {
		p = p->next;
	}
	return p;
}

void insert(Vertices * node, int n) {
	Vertices * p, * tmp;				//n은 edge인덱스!
	tmp = findNode(node);
	p = (Vertices *)malloc(sizeof(Vertices));
	p->label = 0;						//fresh = 0, visited = 1, back = -1
	p->identifier = n;
	p->next = tmp->next;
	tmp->next = p;
}

void rDFS(Vertices * node) {
	int i,num;
	Vertices * p;
	node->label = 1; //visted
	while (node->next != NULL) {
		p = node->next;
		num = p->identifier;
		if ((edge + num)->label == 0) {

		}
	}
}

void DFS(Vertices * vertice,int N) {
	//fresh = 0, visited = 1, back = -1
	
	int i;
	for (i = 0; i < N; i++) {
		if ((vertice + i)->label == 0) { //fresh일 때
			rDFS(vertice + i);
		}
	}
}

int main() {
	int n, m, s;
	int i;
	int s_vertice, e_vertice;
	Vertices * vertice;

	scanf("%d %d %d", &n, &m, &s);

	vertice = (Vertices *)malloc(sizeof(Vertices)*n);

	for (i = 0; i < m; i++) {
		scanf("%d %d", &s_vertice, &e_vertice);

		insert(vertice + s_vertice - 1, M);
		insert(vertice + e_vertice - 1, M);
		insert_edge(s_vertice, e_vertice);
	}


}