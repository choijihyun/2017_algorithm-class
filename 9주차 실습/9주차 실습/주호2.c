#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

int isEmpty(int p) {
	if (p == 0)
		return 1;
	else
		return 0;
}

void initBucket(int * A, int m) {
	int i;
	for (i = 0; i<m; i++)
		A[i] = 0;
}
int insertItem(int * A, int m, int x) {
	int v;
	int cnt=1;
	v = x%m;
	if (isEmpty(A[v])) {
		A[v] = x;
		return v;
	}
	else {
		while (A[v] != 0) {
			if (cnt == m + 1)
				return;
			printf("C");
			v = (v + (cnt)) % m;
		}
		*(A+v) = x;
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
int main() {
	int m, n, *A, id, x;
	int cnt = 0;
	int i;
	char ch;

	scanf("%d %d", &m, &n);
	A = (int*)malloc(sizeof(int)*m);
	initBucket(A, m);
	while (1) {
		getchar();
		scanf("%c", &ch);
		switch (ch) {
		case 'i':
			scanf("%d", &x);
			if (cnt == n) break;
			printf("%d\n", insertItem(A,m, x));
			cnt++;
			break;
		case 's':
			scanf("%d", &x);
			findElement(A, m, x);
			break;
		case 'e': return;
		}
	}
}