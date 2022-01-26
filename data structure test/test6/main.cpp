#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "Queue.h"
#include "Stack.h"
#include "Cnode.h"

//@file : main.cpp
/*���Ḯ��Ʈ�� ������ �����ϴ� �Լ����� ����Ͽ�
�Ϲ� ���Ḯ��Ʈ�� ����, ���Ḯ��Ʈ�� ������ ������ ����,
���Ḯ��Ʈ�� ������ ť�� ����, ���� ���Ḯ��Ʈ�� ������
�ǽ��غ��� ���α׷��� main�Լ�*/

int main() {
	int num = 0;
	node* A = NULL;
	node* B = NULL;
	node* temp = NULL;
	A = (node*)malloc(sizeof(node));//�Լ����� A�� ���� �����Ҵ�
	if (A == NULL) {//�����Ҵ翡 �������� ���
		printf("�����Ҵ翡 �����߽��ϴ�. �����մϴ�.\n");
		exit(1);//����
	}
	A->next = NULL;//NULL�� ���� ������ �����Ⱚ�� ��

	scan(A);//insert_front, insert_last, search, delete_front, delete_, print_list����
	free_list(A->next);//A����Ʈ�� head�� ������ ��� �����Ҵ� ����
	A->next = NULL;//NULL�� ���� ������ �����Ⱚ�� ��

	printf("�������� ��ȯ�մϴ�.\n");
	stack(A);//push()�� pop()����
	free_list(A->next);//A����Ʈ�� head�� ������ ��� �����Ҵ� ����
	A->next = NULL;//NULL�� ���� ������ �����Ⱚ�� ��

	printf("ť�� ��ȯ�մϴ�.\n");
	queue(A);//push()�� pop()����
	free_list(A->next);//A����Ʈ�� head�� ������ ��� �����Ҵ� ����
	A->next = NULL;//NULL�� ���� ������ �����Ⱚ�� ��

	printf("\ninvert()�� �����մϴ�.\n");
	while (num != -1) {
		printf("����Ʈ�� ������ ���� �Է��� �ּ���.[insert_front()�� ����˴ϴ�.]\n");
		printf("[-1�� �Է��ϸ� ����˴ϴ�.]\n>>");
		scanf_s("%d", &num);
		if (num == -1)
			break;
		else
			insert_front(A, num);
	}
	printf("invert()��� �� ����Ʈ.\n");
	print_list(A);//invert()����� ����Ʈ ���� ���
	invert(A);
	printf("invert()��� �� ����Ʈ.\n");
	print_list(A);//invert()����� ����Ʈ ���� ���
	free_list(A->next);//A����Ʈ�� head�� ������ ��� �����Ҵ� ����
	A->next = NULL;//NULL�� ���� ������ �����Ⱚ�� ��

	B = (node*)malloc(sizeof(node));//�Լ����� A�� ���� �����Ҵ�
	if (B == NULL) {//�����Ҵ翡 �������� ���
		printf("�����Ҵ翡 �����߽��ϴ�. �����մϴ�.\n");
		free(A);//�ٷ� ������ A����Ʈ�� A(head)�� �����ϰ� �����߱� ������ A�� ����
		exit(1);//����
	}
	B->next = NULL;//NULL�� ���� ������ �����Ⱚ�� ��

	printf("\nmerge()�� �����մϴ�.\n");
	printf("����ƮA�� �Է¹޽��ϴ�.\n");
	input(A);
	printf("����ƮB�� �Է¹޽��ϴ�.\n");
	input(B);
	printf("merge()��� �� ����ƮA.\n");
	print_list(A);
	printf("merge()��� �� ����ƮB.\n");
	print_list(B);
	merge(A, B);//A��B�� �����ϰ� B ��ü ����
	printf("merge()��� �� ����ƮA.\n");
	print_list(A);
	free_list(A->next);//A����Ʈ�� ��� �����Ҵ� ����
	A->next = NULL;//NULL�� ���� ������ �����Ⱚ�� ��

	printf("\n���� ���Ḯ��Ʈ�� �����մϴ�.\n");
	Cscan(A);//-1�� �Էµɶ� ���� Cinsert_front, Cinsert_last, Csearch, Cdelete_front, Cdelete_, Cprint_list �� ��� �������� �Է¹ް� ����
	Cfree_list(A);//A����Ʈ�� head�� ������ ��� �����Ҵ� ����

	return 0;
}
