#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4996)
#define MAX 20 //n�� �������� ��찡 ����������� ��Ȯ�� �����Ǿ������ʾƼ� ���߿� ��ġ�� ���ϰ� MAX�� �� ����


void arraySwap(int * L, int n1, int n2) {
	int temp; // �ӽ÷� ���� ������ ����

	temp = L[n1];
	L[n1] = L[n2];
	L[n2] = temp;
	// A[n1]�� ���� A[n2]�� ���� swap�Ѵ�
}


void downHeap(int i, int n, int * L) {
	int left, right, smaller;

	left = i * 2;
	right = left + 1;

	if (left > n)//�ܺγ���϶�
		return ;
	smaller = left;
	if (right <= n) {
		if (L[right] < L[smaller])//smaller�� ��ġ�� �ִ� Ű���� right�� ��ġ�� �ִ� Ű������ ������ /�ּ��� 
			smaller = right;
	}
	if (L[i] <= L[smaller]) // i�� ��ġ�� �ִ� ���� smaller�� ��ġ�� �ִ� ������ �۰ų� ���ƾ߸� ���� / �ּ���
		return ;
	arraySwap(L, i, smaller);
	downHeap(smaller,n,L);//����Լ�
}

void buildHeap(int n,int *L) {//������
	int i;
	for (i = n / 2; i >= 1; i--)
		downHeap(i,n,L);
}

int findKthSmallest(int * L,int n, int k) {
	int i, e;
	int last = n;//����Ʈ�� ũ�⸦ ����

	buildHeap(n,L);

	for (i = 0; i < k; i++) {
		e = L[1];//�ּڰ� ����
		arraySwap(L, 1, last);
		last--;//����Ʈũ�� �ϳ� ����
		downHeap(1,last,L);
	}
	
	return e;//k���� ����
}

int main() {
	int n, i, *L, k , e;

	printf("����Ʈ ũ��:");
	scanf("%d", &n);
	L = (int *)malloc(sizeof(int)*(n + 1));

	srand(time(NULL));
	for (i = 1; i <= n; i++) {
		*(L + i) = (rand()*rand()) % 1000000 + 1;// rand()�� ������ 0~32767�������̴�. ���� 1~1000000������ ������ �߻���Ű�� ���� rand()*rand()�� �ؼ� ������ ������ %1000000+1�� �Ѵ�
	}
	
	if (n <= MAX) {
		printf("����Ʈ :");
		for (i = 1; i <= n; i++)
			printf(" %d", L[i]);
		printf("\n");
	}

	buildHeap(n, L);

	for (i = 0; i < 3; i++) {
		printf("����: ");
		scanf("%d", &k);
		e = findKthSmallest(L,n, k);
		printf("����: %d\n", e);
	}

	
}