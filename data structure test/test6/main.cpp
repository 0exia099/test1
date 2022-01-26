#include <stdio.h>
#include <stdlib.h>
#include "Node.h"
#include "Queue.h"
#include "Stack.h"
#include "Cnode.h"

//@file : main.cpp
/*연결리스트의 동작을 실행하는 함수들을 사용하여
일반 연결리스트의 동작, 연결리스트로 구현한 스택의 동작,
연결리스트로 구현한 큐의 동작, 원형 연결리스트의 동작을
실습해보는 프로그램의 main함수*/

int main() {
	int num = 0;
	node* A = NULL;
	node* B = NULL;
	node* temp = NULL;
	A = (node*)malloc(sizeof(node));//함수에서 A를 위해 동적할당
	if (A == NULL) {//동적할당에 실패했을 경우
		printf("동적할당에 실패했습니다. 종료합니다.\n");
		exit(1);//종료
	}
	A->next = NULL;//NULL을 넣지 않으면 쓰레기값이 들어감

	scan(A);//insert_front, insert_last, search, delete_front, delete_, print_list동작
	free_list(A->next);//A리스트의 head를 제외한 모든 동적할당 해제
	A->next = NULL;//NULL을 넣지 않으면 쓰레기값이 들어감

	printf("스택으로 전환합니다.\n");
	stack(A);//push()와 pop()동작
	free_list(A->next);//A리스트의 head를 제외한 모든 동적할당 해제
	A->next = NULL;//NULL을 넣지 않으면 쓰레기값이 들어감

	printf("큐로 전환합니다.\n");
	queue(A);//push()와 pop()동작
	free_list(A->next);//A리스트의 head를 제외한 모든 동적할당 해제
	A->next = NULL;//NULL을 넣지 않으면 쓰레기값이 들어감

	printf("\ninvert()를 실행합니다.\n");
	while (num != -1) {
		printf("리스트에 저장할 수를 입력해 주세요.[insert_front()로 저장됩니다.]\n");
		printf("[-1을 입력하면 종료됩니다.]\n>>");
		scanf_s("%d", &num);
		if (num == -1)
			break;
		else
			insert_front(A, num);
	}
	printf("invert()사용 전 리스트.\n");
	print_list(A);//invert()사용전 리스트 상태 출력
	invert(A);
	printf("invert()사용 후 리스트.\n");
	print_list(A);//invert()사용전 리스트 상태 출력
	free_list(A->next);//A리스트의 head를 제외한 모든 동적할당 해제
	A->next = NULL;//NULL을 넣지 않으면 쓰레기값이 들어감

	B = (node*)malloc(sizeof(node));//함수에서 A를 위해 동적할당
	if (B == NULL) {//동적할당에 실패했을 경우
		printf("동적할당에 실패했습니다. 종료합니다.\n");
		free(A);//바로 직전에 A리스트의 A(head)를 제외하고 해제했기 때문에 A만 해제
		exit(1);//종료
	}
	B->next = NULL;//NULL을 넣지 않으면 쓰레기값이 들어감

	printf("\nmerge()를 실행합니다.\n");
	printf("리스트A를 입력받습니다.\n");
	input(A);
	printf("리스트B를 입력받습니다.\n");
	input(B);
	printf("merge()사용 전 리스트A.\n");
	print_list(A);
	printf("merge()사용 전 리스트B.\n");
	print_list(B);
	merge(A, B);//A와B를 병합하고 B 전체 해제
	printf("merge()사용 후 리스트A.\n");
	print_list(A);
	free_list(A->next);//A리스트의 모든 동적할당 해제
	A->next = NULL;//NULL을 넣지 않으면 쓰레기값이 들어감

	printf("\n원형 연결리스트를 실행합니다.\n");
	Cscan(A);//-1이 입력될때 까지 Cinsert_front, Cinsert_last, Csearch, Cdelete_front, Cdelete_, Cprint_list 중 어떤걸 실행할지 입력받고 실행
	Cfree_list(A);//A리스트의 head를 포함한 모든 동적할당 해제

	return 0;
}
