#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#pragma warning(disable:4996)

int main() {
	int n,i;
	int max, tmp, max_pos,j;
	int *A, *B;
	float Ainterval, Binterval;
	LARGE_INTEGER AFrequency, BFrequency;
	LARGE_INTEGER ABeginTime, BBeginTime;
	LARGE_INTEGER AEndTime, BEndTime;


	scanf("%d", &n);
	A = (int*)malloc(sizeof(int)*n);
	B = (int*)malloc(sizeof(int)*n);
	srand(time(NULL));
	for (i = 0; i < n; i++) {
		A[i] = rand();
		B[i] = rand();
	}

	QueryPerformanceFrequency(&AFrequency);
	QueryPerformanceCounter(&ABeginTime);
	for (i = n - 1; i >= 0; i--) {
		max = A[i];
		max_pos = i;
		for (j = 0; j < i; j++) {
			if (max < A[j]) {
				max = A[j];
				max_pos = j;
			}
		}
		tmp = A[i];
		A[i] = A[max_pos];
		A[max_pos] = tmp;
	}
	QueryPerformanceCounter(&AEndTime);

	QueryPerformanceFrequency(&BFrequency);
	QueryPerformanceCounter(&BBeginTime);
	for (i = 1; i < n; i++) {
		tmp = B[i];
		j = i - 1;
		while (j >= 0 && B[j] > tmp) {
			B[j + 1] = B[j];
			j -= 1;
		}
		B[j + 1] = tmp;
	}
	QueryPerformanceCounter(&BEndTime);

	Ainterval = (float)(AEndTime.QuadPart - ABeginTime.QuadPart) / AFrequency.QuadPart;
	Binterval = (float)(BEndTime.QuadPart - BBeginTime.QuadPart) / BFrequency.QuadPart;
	printf("%lf\n", Ainterval);
	printf("%lf\n", Binterval);
}