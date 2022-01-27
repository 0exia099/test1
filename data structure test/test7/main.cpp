#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:28182)

//@file : main.cpp
/*원형연결리스트를 이용하여 다항식을 표현하고 다항식의 덧셈과 곱셉을 구현하는 코드
연결리스트에 사용하는 노드는 가용노드리스트를 사용하여 malloc과 free를 최소화한다.
create_polynomial함수를 통해 계수와 차수 모두 -1을 입력받을때 까지 다항식을 입력받아 저장한다.
cpadd함수를 통해 두 다항식을 더하고, cpmul함수를 통해 두 다항식을 곱한다.
*/

#include <stdio.h>
#include <stdlib.h>

#define COMPARE(x,y) x<y ? -1: x>y ? 1:0

typedef struct poly_* polyP;
typedef struct poly_ {
	float coef;
	int expon;
	polyP link;
}poly;

polyP avail = NULL;
polyP a, b, c, d, t, xi;//동적할당 실패시 지금까지 할당받은것 free하기위해 할당 받은 리스트를 가지는 전역변수

polyP getNode();
void retNode(polyP node);
void cerase(polyP* ptr);
void freeAvail();//avail의 모든 노드를 free하는 함수
void create_polynomial(polyP* a);
void print_polynomial(polyP a);
polyP cpadd(polyP a, polyP b);
void attach(float coefficient, int exponent, polyP* rear);
polyP cpmul(polyP a, polyP b);
polyP single_mul(polyP a, polyP b);

int main() {
	polyP A, B, C, D;
	A = NULL;
	B = NULL;

	printf("다항식A를");
	create_polynomial(&A);
	a = A;//전역변수에 해당 리스트 저장
	printf("다항식B를");
	create_polynomial(&B);
	b = B;//전역변수에 해당 리스트 저장

	printf("\n다항식A :\t 계수/차수\n");
	print_polynomial(A);
	printf("다항식B :\t 계수/차수\n");
	print_polynomial(B);

	printf("다항식A + 다항식B = 다항식C\n");
	C = cpadd(A, B);
	c = C;//전역변수에 해당 리스트 저장
	printf("다항식C :\t 계수/차수\n");
	print_polynomial(C);

	printf("다항식A * 다항식B = 다항식D\n");
	D = cpmul(A, B);
	d = D;//전역변수에 해당 리스트 저장
	printf("다항식D :\t 계수/차수\n");
	print_polynomial(D);

	//할당 해제
	cerase(&a);
	cerase(&b);
	cerase(&c);
	cerase(&d);
	cerase(&t);
	cerase(&xi);
	freeAvail();

	system("PAUSE");//실행파일에서 바로 종료되는 것을 막기위한 일시정지
}
polyP getNode() {
	polyP node;
	if (avail != NULL) {//avail에 노드가 있으면 그 노드를 반환
		node = avail;
		avail = avail->link;
	}
	else {//없으면 malloc
		node = (polyP)malloc(sizeof(*node));
		if (!node) {//할당 실패시 이전것 free후 종료
			cerase(&a);
			cerase(&b);
			cerase(&c);
			cerase(&d);
			cerase(&t);
			cerase(&xi);
			freeAvail();
			exit(1);
		}
	}
	return node;
}
void retNode(polyP node) {
	node->link = avail;
	avail = node;
	return;
}
void cerase(polyP* ptr) {
	polyP temp;
	if (*ptr) {//ptr이 NULL이 아니면 원형리스트의 두번째노드부터 avail에 추가
		temp = (*ptr)->link;
		(*ptr)->link = avail;
		avail = temp;
		*ptr = NULL;
	}
	return;
}
void freeAvail() {
	polyP ptr;

	for (; avail != NULL;) {//avail의 모든 노드 free
		ptr = avail;
		avail = avail->link;
		free(ptr);
	}
}
void create_polynomial(polyP* a) {
	int count = 1;//몇번째 항인지 나타내는 변수
	float coe = 0;
	int rexp = 0;//전exp의 값을 가지는 변수
	int exp = 0;
	polyP temp;

	printf(" 입력받습니다.\n(-1 -1)입력시 종료됩니다.\n");
	while (coe != -1 || exp != -1) {
		printf("%d번째 항의 계수 차수 : ", count);
		if (count == 1) {//첫항이면
			while (scanf("%f %d", &coe, &exp) != 2) {//coe와 exp를 입력받지 못할경우 다시 입력
				while (getchar() != '\n') {}//버퍼에 저장된 값 지우기
				printf("다시 입력해 주세요\n");
				printf("%d번 항의 계수 차수 : ", count);
			}
		}
		else {//첫항이 아니면
			while (scanf("%f %d", &coe, &exp) != 2 || rexp <= exp) {//전항의 exp값보다 작은 값만 받음
				while (getchar() != '\n') {}//버퍼에 저장된 값 지우기
				printf("다시 입력해 주세요\n");
				printf("%d번 항의 계수 차수 : ", count);
			}
		}
		if (coe != 0) {//계수가 0이면 항이 없는것이므로 0이 아닐때만 리스트에 저장
			count++;
			rexp = exp;
			temp = getNode();
			temp->coef = coe;
			temp->expon = exp;
			if (!(*a)) {//첫항일 경우
				temp->link = temp;
				(*a) = temp;//마지막에 -1,-1이 저장된 노드가 a노드
				t = *a;//전역변수에 해당 리스트 저장
			}
			else {//첫항이 아닐경우
				temp->link = (*a)->link;
				(*a)->link = temp;
				(*a) = temp;//마지막에 -1,-1이 저장된 노드가 a노드
			}
		}
	}
}
void print_polynomial(polyP a) {
	polyP ptr;
	int count = 1;

	ptr = a->link;//a에는 -1, -1이 있으므로 다음노드부터
	for (; ptr != a; ptr = ptr->link) {
		if (ptr->coef >= 0)
			printf("%d번째 항\t %.2f/%d\n", count++, ptr->coef, ptr->expon);
		else
			printf("%d번째 항\t%.2f/%d\n", count++, ptr->coef, ptr->expon);
	}
	printf("\n");
}
polyP cpadd(polyP a, polyP b) {
	polyP startA, c, lastC;
	float sum;
	bool done = false;//done은 true/false만을 나타냄으로 bool형

	startA = a;
	a = a->link;
	b = b->link;
	c = getNode();
	c->coef = -1;
	c->expon = -1;
	c->link = c;
	lastC = c;
	t = c;//전역변수에 해당 리스트 저장

	while (!done) {
		switch (COMPARE(a->expon, b->expon)) {
		case -1://a->expon < b->expon
			attach(b->coef, b->expon, &lastC);
			b = b->link;
			break;
		case 0://a->expon == b->expon
			if (startA == a)//case 0인경우 a->expon과 b->expon이 같으므로 a가 처음이라면 a->expon이-1이고 b->expon도 -1이 라는 뜻이므로 b도 처음
				done = true;
			else {
				sum = a->coef + b->coef;
				if (sum != 0)
					attach(sum, a->expon, &lastC);
				a = a->link;
				b = b->link;
			}
			break;
		case 1://a->expon > b->expon
			attach(a->coef, a->expon, &lastC);
			a = a->link;
		}
	}
	//동적할당 오류시 전역변수를 이용해 cerase를 하고 free를 하기위해 attach함수에서부터 원형연결리스트로 만들기 때문에 lastC->link = c;필요없음
	return c;
}
void attach(float coefficient, int exponent, polyP* lastC) {
	polyP temp;

	temp = getNode();
	temp->coef = coefficient;
	temp->expon = exponent;
	temp->link = (*lastC)->link;//원형연결리스트로 만듬
	(*lastC)->link = temp;
	*lastC = temp;
}
polyP cpmul(polyP a, polyP b) {
	polyP D, Xi1, Xi2, startb;
	int count = 1;

	startb = b;
	b = b->link;
	D = getNode();
	D->coef = -1;
	D->expon = -1;
	D->link = D;
	d = D;//전역변수에 해당 리스트 저장

	for (; b != startb; b = b->link) {
		Xi2 = D;//Xi2에 다항식D 저장
		Xi1 = single_mul(a, b);//Xi1에 다항식A와 B항하나의 곱 저장
		xi = Xi1;//전역변수에 해당 리스트 저장
		printf("X%d : \n", count++);
		print_polynomial(Xi1);
		D = cpadd(Xi1, Xi2);//다항식 Xi1와 Xi2의 합 D에 저장.
		d = D;//전역변수에 해당 리스트 저장
		//계산한 다항식 삭제
		cerase(&Xi1);//Xi1삭제
		cerase(&Xi2);//D에 새로운 리스트가 저장되었으므로 Xi2삭제
	}
	return D;
}

polyP single_mul(polyP a, polyP b) {
	float coe;
	int exp;
	polyP Xi, lastXi, starta;

	starta = a;
	a = a->link;
	Xi = getNode();
	Xi->coef = -1;
	Xi->expon = -1;
	Xi->link = Xi;
	lastXi = Xi;
	t = Xi;//전역변수에 해당 리스트 저장

	for (; a != starta; a = a->link) {
		coe = (a->coef) * (b->coef);//계수는 곱한다.
		exp = (a->expon) + (b->expon);//지수는 더한다.
		if (coe != 0) {//계수가 0일경우 항이 없는것이므로 계수가 0이 아닌것만 추가
			attach(coe, exp, &lastXi);
		}
	}
	//동적할당 오류시 전역변수를 이용해 cerase를 하고 free를 하기위해 attach함수에서부터 원형연결리스트로 만들기 때문에 lastXi->link = Xi;필요없음
	return Xi;
}
