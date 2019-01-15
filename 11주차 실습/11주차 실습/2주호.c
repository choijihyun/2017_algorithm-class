#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)
#define FRESH 0
#define VISITED 1
#define TREE 1

typedef struct vertex {
	int name;
	int label;
}vertex;
typedef struct edge {
	int label;
	int s_vertice, e_vertice;
}edge;

vertex *Vertice;
edge *Edge;
int **Graph = NULL;

void BFS1(int n, int m, int s) {
	int i, j, k, h;
	int opp;
	int *L;

	L = (int *)malloc(sizeof(int) * n);

	for (i = 0; i<n; i++)
		L[i] = 0;

	printf("%d\n", s + 1);
	L[0] = s + 1;

	Vertice[s].label = VISITED;

	i = 0;
	h = 0;
	while (L[i] != 0) {
		for (j = 0; j<n; j++) {
			if (Graph[L[i] - 1][j] != 0) {
				opp = j + 1;
				if (Vertice[opp - 1].label == FRESH) {
					for (k = 0; k<m; k++) {
						if ((Edge[k].s_vertice == opp && Edge[k].e_vertice == L[i] && Edge[k].label == FRESH)
							|| (Edge[k].e_vertice == opp && Edge[k].s_vertice == L[i] && Edge[k].label == FRESH)) {
							printf("%d\n", opp);
							L[++h] = opp;
							Vertice[opp - 1].label = VISITED;
							Edge[k].label = TREE;
							break;
						}
					}
				}
			}
		}
		i++;
		if (i>n - 1) break;
	}
}

void BFS(int n, int m, int s) {
	int i, j, a, b;

	for (i = 0; i<n; i++)
		for (j = 0; j<n; j++)
			Graph[i][j] = 0;

	for (i = 0; i<n; i++) {
		Vertice[i].name = i + 1;
		Vertice[i].label = FRESH;
	}

	for (i = 0; i<m; i++) {
		scanf("%d %d", &a, &b);
		Edge[i].s_vertice = a;
		Edge[i].e_vertice = b;
		Edge[i].label = FRESH;
		Graph[a - 1][b - 1] = 1;
		Graph[b - 1][a - 1] = 1;
	}
	
	for (i = s - 1; i<s - 1 + n; i++) {
		if (Vertice[i%n].label == FRESH)
			BFS1(n, m, i%n);
	}
}

int main() {
	int m, n, s, i;

	scanf("%d%d%d", &n, &m, &s);

	Vertice = (vertex *)malloc(sizeof(vertex)*n);
	Edge = (edge *)malloc(sizeof(edge)*m);
	Graph = (int**)malloc(sizeof(int*)*n);

	for (i = 0; i<n; i++)
		*(Graph + i) = (int*)malloc(sizeof(int)*n);

	BFS(n, m, s);
}