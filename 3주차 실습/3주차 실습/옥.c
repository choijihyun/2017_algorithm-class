#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable: 4996)

int H[100];
int n = 0;
void insertItem(int k);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();

void insertItem(int key)
{
	n++;
	H[n] = key;
	upHeap(n);
	printf("삽입완료\n");
}

int removeMax()
{
	int key;

	key = H[1];
	H[1] = H[n];
	n--;
	downHeap(1);
	printf("%d\n", key);

	return key;
}

void upHeap(int i) {//상향이동(insert때 사용) O(log n)
	int parent = i / 2;
	int tmp, bigger;

	if ((parent >= 1) && (H[i] > H[parent]))
		bigger = i;
	else
		bigger = parent;

	if (bigger != parent) {
		tmp = H[parent];
		H[parent] = H[i];
		H[i] = tmp;
		upHeap(parent);
	}
}

void downHeap(int i)
{
	int tmp, larger;

	if (n < i * 2 && n < (i * 2) + 1)
		return;

	larger = i * 2;
	if (n >= (i * 2) + 1) //오른쪽자식이 존재하면
	{
		if (H[i * 2 + 1] > H[larger])
			larger = (i * 2) + 1;
	}
	if (H[i] > H[larger])
		return;
	else {
		tmp = H[i];
		H[i] = H[larger];
		H[larger] = tmp;

		downHeap(larger);
	}
}

void printHeap()
{
	int i;
	for (i = 1; i <= n; i++)
		printf(" %d", H[i]);
	printf("\n");
}

int main() {
	char func;
	int num;

	while (1) {
		scanf("%c", &func);
		switch (func) {
		case 'i':scanf("%d", &num); getchar();
			insertItem(num); break;
		case 'd':getchar();
			removeMax();
			break;
		case 'p':getchar();
			printHeap();
			break;
		case 'q': return 0;
		}
	}
}