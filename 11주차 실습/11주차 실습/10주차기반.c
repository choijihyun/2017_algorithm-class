#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)
#define FRESH 0
#define VISITED 1
#define BACK -1
#define TREE -1
typedef struct Edge {
	int s_vertices, e_vertices;
	int elabel;
}Edge;

typedef struct Vertices {
	int identifier;			//처음노드는 정점이름, 다음부터는 간점인덱스
	struct Vertices *next;
	int vlabel;
}Vertices;

Vertices *vertice;
Edge edge[1000];
int M = 0;
int N;

void insert_edge(int s, int e) {
	(edge + M)->s_vertices = s;
	(edge + M)->e_vertices = e;
	(edge + M)->elabel = FRESH;//fresh
	M++;
}


Vertices * findNode(Vertices * node, int n, int index) {
	Vertices * p;		//n = edge index, index = vertices index
	int s, e, pivot, next_Snum, next_Enum, next_num;
	pivot = index + 1;
	p = node;
	while (p->next != NULL) {
		next_Snum = (edge + (p->next->identifier))->s_vertices;
		next_Enum = (edge + (p->next->identifier))->e_vertices;

		if (pivot == next_Snum)	//다음에 오는 숫자
			next_num = next_Enum;
		else
			next_num = next_Snum;

		//새로 넣을 edge
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

void init_graph(int n) {
	Vertices *p;
	int i, j;

	for (i = 0; i < n; i++) {
		(vertice + i)->identifier = i + 1;
		(vertice + i)->next = NULL;
	}
}


void insert(Vertices * node, int n, int index) {//오름차순 정렬해야됌
	Vertices * p, *tmp;			//n = edge index, index = vertices index

	tmp = findNode(node, n, index);
	p = (Vertices *)malloc(sizeof(Vertices));
	p->identifier = n;
	p->vlabel = FRESH;//fresh
	p->next = tmp->next;
	tmp->next = p;
}

Vertices * opposite(Vertices * p, int n) {
	int num, opp_num;
	num = p->identifier;
	opp_num = (edge + num)->e_vertices;
	if ((edge + num)->s_vertices != n) {
		opp_num = (edge + num)->s_vertices;
	}
	//printf("opp_label = %d\n", (vertice + opp_num - 1)->vlabel);
	return vertice + opp_num - 1;
}

int vert_num(Vertices * p, int n) {
	int num, opp_num;
	num = p->identifier;
	opp_num = (edge + num)->e_vertices;
	if ((edge + num)->s_vertices != n) {
		opp_num = (edge + num)->s_vertices;
	}
	return opp_num;
}


/**/
void check_label() {
	int i;
	for (i = 0; i < N; i++) {
		printf("%d label = %d\n", i, (vertice + i)->vlabel);
	}
	printf("\n");
}

void printEdge() {
	int i;
	printf("================================\n");
	for (i = 0; i < M; i++) {
		printf("index = %d  s = %d  e = %d label = %d\n", i, (edge + i)->s_vertices, (edge + i)->e_vertices, (edge + i)->elabel);
	}
	printf("================================\n");
}

void printall(int N) {
	int i, num;
	Vertices * p;

	printf("M = %d\n", M);
	for (i = 0; i < N; i++) {
		printf("=========%d===========\n", i);
		p = (vertice + i);
		while (p->next != NULL) {
			p = p->next;
			printf("identi = %d verticelabel = %d ", p->identifier, p->vlabel);
			num = p->identifier;
			printf("start = %d  end = %d edgelabel = %d\n", (edge + num)->s_vertices, (edge + num)->e_vertices, (edge + num)->elabel);
		}
		printf("\n");
	}
}

/**/


void rDFS(Vertices * node, int n) {
	int i, num, num2;
	Vertices * p = node;
	Vertices * w;
	//printf("============================\n");
	//check_label();
	//printf("============================\n");
	printf("%d\n", n);
	p->vlabel = VISITED; //visited

	//printf("============================\n");
	//check_label();
	//printf("============================\n");

	while (p->next != NULL) {
		p = p->next;
		num = p->identifier; //num에 간선의 인덱스를 저장한다.
		//printf("p->idntfi= %d\n", p->identifier);
		//printf("(edge + num)->label = %d\n", (edge + num)->elabel);
		if ((edge + num)->elabel == FRESH) { //그 간선이 fresh인지 확인
			//p의 오포짓찾음

			w = opposite(p, n);
			num2 = vert_num(p, n);
			//printEdge();
			//printf("n = %d veritece = %d\n",n, num2);
			//printf("w->label = %d\n", w->vlabel);

			if (w->vlabel == FRESH) {
				//printf("드디어\n");
				(edge + num)->elabel = TREE;//tree
				num2 = vert_num(p, n);
				//printf("vert_num = %d\n", num2);
				//printf("%d\n", num2);
				rDFS(w, vert_num(p, n));
			}
			else {
				(edge + num)->elabel = BACK;//back
			}
		}
	}
}

void DFS(int s) {
	//fresh = 0, visited = 1, back = -1
	rDFS(vertice + s-1, s);
}
int main() {
	int n, m, s;
	int i;
	int s_vertice, e_vertice;

	scanf("%d %d %d", &n, &m, &s);
	N = n;
	vertice = (Vertices *)malloc(sizeof(Vertices)*n);
	init_graph(n);

	for (i = 0; i < N; i++) {
		(vertice + i)->vlabel = FRESH;
	}
	//check_label();

	for (i = 0; i < m; i++) {

		scanf("%d %d", &s_vertice, &e_vertice);

		//M = edge index, index = vertices index
		insert_edge(s_vertice, e_vertice);
		insert(vertice + s_vertice - 1, M - 1, s_vertice - 1);
		insert(vertice + e_vertice - 1, M - 1, e_vertice - 1);

	}
	//printall(n);
	//printf("%d\n", s);
	//printall(N);
	DFS(s);

}