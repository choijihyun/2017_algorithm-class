#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int main() {
	int n,i,j,tmp,pos;
	int *p;
	
	scanf("%d", &n);
	p = (int *)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
		scanf("%d", p + i);
	for (i = 1; i < n; i++) {
		tmp = p[i];
		j = i - 1;
		while (j >= 0 && p[j] > tmp) {
			p[j + 1] = p[j];
			j -= 1;
		}
		p[j + 1] = tmp;
	}
	for (i = 0; i < n; i++) {
		printf(" %d", p[i]);
	}
}