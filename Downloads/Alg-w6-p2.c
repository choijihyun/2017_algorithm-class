#include <stdio.h>
#include <stdlib.h>

int findElement(int * p, int k, int n) {
	int l, r, mid;
	int tmp = -1;

	l = 0;
	r = n - 1;

	while (l <= r) {
		mid = (l + r) / 2;

		if (k == p[mid])
			return mid;
		else if (k < p[mid]) {
			r = mid - 1;
			tmp = mid;
		}
		else
			l = mid + 1;
	}

	if (tmp == -1)
		return n;
	else
		return tmp;
}

int main() {
	int * p;
	int n,k;

	scanf("%d %d", &n, &k);

	p = (int *)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++)
		scanf("%d", &p[i]);

	printf(" %d", findElement(p, k,n));

	free(p);

	return 0;
}
