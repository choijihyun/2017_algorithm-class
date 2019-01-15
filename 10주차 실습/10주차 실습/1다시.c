// m 1 2 0후에 m 2 1 0문제

#include <stdio.h>
#include <stdlib.h>
#define N 6
#pragma warning(disable: 4996)

typedef struct Edge {
	int w;
	int s_vertices, e_vertices;
}Edge;

typedef struct Vertices {
	int identifier;			//처음노드는 정점이름, 다음부터는 간점인덱스
	struct Vertices *next;
}Vertices;


Vertices vertices[6];
Edge edge[21];
int M = 8;


Vertices * findNode(Vertices * node, int n, int index) {
	Vertices * p;
	int s, e, pivot, next_Snum, next_Enum, next_num;
	pivot = index + 1;
	p = node;
	while (p->next != NULL) {
		next_Snum = (edge + (p->next->identifier))->s_vertices;
		next_Enum = (edge + (p->next->identifier))->e_vertices;

		if (pivot == next_Snum)	//다음 에 오는 숫자
			next_num = next_Enum;
		else
			next_num = next_Snum;


		s = (edge + n)->s_vertices;
		e = (edge + n)->e_vertices;
		if (s == pivot) {
			if (e < next_num)
				return p;
		}
		else {
			if (s < next_num)
				return p;
		}
		p = p->next;
	}
	return p;
}

void insert(Vertices * node, int n, int index) {//오름차순 정렬해야됨
	Vertices * p, *tmp;			//n = edge index, index = vertices index
	Vertices * graph;
	int cnt = 0;
	tmp = findNode(node, n, index);
	p = (Vertices *)malloc(sizeof(Vertices));
	p->identifier = n;
	p->next = tmp->next;
	tmp->next = p;
}

void init_graph() {
	Vertices *p;
	int i, j;

	for (i = 0; i < N; i++) {
		(vertices + i)->identifier = i + 1;
		(vertices + i)->next = NULL;
	}

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

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			if ((vertices + i)->identifier == (edge + j)->e_vertices || (vertices + i)->identifier == (edge + j)->s_vertices) {
				insert(vertices + i, j, i);
			}
		}
	}
}

void printEdge() {
	int i;
	printf("================================\n");
	for (i = 0; i < M; i++) {
		printf("index = %d  s = %d  e = %d  w = %d\n", i, (edge + i)->s_vertices, (edge + i)->e_vertices, (edge + i)->w);
	}
	printf("================================\n");
}

void printall() {
	int i, num;
	Vertices * p;

	printf("M = %d\n", M);
	for (i = 0; i < N; i++) {
		printf("=========%d===========\n", i);
		p = (vertices + i);
		while (p->next != NULL) {
			p = p->next;
			printf("identi = %d ", p->identifier);
			num = p->identifier;
			printf("start = %d  end = %d  w = %d\n", (edge + num)->s_vertices, (edge + num)->e_vertices, (edge + num)->w);
		}
		printf("\n");
	}
}

int graph(int num) {
	int i;
	for (i = 0; i < N; i++) {
		if (i + 1 == num)
			return 1;
	}
	return 0;
}

Vertices * findElement(int node_num) {
	Vertices * p;

	if (!graph(node_num)) {
		return NULL;
	}

	return vertices + node_num - 1;
}

void func_a(int num) {
	int fnum;
	Vertices * p;

	p = findElement(num);

	if (p == NULL) {	//아예 없는 정점 호출
		printf("-1\n");
		return;
	}

	if (p->next == NULL) {
		printf("-1\n");
		return;
	}
	//printf("index = %d\n", p->identifier);

	p = p->next;
	//printf("p = %d\n", p->identifier);
	while (p != NULL) {
		fnum = p->identifier;
		if ((edge + fnum)->s_vertices == num)
			printf(" %d %d", (edge + fnum)->e_vertices, (edge + fnum)->w);
		else if ((edge + fnum)->e_vertices == num)
			printf(" %d %d", (edge + fnum)->s_vertices, (edge + fnum)->w);
		p = p->next;
	}
	printf("\n");
}

int isEdgeExist(int s, int e) {
	int i;
	for (i = 0; i < M; i++) {
		if (((edge + i)->s_vertices == s && (edge + i)->e_vertices == e) || ((edge + i)->s_vertices == e && (edge + i)->e_vertices == s))
			return 1;
	}
	return 0;
}

int EdgeIndex(int s, int e) {
	int i;
	for (i = 0; i < M; i++) {
		if (((edge + i)->s_vertices == s && (edge + i)->e_vertices == e) || ((edge + i)->s_vertices == e && (edge + i)->e_vertices == s))
			return i;
	}
}

void removeEdge(int s, int e) {
	Vertices *Sp, *Sbp;
	Vertices *Ep, *Ebp;
	int num;

	num = EdgeIndex(s, e);

	Sp = vertices + s - 1;
	Sbp = vertices + s - 1;
	while (Sp->next != NULL) {
		Sbp = Sp;
		Sp = Sp->next;
		if (Sp->identifier == num) {
			Sbp->next = Sp->next;
			break;
		}
	}

	if (s == e)
		return;

	Ep = vertices + e - 1;
	Ebp = vertices + e - 1;
	while (Ep->next != NULL) {
		Ebp = Ep;
		Ep = Ep->next;
		if (Ep->identifier == num) {
			Ebp->next = Ep->next;
			break;
		}
	}
}

int isVerticesExist(int s, int e) {//s와 e를 가진 edge가 vertices의 identifier에 있는지 확인
	Vertices *p;
	int num;
	int index;

	index = EdgeIndex(s, e);

	p = (vertices + s - 1);
	while (p->next != NULL) {
		p = p->next;
		if (p->identifier == index)
			return 1;
	}
	return 0;

}

void RNode(int s, int e, int w) {
	int num;
	if (s > N || e > N) {
		printf("-1\n");
		return;
	}
	if (w == 0) {	//간선이 있을때 삭제, 없으면 -1출력
		if (isEdgeExist(s, e)) {	//삭제 함수 만들기
			if (isVerticesExist(s, e)) {
				if (s != e) {
					removeEdge(s, e);
					removeEdge(e, s);
				}
				else
					removeEdge(s, e);
			}
			//else {
			//	printf("-1\n");
			//}
		}
		//else {
		//	printf("-1\n");
		//}
	}
	else {	// 간선이 없으면 추가 있으면값 바꾸기
		if (isEdgeExist(s, e)) {	//값 바꾸기

			//예전에 삭제한 거 다시 넣을 경우 == 결국 정점에 ㄴㄴ존재하는 간점인지 확인하기
			if (isVerticesExist(s, e)) {//있다면 값만 바꿔주고
				num = EdgeIndex(s, e);
				(edge + num)->w = w;
			}
			else {//없으면 다시 넣어주고
				num = EdgeIndex(s, e); 
				(edge + num)->w = w;
				if(s==e)
					insert(vertices + s - 1, num, s - 1);
				else {
					insert(vertices + s - 1, num, s - 1);
					insert(vertices + e - 1, num, e - 1);
				}
			}
		}
		else {	//간선 추가하기

			if (s > N || e > N) {
				printf("-1\n");
				return;
			}
				
			(edge + M)->s_vertices = s;
			(edge + M)->e_vertices = e;
			(edge + M)->w = w;
			
			if (s == e)
				insert(vertices + s - 1, M, s - 1);
			else {
				insert(vertices + s - 1, M, s - 1);
				insert(vertices + e - 1, M, e - 1);
			}
			M++;
		}
	}
}

int main() {
	int node_num;
	int edge_s, edge_e, w;
	char ch;

	init_graph();

	while (1) {
		scanf("%c", &ch);
		if (ch == 'a') {
			scanf("%d", &node_num);
			getchar();
			func_a(node_num);
		}

		else if (ch == 'm') {
			scanf("%d %d %d", &edge_s, &edge_e, &w);
			getchar();
			RNode(edge_s, edge_e, w);
		}

		else if (ch == 'p')
			printall();
		
		else if (ch == 'e')
			printEdge();

		else if (ch == 'q')
			return 0;
	}
}