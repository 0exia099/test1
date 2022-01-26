#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

//@file : Stack.cpp
/*연결리스트로 구현한 스택의 동작을 하기위한
함수들을 정의해놓은 cpp파일*/

node* top = NULL;////연결리스트로 스택을 구현할때 사용할 top

void stack(node* A) {//-1을 입력할때까지 연결리스트를 스택으로 사용하여 push()와 pop()중 어떤걸 실행할지 입력받고 실행시키는 함수
	int num = 0;
	int n = 0;
	int m = 0;
	while (num != -1) {
		printf("원하시는 기능의 번호를 입력해 주세요.\n");
		printf("[1. push] ");
		printf("[2. pop] ");
		printf("[3. print_list(stack)] ");
		printf("[-1. 종료(큐로 전환)]\n>>");
		scanf_s("%d", &num);
		switch (num) {
		case -1:
			printf("\n");
			return;
		case 1:
			printf("저장할 정수 데이터를 입력해 주세요.>>");
			scanf_s("%d", &n);
			push(A, n);
			break;
		case 2:
			m = pop(A);
			if (m == -1) {
				;
			}
			else {
				printf("\n스텍에서 데이터를 하나 삭제합니다.\n삭제한 데이터:%d.\n\n", m);
			}
			break;
		case 3:
			print_list(A);
			break;
		}
	}
}
void push(node* A, int data) {//연결리스트를 이용한 스택의 push함수
	//연결리스트에서 가장 앞부분을 top으로 생각하면 push()는 insert_front()와 동일한 동작
	//(A리스트의 가장 처음이 항상 top이기 때문에 굳이 top필요없음->insert_front()와 같음)
	//top이 없을경우 insert_front()와 완전히 같기 때문에 아래는 top을 이용하여 push()를 구현한것
	node* temp = (node*)malloc(sizeof(node));

	if (temp == NULL) {//동적할당에 실패했을 경우
		printf("동적할당에 실패했습니다. 종료합니다.\n");
		A = A->next;
		while (A != NULL) {//리스트의 모든 동적할당 해제
			temp = A;
			A = A->next;
			free(temp);
			temp = NULL;
		}
		exit(1);//종료
	}

	temp->data = data;
	temp->next = top;
	A->next = top = temp;

	return;
}
int pop(node* A) {//연결리스트를 이용한 스택의 pop함수
	//연결리스트에서 가장 앞부분을 top으로 생각하면 pop()은 delete_front()와 동일한 동작
	//(A리스트의 가장 처음이 항상 top이기 때문에 굳이 top필요없음->delete_front()와 같음)
	//top이 없을경우 delete_front()와 완전히 같기 때문에 아래는 top을 이용하여 pop()를 구현한것
	int data;
	node* temp = top;

	if (temp == NULL) {
		printf("스택이 비었습니다.\n");
		return -1;
	}

	data = temp->data;
	top = temp->next;
	A->next = top;
	free(temp);
	temp = NULL;

	return data;
}