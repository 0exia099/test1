#include "Binsearch.h"

int search(int& n, int list[], int listnum[], int& count, int& step) {
	int i;
	int num = 0;
	printf("\n배열크기가 %d일때 검색\n", n);
	for (int j = 0; j < 11; j++) {
		if (!binsearch(list, listnum[j], 0, n - 1, count)) {
			printf("%d가 리스트에 존재하지 않습니다.\n", listnum[j]);
			num++;
		}
	}
	if (num != 0) {
		printf("찾지못한 수가 있으므로 해당 배열의 크기를 재실행 합니다.\n");
		n -= step;
		return n + step;
	}
	else {//정확한 검색알고리즘 성능평가를 위해 1부터n까지 순차적으로 입력된 list를 만들고 검색.
		printf("\n1부터n까지 순차적으로 입력된 list\n");
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