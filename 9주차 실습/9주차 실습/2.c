#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

void insertItem(int*h,int k,int m) {
	int v, i, b;
	i = 0;
	v = k%m;
	while (i < m) {
		b = getNextBucket(v, i, m);
		if (isEmpty(h[b])){
			h[b] = k;
			printf("%d\n", b);
			return;
		}
		else {
			printf("C");
			i++;
		}
	}
	printf("\n");
}

void findElement(int *h,int k,int m) {
	int v,i,b;
	i = 0;
	v = k%m;
	while (i < m) {
		b = getNextBucket(v, i, m);
		if (isEmpty(h[b]))
			return 0;
		else if (k == h[b]) {
			printf("%d\n", b);
			return;
		}
		else {
			i++;
		}
	}
	printf("-1\n");
}

int isEmpty(int *p) {
	if (*p == 0)
		return 1;
	else
		return 0;
}

int getNextBucket(int v,int i,int m) {
	return (v + i) % m;
}

int main() {
	int m,n, i,cnt=0,num;
	int *p;
	char ch;
	scanf("%d %d", &m, &n);
	p = (int*)malloc(sizeof(int)*m);
	for (i = 0; i < m; i++)
		*(p + i) = 0 ;
	while (1) {
		scanf("%c",&ch);
		if (ch == 'i') {
			if (cnt >= n)continue;
			scanf("%d", &num);
			insertItem(p, num, m);
			cnt++;
		}
		else if (ch == 's') {
			scanf("%d", &num);
			findElement(p, num, m);
		}
		else if (ch == 'e')
			return 0;
	}
}