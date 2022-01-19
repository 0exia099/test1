#define _CRT_SECURE_NO_WARNINGS//scanf사용을위함
#pragma warning(disable : 6031)

//@file : main.cpp
/*두 다항식 생성후 두 다항식의 합인 다항식과 곱인 다항식을 생성하여 출력하는 프로그램의 main함수.
이를 위해 총6개의 다항식을 동적할당으로 전역변수에 가지고 이 6개의 배열크기를 가지는 변수또한
전역변수로 가진다. realloc사용시 오류를 알려주는 변수도 전역변수로 가진다.
두 다항식을 입력받을지 랜덤으로 생성할지 입력받는 코드를 가진다.*/

#include "PaddPmul.h"

int sizeA = 10;//다항식 A의 배열 크기
int sizeB = 10;//다항식 B의 배열 크기
int sizeC = 10;//다항식 C의 배열 크기
int sizeD = 10;//다항식 D의 배열 크기
int sizeE = 10;//다항식 E의 배열 크기
int sizeF = 10;//다항식 F의 배열 크기
int error = 0;//DInput, RInput, attach함수에서 재할당 실패시 실패를 알려주는 신호로 사용할 변수

polynomial* A = (polynomial*)calloc(sizeA, sizeof(polynomial));//다항식 동적할당
polynomial* B = (polynomial*)calloc(sizeB, sizeof(polynomial));
polynomial* C = (polynomial*)calloc(sizeC, sizeof(polynomial));//더하기 값 다항식
polynomial* D = (polynomial*)calloc(sizeD, sizeof(polynomial));//곱하기 값 다항식
polynomial* E = (polynomial*)calloc(sizeE, sizeof(polynomial));//곱셈의 계산에서 사용될 다항식
polynomial* F = (polynomial*)calloc(sizeF, sizeof(polynomial));//곱셈의 계산에서 사용될 다항식

polynomial* temp;//동적할당 재할당시 메모리공간 부족으로 주소가 바뀔시 이전주소를 반환하기 위해 이전 주소를 가지고 있을 변수

int main() {
	int num;//다항식 생성시 입력받을지 랜덤으로 만들지 입력받는 변수

	//동적할당이 제대로 되었는지 확인
	if (A == NULL) {//동적할당 실패시 해제 후 종료
		printf("동적할당 실패.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}
	if (B == NULL) {
		printf("동적할당 실패.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}
	if (C == NULL) {
		printf("동적할당 실패.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}
	if (D == NULL) {
		printf("동적할당 실패.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}
	if (E == NULL) {
		printf("동적할당 실패.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}
	if (F == NULL) {
		printf("동적할당 실패.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}

	//다항식을 직접 입력할지 랜덤으로 받을지 선택받습니다.
	while (true) {
		printf("다항식을 2개 생성합니다.\n직접 입력하시려면 1, 랜덤으로 만드시려면 2를 입력해 주세요.\n(랜덤 생성시 지수는 1~30, 계수는 -100 ~ 100)\n");
		scanf("%d", &num);
		if (num == 1 || num == 2)//들어올수있는 답인 1, 2이외에는 입력받지 않도록 예외처리
			break;
		else {
			while (getchar() != '\n') {}//버퍼에 저장된 값 지우기
			printf("다시 입력해 주세요.\n");
		}
	}

	if (num == 1) {//직접 입력할 경우
		DInput();//직접입력받는 함수
		if (error != 0) {//DInput함수에서 재할당 실패시 동적할당 해제 후 종료
			free(A);
			free(B);
			free(C);
			free(D);
			free(E);
			free(F);
			return 0;
		}
	}
	else {//랜덤으로 입력할경우
		RInput();//랜덤으로 생성하는 함수
		if (error != 0) {//RInput함수에서 재할당 실패시 동적할당 해제 후 종료
			free(A);
			free(B);
			free(C);
			free(D);
			free(E);
			free(F);
			return 0;
		}
	}

	printf("\n두 다항식\n");//다시한번 두개의 A,B다항식 출력하여 두 다항식을 확인할 수 있도록 한다.
	printf("------------------------\n");
	printf("다항식 A\n");
	printArry(A);
	printf("------------------------\n");

	printf("\n");
	printf("------------------------\n");
	printf("다항식 B\n");
	printArry(B);
	printf("------------------------\n");

	printf("아무런 키를 누르면 두 다항식의 합이 출력 됩니다.\n");
	system("pause");//두 다항식을 확인할 수 있도록 일시정지

	printf("\n두 다항식의 합.\n");

	C = padd(A, B, C, &sizeC);//두 다항식을 더하는 함수

	if (error != 0) {//attach함수에서 재할당 실패시 동적할당 해제 후 종료
		C = temp;
		printf("동적할당 실패.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}	
	//더해진 다항식 출력
	printf("------------------------\n");
	printf("다항식 C\n");
	printArry(C);
	printf("------------------------\n");

	printf("아무런 키를 누르면 두 다항식의 곱이 출력 됩니다.\n");
	system("pause");//다항식의 합을 확인할 수 있도록 일시정지

	printf("\n두 다항식의 곱.\n");//두 다항식의 곱을 출력하는 안내
	//두 다항식을 곱하는 함수
	D = pmul(A, B, D);
	if (error != 0) {//attach함수에서 재할당 실패시 동적할당 해제 후 종료
		D = temp;
		printf("동적할당 실패.\n");
		free(A);
		free(B);
		free(C);
		free(D);
		free(E);
		free(F);
		return 0;
	}
	printf("------------------------\n");//곱해진 다항식 출력
	printf("다항식 D\n");
	printArry(D);
	printf("------------------------\n");


	//동적할당 해제 후 종료
	free(A);
	free(B);
	free(C);
	free(D);
	free(E);
	free(F);
	printf("종료합니다.\n");//종료 메시지
	//실행파일(exe)실행시 바로 종료되므로 일시정지추가 
	system("pause");
	return 0;
}