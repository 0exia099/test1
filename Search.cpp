#include "Binsearch.h"

int search(int& n, int list[], int listnum[], int& count, int& step) {
	int i;
	int num = 0;
	printf("\n�迭ũ�Ⱑ %d�϶� �˻�\n", n);
	for (int j = 0; j < 11; j++) {
		if (!binsearch(list, listnum[j], 0, n - 1, count)) {
			printf("%d�� ����Ʈ�� �������� �ʽ��ϴ�.\n", listnum[j]);
			num++;
		}
	}
	if (num != 0) {
		printf("ã������ ���� �����Ƿ� �ش� �迭�� ũ�⸦ ����� �մϴ�.\n");
		n -= step;
		return n + step;
	}
	else {//��Ȯ�� �˻��˰��� �����򰡸� ���� 1����n���� ���������� �Էµ� list�� ����� �˻�.
		printf("\n1����n���� ���������� �Էµ� list\n");
		for (i = 0; i < n; i++) {
			list[i] = i + 1;
		}
		for (int j = 0; j < 11; j++) {
			binsearch(list, listnum[j], 0, n - 1, count);
		}
		printf("\n");
		return 0;
	}
}