#include <stdio.h>
#include <stdlib.h>

int * p;
int N, K;

int rFE(int k, int l, int r) {
	int mid;
	int result;

	if (l > r)
		return -1;

	mid = (l + r) / 2;

	if (k == p[mid])
		return mid;
	else if (k < p[mid])
		return rFE(k, l, mid - 1);
	else {
		result = rFE(k, mid + 1, r);
		if (result == -1)
			return mid;
		else
			return result;
	}
}

int findElement() {
	return rFE(K, 0, N - 1);
}

int main()
{
	scanf("%d %d", &N, &K);

	p = (int *)malloc(sizeof(int)*N);

	for (int i = 0; i < N; i++)
		scanf("%d", &p[i]);

	printf(" %d", findElement());

	free(p);

	return 0;
}
