#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)

typedef struct Quick // 파티션에게서 중복값의 처음과 끝 위치를 받기위한 구조체
{
	int a, b; // 중복원소가 모여있는 곳의 첫과 마지막 위치값
}quick;

void inPlaceQuickSort(int * L, int l, int r);
/*
function name : inPlaceQuickSort
pre condition(전제 조건) : 함수를 호출하면서 리스트의 처음, 끝 인덱스값과 리스트를 전달받는다
function(기능) : 제자리 퀵정렬을 수행한다
*/
quick inPlacePartition(int *A, int l, int r, int k);
/*
function name : inPlacePartition
pre condition(전제 조건) : 함수를 호출하면서 리스트의 처음, 끝 인덱스값과 리스트와 기준이 될 원소 위치를 전달받는다
function(기능) : 기준값을 기준으로 파티션 작업 수행 -> 역정렬
*/
void arraySwap(int *A, int n1, int n2);
/*
function name : arraySwap
pre condition(전제 조건) : 리스트와 바꾸고자 하는 두 값의 위치 값
function(기능) :  A[n1]과 A[n2]의 값을 바꿔준다
*/

int findPivotIndex(int * A);
/*
function name : findPivotIndex
pre condition : 리스트와 
*/


int main(){
	int n,num,i;
	int * p;

	scanf("%d", &n);
	p = (int *)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++) {
		scanf("%d", p + i);
	}
	inPlaceQuickSort(p, 0, n - 1);
	for (i = 0; i < n; i++)
		printf(" %d", p[i]);
	printf("\n");
}


void inPlaceQuickSort(int * L, int l, int r) {
	int k;
	quick q;

	if (l >= r)//l이 r보다 커야지 재귀종료
		return;

	k = r; // 결정적 퀵정렬이기 때문에 기준원소는 가장 마지막에 위치한 값이다

	q = inPlacePartition(L, l, r, k); // 중복원소 가능한 파티션 호출

	inPlaceQuickSort(L, l, (q.a) - 1); // 기준값 기준으로 왼쪽 분할 퀵정렬
	inPlaceQuickSort(L, (q.b) + 1, r); // 기준값 기준으로 오른쪽 분할 퀵정렬
}
quick inPlacePartition(int *A, int l, int r, int k) {
	quick q;
	int i, j;
	int a, b;
	int temp_loc;
	int p;

	p = A[k]; // k의 위치에 있는 값이 기준값

	i = l; // i는 l을 시작점으로 한다
	j = r - 1; // j는 r-1을 시작점으로 한다

	a = l; // 중복된 원소를 배열 가장 앞부터 모아둔다
	b = r; // 중복된 원소를 배열 가장 뒤부터 모아둔다

	while (i <= j) {
		while (i <= j && A[i] <= p) { // i은 l를 시작점으로 p보다 작거나 같은값을 찾음//작은거
			if (A[i] == p) { // 같은값을 찾을 경우, 해당범위내 배열 왼쪽에 모아둠
				arraySwap(A, a, i); // 현재 i의 값과 a의 값을 바꾼다
				a++; // a가 다음 인덱스값으로 이동한다
			}
			i++;
		}

		while (i <= j && A[j] >= p) { // j은 r-1를 시작점으로 p보다 크거나 같은값을 찾음//큰거
			if (A[j] == p) { // 같은값을 찾을 경우, 해당범위내 배열 오른쪽에 모아둠
				b--;
				arraySwap(A, j, b);
			}
			j--;
		}
		if (i < j) {
			arraySwap(A, i, j); // i < j일 경우 i과 j의 값을 바꿈
		}
	}
	printf("a = %d\ti = %d\n", a, i);
	// 해당 범위내의 배열의 왼쪽과 오른쪽에 모아둔 p와 중복되는 값을 배열 중앙으로 보낸다
	temp_loc = i - 1; // a에게 i-1의 위치를 전달하기 위해 임시로 저장//중복값
	while (a > i) {
		arraySwap(A, a, temp_loc);
		a--;
		temp_loc--;
	} // a가 i보다 클 때 중복된 값을 하나씩 중앙으로 이동한다
	a = temp_loc + 1; // a는 현재 중복된 원소 모아놓은 것 의 가장 첫번째 위치를 가진다

	temp_loc = i; // a에게 i의 위치를 전달하기 위해 임시로 저장
	while (b < r + 1) {
		arraySwap(A, b, temp_loc);
		b++;
		temp_loc++;
	} // b가 r+1보다 작을 때 중복된 값을 하나씩 중앙으로 이동한다
	b = temp_loc - 1; // b는 현재 중복된 원소 모아놓은 것 의 가장 마지막 위치를 가진다

	q.a = a;
	q.b = b; // 구조체 이용해서 a,b값 전달 

	return q;
}
void arraySwap(int * A, int n1, int n2) {
	int temp; // 임시로 값을 저장할 변수

	temp = A[n1];
	A[n1] = A[n2];
	A[n2] = temp;
	// A[n1]의 값과 A[n2]의 값을 swap한다
}