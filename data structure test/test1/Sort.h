//#pragma once
#ifndef _SORT_
#define _SORT_
#include <stdio.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))//스왑 매크로

void sort(int[], int);//정렬함수
void Rsort(int[], int);//내림차순 정렬함수
#endif