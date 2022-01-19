#define _CRT_SECURE_NO_WARNINGS//scanf���������
#pragma warning(disable : 6031)

//@file : main.cpp
/*�� ���׽� ������ �� ���׽��� ���� ���׽İ� ���� ���׽��� �����Ͽ� ����ϴ� ���α׷��� main�Լ�.
�̸� ���� ��6���� ���׽��� �����Ҵ����� ���������� ������ �� 6���� �迭ũ�⸦ ������ ��������
���������� ������. realloc���� ������ �˷��ִ� ������ ���������� ������.
�� ���׽��� �Է¹����� �������� �������� �Է¹޴� �ڵ带 ������.*/

#include "PaddPmul.h"

int sizeA = 10;//���׽� A�� �迭 ũ��
int sizeB = 10;//���׽� B�� �迭 ũ��
int sizeC = 10;//���׽� C�� �迭 ũ��
int sizeD = 10;//���׽� D�� �迭 ũ��
int sizeE = 10;//���׽� E�� �迭 ũ��
int sizeF = 10;//���׽� F�� �迭 ũ��
int error = 0;//DInput, RInput, attach�Լ����� ���Ҵ� ���н� ���и� �˷��ִ� ��ȣ�� ����� ����

polynomial* A = (polynomial*)calloc(sizeA, sizeof(polynomial));//���׽� �����Ҵ�
polynomial* B = (polynomial*)calloc(sizeB, sizeof(polynomial));
polynomial* C = (polynomial*)calloc(sizeC, sizeof(polynomial));//���ϱ� �� ���׽�
polynomial* D = (polynomial*)calloc(sizeD, sizeof(polynomial));//���ϱ� �� ���׽�
polynomial* E = (polynomial*)calloc(sizeE, sizeof(polynomial));//������ ��꿡�� ���� ���׽�
polynomial* F = (polynomial*)calloc(sizeF, sizeof(polynomial));//������ ��꿡�� ���� ���׽�

polynomial* temp;//�����Ҵ� ���Ҵ�� �޸𸮰��� �������� �ּҰ� �ٲ�� �����ּҸ� ��ȯ�ϱ� ���� ���� �ּҸ� ������ ���� ����

int main() {
	int num;//���׽� ������ �Է¹����� �������� ������ �Է¹޴� ����

	//�����Ҵ��� ����� �Ǿ����� Ȯ��
	if (A == NULL) {//�����Ҵ� ���н� ���� �� ����
		printf("�����Ҵ� ����.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}
	if (B == NULL) {
		printf("�����Ҵ� ����.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}
	if (C == NULL) {
		printf("�����Ҵ� ����.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}
	if (D == NULL) {
		printf("�����Ҵ� ����.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}
	if (E == NULL) {
		printf("�����Ҵ� ����.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}
	if (F == NULL) {
		printf("�����Ҵ� ����.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}

	//���׽��� ���� �Է����� �������� ������ ���ù޽��ϴ�.
	while (true) {
		printf("���׽��� 2�� �����մϴ�.\n���� �Է��Ͻ÷��� 1, �������� ����÷��� 2�� �Է��� �ּ���.\n(���� ������ ������ 1~30, ����� -100 ~ 100)\n");
		scanf("%d", &num);
		if (num == 1 || num == 2)//���ü��ִ� ���� 1, 2�̿ܿ��� �Է¹��� �ʵ��� ����ó��
			break;
		else {
			while (getchar() != '\n') {}//���ۿ� ����� �� �����
			printf("�ٽ� �Է��� �ּ���.\n");
		}
	}

	if (num == 1) {//���� �Է��� ���
		DInput();//�����Է¹޴� �Լ�
		if (error != 0) {//DInput�Լ����� ���Ҵ� ���н� �����Ҵ� ���� �� ����
			free(A);
			free(B);
			free(C);
			free(D);
			free(E);
			free(F);
			return 0;
		}
	}
	else {//�������� �Է��Ұ��
		RInput();//�������� �����ϴ� �Լ�
		if (error != 0) {//RInput�Լ����� ���Ҵ� ���н� �����Ҵ� ���� �� ����
			free(A);
			free(B);
			free(C);
			free(D);
			free(E);
			free(F);
			return 0;
		}
	}

	printf("\n�� ���׽�\n");//�ٽ��ѹ� �ΰ��� A,B���׽� ����Ͽ� �� ���׽��� Ȯ���� �� �ֵ��� �Ѵ�.
	printf("------------------------\n");
	printf("���׽� A\n");
	printArry(A);
	printf("------------------------\n");

	printf("\n");
	printf("------------------------\n");
	printf("���׽� B\n");
	printArry(B);
	printf("------------------------\n");

	printf("�ƹ��� Ű�� ������ �� ���׽��� ���� ��� �˴ϴ�.\n");
	system("pause");//�� ���׽��� Ȯ���� �� �ֵ��� �Ͻ�����

	printf("\n�� ���׽��� ��.\n");

	C = padd(A, B, C, &sizeC);//�� ���׽��� ���ϴ� �Լ�

	if (error != 0) {//attach�Լ����� ���Ҵ� ���н� �����Ҵ� ���� �� ����
		C = temp;
		printf("�����Ҵ� ����.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}	
	//������ ���׽� ���
	printf("------------------------\n");
	printf("���׽� C\n");
	printArry(C);
	printf("------------------------\n");

	printf("�ƹ��� Ű�� ������ �� ���׽��� ���� ��� �˴ϴ�.\n");
	system("pause");//���׽��� ���� Ȯ���� �� �ֵ��� �Ͻ�����

	printf("\n�� ���׽��� ��.\n");//�� ���׽��� ���� ����ϴ� �ȳ�
	//�� ���׽��� ���ϴ� �Լ�
	D = pmul(A, B, D);
	if (error != 0) {//attach�Լ����� ���Ҵ� ���н� �����Ҵ� ���� �� ����
		D = temp;
		printf("�����Ҵ� ����.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}
	printf("------------------------\n");//������ ���׽� ���
	printf("���׽� D\n");
	printArry(D);
	printf("------------------------\n");


	//�����Ҵ� ���� �� ����
	free(A);
	free(B);
	free(C);
	free(D);
	free(E);
	free(F);
	printf("�����մϴ�.\n");//���� �޽���
	//��������(exe)����� �ٷ� ����ǹǷ� �Ͻ������߰� 
	system("pause");
	return 0;
}