#include "PaddPmul.h"

//@file : pmul.cpp
/*�� ���׽� ������ �� ���׽��� ���� ���׽İ� ���� ���׽��� �����Ͽ� ����ϴ� ���α׷�����
�� ���׽��� ���ϴ� �Լ�(polynomial* pmul())�� ���ǵ� ����.*/

//�����Լ��� ��������
extern int error;
extern int sizeD;
extern int sizeF;
extern int sizeE;
extern polynomial* E;
extern polynomial* F;

polynomial* pmul(polynomial* A, polynomial* B, polynomial* D) {
	int i, j;
	int nowF = 0;//���� F�� ���� ��Ÿ���� ����
	F[0].coef = -1;//ó�� F�� �ƹ��� ���� ������ �ʴ´�
	F[0].expon = -1;

	for (i = 0; B[i].expon != -1; i++) {
		E = single_mul(A, B[i].coef, B[i].expon, E, &sizeE);//E�� ���׽�A�� B���ϳ��� �� ����
		if (error != 0)//attach�Լ����� ���Ҵ� ���н� ����
			return D;

		D = padd(F, E, D, &sizeD);//���׽� E��F�� �� D�� ����.
		if (error != 0)//attach�Լ����� ���Ҵ� ���н� ����
			return D;
		for (j = 0; D[j].expon != -1; j++) {//F�� D�� ����
			F = attach(D[j].coef, D[j].expon, &nowF, F, &sizeF);
			if (error != 0)//attach�Լ����� ���Ҵ� ���н� ����
				return D;
		}
		F = attach(-1, -1, &nowF, F, &sizeF);//F�� ��������-1-1����
		if (error != 0)//attach�Լ����� ���Ҵ� ���н� ����
			return D;
		nowF = 0;//D�� F�� ������ �Ŀ��� �ٽ� �����ϱ����� 0���� �ʱ�ȭ
	}
	return D;
}