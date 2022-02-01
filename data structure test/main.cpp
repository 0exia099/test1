#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:28182)

//@file : main.cpp
/*이진탐색트리를 구조체를 사용한 연결리스트로 표현하는 코드
가용노드리스트를 사용하여 malloc과 free를 최소화한다.
insert함수를 통하여 새로운 노드를 이진탐색트리에 추가한다.
inorder로 생성된 트리를 출력하고 iterSearch함수를 통하여 생성된 트리에서 검색을 할 수 있다.
make_bst함수를 이용하여 입력받은 n의 갯수만큼 노드를 생성하여 이진탐색트리를 만들고 생성 실행시간을 측정한다.
getNumOfNodes, treeHeight_root, treeHeight, getNumOfLeafs 함수를 이용하여 노드수, 트리 높이, 리프노드수를 출력한다.
deleteNode함수를 통하여 이진탐색트리의 구조를 유지하며 하나의 노드를 삭제한다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node* treePointer;
typedef struct node {
	int key;
	double value;
	treePointer lchild;
	treePointer rchild;
}node;

treePointer avail = NULL;//가용노드리스트를 이용하기 위한 avail
//가용노드 리스트를 위한 함수
treePointer getNode();
void retNode(treePointer temp);
void erase_tree(treePointer ptr);//트리를 avail에 추가하는 함수
void freeAvail();//avail의 모든 노드를 free하는 함수

void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

void insert(treePointer* node, int k, double v);
treePointer modifiedSearch(treePointer node, int k);
treePointer iterSearch(treePointer tree, int k);
treePointer make_bst(int n);

int getNumOfNodes(treePointer ptr);
int treeHeight_root(treePointer ptr);//루트는 높이의 숫자에 포함하지 않기위해 따로함수
int treeHeight(treePointer ptr);
int getNumOfLeafs(treePointer ptr);

void deleteNode(treePointer* ptr, int k);

int main() {
	int i;
	int key[10] = { 5, 3, 8, 1,9,2,7,10,6,4 };//보고서에 있는 key입력순서
	int n = 0;
	double start, stop;
	treePointer A = NULL;
	treePointer temp;

	for (i = 0; i < 10; i++) {
		insert(&A, key[i], 1.0 / key[i]);
	}
	printf("inorder : ");
	inorder(A);
	printf("\n");

	while (true) {//-1입력시까지 검색
		printf("\n찾으실 key값을 입력해 주세요.(-1입력 시 검색 종료)>>");
		scanf("%d", &n);
		if (n == -1)
			break;
		temp = iterSearch(A, n);
		if (!temp) {//iterSearch에서 NULL리턴한 경우 인자로 넘긴 트리가 NULL이거나 해당 key값이 없는 경우.
			printf("입력하신 key값이 존재하지 않습니다.\n");//두 경우다 key값이 존재하지 않는다.
		}
		else {
			printf("입력하신 key값의 value : (%d, %.3lf)\n", temp->key, temp->value);
		}
	}
	erase_tree(A);//가용노드 리스트로 이동
	A = NULL;

	while (true) {//-1입력시까지 n개의 노드를 가진 트리 생성
		printf("\n만드실 이진 탐색 트리의 노드 수를 입력해 주세요.(-1입력시 트리 생성 종료)>>");
		scanf("%d", &n);
		if (n == -1)
			break;
		start = (double)clock();
		A = make_bst(n);
		stop = (double)clock();
		/*printf("inorder : ");//노드 전부 출력시 많아짐으로 출력은 뺌
		inorder(A);
		printf("\n");*/
		printf("트리 생성 시간 : %.3lf\n", (stop - start)/CLOCKS_PER_SEC);
		printf("노드 수 : %d\n", getNumOfNodes(A));
		printf("트리 높이 : %d\n", treeHeight_root(A));
		printf("리프 노드 수 : %d\n", getNumOfLeafs(A));

		erase_tree(A);//가용노드 리스트로 이동
		A = NULL;
	}

	for (i = 0; i < 10; i++) {//보고서에 있던 트리를 활용하여 삭제함수 테스트
		insert(&A, key[i], 1.0 / key[i]);
	}
	printf("inorder : ");
	inorder(A);
	printf("\n");
	printf("preorder : ");//삭제 함수 실행 후 트리 모양을 확인하기 위해 preorder, postorder사용
	preorder(A);
	printf("\n");
	printf("postorder : ");
	postorder(A);
	printf("\n");
	printf("노드 수 : %d\n", getNumOfNodes(A));
	printf("트리 높이 : %d\n", treeHeight_root(A));
	printf("리프 노드 수 : %d\n", getNumOfLeafs(A));
	while (true) {//-1입력시 까지 노드 삭제
		printf("\n삭제할 노드의 key를 입력해 주세요.(-1입력시 종료)>>");
		scanf("%d", &n);
		if (n == -1)
			break;
		deleteNode(&A, n);
		printf("inorder : ");
		inorder(A);
		printf("\n");
		printf("preorder : ");
		preorder(A);
		printf("\n");
		printf("postorder : ");
		postorder(A);
		printf("\n");
		printf("노드 수 : %d\n", getNumOfNodes(A));
		printf("트리 높이 : %d\n", treeHeight_root(A));
		printf("리프 노드 수 : %d\n", getNumOfLeafs(A));
	}

	erase_tree(A);//가용노드 리스트로 이동
	freeAvail();//가용노드 리스트 전체 반환

	system("PAUSE");//실행파일에서 바로 종료되는 것을 막기위한 일시정지
	return 0;
}
treePointer getNode() {
	treePointer temp;
	if (avail != NULL) {//avail에 노드가 있으면 그 노드를 반환
		temp = avail;
		avail = avail->rchild;//rchild를 link로 사용
	}
	else {//없으면 malloc
		temp = (treePointer)malloc(sizeof(*temp));
		if (!temp) {//할당 실패 시 종료
			fprintf(stderr, "Insufficient memory");
			exit(EXIT_FAILURE);
		}
	}
	return temp;
}
void retNode(treePointer temp) {//노드 하나 avail로 이동
	temp->rchild = avail;
	avail = temp;
	return;
}
void erase_tree(treePointer ptr) {//tree에 사용하는 연결리스트는 원형연결리스트가 아니므로 하나씩 avail로 이동.
	if (ptr) {
		//재귀함수로 postorder방식을 사용하여 avail로 이동
		erase_tree(ptr->lchild);
		erase_tree(ptr->rchild);
		retNode(ptr);
	}
}
void freeAvail() {
	treePointer ptr;

	for (; avail != NULL;) {//avail의 모든 노드 free
		ptr = avail;
		avail = avail->rchild;
		free(ptr);
	}
}
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->lchild);
		printf("(%d, ", ptr->key);
		printf("%.3lf) ", ptr->value);
		inorder(ptr->rchild);
	}
}
void preorder(treePointer ptr) {
	if (ptr) {
		printf("(%d, ", ptr->key);
		printf("%.3lf) ", ptr->value);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->lchild);
		postorder(ptr->rchild);
		printf("(%d, ", ptr->key);
		printf("%.3lf) ", ptr->value);
	}
}
void insert(treePointer* node, int k, double v) {
	treePointer ptr, temp = modifiedSearch(*node, k);//modifiedSearch함수로 k가 들어갈 부모노드 찾음
	if (temp || !(*node)) {//temp값이 있거나 node가 NULL인경우->이미 k인 key가 있는 경우 제외
		ptr = getNode();//가용노드 사용
		/*ptr = (treePointer)malloc(sizeof(*ptr));
		if (!ptr) {
			fprintf(stderr, "Insufficient memory");
			exit(EXIT_FAILURE);
		}*/
		ptr->key = k;
		ptr->value = v;
		ptr->lchild = ptr->rchild = NULL;
		if (*node)
			if (k < temp->key)//부모노드보다 크면 rchild 작으면lchild
				temp->lchild = ptr;
			else
				temp->rchild = ptr;
		else
			*node = ptr;
	}
}
treePointer modifiedSearch(treePointer node, int k) {//k가 들어갈 NULL자리의 부모노드 찾는 함수
	for (treePointer ptr = node; ptr != NULL;) {
		if (ptr->key == k)//key값이 있는경우
			return NULL;
		if (k < ptr->key) {//key보다 k가 작으면 왼쪽
			if (ptr->lchild == NULL)
				return ptr;
			else
				ptr = ptr->lchild;
		}
		else {
			if (ptr->rchild == NULL)
				return ptr;
			else
				ptr = ptr->rchild;
		}
	}
	return NULL;//루트가 NULL인경우
}
treePointer iterSearch(treePointer tree, int k) {
	int count = 1;//iterSearch가 이미 불려왔으므로 1부터 시작
	while (tree) {
		if (k == tree->key) {
			printf("search 반복 횟수 : %d\n", count);//iterSearch이기 때문에 함수 호출횟수가 아닌 반복 횟수를 출력
			return tree;
		}
		if (k < tree->key)
			tree = tree->lchild;
		else
			tree = tree->rchild;
		count++;
	}
	printf("search 반복 횟수 : %d\n", count);//iterSearch이기 때문에 함수 호출횟수가 아닌 반복 횟수를 출력
	return NULL;
}
treePointer make_bst(int n) {
	treePointer temp = NULL;
	int key;
	double value;
	int i;

	for (i = 0; i < n; i++) {//n번만큼 key와 value 생성 후 insert함수로 노드 생성
		key = (int)((rand() / (0x7fff * 1.0)) * 100000000);
		value = 1.0 / key;
		insert(&temp, key, value);
	}
	return temp;
}
int getNumOfNodes(treePointer ptr) {
	int count = 0;
	if (ptr) {
		//lchild 노드 갯수 + 자신 + rchild 노드 갯수
		count += getNumOfNodes(ptr->lchild);
		count++;
		count += getNumOfNodes(ptr->rchild);
	}
	return count;
}
int treeHeight_root(treePointer ptr) {//루트는 높이에 포함을 하지 않기때문에 +1이 없는 것
	int height = 0;
	int l, r;
	l = r = 0;
	if (ptr)
	{
		l = treeHeight(ptr->lchild);//함수호출 줄이기 위하여 변수에 값 저장.
		r = treeHeight(ptr->rchild);
		height = ((l > r) ? l : r);//루트는 포함하지 않음으로 lchild, rchild중 큰 값
	}
	return height;
}
int treeHeight(treePointer ptr) {//루트 이외에는 +1씩 계산
	int height = 0;
	int l, r;
	l = r = 0;
	if (ptr)
	{
		l = treeHeight(ptr->lchild);//함수호출 줄이기 위하여 변수에 값 저장.
		r = treeHeight(ptr->rchild);
		height = 1 + ((l > r) ? l : r);//lchild, rchild중 큰 값 +1
	}
	return height;
}
int getNumOfLeafs(treePointer ptr) {
	int count = 0;
	if (ptr)
	{
		if (ptr->lchild == NULL && ptr->rchild == NULL)//리프노드라면 1반환
			return 1;
		else
		{
			count += getNumOfLeafs(ptr->lchild);//lchild의 리프노드 갯수 + rchild 리프노드 갯수
			count += getNumOfLeafs(ptr->rchild);
		}
	}
	return count;
}
void deleteNode(treePointer* ptr, int k) {
	int left = 2;//삭제할 노드의 부모노드에서 삭제할 노드가 lchild인지 rchild인지 구분하기위한 변수. 0이면 rchild 1이면 lchild 2면 key값이 없는경우
	treePointer parent = *ptr;//삭제할 노드의 부모 노드
	treePointer temp = NULL;//삭제할 노드
	treePointer next = NULL;//삭제할 노드의 자리로 이동될 노드
	treePointer nextParent = NULL;//이동될 노드의 부모노드

	if (!parent) {//루트가 NULL인경우
		printf("트리가 비었습니다.\n");
		return;
	}
	if (parent->key == k) {//루트가 삭제할 노드인 경우
		temp = parent;
		if (temp->lchild == NULL && temp->rchild == NULL) {//루트가 리프노드일 경우 NULL
			*ptr = NULL;
		}
		else if ((temp->lchild) && temp->rchild == NULL) {//temp가 lchild만 가진 경우 temp->lchild가 루트
			*ptr = temp->lchild;
		}
		else if (temp->lchild == NULL && (temp->rchild)) {//temp가 rchild만 가진 경우 temp->rchild가 루트
			*ptr = temp->rchild;
		}
		else {//temp가 lchild, rchild둘다 가진 경우
			for (next = temp->lchild; next->rchild != NULL; next = next->rchild) {//temp의 key와 가장 가까우면서 작은 값을 가진 next찾기
				nextParent = next;//next의 부모노드 nextParent
			}
			if (!nextParent) {//nextParent가 NULL이라면 temp의 lchild가 next인 경우
				next->rchild = temp->rchild;//next의 rchild는 NULL이므로 여기에 temp의 rchild를 연결
				*ptr = next;//parent에 next연결
			}
			else {
				nextParent->rchild = next->lchild;//nextParent의 rchild는 next인데 next를 temp위치로 옮김으로 next의 lchild를 nextParent의 rchild로
				next->lchild = temp->lchild;//temp의 자식노드를 next의 자식 노드로 변경
				next->rchild = temp->rchild;
				*ptr = next;//parent에 next연결
			}
		}
	}
	else {
		while (parent) {//parent의 자식 노드가 찾는 key값이 될때까지 반복
			if (parent->rchild != NULL && k == parent->rchild->key) {
				left = 0;//parent의 rchild가 key인 경우
				break;
			}
			if (parent->lchild != NULL && k == parent->lchild->key) {
				left = 1;//parent의 lchild가 key인 경우
				break;
			}
			if (k < parent->key) {
				parent = parent->lchild;
			}
			else {
				parent = parent->rchild;
			}
		}
		if (left == 2) {//key값을 찾지 못하고 parent가 NULL이 된경우
			printf("해당 key값이 없습니다.\n");
			return;
		}
		if (left == 1)//parent의 lchild가 key인 경우
			temp = parent->lchild;//temp는 parent의 lchild
		else
			temp = parent->rchild;

		if (temp->lchild==NULL && temp->rchild==NULL) {//temp가 리프노드일 경우 parent다음 NULL
			if (left == 1)
				parent->lchild = NULL;
			else
				parent->rchild = NULL;
		}
		else if ((temp->lchild) && temp->rchild == NULL) {//temp가 lchild만 가진 경우 parent다음 temp->lchild연결
			if (left == 1)
				parent->lchild = temp->lchild;
			else
				parent->rchild = temp->lchild;
		}
		else if (temp->lchild == NULL && (temp->rchild)) {//temp가 rchild만 가진 경우 parent다음 temp->rchild연결
			if (left == 1)
				parent->lchild = temp->rchild;
			else
				parent->rchild = temp->rchild;
		}
		else {//temp가 lchild, rchild둘다 가진 경우
			for (next = temp->lchild; next->rchild != NULL; next = next->rchild) {//temp의 key와 가장 가까우면서 작은 값을 가진 next찾기
				nextParent = next;//next의 부모노드 nextParent
			}
			if (!nextParent) {//nextParent가 NULL이라면 temp의 lchild가 next인 경우
				next->rchild = temp->rchild;//next의 rchild는 NULL이므로 여기에 temp의 rchild를 연결
				if (left == 1)
					parent->lchild = next;//parent에 next연결
				else
					parent->rchild = next;
			}
			else {
				nextParent->rchild = next->lchild;//nextParent의 rchild는 next인데 next를 temp위치로 옮김으로 next의 lchild를 nextParent의 rchild로
				next->lchild = temp->lchild;//next의 자식 노드를 temp의 자식노드로
				next->rchild = temp->rchild;
				if (left == 1)
					parent->lchild = next;//parent에 next연결
				else
					parent->rchild = next;
			}
		}
	}
	printf("(%d, %.3lf)노드를 삭제합니다.\n", temp->key, temp->value);
	retNode(temp);
	return;
}