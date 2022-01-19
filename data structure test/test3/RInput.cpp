#include "PaddPmul.h"

//@file : RInput.cpp
/*두 다항식 생성후 두 다항식의 합인 다항식과 곱인 다항식을 생성하여 출력하는 프로그램에서
두 다항식을 랜덤으로 생성하는 함수(void RInput())가 정의된 파일.*/

//메인함수의 전역변수
extern int sizeA;
extern int sizeB;
extern int error;
extern polynomial* temp;
extern polynomial* A;
extern polynomial* B;

//다항식을 랜덤으로 생성하는 원리
//랜덤으로 1~30의 값을 그 다항식의 최대 지수값으로 설정.
//그 후 랜덤수를 두개 생성해 계수를 만든다. 첫번째 랜덤수는 계수의 양,음수를 정하는 수고 두번째 랜덤수는 계수의 값을 나타내는 수 이다.
//랜덤수를 생성해 0~2의 값을 갖게하고 그 값이 1보다 작으면 음수, 1보다 크면 양수, 1이면 0인 계수를 갖도록한다.(계수가0이라 표시되지 않는 항을 늘리기위해)
//(0인 계수가 많이 필요없으면 짝수홀수로 양수음수를 나눈다.)
//두번째 랜덤수를 생성해 계수로 만들 값을 정한다.
//위의 계수생성과정을 (최대 지수값 + 1)만큼 반복하여 최대 지수부터 지수0까지의 계수로 넣음
//계수가 0일경우 그 항은 없는것이 된다.

void RInput() {
	int i;//저장되는 항의 순서를 나타내는 값
	int j;//for문을 사용할때 쓰는 변수
	int exp = 0;//지수값
	float coe = 0.0;//계수값
	int maxexp = 0;//랜덤생성시 최대 지수값 저장하는 변수
	int random;//랜덤생성시 랜덤값을 잠시 저장하는 변수

	srand((unsigned)time(NULL));//실행시킬때 마다 다른값이 나오도록하기위한 time
	//다항식 A랜덤 생성
	i = 0;
	maxexp = rand() % 30 + 1;//최대 지수값

	for (j = 0; j <= maxexp; j++) {
		random = rand() % 3;//첫번째 랜덤수 생성
		if (random < 1) {//값이 2보다 작으면 계수는 음수
			coe = (float)((-1) * (rand() % 10001)) / 100;
			if (coe > -1.0)//0의 비중을 늘리기 위해 0.xxxx의 값도 0으로 변경
				coe = 0.0;
		}
		else if (random > 1) {//값이 2보다 크면 계수는 양수
			coe = (float)(rand() % 10001) / 100;
			if (coe < 1.0)
				coe = 0.0;
		}
		else//2인경우 계수는 0
			coe = 0.0;

		if (coe != 0.0) {//계수가 0인경우 저장하지 않음
			A[i].coef = coe;
			A[i].expon = maxexp - j;
			i++;
		}
		if (i >= (sizeA - 1)) {//배열이 다 찰경우 재할당을 통해 배열의 크기를 늘려준다.
			sizeA += 10;
			temp = A;//realloc사용으로 이전 주소값을 잃을수도 있으므로 다른 변수에 저장.
			A = (polynomial*)realloc(A, sizeof(polynomial) * sizeA);
			if (A == NULL) {//재할당 실패시 실패신호 및 종료
				A = temp;
				printf("동적할당 실패.\n");
				error++;
				return;
			}
		}
	}

	A[i].coef = -1;//c6386경고가 뜨지만 위의 realloc사용으로 i보다 배열크기가 항상크다.
	A[i].expon = -1;

	printf("다항식 A\n");//다항식을 출력함
	printArry(A);

	//**********************아래는 다항식 B생성**********************************
	//A와 같으므로 주석 생략
	i = 0;
	maxexp = rand() % 30 + 1;

	for (j = 0; j <= maxexp; j++) {
		random = rand() % 3;
		if (random < 1) {
			coe = (float)((-1) * (rand() % 10001)) / 100;
			if (coe > -1.0)
				coe = 0.0;
		}
		else if (random > 1) {
			coe = (float)(rand() % 10001) / 100;
			if (coe < 1.0)
				coe = 0.0;
		}
		else
			coe = 0.0;

		if (coe != 0.0) {
			B[i].coef = coe;
			B[i].expon = maxexp - j;
			i++;
		}
		if (i >= (sizeB - 1)) {
			sizeB += 10;
			temp = B;
			B = (polynomial*)realloc(B, sizeof(polynomial) * sizeB);
			if (B == NULL) {
				B = temp;
				printf("동적할당 실패.\n");
				error++;
				return;
			}
		}
	}

	B[i].coef = -1;//c6386경고가 뜨지만 위의 realloc사용으로 i보다 배열크기가 항상크다.
	B[i].expon = -1;

	printf("\n다항식 B\n");
	printArry(B);
}