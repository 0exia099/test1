#include "Binsearch.h"
#include "COMPARE.h"

bool binsearch(int list[], int searchnum, int left, int right, int& count)
{ 
	int middle;
	count = 0;
	while (left <= right) {
		count++;
		middle = (left + right) / 2;
		switch (COMPARE(list[middle], searchnum))
		{
		case -1: left = middle + 1;
			break;
		case  0: printf("%d : count = %d\n", searchnum, count); return 1;//찾으면 카운터 출력 후 1리턴
		case  1: right = middle - 1;
		}
	}
	return 0;//못찾으면 0리턴
}
