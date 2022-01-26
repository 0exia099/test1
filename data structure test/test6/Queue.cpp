#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

//@file : Queue.cpp
/*연결리스트로 구현한 큐의 동작을 하기위한
함수들을 정의해놓은 cpp파일*/

node* rear = NULL;//연결리스트로 큐를 구현할때 사용할 rear(front는 리스트의 head와 같으므로 필요없음)

void queue(node* A) {//-1을 입력할때까지 연결리스트를 큐로 사용하여 addQ()와 deleteQ()중 어떤걸 실행할지 입력받고 실행시키는 함수
	int num = 0;
	int n = 0;
	int m = 0;
	while (num != -1) {
		printf("원하시는 기능의 번호를 입력해 주세요.\n");
		printf("[1. add] ");
		printf("[2. delete] ");
		printf("[3. print_list(queue)] ");
		printf("[-1. 종료(invert를 실행)]\n>>");
		scanf_s("%d", &num);
		switch (num) {
		case -1:
			printf("\n");
			return;
		case 1:
			printf("저장할 정수 데이터를 입력해 주세요.>>");
			scanf_s("%d", &n);
			addQ(A, n);
			break;
		case 2:
			m = deleteQ(A);
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
void addQ(node* A, int data) {//연결리스트를 이용한 큐의 add함수
	//연결리스트의 head를 front, 가장 뒤를 rear로 생각하면 addQ()는 가장뒤에 데이터를 저장하는 insert_last()와 비슷한 동작
	//(A리스트의 head가 front와 같으므로 front필요없음, A리스트의 끝이 rear와 같아 rear가 없어도 되지만 addQ()시 리스트의 끝까지 반복문을 돌리지 않기위해 rear필요함.)
	//아래는 front는 없고 rear만 사용하여 addQ()를 구현한것
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
	temp->next = NULL;
	if (A->next == NULL) {//큐가 비었을때는 head다음에 저장
		A->next = temp;
	}
	else {//큐가 비지 않을경우에는 마지막(rear)에 저장
		rear->next = temp;
	}
	rear = temp;

	return;
}
int deleteQ(node* A) {//연결리스트를 이용한 큐의 delete함수
	//연결리스트에서 head를 front로 생각하면 deleteQ()는 delete_front()와 동일한 동작
	//(A리스트의 head가 항상 front이기 때문에 굳이 front필요없음->delete_front()와 같음)
	int data;
	node* temp = A->next;

	if (temp == NULL) {
		printf("큐가 비었습니다.\n");
		return -1;
	}
	data = temp->data;
	A->next = temp->next;
	free(temp);
	temp = NULL;

	return data;
}