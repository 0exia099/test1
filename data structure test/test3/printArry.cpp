#include "PaddPmul.h"

//@file : printArry.cpp
/*�� ���׽� ������ �� ���׽��� ���� ���׽İ� ���� ���׽��� �����Ͽ� ����ϴ� ���α׷�����
���׽��� ����ϴ� �Լ�(void printArry())�� ���ǵ� ����.*/

void printArry(polynomial* A) {//���׽� �迭�� ����ϴ� �Լ�.
	int j;
	printf("�� ����        ���/����\n");
	for (j = 0; A[j].expon != -1; j++) {
		//����� ĭ�� ���߱����� ���� ����, ���� ���, ���ڸ��� ���ڸ��� ���ڸ��������� ����
		if (j < 9) {//���� ���� ���ڸ����� ���ڸ��� ����
			if (A[j].coef < 0) {//������ ��� ����
				if (A[j].coef <= -10) {//coef���� ���ڸ����� ���ڸ����� ���ڸ��� ����
					if (A[j].coef <= -100) {
						printf("%d�� ��      %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
					}
					else
						printf("%d�� ��       %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
				}
				else
					printf("%d�� ��        %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
			}
			else {
				if (A[j].coef >= 10) {
					if (A[j].coef >= 100) {
						printf("%d�� ��       %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
					}
					else
						printf("%d�� ��        %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
				}
				else
					printf("%d�� ��         %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
			}

		}
		else {
			if (A[j].coef < 0) {//���� ����
				if (A[j].coef <= -10) {
					if (A[j].coef <= -100) {
						printf("%d�� ��     %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
					}
					else
						printf("%d�� ��      %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
				}
				else
					printf("%d�� ��       %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
			}
			else {
				if (A[j].coef >= 10) {
					if (A[j].coef >= 100) {
						printf("%d�� ��      %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
					}
					else
						printf("%d�� ��       %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
				}
				else
					printf("%d�� ��        %.2f/%d\n", j + 1, A[j].coef, A[j].expon);
			}
		}
	}
}