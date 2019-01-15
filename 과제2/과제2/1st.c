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
typedef struct Node {//Node ����ü ����
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

void push_Node(Node ** head, int num) {//head�� ����Ű�� ��� ����
	Node * newnode = (Node *)malloc(sizeof(Node));
	newnode->data = num;
	newnode->next = (*head);
	(*head) = newnode;
}

void mergeSort(Node ** head) {
	Node * Node_Head = *head;//�Ǿճ��
	Node * a, *b;//�׳� ���

	if ((Node_Head == NULL) || (Node_Head->next == NULL))
		return;//��尡 �ϳ�(�Ǵ� ������)�� �����ʿ� ���� ����

	partition(&a, &b, Node_Head);

	mergeSort(&a);//���������͸� ����Ѱ�(����� �ּҸ� ����
	mergeSort(&b);

	*head = merge(a, b);//head�� ���ĵ� ����� ��带 ������
}

Node * merge(Node * a, Node * b) {
	Node * result = NULL;//���ĵ� ��带 ���⿡ �����Ұ���
	Node * p;//�ӽ÷� �����Ϸ��� �������� ���

	if (a == NULL)//�ϳ��� ������� �ϳ��� �� �����ִ°Ŵϱ�!!
		return b;
	else if (b == NULL)
		return a;

	if (a->data <= b->data) {//�����ϴ°Ŵϱ� ũ�� ���ϱ�
		result = a;
		a = a->next;
	}
	else {
		result = b;
		b = b->next;
	}
	p = result;//�� ������ ã�Ƽ� p�� ���������� ��ƹ���

	while (a != NULL && b != NULL) {//�Ѵ� �Ⱥ�������
		if (a->data <= b->data) {//�� ������ ã������
			p->next = a;//p�� �����Ű��
			a = a->next;//����Ȱ� �ϳ��� �ٳѱ��
			p = p->next;
		}
		else {
			p->next = b;
			b = b->next;
			p = p->next;
		}
	}
	if (a == NULL)//�� ������� �׳� ������ �̾������
		p->next = b;
	else
		p->next = a;


	return result;
}

void partition(Node ** Front, Node ** Last, Node * node) {
	Node * fast;//Ư�����
	Node * slow;//Ư������� ���� ���
	if (node == NULL || node->next == NULL) {
		*Front = node;
		*Last = NULL;//��尡 �ϳ��ۿ� �����ϱ�!
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

	if (l >= r)//l�� r���� Ŀ���� �������
		return;

	k = r; // ������ �������̱� ������ ���ؿ��Ҵ� ���� �������� ��ġ�� ���̴�

	q = inPlacePartition(L, l, r, k); // �ߺ����� ������ ��Ƽ�� ȣ��

	inPlaceQuickSort(L, l, (q.a) - 1); // ���ذ� �������� ���� ���� ������
	inPlaceQuickSort(L, (q.b) + 1, r); // ���ذ� �������� ������ ���� ������
}

quick inPlacePartition(int *A, int l, int r, int k) {
	//�̰Ŵ� ����� ���ĵȰ�
	quick q;
	int i, j;
	int a, b;
	int temp_loc;
	int p;

	p = A[k]; // k�� ��ġ�� �ִ� ���� ���ذ�

	i = l; // i�� l�� ���������� �Ѵ�
	j = r - 1; // j�� r-1�� ���������� �Ѵ�

	a = l; // �ߺ��� ���Ҹ� �迭 ���� �պ��� ��Ƶд�
	b = r; // �ߺ��� ���Ҹ� �迭 ���� �ں��� ��Ƶд�

	while (i <= j) {
		while (i <= j && A[i] <= p) { // i�� l�� ���������� p���� �۰ų� �������� ã��//������
			if (A[i] == p) { // �������� ã�� ���, �ش������ �迭 ���ʿ� ��Ƶ�
				arraySwap(A, a, i); // ���� i�� ���� a�� ���� �ٲ۴�
				a++; // a�� ���� �ε��������� �̵��Ѵ�
			}
			i++;
		}

		while (i <= j && A[j] >= p) { // j�� r-1�� ���������� p���� ũ�ų� �������� ã��//ū��
			if (A[j] == p) { // �������� ã�� ���, �ش������ �迭 �����ʿ� ��Ƶ�
				b--;
				arraySwap(A, j, b);
			}
			j--;
		}
		if (i < j) {
			arraySwap(A, i, j); // i < j�� ��� i�� j�� ���� �ٲ�
		}
	}

	// �ش� �������� �迭�� ���ʰ� �����ʿ� ��Ƶ� p�� �ߺ��Ǵ� ���� �迭 �߾����� ������
	temp_loc = i - 1; // a���� i-1�� ��ġ�� �����ϱ� ���� �ӽ÷� ����//�ߺ���
	while (a > i) {
		arraySwap(A, a, temp_loc);
		a--;
		temp_loc--;
	} // a�� i���� Ŭ �� �ߺ��� ���� �ϳ��� �߾����� �̵��Ѵ�
	a = temp_loc + 1; // a�� ���� �ߺ��� ���� ��Ƴ��� �� �� ���� ù��° ��ġ�� ������

	temp_loc = i; // a���� i�� ��ġ�� �����ϱ� ���� �ӽ÷� ����
	while (b < r + 1) {
		arraySwap(A, b, temp_loc);
		b++;
		temp_loc++;
	} // b�� r+1���� ���� �� �ߺ��� ���� �ϳ��� �߾����� �̵��Ѵ�
	b = temp_loc - 1; // b�� ���� �ߺ��� ���� ��Ƴ��� �� �� ���� ������ ��ġ�� ������

	q.a = a;
	q.b = b; // ����ü �̿��ؼ� a,b�� ���� 

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
		while (i <= j && A[i] >= p) { // i�� l�� ���������� p���� �۰ų� �������� ã��//������
			if (A[i] == p) { // �������� ã�� ���, �ش������ �迭 ���ʿ� ��Ƶ�
				arraySwap(A, a, i); // ���� i�� ���� a�� ���� �ٲ۴�
				a++; // a�� ���� �ε��������� �̵��Ѵ�
			}
			i++;
		}

		while (i <= j && A[j] <= p) { // j�� r-1�� ���������� p���� ũ�ų� �������� ã��//ū��
			if (A[j] == p) { // �������� ã�� ���, �ش������ �迭 �����ʿ� ��Ƶ�
				b--;
				arraySwap(A, j, b);
			}
			j--;
		}
		if (i < j) {
			arraySwap(A, i, j); // i < j�� ��� i�� j�� ���� �ٲ�
		}
	}

	// �ش� �������� �迭�� ���ʰ� �����ʿ� ��Ƶ� p�� �ߺ��Ǵ� ���� �迭 �߾����� ������
	temp_loc = i - 1; // a���� i-1�� ��ġ�� �����ϱ� ���� �ӽ÷� ����//�ߺ���
	while (a > i) {
		arraySwap(A, a, temp_loc);
		a--;
		temp_loc--;
	} // a�� i���� Ŭ �� �ߺ��� ���� �ϳ��� �߾����� �̵��Ѵ�
	a = temp_loc + 1; // a�� ���� �ߺ��� ���� ��Ƴ��� �� �� ���� ù��° ��ġ�� ������

	temp_loc = i; // a���� i�� ��ġ�� �����ϱ� ���� �ӽ÷� ����
	while (b < r + 1) {
		arraySwap(A, b, temp_loc);
		b++;
		temp_loc++;
	} // b�� r+1���� ���� �� �ߺ��� ���� �ϳ��� �߾����� �̵��Ѵ�
	b = temp_loc - 1; // b�� ���� �ߺ��� ���� ��Ƴ��� �� �� ���� ������ ��ġ�� ������

	q.a = a;
	q.b = b; // ����ü �̿��ؼ� a,b�� ���� 

	return q;
}


void Almost_inPlaceQuickSort(int * L, int l, int r) {//���⼭ limit���
	//���� ���ĵ�

	quick q;

	if (r - l > LIMIT) {
		q = inPlacePartition(L, l, r, 0); // �ߺ����� ������ ��Ƽ�� ȣ��
		Almost_inPlaceQuickSort(L, l, (q.a) - 1); // ���ذ� �������� ���� ���� ������
		Almost_inPlaceQuickSort(L, (q.b) + 1, r); // ���ذ� �������� ������ ���� ������
	}
}

void Reverse_inPlaceQuickSort(int * L, int l, int r) {
	//���� �����ĵ�

	quick q;
	if (r - l > LIMIT) {
		q = Reverse_inPlacePartition(L, l, r, 0); // �ߺ����� ������ ��Ƽ�� ȣ��
		Reverse_inPlaceQuickSort(L, l, (q.a) - 1); // ���ذ� �������� ���� ���� ������
		Reverse_inPlaceQuickSort(L, (q.b) + 1, r); // ���ذ� �������� ������ ���� ������
	}
}

void arraySwap(int * A, int n1, int n2) {
	int temp; // �ӽ÷� ���� ������ ����

	temp = A[n1];
	A[n1] = A[n2];
	A[n2] = temp;
	// A[n1]�� ���� A[n2]�� ���� swap�Ѵ�
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
	LARGE_INTEGER Start, End, Freq; // ����ð��� ��� ������. 
	double runtime; // ����ð��� �����ϴ� ����

	L = createArray();
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  // ����ð� ���۽ð�
	inPlaceQuickSort(L.A, 0, N - 1); // {deterministic version} ���ڸ� ������ �� ���� ����
	QueryPerformanceCounter(&End); // ����ð� ����ð�
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart; // ����ð� ���
	printf("������(����) CPU time = %0.10lf\n", runtime); // ����ð� ���
	
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  // ����ð� ���۽ð�
	mergeSort(L.A1, 0, N - 1);// �պ����� ����
	QueryPerformanceCounter(&End); // ����ð� ����ð�
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart; // ����ð� ���
	printf("�պ�����(����) CPU time = %0.10lf\n", runtime); // ����ð� ���
	printf("\n");
	// ���� ����Ʈ
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  // ����ð� ���۽ð�
	inPlaceQuickSort(L.B, 0, N - 1); // {deterministic version} ���ڸ� ������ �� ���� ����
	QueryPerformanceCounter(&End); // ����ð� ����ð�
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart; // ����ð� ���
	printf("������(���� ���ĵ�) CPU time = %0.10lf\n", runtime); // ����ð� ���

	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  // ����ð� ���۽ð�
	mergeSort(L.B1, 0, N - 1);// �պ����� ����
	QueryPerformanceCounter(&End); // ����ð� ����ð�
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart; // ����ð� ���
	printf("�պ�����(���� ���ĵ�) CPU time = %0.10lf\n", runtime); // ����ð� ���
	printf("\n");
	// ���� ���ĵ� ����Ʈ
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  // ����ð� ���۽ð�
	inPlaceQuickSort(L.C, 0, N - 1);// {deterministic version} ���ڸ� ������ �� ���� ����
	QueryPerformanceCounter(&End); // ����ð� ����ð�
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart; // ����ð� ���
	printf("������(���� �����ĵ�) CPU time = %0.10lf\n", runtime); // ����ð� ���

	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  // ����ð� ���۽ð�
	mergeSort(L.C1, 0, N - 1); // �պ����� ����
	QueryPerformanceCounter(&End); // ����ð� ����ð�
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart; // ����ð� ���
	printf("�պ�����(���� �����ĵ�) CPU time = %0.10lf\n", runtime); // ����ð� ���
														   // ���� �����ĵ� ����Ʈ



}