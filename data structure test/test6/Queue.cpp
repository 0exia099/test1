#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

//@file : Queue.cpp
/*���Ḯ��Ʈ�� ������ ť�� ������ �ϱ�����
�Լ����� �����س��� cpp����*/

node* rear = NULL;//���Ḯ��Ʈ�� ť�� �����Ҷ� ����� rear(front�� ����Ʈ�� head�� �����Ƿ� �ʿ����)

void queue(node* A) {//-1�� �Է��Ҷ����� ���Ḯ��Ʈ�� ť�� ����Ͽ� addQ()�� deleteQ()�� ��� �������� �Է¹ް� �����Ű�� �Լ�
	int num = 0;
	int n = 0;
	int m = 0;
	while (num != -1) {
		printf("���Ͻô� ����� ��ȣ�� �Է��� �ּ���.\n");
		printf("[1. add] ");
		printf("[2. delete] ");
		printf("[3. print_list(queue)] ");
		printf("[-1. ����(invert�� ����)]\n>>");
		scanf_s("%d", &num);
		switch (num) {
		case -1:
			printf("\n");
			return;
		case 1:
			printf("������ ���� �����͸� �Է��� �ּ���.>>");
			scanf_s("%d", &n);
			addQ(A, n);
			break;
		case 2:
			m = deleteQ(A);
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
void addQ(node* A, int data) {//���Ḯ��Ʈ�� �̿��� ť�� add�Լ�
	//���Ḯ��Ʈ�� head�� front, ���� �ڸ� rear�� �����ϸ� addQ()�� ����ڿ� �����͸� �����ϴ� insert_last()�� ����� ����
	//(A����Ʈ�� head�� front�� �����Ƿ� front�ʿ����, A����Ʈ�� ���� rear�� ���� rear�� ��� ������ addQ()�� ����Ʈ�� ������ �ݺ����� ������ �ʱ����� rear�ʿ���.)
	//�Ʒ��� front�� ���� rear�� ����Ͽ� addQ()�� �����Ѱ�
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
	temp->next = NULL;
	if (A->next == NULL) {//ť�� ��������� head������ ����
		A->next = temp;
	}
	else {//ť�� ���� ������쿡�� ������(rear)�� ����
		rear->next = temp;
	}
	rear = temp;

	return;
}
int deleteQ(node* A) {//���Ḯ��Ʈ�� �̿��� ť�� delete�Լ�
	//���Ḯ��Ʈ���� head�� front�� �����ϸ� deleteQ()�� delete_front()�� ������ ����
	//(A����Ʈ�� head�� �׻� front�̱� ������ ���� front�ʿ����->delete_front()�� ����)
	int data;
	node* temp = A->next;

	if (temp == NULL) {
		printf("ť�� ������ϴ�.\n");
		return -1;
	}
	data = temp->data;
	A->next = temp->next;
	free(temp);
	temp = NULL;

	return data;
}