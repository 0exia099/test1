#include <stdio.h>
#include <stdlib.h>
#include "Cnode.h"

//@file : Cnode.cpp
/*원형 연결리스트를 동작을 하기위한
함수들을 정의해놓은 cpp파일*/

void Cinsert_front(node* A, int data) {//A원형리스트의 가장 앞에 데이터를 저장하는 함수
	node* temp = (node*)malloc(sizeof(node));
	node* ptr = NULL;

	if (temp == NULL) {//동적할당에 실패했을 경우
		printf("동적할당에 실패했습니다. 종료합니다.\n");
		if (A->next == NULL)
			free(A);
		else {
			while (A->next->next != A->next) {//리스트의 head와 첫노드 제외한 모든 동적할당 해제
				temp = A->next;
				A->next = temp->next;
				free(temp);
				temp = NULL;
			}
			temp = A->next;
			free(A);//head동적할당 해제
			free(temp);//첫노드 동적할당 해제
			temp = NULL;
		}
		exit(1);//종료
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
void Cprint_list(node* A) {//A리스트를 출력하는 함수
	node* ptr = NULL;

	if (A->next == NULL) {
		printf("리스트에 노드가 존재하지 않습니다.\n");
		return;
	}
	printf("list : ");
	if (A->next->next == A->next) {//리스트의 값이 하나인 경우
		printf("%d\n", A->next->data);
		return;
	}
	for (ptr = A->next; ptr->next != A->next; ptr = ptr->next) {//다음노드가 첫노드(A->next)이면 마지막 노드
		printf("%d-", ptr->data);
	}
	printf("%d\n", ptr->data);//마지막 노드 출력
	return;
}
void Cinsert_last(node* A, int data) {//A리스트의 가장 뒤에 데이터를 저장하는 함수
	node* ptr = NULL;
	node* temp = (node*)malloc(sizeof(node));

	if (temp == NULL) {//동적할당에 실패했을 경우
		printf("동적할당에 실패했습니다. 종료합니다.\n");
		if (A->next == NULL)
			free(A);
		else {
			while (A->next->next != A->next) {//리스트의 head와 첫노드 제외 모든 동적할당 해제
				temp = A->next;
				A->next = temp->next;
				free(temp);
				temp = NULL;
			}
			temp = A->next;
			free(A);//head 동적할당 해제
			free(temp);//첫노드 동적할당 해제
			temp = NULL;
		}
		exit(1);//종료
	}

	temp->data = data;
	if (A->next == NULL) {//리스트A가 비었으면
		temp->next = temp;
		A->next = temp;
	}
	else {
		temp->next = A->next;
		for (ptr = A->next; ptr->next != A->next; ptr = ptr->next)//다음노드가 첫노드(A->next)이면 마지막 노드
			;
		ptr->next = temp;
	}
	return;
}
int Csearch(node* A, int data) {//A리스트에서 data가 몇번째 노드에 있는지 찾는 함수
	int count = 0;
	node* ptr = NULL;

	if (A->next == NULL) {
		printf("리스트가 비어있습니다.\n");
		return -1;
	}
	if (A->next->data == data) {
		return count;
	}
	count++;
	for (ptr = A->next; ptr->next != A->next && ptr->next->data != data; ptr = ptr->next) {//ptr->next가 처음노드(A->next)이거나 ptr->next의 data가 찾는 data일때까지
		count++;
	}
	if (ptr->next == A->next) {
		printf("찾으시는 데이터가 없습니다.\n");
		return -1;
	}
	return count;
}
int Cdelete_front(node* A) {//A리스트의 가장 앞 데이터를 삭제하는 함수
	int data;
	node* temp = A->next;
	node* ptr = NULL;

	if (temp == NULL) {
		printf("리스트에 노드가 존재하지 않습니다.\n");
		return -1;
	}
	data = temp->data;
	if (temp->next == A->next) {//노드가 하나일때
		free(temp);//그냥 노드삭제
		A->next = NULL;
		return data;
	}
	else {//노드가 여러개일경우 마지막 노드의 next를 두번째 노드로 바꾸고 A의 next도 두번째노드로 바꾸고 노드삭제
		for (ptr = A->next; ptr->next != A->next; ptr = ptr->next)
			;
		ptr->next = temp->next;
		A->next = temp->next;
	}
	free(temp);
	temp = NULL;

	return data;
}
int Cdelete_(node* A, int data) {//A리스트에서 data를 찾아 삭제하는 함수(같은 데이터가 여러개일경우 하나만 삭제)
	node* ptr = NULL;
	node* temp = NULL;

	if (A->next == NULL) {
		printf("리스트에 노드가 존재하지 않습니다.\n");
		return -1;
	}
	if (A->next->data == data) {//첫노드의 데이터가 data일때
		if (A->next->next == A->next) {//첫노드가 유일한 노드이면 그냥 삭제
			free(A->next);
			A->next = NULL;
			return data;
		}
		//노드가 여러개 있다면
		temp = A->next;
		for (ptr = A->next; ptr->next != A->next; ptr = ptr->next)//다음노드가 첫노드(A->next)이면 마지막 노드
			;
		ptr->next = temp->next;
		A->next = temp->next;
		free(temp);
		temp = NULL;
		return data;
	}
	//첫노드의 데이터가 data가 아닐경우
	for (ptr = A->next; ptr->next != A->next && ptr->next->data != data; ptr = ptr->next)//ptr->next가 A->next이거나 ptr->next의 data가 찾는 data일때까지
		;
	if (ptr->next == A->next) {//다음노드가 첫노드(A->next)이면 마지막 노드
		printf("리스트에 찾으시는 data가 존재하지 않습니다.\n");
		return -1;
	}
	temp = ptr->next;
	ptr->next = temp->next;
	free(temp);
	temp = NULL;

	return data;
}
void Cscan(node* A) {//-1이 입력될때 까지 Cinsert_front, Cinsert_last, Csearch, Cdelete_front, Cdelete_, Cprint_list 중 어떤걸 실행할지 입력받고 실행시키는 함수
	int num = 0;
	int n = 0;
	int m = 0;
	while (num != -1) {
		printf("원하시는 기능의 번호를 입력해 주세요.\n");
		printf("[1. Cinsert_front] ");
		printf("[2. Cinsert_last] ");
		printf("[3. Csearch] ");
		printf("[4. Cdelete_front] ");
		printf("[5. Cdelete_] ");
		printf("[6. Cprint_list] ");
		printf("[-1. 종료(프로그램 종료)]\n>>");
		scanf_s("%d", &num);
		switch (num) {
		case -1:
			printf("\n");
			return;
		case 1:
			printf("저장할 정수 데이터를 입력해 주세요.>>");
			scanf_s("%d", &n);
			Cinsert_front(A, n);
			break;
		case 2:
			printf("저장할 정수 데이터를 입력해 주세요.>>");
			scanf_s("%d", &n);
			Cinsert_last(A, n);
			break;
		case 3:
			printf("검색 할 정수 데이터를 입력해 주세요.>>");
			scanf_s("%d", &n);
			m = Csearch(A, n);
			if (m == -1) {
				;
			}
			else {
				printf("\n리스트의 %d번 노드에 데이터 %d가 있습니다.\n\n", m, n);
			}
			break;
		case 4:
			m = Cdelete_front(A);
			if (m == -1) {
				;
			}
			else {
				printf("\n리스트의 첫번째 노드를 삭제합니다.\n삭제한 노드의 데이터:%d.\n\n", m);
			}
			break;
		case 5:
			printf("삭제할 정수 데이터를 입력해 주세요.>>");
			scanf_s("%d", &n);
			m = Cdelete_(A, n);
			if (m == -1) {
				;
			}
			else {
				printf("\n데이터가 %d인 노드를 하나 삭제합니다.\n삭제한 노드의 데이터:%d.\n\n", n, m);
			}
			break;
		case 6:
			Cprint_list(A);
			break;
		}
	}
}
void Cfree_list(node* A) {//리스트A를 동적할당 해제하는 함수(A는 리스트의head만 가능)
	node* temp = NULL;

	if (A == NULL) {
		return;
	}


	if (A->next == NULL)
		free(A);
	else {
		while (A->next->next != A->next) {//리스트의 head와 첫노드를 빼고 모든 동적할당 해제
			temp = A->next;
			A->next = temp->next;
			free(temp);
			temp = NULL;
		}
		temp = A->next;
		free(A);//head 동적할당 해제
		free(temp);//첫노드 동적할당 해제
		temp = NULL;
	}
	return;
}