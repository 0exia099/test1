#include "PaddPmul.h"

//@file : DInput.cpp
/*두 다항식 생성후 두 다항식의 합인 다항식과 곱인 다항식을 생성하여 출력하는 프로그램에서
두 다항식을 직접 입력받는 함수(void DInput())가 정의된 파일.*/

//메인함수의 전역변수
extern int sizeA;
extern int sizeB;
extern int error;
extern polynomial* temp;
extern polynomial* A;
extern polynomial* B;

void DInput() {
	int i;//입력받는 항의 순서를 나타내는 값
	int T = 1;//지수를 입력받을때 전 항의 지수값보다 크면 1을 저장해 다시 값을 입력받게하는 변수
	int exp = 0;//입력받을때 지수값
	float coe = 0.0;//입력받을때 계수값
	//다항식 A를 입력받음
	//printf("다항식 A를 입력받습니다. 지수가 큰 항부터 입력해 주십시오.\n");
	printf("***마지막 항까지 입력하셨으면 다음 계수와 지수에-1을 입력해 주십시오.***\n");
	i = 1;//몇번째 항인지 알려주는 i
	while (coe != -1.0 && exp != -1) {//계수와 지수가 -1인경우까지 입력받음
		T = 1;
		printf("%d번 항의 '계수'값을 적어주세요>>", i);
		while (scanf("%f", &coe) != 1) {//실수가 아닌경우 예외처리
			while (getchar() != '\n') {}//버퍼에 저장된 값 지우기
			printf("실수를 입력해 주십시오\n");
			printf("%d번 항의 '계수'값을 적어주세요>>", i);
		}

		if (i != 1) {//처음 항이 아닐경우 전항보다 지수가 큰경우를 입력하지 못하도록 함
			while (T == 1) {//지수의 값이 전보다 클경우 다시 입력받음
				printf("%d번 항의 '지수'값을 적어주세요>>", i);
				while (scanf("%d", &exp) != 1) {//정수가 아닌경우 예외처리
					while (getchar() != '\n') {}
					printf("정수를 입력해 주십시오\n");
					printf("%d번 항의 '지수'값을 적어주세요>>", i);
				}
				if (exp >= A[i - 2].expon) {//지수값이 전보다 크면 반복하는 신호를 준다
					T = 1;
					printf("전의 항들 보다 작은 수를 지수로 적어주세요.\n");
				}
				else T = 0;
			}
		}
		else {//처음 항인경우 아무 정수 지수입력받음
			printf("%d번 항의 '지수'값을 적어주세요>>", i);
			while (scanf("%d", &exp) != 1) {
				while (getchar() != '\n') {}
				printf("정수를 입력해 주십시오\n");
				printf("%d번 항의 '지수'값을 적어주세요>>", i);
			}
		}
		printf("\n");

		//A에 값저장
		A[i - 1].coef = coe;//c6386경고가 뜨지만 아래의 realloc사용으로 i보다 배열크기가 항상크다.
		A[i - 1].expon = exp;

		//coe에-1 exp에1을 넣을경우 while문이 멈추며 오류가 일어나서
		//이를 막고자 다시한번 coe와exp의 값 확인 후
		//-1-1이 아니라면 0 0으로 고정
		if (coe == -1 && exp == -1)
			;
		else {
			coe = 0;
			exp = 0;
		}
		i++;//항을 다음항으로
		if (i >= sizeA - 1) {//배열이 다 찰경우 재할당을 통해 배열의 크기를 늘려준다.
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
	printf("다항식 A\n");
	printArry(A);
	printf("\n");
	while (getchar() != '\n') {}
	//*********************아래는 다항식 B를 입력받는 부분. A와 완전히 동일하여 주석을 적지않음.*********************************
	printf("\n다항식 B를 입력받습니다. 지수가 큰 항부터 입력해 주십시오.\n");
	printf("***마지막 항까지 입력하셨으면 다음 계수와 지수에-1을 입력해 주십시오.***\n");
	i = 1;//변수들 초기화
	coe = 0;
	exp = 0;
	while (coe != -1 && exp != -1) {
		T = 1;
		printf("%d번 항의 '계수'값을 적어주세요>>", i);
		while (scanf("%f", &coe) != 1) {
			while (getchar() != '\n') {}
			printf("실수를 입력해 주십시오\n");
			printf("%d번 항의 '계수'값을 적어주세요>>", i);
		}

		if (i != 1) {
			while (T == 1) {
				printf("%d번 항의 '지수'값을 적어주세요>>", i);
				while (scanf("%d", &exp) != 1) {
					while (getchar() != '\n') {}
					printf("정수를 입력해 주십시오\n");
					printf("%d번 항의 '지수'값을 적어주세요>>", i);
				}
				if (exp >= B[i - 2].expon) {
					T = 1;
					printf("전의 항들 보다 작은 수를 지수로 적어주세요.\n");
				}
				else T = 0;
			}
		}
		else {
			printf("%d번 항의 '지수'값을 적어주세요>>", i);
			while (scanf("%d", &exp) != 1) {
				while (getchar() != '\n') {}
				printf("정수를 입력해 주십시오\n");
				printf("%d번 항의 '지수'값을 적어주세요>>", i);
			}
		}
		printf("\n");

		B[i - 1].coef = coe;//c6386경고가 뜨지만 아래의 realloc사용으로 i보다 배열크기가 항상크다.
		B[i - 1].expon = exp;
		i++;
		if (coe == -1 && exp == -1)
			;
		else {
			coe = 0;
			exp = 0;
		}
		if (i >= sizeB) {
			sizeA += 10;
			temp = B;
			B = (polynomial*)realloc(B, sizeof(polynomial) * sizeA);
			if (B == NULL) {
				B = temp;
				printf("동적할당 실패.\n");
				error++;
				return;
			}
		}
	}
	printf("다항식 B\n");
	printArry(B);
	printf("\n");
}