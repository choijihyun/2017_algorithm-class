//순위를 뭘 물어볼지 모르니까 최악까지 생각해야된다
//그러므로 전체를 정렬해서 순서를 찾는것이 효율적
//힙 정렬 특히 상향식으로 하는게 제일 효율적

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4996)

#define MAX 10

int cnt = 0;

/*
void downHeap(int * L,int n) {//힙생성
int parent = 1;
int left = parent * 2, right = left + 1;
int smaller,tmp;

while (1) {
if (parent * 2 > n)break;
if (left >= n)break;
if (right >= n)smaller = left;
else {
if (*(L + left) > L[right])
smaller = right;
else
smaller = left;
}

if (L[parent] > L[smaller]) {
tmp = L[parent];
L[parent] = L[smaller];
L[smaller] = tmp;
smaller = parent;
}
left = smaller * 2;
right = left + 1;
}
}
*/

void downHeap(int i, int n, int *H) {
	int bigger, tmp;
	int left = 2 * i;
	int right = 2 * i + 1;
	int parent = i;

	if (H[left] >= H[right])
		bigger = left;
	else
		bigger = right;

	while (1) {
		if (parent * 2 > n)
			break;
		if (H[parent] > H[bigger])
			break;
		else {
			tmp = H[parent];
			H[parent] = H[bigger];
			H[bigger] = tmp;
			parent = bigger;
		}

		left = 2 * parent;
		right = left + 1;
		if (H[left] >= H[right])
			bigger = left;
		else
			bigger = right;
	}
}

void buildHeap(int n, int *L) {
	int i;
	for (i = n / 2; i >= 1; i--)
		downHeap(i, n, L);
}


int findKthSmallest(int * L, int n, int k) {
	int i, tmp;
	
	if (cnt < k) {
		for (i = cnt; i < k; i++) {
			tmp = L[n-i];
			L[n-i] = L[1];
			L[1] = tmp;
			printf("tmp= %d\n", L[n-i]);

			downHeap(1, n - i - 1, L);
		}
		cnt = k;
	}

	for (i = 1; i <= n; i++)
		printf(" %d", L[i]);
	printf("\n");

	printf("===%d===\n", L[n - k + 1]);
	return L[n - k + 1];
}

int main() {
	int n, i, k, e;
	int *L;

	printf("리스트 크기:");
	scanf("%d", &n);
	L = (int *)malloc(sizeof(int)*(n + 1));

	srand(time(NULL));
	for (i = 1; i <= n; i++) {
		*(L + i) = (rand() % 1000000) + 1;
	}
	if (n < MAX) {
		printf("리스트:");
		for (i = 1; i <= n; i++)
			printf(" %d", *(L + i));
		printf("\n");
	}

	buildHeap(n, L);

	for (i = 1; i <= n; i++)
		printf(" %d", L[i]);
	printf("\n");

	for (i = 0; i < 3; i++) {
		printf("순위: ");
		scanf("%d", &k);
		e = findKthSmallest(L, n, k);
		printf("원소: %d\n", e);
	}
}