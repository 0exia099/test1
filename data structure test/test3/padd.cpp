#include "PaddPmul.h"

//@file : padd.cpp
/*두 다항식 생성후 두 다항식의 합인 다항식과 곱인 다항식을 생성하여 출력하는 프로그램에서
두 다항식을 더하는 함수(polynomial* padd())가 정의된 파일.*/

extern int error;//메인함수의 전역변수

polynomial* padd(polynomial*A,polynomial*B,polynomial*C, int* sizeC) {
	float cofficient;//A의 계수와 B의 계수를 더한값을 저장할 변수
	int nowA = 0;//현재의 A항을 나타낼 변수
	int nowB = 0;//현재의 B항을 나타낼 변수
	int nowC = 0;//현재의 C항을 나타낼 변수

	while (A[nowA].expon != -1 && B[nowB].expon != -1) {//A나B가 끝날때 까지 반복
		switch (COMPARE(A[nowA].expon, B[nowB].expon)) {
		case -1://A의 expon이 B의 expon보다 작을때
			C = attach(B[nowB].coef, B[nowB].expon, &nowC, C, sizeC);
			nowB++;
			break;
		case 0://A와 B의 지수가 같은경우
			cofficient = A[nowA].coef + B[nowB].coef;
			if (cofficient)
				C = attach(cofficient, A[nowA].expon, &nowC, C, sizeC);
			nowA++;
			nowB++;
			break;
		case 1://A의 expon이 B의 expon보다 클때
			C = attach(A[nowA].coef, A[nowA].expon, &nowC, C, sizeC);
			nowA++;
			break;
		}
		if (error != 0)//attach함수에서 재할당 실패시 종료
			return C;
	}
	//A의 나머지 항들을 더한다.
	if (A[nowA].expon != -1) {
		for (; A[nowA].expon != -1; nowA++) {
			C = attach(A[nowA].coef, A[nowA].expon, &nowC, C, sizeC);
			if (error != 0)
				return C;
		}
	}
	//B의 나머지 항들을 더한다.
	if (B[nowB].expon != -1) {
		for (; B[nowB].expon != -1; nowB++) {
			C = attach(B[nowB].coef, B[nowB].expon, &nowC, C, sizeC);
			if (error != 0)
				return C;
		}
	}
	//C다항식의 마지막을 나타내는-1 
	C[nowC].coef = -1;
	C[nowC].expon = -1;
	return C;
}