//@file : PaddPmul.h
/*두 다항식 생성후 두 다항식의 합인 다항식과 곱인 다항식을 생성하여 출력하는 프로그램의 헤더파일.
사용하는 헤더파일, 구조체, 매크로, 함수들의 원형 선언해 놓은 파일
*/
#ifndef _PaddPmul_//include중복 방지

#define _PaddPmul_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define COMPARE(x,y) (((x)<(y))?-1:((x)==(y))?0:1)//두 값을 비교할때 사용하는 매크로

typedef struct {//다항식을 저장하는 구조체
	float coef;
	int expon;
} polynomial;

void DInput();//직접 입력할경우 다항식A, B를 입력을 받고 입력받은 값을 출력하는 함수
void RInput();//랜덤으로 입력할경우 다항식 A,B를 랜덤으로 만들고 출력하는 함수
void printArry(polynomial* A);//다항식 배열을 출력하는 함수.

//realloc사용시 주소가 변할 수 있으므로 다항식의 주소값을 반환하도록 polynomial*형태이다.
polynomial* padd(polynomial* A, polynomial* B, polynomial* C, int* sizeC);//다항식 A,B의 배열들을 더한 후 attach함수에 저장할 값을 주고 더한값인 C를 반환하는 함수 
polynomial* attach(float coefficient, int exponent, int* nowC, polynomial* C, int* sizeC);//지수와 계수를 다항식에 저장하고 저장된 다항식을 반환하는 함수
polynomial* pmul(polynomial* A, polynomial* B, polynomial* D);//다항식 A,B을 곱하고 곱한 값인 D를 반환 함수
polynomial* single_mul(polynomial* A, float coefficient, int exponent, polynomial* D, int* sizeD);//다항식 A와 B의 항하나를 곱하고 곱해진 다항식을 반환하는 함수
#endif