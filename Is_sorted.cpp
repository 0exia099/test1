#include "Is_sorted.h"

bool is_sorted(int* list, int n) {
	for (int i = 0; i < n - 1; i++) {//n��°�� �迭�� ������°�� �����Ƿ� n-1
		if (list[i] > list[i + 1]) {
			return 0;
		}
	}
	return 1;
}