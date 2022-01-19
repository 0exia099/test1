#include "PaddPmul.h"

//@file : printArry.cpp
/*두 다항식 생성후 두 다항식의 합인 다항식과 곱인 다항식을 생성하여 출력하는 프로그램에서
다항식을 출력하는 함수(void printArry())가 정의된 파일.*/

void printArry(polynomial* A) {//다항식 배열을 출력하는 함수.
	int j;
	printf("항 순서        계수/지수\n");
	for (j = 0; A[j].expon != -1; j++) {
		//출력의 칸을 맞추기위해 항의 갯수, 음수 양수, 한자릴수 두자릿수 세자릿수에따라 나눔
		if (j < 9) {//항의 갯수 한자릿수와 두자릿수 나눔
			if (A[j].coef < 0) {//음수와 양수 나눔
				if (A[j].coef <= -10) {//coef값이 한자릿수와 두자릿수와 세자릿수 나눔
					if (A[j].coef <= -100) {
						printf("%d번 항      %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
					}
					else
						printf("%d번 항       %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
				}
				else
					printf("%d번 항        %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
			}
			else {
				if (A[j].coef >= 10) {
					if (A[j].coef >= 100) {
						printf("%d번 항       %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
					}
					else
						printf("%d번 항        %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
				}
				else
					printf("%d번 항         %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
			}

		}
		else {
			if (A[j].coef < 0) {//위와 같음
				if (A[j].coef <= -10) {
					if (A[j].coef <= -100) {
						printf("%d번 항     %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
					}
					else
						printf("%d번 항      %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
				}
				else
					printf("%d번 항       %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
			}
			else {
				if (A[j].coef >= 10) {
					if (A[j].coef >= 100) {
						printf("%d번 항      %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
					}
					else
						printf("%d번 항       %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
				}
				else
					printf("%d번 항        %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
			}
		}
	}
}