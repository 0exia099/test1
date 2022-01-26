#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

//@file : Node.cpp
/*���Ḯ��Ʈ�� ������ �ϱ�����
�Լ����� �����س��� cpp����
invert�� merge�Լ� ����, merge�Լ��� ���� input, insertAsc�Լ� ����*/

void insert_front(node* A, int data) {//A����Ʈ�� ���� �տ� �����͸� �����ϴ� �Լ�
	node* temp = (node*)malloc(sizeof(node));

	if (temp == NULL) {//�����Ҵ翡 �������� ���
		printf("�����Ҵ翡 �����߽��ϴ�. �����մϴ�.\n");
		while (A != NULL) {//����Ʈ�� ��� �����Ҵ� ����
			temp = A;
			A = A->next;
			free(temp);
			temp = NULL;
		}
		exit(1);//����
	}

	temp->data = data;
	temp->next = A->next;
	A->next = temp;
	return;
}
void print_list(node* A) {//A����Ʈ�� ����ϴ� �Լ�
	node* ptr = NULL;

	if (A->next == NULL) {
		printf("����Ʈ�� ��尡 �������� �ʽ��ϴ�.\n");
		return;
	}
	printf("list : ");
	for (ptr = A->next; ptr->next != NULL; ptr = ptr->next) {
		printf("%d ", ptr->data);
	}
	printf("%d\n", ptr->data);//������ ��� ���
	return;
}
void insert_last(node* A, int data) {//A����Ʈ�� ���� �ڿ� �����͸� �����ϴ� �Լ�
	node* ptr = NULL;
	node* temp = (node*)malloc(sizeof(node));

	if (temp == NULL) {//�����Ҵ翡 �������� ���
		printf("�����Ҵ翡 �����߽��ϴ�. �����մϴ�.\n");
		while (A != NULL) {//����Ʈ�� ��� �����Ҵ� ����
			temp = A;
			A = A->next;
			free(temp);
			temp = NULL;
		}
		exit(1);//����
	}

	temp->data = data;
	temp->next = NULL;
	if (A->next == NULL) {//����ƮA�� �������
		A->next = temp;
	}
	else {
		for (ptr = A->next; ptr->next != NULL; ptr = ptr->next)
			;
		ptr->next = temp;
	}
	return;
}
int search(node* A, int data) {//A����Ʈ���� data�� ���° ��忡 �ִ��� ã�� �Լ�
	int count = 0;
	node* ptr = NULL;

	if (A->next == NULL) {
		printf("����Ʈ�� ����ֽ��ϴ�.\n");
		return -1;
	}

	for (ptr = A; ptr->next != NULL && ptr->next->data != data; ptr = ptr->next) {//ptr->next�� NULL�̰ų� ptr->next�� data�� ã�� data�϶�����
		//for�� �߰��� ptr->next->data != data && ptr->next != NULL�� ������ ptr->next�� NULL�ϰ�� NULL�� data�� Ȯ���ϰ� �Ǹ鼭 �����߻�
		count++;
	}
	if (ptr->next == NULL) {
		printf("ã���ô� �����Ͱ� �����ϴ�.\n");
		return -1;
	}
	return count;
}
int delete_front(node* A) {//A����Ʈ�� ���� �� �����͸� �����ϴ� �Լ�
	int data;
	node* temp = A->next;

	if (temp == NULL) {
		printf("����Ʈ�� ��尡 �������� �ʽ��ϴ�.\n");
		return -1;
	}
	data = temp->data;
	A->next = temp->next;
	free(temp);
	temp = NULL;

	return data;
}
int delete_(node* A, int data) {//A����Ʈ���� data�� ã�� �����ϴ� �Լ�(���� �����Ͱ� �������ϰ�� �ϳ��� ����)
	node* ptr = NULL;
	node* temp = NULL;

	if (A->next == NULL) {
		printf("����Ʈ�� ��尡 �������� �ʽ��ϴ�.\n");
		return -1;
	}
	for (ptr = A; ptr->next != NULL && ptr->next->data != data; ptr = ptr->next)//ptr->next�� NULL�̰ų� ptr->next�� data�� ã�� data�϶�����
		;//for�� �߰��� ptr->next->data != data && ptr->next != NULL�� ������ ptr->next�� NULL�ϰ�� NULL�� data�� Ȯ���ϰ� �Ǹ鼭 �����߻�
	if (ptr->next == NULL) {
		printf("����Ʈ�� ã���ô� data�� �������� �ʽ��ϴ�.\n");
		return -1;
	}
	temp = ptr->next;
	ptr->next = temp->next;
	free(temp);
	temp = NULL;

	return data;
}

void scan(node* A) {//-1�� �Էµɶ� ���� insert_front, insert_last, search, delete_front, delete_, print_list �� ��� �������� �Է¹ް� �����Ű�� �Լ�
	int num = 0;
	int n = 0;
	int m = 0;
	while (num != -1) {
		printf("���Ͻô� ����� ��ȣ�� �Է��� �ּ���.\n");
		printf("[1. insert_front] ");
		printf("[2. insert_last] ");
		printf("[3. search] ");
		printf("[4. delete_front] ");
		printf("[5. delete_] ");
		printf("[6. print_list] ");
		printf("[-1. ����(�������� ��ȯ)]\n>>");
		scanf_s("%d", &num);
		switch (num) {
		case -1:
			printf("\n");
			return;
		case 1:
			printf("������ ���� �����͸� �Է��� �ּ���.>>");
			scanf_s("%d", &n);
			insert_front(A, n);
			break;
		case 2:
			printf("������ ���� �����͸� �Է��� �ּ���.>>");
			scanf_s("%d", &n);
			insert_last(A, n);
			break;
		case 3:
			printf("�˻� �� ���� �����͸� �Է��� �ּ���.>>");
			scanf_s("%d", &n);
			m = search(A, n);
			if (m == -1) {
				;
			}
			else {
				printf("\n����Ʈ�� %d�� ��忡 ������ %d�� �ֽ��ϴ�.\n\n", m, n);
			}
			break;
		case 4:
			m = delete_front(A);
			if (m == -1) {
				;
			}
			else {
				printf("\n����Ʈ�� ù��° ��带 �����մϴ�.\n������ ����� ������:%d.\n\n", m);
			}
			break;
		case 5:
			printf("������ ���� �����͸� �Է��� �ּ���.>>");
			scanf_s("%d", &n);
			m = delete_(A, n);
			if (m == -1) {
				;
			}
			else {
				printf("\n�����Ͱ� %d�� ��带 �ϳ� �����մϴ�.\n������ ����� ������:%d.\n\n", n, m);
			}
			break;
		case 6:
			print_list(A);
			break;
		}
	}
}
void free_list(node* A) {//����ƮA�� �����Ҵ� �����ϴ� �Լ�
	node* temp = NULL;

	if (A == NULL) {
		return;
	}

	while (A != NULL) {//����Ʈ�� ��� �����Ҵ� ����
		temp = A;
		A = A->next;
		free(temp);
		temp = NULL;
	}

	return;
}
void invert(node* A) {//����ƮA�� ������ �������� ����� �Լ�

	//����Ʈ�� 3���� ���ӵ� ����� ��ġ�� ������ ������ ������
	//3���� ��� �ѳ�徿 �ڷΰ��� �߰� ����� next�� ���� ��带 ����Ű���� ��
	//���� ���� ��带 ����Ű�� ������ next�� ���������� ���� ��带 ����Ŵ���� ���� ���� ���氡���ϰ�
	//�߰� ��带 ����Ű�� ������ ���� ���� ��带 ����Ű�� ������ �����ϸ� ���� ���� ������ ���̰�
	//���� ���� ��带 ����Ű�� ������ �߰� ��带 ����Ű�� ������ �����ϸ� ���� ���� �����Ѱ��̴�.
	//�� ������ �ݺ��ϴ� ���� ���� ��带 ����Ű�� ������ NULL�̵Ǹ� ������ ����� next ������ ���� ���� ����ȴ�.

	node* temp = NULL;//3���� ����� ���� ���� ��带 ����Ű�� ����
	node* ptr1 = NULL;//3���� ����� �߰� ��带 ����Ű�� ����
	node* ptr2 = NULL;//3���� ����� ���� ���� ��带 ����Ű�� ����

	temp = A->next;//temp�� ����Ʈ ���ۺ���
	while (temp != NULL) {//���� �ڸ� ����Ű�� ������ ������ ����� next�� ���� NULL�� ������ ����
		ptr2 = ptr1;//���� ���� ��带 ����Ű�� ������ �߰� ��带 ����Ű�� ������ ����
		ptr1 = temp;//�߰� ��带 ����Ű�� ������ ���� ���� ��带 ����Ű�� ������ ����
		temp = temp->next;//���� ���� ��带 ����Ű�� ������ next
		ptr1->next = ptr2;//�߰� ����� next�� ���� ��带 ����Ű���� ����
	}
	//while�� ������ ����Ʈ�� ������ �ݴ�� ��
	A->next = ptr1;//����Ʈ�� head�� ������ ��带 ����Ű����.
}
struct node* merge(node* A, node* B) {//����Ʈ �ΰ��� �������� ������������ �����ϴ� �Լ�(A�� �����Ͽ� A����)
	node* ptrA = A->next;//A����Ʈ�� ���� ��带 ������ ����
	node* ptrB = B->next;//B����Ʈ�� ���� ��带 ������ ����
	node* temp = A;//������� ���յ� ����� �������� ����Ű�� ����

	if (A->next == NULL) {//A����Ʈ�� ���������
		A->next = B->next;
		free(B);
		return A;
	}
	else if (B->next == NULL)//B����Ʈ�� ���������
		return A;
	else {
		while (ptrA != NULL && ptrB != NULL) {//�� �� �ϳ��� ����Ʈ�� ����������
			if (ptrA->data < ptrB->data) {//A����Ʈ�� ���� ����� �����Ͱ� ������
				temp->next = ptrA;//A�� ���� ��� ����
				temp = temp->next;//���յ� ��带 ���� ����
				ptrA = ptrA->next;//A�� ���� ����
			}
			else if (ptrA->data > ptrB->data) {//B����Ʈ�� ���� ����� �����Ͱ� ������
				temp->next = ptrB;//B�� ���� ��� ����
				temp = temp->next;
				ptrB = ptrB->next;
			}
			else {//�� ����� �����Ͱ� ������ �Ѵ� �����ϰ� ��������
				temp->next = ptrA;
				temp = temp->next;
				ptrA = ptrA->next;

				temp->next = ptrB;
				temp = temp->next;
				ptrB = ptrB->next;
			}
		}
		if (ptrA != NULL)//A����Ʈ�� ��������
			temp->next = ptrA;//A����Ʈ ������ ��� �״�� ����

		if (ptrB != NULL)//B����Ʈ�� ��������
			temp->next = ptrB;//B����Ʈ ������ ��� �״�� ����
		free(B);//B����Ʈ�� ������ ���� A�� ����Ǿ������� B�� head �����Ҵ� ����
	}
	return A;
}
void input(node* A) {//-1�� �Էµɶ� ���� ����� �����͸� �Է¹޾� ������������ ����Ʈ�� �����ϴ� �Լ�
	int num = 0;
	int n = 0;
	int m = 0;
	while (num != -1) {
		printf("����Ʈ�� ������ ����� �Է��� �ּ���.-1�Է½� ����\n");
		scanf_s("%d", &num);
		if (num == -1)
			return;
		insertAsc(A, num);
	}
}
void insertAsc(node* A, int data) {//A����Ʈ�� ������������ �����͸� �����ϴ� �Լ�
	node* ptr = NULL;
	node* temp = (node*)malloc(sizeof(node));

	if (temp == NULL) {//�����Ҵ翡 �������� ���
		printf("�����Ҵ翡 �����߽��ϴ�. �����մϴ�.\n");
		while (A != NULL) {//����Ʈ�� ��� �����Ҵ� ����
			temp = A;
			A = A->next;
			free(temp);
			temp = NULL;
		}
		exit(1);//����
	}

	temp->data = data;
	if (A->next == NULL) {//A����Ʈ�� ����������
		temp->next = A->next;
		A->next = temp;
		return;
	}
	for (ptr = A; ptr->next != NULL && ptr->next->data <= data; ptr = ptr->next)
		;
	if (ptr->next == NULL) {//data���� ū ���� ������ ���
		temp->next = NULL;
		ptr->next = temp;
		return;
	}
	//ptr->next�� �����Ͱ� data���� ŭ����
	temp->next = ptr->next;
	ptr->next = temp;
	return;
}