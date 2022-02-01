#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:28182)

//@file : main.cpp
/*����Ž��Ʈ���� ����ü�� ����� ���Ḯ��Ʈ�� ǥ���ϴ� �ڵ�
�����帮��Ʈ�� ����Ͽ� malloc�� free�� �ּ�ȭ�Ѵ�.
insert�Լ��� ���Ͽ� ���ο� ��带 ����Ž��Ʈ���� �߰��Ѵ�.
inorder�� ������ Ʈ���� ����ϰ� iterSearch�Լ��� ���Ͽ� ������ Ʈ������ �˻��� �� �� �ִ�.
make_bst�Լ��� �̿��Ͽ� �Է¹��� n�� ������ŭ ��带 �����Ͽ� ����Ž��Ʈ���� ����� ���� ����ð��� �����Ѵ�.
getNumOfNodes, treeHeight_root, treeHeight, getNumOfLeafs �Լ��� �̿��Ͽ� ����, Ʈ�� ����, ���������� ����Ѵ�.
deleteNode�Լ��� ���Ͽ� ����Ž��Ʈ���� ������ �����ϸ� �ϳ��� ��带 �����Ѵ�.
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

treePointer avail = NULL;//�����帮��Ʈ�� �̿��ϱ� ���� avail
//������ ����Ʈ�� ���� �Լ�
treePointer getNode();
void retNode(treePointer temp);
void erase_tree(treePointer ptr);//Ʈ���� avail�� �߰��ϴ� �Լ�
void freeAvail();//avail�� ��� ��带 free�ϴ� �Լ�

void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

void insert(treePointer* node, int k, double v);
treePointer modifiedSearch(treePointer node, int k);
treePointer iterSearch(treePointer tree, int k);
treePointer make_bst(int n);

int getNumOfNodes(treePointer ptr);
int treeHeight_root(treePointer ptr);//��Ʈ�� ������ ���ڿ� �������� �ʱ����� �����Լ�
int treeHeight(treePointer ptr);
int getNumOfLeafs(treePointer ptr);

void deleteNode(treePointer* ptr, int k);

int main() {
	int i;
	int key[10] = { 5, 3, 8, 1,9,2,7,10,6,4 };//������ �ִ� key�Է¼���
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

	while (true) {//-1�Է½ñ��� �˻�
		printf("\nã���� key���� �Է��� �ּ���.(-1�Է� �� �˻� ����)>>");
		scanf("%d", &n);
		if (n == -1)
			break;
		temp = iterSearch(A, n);
		if (!temp) {//iterSearch���� NULL������ ��� ���ڷ� �ѱ� Ʈ���� NULL�̰ų� �ش� key���� ���� ���.
			printf("�Է��Ͻ� key���� �������� �ʽ��ϴ�.\n");//�� ���� key���� �������� �ʴ´�.
		}
		else {
			printf("�Է��Ͻ� key���� value : (%d, %.3lf)\n", temp->key, temp->value);
		}
	}
	erase_tree(A);//������ ����Ʈ�� �̵�
	A = NULL;

	while (true) {//-1�Է½ñ��� n���� ��带 ���� Ʈ�� ����
		printf("\n����� ���� Ž�� Ʈ���� ��� ���� �Է��� �ּ���.(-1�Է½� Ʈ�� ���� ����)>>");
		scanf("%d", &n);
		if (n == -1)
			break;
		start = (double)clock();
		A = make_bst(n);
		stop = (double)clock();
		/*printf("inorder : ");//��� ���� ��½� ���������� ����� ��
		inorder(A);
		printf("\n");*/
		printf("Ʈ�� ���� �ð� : %.3lf\n", (stop - start)/CLOCKS_PER_SEC);
		printf("��� �� : %d\n", getNumOfNodes(A));
		printf("Ʈ�� ���� : %d\n", treeHeight_root(A));
		printf("���� ��� �� : %d\n", getNumOfLeafs(A));

		erase_tree(A);//������ ����Ʈ�� �̵�
		A = NULL;
	}

	for (i = 0; i < 10; i++) {//������ �ִ� Ʈ���� Ȱ���Ͽ� �����Լ� �׽�Ʈ
		insert(&A, key[i], 1.0 / key[i]);
	}
	printf("inorder : ");
	inorder(A);
	printf("\n");
	printf("preorder : ");//���� �Լ� ���� �� Ʈ�� ����� Ȯ���ϱ� ���� preorder, postorder���
	preorder(A);
	printf("\n");
	printf("postorder : ");
	postorder(A);
	printf("\n");
	printf("��� �� : %d\n", getNumOfNodes(A));
	printf("Ʈ�� ���� : %d\n", treeHeight_root(A));
	printf("���� ��� �� : %d\n", getNumOfLeafs(A));
	while (true) {//-1�Է½� ���� ��� ����
		printf("\n������ ����� key�� �Է��� �ּ���.(-1�Է½� ����)>>");
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
		printf("��� �� : %d\n", getNumOfNodes(A));
		printf("Ʈ�� ���� : %d\n", treeHeight_root(A));
		printf("���� ��� �� : %d\n", getNumOfLeafs(A));
	}

	erase_tree(A);//������ ����Ʈ�� �̵�
	freeAvail();//������ ����Ʈ ��ü ��ȯ

	system("PAUSE");//�������Ͽ��� �ٷ� ����Ǵ� ���� �������� �Ͻ�����
	return 0;
}
treePointer getNode() {
	treePointer temp;
	if (avail != NULL) {//avail�� ��尡 ������ �� ��带 ��ȯ
		temp = avail;
		avail = avail->rchild;//rchild�� link�� ���
	}
	else {//������ malloc
		temp = (treePointer)malloc(sizeof(*temp));
		if (!temp) {//�Ҵ� ���� �� ����
			fprintf(stderr, "Insufficient memory");
			exit(EXIT_FAILURE);
		}
	}
	return temp;
}
void retNode(treePointer temp) {//��� �ϳ� avail�� �̵�
	temp->rchild = avail;
	avail = temp;
	return;
}
void erase_tree(treePointer ptr) {//tree�� ����ϴ� ���Ḯ��Ʈ�� �������Ḯ��Ʈ�� �ƴϹǷ� �ϳ��� avail�� �̵�.
	if (ptr) {
		//����Լ��� postorder����� ����Ͽ� avail�� �̵�
		erase_tree(ptr->lchild);
		erase_tree(ptr->rchild);
		retNode(ptr);
	}
}
void freeAvail() {
	treePointer ptr;

	for (; avail != NULL;) {//avail�� ��� ��� free
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
	treePointer ptr, temp = modifiedSearch(*node, k);//modifiedSearch�Լ��� k�� �� �θ��� ã��
	if (temp || !(*node)) {//temp���� �ְų� node�� NULL�ΰ��->�̹� k�� key�� �ִ� ��� ����
		ptr = getNode();//������ ���
		/*ptr = (treePointer)malloc(sizeof(*ptr));
		if (!ptr) {
			fprintf(stderr, "Insufficient memory");
			exit(EXIT_FAILURE);
		}*/
		ptr->key = k;
		ptr->value = v;
		ptr->lchild = ptr->rchild = NULL;
		if (*node)
			if (k < temp->key)//�θ��庸�� ũ�� rchild ������lchild
				temp->lchild = ptr;
			else
				temp->rchild = ptr;
		else
			*node = ptr;
	}
}
treePointer modifiedSearch(treePointer node, int k) {//k�� �� NULL�ڸ��� �θ��� ã�� �Լ�
	for (treePointer ptr = node; ptr != NULL;) {
		if (ptr->key == k)//key���� �ִ°��
			return NULL;
		if (k < ptr->key) {//key���� k�� ������ ����
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
	return NULL;//��Ʈ�� NULL�ΰ��
}
treePointer iterSearch(treePointer tree, int k) {
	int count = 1;//iterSearch�� �̹� �ҷ������Ƿ� 1���� ����
	while (tree) {
		if (k == tree->key) {
			printf("search �ݺ� Ƚ�� : %d\n", count);//iterSearch�̱� ������ �Լ� ȣ��Ƚ���� �ƴ� �ݺ� Ƚ���� ���
			return tree;
		}
		if (k < tree->key)
			tree = tree->lchild;
		else
			tree = tree->rchild;
		count++;
	}
	printf("search �ݺ� Ƚ�� : %d\n", count);//iterSearch�̱� ������ �Լ� ȣ��Ƚ���� �ƴ� �ݺ� Ƚ���� ���
	return NULL;
}
treePointer make_bst(int n) {
	treePointer temp = NULL;
	int key;
	double value;
	int i;

	for (i = 0; i < n; i++) {//n����ŭ key�� value ���� �� insert�Լ��� ��� ����
		key = (int)((rand() / (0x7fff * 1.0)) * 100000000);
		value = 1.0 / key;
		insert(&temp, key, value);
	}
	return temp;
}
int getNumOfNodes(treePointer ptr) {
	int count = 0;
	if (ptr) {
		//lchild ��� ���� + �ڽ� + rchild ��� ����
		count += getNumOfNodes(ptr->lchild);
		count++;
		count += getNumOfNodes(ptr->rchild);
	}
	return count;
}
int treeHeight_root(treePointer ptr) {//��Ʈ�� ���̿� ������ ���� �ʱ⶧���� +1�� ���� ��
	int height = 0;
	int l, r;
	l = r = 0;
	if (ptr)
	{
		l = treeHeight(ptr->lchild);//�Լ�ȣ�� ���̱� ���Ͽ� ������ �� ����.
		r = treeHeight(ptr->rchild);
		height = ((l > r) ? l : r);//��Ʈ�� �������� �������� lchild, rchild�� ū ��
	}
	return height;
}
int treeHeight(treePointer ptr) {//��Ʈ �̿ܿ��� +1�� ���
	int height = 0;
	int l, r;
	l = r = 0;
	if (ptr)
	{
		l = treeHeight(ptr->lchild);//�Լ�ȣ�� ���̱� ���Ͽ� ������ �� ����.
		r = treeHeight(ptr->rchild);
		height = 1 + ((l > r) ? l : r);//lchild, rchild�� ū �� +1
	}
	return height;
}
int getNumOfLeafs(treePointer ptr) {
	int count = 0;
	if (ptr)
	{
		if (ptr->lchild == NULL && ptr->rchild == NULL)//��������� 1��ȯ
			return 1;
		else
		{
			count += getNumOfLeafs(ptr->lchild);//lchild�� ������� ���� + rchild ������� ����
			count += getNumOfLeafs(ptr->rchild);
		}
	}
	return count;
}
void deleteNode(treePointer* ptr, int k) {
	int left = 2;//������ ����� �θ��忡�� ������ ��尡 lchild���� rchild���� �����ϱ����� ����. 0�̸� rchild 1�̸� lchild 2�� key���� ���°��
	treePointer parent = *ptr;//������ ����� �θ� ���
	treePointer temp = NULL;//������ ���
	treePointer next = NULL;//������ ����� �ڸ��� �̵��� ���
	treePointer nextParent = NULL;//�̵��� ����� �θ���

	if (!parent) {//��Ʈ�� NULL�ΰ��
		printf("Ʈ���� ������ϴ�.\n");
		return;
	}
	if (parent->key == k) {//��Ʈ�� ������ ����� ���
		temp = parent;
		if (temp->lchild == NULL && temp->rchild == NULL) {//��Ʈ�� ��������� ��� NULL
			*ptr = NULL;
		}
		else if ((temp->lchild) && temp->rchild == NULL) {//temp�� lchild�� ���� ��� temp->lchild�� ��Ʈ
			*ptr = temp->lchild;
		}
		else if (temp->lchild == NULL && (temp->rchild)) {//temp�� rchild�� ���� ��� temp->rchild�� ��Ʈ
			*ptr = temp->rchild;
		}
		else {//temp�� lchild, rchild�Ѵ� ���� ���
			for (next = temp->lchild; next->rchild != NULL; next = next->rchild) {//temp�� key�� ���� �����鼭 ���� ���� ���� nextã��
				nextParent = next;//next�� �θ��� nextParent
			}
			if (!nextParent) {//nextParent�� NULL�̶�� temp�� lchild�� next�� ���
				next->rchild = temp->rchild;//next�� rchild�� NULL�̹Ƿ� ���⿡ temp�� rchild�� ����
				*ptr = next;//parent�� next����
			}
			else {
				nextParent->rchild = next->lchild;//nextParent�� rchild�� next�ε� next�� temp��ġ�� �ű����� next�� lchild�� nextParent�� rchild��
				next->lchild = temp->lchild;//temp�� �ڽĳ�带 next�� �ڽ� ���� ����
				next->rchild = temp->rchild;
				*ptr = next;//parent�� next����
			}
		}
	}
	else {
		while (parent) {//parent�� �ڽ� ��尡 ã�� key���� �ɶ����� �ݺ�
			if (parent->rchild != NULL && k == parent->rchild->key) {
				left = 0;//parent�� rchild�� key�� ���
				break;
			}
			if (parent->lchild != NULL && k == parent->lchild->key) {
				left = 1;//parent�� lchild�� key�� ���
				break;
			}
			if (k < parent->key) {
				parent = parent->lchild;
			}
			else {
				parent = parent->rchild;
			}
		}
		if (left == 2) {//key���� ã�� ���ϰ� parent�� NULL�� �Ȱ��
			printf("�ش� key���� �����ϴ�.\n");
			return;
		}
		if (left == 1)//parent�� lchild�� key�� ���
			temp = parent->lchild;//temp�� parent�� lchild
		else
			temp = parent->rchild;

		if (temp->lchild==NULL && temp->rchild==NULL) {//temp�� ��������� ��� parent���� NULL
			if (left == 1)
				parent->lchild = NULL;
			else
				parent->rchild = NULL;
		}
		else if ((temp->lchild) && temp->rchild == NULL) {//temp�� lchild�� ���� ��� parent���� temp->lchild����
			if (left == 1)
				parent->lchild = temp->lchild;
			else
				parent->rchild = temp->lchild;
		}
		else if (temp->lchild == NULL && (temp->rchild)) {//temp�� rchild�� ���� ��� parent���� temp->rchild����
			if (left == 1)
				parent->lchild = temp->rchild;
			else
				parent->rchild = temp->rchild;
		}
		else {//temp�� lchild, rchild�Ѵ� ���� ���
			for (next = temp->lchild; next->rchild != NULL; next = next->rchild) {//temp�� key�� ���� �����鼭 ���� ���� ���� nextã��
				nextParent = next;//next�� �θ��� nextParent
			}
			if (!nextParent) {//nextParent�� NULL�̶�� temp�� lchild�� next�� ���
				next->rchild = temp->rchild;//next�� rchild�� NULL�̹Ƿ� ���⿡ temp�� rchild�� ����
				if (left == 1)
					parent->lchild = next;//parent�� next����
				else
					parent->rchild = next;
			}
			else {
				nextParent->rchild = next->lchild;//nextParent�� rchild�� next�ε� next�� temp��ġ�� �ű����� next�� lchild�� nextParent�� rchild��
				next->lchild = temp->lchild;//next�� �ڽ� ��带 temp�� �ڽĳ���
				next->rchild = temp->rchild;
				if (left == 1)
					parent->lchild = next;//parent�� next����
				else
					parent->rchild = next;
			}
		}
	}
	printf("(%d, %.3lf)��带 �����մϴ�.\n", temp->key, temp->value);
	retNode(temp);
	return;
}