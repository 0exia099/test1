#include "PaddPmul.h"

//@file : single_mul.cpp
/*두 다항식 생성후 두 다항식의 합인 다항식과 곱인 다항식을 생성하여 출력하는 프로그램에서
다항식A와 다항식B의 하나의 항을 곱하여 다항식D에 저장하는 함수(polynomial* single_mul())가 정의된 파일.*/

extern int error;//메인함수의 전역변수

polynomial* single_mul(polynomial* A, float coefficient, int exponent, polynomial* D, int* sizeD) {
	float coe;//계수들의 곱을 저장할 변수
	int exp;//지수들의 합을 저장할 변수
	int i;
	int nowD = 0;//D의 현재 항을 나타내는 변수
	for (i = 0; A[i].expon != -1; i++) {
		coe = A[i].coef * coefficient;//계수는 곱한다.
		exp = A[i].expon + exponent;//지수는 더한다.
		if (coe == 0) {//계수 곱이 0인경우 항없는것임으로 리턴
			return D;
		}
		D = attach(coe, exp, &nowD, D, sizeD);
		if (error != 0)//attach함수에서 재할당 실패시 종료
			return D;
		if (A[i + 1].expon == -1) {
			D = attach(-1, -1, &nowD, D, sizeD);//D의 마지막에-1-1저장
			if (error != 0)//attach함수에서 재할당 실패시 종료
				return D;
		}
	}
	return D;
}