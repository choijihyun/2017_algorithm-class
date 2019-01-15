#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int main() {
	int n, i, j, max, max_pos, tmp;
	int *p;
	scanf("%d", &n);
	p = (int*)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
		scanf("%d", p + i);

	for (i = n - 1; i >= 0; i--) {
		max = p[i];
		max_pos = i;
		for (j = 0; j < i; j++) {
			if (max < p[j]) {
				max = p[j];
				max_pos = j;
			}
		}
		tmp = p[i];
		p[i] = p[max_pos];
		p[max_pos] = tmp;
	}
	for (i = 0; i < n; i++) {
		printf(" %d", p[i]);
	}
}