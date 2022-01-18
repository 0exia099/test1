#include <stdio.h>
//@file : PermutationMain.cpp
//@date : 2021/09/19
//@author : 21812076 심상혁
//순열을 구하는 알고리즘 구현 후 { "GO", "BOY", "GIRL", "GIRLS" }를 순열 알고리즘을 호출하여 출력

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))//perm함수에 사용할 스왑 매크로

void perm(char* list, int i, int n);//char배열에서 i번째부터 n까지의 순열을 출력하는 함수perm 선언

int main() {

	int i, j, k;
	char list[][10] = { "GO", "BOY", "GIRL", "GIRLS", NULL };//list[]의 마지막을 알리기위한 NULL

	for (i = 0; list[i][0] != NULL; i++) {//list[][]에서 값이 저장된 부분을 순열로 출력시키기위한 반복문
		for (j = 0; list[i][j] != NULL; j++)
			;//j는 list[i][]에서 값이 저장된 마지막 배열+1 (list[i][j-1]까지가 값이 저장되어있음)
		for (k = 0; k <= j; k++) {
			printf("%c", list[i][k]);
		}
		printf(" : ");

		perm(list[i], 0, j-1);
		printf("\n\n");
	}
	return 0;
}

void perm(char* list, int i, int n) {
	/*원소 n개의 순열은 제일 앞의 값을 모든 원소 n개 중 하나로 고정시키고 나머지 원소 n - 1개의 순열을 구하는것과 같다.
	이때 모든 원소가 제일 앞의 값에 올수 있으므로 원소 n-1개의 순열을 n번 구하는것과 같다.*/
	int j, temp;
	if (i == n) {//i==n인 경우 순열이 하나이므로 바로 출력
		printf("{");
		for (j = 0; j <= n; j++) {
			printf("%c", list[j]);
		}
		printf("} ");
	}
	else {//순열이 하나 이상인 경우 원소 n-1개의 순열을 구하기위해 재귀적으로 출력
		for (j = i; j <= n; j++) {
			//원소 n-i개의 순열에서 고정하는 제일 앞의 값을 n-i번 바꾸며 원소 n-(i+1)개의 순열을 구하는 함수호출
			SWAP(list[i], list[j], temp);
			perm(list, i + 1, n);
			SWAP(list[i], list[j], temp);//바꿨던 제일 앞의 값을 원래대로 초기화시킨다.
		}
	}
}
