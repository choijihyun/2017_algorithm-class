#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define N 1000 // ����Ʈ�� ũ��
#define Limit 50 // ���� ���ĵ�, ���� �����ĵ� ����Ʈ�� ���� ������ ����

typedef struct Arrays {
	int *A, *B, *C, *A1, *B1, *C1; 
}arrays;
typedef struct Quick {
	int a, b; 
}quick;

void mergeSort(int * A, int l, int r);
void merge(int * A, int l, int m, int r);
void inPlaceQuickSort(int * L, int l, int r);
quick inPlacePartition(int *A, int l, int r, int k);
void arraySwap(int *A, int n1, int n2);
arrays createArrays();
void a_s_inPlaceQuickSort(int * L, int l, int r);
void a_i_s_inPlaceQuickSort(int * L, int l, int r);
quick inverse_inPlacePartition(int *A, int l, int r, int k);

int main()
{
	arrays L; 
	LARGE_INTEGER Start, End, Freq;
	double runtime; 

	L = createArrays();

	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);
	inPlaceQuickSort(L.A, 0, N - 1);
	QueryPerformanceCounter(&End); 
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart;
	printf("������(����) CPU time = %0.10lf\n", runtime); 

	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start); 
	mergeSort(L.A1, 0, N - 1);
	QueryPerformanceCounter(&End);
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart;
	printf("�պ�����(����) CPU time = %0.10lf\n", runtime); 
	printf("\n");
	// ���� ����Ʈ
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start); 
	inPlaceQuickSort(L.B, 0, N - 1); 
	QueryPerformanceCounter(&End); 
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart;
	printf("������(���� ���ĵ�) CPU time = %0.10lf\n", runtime); 

	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start); 
	mergeSort(L.B1, 0, N - 1);
	QueryPerformanceCounter(&End);
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart;
	printf("�պ�����(���� ���ĵ�) CPU time = %0.10lf\n", runtime);
	printf("\n");
	// ���� ���ĵ� ����Ʈ
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start); 
	inPlaceQuickSort(L.C, 0, N - 1);
	QueryPerformanceCounter(&End); 
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart;
	printf("������(���� �����ĵ�) CPU time = %0.10lf\n", runtime);

	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Start);  
	mergeSort(L.C1, 0, N - 1);
	QueryPerformanceCounter(&End);
	runtime = (double)(End.QuadPart - Start.QuadPart) / (double)Freq.QuadPart;
	printf("�պ�����(���� �����ĵ�) CPU time = %0.10lf\n", runtime);
	// ���� �����ĵ� ����Ʈ

	return 0;
}

void mergeSort(int * A, int l, int r) {
	int m;

	if (l < r) {
		m = (l + r) / 2; // ����Ʈ ������ ����

		mergeSort(A, l, m);      //���� ��� ����
		mergeSort(A, m + 1, r);  //������ ��� ����
		merge(A, l, m, r);   //���ҵ� ��� ����
	}
}

void merge(int * A, int l, int m, int r) {
	int i, j, k;
	int B[N]; // Nũ���� �迭 ����

	i = l;
	j = m + 1;
	k = l;    //��� �迭�� �ε���

			  //i���� m ������ ��ϰ� j���� r������ ����� ���� ���ϴ� �κ�
	while (i <= m && j <= r) {
		if (A[i] <= A[j])  //i ���� j ������ �۰ų� ������ i ���� ��� ����
			B[k++] = A[i++];
		else      //�ƴ϶�� j ����  ����
			B[k++] = A[j++];
	}

	while (i <= m)
		B[k++] = A[i++];

	while (j <= r)
		B[k++] = A[j++];

	for (k = l; k <= r; k++)
		A[k] = B[k]; // �����ߴ� �� ������
}
void inPlaceQuickSort(int * L, int l, int r) {
	int k;
	quick q;

	if (l >= r)
		return;

	k = r; 

	q = inPlacePartition(L, l, r, k); 

	inPlaceQuickSort(L, l, (q.a) - 1);
	inPlaceQuickSort(L, (q.b) + 1, r);
}
quick inPlacePartition(int *A, int l, int r, int k) {
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
		while (i <= j && A[i] <= p) { // i�� l�� ���������� p���� �۰ų� �������� ã��
			if (A[i] == p) { // �������� ã�� ���, �ش������ �迭 ���ʿ� ��Ƶ�
				arraySwap(A, a, i); // ���� i�� ���� a�� ���� �ٲ۴�
				a++; // a�� ���� �ε��������� �̵��Ѵ�
			}
			i++;
		}

		while (i <= j && A[j] >= p) { // j�� r-1�� ���������� p���� ũ�ų� �������� ã��
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
	temp_loc = i - 1; // a���� i-1�� ��ġ�� �����ϱ� ���� �ӽ÷� ����
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

void arraySwap(int * A, int n1, int n2) {
	int temp; 

	temp = A[n1];
	A[n1] = A[n2];
	A[n2] = temp;
}

arrays createArrays() {
	arrays L;
	int i;

	L.A = (int*)malloc(sizeof(int) * N);
	L.B = (int*)malloc(sizeof(int) * N);
	L.C = (int*)malloc(sizeof(int) * N);
	L.A1 = (int*)malloc(sizeof(int) * N);
	L.B1 = (int*)malloc(sizeof(int) * N);
	L.C1 = (int*)malloc(sizeof(int) * N);


	srand((unsigned)time(NULL));

	for (i = 0; i<N; i++) {
		L.A[i] = rand() % N + 1;
	} 

	for (i = 0; i<N; i++) {
		L.B[i] = L.A[i];
		L.C[i] = L.A[i];
	} 

	a_s_inPlaceQuickSort(L.B, 0, N - 1);
	a_i_s_inPlaceQuickSort(L.C, 0, N - 1);

	for (i = 0; i<N; i++) {
		L.A1[i] = L.A[i]; 
		L.B1[i] = L.B[i]; 
		L.C1[i] = L.C[i]; 
	}

	return L;
}

void a_s_inPlaceQuickSort(int * A, int l, int r) {
	quick q;

	if ((r - l) > Limit) { 
		q = inPlacePartition(A, l, r, 0);
		a_s_inPlaceQuickSort(A, l, q.a - 1);
		a_s_inPlaceQuickSort(A, q.b + 1, r);
	}
	// ���� ���ĵ� ����Ʈ�� �ȴ�
}
void a_i_s_inPlaceQuickSort(int * A, int l, int r) {
	quick q;

	if ((r - l) > Limit) { 
		q = inverse_inPlacePartition(A, l, r, 0);
		a_i_s_inPlaceQuickSort(A, l, q.a - 1);
		a_i_s_inPlaceQuickSort(A, q.b + 1, r);
	}
	// ���� �����ĵ� ����Ʈ�� �ȴ�
}
quick inverse_inPlacePartition(int *A, int l, int r, int k) {
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
	// �ּ� �޸� �κ� �����ϰ� inPlacePartition�� ����
	while (i <= j) {
		while (i <= j && A[i] >= p) {	// �������� ���� inPlacePartition���� �ٸ��� i�� l�� ���������� p���� ũ�ų� �������� ã��
			if (A[i] == p) {
				arraySwap(A, a, i);
				a++;
			}
			i++;
		}
		while (i <= j && A[j] <= p) {	// �������� ���� inPlacePartition���� �ٸ��� j�� r-1�� ���������� p���� �۰ų� �������� ã��
			if (A[j] == p) {
				b--;
				arraySwap(A, j, b);
			}
			j--;
		}
		if (i < j) {
			arraySwap(A, i, j);
		}
	}
	temp_loc = i - 1;
	while (a > i) {
		arraySwap(A, a, temp_loc);
		a--;
		temp_loc--;
	}
	a = temp_loc + 1;

	temp_loc = i;
	while (b < r + 1) {
		arraySwap(A, b, temp_loc);
		b++;
		temp_loc++;
	}
	b = temp_loc - 1;

	q.a = a;
	q.b = b;

	return q;
}

