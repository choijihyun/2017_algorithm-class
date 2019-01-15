#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define N 6
typedef struct Edge {
	int w;
	int s_vertices, e_vertices;
}Edge;

typedef struct Vertices {
	int identifier;			//처음노드는 정점이름, 다음부터는 간점인덱스
	struct Vertices *next;
}Vertices;

int arr[N][N];
Vertices vertices[6];
Edge edge[21];
int M = 8;

void init_edge() {
	edge->s_vertices = 1;
	edge->e_vertices = 2;
	edge->w = 1;

	(edge + 1)->s_vertices = 1;
	(edge + 1)->e_vertices = 3;
	(edge + 1)->w = 1;

	(edge + 2)->s_vertices = 1;
	(edge + 2)->e_vertices = 4;
	(edge + 2)->w = 1;

	(edge + 3)->s_vertices = 1;
	(edge + 3)->e_vertices = 6;
	(edge + 3)->w = 2;

	(edge + 4)->s_vertices = 2;
	(edge + 4)->e_vertices = 3;
	(edge + 4)->w = 1;

	(edge + 5)->s_vertices = 3;
	(edge + 5)->e_vertices = 5;
	(edge + 5)->w = 4;

	(edge + 6)->s_vertices = 5;
	(edge + 6)->e_vertices = 5;
	(edge + 6)->w = 4;

	(edge + 7)->s_vertices = 5;
	(edge + 7)->e_vertices = 6;
	(edge + 7)->w = 3;
}

void add_edge(int s, int e, int w) {
	(edge + M)->s_vertices = s;
	(edge + M)->e_vertices = e;
	(edge + M)->w = w;
	M++;
}

int is_EExist(int s,int e) {
	int i;
	for (i = 0; i < M; i++) {
		if (((edge + i)->s_vertices == s && (edge + i)->e_vertices == e) || ((edge + i)->s_vertices == e && (edge + i)->e_vertices == s))
			return 1;
	}
	return 0;
}

int Edge_loc(int s, int e) {
	int i;
	for (i = 0; i < M; i++) {
		if (((edge + i)->s_vertices == s && (edge + i)->e_vertices == e) || ((edge + i)->s_vertices == e && (edge + i)->e_vertices == s))
			return i;
	}
}

void insertgraph(int s, int e, int w) {
	arr[s - 1][e - 1] = w;
	arr[e - 1][s - 1] = w;
}

void init_graph() {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			arr[i][j] = -1;
		}
	}
	init_edge();
	insertgraph(1, 2, 0);
	insertgraph(1, 3, 1);
	insertgraph(1, 4, 2);
	insertgraph(1, 6, 3);
	insertgraph(2, 3, 4);
	insertgraph(3, 5, 5);
	insertgraph(5, 5, 6);
	insertgraph(5, 6, 7);
}

int vertices_num(int num,int vertice) {
	int s, e;
	s = (edge + num)->s_vertices;
	e = (edge + num)->e_vertices;
	if (s == vertice) 
		return e;
	else if (e == vertice) 
		return s;
}

void func_a(int num) {
	int i,flag=0,vertice,pass_num;
	if(num>N){
		printf("-1\n");
		return;
	}
	for (i = 0; i < N; i++) {
		if (arr[num - 1][i] != -1) {
			pass_num = arr[num - 1][i];
			vertice = vertices_num(pass_num,num);
			printf(" %d %d",vertice,(edge+ arr[num - 1][i])->w);
			flag = 1;
		}
	}
	if (!flag) {
		printf("-1\n");
		return;
	}
	printf("\n");
}

void RNode(int s, int e, int w) {
	int num;
	if (s > N || e > N) {
		printf("-1\n");
		return;
	}

	if (w == 0) {//노드 삭제
		arr[s - 1][e - 1] = -1;
		arr[e - 1][s - 1] = -1;
	}
	else { //새롭게 간선 추가 또는 간선 수정 
		if (is_EExist(s, e)) { //간선 존재 -> 간선 찾아서 값만 바꿔주기
			num = Edge_loc(s, e);
			(edge + num)->w = w;
			insertgraph(s, e, num);
		}
		else { //간선 존재 하지 않음 -> 간선 추가해주고 이차원배열에 넣어주기
			add_edge(s, e, w);
			insertgraph(s, e, M-1);
		}
	}
}

int main() {
	char ch;
	int num,s,e,w;
	init_graph();

	while (1) {
		scanf("%c", &ch);
		if (ch == 'a') {
			scanf("%d", &num);
			getchar();
			func_a(num);
		}
		else if (ch == 'm') {
			scanf("%d %d %d", &s, &e, &w);
			getchar();
			RNode(s, e, w);
		}
		else if (ch == 'q')
			return 0;
	}
}