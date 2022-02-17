#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:28182)

#pragma warning(disable:6386)
#pragma warning(disable:6385)
#pragma warning(disable:6011)

//@file : main.cpp
/*����(���)�� ���� ���� ������ �Է¹޾� ���� ����Ʈ�� ���·� �����⼺ �׷����� ����� �ڵ�
find_mostDegree�Լ��� ���� �ϼ��� ���� ����Ʈ���� degree�� ���� ū ��带 ã�´�.
DFS, BFS�� ���� �׷����� �⺻ ������ Ž���� �����Ѵ�.
DFS_spanning_tree, BFS_spanning_tree�Լ��� ���� DFS��� ����Ʈ��, BFS��� ����Ʈ���� ����Ѵ�.
*/

#include <stdio.h>
#include <stdlib.h>

struct node {
	int vertex;
	struct node* next;
};

int	num;//���� ���� �Է¹��� ����
struct node** graph;//���� ����Ʈ�� ��带 ���� ���� �迭
bool* visited;//�湮 Ȯ���� ���� �迭

int* queue;//BFS���� �� ť
int front = -1;
int rear = -1;

void insert_front(struct node** start, int data);//���Ḯ��Ʈ �տ� �߰��ϴ� �Լ�

int find_mostDegree();//degree�� ���� ū ��� ã�� �Լ�

void addq(int data);//ť�� add
int deleteq();//ť�� delete

void DFS(int v);//����Լ� ��� DFS
void BFS(int v);//ť ��� BFS

void DFS_spanning_tree(int v);//DFS ����Ʈ�� ��� �Լ�
void BFS_spanning_tree(int v);//BFS ����Ʈ�� ��� �Լ�

int main() {
	int v1 = 0, v2 = 0;
	int i;
	struct node* ptr = NULL;
	struct node* temp = NULL;

	printf("�׷������� ������ ������ �Է��� �ּ���\n");
	scanf("%d", &num);

	graph = (struct node**)malloc(sizeof(struct node*) * num);//���� ���� ��ŭ �迭 ����
	if (graph == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	for (i = 0; i < num; i++)//graph�迭 �ʱ�ȭ
		graph[i] = NULL;

	visited = (bool*)malloc(sizeof(bool) * num);//���� ���� ��ŭ �迭 ����
	if (visited == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	for (i = 0; i < num; i++)//visited���� false�� �ʱ�ȭ
		visited[i] = false;

	queue = (int*)malloc(sizeof(int) * (num));//���� ���� ��ŭ�� ũ�� ť ����
	if (queue == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	printf("���� ������ �Է��� �ּ���.-1 -1�Է½� ����.\n");
	while (true) {//-1 -1 �Է½ñ��� ���� ���� �Է¹���
		scanf("%d %d", &v1, &v2);
		if (v1 == -1 && v2 == -1)
			break;
		insert_front(&graph[v1], v2);//������ ������� ���Ḯ��Ʈ�� �߰��Ͽ� ��������Ʈ ����
		insert_front(&graph[v2], v1);//���� ���� �Ѵٿ� ����
	}
	for (i = 0; i < num; i++) {//������ ä������� ����� �׷��� ���
		printf("%d�� ����� ������ ����Ʈ ��� : ", i);
		for (ptr = graph[i]; ptr != NULL; ptr = ptr->next) {
			printf("%d ", ptr->vertex);
		}
		printf("\n");
	}
	v1 = find_mostDegree();//degree���� ū ����� ��ȣ
	printf("degree�� ���� ū ��� : %d\n", v1);
	printf("degree�� ���� ū ��忡 ����� ������ ����Ʈ ��� : ");
	for (ptr = graph[v1]; ptr != NULL; ptr = ptr->next) {
		printf("%d ", ptr->vertex);
	}

	printf("\n\n���� �켱 Ž��(DFS)");
	printf("\n���۳�� : 0\n");
	for (i = 0; i < num; i++)//DFS�� ���� visited�ʱ�ȭ
		visited[i] = false;
	DFS(0);
	printf("\n���۳�� : 2\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	DFS(2);
	printf("\n���۳�� : 4\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	DFS(4);

	printf("\n\n�ʺ� �켱 Ž��(BFS)");
	printf("\n���۳�� : 1\n");
	for (i = 0; i < num; i++)//BFS�� ���� visited�ʱ�ȭ
		visited[i] = false;
	BFS(1);
	printf("\n���۳�� : 3\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	BFS(3);
	printf("\n���۳�� : 5\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	BFS(5);

	printf("\n\nDFS����Ʈ��");
	printf("\n���۳�� : 0\n");
	for (i = 0; i < num; i++)//DFS����Ʈ���� ���� visited�ʱ�ȭ
		visited[i] = false;
	DFS_spanning_tree(0);
	printf("\n���۳�� : 2\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	DFS_spanning_tree(2);
	printf("\n���۳�� : 4\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	DFS_spanning_tree(4);

	printf("\n\nBFS����Ʈ��");
	printf("\n���۳�� : 1\n");
	for (i = 0; i < num; i++)//BFS����Ʈ���� ���� visited�ʱ�ȭ
		visited[i] = false;
	BFS_spanning_tree(1);
	printf("\n���۳�� : 3\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	BFS_spanning_tree(3);
	printf("\n���۳�� : 5\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	BFS_spanning_tree(5);
	printf("\n");

	//�����Ҵ� ����
	free(queue);
	free(visited);
	for (i = 0; i < num; i++) {
		for (ptr = graph[i]; ptr != NULL; ptr = temp) {
			temp = ptr->next;
			free(ptr);
		}
	}
	free(graph);

	system("PAUSE");//�������Ͽ��� �ٷ� ����Ǵ� ���� �������� �Ͻ�����
	return 0;
}
void insert_front(struct node** start, int data) {
	struct node* temp;
	temp = (struct node*)malloc(sizeof(struct node));
	if (temp == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	temp->vertex = data;
	if (start != NULL)//graph�迭�� ����� ��� ������ start�� temp->next��
		temp->next = *start;
	else//������ ó�� �����ϴ� ���̴� NULL;
		temp->next = NULL;
	*start = temp;
	return;
}
int find_mostDegree() {
	int i;
	int count = 0;
	int most = 0;
	int node = -1;
	struct node* ptr;

	for (i = 0; i < num; i++) {
		count = 0;
		for (ptr = graph[i]; ptr != NULL; ptr = ptr->next) {
			count++;//�� ������ degree���� count�� ����.
		}
		if (count > most) {//���ݱ��� degree���� ���� ū�ź��� Ŭ ���
			most = count;
			node = i;//degree���� ���� ū ������ ��ȣ ����
		}
	}
	return node;
}
void addq(int data) {
	if (rear == num - 1) {
		printf("ť�� ���� á���ϴ�.\n");
		exit(1);
	}
	queue[++rear] = data;
}
int deleteq() {
	if (rear == front) {
		printf("ť�� ������ϴ�.\n");
		exit(1);
	}
	return queue[++front];
}
void DFS(int v) {
	struct node* w;
	visited[v] = true;
	printf("%5d", v);
	for (w = graph[v]; w; w = w->next)
		if (!visited[w->vertex])
			DFS(w->vertex);
}
void BFS(int v) {
	struct node* w;
	front = rear = -1;//ť����� ���� front�� rear�ʱ�ȭ
	printf("%5d", v);
	visited[v] = true;
	addq(v);
	while (front != rear) {//ť�� �������� �ݺ�
		v = deleteq();
		for (w = graph[v]; w; w = w->next)
			if (!visited[w->vertex]) {
				printf("%5d", w->vertex);
				addq(w->vertex);
				visited[w->vertex] = true;
			}
	}
}
void DFS_spanning_tree(int v) {
	struct node* w;
	visited[v] = true;
	for (w = graph[v]; w; w = w->next)
		if (!visited[w->vertex]) {//w->vertex�� �湮 �� ���� �������
			printf("(%d,%d)", v, w->vertex);//v�� w->vertex�� ���������� ���
			DFS_spanning_tree(w->vertex);
		}
}
void BFS_spanning_tree(int v) {
	struct node* w;
	front = rear = -1;
	visited[v] = true;
	addq(v);
	while (front != rear) {
		v = deleteq();
		for (w = graph[v]; w; w = w->next)
			if (!visited[w->vertex]) {//w->vertex�� �湮 �� ���� �������
				printf("(%d,%d)", v, w->vertex);//v�� w->vertex�� ���������� ���
				addq(w->vertex);
				visited[w->vertex] = true;
			}
	}
}