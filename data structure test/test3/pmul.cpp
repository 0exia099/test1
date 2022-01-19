#include "PaddPmul.h"

//@file : pmul.cpp
/*두 다항식 생성후 두 다항식의 합인 다항식과 곱인 다항식을 생성하여 출력하는 프로그램에서
두 다항식을 곱하는 함수(polynomial* pmul())가 정의된 파일.*/

//메인함수의 전역변수
extern int error;
extern int sizeD;
extern int sizeF;
extern int sizeE;
extern polynomial* E;
extern polynomial* F;

polynomial* pmul(polynomial* A, polynomial* B, polynomial* D) {
	int i, j;
	int nowF = 0;//현재 F의 항을 나타내는 변수
	F[0].coef = -1;//처음 F는 아무런 항을 가지지 않는다
	F[0].expon = -1;

	for (i = 0; B[i].expon != -1; i++) {
		E = single_mul(A, B[i].coef, B[i].expon, E, &sizeE);//E에 다항식A와 B항하나의 곱 저장
		if (error != 0)//attach함수에서 재할당 실패시 종료
			return D;

		D = padd(F, E, D, &sizeD);//다항식 E와F의 합 D에 저장.
		if (error != 0)//attach함수에서 재할당 실패시 종료
			return D;
		for (j = 0; D[j].expon != -1; j++) {//F에 D를 복사
			F = attach(D[j].coef, D[j].expon, &nowF, F, &sizeF);
			if (error != 0)//attach함수에서 재할당 실패시 종료
				return D;
		}
		F = attach(-1, -1, &nowF, F, &sizeF);//F의 마지막에-1-1저장
		if (error != 0)//attach함수에서 재할당 실패시 종료
			return D;
		nowF = 0;//D를 F에 복사한 후에는 다시 복사하기위해 0으로 초기화
	}
	return D;
}