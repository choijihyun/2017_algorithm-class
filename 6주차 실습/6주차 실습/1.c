//����Ž�� - ���

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

int search(int * p, int parent,int k,int n,int * key_loc) {
	int right, left;

	left = parent * 2 + 1;
	right = left + 1;

	if (left > n || parent > n)//�ܺγ���϶�
		return 0;
	
	if (p[left] == k) {
		*key_loc = left;
		return 0;
	}
	else if (p[right] == k) {
		*key_loc = right;
		return 0;
	}

	search(p, left, k, n, key_loc);
	search(p, right, k, n, key_loc);
}

int main() {
	int n,i,key,key_loc = -1;
	int *p;

	scanf("%d", &n);
	scanf("%d", &key);
	p = (int *)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++)
		scanf("%d", p + i);
	search(p, 0, key, n,&key_loc);
	printf(" %d", key_loc);
}