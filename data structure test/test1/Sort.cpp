#include "Sort.h"

void sort(int list[], int n)//�������� ����
{
	int i, j, min, temp;

	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[min])
				min = j;
		SWAP(list[i], list[min], temp);
	}
}
void Rsort(int list[], int n)//�������� ����
{
	int i, j, maj, temp;

	for (i = 0; i < n - 1; i++) {
		maj = i;
		for (j = i + 1; j < n; j++)
			if (list[j] > list[maj])
				maj = j;
		SWAP(list[i], list[maj], temp);
	}
}