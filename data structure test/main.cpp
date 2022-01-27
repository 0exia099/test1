#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:28182)

//@file : main.cpp
/*�������Ḯ��Ʈ�� �̿��Ͽ� ���׽��� ǥ���ϰ� ���׽��� ������ ������ �����ϴ� �ڵ�
���Ḯ��Ʈ�� ����ϴ� ���� �����帮��Ʈ�� ����Ͽ� malloc�� free�� �ּ�ȭ�Ѵ�.
create_polynomial�Լ��� ���� ����� ���� ��� -1�� �Է¹����� ���� ���׽��� �Է¹޾� �����Ѵ�.
cpadd�Լ��� ���� �� ���׽��� ���ϰ�, cpmul�Լ��� ���� �� ���׽��� ���Ѵ�.
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
polyP a, b, c, d, t, xi;//�����Ҵ� ���н� ���ݱ��� �Ҵ������ free�ϱ����� �Ҵ� ���� ����Ʈ�� ������ ��������

polyP getNode();
void retNode(polyP node);
void cerase(polyP* ptr);
void freeAvail();//avail�� ��� ��带 free�ϴ� �Լ�
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

	printf("���׽�A��");
	create_polynomial(&A);
	a = A;//���������� �ش� ����Ʈ ����
	printf("���׽�B��");
	create_polynomial(&B);
	b = B;//���������� �ش� ����Ʈ ����

	printf("\n���׽�A :\t ���/����\n");
	print_polynomial(A);
	printf("���׽�B :\t ���/����\n");
	print_polynomial(B);

	printf("���׽�A + ���׽�B = ���׽�C\n");
	C = cpadd(A, B);
	c = C;//���������� �ش� ����Ʈ ����
	printf("���׽�C :\t ���/����\n");
	print_polynomial(C);

	printf("���׽�A * ���׽�B = ���׽�D\n");
	D = cpmul(A, B);
	d = D;//���������� �ش� ����Ʈ ����
	printf("���׽�D :\t ���/����\n");
	print_polynomial(D);

	//�Ҵ� ����
	cerase(&a);
	cerase(&b);
	cerase(&c);
	cerase(&d);
	cerase(&t);
	cerase(&xi);
	freeAvail();

	system("PAUSE");//�������Ͽ��� �ٷ� ����Ǵ� ���� �������� �Ͻ�����
}
polyP getNode() {
	polyP node;
	if (avail != NULL) {//avail�� ��尡 ������ �� ��带 ��ȯ
		node = avail;
		avail = avail->link;
	}
	else {//������ malloc
		node = (polyP)malloc(sizeof(*node));
		if (!node) {//�Ҵ� ���н� ������ free�� ����
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
	if (*ptr) {//ptr�� NULL�� �ƴϸ� ��������Ʈ�� �ι�°������ avail�� �߰�
		temp = (*ptr)->link;
		(*ptr)->link = avail;
		avail = temp;
		*ptr = NULL;
	}
	return;
}
void freeAvail() {
	polyP ptr;

	for (; avail != NULL;) {//avail�� ��� ��� free
		ptr = avail;
		avail = avail->link;
		free(ptr);
	}
}
void create_polynomial(polyP* a) {
	int count = 1;//���° ������ ��Ÿ���� ����
	float coe = 0;
	int rexp = 0;//��exp�� ���� ������ ����
	int exp = 0;
	polyP temp;

	printf(" �Է¹޽��ϴ�.\n(-1 -1)�Է½� ����˴ϴ�.\n");
	while (coe != -1 || exp != -1) {
		printf("%d��° ���� ��� ���� : ", count);
		if (count == 1) {//ù���̸�
			while (scanf("%f %d", &coe, &exp) != 2) {//coe�� exp�� �Է¹��� ���Ұ�� �ٽ� �Է�
				while (getchar() != '\n') {}//���ۿ� ����� �� �����
				printf("�ٽ� �Է��� �ּ���\n");
				printf("%d�� ���� ��� ���� : ", count);
			}
		}
		else {//ù���� �ƴϸ�
			while (scanf("%f %d", &coe, &exp) != 2 || rexp <= exp) {//������ exp������ ���� ���� ����
				while (getchar() != '\n') {}//���ۿ� ����� �� �����
				printf("�ٽ� �Է��� �ּ���\n");
				printf("%d�� ���� ��� ���� : ", count);
			}
		}
		if (coe != 0) {//����� 0�̸� ���� ���°��̹Ƿ� 0�� �ƴҶ��� ����Ʈ�� ����
			count++;
			rexp = exp;
			temp = getNode();
			temp->coef = coe;
			temp->expon = exp;
			if (!(*a)) {//ù���� ���
				temp->link = temp;
				(*a) = temp;//�������� -1,-1�� ����� ��尡 a���
				t = *a;//���������� �ش� ����Ʈ ����
			}
			else {//ù���� �ƴҰ��
				temp->link = (*a)->link;
				(*a)->link = temp;
				(*a) = temp;//�������� -1,-1�� ����� ��尡 a���
			}
		}
	}
}
void print_polynomial(polyP a) {
	polyP ptr;
	int count = 1;

	ptr = a->link;//a���� -1, -1�� �����Ƿ� ����������
	for (; ptr != a; ptr = ptr->link) {
		if (ptr->coef >= 0)
			printf("%d��° ��\t %.2f/%d\n", count++, ptr->coef, ptr->expon);
		else
			printf("%d��° ��\t%.2f/%d\n", count++, ptr->coef, ptr->expon);
	}
	printf("\n");
}
polyP cpadd(polyP a, polyP b) {
	polyP startA, c, lastC;
	float sum;
	bool done = false;//done�� true/false���� ��Ÿ������ bool��

	startA = a;
	a = a->link;
	b = b->link;
	c = getNode();
	c->coef = -1;
	c->expon = -1;
	c->link = c;
	lastC = c;
	t = c;//���������� �ش� ����Ʈ ����

	while (!done) {
		switch (COMPARE(a->expon, b->expon)) {
		case -1://a->expon < b->expon
			attach(b->coef, b->expon, &lastC);
			b = b->link;
			break;
		case 0://a->expon == b->expon
			if (startA == a)//case 0�ΰ�� a->expon�� b->expon�� �����Ƿ� a�� ó���̶�� a->expon��-1�̰� b->expon�� -1�� ��� ���̹Ƿ� b�� ó��
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
	//�����Ҵ� ������ ���������� �̿��� cerase�� �ϰ� free�� �ϱ����� attach�Լ��������� �������Ḯ��Ʈ�� ����� ������ lastC->link = c;�ʿ����
	return c;
}
void attach(float coefficient, int exponent, polyP* lastC) {
	polyP temp;

	temp = getNode();
	temp->coef = coefficient;
	temp->expon = exponent;
	temp->link = (*lastC)->link;//�������Ḯ��Ʈ�� ����
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
	d = D;//���������� �ش� ����Ʈ ����

	for (; b != startb; b = b->link) {
		Xi2 = D;//Xi2�� ���׽�D ����
		Xi1 = single_mul(a, b);//Xi1�� ���׽�A�� B���ϳ��� �� ����
		xi = Xi1;//���������� �ش� ����Ʈ ����
		printf("X%d : \n", count++);
		print_polynomial(Xi1);
		D = cpadd(Xi1, Xi2);//���׽� Xi1�� Xi2�� �� D�� ����.
		d = D;//���������� �ش� ����Ʈ ����
		//����� ���׽� ����
		cerase(&Xi1);//Xi1����
		cerase(&Xi2);//D�� ���ο� ����Ʈ�� ����Ǿ����Ƿ� Xi2����
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
	t = Xi;//���������� �ش� ����Ʈ ����

	for (; a != starta; a = a->link) {
		coe = (a->coef) * (b->coef);//����� ���Ѵ�.
		exp = (a->expon) + (b->expon);//������ ���Ѵ�.
		if (coe != 0) {//����� 0�ϰ�� ���� ���°��̹Ƿ� ����� 0�� �ƴѰ͸� �߰�
			attach(coe, exp, &lastXi);
		}
	}
	//�����Ҵ� ������ ���������� �̿��� cerase�� �ϰ� free�� �ϱ����� attach�Լ��������� �������Ḯ��Ʈ�� ����� ������ lastXi->link = Xi;�ʿ����
	return Xi;
}