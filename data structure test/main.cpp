#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:28182)

//@file : main.cpp
/*그래프의 노드 수와 에지 정보(시작정점, 종료 정점, 가중치)를 입력 받아
* 인접행렬로 그래프를 표현하고 shortestPath함수를 통해 단일 출발점에서 최단경로,
allcosts함수를 통해 모든 쌍의 최단 경로를 출력한다.
여러 그래프를 실습할 수 있게 반복문을 통해 프로그램 종료 없이 그래프를 여러번 입력받을 수 있다.
*/

#include <stdio.h>
#include <stdlib.h>

void shortestPath(int v, int **graph, int distance[], int n, short int found[]);
int choose(int distance[], int n, short int found[]);
void allcosts(int** graph, int** distance, int n);

int main() {
	int num = 6, i, j;
	int v1, v2, w;
	int** graph;//그래프 인접행렬표현을 위한 변수
	int* distance;//shortestPath의 결과를 저장할 변수
	int** all_distance;//allcosts의 결과를 저장할 변수
	short int* found;

	printf("여러 그래프를 확인하기 위하여 그래프를 입력 받은 뒤\nshortestPath(), allCost()까지 출력하고 다시 그래프 입력받음.\n");
	
	while (true) {//여러 그래프 확인을 위한 반복문
		printf("노드 수를 입력해 주세요.(-1입력시 종료)>>");
		if (scanf("%d", &num) != 1) {
			printf("입력실패\n");
			exit(1);
		}
		if (num == -1)
			break;

		//graph[][]동적할당
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

		distance = (int*)malloc(sizeof(int) * num);//distance동적할당
		if (distance == NULL) {
			fprintf(stderr, "The memory is full\n");
			exit(1);
		}

		//all_distance[][]동적할당
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

		found = (short int*)malloc(sizeof(short int) * num);//found동적할당
		if (found == NULL) {
			fprintf(stderr, "The memory is full\n");
			exit(1);
		}

		for (i = 0; i < num; i++) {//graph행렬 초기화
			for (j = 0; j < num; j++) {
				if (i == j)//자기자신은 가중치 0
					graph[i][j] = 0;
				else
					graph[i][j] = 9999;//무한대 대신 9999
			}
		}

		printf("에지 정보(시작정점, 종료 정점, 가중치)를 입력해 주세요.\n***-1 -1 -1입력시 종료.***\n");
		while (true) {//-1 -1 -1입력시까지 에지 정보 입력받음
			scanf("%d %d %d", &v1, &v2, &w);
			if (v1 == -1 && v2 == -1 && w == -1)
				break;
			graph[v1][v2] = w;//graph행렬에 저장
		}

		printf("입력받은 그래프 인접행렬로 표현\n");
		for (i = 0; i < num; i++) {//graph인접행렬 출력
			for (j = 0; j < num; j++) {
				if (graph[i][j] == 9999)
					printf("-\t");
				else
					printf("%d\t", graph[i][j]);
			}
			printf("\n");
		}
		printf("\n");

		while (true) {//shortestPath함수 실행
			printf("shortestPath()의 시작노드를 입력해 주세요. -1입력시 반복 종료.\n");
			if (scanf("%d", &v1) != 1) {
				printf("입력실패\n");
				exit(1);
			}
			if (v1 == -1)
				break;
			printf("shortestPath().시작노드 : %d\n", v1);
			shortestPath(v1, graph, distance, num, found);
			for (i = 0; i < num; i++) {//결과 출력
				if (distance[i] == 9999)
					printf("-\t");
				else
					printf("%d\t", distance[i]);
			}
			printf("\n");
		}
		printf("\n");

		printf("allCost()\n");
		allcosts(graph, all_distance, num);//allcosts함수 실행
		for (i = 0; i < num; i++) {//결과 출력
			for (j = 0; j < num; j++) {
				if (all_distance[i][j] == 9999)
					printf("-\t");
				else
					printf("%d\t", all_distance[i][j]);
			}
			printf("\n");
		}

		//동적할당 해제
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
	}//전체 반복문 종료
	system("PAUSE");//실행파일에서 바로 종료되는 것을 막기위한 일시정지
}

void shortestPath(int v, int **graph, int distance[], int n, short int found[]) {
	int i, u, w;
	for (i = 0; i < n; i++) {
		found[i] = 0;//found초기화
		distance[i] = graph[v][i];//distance의 초기값을 graph로 초기화
	}
	//시작값의 found, distance값 변경
	found[v] = 1;
	distance[v] = 0;
	for (i = 0; i < n - 1; i++) {
		u = choose(distance, n, found);//가중치 적은것 찾음
		found[u] = 1;
		for (w = 0; w < n; w++)
			if (found[w] == 0)
				if (distance[u] + graph[u][w] < distance[w])//u갔다 w가는 경로가 바로 w로 가는 경로보다 가중치 적으면
					distance[w] = distance[u] + graph[u][w];//적은 값으로 변경
	}
}
int choose(int distance[], int n, short int found[]) {
	int i, min, minpos;

	min = INT_MAX;
	minpos = -1;
	for(i=0;i<n;i++)
		if (distance[i] < min && found[i] == 0) {//아직 가지 않은 것 중 가중치 적은것 찾기 
			min = distance[i];
			minpos = i;
		}
	return minpos;
}
void allcosts(int** graph, int** distance, int n) {
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			distance[i][j] = graph[i][j];//distance 초기화
	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (distance[i][k] + distance[k][j] < distance[i][j])//i->k->j의 가중치와 i->j의 가중치 중 적은것 저장
					distance[i][j] = distance[i][k] + distance[k][j];
}