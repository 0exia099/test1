//@file : PaddPmul.h
/*�� ���׽� ������ �� ���׽��� ���� ���׽İ� ���� ���׽��� �����Ͽ� ����ϴ� ���α׷��� �������.
����ϴ� �������, ����ü, ��ũ��, �Լ����� ���� ������ ���� ����
*/
#ifndef _PaddPmul_//include�ߺ� ����

#define _PaddPmul_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COMPARE(x,y) (((x)<(y))?-1:((x)==(y))?0:1)//�� ���� ���Ҷ� ����ϴ� ��ũ��

typedef struct {//���׽��� �����ϴ� ����ü
	float coef;
	int expon;
} polynomial;

void DInput();//���� �Է��Ұ�� ���׽�A, B�� �Է��� �ް� �Է¹��� ���� ����ϴ� �Լ�
void RInput();//�������� �Է��Ұ�� ���׽� A,B�� �������� ����� ����ϴ� �Լ�
void printArry(polynomial* A);//���׽� �迭�� ����ϴ� �Լ�.

//realloc���� �ּҰ� ���� �� �����Ƿ� ���׽��� �ּҰ��� ��ȯ�ϵ��� polynomial*�����̴�.
polynomial* padd(polynomial* A, polynomial* B, polynomial* C, int* sizeC);//���׽� A,B�� �迭���� ���� �� attach�Լ��� ������ ���� �ְ� ���Ѱ��� C�� ��ȯ�ϴ� �Լ� 
polynomial* attach(float coefficient, int exponent, int* nowC, polynomial* C, int* sizeC);//������ ����� ���׽Ŀ� �����ϰ� ����� ���׽��� ��ȯ�ϴ� �Լ�
polynomial* pmul(polynomial* A, polynomial* B, polynomial* D);//���׽� A,B�� ���ϰ� ���� ���� D�� ��ȯ �Լ�
polynomial* single_mul(polynomial* A, float coefficient, int exponent, polynomial* D, int* sizeD);//���׽� A�� B�� ���ϳ��� ���ϰ� ������ ���׽��� ��ȯ�ϴ� �Լ�
#endif