#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define INIF 999999

typedef struct Graph {
	struct Vertices * vertice;
	struct Edges * edge;
}Graph;

typedef struct HEAP { //우선순위큐를 구성하는 힙
	int index;	//edges index
	int key; // edges weight
}HEAP;

typedef struct Node { //우선순위 큐 만들어내는 노드
	struct Node * link;
	int EdgeNode;
}Node;

typedef struct Head {
	struct Node * head;
}Head;

typedef struct Vertices {
	struct Head * head; // 간선 연결시킬거
	//배낭을 이루는 애도 필요할듯
	int index;
	int distance;
}Vertices;

typedef struct Edges {
	int weight;
	int vert_s, vert_e;
}Edges;

//=============전역 변수들=================

Vertices vertices[100];
Vertices Tvertices[100];
Edges edges[1000];
Graph G;
Graph T; // MST를 만들 그래프!
int n, m;
HEAP *Heap;
int Hcnt = 1; // Heap안에 있는 간선의 갯수
int Tcnt = 1; // MST T안에 있는 간선의 갯수
int sum = 0;
int * Sack;



//============제대로 생성 됬나 확인하는 함수====================

void showGraph() { // 간섬과 정점 잘 들어갔나 보는 함수
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

void checkH() { //힙 제대로 만들어졌나 확인
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
	HEAP temp; // 임시로 값을 저장할 변수

	temp = Heap[n1];
	Heap[n1] = Heap[n2];
	Heap[n2] = temp;
	// A[n1]의 값과 A[n2]의 값을 swap한다
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

void buildHeap() { // 힙생성
	int i;
	Heap = (HEAP*)malloc(sizeof(HEAP)*(m + 1));// 간선의 개수만큼 할당시킨다
	Hcnt = m;
	for (i = 1; i <= m; i++) {
		Heap[i].index = i - 1; // edges의 인덱스
		Heap[i].key = edges[i - 1].weight; // 해당인덱스의 가중치
	}
	for (i = Hcnt / 2; i >= 1; i--)
		downHeap(i);
}


int removeMin() { // 해당 인덱스 찾고 지우기,,,?
	int num;
	num = Heap[1].index;
	downHeap(1);
	return num;
}

void init_G() { // 그래프 연결 및 초기화
	int i;
	G.edge = edges;
	G.vertice = vertices;
	for (i = 0; i < n; i++) {
		G.vertice[i].index = i + 1;
		G.vertice[i].head = (Head *)malloc(sizeof(Head));
		G.vertice[i].head->head = NULL;
	}
}

void init_T() { // MST T 정점만 초기화
	int i;

	Sack = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++) {
		Sack[i] = i + 1; // 이름에 맞게 배낭지정 ex)이름이 1인 정점은 Sack[0]=1;로 저장
	}
	T.vertice = Tvertices;
	for (i = 0; i < m; i++) {
		T.vertice[i].index = i + 1;
		T.vertice[i].head = (Head *)malloc(sizeof(Head));
		T.vertice[i].index = i + 1;
		T.vertice[i].head->head = NULL;
	}
}

void setVertices(int s) { // 정점 설정
	vertices[s - 1].index = s;
}

void initEdge(int i, int s, int e, int w) { // 간선 설정
	edges[i].vert_s = s;
	edges[i].vert_e = e;
	edges[i].weight = w;
}

Node * getNode() { // 한정점에 연결된 간선 이어줄때 노드 만들기
	Node * node;
	node = (Node *)malloc(sizeof(Node));
	node->link = NULL;
	return node;
}

void insert_Node(Graph Graph, int loc, int i) { //loc은 vertices위치 i는 edge위치
	Node * node;
	Head * tmp;

	node = getNode();
	node->EdgeNode = i;
	tmp = Graph.vertice[loc - 1].head;
	node->link = tmp->head;
	tmp->head = node;
}

int opposite(int u, Node *e) { // 한 정점에 연결된 간선 반대편 정점을 반환하는 함수
	return edges[e->EdgeNode].vert_s + edges[e->EdgeNode].vert_e - u;
}

int is_Exist(int num) { // heap에 num이라는 값이 있나 보는 함수
	int i;
	for (i = 1; i <= Hcnt; i++) {
		if (Heap[i].index == num) {
			return 1;
		}
	}
	//printf("return 0\n");
	return 0;
}

int Weight(int u, int z) { // 두정점에 이어진 간선의 가중치 구하는 함수
	int i;
	for (i = 0; i < m; i++) {
		if (edges[i].vert_s == u && edges[i].vert_e == z)
			return edges[i].weight;
		else if (edges[i].vert_s == z && edges[i].vert_e == u)
			return edges[i].weight;
	}
	return -1;
}

int findCnt(int v) { // 그 해당 배낭속에 들어있는 간선의 갯수를 본다
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

	uCnt = findCnt(Sack[u-1]); // 모든 배낭의 이름을 확인해서 갯수를 센다
	vCnt = findCnt(Sack[v-1]);

	//printf("ucnt = %d vcnt = %d\n", uCnt, vCnt);

	if (uCnt < vCnt) { //u를v로 다옮길거야
		//printf("%d의 갯수 %d로 더 작아서 %d로 합쳐진다\n",u,uCnt,Sack[v-1]);
		num = Sack[u - 1];
		num2 = Sack[v - 1];
		for (i = 0; i < n; i++) {
			if (Sack[i] == num) { // 바껴야되는 작은애들을 다 찾음
				Sack[i] = num2;
			}
		}
		//Sack[u - 1] = v; // 이게뭐야?
	}
	else {
		//printf("%d의 갯수 %d로 더 작아서 %d로 합쳐진다\n", v, vCnt, Sack[u-1]);
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
	while (Tcnt < n) { // n-1번 반복
		min = removeMin(); //제일작은 인덱스를 반환함
		
		Heap[1] = Heap[Hcnt];
		Hcnt--;
		downHeap(1);

		// 힙에서 가중치가 제일 작은 간선에 연결된 두 정점을 뽑아낸다
		v = edges[min].vert_s; //정점이름
		u = edges[min].vert_e; //정점이름

		if (Sack[v - 1] != Sack[u - 1]) { //두개의 배낭이 같지 않을 때
			printf(" %d", edges[min].weight);
			sum += edges[min].weight;
			//printf("여기서 이제 합침이 일어나지 정점 %d랑 정점%d\n",v,u);
			// insert_Node()써서 T에 간선 연결해주기 -> 연결할 정점인덱스와 연결될 간선의 인덱스가 필요함
			//removeMin()의 값이 간선의 인덱스!!
			insert_Node(T, v, min); //T에 v정점에 min간선 추가
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
		setVertices(vert_s); // 정점생성
		setVertices(vert_e); // 정점생성
		initEdge(i, vert_s, vert_e, weight); // 간선만들어주기
		insert_Node(G, vert_s, i);
		insert_Node(G, vert_e, i);
	}

	KruskalMST();
	printf("\n%d\n", sum);

}