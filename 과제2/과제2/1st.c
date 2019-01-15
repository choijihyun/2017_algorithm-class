#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#pragma warning (disable :4996)

#define N 1000
#define LIMIT 50

typedef struct Quick {
	int a, b;
}quick;
typedef struct Array {
	int * A, *A1, *B, *B1, *C, *C1;
}Array;
typedef struct Node {//Node 구조체 선언
	int data;
	struct Node * next;
}Node;



void push_Node(Node ** head, int num);
Node * merge(Node *a, Node *b);
void mergeSort(Node ** head);
void partition(Node **Front, Node **Last, Node * node);
void print_Node(Node ** head);
void printList(Node * node);
Array createArray();
void arraySwap(int * A, int n1, int n2);
void Reverse_inPlaceQuickSort(int * L, int l, int r);
void Almost_inPlaceQuickSort(int * L, int l, int r);
quick Reverse_inPlacePartition(int *A, int l, int r, int k);
quick inPlacePartition(int *A, int l, int r, int k);
void inPlaceQuickSort(int * L, int l, int r);

void push_Node(Node ** head, int num) {//head가 가르키게 노드 생성
	Node * newnode = (Node *)malloc(sizeof(Node));
	newnode->data = num;
	newnode->next = (*head);
	(*head) = newnode;
}

void mergeSort(Node ** head) {
	Node * Node_Head = *head;//맨앞노드
	Node * a, *b;//그냥 노드

	if ((Node_Head == NULL) || (Node_Head->next == NULL))
		return;//노드가 하나(또는 없으면)면 정렬필요 없기 때문

	partition(&a, &b, Node_Head);

	mergeSort(&a);//이중포인터를 사용한거(노드의 주소를 보냄
	mergeSort(&b);

	*head = merge(a, b);//head에 정렬된 노드의 헤드를 저장함
}

Node * merge(Node * a, Node * b) {
	Node * result = NULL;//정렬된 노드를 여기에 연결할거임
	Node * p;//임시로 저정하려고 만들어놓은 노드

	if (a == NULL)//하나가 비었으면 하나에 다 몰려있는거니까!!
		return b;
	else if (b == NULL)
		return a;

	if (a->data <= b->data) {//정렬하는거니까 크기 비교하기
		result = a;
		a = a->next;
	}
	else {
		result = b;
		b = b->next;
	}
	p = result;//더 작은거 찾아서 p에 시작점으로 잡아버림

	while (a != NULL && b != NULL) {//둘다 안빌때까지
		if (a->data <= b->data) {//더 작은거 찾았으면
			p->next = a;//p에 저장시키고
			a = a->next;//저장된거 하나씩 다넘기고
			p = p->next;
		}
		else {
			p->next = b;
			b = b->next;
			p = p->next;
		}
	}
	if (a == NULL)//다 비었으면 그냥 나머지 이어버리기
		p->next = b;
	else
		p->next = a;


	return result;
}

void partition(Node ** Front, Node ** Last, Node * node) {
	Node * fast;//특정노드
	Node * slow;//특정노드의 뒤의 노드
	if (node == NULL || node->next == NULL) {
		*Front = node;
		*Last = NULL;//노드가 하나밖에 없으니까!
	}
	else {
		slow = node;
		fast = node->next;

		while (fast != NULL) {
			fast = fast->next;
			if (fast != NULL) {
				slow = slow->next;
				fast = fast->next;
			}
		}

		*Front = node;
		*Last = slow->next;
		slow->next = NULL;
	}
}

void printList(Node * node) {
	while (node != NULL) {
		printf(" %d", node->data);
		node = node->next;
	}
}

void print_Node(Node ** head) {
	Node * tmp = *head;
	while (tmp != NULL) {
		printf(" %d", tmp->data);
		tmp = tmp->next;
	}
}

void inPlaceQuickSort(int * L, int l, int r) {
	int k;
	quick q;

	if (l >= r)//l이 r보다 커야지 재귀종료
		return;

	k = r; // 결정적 퀵정렬이기 때문에 기준원소는 가장 마지막에 위치한 값이다

	q = inPlacePartition(L, l, r, k); // 중복원소 가능한 파티션 호출

	inPlaceQuickSort(L, l, (q.a) - 1); // 기준값 기준으로 왼쪽 분할 퀵정렬
	inPlaceQuickSort(L, (q.b) + 1, r); // 기준값 기준으로 오른쪽 분할 퀵정렬
}

quick inPlacePartition(int *A, int l, int r, int k) {
	//이거는 제대로 정렬된거
	quick q;
	int i, j;
	int a, b;
	int temp_loc;
	int p;

	p = A[k]; // k의 위치에 있는 값이 기준값

	i = l; // i는 l을 시작점으로 한다
	j = r - 1; // j는 r-1을 시작점으로 한다

	a = l; // 중복된 원소를 배열 가장 앞부터 모아둔다
	b = r; // 중복된 원소를 배열 가장 뒤부터 모아둔다

	while (i <= j) {
		while (i <= j && A[i] <= p) { // i은 l를 시작점으로 p보다 작거나 같은값을 찾음//작은거
			if (A[i] == p) { // 같은값을 찾을 경우, 해당범위내 배열 왼쪽에 모아둠
				arraySwap(A, a, i); // 현재 i의 값과 a의 값을 바꾼다
				a++; // a가 다음 인덱스값으로 이동한다
			}
			i++;
		}

		while (i <= j && A[j] >= p) { // j은 r-1를 시작점으로 p보다 크거나 같은값을 찾음//큰거
			if (A[j] == p) { // 같은값을 찾을 경우, 해당범위내 배열 오른쪽에 모아둠
				b--;
				arraySwap(A, j, b);
			}
			j--;
		}
		if (i < j) {
			arraySwap(A, i, j); // i < j일 경우 i과 j의 값을 바꿈
		}
	}

	// 해당 범위내의 배열의 왼쪽과 오른쪽에 모아둔 p와 중복되는 값을 배열 중앙으로 보낸다
	temp_loc = i - 1; // a에게 i-1의 위치를 전달하기 위해 임시로 저장//중복값
	while (a > i) {
		arraySwap(A, a, temp_loc);
		a--;
		temp_loc--;
	} // a가 i보다 클 때 중복된 값을 하나씩 중앙으로 이동한다
	a = temp_loc + 1; // a는 현재 중복된 원소 모아놓은 것 의 가장 첫번째 위치를 가진다

	temp_loc = i; // a에게 i의 위치를 전달하기 위해 임시로 저장
	while (b < r + 1) {
		arraySwap(A, b, temp_loc);
		b++;
		temp_loc++;
	} // b가 r+1보다 작을 때 중복된 값을 하나씩 중앙으로 이동한다
	b = temp_loc - 1; // b는 현재 중복된 원소 모아놓은 것 의 가장 마지막 위치를 가진다

	q.a = a;
	q.b = b; // 구조체 이용해서 a,b값 전달 

	return q;
}


quick Reverse_inPlacePartition(int *A, int l, int r, int k) {
	quick q;
	int i, j;
	int a, b;
	int temp_loc;
	int p;

	p = A[k];

	i = l;
	j = r - 1;
	a = l;
	b = r;

	while (i <= j) {
		while (i <= j && A[i] >= p) { // i은 l를 시작점으로 p보다 작거나 같은값을 찾음//작은거
			if (A[i] == p) { // 같은값을 찾을 경우, 해당범위내 배열 왼쪽에 모아둠
				arraySwap(A, a, i); // 현재 i의 값과 a의 값을 바꾼다
				a++; // a가 다음 인덱스값으로 이동한다
			}
			i++;
		}

		while (i <= j && A[j] <= p) { // j은 r-1를 시작점으로 p보다 크거나 같은값을 찾음//큰거
			if (A[j] == p) { // 같은값을 찾을 경우, 해당범위내 배열 오른쪽에 모아둠
				b--;
				arraySwap(A, j, b);
			}
			j--;
		}
		if (i < j) {
			arraySwap(A, i, j); // i < j일 경우 i과 j의 값을 바꿈
		}
	}

	// 해당 범위내의 배열의 왼쪽과 오른쪽에 모아둔 p와 중복되는 값을 배열 중앙으로 보낸다
	temp_loc = i - 1; // a에게 i-1의 위치를 전달하기 위해 임시로 저장//중복값
	while (a > i) {
		arraySwap(A, a, temp_loc);
		a--;
		temp_loc--;
	} // a가 i보다 클 때 중복된 값을 하나씩 중앙으로 이동한다
	a = temp_loc + 1; // a는 현재 중복된 원소 모아놓은 것 의 가장 첫번째 위치를 가진다

	temp_loc = i; // a에게 i의 위치를 전달하기 위해 임시로 저장
	while (b < r + 1) {
		arraySwap(A, b, temp_loc);
		b++;
		temp_loc++;
	} // b가 r+1보다 작을 때 중복된 값을 하나씩 중앙으로 이동한다
	b = temp_loc - 1; // b는 현재 중복된 원소 모아놓은 것 의 가장 마지막 위치를 가진다

	q.a = a;
	q.b = b; // 구조체 이용해서 a,b값 전달 

	return q;
}


void Almost_inPlaceQuickSort(int * L, int l, int r) {//여기서 limit사용
	//거의 정렬된

	quick q;

	if (r - l > LIMIT) {
		q = inPlacePartition(L, l, r, 0); // 중복원소 가능한 파티션 호출
		Almost_inPlaceQuickSort(L, l, (q.a) - 1); // 기준값 기준으로 왼쪽 분할 퀵정렬
		Almost_inPlaceQuickSort(L, (q.b) + 1, r); // 기준값 기준으로 오른쪽 분할 퀵정렬
	}
}

void Reverse_inPlaceQuickSort(int * L, int l, int r) {
	//거의 역정렬된

	quick q;
	if (r - l > LIMIT) {
		q = Reverse_inPlacePartition(L, l, r, 0); // 중복원소 가능한 파티션 호출
		Reverse_inPlaceQuickSort(L, l, (q.a) - 1); // 기준값 기준으로 왼쪽 분할 퀵정렬
		Reverse_inPlaceQuickSort(L, (q.b) + 1, r); // 기준값 기준으로 오른쪽 분할 퀵정렬
	}
}

void arraySwap(int * A, int n1, int n2) {
	int temp; // 임시로 값을 저장할 변수

	temp = A[n1];
	A[n1] = A[n2];
	A[n2] = temp;
	// A[n1]의 값과 A[n2]의 값을 swap한다
}

Array createArray() {
	Array List;
	int i;

	List.A = (int *)malloc(sizeof(int)*N);
	List.A1 = (int *)malloc(sizeof(int)*N);
	List.B = (int *)malloc(sizeof(int)*N);
	List.B1 = (int *)malloc(sizeof(int)*N);
	List.C = (int *)malloc(sizeof(int)*N);
	List.C1 = (int *)malloc(sizeof(int)*N);

	for (i = 0; i < N; i++) {
		srand((unsigned)time(NULL));
		List.A[i] = rand() % N + 1;
	}

	for (i = 0; i < N; i++) {
		List.B[i] = List.A[i];
		List.C[i] = List.A[i];
	}

	inPlaceQuickSort(List.B, 0, N - 1);
	inPlaceQuickSort(List.C, 0, N - 1);
	
	for (i = 0; i < N; i++) {
		List.A1[i] = List.A[i];
		List.B1[i] = List.B[i];
		List.C1[i] = List.C[i];
	}
	return List;
}

int main() {
	Array L;
	LARGE_INTEGER Start, End, Freq; // 실행시간을 재는 변수들. 
	double runtime; // 실행시간을 저장하는 변수

	L = createArray();
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  // 실행시간 시작시간
	inPlaceQuickSort(L.A, 0, N - 1); // {deterministic version} 제자리 결정적 퀵 정렬 실행
	QueryPerformanceCounter(&End); // 실행시간 종료시간
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart; // 실행시간 계산
	printf("퀵정렬(랜덤) CPU time = %0.10lf\n", runtime); // 실행시간 출력
	
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  // 실행시간 시작시간
	mergeSort(L.A1, 0, N - 1);// 합병정렬 실행
	QueryPerformanceCounter(&End); // 실행시간 종료시간
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart; // 실행시간 계산
	printf("합병정렬(랜덤) CPU time = %0.10lf\n", runtime); // 실행시간 출력
	printf("\n");
	// 랜덤 리스트
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  // 실행시간 시작시간
	inPlaceQuickSort(L.B, 0, N - 1); // {deterministic version} 제자리 결정적 퀵 정렬 실행
	QueryPerformanceCounter(&End); // 실행시간 종료시간
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart; // 실행시간 계산
	printf("퀵정렬(거의 정렬된) CPU time = %0.10lf\n", runtime); // 실행시간 출력

	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  // 실행시간 시작시간
	mergeSort(L.B1, 0, N - 1);// 합병정렬 실행
	QueryPerformanceCounter(&End); // 실행시간 종료시간
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart; // 실행시간 계산
	printf("합병정렬(거의 정렬된) CPU time = %0.10lf\n", runtime); // 실행시간 출력
	printf("\n");
	// 거의 정렬된 리스트
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  // 실행시간 시작시간
	inPlaceQuickSort(L.C, 0, N - 1);// {deterministic version} 제자리 결정적 퀵 정렬 실행
	QueryPerformanceCounter(&End); // 실행시간 종료시간
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart; // 실행시간 계산
	printf("퀵정렬(거의 역정렬된) CPU time = %0.10lf\n", runtime); // 실행시간 출력

	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  // 실행시간 시작시간
	mergeSort(L.C1, 0, N - 1); // 합병정렬 실행
	QueryPerformanceCounter(&End); // 실행시간 종료시간
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart; // 실행시간 계산
	printf("합병정렬(거의 역정렬된) CPU time = %0.10lf\n", runtime); // 실행시간 출력
														   // 거의 역정렬된 리스트



}