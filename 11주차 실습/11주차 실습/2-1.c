#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define FRESH 0
#define VISITED 1
#define CROSS -1
#define TREE -1

typedef struct Edge {
	int s_vertices, e_vertices;
	int elabel;
}Edge;

typedef struct Vertices {
	int vlabel;
}Vertices;

int M = 0;
int N = 0;

int arr[100][100];
Vertices vertices[100];
Edge edge[1000];

void add_edge(int s, int e) {
	(edge + M)->s_vertices = s;
	(edge + M)->e_vertices = e;
	(edge + M)->elabel = FRESH;
	M++;
}

void insertgraph(int s, int e, int w) {
	arr[s - 1][e - 1] = w;
	arr[e - 1][s - 1] = w;
}

void init_graph() {
	int i, j;
	for (i = 0; i < N; i++) {
		vertices[i].vlabel = FRESH;
		for (j = 0; j < N; j++) {
			arr[i][j] = -1;
		}
	}
}

int vertices_num(int num, int vertice) {
	int s, e;
	s = (edge + num)->s_vertices;
	e = (edge + num)->e_vertices;
	if (s == vertice)
		return e;
	else if (e == vertice)
		return s;
}

void RNode(int s, int e, int w) {
	int num;
	add_edge(s, e, w);
	insertgraph(s, e, M - 1);
}

int vert_num(int s, int j) {
	int num;
	num = arr[s - 1][j];
	if (edge[num].e_vertices == s)
		return edge[num].s_vertices;
	else
		return edge[num].e_vertices;
}



int main() {
	int n, m, s;
	int i, j;
	int s_vertice, e_vertice;

	scanf("%d %d %d", &n, &m, &s);
	N = n;

	init_graph(n);

	for (i = 0; i < m; i++) {
		scanf("%d %d", &s_vertice, &e_vertice);
		RNode(s_vertice, e_vertice, M);
	}

	BFS(s);

}