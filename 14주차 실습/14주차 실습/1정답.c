#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct Edge
{
	int endpoint1, endpoint2;
	int weight;
}Edge;

typedef struct IncidentEdges
{
	int edge_num;
	struct IncidentEdges* next;

}IncidentEdges;

typedef struct Vertex
{
	int name;
	IncidentEdges *incidentedges;

}Vertex;

typedef struct Graph
{
	Vertex vertex[102];
	Edge edges[1002];
	int n;

}Graph;

typedef struct PQ
{
	int vertex_name;
	int weight;

}PQ;
 //===========================================================
void init_G(Graph *graph, int N);
void Input(Graph *graph, int vertex_index, int u, int v, int w);
void DijkstraShortestPaths(Graph *graph, int S);
void Input_H(PQ heap[], int vt_name, int w, int* heap_len);
int removeMin(PQ heap[], int *heap_len);
void HEAP(PQ heap[], int root_index, int heap_len);
void Swap(int *x, int *y);
int Opposite(Graph* graph, IncidentEdges *e, int u);
int replacetKey(PQ heap[], int z, int Dis, int *heap_len);
//===========================================================
void Swap(int *x, int *y){
	int t;
	t = *x;
	*x = *y;
	*y = t;
}

void Input_H(PQ heap[], int vt_name, int w, int* heap_len){
	int i;
	int parent;
	heap[*heap_len].vertex_name = vt_name;
	heap[*heap_len].weight = w;
	i = *heap_len;
	parent = i / 2;
	(*heap_len)++;
	while (i != 1 && heap[parent].weight > heap[i].weight){
		Swap(&heap[parent].vertex_name, &heap[i].vertex_name);
		Swap(&heap[parent].weight, &heap[i].weight);
		i = parent;
		parent = i / 2;
	}
}

int removeMin(PQ heap[], int *heap_len){
	int result1, result2;
	result1 = heap[1].vertex_name;
	result2 = heap[1].weight;
	heap[1].vertex_name = heap[(*heap_len) - 1].vertex_name;
	heap[1].weight = heap[(*heap_len) - 1].weight;
	heap[(*heap_len) - 1].vertex_name = 0;
	heap[(*heap_len) - 1].weight = 0;
	(*heap_len)--;
	HEAP(heap, 1, *heap_len);
	return result1;
}

void HEAP(PQ heap[], int root_index, int heap_len){
	int l, r;
	int sm;
	l = root_index * 2;
	r = (root_index * 2) + 1;
	sm = root_index;
	if (l < heap_len && heap[l].weight < heap[root_index].weight || (heap[l].weight == heap[root_index].weight && heap[l].vertex_name < heap[root_index].vertex_name)){
		sm = l;
	}
	if (r < heap_len && heap[r].weight < heap[sm].weight || (heap[r].weight == heap[sm].weight && heap[r].vertex_name < heap[sm].vertex_name)){
		sm = r;
	}
	if (sm != root_index){
		Swap(&heap[root_index].vertex_name, &heap[sm].vertex_name);
		Swap(&heap[root_index].weight, &heap[sm].weight);
		HEAP(heap, sm, heap_len);
	}
}

int Search(PQ heap[], int z, int i){ // 정점이름이 있는지 없는 지 확인
	int l, r;
	if (heap[i].vertex_name == 0){
		return 0;
	}

	if (heap[i].vertex_name == z){
		return i;
	}
	else{
		l = Search(heap, z, i * 2);
		r = Search(heap, z, (i * 2) + 1);
		if (l > 0){
			return l;
		}
		else if (r > 0){
			return r;
		}
		else{
			return 0;
		}
	}
}

int Opposite(Graph* graph, IncidentEdges *e, int u){ //반대편 정점 찾기
	return graph->edges[e->edge_num].endpoint2 + graph->edges[e->edge_num].endpoint1 - u;
}

void DijkstraShortestPaths(Graph *graph, int S){
	int Distance[102];
	PQ heap[1002];
	int flag[102] = { 0 };
	int heap_len = 1;
	int i;
	int u, z;
	IncidentEdges* e;
	for (i = 0; i < graph->n; i++){
		Distance[i] = 30000;
	}
	Distance[S - 1] = 0;
	Input_H(heap, S - 1, 0, &heap_len);
	while (heap_len > 1){
		u = removeMin(heap, &heap_len);
		flag[u] = 1;
		e = graph->vertex[u].incidentedges;
		while (e != NULL){
			z = Opposite(graph, e, u);
			if (Distance[u] + graph->edges[e->edge_num].weight < Distance[z]){
				Distance[z] = Distance[u] + graph->edges[e->edge_num].weight;
				replacetKey(heap, z, Distance[z], &heap_len);
			}
			e = e->next;
		}
	}

	for (i = 0; i < graph->n; i++){
		if (i != S - 1 && Distance[i] != 30000){
			printf("%d %d\n", i + 1, Distance[i]);
		}
	}
}

int replacetKey(PQ heap[], int z, int Dis, int *heap_len){ // 힙 위치 다시 잡아주기
	int i;
	int parent;
	int v_index;

	i = Search(heap, z, 1);
	if (i != 0){
		heap[i].weight = -1;
		parent = i / 2;
		while (i != 1 && heap[parent].weight > heap[i].weight){
			Swap(&heap[parent].vertex_name, &heap[i].vertex_name);
			Swap(&heap[parent].weight, &heap[i].weight);
			i = parent;
			parent = i / 2;
		}
		v_index = heap[1].vertex_name;
		removeMin(heap, heap_len);
		Input_H(heap, v_index, Dis, heap_len);
	}
	else{
		Input_H(heap, z, Dis, heap_len);
	}
	return 0;
}

IncidentEdges* makeEdge(int vertex_index, int w){ // 간선 만들기
	IncidentEdges *p;
	p = (IncidentEdges*)malloc(sizeof(IncidentEdges));
	memset(p, 0, sizeof(IncidentEdges));
	p->edge_num = vertex_index;
	return p;
}

void Input(Graph* graph, int vertex_index, int u, int v, int w){
	IncidentEdges *p;
	graph->edges[vertex_index].weight = w; // 가중치
	graph->edges[vertex_index].endpoint1 = u; // 정점 
	graph->edges[vertex_index].endpoint2 = v; // 다른정점
	// u
	if (graph->vertex[u].incidentedges == NULL){ // 정점에 연결된 간선이 없을때
		p = makeEdge(vertex_index, w); // 간선 만들기
		graph->vertex[u].incidentedges = p; // 넣어주기
	}
	else{ // 연결된 간선이 하나라도 있을 때
		p = graph->vertex[u].incidentedges;
		while (p->next != NULL){ // 마지막 간선 위치 노드 찾기
			p = p->next;
		}
		p->next = makeEdge(vertex_index, w); // 위치 찾아서 넣기
	}
	// v
	if (graph->vertex[v].incidentedges == NULL){
		p = makeEdge(vertex_index, w);
		graph->vertex[v].incidentedges = p;
	}
	else{
		p = graph->vertex[v].incidentedges;
		while (p->next != NULL){
			p = p->next;
		}
		p->next = makeEdge(vertex_index, w);
	}
}

void init_G(Graph* graph, int N){ //그래프 초기화
	int i;
	for (i = 0; i < N; i++){
		graph->vertex[i].name = i + 1; // 정점이름으로 초기화
	}
	graph->n = N; // 그래프 정점 저장해줌
}


int main() {
	int N, M, S;
	int i;
	int u, v, w;
	Graph *graph;
	scanf("%d %d %d", &N, &M, &S);
	graph = (Graph*)malloc(sizeof(Graph));
	memset(graph, 0, sizeof(Graph));
	init_G(graph, N);
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &u, &v, &w);
		Input(graph, i, u - 1, v - 1, w);
	}
	DijkstraShortestPaths(graph, S);
	return 0;
}
