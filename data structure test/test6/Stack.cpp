#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

//@file : Stack.cpp
/*���Ḯ��Ʈ�� ������ ������ ������ �ϱ�����
�Լ����� �����س��� cpp����*/

node* top = NULL;////���Ḯ��Ʈ�� ������ �����Ҷ� ����� top

void stack(node* A) {//-1�� �Է��Ҷ����� ���Ḯ��Ʈ�� �������� ����Ͽ� push()�� pop()�� ��� �������� �Է¹ް� �����Ű�� �Լ�
	int num = 0;
	int n = 0;
	int m = 0;
	while (num != -1) {
		printf("���Ͻô� ����� ��ȣ�� �Է��� �ּ���.\n");
		printf("[1. push] ");
		printf("[2. pop] ");
		printf("[3. print_list(stack)] ");
		printf("[-1. ����(ť�� ��ȯ)]\n>>");
		scanf_s("%d", &num);
		switch (num) {
		case -1:
			printf("\n");
			return;
		case 1:
			printf("������ ���� �����͸� �Է��� �ּ���.>>");
			scanf_s("%d", &n);
			push(A, n);
			break;
		case 2:
			m = pop(A);
			if (m == -1) {
				;
			}
			else {
				printf("\n���ؿ��� �����͸� �ϳ� �����մϴ�.\n������ ������:%d.\n\n", m);
			}
			break;
		case 3:
			print_list(A);
			break;
		}
	}
}
void push(node* A, int data) {//���Ḯ��Ʈ�� �̿��� ������ push�Լ�
	//���Ḯ��Ʈ���� ���� �պκ��� top���� �����ϸ� push()�� insert_front()�� ������ ����
	//(A����Ʈ�� ���� ó���� �׻� top�̱� ������ ���� top�ʿ����->insert_front()�� ����)
	//top�� ������� insert_front()�� ������ ���� ������ �Ʒ��� top�� �̿��Ͽ� push()�� �����Ѱ�
	node* temp = (node*)malloc(sizeof(node));

	if (temp == NULL) {//�����Ҵ翡 �������� ���
		printf("�����Ҵ翡 �����߽��ϴ�. �����մϴ�.\n");
		A = A->next;
		while (A != NULL) {//����Ʈ�� ��� �����Ҵ� ����
			temp = A;
			A = A->next;
			free(temp);
			temp = NULL;
		}
		exit(1);//����
	}

	temp->data = data;
	temp->next = top;
	A->next = top = temp;

	return;
}
int pop(node* A) {//���Ḯ��Ʈ�� �̿��� ������ pop�Լ�
	//���Ḯ��Ʈ���� ���� �պκ��� top���� �����ϸ� pop()�� delete_front()�� ������ ����
	//(A����Ʈ�� ���� ó���� �׻� top�̱� ������ ���� top�ʿ����->delete_front()�� ����)
	//top�� ������� delete_front()�� ������ ���� ������ �Ʒ��� top�� �̿��Ͽ� pop()�� �����Ѱ�
	int data;
	node* temp = top;

	if (temp == NULL) {
		printf("������ ������ϴ�.\n");
		return -1;
	}

	data = temp->data;
	top = temp->next;
	A->next = top;
	free(temp);
	temp = NULL;

	return data;
}