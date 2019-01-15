#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

int H[100];
int n = 0;//key����

void buildHeap();
void downHeap(int i);
void inPlaceHeapSort();
void printArray();
void arraySwap(int a, int b);

void buildHeap() {
	int i;
	for (i = n / 2; i >= 1; i--)
		downHeap(i);
}

void arraySwap(int n1, int n2) {
	int temp; // �ӽ÷� ���� ������ ����

	temp = H[n1];
	H[n1] = H[n2];
	H[n2] = temp;
	// A[n1]�� ���� A[n2]�� ���� swap�Ѵ�
}

void downHeap(int i) {
	int right, left;
	int smaller;

	left = 2 * i;
	right = left + 1;

	if (left > n)//��������
		return;
	smaller = left;
	if (right <= n) {
		if (H[left] <= H[right])
			smaller = right;
	}
	if (H[i] >= H[smaller])
		return;
	arraySwap(i, smaller);
	downHeap(smaller);
}

void inPlaceHeapSort() {
	int i;
	buildHeap();
	for (i = n; i >1; i--) {
		arraySwap(1, i);
		n--;
		downHeap(1);
	}
}

void printArray() {
	int i;
	for (i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}

int main() {
	int i,cnt;
	scanf("%d", &cnt);
	for (i = 1; i <= cnt; i++)
		scanf("%d", H+i);
	n = cnt;
	inPlaceHeapSort();
	n = cnt;
	printArray();
}