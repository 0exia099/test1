//#pragma once
#ifndef _BINSEARCH_
#define _BINSEARCH_
#include <stdio.h>

bool binsearch(int list[], int searchnum, int left, int right, int& count);//이진검색 후 찾으면 1반환, 못찾으면 0반환하는 함수
int search(int& n, int list[], int listnum[], int& count, int& step);//binsearch함수 실행 후 찾는 수가 없으면 찾는수를 강제로 넣게하는 신호리턴
//찾는 수가 모두 있으면 1부터n까지 수를 넣은 배열에서 이진검색실행하고 0리턴 하는 함수
#endif