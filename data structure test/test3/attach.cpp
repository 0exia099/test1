#include "PaddPmul.h"

//@file : attach.cpp
/*�� ���׽� ������ �� ���׽��� ���� ���׽İ� ���� ���׽��� �����Ͽ� ����ϴ� ���α׷�����
���׽Ŀ� ���� �����ϴ� �Լ�(polynomial* attach())�� ���ǵ� ����.*/

//�����Լ��� ��������
extern int error;
extern polynomial* temp;

//padd�Լ��� �������� nowC�� ���� �ٲٱ����� int* nowC�� ���, sizeC�� ���� ��ȭ�ϴ°� �����ϱ� ���� int* sizeC���
polynomial* attach(float coefficient, int exponent, int* nowC, polynomial* C, int* sizeC) {
	//C�� ������
	C[*nowC].coef = coefficient;
	C[*nowC].expon = exponent;
	(*nowC)++;//���� ���� ������ ��Ÿ��������++

	if (*nowC >= (*sizeC) - 1) {//���� C�� ���� ������ nowC�� C�迭ũ�⺸�� Ŀ����� realloc���� ���Ҵ�
		(*sizeC) += 10;
		temp = C;//realloc������� ���� �ּҰ��� �������� �����Ƿ� �ٸ� ������ ����.
		C = (polynomial*)realloc(C, sizeof(polynomial) * (*sizeC));
		if (C == NULL) {//���Ҵ� ���н� ���н�ȣ �� ����
			C = temp;
			printf("�����Ҵ� ����.\n");
			error++;//���Ҵ� ���н� �����Լ����� ���� �����ϱ����� ��ȣ
			return C;
		}
	}
	return C;
}