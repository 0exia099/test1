#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:28182)

//@file : main.cpp
/*�׷����� ��� ���� ���� ����(��������, ���� ����, ����ġ)�� �Է� �޾�
* ������ķ� �׷����� ǥ���ϰ� shortestPath�Լ��� ���� ���� ��������� �ִܰ��,
allcosts�Լ��� ���� ��� ���� �ִ� ��θ� ����Ѵ�.
���� �׷����� �ǽ��� �� �ְ� �ݺ����� ���� ���α׷� ���� ���� �׷����� ������ �Է¹��� �� �ִ�.
*/

#include <stdio.h>
#include <stdlib.h>

void shortestPath(int v, int **graph, int distance[], int n, short int found[]);
int choose(int distance[], int n, short int found[]);
void allcosts(int** graph, int** distance, int n);

int main() {
	int num = 6, i, j;
	int v1, v2, w;
	int** graph;//�׷��� �������ǥ���� ���� ����
	int* distance;//shortestPath�� ����� ������ ����
	int** all_distance;//allcosts�� ����� ������ ����
	short int* found;

	printf("���� �׷����� Ȯ���ϱ� ���Ͽ� �׷����� �Է� ���� ��\nshortestPath(), allCost()���� ����ϰ� �ٽ� �׷��� �Է¹���.\n");
	
	while (true) {//���� �׷��� Ȯ���� ���� �ݺ���
		printf("��� ���� �Է��� �ּ���.(-1�Է½� ����)>>");
		if (scanf("%d", &num) != 1) {
			printf("�Է½���\n");
			exit(1);
		}
		if (num == -1)
			break;

		//graph[][]�����Ҵ�
		graph = (int**)malloc(sizeof(int*) * num);
		if (graph == NULL) {
			fprintf(stderr, "The memory is full\n");
			exit(1);
		}
		for (i = 0; i < num; i++) {
			graph[i] = (int*)malloc(sizeof(int) * num);
			if (graph[i] == NULL) {
				fprintf(stderr, "The memory is full\n");
				exit(1);
			}
		}

		distance = (int*)malloc(sizeof(int) * num);//distance�����Ҵ�
		if (distance == NULL) {
			fprintf(stderr, "The memory is full\n");
			exit(1);
		}

		//all_distance[][]�����Ҵ�
		all_distance = (int**)malloc(sizeof(int*) * num);
		if (all_distance == NULL) {
			fprintf(stderr, "The memory is full\n");
			exit(1);
		}
		for (i = 0; i < num; i++) {
			all_distance[i] = (int*)malloc(sizeof(int) * num);
			if (all_distance[i] == NULL) {
				fprintf(stderr, "The memory is full\n");
				exit(1);
			}
		}

		found = (short int*)malloc(sizeof(short int) * num);//found�����Ҵ�
		if (found == NULL) {
			fprintf(stderr, "The memory is full\n");
			exit(1);
		}

		for (i = 0; i < num; i++) {//graph��� �ʱ�ȭ
			for (j = 0; j < num; j++) {
				if (i == j)//�ڱ��ڽ��� ����ġ 0
					graph[i][j] = 0;
				else
					graph[i][j] = 9999;//���Ѵ� ��� 9999
			}
		}

		printf("���� ����(��������, ���� ����, ����ġ)�� �Է��� �ּ���.\n***-1 -1 -1�Է½� ����.***\n");
		while (true) {//-1 -1 -1�Է½ñ��� ���� ���� �Է¹���
			scanf("%d %d %d", &v1, &v2, &w);
			if (v1 == -1 && v2 == -1 && w == -1)
				break;
			graph[v1][v2] = w;//graph��Ŀ� ����
		}

		printf("�Է¹��� �׷��� ������ķ� ǥ��\n");
		for (i = 0; i < num; i++) {//graph������� ���
			for (j = 0; j < num; j++) {
				if (graph[i][j] == 9999)
					printf("-\t");
				else
					printf("%d\t", graph[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		while (true) {//shortestPath�Լ� ����
			printf("shortestPath()�� ���۳�带 �Է��� �ּ���. -1�Է½� �ݺ� ����.\n");
			if (scanf("%d", &v1) != 1) {
				printf("�Է½���\n");
				exit(1);
			}
			if (v1 == -1)
				break;
			printf("shortestPath().���۳�� : %d\n", v1);
			shortestPath(v1, graph, distance, num, found);
			for (i = 0; i < num; i++) {//��� ���
				if (distance[i] == 9999)
					printf("-\t");
				else
					printf("%d\t", distance[i]);
			}
			printf("\n");
		}
		printf("\n");

		printf("allCost()\n");
		allcosts(graph, all_distance, num);//allcosts�Լ� ����
		for (i = 0; i < num; i++) {//��� ���
			for (j = 0; j < num; j++) {
				if (all_distance[i][j] == 9999)
					printf("-\t");
				else
					printf("%d\t", all_distance[i][j]);
			}
			printf("\n");
		}

		//�����Ҵ� ����
		free(distance);
		free(found);
		for (i = 0; i < num; i++) {
			free(graph[i]);
		}
		free(graph);
		for (i = 0; i < num; i++) {
			free(all_distance[i]);
		}
		free(all_distance);
	}//��ü �ݺ��� ����
	system("PAUSE");//�������Ͽ��� �ٷ� ����Ǵ� ���� �������� �Ͻ�����
}

void shortestPath(int v, int **graph, int distance[], int n, short int found[]) {
	int i, u, w;
	for (i = 0; i < n; i++) {
		found[i] = 0;//found�ʱ�ȭ
		distance[i] = graph[v][i];//distance�� �ʱⰪ�� graph�� �ʱ�ȭ
	}
	//���۰��� found, distance�� ����
	found[v] = 1;
	distance[v] = 0;
	for (i = 0; i < n - 1; i++) {
		u = choose(distance, n, found);//����ġ ������ ã��
		found[u] = 1;
		for (w = 0; w < n; w++)
			if (found[w] == 0)
				if (distance[u] + graph[u][w] < distance[w])//u���� w���� ��ΰ� �ٷ� w�� ���� ��κ��� ����ġ ������
					distance[w] = distance[u] + graph[u][w];//���� ������ ����
	}
}
int choose(int distance[], int n, short int found[]) {
	int i, min, minpos;

	min = INT_MAX;
	minpos = -1;
	for(i=0;i<n;i++)
		if (distance[i] < min && found[i] == 0) {//���� ���� ���� �� �� ����ġ ������ ã�� 
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
void allcosts(int** graph, int** distance, int n) {
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			distance[i][j] = graph[i][j];//distance �ʱ�ȭ
	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (distance[i][k] + distance[k][j] < distance[i][j])//i->k->j�� ����ġ�� i->j�� ����ġ �� ������ ����
					distance[i][j] = distance[i][k] + distance[k][j];
}