//배열로

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
	int i, j;//while로 순회할 애들
	int a, b;//위지 외워둘 애들
	int tmp_loc;

	i = l;
	j = r - 1;
	a = l;
	b = r;

	swap_Node(pnum, j, k);//기준원소를 맨 오른쪽에 위치시킨다.

	while (i <= j) {
		while (i <= j && pnum[i] <= pnum[k]) {
			if (pnum[i] == pnum[k]) {
				swap_Node(pnum, i, a);
				a++;
			}//왼쪽에 a개 만큼 중복 원소 배치해 놓음
			i++;
		}//i의값이 k보다 크면 멈춤
		while (i <= j&&pnum[j] >= pnum[k]) {
			if (pnum[j] == pnum[k]) {
				b--;
				swap_Node(pnum, j, b);
			}//오른쪽에 b개 만큼 중복 원소 배치해 놓음
			j--;
		}//j의값이 p보다 작으면 멈춤
		if (i < j)
			swap_Node(pnum, i, j);//그러니까 두개를 바꿔줘야지 오름차순!
	}
	
	//같은거 왼쪽에 다 몰아놨으니까 가운데로 다시 돌려놓기!
	tmp_loc = i - 1;//여기서 i-1 의미하는게 뭘까->j위치
	while (a > i) {//a랑i가 어디에있지,,,
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