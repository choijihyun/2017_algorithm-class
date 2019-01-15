#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable :4996)



int main() {
	int n, i, k, e;
	int *L;

	printf("리스트 크기:");
	scanf("%d", &n);
	L = (int *)malloc(sizeof(int)*n);

	srand(time(NULL));
	for (i = 0; i < n; i++) {
		*(L + i) = (rand() % 1000000) + 1;
	}
}