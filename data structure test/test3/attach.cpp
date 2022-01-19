#include "PaddPmul.h"

//@file : attach.cpp
/*두 다항식 생성후 두 다항식의 합인 다항식과 곱인 다항식을 생성하여 출력하는 프로그램에서
다항식에 값을 저장하는 함수(polynomial* attach())가 정의된 파일.*/

//메인함수의 전역변수
extern int error;
extern polynomial* temp;

//padd함수의 지역변수 nowC의 값을 바꾸기위해 int* nowC를 사용, sizeC의 값도 변화하는걸 저장하기 위해 int* sizeC사용
polynomial* attach(float coefficient, int exponent, int* nowC, polynomial* C, int* sizeC) {
	//C에 값저장
	C[*nowC].coef = coefficient;
	C[*nowC].expon = exponent;
	(*nowC)++;//다음 항의 순서를 나타내기위해++

	if (*nowC >= (*sizeC) - 1) {//현재 C의 항의 순서인 nowC가 C배열크기보다 커질경우 realloc으로 재할당
		(*sizeC) += 10;
		temp = C;//realloc사용으로 이전 주소값을 잃을수도 있으므로 다른 변수에 저장.
		C = (polynomial*)realloc(C, sizeof(polynomial) * (*sizeC));
		if (C == NULL) {//재할당 실패시 실패신호 및 종료
			C = temp;
			printf("동적할당 실패.\n");
			error++;//재할당 실패시 메인함수에서 전부 해제하기위한 신호
			return C;
		}
	}
	return C;
}