#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//filename : hw1.cpp
//author : 21812076 심상혁
//date : 2021.10.10
//스도쿠 문제 파일을 입력받은 후 후보 값이 하나인 빈칸을 채워 출력, 해답 1개 출력, 나머지 해답 출력 하는 cpp파일

//이 파일에서 스도쿠 배열의 위치를 나타내는 방식으로 2가지를 사용하는데 방식1은 x,y형식으로 0<=x,y<=8로 좌표를 표시하는 방식이고
//방식2는 스도쿠 판의 가장 왼쪽 위를 0으로 시작하여 오른쪽으로 글을 읽는 순서로 번호를 매겨 가장 오른쪽 아래는 80으로 표시하는 방식입니다.
//위치 변수가 1개라면 방식2라고 생각하시면 됩니다.
//방식2의 값이 a라고 하면 이를 방식1로 바꾸면 (a/9),(a%9)가 됩니다.


int blank = 81;//빈칸의 갯수를 가지는 변수. 0이될 경우 해답
int answerCount = 0;//출력한 해답의 수를 저장하는 변수.
int prtsign = 0;//스도쿠 첫번째 해답을 출력할지 나머지 전부출력할지 구분하는 신호를 저장하는 변수.

int** canNum;//왼쪽위부터 오른쪽아래까지 순서로 해당 칸에 할당될 수 있는 값을 가지는 동적할당 할 배열(빈칸이 아닐경우 0, 할당 불가능한 값의 번째 배열도 0)
//	//ex)오른쪽 제일 위 칸에 할당될 수 있는 수가 2, 7이면 canNum[8][0]~canNum[8][8]은 0,2,0,0,0,0,7,0,0의 값을 가짐.
//	//ex)왼쪽 제일 위 칸이 빈칸이 아니라면 canNum[0][0]~canNum[0][8]은 0,0,0,0,0,0,0,0,0의 값을 가짐.

int** blankArry;//빈칸인 위치와 들어갈 수 있는값을 저장하는 동적할당을 할 배열(canNum배열에서 빈칸인 칸과 그 칸의 할당 가능한 값만 저장된것.)
	//blankArry[][0]에는 위치가 저장되고 blankArry[][1]~blankArry[][9]에는 들어갈 수 있는값이 순서대로 저장되어있다.
	//ex)오른쪽 제일 위 칸에 할당될 수 있는 수가 2, 7이면 blankArry[][0]은 8, blankArry[][1]~blankArry[][9]은 2,7,0,0,0,0,0,0,0의 값을 가짐.

//후보 값이 하나인 빈칸을 채울때는 다른 빈칸에 같은 할당 가능한 수가 있는지를 비교해야 함으로
//같은 할당 가능한 수가 있다면 배열에서 할당 가능한 수의 위치가 같은 것이 찾기 편함으로 canNum배열을 사용한다.

//스도쿠의 나머지부분을 채울때는 할당 가능한 수를 빠르게 찾는 것이 반복횟수가 줄어들기 때문에 blankArry배열을 사용.

void ReadFile(int sudoku[][9]);//파일을 열어 sudoku배열에 저장하는 함수. 파일의 내용을 sudoku배열에 저장하지 못하면 false반환

void prtSudoku(int sudoku[][9]);//스도쿠배열을 출력하는 함수
bool canNumber(int sudoku[][9], int location, int num);//해당 숫자(num)을 location위치의 가로,세로,9칸에 같은숫자가 있는지 확인 후 없으면 true반환하는 함수

void FirstSudoku(int sudoku[][9]);//후보 값이 하나인 빈칸을 채우는 함수
void deleteRC9(int location, int value);//해당location이 빈칸이 아니게 되면 해당 칸의 가로,세로,9칸의 canNum배열에서 값(value)제거하는 함수

void SecondSudoku(int sudoku[][9]);//하나의 해답을 출력하는 함수
void DoBackT(int sudoku[][9], int num);//재귀함수를 통해 백트래킹을 하여 스도쿠 답을 출력하는 함수
void ThirdSudoku(int sudoku[][9]);//남은 나머지 해답을 모두 출력하는 함수


int main() {
	int sudoku[9][9] = { 0 };//스도쿠배열 전부 0으로 초기화(빈칸을 0으로 표시)

	ReadFile(sudoku);//파일을 읽어와 스도쿠 문제를 입력

	printf("*문제의 행렬을 예쁘게 출력 :\n\n");
	prtSudoku(sudoku);//스도쿠 배열 출력
	printf("\n");

	printf("*후보 값이 하나인 cell에 값을 할당한 결과 :\n\n");
	FirstSudoku(sudoku);//후보 값이 하나인 cell에 값 할당

	if (blank == 0) {//후보 값이 하나인 빈칸을 채운것으로 스도쿠가 완성되었을 경우 해답은 1개이다.
		prtSudoku(sudoku);//출력
		printf("\n");
		answerCount++;//해답 수 1로 증가.
		printf("해답의 수 : %d\n", answerCount);
		printf("후보 값이 하나인 cell에 값을 할당해서 해답이 나와 더 이상의 해답은 없습니다.\n");
		return 0;//종료
	}
	prtSudoku(sudoku);//출력
	printf("\n");

	SecondSudoku(sudoku);//해답을 1개 출력

	ThirdSudoku(sudoku);//나머지 해답 전부 출력

	printf("해답의 수 : %d\n", answerCount);//해답 수 출력

	return 0;
}

void ReadFile(int sudoku[][9]) {
	char fileName[20] = { '\0' };//fileName초기화
	FILE* fsudoku;//읽을 파일변수
	int i;
	int num;//읽은 파일에서 처음 정해진 값의 갯수
	int row, column, value;

	printf("파일 이름? ");
	if (scanf("%[^\n]s", fileName) == NULL) {
		printf("입력에 실패했습니다.\n종료합니다.\n");
		exit(1);
	}

	fsudoku = fopen(fileName, "r");//파일이 해당 프로젝트 폴더 안에 존재할때 열 수 있음.
	if (fsudoku == NULL) {
		printf("파일을 여는데 실패했습니다. 해당 파일이 프로젝트 폴더안에 존재하는지 확인해 주십시오.\n종료합니다.\n");
		exit(1);
	}

	if (fscanf(fsudoku, "%d", &num) == NULL) {//스도쿠 파일의 처음 정수n인 (row, column, value) 쌍의 수를 읽어온다.
		printf("파일에서 데이터를 읽을 수 없습니다.\n종료합니다.\n");
		exit(1);
	}

	blank -= num;//입력 받는 칸 수만큼 빈칸의 갯수감소

	for (i = 0; i < num; i++) {//스도쿠 파일의 정수n만큼의 (row, column, value) 쌍의 수가 있으므로 그 수만큼 읽어온다.
		if (fscanf(fsudoku, "%d %d %d", &row, &column, &value) == NULL) {
			printf("파일에서 데이터를 읽을 수 없습니다.\n종료합니다.\n");
			exit(1);
		}
		sudoku[row][column] = value;//파일의 값을 스도쿠배열에 저장
	}
	fclose(fsudoku);//파일 사용끝났으므로 fclose
	return;
}

void prtSudoku(int sudoku[][9]) {//스도쿠배열을 출력하는 함수
	int i, j;
	for (j = 0; j < 3; j++) {
		printf(" ");
		for (i = 0; i < 9; i++) {
			if (i != 0 && i % 3 == 0) {//3칸마다 세로선
				printf("| ");
			}
			if (sudoku[j][i] == 0) {//빈칸은 .으로 표시
				printf(". ");
			}
			else
				printf("%d ", sudoku[j][i]);//빈칸이 아니면 출력
		}
		printf("\n");
	}
	for (j = 1; j < 24; j++) {//세로선
		if (j % 8 == 0) {//가로선과 세로선이 만난는 부분
			printf("+");
		}
		else
			printf("-");
	}
	printf("\n");
	for (j = 3; j < 6; j++) {
		printf(" ");
		for (i = 0; i < 9; i++) {
			if (i != 0 && i % 3 == 0) {
				printf("| ");
			}
			if (sudoku[j][i] == 0) {
				printf(". ");
			}
			else
				printf("%d ", sudoku[j][i]);
		}
		printf("\n");
	}
	for (j = 1; j < 24; j++) {
		if (j % 8 == 0) {
			printf("+");
		}
		else
			printf("-");
	}
	printf("\n");
	for (j = 6; j < 9; j++) {
		printf(" ");
		for (i = 0; i < 9; i++) {
			if (i != 0 && i % 3 == 0) {
				printf("| ");
			}
			if (sudoku[j][i] == 0) {
				printf(". ");
			}
			else
				printf("%d ", sudoku[j][i]);
		}
		printf("\n");
	}
	return;
}

bool canNumber(int sudoku[][9], int location, int num) {//해당 숫자(num)을 location위치의 가로,세로,9칸에 같은숫자가 있는지 확인 후 없으면 true반환하는 함수
	int i, j;
	int count = 0;//다른 위치에 num이 존재하는 경우의 수를 저장하는 변수

	for (i = 0; i < 9; i++) {//가로 확인
		if (sudoku[location / 9][i] == num)
			count++;
	}

	for (i = 0; i < 9; i++) {//세로 확인
		if (sudoku[i][location % 9] == num)
			count++;
	}

	for (i = 0; i < 3; i++) {//n,m이 포함된 3*3칸에서 확인
		for (j = 0; j < 3; j++) {
			if (sudoku[location / 9 / 3 * 3 + i][location % 9 / 3 * 3 + j] == num)
				count++;
		}
	}

	if (count == 0) {//같은경우가 없을경우 true
		return true;
	}
	else {
		return false;
	}
}

void FirstSudoku(int sudoku[][9]) {//후보 값이 하나인 빈칸을 채우는 함수
	int i, j, k;
	int count = 0;
	int num;
	int origin[81];//후보 값이 하나인 빈칸을 채우는 과정이 실행되기 전의 스도쿠배열의 값을 가지는 배열.
	//후보 값이 하나인 빈칸을 채우는 과정 실행 후 빈칸이 채워져 혹시 또 다른 빈칸을 채울 수 있게 될수 있으므로
	//origin배열과 빈칸을 채운 sudoku배열을 확인하여 두 값이 같을때 까지 후보 값이 하나인 빈칸을 채우는 과정을 실행한다.

	canNum = (int**)calloc(81, sizeof(int*));//canNum동적할당
	
	if (canNum == NULL) {//canNum의 동적할당에 실패했을경우
		printf("동적할당에 실패했습니다. 종료합니다.\n");
		exit(1);
	}
	else {
		for (i = 0; i < 81; i++) {
			canNum[i] = (int*)calloc(9, sizeof(int*));
			if (canNum[i] == NULL) {//canNum[i]의 동적할당에 실패했을경우
				printf("동적할당에 실패했습니다. 종료합니다.\n");
				for (int j = 0; j < i; j++) {
					free(canNum[j]);//canNum[i]전까지 해제
				}
				free(canNum);//canNum 해제
				exit(1);
			}
		}
	}

	//빈칸일 경우 1~9까지 숫자 중 할당 가능한 값만을 canNum에 저장.
	for (j = 0; j < 9; j++) {
		for (i = 0; i < 9; i++) {
			if (sudoku[j][i] == 0) {
				for (k = 0; k < 9; k++) {
					if (canNumber(sudoku, j * 9 + i, k + 1)) {//canNumber함수를 통해 할당 가능한 수인지 확인
						canNum[(j * 9 + i)][k] = k + 1;
					}
				}
			}
		}
	}

	//후보 값이 하나인 빈칸을 채우는 과정 후 이로 인해 채워진 빈칸으로 또 다른 후보값이 하나인 빈칸이 생길 수 있음.
	// 무한 반복문에서 origin배열과 빈칸을 채운 sudoku배열을 확인하여 두 값이 같으면 break;
	while (true) {

		k = 0;
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				origin[k++] = sudoku[i][j];//후보 값이 하나인 빈칸을 채우는 과정이 1번 실행되기 전의 스도쿠배열의 값 저장
			}
		}

		//빈칸의 할당가능한 값이 하나인 경우 빈칸은 그 값만 할당가능
		for (i = 0; i < 81; i++) {
			count = 0;
			for (j = 0; j < 9; j++) {
				if (canNum[i][j] != 0) {//i위치의 할당가능한 값의 갯수확인
					count++;
					num = canNum[i][j];
				}
			}
			if (count == 1) {//할당 가능한 값이 1개일 경우
				sudoku[i / 9][i % 9] = num;//해당 칸에 값 저장
				blank--;//빈칸 감소
				deleteRC9(i, num);//해당 칸의 가로,세로,3*3칸에서 값 제거
			}
		}

		//3*3칸에서 빈칸중 자신만 할당가능한 수가 있는 빈칸이 있을 때 그 수가 그 칸의 값이다. 
		for (k = 0; k <= 60; k += 3) {//k는 3*3칸에서 왼쪽위칸의 위치를 나타냄
			for (j = 0; j < 9; j++) {
				count = 0;
				for (i = k; i <= k + 20; i++) {//3*3칸 안에서 왼쪽위칸부터 나머지 9칸 전부 확인
					if (canNum[i][j] != 0) {
						count++;
						num = i;
					}
					if (i == k + 2 || i == k + 11) {//3*3칸 안에서 오른쪽칸일 경우 다음행 왼쪽칸이되기 위해서+7을 해야됨 for문으로+1이됨으로 6증가
						i += 6;
					}
				}
				if (count == 1) {
					sudoku[num / 9][num % 9] = j + 1;//해당 칸에 값 저장
					blank--;//빈칸 감소
					deleteRC9(num, j + 1);//해당 칸의 가로,세로,3*3칸에서 값 제거
				}
			}
			if (k == 6 || k == 33) {//3*3의 크기를 가지는 중간크기 박스 중 오른쪽일 경우 다음 3*3크기 박스로 넘어가기위해서는 +21필요
				k += 18;//for문으로 +3이 됨으로 +18
			}
		}

		//가로 빈칸중 자신만 할당 가능한 수가 있는 빈칸이 있을 때 그 수가 그 칸의 값이다.
		for (k = 0; k < 9; k++) {
			for (i = 0; i < 9; i++) {
				count = 0;
				for (j = 0; j < 9; j++) {
					if (canNum[k * 9 + j][i] != 0) {//<k,j>위치의 할당가능한 값의 갯수확인
						count++;
						num = j;
					}
				}
				if (count == 1) {//k행에서 할당 가능한 값이 1개일 경우
					sudoku[k][num] = i + 1;//해당 칸에 값 저장
					blank--;//빈칸 감소
					deleteRC9(k * 9 + num, i + 1);//해당 칸의 가로,세로,3*3칸에서 값 제거
				}
			}
		}

		//세로 빈칸중 자신만 할당 가능한 수가 있는 빈칸이 있을 때 그 수가 그 칸의 값이다.
		for (j = 0; j < 9; j++) {
			for (i = 0; i < 9; i++) {
				count = 0;
				for (k = 0; k < 9; k++) {
					if (canNum[k * 9 + j][i] != 0) {//<k,j>위치의 할당가능한 값의 갯수확인
						count++;
						num = k;
					}
				}
				if (count == 1) {//j열에서 할당 가능한 값이 1개일 경우
					sudoku[num][j] = i + 1;//해당 칸에 값 저장
					blank--;//빈칸 감소
					deleteRC9(num * 9 + j, i + 1);//해당 칸의 가로,세로,3*3칸에서 값 제거
				}
			}
		}

		//origin과 sudoku가 같을경우 반복 끝
		k = 0;
		count = 0;
		for (i = 0; i < 9; i++) {
			for (j = 0; j < 9; j++) {
				if (origin[k++] != sudoku[i][j]) {
					count++;
				}
			}
		}
		if (count == 0)
			break;
	}
	return;
}

void deleteRC9(int location, int value) {//해당location이 빈칸이 아니게 되면 해당 칸의 가로,세로,3*3칸의 canNum배열에서 값(value)제거하는 함수
	int i, j;

	//해당칸의 모든 할당가능한 값 제거
	for (i = 0; i < 9; i++) {
		canNum[location][i] = 0;
	}

	//해당칸 가로의 할당가능 값 제거
	for (i = 9 * (location / 9); i < 9 * (location / 9) + 9; i++) {
		canNum[i][value - 1] = 0;
	}

	//해당칸 세로의 할당가능 값 제거
	for (i = location % 9; i < 81; i += 9) {
		canNum[i][value - 1] = 0;
	}

	//3*3칸에서 가로 세로를 뺀 4칸의 할당가능 값 제거
	for (i = 0; i <= 18; i += 9) {
		for (j = 0; j < 3; j++) {
			//(location / 9 / 3 * 27) + (location % 9 / 3 * 3)는 location이 포함된 3*3칸에서 왼쪽위의 위치
			canNum[(location / 9 / 3 * 27) + (location % 9 / 3 * 3) + j + i][value - 1] = 0;
		}
	}
	
	return;
}

void SecondSudoku(int sudoku[][9]) {//하나의 해답을 출력하는 함수
	int i, j, k;
	int count1 = 0;
	int count2 = 1;

	//blankArry동적할당
	blankArry = (int**)calloc(blank + 1, sizeof(int*));//blankArry의 마지막인 것을 표시(blank[][1] = 0인 것)하기위해 빈칸 수 보다1크게
	if (blankArry == NULL) {//blankArry의 동적할당에 실패했을경우
		printf("동적할당에 실패했습니다. 종료합니다.\n");
		for (i = 0; i < 81; i++) {
			free(canNum[i]);//canNum[]해제
		}
		free(canNum);//canNum해제
		exit(1);
	}
	else {
		for (i = 0; i < blank + 1; i++) {
			blankArry[i] = (int*)calloc(10, sizeof(int*));
			if (blankArry[i] == NULL) {//blankArry[i]에서 할당실패일경우
				printf("동적할당에 실패했습니다. 종료합니다.\n");
				for (k = 0; k < 81; k++) {
					free(canNum[k]);//canNum[]해제
				}
				free(canNum);//canNum해제
				for (int j = 0; j < i; j++) {
					free(blankArry[j]);//blankArry[i]전까지 해제
				}
				free(blankArry);//blankArry 해제
				exit(1);
			}
		}
	}

	//blankArry를 사용하기 위해 canNum의 값을 blankArry에 옮김.
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (sudoku[i][j] == 0) {
				blankArry[count1][0] = i * 9 + j;
				for (k = 0; k < 9; k++) {
					if (canNum[9 * i + j][k] != 0) {//canNum에서 0인값은 옮기지 않음
						blankArry[count1][count2++] = canNum[9 * i + j][k];
					}
				}
				count1++;
				count2 = 1;
			}
		}
	}

	//canNum은 더 이상 사용하지 않음으로 해제
	for (i = 0; i < 81; i++) {
		free(canNum[i]);
	}
	free(canNum);

	prtsign = 0;//해답 1만 출력하는 신호
	DoBackT(sudoku, 0);//재귀함수로 스도쿠 해답 출력

	return;
}

void DoBackT(int sudoku[][9], int num) {//재귀함수를 통해 백트래킹을 하여 스도쿠 답을 출력하는 함수
	int i;

	for (i = 1; blankArry[num][i] != 0; i++) {//빈칸의 할당 가능한 값 만을 대입해 본다.
		if (canNumber(sudoku, blankArry[num][0], blankArry[num][i])) {//해당값이 canNumber함수를 통해 확인한 후 할당가능하다면
			sudoku[blankArry[num][0] / 9][blankArry[num][0] % 9] = blankArry[num][i];//sudoku배열에 대입
			blank--;//빈칸수 -1
			if (blank == 0) {//남은 빈칸이 없을 경우 답이 완성
				if (prtsign == 0) {//해답1만 출력하는 신호
					prtsign--;
					answerCount++;//해답 수 +1
					printf("*해답 %d :\n\n", answerCount);
					prtSudoku(sudoku);
					printf("\n");
					//여기서 그냥 return을 사용할 시 sudoku에 값이 저장되어 다음 동작에서 나머지 해답이 출력되지 않음.
					//따라서 빈칸 복구 후에 return
					sudoku[blankArry[num][0] / 9][blankArry[num][0] % 9] = 0;
					blank++;//빈칸도 증가
					return;
				}
				if (prtsign == 1)//해답 1을 빼고 나머지 출력하는 신호
					prtsign++;//해답1인경우 출력하지않음(이미 해답 1의 해답 수는 증가시켰으므로 c++을 하지않는다.)
				else if (prtsign == 2) {//해답 2 부터 출력
					answerCount++;
					printf("*해답 %d :\n\n", answerCount);
					prtSudoku(sudoku);
					printf("\n");

				}
			}
			DoBackT(sudoku, num + 1);//다음 빈칸의 할당가능한 값을 대입하도록 재귀함수.
			sudoku[blankArry[num][0] / 9][blankArry[num][0] % 9] = 0;//답을 못찾았을경우 sudoku에 해당칸을 다시 빈칸으로
			blank++;//빈칸수 +1
		}
	}
	return;
}

void ThirdSudoku(int sudoku[][9]) {
	prtsign = 1;//해답 1을 빼고 나머지를 출력하는 신호
	DoBackT(sudoku, 0);//재귀함수로 스도쿠 해답 출력

	//blankArry동적할당 해제
	for (int i = 0; i < blank + 1; i++) {//DoBackT에서 blank의 수를 원래대로 돌리기 때문에 blank의 수는 후보값1개 인것을 채우고난 후와 같으므로 blankArry[]를 모두 해제가능
		free(blankArry[i]);
	}
	free(blankArry);

	return;
}
