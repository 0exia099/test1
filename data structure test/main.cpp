#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:28182)

//@file : main.cpp
/*tree�� ����ü�� ����� ���Ḯ��Ʈ�� ǥ���ϴ� �ڵ�
�����帮��Ʈ�� ����Ͽ� malloc�� free�� �ּ�ȭ�Ѵ�.
inorder, preordcer, postorder���� tree�� ǥ���ϴ� ��ȸ �Լ��� ����
tree�� ����ϰ� tree�� �����ϴ� copy�Լ�, �¿츦 �ٲپ� �����ϴ� swap�Լ��� ����Ͽ�
tree�� ������ �� ��ȸ �Լ��� ����ϰ� �� tree�� ������ Ȯ���ϴ� equal�Լ��� �̿��Ͽ� ���Ѵ�.
�������� tree�� ����� make_tree_rand�Լ��� ���Ͽ� tree�� ����� ��ȸ �Լ��� ����Ѵ�.
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

nodeP avail = NULL;//�����帮��Ʈ�� �̿��ϱ� ���� avail
//������ ����Ʈ�� ���� �Լ�
nodeP getNode();
void retNode(nodeP temp);
void erase_tree(nodeP ptr);//Ʈ���� avail�� �߰��ϴ� �Լ�
void freeAvail();//avail�� ��� ��带 free�ϴ� �Լ�

nodeP make_tree_by_code();//���ǿ� ���� ��Ʈ�� 5�� Ʈ���� ����� �Լ�
void inorder(nodeP ptr);
void preorder(nodeP ptr);
void postorder(nodeP ptr);
nodeP copy(nodeP ptr);
bool equal(nodeP ptr1, nodeP ptr2);
nodeP swap(nodeP ptr);
nodeP make_tree_rand();//�������� tree�� ����� �Լ�

int main() {
	nodeP A, B, C;
	A = B = C = NULL;

	A = make_tree_by_code();//���ǿ� ���� ��Ʈ�� 5�� Ʈ��
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
	equal(A, B) ? printf("A�� B�µ����մϴ�.\n\n") : printf("A�� B�� �����մϴ�.\n\n");//equal�Լ��� ���ϰ��� ���� ���

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
	equal(A, C) ? printf("A�� C�� �����մϴ�.\n\n") : printf("A�� C�� �����մϴ�.\n\n");

	//�����ϴ� Ʈ�� �����帮��Ʈ�� �̵�
	erase_tree(A);
	erase_tree(B);
	erase_tree(C);

	A = make_tree_rand();
	printf("�������� tree :\n");
	printf("inorder : ");
	inorder(A);
	printf("\npreorder : ");
	preorder(A);
	printf("\npostorder : ");
	postorder(A);
	printf("\n\n");

	//�������� ���� Ʈ�� �����帮��Ʈ�� �̵� �� ������ ����Ʈ free
	erase_tree(A);
	freeAvail();

	system("PAUSE");//�������Ͽ��� �ٷ� ����Ǵ� ���� �������� �Ͻ�����
	return 0;
}
nodeP getNode() {
	nodeP temp;
	if (avail != NULL) {//avail�� ��尡 ������ �� ��带 ��ȯ
		temp = avail;
		avail = avail->rchild;//rchild�� link�� ���
	}
	else {//������ malloc
		temp = (nodeP)malloc(sizeof(*temp));
		if (!temp) {//�Ҵ� ���� �� ����
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
void erase_tree(nodeP ptr) {//tree�� ����ϴ� ���Ḯ��Ʈ�� �������Ḯ��Ʈ�� �ƴϹǷ� �ϳ��� avail�� �̵�.
	if (ptr) {
		//����Լ��� postorder����� ����Ͽ� avail�� �̵�
		erase_tree(ptr->lchild);
		erase_tree(ptr->rchild);
		retNode(ptr);
	}
}
void freeAvail() {
	nodeP ptr;

	for (; avail != NULL;) {//avail�� ��� ��� free
		ptr = avail;
		avail = avail->rchild;
		free(ptr);
	}
}
nodeP make_tree_by_code() {

	nodeP temp5 = getNode();//data�� 4�� ���
	temp5->data = 4;
	temp5->lchild = NULL;
	temp5->rchild = NULL;

	nodeP temp4 = getNode();//data�� 1�� ���
	temp4->data = 1;
	temp4->lchild = NULL;
	temp4->rchild = NULL;

	nodeP temp3 = getNode();//data�� 8�� ���
	temp3->data = 8;
	temp3->lchild = NULL;
	temp3->rchild = NULL;

	nodeP temp2 = getNode();//data�� 3�� ���
	temp2->data = 3;
	temp2->lchild = temp4;
	temp2->rchild = temp5;

	nodeP temp1 = getNode();//data�� 5�� ���
	temp1->data = 5;
	temp1->lchild = temp2;
	temp1->rchild = temp3;
	
	return temp1;
}

void inorder(nodeP ptr) {
	if (ptr) {
		inorder(ptr->lchild);
		printf("%d ", ptr->data);//lchild���� ���� ���
		inorder(ptr->rchild);
	}
}
void preorder(nodeP ptr) {
	if (ptr) {
		printf("%d ", ptr->data);//���� ��� ���� lchild
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}
void postorder(nodeP ptr) {
	if (ptr) {
		postorder(ptr->lchild);
		postorder(ptr->rchild);
		printf("%d ", ptr->data);//lchild, rchild ���� ���� ���
	}
}

nodeP copy(nodeP ptr) {
	nodeP temp;
	if (ptr) {
		temp = getNode();
		temp->lchild = copy(ptr->lchild);//ptr�� lchild�� �������� ���� ����
		temp->rchild = copy(ptr->rchild);//ptr�� rchild�� �������� ���� ����
		temp->data = ptr->data;//ptr����
		return temp;
	}
	else
		return NULL;
}

bool equal(nodeP ptr1, nodeP ptr2) {
	//�Ѵ� NULL�̰ų� (�Ѵ� NULL�� �ƴϰ� ��Ʈ�� data�� ���� ��Ʈ�� ���������� ���� ���� ���)����.
	return((!ptr1 && !ptr2) || (ptr1 && ptr2 && (ptr1->data == ptr2->data) && equal(ptr1->lchild, ptr2->lchild) && equal(ptr1->rchild, ptr2->rchild)));
}

nodeP swap(nodeP ptr) {
	nodeP temp;
	if (ptr) {
		temp = getNode();
		temp->lchild = swap(ptr->rchild);//ptr�� rchild���� �����Ͽ� �¿� ����
		temp->rchild = swap(ptr->lchild);//ptr�� lchild���� �����Ͽ� �¿� ����
		temp->data = ptr->data;//��Ʈ�� �¿찡 �����Ƿ� �״��
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
	
	printf("���� Ʈ���� ��� ������ �Է��ϼ��� : ");
	scanf("%d", &num);//��� ���� �Է�
	if (num == 0) {//0���ΰ�� NULL�� tree
		return temp;
	}
	temp = getNode();
	temp->data = 1;//1�� ��Ʈ���
	temp->lchild = NULL;
	temp->rchild = NULL;
	srand((unsigned int)time(NULL));

	for (i = 2; i <= num; i++) {//2���� num���� ��� ����
		ptr = temp;//��Ʈ��� ���� �Ʒ��� Ž��
		tree_node = getNode();//������ ���
		tree_node->data = i;
		tree_node->lchild = NULL;
		tree_node->rchild = NULL;
		while (true) {
			count = rand() % 2;//count�� 0�̸� ���� 1�̸� ������
			if (count == 0) {
				if (ptr->lchild)//���� ����� lchild�� NULL�� �ƴϸ� lchild�� ������
					ptr = ptr->lchild;
				else {//lchild�� NULL�̸� ������ ��� ����
					ptr->lchild = tree_node;
					break;//while�� break
				}
			}
			else {
				if (ptr->rchild)//���� ����� rchild�� NULL�� �ƴϸ� rchild�� ������
					ptr = ptr->rchild;
				else {//rchild�� NULL�̸� ������ ��� ����
					ptr->rchild = tree_node;
					break;//while�� break
				}
			}
		}
	}
	
	return temp;
}