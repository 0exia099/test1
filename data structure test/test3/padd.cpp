#include "PaddPmul.h"

//@file : padd.cpp
/*�� ���׽� ������ �� ���׽��� ���� ���׽İ� ���� ���׽��� �����Ͽ� ����ϴ� ���α׷�����
�� ���׽��� ���ϴ� �Լ�(polynomial* padd())�� ���ǵ� ����.*/

extern int error;//�����Լ��� ��������

polynomial* padd(polynomial*A,polynomial*B,polynomial*C, int* sizeC) {
	float cofficient;//A�� ����� B�� ����� ���Ѱ��� ������ ����
	int nowA = 0;//������ A���� ��Ÿ�� ����
	int nowB = 0;//������ B���� ��Ÿ�� ����
	int nowC = 0;//������ C���� ��Ÿ�� ����

	while (A[nowA].expon != -1 && B[nowB].expon != -1) {//A��B�� ������ ���� �ݺ�
		switch (COMPARE(A[nowA].expon, B[nowB].expon)) {
		case -1://A�� expon�� B�� expon���� ������
			C = attach(B[nowB].coef, B[nowB].expon, &nowC, C, sizeC);
			nowB++;
			break;
		case 0://A�� B�� ������ �������
			cofficient = A[nowA].coef + B[nowB].coef;
			if (cofficient)
				C = attach(cofficient, A[nowA].expon, &nowC, C, sizeC);
			nowA++;
			nowB++;
			break;
		case 1://A�� expon�� B�� expon���� Ŭ��
			C = attach(A[nowA].coef, A[nowA].expon, &nowC, C, sizeC);
			nowA++;
			break;
		}
		if (error != 0)//attach�Լ����� ���Ҵ� ���н� ����
			return C;
	}
	//A�� ������ �׵��� ���Ѵ�.
	if (A[nowA].expon != -1) {
		for (; A[nowA].expon != -1; nowA++) {
			C = attach(A[nowA].coef, A[nowA].expon, &nowC, C, sizeC);
			if (error != 0)
				return C;
		}
	}
	//B�� ������ �׵��� ���Ѵ�.
	if (B[nowB].expon != -1) {
		for (; B[nowB].expon != -1; nowB++) {
			C = attach(B[nowB].coef, B[nowB].expon, &nowC, C, sizeC);
			if (error != 0)
				return C;
		}
	}
	//C���׽��� �������� ��Ÿ����-1 
	C[nowC].coef = -1;
	C[nowC].expon = -1;
	return C;
}