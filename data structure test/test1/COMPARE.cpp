#include "COMPARE.h"

int COMPARE(int x, int y)//������0, x�� ũ�� 1, y�� ũ��-1 ��ȯ
{
	if (x < y) return -1;
	else if (x == y) return 0;
	else return 1;
}