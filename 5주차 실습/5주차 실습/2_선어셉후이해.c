//�迭��

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

typedef struct List{
	int a, b;
}List;

void swap_Node(int * pnum, int i,int j) {
	int tmp;
	
	tmp = pnum[i];
	pnum[i] = pnum[j];
	pnum[j] = tmp;
}

List * partition(int * pnum, int l, int r, int k) {
	List * q;
	int i, j;//while�� ��ȸ�� �ֵ�
	int a, b;//���� �ܿ��� �ֵ�
	int tmp_loc;

	i = l;
	j = r - 1;
	a = l;
	b = r;

	swap_Node(pnum, j, k);//���ؿ��Ҹ� �� �����ʿ� ��ġ��Ų��.

	while (i <= j) {
		while (i <= j && pnum[i] <= pnum[k]) {
			if (pnum[i] == pnum[k]) {
				swap_Node(pnum, i, a);
				a++;
			}//���ʿ� a�� ��ŭ �ߺ� ���� ��ġ�� ����
			i++;
		}//i�ǰ��� k���� ũ�� ����
		while (i <= j&&pnum[j] >= pnum[k]) {
			if (pnum[j] == pnum[k]) {
				b--;
				swap_Node(pnum, j, b);
			}//�����ʿ� b�� ��ŭ �ߺ� ���� ��ġ�� ����
			j--;
		}//j�ǰ��� p���� ������ ����
		if (i < j)
			swap_Node(pnum, i, j);//�׷��ϱ� �ΰ��� �ٲ������ ��������!
	}
	
	//������ ���ʿ� �� ���Ƴ����ϱ� ����� �ٽ� ��������!
	tmp_loc = i - 1;//���⼭ i-1 �ǹ��ϴ°� ����->j��ġ
	while (a > i) {//a��i�� �������,,,
		swap_Node(pnum, tmp_loc, a);
		tmp_loc--;
		a--;
	}
	a = tmp_loc + 1;

	q->a = a;
	q->b = b;
	return q;
}

int main() {
	int num, i, data;
	int * pnum;
	int p, r, l;

	scanf("%d", &num);
	pnum = (int *)malloc(sizeof(int)*num);
	for (i = 0; i < num; i++) 
		scanf("%d", pnum+i);

	p = pnum[num - 1];
	l = 0;
	r = num-1;

	partition(pnum, l, r, p);
}