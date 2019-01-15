#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define INIF 999999

typedef struct Graph {
	struct Vertices * vertice;
	struct Edges * edge;
}Graph;

typedef struct HEAP { //�켱����ť�� �����ϴ� ��
	int index;	//edges index
	int key; // edges weight
}HEAP;

typedef struct Node { //�켱���� ť ������ ���
	struct Node * link;
	int EdgeNode;
}Node;

typedef struct Head {
	struct Node * head;
}Head;

typedef struct Vertices {
	struct Head * head; // ���� �����ų��
	//�賶�� �̷�� �ֵ� �ʿ��ҵ�
	int index;
	int distance;
}Vertices;

typedef struct Edges {
	int weight;
	int vert_s, vert_e;
}Edges;

//=============���� ������=================

Vertices vertices[100];
Vertices Tvertices[100];
Edges edges[1000];
Graph G;
Graph T; // MST�� ���� �׷���!
int n, m;
HEAP *Heap;
int Hcnt = 1; // Heap�ȿ� �ִ� ������ ����
int Tcnt = 1; // MST T�ȿ� �ִ� ������ ����
int sum = 0;
int * Sack;



//============����� ���� �糪 Ȯ���ϴ� �Լ�====================

void showGraph() { // ������ ���� �� ���� ���� �Լ�
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
		}
		printf("\n");
	}
}

void checkH() { //�� ����� ��������� Ȯ��
	int i;
	for (i = 1; i <= m; i++) {
		printf("====%d====\nkey : %d   index : %d\n=========\n", i, Heap[i].key, Heap[i].index);
	}
}

void checkS() {
	int i;
	printf("\n=================Sack==================\n");
	for (i = 0; i < n; i++) {
		printf(" %d", Sack[i]);
	}
	printf("\n============================================\n\n");
}

//=================================================================
//=================================================================

void arraySwap(int n1, int n2) {
	HEAP temp; // �ӽ÷� ���� ������ ����

	temp = Heap[n1];
	Heap[n1] = Heap[n2];
	Heap[n2] = temp;
	// A[n1]�� ���� A[n2]�� ���� swap�Ѵ�
}

void downHeap(int i)
{
	HEAP tmp;

	if (i * 2 + 1 > Hcnt && Heap[i].key > Heap[2 * i].key) {
		tmp = Heap[i];
		Heap[i] = Heap[2 * i];
		Heap[2 * i] = tmp;
	}
	else {

		while (i * 2 + 1 <= Hcnt) {
			if (Heap[2 * i].key <= Heap[2 * i + 1].key) {
				if (Heap[i].key >= Heap[2 * i].key) {
					tmp = Heap[i];
					Heap[i] = Heap[2 * i];
					Heap[2 * i] = tmp;
				}
				i = i * 2;
			}
			else {
				if (Heap[i].key >= Heap[2 * i + 1].key) {
					tmp = Heap[i];
					Heap[i] = Heap[2 * i + 1];
					Heap[2 * i + 1] = tmp;
				}
				i = i * 2 + 1;
			}

		}
	}
}

void buildHeap() { // ������
	int i;
	Heap = (HEAP*)malloc(sizeof(HEAP)*(m + 1));// ������ ������ŭ �Ҵ��Ų��
	Hcnt = m;
	for (i = 1; i <= m; i++) {
		Heap[i].index = i - 1; // edges�� �ε���
		Heap[i].key = edges[i - 1].weight; // �ش��ε����� ����ġ
	}
	for (i = Hcnt / 2; i >= 1; i--)
		downHeap(i);
}


int removeMin() { // �ش� �ε��� ã�� �����,,,?
	int num;
	num = Heap[1].index;
	downHeap(1);
	return num;
}

void init_G() { // �׷��� ���� �� �ʱ�ȭ
	int i;
	G.edge = edges;
	G.vertice = vertices;
	for (i = 0; i < n; i++) {
		G.vertice[i].index = i + 1;
		G.vertice[i].head = (Head *)malloc(sizeof(Head));
		G.vertice[i].head->head = NULL;
	}
}

void init_T() { // MST T ������ �ʱ�ȭ
	int i;

	Sack = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++) {
		Sack[i] = i + 1; // �̸��� �°� �賶���� ex)�̸��� 1�� ������ Sack[0]=1;�� ����
	}
	T.vertice = Tvertices;
	for (i = 0; i < m; i++) {
		T.vertice[i].index = i + 1;
		T.vertice[i].head = (Head *)malloc(sizeof(Head));
		T.vertice[i].index = i + 1;
		T.vertice[i].head->head = NULL;
	}
}

void setVertices(int s) { // ���� ����
	vertices[s - 1].index = s;
}

void initEdge(int i, int s, int e, int w) { // ���� ����
	edges[i].vert_s = s;
	edges[i].vert_e = e;
	edges[i].weight = w;
}

Node * getNode() { // �������� ����� ���� �̾��ٶ� ��� �����
	Node * node;
	node = (Node *)malloc(sizeof(Node));
	node->link = NULL;
	return node;
}

void insert_Node(Graph Graph, int loc, int i) { //loc�� vertices��ġ i�� edge��ġ
	Node * node;
	Head * tmp;

	node = getNode();
	node->EdgeNode = i;
	tmp = Graph.vertice[loc - 1].head;
	node->link = tmp->head;
	tmp->head = node;
}

int opposite(int u, Node *e) { // �� ������ ����� ���� �ݴ��� ������ ��ȯ�ϴ� �Լ�
	return edges[e->EdgeNode].vert_s + edges[e->EdgeNode].vert_e - u;
}

int is_Exist(int num) { // heap�� num�̶�� ���� �ֳ� ���� �Լ�
	int i;
	for (i = 1; i <= Hcnt; i++) {
		if (Heap[i].index == num) {
			return 1;
		}
	}
	//printf("return 0\n");
	return 0;
}

int Weight(int u, int z) { // �������� �̾��� ������ ����ġ ���ϴ� �Լ�
	int i;
	for (i = 0; i < m; i++) {
		if (edges[i].vert_s == u && edges[i].vert_e == z)
			return edges[i].weight;
		else if (edges[i].vert_s == z && edges[i].vert_e == u)
			return edges[i].weight;
	}
	return -1;
}

int findCnt(int v) { // �� �ش� �賶�ӿ� ����ִ� ������ ������ ����
	int i, cnt = 0;
	for (i = 0; i < n; i++) {
		if (Sack[i] == v) {
			cnt++;
		}
	}
	return cnt;
}

void Union(int u, int v) {
	int uCnt, vCnt;
	int i, num, num2;

	uCnt = findCnt(Sack[u-1]); // ��� �賶�� �̸��� Ȯ���ؼ� ������ ����
	vCnt = findCnt(Sack[v-1]);

	//printf("ucnt = %d vcnt = %d\n", uCnt, vCnt);

	if (uCnt < vCnt) { //u��v�� �ٿű�ž�
		//printf("%d�� ���� %d�� �� �۾Ƽ� %d�� ��������\n",u,uCnt,Sack[v-1]);
		num = Sack[u - 1];
		num2 = Sack[v - 1];
		for (i = 0; i < n; i++) {
			if (Sack[i] == num) { // �ٲ��ߵǴ� �����ֵ��� �� ã��
				Sack[i] = num2;
			}
		}
		//Sack[u - 1] = v; // �̰Թ���?
	}
	else {
		//printf("%d�� ���� %d�� �� �۾Ƽ� %d�� ��������\n", v, vCnt, Sack[u-1]);
		num = Sack[u - 1];
		num2 = Sack[v - 1];
		for (i = 0; i < n; i++) {
			if (Sack[i] == num2) {
				Sack[i] = num;
			}
		}
		//Sack[v - 1] = u;
	}
}

void KruskalMST() {
	int v, u;
	int min, i;
	Vertices * tmp;
	for (i = 0; i < n; i++) {
		v = vertices[i].index;
		//define a Sack(v)
	}
	buildHeap(); // using weight as a key to make heap
	//checkH();
	init_T();
	while (Tcnt < n) { // n-1�� �ݺ�
		min = removeMin(); //�������� �ε����� ��ȯ��
		
		Heap[1] = Heap[Hcnt];
		Hcnt--;
		downHeap(1);

		// ������ ����ġ�� ���� ���� ������ ����� �� ������ �̾Ƴ���
		v = edges[min].vert_s; //�����̸�
		u = edges[min].vert_e; //�����̸�

		if (Sack[v - 1] != Sack[u - 1]) { //�ΰ��� �賶�� ���� ���� ��
			printf(" %d", edges[min].weight);
			sum += edges[min].weight;
			//printf("���⼭ ���� ��ħ�� �Ͼ�� ���� %d�� ����%d\n",v,u);
			// insert_Node()�Ἥ T�� ���� �������ֱ� -> ������ �����ε����� ����� ������ �ε����� �ʿ���
			//removeMin()�� ���� ������ �ε���!!
			insert_Node(T, v, min); //T�� v������ min���� �߰�
			insert_Node(T, u, min);
			Tcnt++;
			//merge Sack(u) and Sack(v)
			Union(u, v);

		}

		//
		//checkH();
		//checkS();
	}
}

int main() {
	int i;
	int vert_s, vert_e, weight;
	scanf("%d %d", &n, &m);
	init_G();
	for (i = 0; i < m; i++) {
		scanf("%d %d %d", &vert_s, &vert_e, &weight);
		setVertices(vert_s); // ��������
		setVertices(vert_e); // ��������
		initEdge(i, vert_s, vert_e, weight); // ����������ֱ�
		insert_Node(G, vert_s, i);
		insert_Node(G, vert_e, i);
	}

	KruskalMST();
	printf("\n%d\n", sum);

}