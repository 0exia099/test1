#include <stdio.h>
#include <stdlib.h>
#include "Cnode.h"

//@file : Cnode.cpp
/*���� ���Ḯ��Ʈ�� ������ �ϱ�����
�Լ����� �����س��� cpp����*/

void Cinsert_front(node* A, int data) {//A��������Ʈ�� ���� �տ� �����͸� �����ϴ� �Լ�
	node* temp = (node*)malloc(sizeof(node));
	node* ptr = NULL;

	if (temp == NULL) {//�����Ҵ翡 �������� ���
		printf("�����Ҵ翡 �����߽��ϴ�. �����մϴ�.\n");
		if (A->next == NULL)
			free(A);
		else {
			while (A->next->next != A->next) {//����Ʈ�� head�� ù��� ������ ��� �����Ҵ� ����
				temp = A->next;
				A->next = temp->next;
				free(temp);
				temp = NULL;
			}
			temp = A->next;
			free(A);//head�����Ҵ� ����
			free(temp);//ù��� �����Ҵ� ����
			temp = NULL;
		}
		exit(1);//����
	}

	temp->data = data;
	if (A->next == NULL) {
		temp->next = temp;
		A->next = temp;
		return;
	}
	temp->next = A->next;
	for (ptr = A->next; ptr->next != A->next; ptr = ptr->next)
		;
	ptr->next = temp;
	A->next = temp;
	return;
}
void Cprint_list(node* A) {//A����Ʈ�� ����ϴ� �Լ�
	node* ptr = NULL;

	if (A->next == NULL) {
		printf("����Ʈ�� ��尡 �������� �ʽ��ϴ�.\n");
		return;
	}
	printf("list : ");
	if (A->next->next == A->next) {//����Ʈ�� ���� �ϳ��� ���
		printf("%d\n", A->next->data);
		return;
	}
	for (ptr = A->next; ptr->next != A->next; ptr = ptr->next) {//������尡 ù���(A->next)�̸� ������ ���
		printf("%d-", ptr->data);
	}
	printf("%d\n", ptr->data);//������ ��� ���
	return;
}
void Cinsert_last(node* A, int data) {//A����Ʈ�� ���� �ڿ� �����͸� �����ϴ� �Լ�
	node* ptr = NULL;
	node* temp = (node*)malloc(sizeof(node));

	if (temp == NULL) {//�����Ҵ翡 �������� ���
		printf("�����Ҵ翡 �����߽��ϴ�. �����մϴ�.\n");
		if (A->next == NULL)
			free(A);
		else {
			while (A->next->next != A->next) {//����Ʈ�� head�� ù��� ���� ��� �����Ҵ� ����
				temp = A->next;
				A->next = temp->next;
				free(temp);
				temp = NULL;
			}
			temp = A->next;
			free(A);//head �����Ҵ� ����
			free(temp);//ù��� �����Ҵ� ����
			temp = NULL;
		}
		exit(1);//����
	}

	temp->data = data;
	if (A->next == NULL) {//����ƮA�� �������
		temp->next = temp;
		A->next = temp;
	}
	else {
		temp->next = A->next;
		for (ptr = A->next; ptr->next != A->next; ptr = ptr->next)//������尡 ù���(A->next)�̸� ������ ���
			;
		ptr->next = temp;
	}
	return;
}
int Csearch(node* A, int data) {//A����Ʈ���� data�� ���° ��忡 �ִ��� ã�� �Լ�
	int count = 0;
	node* ptr = NULL;

	if (A->next == NULL) {
		printf("����Ʈ�� ����ֽ��ϴ�.\n");
		return -1;
	}
	if (A->next->data == data) {
		return count;
	}
	count++;
	for (ptr = A->next; ptr->next != A->next && ptr->next->data != data; ptr = ptr->next) {//ptr->next�� ó�����(A->next)�̰ų� ptr->next�� data�� ã�� data�϶�����
		count++;
	}
	if (ptr->next == A->next) {
		printf("ã���ô� �����Ͱ� �����ϴ�.\n");
		return -1;
	}
	return count;
}
int Cdelete_front(node* A) {//A����Ʈ�� ���� �� �����͸� �����ϴ� �Լ�
	int data;
	node* temp = A->next;
	node* ptr = NULL;

	if (temp == NULL) {
		printf("����Ʈ�� ��尡 �������� �ʽ��ϴ�.\n");
		return -1;
	}
	data = temp->data;
	if (temp->next == A->next) {//��尡 �ϳ��϶�
		free(temp);//�׳� ������
		A->next = NULL;
		return data;
	}
	else {//��尡 �������ϰ�� ������ ����� next�� �ι�° ���� �ٲٰ� A�� next�� �ι�°���� �ٲٰ� ������
		for (ptr = A->next; ptr->next != A->next; ptr = ptr->next)
			;
		ptr->next = temp->next;
		A->next = temp->next;
	}
	free(temp);
	temp = NULL;

	return data;
}
int Cdelete_(node* A, int data) {//A����Ʈ���� data�� ã�� �����ϴ� �Լ�(���� �����Ͱ� �������ϰ�� �ϳ��� ����)
	node* ptr = NULL;
	node* temp = NULL;

	if (A->next == NULL) {
		printf("����Ʈ�� ��尡 �������� �ʽ��ϴ�.\n");
		return -1;
	}
	if (A->next->data == data) {//ù����� �����Ͱ� data�϶�
		if (A->next->next == A->next) {//ù��尡 ������ ����̸� �׳� ����
			free(A->next);
			A->next = NULL;
			return data;
		}
		//��尡 ������ �ִٸ�
		temp = A->next;
		for (ptr = A->next; ptr->next != A->next; ptr = ptr->next)//������尡 ù���(A->next)�̸� ������ ���
			;
		ptr->next = temp->next;
		A->next = temp->next;
		free(temp);
		temp = NULL;
		return data;
	}
	//ù����� �����Ͱ� data�� �ƴҰ��
	for (ptr = A->next; ptr->next != A->next && ptr->next->data != data; ptr = ptr->next)//ptr->next�� A->next�̰ų� ptr->next�� data�� ã�� data�϶�����
		;
	if (ptr->next == A->next) {//������尡 ù���(A->next)�̸� ������ ���
		printf("����Ʈ�� ã���ô� data�� �������� �ʽ��ϴ�.\n");
		return -1;
	}
	temp = ptr->next;
	ptr->next = temp->next;
	free(temp);
	temp = NULL;

	return data;
}
void Cscan(node* A) {//-1�� �Էµɶ� ���� Cinsert_front, Cinsert_last, Csearch, Cdelete_front, Cdelete_, Cprint_list �� ��� �������� �Է¹ް� �����Ű�� �Լ�
	int num = 0;
	int n = 0;
	int m = 0;
	while (num != -1) {
		printf("���Ͻô� ����� ��ȣ�� �Է��� �ּ���.\n");
		printf("[1. Cinsert_front] ");
		printf("[2. Cinsert_last] ");
		printf("[3. Csearch] ");
		printf("[4. Cdelete_front] ");
		printf("[5. Cdelete_] ");
		printf("[6. Cprint_list] ");
		printf("[-1. ����(���α׷� ����)]\n>>");
		scanf_s("%d", &num);
		switch (num) {
		case -1:
			printf("\n");
			return;
		case 1:
			printf("������ ���� �����͸� �Է��� �ּ���.>>");
			scanf_s("%d", &n);
			Cinsert_front(A, n);
			break;
		case 2:
			printf("������ ���� �����͸� �Է��� �ּ���.>>");
			scanf_s("%d", &n);
			Cinsert_last(A, n);
			break;
		case 3:
			printf("�˻� �� ���� �����͸� �Է��� �ּ���.>>");
			scanf_s("%d", &n);
			m = Csearch(A, n);
			if (m == -1) {
				;
			}
			else {
				printf("\n����Ʈ�� %d�� ��忡 ������ %d�� �ֽ��ϴ�.\n\n", m, n);
			}
			break;
		case 4:
			m = Cdelete_front(A);
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
			m = Cdelete_(A, n);
			if (m == -1) {
				;
			}
			else {
				printf("\n�����Ͱ� %d�� ��带 �ϳ� �����մϴ�.\n������ ����� ������:%d.\n\n", n, m);
			}
			break;
		case 6:
			Cprint_list(A);
			break;
		}
	}
}
void Cfree_list(node* A) {//����ƮA�� �����Ҵ� �����ϴ� �Լ�(A�� ����Ʈ��head�� ����)
	node* temp = NULL;

	if (A == NULL) {
		return;
	}


	if (A->next == NULL)
		free(A);
	else {
		while (A->next->next != A->next) {//����Ʈ�� head�� ù��带 ���� ��� �����Ҵ� ����
			temp = A->next;
			A->next = temp->next;
			free(temp);
			temp = NULL;
		}
		temp = A->next;
		free(A);//head �����Ҵ� ����
		free(temp);//ù��� �����Ҵ� ����
		temp = NULL;
	}
	return;
}