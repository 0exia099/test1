#include "Is_sorted.h"

bool is_sorted(int* list, int n) {
	for (int i = 0; i < n - 1; i++) {//n번째는 배열에 다음번째가 없으므로 n-1
		if (list[i] > list[i + 1]) {
			return 0;
		}
	}
	return 1;
}