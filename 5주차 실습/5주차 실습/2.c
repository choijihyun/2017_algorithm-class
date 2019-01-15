//inPlacePartition() => 하나하나 작게 정렬하는거?
//inPlaceQuickSort() => 정렬을 모아놓는 곳
//findPivotIndex()   => pivot반환하는 함수
//partition()        => 인덱스 두개 반환

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable: 4996)

typedef struct Quick {
	int a, b;
}quick;
