#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:28182)

#pragma warning(disable:6386)
#pragma warning(disable:6385)
#pragma warning(disable:6011)

//@file : main.cpp
/*정점(노드)의 수와 에지 정보를 입력받아 인접 리스트의 형태로 무방향성 그래프를 만드는 코드
find_mostDegree함수를 통해 완성된 인접 리스트에서 degree가 가장 큰 노드를 찾는다.
DFS, BFS를 통해 그래프의 기본 연산인 탐색을 실행한다.
DFS_spanning_tree, BFS_spanning_tree함수를 통해 DFS기반 신장트리, BFS기반 신장트리를 출력한다.
*/

#include <stdio.h>
#include <stdlib.h>

struct node {
	int vertex;
	struct node* next;
};

int	num;//정점 수를 입력받을 변수
struct node** graph;//인접 리스트의 헤드를 위한 정점 배열
bool* visited;//방문 확인을 위한 배열

int* queue;//BFS에서 쓸 큐
int front = -1;
int rear = -1;

void insert_front(struct node** start, int data);//연결리스트 앞에 추가하는 함수

int find_mostDegree();//degree가 가장 큰 노드 찾는 함수

void addq(int data);//큐의 add
int deleteq();//큐의 delete

void DFS(int v);//재귀함수 사용 DFS
void BFS(int v);//큐 사용 BFS

void DFS_spanning_tree(int v);//DFS 신장트리 출력 함수
void BFS_spanning_tree(int v);//BFS 신장트리 출력 함수

int main() {
	int v1 = 0, v2 = 0;
	int i;
	struct node* ptr = NULL;
	struct node* temp = NULL;

	printf("그래프에서 정점의 갯수를 입력해 주세요\n");
	scanf("%d", &num);

	graph = (struct node**)malloc(sizeof(struct node*) * num);//정점 갯수 만큼 배열 생성
	if (graph == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	for (i = 0; i < num; i++)//graph배열 초기화
		graph[i] = NULL;

	visited = (bool*)malloc(sizeof(bool) * num);//정점 갯수 만큼 배열 생성
	if (visited == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	for (i = 0; i < num; i++)//visited전부 false로 초기화
		visited[i] = false;

	queue = (int*)malloc(sizeof(int) * (num));//정점 갯수 만큼의 크기 큐 생성
	if (queue == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}
	printf("에지 정보를 입력해 주세요.-1 -1입력시 종료.\n");
	while (true) {//-1 -1 입력시까지 에지 정보 입력받음
		scanf("%d %d", &v1, &v2);
		if (v1 == -1 && v2 == -1)
			break;
		insert_front(&graph[v1], v2);//에지의 정보대로 연결리스트에 추가하여 인접리스트 구성
		insert_front(&graph[v2], v1);//양쪽 정점 둘다에 연결
	}
	for (i = 0; i < num; i++) {//보고서를 채우기위해 연결된 그래프 출력
		printf("%d에 연결된 노드들의 리스트 출력 : ", i);
		for (ptr = graph[i]; ptr != NULL; ptr = ptr->next) {
			printf("%d ", ptr->vertex);
		}
		printf("\n");
	}
	v1 = find_mostDegree();//degree가장 큰 노드의 번호
	printf("degree가 가장 큰 노드 : %d\n", v1);
	printf("degree가 가장 큰 노드에 연결된 노드들의 리스트 출력 : ");
	for (ptr = graph[v1]; ptr != NULL; ptr = ptr->next) {
		printf("%d ", ptr->vertex);
	}

	printf("\n\n깊이 우선 탐색(DFS)");
	printf("\n시작노드 : 0\n");
	for (i = 0; i < num; i++)//DFS를 위해 visited초기화
		visited[i] = false;
	DFS(0);
	printf("\n시작노드 : 2\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	DFS(2);
	printf("\n시작노드 : 4\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	DFS(4);

	printf("\n\n너비 우선 탐색(BFS)");
	printf("\n시작노드 : 1\n");
	for (i = 0; i < num; i++)//BFS를 위해 visited초기화
		visited[i] = false;
	BFS(1);
	printf("\n시작노드 : 3\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	BFS(3);
	printf("\n시작노드 : 5\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	BFS(5);

	printf("\n\nDFS신장트리");
	printf("\n시작노드 : 0\n");
	for (i = 0; i < num; i++)//DFS신장트리를 위해 visited초기화
		visited[i] = false;
	DFS_spanning_tree(0);
	printf("\n시작노드 : 2\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	DFS_spanning_tree(2);
	printf("\n시작노드 : 4\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	DFS_spanning_tree(4);

	printf("\n\nBFS신장트리");
	printf("\n시작노드 : 1\n");
	for (i = 0; i < num; i++)//BFS신장트리를 위해 visited초기화
		visited[i] = false;
	BFS_spanning_tree(1);
	printf("\n시작노드 : 3\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	BFS_spanning_tree(3);
	printf("\n시작노드 : 5\n");
	for (i = 0; i < num; i++)
		visited[i] = false;
	BFS_spanning_tree(5);
	printf("\n");

	//동적할당 해제
	free(queue);
	free(visited);
	for (i = 0; i < num; i++) {
		for (ptr = graph[i]; ptr != NULL; ptr = temp) {
			temp = ptr->next;
			free(ptr);
		}
	}
	free(graph);

	system("PAUSE");//실행파일에서 바로 종료되는 것을 막기위한 일시정지
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
	if (start != NULL)//graph배열에 연결된 노드 있으면 start를 temp->next로
		temp->next = *start;
	else//없으면 처음 연결하는 것이니 NULL;
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
			count++;//각 정점의 degree수를 count에 저장.
		}
		if (count > most) {//지금까지 degree수가 가장 큰거보다 클 경우
			most = count;
			node = i;//degree수가 가장 큰 정점의 번호 저장
		}
	}
	return node;
}
void addq(int data) {
	if (rear == num - 1) {
		printf("큐가 가득 찼습니다.\n");
		exit(1);
	}
	queue[++rear] = data;
}
int deleteq() {
	if (rear == front) {
		printf("큐가 비었습니다.\n");
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
	front = rear = -1;//큐사용을 위해 front와 rear초기화
	printf("%5d", v);
	visited[v] = true;
	addq(v);
	while (front != rear) {//큐가 빌때까지 반복
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
		if (!visited[w->vertex]) {//w->vertex를 방문 한 적이 없을경우
			printf("(%d,%d)", v, w->vertex);//v와 w->vertex가 에지임으로 출력
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
			if (!visited[w->vertex]) {//w->vertex를 방문 한 적이 없을경우
				printf("(%d,%d)", v, w->vertex);//v와 w->vertex가 에지임으로 출력
				addq(w->vertex);
				visited[w->vertex] = true;
			}
	}
}
