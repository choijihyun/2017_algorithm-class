#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct Edge {
	char origin, destination;
}Edge;

typedef struct Vertice {
	char name;
	struct NodeHead * outEdge;
	struct NodeHead * inEdge;
	int inDegree;
}Vertice;

typedef struct Graph {
	Vertice * vertices;
	Edge * edges;
}Graph;

typedef struct NodeHead {
	struct Node * head;
}NodeHead;

typedef struct Node {
	int element;
	struct Node * next;
}Node;

typedef struct Queue{
	int front, rear;
	int *data;
}Queue;

int n, m;
int *topOrder, *in;
Graph G;
Queue Q;
int Front, Rear;

int index(char vName) {
	int i;
	for (i = 0; i < n; i++) {
		if (G.vertices[i].name == vName)
			return i;
	}
	return -1;
}

Node * getNode()
{
	Node *node;

	node = (Node *)malloc(sizeof(Node));
	node->next = NULL;

	return node;
}

void insertFirst(NodeHead * H,int i) {
	Node * node;

	node = getNode();
	node->element = i;
	node->next = H->head->next; // 오류발생
	H->head->next = node;
}

void insertDirectedEdge(char uName, char wName, int i) {
	int u, w;

	u = index(uName);
	w = index(wName);

	G.edges[i].origin = u;
	G.edges[i].destination = w;

	insertFirst(G.vertices[u].outEdge, i);
	insertFirst(G.vertices[w].inEdge, i);

	G.vertices[w].inDegree++;
}


NodeHead * newNode()
{
	NodeHead *list;

	list = (NodeHead *)malloc(sizeof(NodeHead));
	list->head = getNode();
	list->head->next = NULL;

	return list;
}

void insertVertex(char vName, int i) {
	G.vertices[i].name = vName;
	G.vertices[i].outEdge = newNode();
	G.vertices[i].inEdge = newNode();
	G.vertices[i].inDegree = 0;
}

void initializeGraph() {
	G.vertices = (Vertice *)malloc(sizeof(Vertice) * 100);
	G.edges = (Edge *)malloc(sizeof(Edge) * 1000);
	topOrder = (int *)malloc(sizeof(int)*101);
	in = (int *)malloc(sizeof(int)*100);
}

void buildGraph() {
	int i;
	char ch;
	char ps, pe;

	initializeGraph();

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		getchar();
		scanf("%c", &ch);
		insertVertex(ch, i);
	}
	scanf("%d", &m);
	for (i = 0; i < m; i++) {
		getchar();
		scanf("%c %c", &ps, &pe);
		insertDirectedEdge(ps, pe, i);
	}

}

void initQueue() {
	Q.front = 0;
	Q.rear = 0;
	Q.data = (int *)malloc(sizeof(int) * n);
}

int isFull() {
	return (Q.rear + 1) % n == Q.front;
}

int isEmpty() {
	return Q.rear == Q.front;
}

void enqueue(int index) {
	if (isFull())
		return;
	Q.rear = (Q.rear + 1) % n;
	Q.data[Q.rear] = index;
}

int dequeue() {
	if (isEmpty())
		return -1;
	Q.front = (Q.front + 1) % n;
	return Q.data[Q.front];
}

void topologicalSort() {
	int i, t, u, e, w;
	Node * node;
	
	initQueue();
	for (i = 0; i < n; i++) {
		in[i] = G.vertices[i].inDegree;
		if (in[i] == 0)
			enqueue(i);
	}
	t = 1;
	while (!isEmpty()) {
		u = dequeue();
		topOrder[t] = u;
		t++;

		node = G.vertices[u].outEdge->head->next;
		while(node!=NULL) {
			e = node->element;
			w = G.edges[e].destination;
			in[w]--;
			if (in[w] == 0)
				enqueue(w);
			node = node->next;
		}
	}

	if (t <= n)
		topOrder[0] = 0;
	else
		topOrder[0] = 1;
}

int main() {
	int i;
	buildGraph();
	topologicalSort();

	if (topOrder[0] == 0)
		printf("0\n");
	else {
		for (i = 1; i <= n; i++) {
			printf("%c ", G.vertices[topOrder[i]].name);
		}
	}
}