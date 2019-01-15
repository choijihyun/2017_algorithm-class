#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int H[100];
int n = 0;

void downHeap(int i);

/*
void rBuildHeap(int i) {
if (i > n)
return;
rBuildHeap(2 * i);
rBuildHeap(2 * i + 1);
downHeap(i);
}
*/

void buildHeap() {
	int i;
	for (i = n / 2; i >= 1; i--)
		downHeap(i);
}

void downHeap(int i) {//하향이동(remove때 사용)
	int bigger, tmp;
	int left = 2 * i;
	int right = 2 * i + 1;
	int parent = 1;

	if (H[left] >= H[right])
		bigger = left;
	else
		bigger = right;
	H[1] = H[n + 1];
	while (1) {
		if (parent * 2 > n)
			break;
		if (H[parent] > H[bigger])
			break;
		else {
			tmp = H[parent];
			H[parent] = H[bigger];
			H[bigger] = tmp;
			parent = bigger;
		}
		left = 2 * parent;
		right = left + 1;
		if (H[left] >= H[right])
			bigger = left;
		else
			bigger = right;
	}
}

void printHeap() {
	int i;
	for (i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
}

int main() {
	int cnt, i;

	scanf("%d", &cnt);
	n = cnt;
	for (i = 1; i <= cnt; i++)
		scanf("%d", H + i);
	for(i=n/2;i>=1;i--)
		downHeap(i);
	printHeap();
}