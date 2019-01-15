#include <stdio.h>
#include <stdlib.h>

int main()
{
	char answer;
	int mid;
	int count = 0;
	int result;
	int A, B, N;

	scanf("%d %d %d\n", &A, &B, &N);

	while (N>0) {
		N--;
		scanf("%c", &answer);

		mid = (A + B) / 2;
		count++;

		if (answer == 'N')
			B = mid;
		else if (answer == 'Y')
			A = mid + 1;

		if (A == B) {
			result = A;
			break;
		}
	}

	printf("%d %d", count, result);

	return 0;
}
