#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)
#define N 6

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

void insert(Vertices * node, int n, int index) {//오름차순 정렬해야됌
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

void printall(){
	int i, num;
	Vertices * p;

	printf("M = %d\n", M);
	for (i = 0; i < N; i++) {
		printf("=========%d===========\n", i);
		p = (vertices + i);
		while (p->next != NULL){
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


void removeEdge(int s, int e, int i) {
	int fnum, flag = 0;
	Edge * p;
	Vertices * vp, *bvp;
	Vertices * vp1, *bvp1;

	vp = vertices + s - 1;
	bvp = vertices + s - 1;
	while (vp->next != NULL) {
		bvp = vp;
		vp = vp->next;
		fnum = vp->identifier;
		//printf("S : fnum = %d\n", fnum);
		if (fnum==i) {
			bvp->next = vp->next;
			flag = 1;
			break;
		}
	}

	if (s == e) {
		return;
	}

	vp1 = vertices + e - 1;
	bvp1 = vertices + e - 1;
	while (vp1->next != NULL) {
		bvp1 = vp1;
		vp1 = vp1->next;
		fnum = vp1->identifier;
		//printf("E : fnum = %d\n", fnum);
		if (fnum==i) {
			bvp1->next = vp1->next;
			flag = 1;
			break;
		}
	}
	if (!flag)
		printf("-1\n");


}

void RNode(int s, int e, int w) {
	int i, j;
	Vertices *p;
	if (w == 0) {//삭제
		for (i = 0; i < M; i++) {
			if (((edge + i)->s_vertices == s && (edge + i)->e_vertices == e) || ((edge + i)->s_vertices == e && (edge + i)->e_vertices == s)) {
				//printf("i = %d\n", i);
				removeEdge(s, e, i);
				return;
			}
		}
		printf("-1\n");
	}
	else {	// 간선삽입
		if (!graph(s) || !graph(e)) {
			printf("-1\n");
			return;
		}

		for (i = 0; i < M; i++) {
			if (((edge + i)->s_vertices == s && (edge + i)->e_vertices == e) || ((edge + i)->s_vertices == e && (edge + i)->e_vertices == s)) {
				//printf("전에 존재했던 간선이 또 들어옴\nedge index = %d\n",i);
				if ((edge + i)->w != w)
					(edge + i)->w = w;



				if (s == e) {
					//printf("s = %d  e = %d\n", s, e);
					insert(vertices + s - 1, i, s - 1);
					printf("같은ㅁ\n");
				}
				else {
					insert(vertices + s - 1, i, s - 1);
					insert(vertices + e - 1, i, e - 1);
				}
				printf("?\n");
				return;
			}
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
