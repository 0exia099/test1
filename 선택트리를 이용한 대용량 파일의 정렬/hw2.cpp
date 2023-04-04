#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)
#pragma warning(disable:28182)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct selection_tree_loserNode {
	double loser;
	int loser_run;
	int winner_run;
}node;

int compare(const void* x, const void* y);
unsigned int makeRunFile();
void makeLoserTree(node** LTree, int numOfLeaf, int count);
void loserSort(FILE** runFile, node** LTree, int numOfLeaf);

int main() {
	unsigned int i;
	unsigned int count = 0;
	int numOfLeaf = 0;
	char runNum[11];
	char fileName[20] = { '\0' };
	FILE** runFile;
	node* LTree;

	count = makeRunFile();

	for (i = 1; i < count; i *= 2)
		;
	numOfLeaf = i;

	LTree = (node*)malloc(sizeof(node) * (2 * numOfLeaf));
	if (LTree == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}

	runFile = (FILE**)malloc(sizeof(FILE*) * count);
	if (runFile == NULL) {
		fprintf(stderr, "The memory is full\n");
		exit(1);
	}

	for (i = 0; i < count; i++) {
		sprintf(runNum, "%d", i);
		strcpy(fileName, "run_");
		strcat(fileName, runNum);
		strcat(fileName, ".txt");

		runFile[i] = fopen(fileName, "r");
		if (runFile[i] == NULL) {
			printf("run_%d.txt 파일을 여는데 실패했습니다.\n종료합니다.\n", i);
			exit(1);
		}
		if (fscanf(runFile[i], "%lf", &LTree[i + numOfLeaf].loser) == NULL) {
			printf("run_%d.txt 파일에서 데이터를 읽을 수 없습니다.\n종료합니다.\n", i);
			exit(1);
		}
		LTree[i + numOfLeaf].loser_run = i;
		LTree[i + numOfLeaf].winner_run = i;
	}
	makeLoserTree(&LTree, numOfLeaf, count);

	loserSort(runFile, &LTree, numOfLeaf);

	for (i = 0; i < count; i++) {
		sprintf(runNum, "%d", i);
		strcpy(fileName, "run_");
		strcat(fileName, runNum);
		strcat(fileName, ".txt");

		if (fclose(runFile[i]) != 0) {
			printf("run_%d.txt 파일을 닫는데 실패했습니다.\n종료합니다.\n", i);
			exit(1);
		}
		if (remove(fileName) != 0)
			printf("run_%d 파일 삭제 실패\n", i);
	}

	free(LTree);
	free(runFile);
	return 0;
}

int compare(const void* x, const void* y) {
	if (*(double*)x == *(double*)y)
		return 0;
	if (*(double*)x < *(double*)y)
		return -1;
	else
		return 1;
}

unsigned int makeRunFile() {
	char runNum[11];
	char fileName[20] = { '\0' };
	unsigned int count = 0;
	int i;
	double M[200];

	FILE* file;
	FILE* runFile;

	printf("파일 이름? ");
	if (scanf("%[^\n]s", fileName) == NULL) {
		printf("입력에 실패했습니다.\n종료합니다.\n");
		exit(1);
	}
	file = fopen(fileName, "r");
	if (file == NULL) {
		printf("파일을 여는데 실패했습니다. 해당 파일이 프로젝트 폴더안에 존재하는지 확인해 주십시오.\n종료합니다.\n");
		exit(1);
	}

	while (!feof(file)) {
		sprintf(runNum, "%d", count);
		strcpy(fileName, "run_");
		strcat(fileName, runNum);
		strcat(fileName, ".txt");

		runFile = fopen(fileName, "w+");
		if (runFile == NULL) {
			printf("run_%d.txt 파일을 생성할 수 없습니다.\n", count);
			exit(1);
		}
		else {
			for (i = 0; i < 200; i++) {
				if (fscanf(file, "%lf", &M[i]) == NULL) {
					printf("파일에서 데이터를 읽을 수 없습니다.\n종료합니다.\n");
					exit(1);
				}
				if (feof(file)) {
					break;
				}
			}

			qsort(M, sizeof(M) / sizeof(double), sizeof(double), compare);

			for (i = 0; i < 200 && M[i] < 1; i++) {
				fprintf(runFile, "%lf\n", M[i]);
				M[i] = 1;
			}
			if (fclose(runFile) != 0) {
				printf("run_%d.txt 파일을 닫는데 실패했습니다.\n종료합니다.\n", count);
				exit(1);
			}
		}
		count++;
	}
	if (fclose(file) != 0) {
		printf("파일을 닫는데 실패했습니다.\n종료합니다.\n");
		exit(1);
	}
	return count;
}

void makeLoserTree(node** LTree, int numOfLeaf, int count) {
	int i;
	int location = count;

	for (i = 0; i < numOfLeaf; i++) {
		(*LTree)[i].loser = 0.0;
		(*LTree)[i].loser_run = -1;
		(*LTree)[i].winner_run = -1;
	}
	for (i = count + numOfLeaf; i < numOfLeaf * 2; i++) {
		(*LTree)[i].loser = 1.0;
		(*LTree)[i].loser_run = location;
		(*LTree)[i].winner_run = location++;
	}

	location = numOfLeaf;
	while (location > 1) {
		for (i = location / 2; i < location; i++) {
			if ((*LTree)[(*LTree)[2 * i].winner_run + numOfLeaf].loser > (*LTree)[(*LTree)[2 * i + 1].winner_run + numOfLeaf].loser) {
				(*LTree)[i].loser = (*LTree)[(*LTree)[2 * i].winner_run + numOfLeaf].loser;
				(*LTree)[i].loser_run = (*LTree)[(*LTree)[2 * i].winner_run + numOfLeaf].loser_run;
				(*LTree)[i].winner_run = (*LTree)[(*LTree)[2 * i + 1].winner_run + numOfLeaf].winner_run;
			}
			else {
				(*LTree)[i].loser = (*LTree)[(*LTree)[2 * i + 1].winner_run + numOfLeaf].loser;
				(*LTree)[i].loser_run = (*LTree)[(*LTree)[2 * i + 1].winner_run + numOfLeaf].loser_run;
				(*LTree)[i].winner_run = (*LTree)[(*LTree)[2 * i].winner_run + numOfLeaf].winner_run;
			}
		}
		location /= 2;
	}
	(*LTree)[0].loser = (*LTree)[(*LTree)[1].winner_run + numOfLeaf].loser;
	(*LTree)[0].loser_run = (*LTree)[1].winner_run;
	(*LTree)[0].winner_run = (*LTree)[1].winner_run;
	return;
}

void loserSort(FILE** runFile, node** LTree, int numOfLeaf) {
	int i;
	FILE* output = fopen("output.txt", "w+");
	if (output == NULL) {
		printf("output.txt 파일을 생성할 수 없습니다.\n");
		exit(1);
	}
	if ((*LTree)[0].loser < 1)
		fprintf(output, "%lf\n", (*LTree)[0].loser);
	else {
		printf("가장 작은수가 1보다 큰 수 입니다.\n");
		exit(1);
	}

	while (true) {
		if (fscanf(runFile[(*LTree)[0].loser_run], "%lf", &(*LTree)[(*LTree)[0].loser_run + numOfLeaf].loser) == NULL) {
			printf("run_%d.txt 파일에서 데이터를 읽을 수 없습니다.\n종료합니다.\n", (*LTree)[0].loser_run);
			exit(1);
		}
		if (feof(runFile[(*LTree)[0].loser_run])) {
			(*LTree)[(*LTree)[0].loser_run + numOfLeaf].loser = 1.0;
		}
		(*LTree)[(*LTree)[0].loser_run + numOfLeaf].loser_run = (*LTree)[0].loser_run;
		(*LTree)[(*LTree)[0].loser_run + numOfLeaf].winner_run = (*LTree)[0].loser_run;

		for (i = (*LTree)[0].loser_run + numOfLeaf; i > 1; i /= 2) {
			if ((*LTree)[(*LTree)[i].winner_run + numOfLeaf].loser > (*LTree)[(i) / 2].loser) {
				(*LTree)[(i) / 2].loser = (*LTree)[(*LTree)[i].winner_run + numOfLeaf].loser;
				(*LTree)[(i) / 2].winner_run = (*LTree)[(i) / 2].loser_run;
				(*LTree)[(i) / 2].loser_run = (*LTree)[i].winner_run;
			}
			else {
				(*LTree)[(i) / 2].winner_run = (*LTree)[(*LTree)[i].winner_run + numOfLeaf].winner_run;
			}
		}
		(*LTree)[0].loser = (*LTree)[(*LTree)[1].winner_run + numOfLeaf].loser;
		(*LTree)[0].loser_run = (*LTree)[1].winner_run;
		(*LTree)[0].winner_run = (*LTree)[1].winner_run;

		if ((*LTree)[0].loser < 1)
			fprintf(output, "%lf\n", (*LTree)[0].loser);
		else
			break;
	}

	if (fclose(output) != 0) {
		printf("output.txt 파일을 닫는데 실패했습니다.\n종료합니다.\n");
		exit(1);
	}
	return;
}
