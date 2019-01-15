//힙은 힙순서와 완전이진트리를 만족한다.

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

int H[101];
int n;

void insertItem(int key);
void upHeap(int i);
void downHeap(int i);
//int buildHeap(int *a);

/*
void inPlaceHeapSort(int * a) {
	int i,tmp;

	buildHeap(a);
	for (i = n; i >= 2; i--) {
		tmp = a[1];
		a[1] = a[i];
		a[i] = tmp;
		downHeap(1, i - 1);
	}
}

int buildHeap(int * a) {
	int i;
	for (i = 1; i <= n; i++) {
		insertItem(a[i]);
	}
}
*/

void upHeap(int i) {//상향이동(insert때 사용) O(log n)
	int parent = i / 2;
	int tmp, bigger;

	if ((parent >= 1) && (H[i] > H[parent]))
		bigger = i;
	else
		bigger = parent;

	if (bigger != parent) {
		tmp = H[parent];
		H[parent] = H[i];
		H[i] = tmp;
		upHeap(parent);
	}
}

void downHeap(int i) {//하향이동(remove때 사용)
	int bigger=0, tmp;
	int left = 2 * i;
	int right = 2 * i + 1;
	int parent = i;
	
	if (left >= n)return ;
	if (right >= n)bigger = left;
	else {
		if (H[left] > H[right])bigger = left;
		else bigger = right;
	}//인덱스 찾기

	if (parent * 2 > n)//범위 제한
		return ;
	if (H[parent] > H[bigger])
		return ;
	else {
		tmp = H[parent];
		H[parent] = H[bigger];
		H[bigger] = tmp;
		downHeap(bigger);
	}
}

void insertItem(int key) {
	n += 1;
	H[n] = key;
	upHeap(n);
	printf("0\n");
}

int removeMax() {//최대값 삭제
	int key;

	key = H[1];
	n -= 1;
	H[1] = H[n + 1];
	downHeap(1);
	return key;
}

void printHeap() {
	int i;
	for (i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
}

int main() {
	char func;
	int num;

	while (1) {
		scanf("%c", &func);
		switch (func) {
		case 'i':scanf("%d", &num); getchar();
			insertItem(num); break;
		case 'd':getchar();
			printf("%d\n", removeMax());
			break;
		case 'p':getchar();
			printHeap();
			break;
		case 'q': return 0;
		}
	}
}