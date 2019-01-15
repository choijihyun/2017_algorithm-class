#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

int isEmpty(int p) {
	if (p == 0)
		return 1;
	else
		return 0;
}

int insertItem(int *A, int m, int x, int q) {
	int v, v2;
	int cnt = 0;
	v = x%m;
	v2 = q - (x%q);
	if (isEmpty(A[v])) {
		A[v] = x;
		return v;
	}
	else {
		while (A[v] != 0) {
			if (cnt == m)
				return;
			v = (v + v2) % m;
			printf("C");
		}
		A[v] = x;
		return v;
	}
}

void findElement(int *A, int m, int x) {
	int i;
	for (i = 0; i<m; i++) {
		if (A[i] == x) {
			printf("%d %d\n", i, x);
			return;
		}
	}
	printf("-1\n");
}

void print(int *A, int m) {
	int i;
	for (i = 0; i<m; i++)
		printf(" %d", A[i]);
	printf("\n");
}

void initBucket(int *A, int m) {
	int i;
	for (i = 0; i<m; i++)
		A[i] = 0;
}

int main() {
	int M, N, *A, q, x;
	int cnt = 0;
	int i;
	char ch;

	scanf("%d%d%d", &M, &N, &q);
	A = (int*)malloc(sizeof(int)*M);

	initBucket(A, M);
	while (1) {
		getchar();
		scanf("%c", &ch);

		if (ch == 'i') {
			scanf("%d", &x);
			if (cnt == N) continue;
			printf("%d\n", insertItem(A, M, x, q));
			cnt++;
		}
		else if (ch == 's') {
			scanf("%d", &x);
			findElement(A, M, x);
		}
		else if (ch == 'p') {
			print(A, M);
		}
		else if (ch == 'e') {
			print(A, M);
			return 0;
		}
	}
}