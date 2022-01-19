#include "PaddPmul.h"

//@file : single_mul.cpp
/*�� ���׽� ������ �� ���׽��� ���� ���׽İ� ���� ���׽��� �����Ͽ� ����ϴ� ���α׷�����
���׽�A�� ���׽�B�� �ϳ��� ���� ���Ͽ� ���׽�D�� �����ϴ� �Լ�(polynomial* single_mul())�� ���ǵ� ����.*/

extern int error;//�����Լ��� ��������

polynomial* single_mul(polynomial* A, float coefficient, int exponent, polynomial* D, int* sizeD) {
	float coe;//������� ���� ������ ����
	int exp;//�������� ���� ������ ����
	int i;
	int nowD = 0;//D�� ���� ���� ��Ÿ���� ����
	for (i = 0; A[i].expon != -1; i++) {
		coe = A[i].coef * coefficient;//����� ���Ѵ�.
		exp = A[i].expon + exponent;//������ ���Ѵ�.
		if (coe == 0) {//��� ���� 0�ΰ�� �׾��°������� ����
			return D;
		}
		D = attach(coe, exp, &nowD, D, sizeD);
		if (error != 0)//attach�Լ����� ���Ҵ� ���н� ����
			return D;
		if (A[i + 1].expon == -1) {
			D = attach(-1, -1, &nowD, D, sizeD);//D�� ��������-1-1����
			if (error != 0)//attach�Լ����� ���Ҵ� ���н� ����
				return D;
		}
	}
	return D;
}