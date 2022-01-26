#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

//@file : Node.cpp
/*연결리스트를 동작을 하기위한
함수들을 정의해놓은 cpp파일
invert와 merge함수 포함, merge함수를 위한 input, insertAsc함수 포함*/

void insert_front(node* A, int data) {//A리스트의 가장 앞에 데이터를 저장하는 함수
	node* temp = (node*)malloc(sizeof(node));

	if (temp == NULL) {//동적할당에 실패했을 경우
		printf("동적할당에 실패했습니다. 종료합니다.\n");
		while (A != NULL) {//리스트의 모든 동적할당 해제
			temp = A;
			A = A->next;
			free(temp);
			temp = NULL;
		}
		exit(1);//종료
	}

	temp->data = data;
	temp->next = A->next;
	A->next = temp;
	return;
}
void print_list(node* A) {//A리스트를 출력하는 함수
	node* ptr = NULL;

	if (A->next == NULL) {
		printf("리스트에 노드가 존재하지 않습니다.\n");
		return;
	}
	printf("list : ");
	for (ptr = A->next; ptr->next != NULL; ptr = ptr->next) {
		printf("%d ", ptr->data);
	}
	printf("%d\n", ptr->data);//마지막 노드 출력
	return;
}
void insert_last(node* A, int data) {//A리스트의 가장 뒤에 데이터를 저장하는 함수
	node* ptr = NULL;
	node* temp = (node*)malloc(sizeof(node));

	if (temp == NULL) {//동적할당에 실패했을 경우
		printf("동적할당에 실패했습니다. 종료합니다.\n");
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
	if (A->next == NULL) {//리스트A가 비었으면
		A->next = temp;
	}
	else {
		for (ptr = A->next; ptr->next != NULL; ptr = ptr->next)
			;
		ptr->next = temp;
	}
	return;
}
int search(node* A, int data) {//A리스트에서 data가 몇번째 노드에 있는지 찾는 함수
	int count = 0;
	node* ptr = NULL;

	if (A->next == NULL) {
		printf("리스트가 비어있습니다.\n");
		return -1;
	}

	for (ptr = A; ptr->next != NULL && ptr->next->data != data; ptr = ptr->next) {//ptr->next가 NULL이거나 ptr->next의 data가 찾는 data일때까지
		//for문 중간에 ptr->next->data != data && ptr->next != NULL로 적으면 ptr->next가 NULL일경우 NULL의 data를 확인하게 되면서 오류발생
		count++;
	}
	if (ptr->next == NULL) {
		printf("찾으시는 데이터가 없습니다.\n");
		return -1;
	}
	return count;
}
int delete_front(node* A) {//A리스트의 가장 앞 데이터를 삭제하는 함수
	int data;
	node* temp = A->next;

	if (temp == NULL) {
		printf("리스트에 노드가 존재하지 않습니다.\n");
		return -1;
	}
	data = temp->data;
	A->next = temp->next;
	free(temp);
	temp = NULL;

	return data;
}
int delete_(node* A, int data) {//A리스트에서 data를 찾아 삭제하는 함수(같은 데이터가 여러개일경우 하나만 삭제)
	node* ptr = NULL;
	node* temp = NULL;

	if (A->next == NULL) {
		printf("리스트에 노드가 존재하지 않습니다.\n");
		return -1;
	}
	for (ptr = A; ptr->next != NULL && ptr->next->data != data; ptr = ptr->next)//ptr->next가 NULL이거나 ptr->next의 data가 찾는 data일때까지
		;//for문 중간에 ptr->next->data != data && ptr->next != NULL로 적으면 ptr->next가 NULL일경우 NULL의 data를 확인하게 되면서 오류발생
	if (ptr->next == NULL) {
		printf("리스트에 찾으시는 data가 존재하지 않습니다.\n");
		return -1;
	}
	temp = ptr->next;
	ptr->next = temp->next;
	free(temp);
	temp = NULL;

	return data;
}

void scan(node* A) {//-1이 입력될때 까지 insert_front, insert_last, search, delete_front, delete_, print_list 중 어떤걸 실행할지 입력받고 실행시키는 함수
	int num = 0;
	int n = 0;
	int m = 0;
	while (num != -1) {
		printf("원하시는 기능의 번호를 입력해 주세요.\n");
		printf("[1. insert_front] ");
		printf("[2. insert_last] ");
		printf("[3. search] ");
		printf("[4. delete_front] ");
		printf("[5. delete_] ");
		printf("[6. print_list] ");
		printf("[-1. 종료(스택으로 전환)]\n>>");
		scanf_s("%d", &num);
		switch (num) {
		case -1:
			printf("\n");
			return;
		case 1:
			printf("저장할 정수 데이터를 입력해 주세요.>>");
			scanf_s("%d", &n);
			insert_front(A, n);
			break;
		case 2:
			printf("저장할 정수 데이터를 입력해 주세요.>>");
			scanf_s("%d", &n);
			insert_last(A, n);
			break;
		case 3:
			printf("검색 할 정수 데이터를 입력해 주세요.>>");
			scanf_s("%d", &n);
			m = search(A, n);
			if (m == -1) {
				;
			}
			else {
				printf("\n리스트의 %d번 노드에 데이터 %d가 있습니다.\n\n", m, n);
			}
			break;
		case 4:
			m = delete_front(A);
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
			m = delete_(A, n);
			if (m == -1) {
				;
			}
			else {
				printf("\n데이터가 %d인 노드를 하나 삭제합니다.\n삭제한 노드의 데이터:%d.\n\n", n, m);
			}
			break;
		case 6:
			print_list(A);
			break;
		}
	}
}
void free_list(node* A) {//리스트A를 동적할당 해제하는 함수
	node* temp = NULL;

	if (A == NULL) {
		return;
	}

	while (A != NULL) {//리스트의 모든 동적할당 해제
		temp = A;
		A = A->next;
		free(temp);
		temp = NULL;
	}

	return;
}
void invert(node* A) {//리스트A의 연결을 역순으로 만드는 함수

	//리스트의 3개의 연속된 노드의 위치를 가지는 포인터 변수로
	//3변수 모두 한노드씩 뒤로가고 중간 노드의 next가 앞의 노드를 가르키도록 함
	//제일 뒤의 노드를 가르키는 변수는 next가 정상적으로 다음 노드를 가르킴으로 다음 노드로 변경가능하고
	//중간 노드를 가리키는 변수는 제일 뒤의 노드를 가리키는 변수를 대입하면 다음 노드로 변경한 것이고
	//제일 앞의 노드를 가르키는 변수는 중간 노드를 가리키는 변수를 대입하면 다음 노드로 변경한것이다.
	//이 과정을 반복하다 제일 뒤의 노드를 가르키는 변수가 NULL이되면 마지막 노드의 next 마지막 직전 노드로 변경된다.

	node* temp = NULL;//3개의 노드중 제일 뒤의 노드를 가리키는 변수
	node* ptr1 = NULL;//3개의 노드중 중간 노드를 가리키는 변수
	node* ptr2 = NULL;//3개의 노드중 제일 앞의 노드를 가리키는 변수

	temp = A->next;//temp는 리스트 시작부터
	while (temp != NULL) {//가장 뒤를 가리키는 변수가 마지막 노드의 next로 가서 NULL을 받으면 종료
		ptr2 = ptr1;//제일 앞의 노드를 가르키는 변수는 중간 노드를 가리키는 변수를 대입
		ptr1 = temp;//중간 노드를 가리키는 변수는 제일 뒤의 노드를 가리키는 변수를 대입
		temp = temp->next;//제일 뒤의 노드를 가르키는 변수는 next
		ptr1->next = ptr2;//중간 노드의 next가 앞의 노드를 가르키도록 변경
	}
	//while이 끝나면 리스트의 연결이 반대로 됨
	A->next = ptr1;//리스트의 head가 마지막 노드를 가리키게함.
}
struct node* merge(node* A, node* B) {//리스트 두개를 데이터의 오름차순으로 병합하는 함수(A에 병합하여 A리턴)
	node* ptrA = A->next;//A리스트의 현재 노드를 가지는 변수
	node* ptrB = B->next;//B리스트의 현재 노드를 가지는 변수
	node* temp = A;//현재까지 병합된 노드의 마지막을 가리키는 변수

	if (A->next == NULL) {//A리스트가 비어있으면
		A->next = B->next;
		free(B);
		return A;
	}
	else if (B->next == NULL)//B리스트가 비어있으면
		return A;
	else {
		while (ptrA != NULL && ptrB != NULL) {//둘 중 하나의 리스트가 끝날때까지
			if (ptrA->data < ptrB->data) {//A리스트의 현재 노드의 데이터가 작으면
				temp->next = ptrA;//A의 현재 노드 연결
				temp = temp->next;//병합된 노드를 다음 노드로
				ptrA = ptrA->next;//A의 다음 노드로
			}
			else if (ptrA->data > ptrB->data) {//B리스트의 현재 노드의 데이터가 작으면
				temp->next = ptrB;//B의 현재 노드 연결
				temp = temp->next;
				ptrB = ptrB->next;
			}
			else {//두 노드의 데이터가 같으면 둘다 연결하고 다음노드로
				temp->next = ptrA;
				temp = temp->next;
				ptrA = ptrA->next;

				temp->next = ptrB;
				temp = temp->next;
				ptrB = ptrB->next;
			}
		}
		if (ptrA != NULL)//A리스트가 남았으면
			temp->next = ptrA;//A리스트 나머지 노드 그대로 연결

		if (ptrB != NULL)//B리스트가 남았으면
			temp->next = ptrB;//B리스트 나머지 노드 그대로 연결
		free(B);//B리스트의 노드들은 전부 A에 연결되었음으로 B의 head 동적할당 해제
	}
	return A;
}
void input(node* A) {//-1이 입력될때 까지 양수의 데이터를 입력받아 오름차순으로 리스트에 저장하는 함수
	int num = 0;
	int n = 0;
	int m = 0;
	while (num != -1) {
		printf("리스트에 저장할 양수를 입력해 주세요.-1입력시 종료\n");
		scanf_s("%d", &num);
		if (num == -1)
			return;
		insertAsc(A, num);
	}
}
void insertAsc(node* A, int data) {//A리스트에 오름차순으로 데이터를 저장하는 함수
	node* ptr = NULL;
	node* temp = (node*)malloc(sizeof(node));

	if (temp == NULL) {//동적할당에 실패했을 경우
		printf("동적할당에 실패했습니다. 종료합니다.\n");
		while (A != NULL) {//리스트의 모든 동적할당 해제
			temp = A;
			A = A->next;
			free(temp);
			temp = NULL;
		}
		exit(1);//종료
	}

	temp->data = data;
	if (A->next == NULL) {//A리스트가 비어있을경우
		temp->next = A->next;
		A->next = temp;
		return;
	}
	for (ptr = A; ptr->next != NULL && ptr->next->data <= data; ptr = ptr->next)
		;
	if (ptr->next == NULL) {//data보다 큰 값이 없었을 경우
		temp->next = NULL;
		ptr->next = temp;
		return;
	}
	//ptr->next의 데이터가 data보다 큼으로
	temp->next = ptr->next;
	ptr->next = temp;
	return;
}