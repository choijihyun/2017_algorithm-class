//������ �� ����� �𸣴ϱ� �־Ǳ��� �����ؾߵȴ�
//�׷��Ƿ� ��ü�� �����ؼ� ������ ã�°��� ȿ����
//�� ���� Ư�� ��������� �ϴ°� ���� ȿ����

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4996)

#define MAX 20

/*
void downHeap(int * L,int n) {//������
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

void downHeap(int i, int n,int *L) {
	int left=2*i;
	int right=left+1;
	int greater,tmp;

	if (left > n)return;
	greater = left;
	if (right <= n)
		if (L[right] > L[greater])
			greater = right;
	if (L[i] >= L[greater])
		return;

	tmp = L[i];
	L[i] = L[greater];
	L[greater] = tmp;
	downHeap(greater, n, L);
}

void sort_Heap(int * L,int n,int k) {
	int key,tmp;
	int i;

	for (i = 0; i < k; i++) {
		key = L[1];

		tmp = L[1];
		L[1] = L[n];
		L[n] = tmp;

		downHeap(1, n - 1, L);
	}
}

int findKthSmallest(int * L, int n, int k) {
	sort_Heap(L, n, k);
	return L[n-k+1];
}

int main() {
	int n,i,k,e;
	int *L;
	
	printf("����Ʈ ũ��:");
	scanf("%d", &n);
	L = (int *)malloc(sizeof(int)*n+1);

	srand(time(NULL));
	for (i = 1; i <= n; i++) {
		*(L + i) = (rand() % 1000000)+1;
	}
	if (n < MAX) {
		printf("����Ʈ:");
		for (i = 0; i < n; i++)
			printf(" %d", *(L + i));
		printf("\n");
	}

	downHeap(1,n,L);

	for (i = 1; i <= n; i++)
		printf("%d��° :%d\n",i, L[i]);

	for (i = 0; i < 3; i++) {
		printf("����:");
		scanf("%d", &k);
		e = findKthSmallest(L, n, k);
		printf("����:", e);
	}
}