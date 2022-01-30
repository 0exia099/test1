#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:28182)

//@file : main.cpp
/*tree를 구조체를 사용한 연결리스트로 표현하는 코드
가용노드리스트를 사용하여 malloc과 free를 최소화한다.
inorder, preordcer, postorder으로 tree를 표현하는 순회 함수를 통해
tree를 출력하고 tree를 복사하는 copy함수, 좌우를 바꾸어 복사하는 swap함수를 사용하여
tree를 복사한 후 순회 함수로 출력하고 두 tree가 같은지 확인하는 equal함수를 이용하여 비교한다.
랜덤으로 tree를 만드는 make_tree_rand함수를 통하여 tree를 만들어 순회 함수로 출력한다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node_* nodeP;
typedef struct node_ {
	int data;
	nodeP lchild;
	nodeP rchild;
}node;

nodeP avail = NULL;//가용노드리스트를 이용하기 위한 avail
//가용노드 리스트를 위한 함수
nodeP getNode();
void retNode(nodeP temp);
void erase_tree(nodeP ptr);//트리를 avail에 추가하는 함수
void freeAvail();//avail의 모든 노드를 free하는 함수

nodeP make_tree_by_code();//강의에 나온 루트가 5인 트리를 만드는 함수
void inorder(nodeP ptr);
void preorder(nodeP ptr);
void postorder(nodeP ptr);
nodeP copy(nodeP ptr);
bool equal(nodeP ptr1, nodeP ptr2);
nodeP swap(nodeP ptr);
nodeP make_tree_rand();//랜덤으로 tree를 만드는 함수

int main() {
	nodeP A, B, C;
	A = B = C = NULL;

	A = make_tree_by_code();//강의에 나온 루트가 5인 트리
	printf("A tree :\n");
	printf("inorder : ");
	inorder(A);
	printf("\npreorder : ");
	preorder(A);
	printf("\npostorder : ");
	postorder(A);
	printf("\n\n");

	B = copy(A);
	printf("B = copy(A)\n");
	printf("B tree :\n");
	printf("inorder : ");
	inorder(B);
	printf("\npreorder : ");
	preorder(B);
	printf("\npostorder : ");
	postorder(B);
	printf("\n");
	equal(A, B) ? printf("A와 B는동일합니다.\n\n") : printf("A와 B는 상이합니다.\n\n");//equal함수의 리턴값에 따라 출력

	C = swap(A);
	printf("C = swap(A)\n");
	printf("C tree :\n");
	printf("inorder : ");
	inorder(C);
	printf("\npreorder : ");
	preorder(C);
	printf("\npostorder : ");
	postorder(C);
	printf("\n");
	equal(A, C) ? printf("A와 C는 동일합니다.\n\n") : printf("A와 C는 상이합니다.\n\n");

	//사용안하는 트리 가용노드리스트로 이동
	erase_tree(A);
	erase_tree(B);
	erase_tree(C);

	A = make_tree_rand();
	printf("랜덤생성 tree :\n");
	printf("inorder : ");
	inorder(A);
	printf("\npreorder : ");
	preorder(A);
	printf("\npostorder : ");
	postorder(A);
	printf("\n\n");

	//랜덤으로 만든 트리 가용노드리스트로 이동 후 가용노드 리스트 free
	erase_tree(A);
	freeAvail();

	system("PAUSE");//실행파일에서 바로 종료되는 것을 막기위한 일시정지
	return 0;
}
nodeP getNode() {
	nodeP temp;
	if (avail != NULL) {//avail에 노드가 있으면 그 노드를 반환
		temp = avail;
		avail = avail->rchild;//rchild를 link로 사용
	}
	else {//없으면 malloc
		temp = (nodeP)malloc(sizeof(*temp));
		if (!temp) {//할당 실패 시 종료
			fprintf(stderr, "Insufficient memory");
			exit(EXIT_FAILURE);
		}
	}
	return temp;
}
void retNode(nodeP temp) {
	temp->rchild = avail;
	avail = temp;
	return;
}
void erase_tree(nodeP ptr) {//tree에 사용하는 연결리스트는 원형연결리스트가 아니므로 하나씩 avail로 이동.
	if (ptr) {
		//재귀함수로 postorder방식을 사용하여 avail로 이동
		erase_tree(ptr->lchild);
		erase_tree(ptr->rchild);
		retNode(ptr);
	}
}
void freeAvail() {
	nodeP ptr;

	for (; avail != NULL;) {//avail의 모든 노드 free
		ptr = avail;
		avail = avail->rchild;
		free(ptr);
	}
}
nodeP make_tree_by_code() {

	nodeP temp5 = getNode();//data가 4인 노드
	temp5->data = 4;
	temp5->lchild = NULL;
	temp5->rchild = NULL;

	nodeP temp4 = getNode();//data가 1인 노드
	temp4->data = 1;
	temp4->lchild = NULL;
	temp4->rchild = NULL;

	nodeP temp3 = getNode();//data가 8인 노드
	temp3->data = 8;
	temp3->lchild = NULL;
	temp3->rchild = NULL;

	nodeP temp2 = getNode();//data가 3인 노드
	temp2->data = 3;
	temp2->lchild = temp4;
	temp2->rchild = temp5;

	nodeP temp1 = getNode();//data가 5인 노드
	temp1->data = 5;
	temp1->lchild = temp2;
	temp1->rchild = temp3;
	
	return temp1;
}

void inorder(nodeP ptr) {
	if (ptr) {
		inorder(ptr->lchild);
		printf("%d ", ptr->data);//lchild다음 본인 출력
		inorder(ptr->rchild);
	}
}
void preorder(nodeP ptr) {
	if (ptr) {
		printf("%d ", ptr->data);//본인 출력 다음 lchild
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}
void postorder(nodeP ptr) {
	if (ptr) {
		postorder(ptr->lchild);
		postorder(ptr->rchild);
		printf("%d ", ptr->data);//lchild, rchild 다음 본인 출력
	}
}

nodeP copy(nodeP ptr) {
	nodeP temp;
	if (ptr) {
		temp = getNode();
		temp->lchild = copy(ptr->lchild);//ptr의 lchild쪽 하위노드들 전부 복사
		temp->rchild = copy(ptr->rchild);//ptr의 rchild쪽 하위노드들 전부 복사
		temp->data = ptr->data;//ptr복사
		return temp;
	}
	else
		return NULL;
}

bool equal(nodeP ptr1, nodeP ptr2) {
	//둘다 NULL이거나 (둘다 NULL이 아니고 루트의 data가 같고 루트의 하위노드들이 전부 같은 경우)같다.
	return((!ptr1 && !ptr2) || (ptr1 && ptr2 && (ptr1->data == ptr2->data) && equal(ptr1->lchild, ptr2->lchild) && equal(ptr1->rchild, ptr2->rchild)));
}

nodeP swap(nodeP ptr) {
	nodeP temp;
	if (ptr) {
		temp = getNode();
		temp->lchild = swap(ptr->rchild);//ptr의 rchild쪽을 복사하여 좌우 반전
		temp->rchild = swap(ptr->lchild);//ptr의 lchild쪽을 복사하여 좌우 반전
		temp->data = ptr->data;//루트는 좌우가 없으므로 그대로
		return temp;
	}
	else
		return NULL;
}

nodeP make_tree_rand(){
	int num;
	int count, i;
	nodeP ptr, tree_node, temp;

	ptr = tree_node = temp = NULL;
	
	printf("만들 트리의 노드 갯수를 입력하세요 : ");
	scanf("%d", &num);//노드 갯수 입력
	if (num == 0) {//0개인경우 NULL인 tree
		return temp;
	}
	temp = getNode();
	temp->data = 1;//1은 루트노드
	temp->lchild = NULL;
	temp->rchild = NULL;
	srand((unsigned int)time(NULL));

	for (i = 2; i <= num; i++) {//2부터 num까지 노드 생성
		ptr = temp;//루트노드 부터 아래로 탐색
		tree_node = getNode();//생성할 노드
		tree_node->data = i;
		tree_node->lchild = NULL;
		tree_node->rchild = NULL;
		while (true) {
			count = rand() % 2;//count가 0이면 왼쪽 1이면 오른쪽
			if (count == 0) {
				if (ptr->lchild)//현재 노드의 lchild가 NULL이 아니면 lchild로 내려감
					ptr = ptr->lchild;
				else {//lchild가 NULL이면 생성한 노드 연결
					ptr->lchild = tree_node;
					break;//while문 break
				}
			}
			else {
				if (ptr->rchild)//현재 노드의 rchild가 NULL이 아니면 rchild로 내려감
					ptr = ptr->rchild;
				else {//rchild가 NULL이면 생성한 노드 연결
					ptr->rchild = tree_node;
					break;//while문 break
				}
			}
		}
	}
	
	return temp;
}
