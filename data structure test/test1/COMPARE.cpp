#include "COMPARE.h"

int COMPARE(int x, int y)//같으면0, x가 크면 1, y가 크면-1 반환
{
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1;
}