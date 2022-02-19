
//@file : main.cpp
/*선택정렬, 삽입정렬, 퀵정렬의 실행시간을 비교하는 코드.
* 랜덤으로 정렬된 배열, 오름차순으로 정렬된 배열, 내림차순으로 정렬된 배열을
* 선택정렬, 삽입정렬, 퀵정렬로 정렬하여 걸린 실행시간을 출력한다.
* 중간에 정렬이 되지않으면 종료된다.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))


void selectionSort(double list[], int n);//선택정렬
void insertSort(double list[], int n);//삽입정렬
void quickSort(double list[], int left, int right);//프로그램 7.6가 n=1000에서 부터 동작하지 않아 pivot을 중간값으로 갖는 알고리즘으로 작성.
void quickSort_reverse(double list[], int left, int right);//내림차순으로 정렬하는 함수
bool isSorted(double list[], int n);//정렬된것을 확인하는 함수

int main() {
	
	double* A = NULL;
	double* B = NULL;
	double start, stop;
	int n, i, j;
	
	for (j = 1000; j <= 1000000; j *= 10) {//1000부터 10배씩 반복
		for (n = j; n < j*10; n += j) {//j값의 *9까지 반복
			if (n > 1000000)//1000000까지 출력 후 정지
				break;
			A = (double*)malloc(sizeof(double) * n);//A배열 동적할당
			if (A == NULL) {
				fprintf(stderr, "The memory is full\n");
				exit(1);
			}

			B = (double*)malloc(sizeof(double) * n);//B배열 동적할당
			if (B == NULL) {
				fprintf(stderr, "The memory is full\n");
				exit(1);
			}

			for (i = 0; i < n; i++) {//A배열에 랜덤 순서로 실수 저장, B배열에 복사
				A[i] = (rand() / (0x7fff * 1.0)) * 100000000;
				B[i] = A[i];
			}
			printf("------------------n = %d------------------\n", n);//n표시
			//선택정렬
			printf("***선택정렬***\n");
			start = (double)clock();
			selectionSort(B, n);//랜덤 선택정렬
			stop = (double)clock();
			if (!isSorted(B, n)) {//정렬 확인
				printf("정렬에 실패했습니다.\n");
				exit(1);//정렬 실패시 종료
			}
			printf("[선택정렬 성공]랜덤->오름차순 시간 : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);
			//오름차순 정렬된것 그대로 사용
			start = (double)clock();
			selectionSort(B, n);//오름차순 선택정렬
			stop = (double)clock();
			if (!isSorted(B, n)) {//정렬 확인
				printf("정렬에 실패했습니다.\n");
				exit(1);//정렬 실패시 종료
			}
			printf("[선택정렬 성공]오름차순->오름차순 시간 : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);

			quickSort_reverse(B, 0, n - 1);//내림차순으로 변경
			for (i = n - 1; i > 0; i--) {//내림차순으로 변경되었는지 확인
				if (B[i - 1] < B[i]) {
					printf("내림차순 정렬에 실패했습니다.\n");
					exit(1);
				}
			}
			start = (double)clock();
			selectionSort(B, n);//내림차순 선택정렬
			stop = (double)clock();
			if (!isSorted(B, n)) {//정렬 확인
				printf("정렬에 실패했습니다.\n");
				exit(1);//정렬 실패시 종료
			}
			printf("[선택정렬 성공]내림차순->오름차순 시간 : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);
			///////////////////////////////////////////////////////////////////////////////////
			//삽입정렬
			printf("***삽입정렬***\n");
			for (i = 0; i < n; i++) {//B에 다시 A배열 복사
				B[i] = A[i];
			}
			start = (double)clock();
			insertSort(B, n);//랜덤 삽입정렬
			stop = (double)clock();
			if (!isSorted(B, n)) {//정렬 확인
				printf("정렬에 실패했습니다.\n");
				exit(1);//정렬 실패시 종료
			}
			printf("[삽입정렬 성공]랜덤->오름차순 시간 : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);
			//오름차순 정렬된것 그대로 사용
			start = (double)clock();
			insertSort(B, n);//오름차순 삽입정렬
			stop = (double)clock();
			if (!isSorted(B, n)) {//정렬 확인
				printf("정렬에 실패했습니다.\n");
				exit(1);//정렬 실패시 종료
			}
			printf("[삽입정렬 성공]오름차순->오름차순 시간 : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);

			quickSort_reverse(B, 0, n - 1);//내림차순으로 변경
			for (i = n - 1; i > 0; i--) {//내림차순으로 변경되었는지 확인
				if (B[i - 1] < B[i]) {
					printf("내림차순 정렬에 실패했습니다.\n");
					exit(1);
				}
			}
			start = (double)clock();
			insertSort(B, n);//내림차순 삽입정렬
			stop = (double)clock();
			if (!isSorted(B, n)) {//정렬 확인
				printf("정렬에 실패했습니다.\n");
				exit(1);//정렬 실패시 종료
			}
			printf("[삽입정렬 성공]내림차순->오름차순 시간 : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);
			/////////////////////////////////////////////////////////////////////////////////////////
			//퀵정렬
			printf("***퀵정렬***\n");
			for (i = 0; i < n; i++) {//B다시 A값 복사
				B[i] = A[i];
			}
			start = (double)clock();
			quickSort(B, 0, n - 1);//랜덤 퀵정렬
			stop = (double)clock();
			if (!isSorted(B, n)) {//정렬 확인
				printf("정렬에 실패했습니다.\n");
				exit(1);//정렬 실패시 종료
			}
			printf("[퀵정렬 성공]랜덤->오름차순 시간 : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);
			//오름차순 정렬된것 그대로 사용
			start = (double)clock();
			quickSort(B, 0, n - 1);//오름차순 퀵정렬
			stop = (double)clock();
			if (!isSorted(B, n)) {//정렬 확인
				printf("정렬에 실패했습니다.\n");
				exit(1);//정렬 실패시 종료
			}
			printf("[퀵정렬 성공]오름차순->오름차순 시간 : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);

			quickSort_reverse(B, 0, n - 1);//내림차순으로 변경
			for (i = n - 1; i > 0; i--) {//내림차순으로 변경되었는지 확인
				if (B[i - 1] < B[i]) {
					printf("내림차순 정렬에 실패했습니다.\n");
					exit(1);
				}
			}
			start = (double)clock();
			quickSort(B, 0, n - 1);//내림차순 퀵정렬
			stop = (double)clock();
			if (!isSorted(B, n)) {//정렬 확인
				printf("정렬에 실패했습니다.\n");
				exit(1);//정렬 실패시 종료
			}
			printf("[퀵정렬 성공]내림차순->오름차순 시간 : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);

			free(A);//n값 만큼의 배열 사용한것 반환
			free(B);
		}
	}
	system("PAUSE");//실행파일에서 바로 종료되는 것을 막기위한 일시정지
}
void selectionSort(double list[], int n) {//선택정렬
	int i, j, min;
	double temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[min])//최소값보다 작으면 그 값이 최소값
				min = j;
		SWAP(list[i], list[min], temp);
	}
}
void insertSort(double list[], int n) {//삽입정렬
	int i, j;
	double next;
	for (i = 1; i < n; i++) {
		next = list[i];
		for (j = i - 1; j >= 0 && next < list[j]; j--)//큰데이터 한칸씩 밀기
			list[j + 1] = list[j];//직전 값보다 작은경우 서로 교체
		list[j + 1] = next;//자신의 위치 찾으면 값 저장
	}
}

//void quickSort(double list[], int left, int right) {// 프로그램7.6
//	int i, j;
//	double temp, pivot;
//	if (left < right) {
//		i = left;
//		j = right + 1;
//		pivot = list[left];
//		do {
//			do i++; while (list[i] < pivot);
//			do j--; while (list[j] > pivot);
//			if (i < j) {
//				SWAP(list[i], list[j], temp);
//			}
//		} while (i < j);
//		SWAP(list[left], list[j], temp);
//		quickSort(list, left, j - 1);
//		quickSort(list, j + 1, right);
//	}
//}


//프로그램 7.6이 적은 배열(n=10)에서는 작동되었으나 n=1000에서는 동작하지 않아 다른방식으로 알고리즘 작성함.
//또한 pivot을 맨 처음으로 두고 하니 n=4000에서 오름차순을 오름차순으로 정렬할때 동작하지 않아 pivot을 중간 값으로 두기로 함.
void quickSort(double list[], int left, int right) {// 프로그램7.6
	int i, j;
	int pivotNum = (left + right) / 2;//중간값을 pivot으로 사용
	double temp, pivot;
	if (left < right) {
		i = left - 1;//do while은 무조건 한번 실행되기때문에 양끝보다 한칸더 주고 시작
		j = right + 1;
		pivot = list[pivotNum];
		do {
			do {
				i++;
				if (i == right + 1) {//i가 끝까지 가면 더이상 가지못하게 i--후 정지
					i--;
					break;
				}
			} while (list[i] < pivot || i == pivotNum);//pivot이 중간에 있기때문에 pivot은 정렬하지 않도록 함.
			do {
				j--;
				if (j == left - 1) {//j가 끝까지 가면 더이상 가지못하게 j++후 정지
					j++;
					break;
				}
			} while (list[j] > pivot || j == pivotNum);
			if (i < j) {
				SWAP(list[i], list[j], temp);
			}
		} while (i < j);
		//i가 pivot값보다 덜갔는데 j가 i보다 작거나 같은 경우 i와 pivot사이에 pivot보다 작은값이 없다는 뜻
		//즉 i를 포함하여 i와 pivot사이에는 pivot보다 큰값만 있으므로 i와 pivot 스왑
		//i가 pivot값보다 더 가서 j가 i보다 작거나 같으며 i위치의 값이 pivot보다 작은경우(right위치의 값이 pivot보다 작은경우)
		//pivot과 i사이에 pivot보다 큰 값이 없기 때문에 스왑
		if (i < pivotNum || list[i] < pivot) {
			SWAP(list[(left + right) / 2], list[i], temp);
			pivotNum = i;//i위치와 pivot을 스왑했으므로 i위치에 pivot값이 있음
		}
		else if (j > pivotNum || list[j] > pivot) {
			//j가 pivot값보다 덜갔는데 j가 i보다 작거나 같은 경우 j와 pivot사이에 pivot보다 큰값이 없다는 뜻
		//즉 j를 포함하여 j와 pivot사이에는 pivot보다 작은값만 있으므로 j와 pivot 스왑
		//j가 pivot값보다 더 가서 j가 i보다 작거나 같으며 j위치의 값이 pivot보다 큰경우(left위치의 값이 pivot보다 큰경우)
		//pivot과 j사이에 pivot보다 작은 값이 없기 때문에 스왑
			SWAP(list[(left + right) / 2], list[j], temp);
			pivotNum = j;//j위치와 pivot을 스왑했으므로 j위치에 pivot값이 있음
		}
		//위의 두가지 경우를 빼면 pivot의 자리는 이미 자신의 자리가 정렬된 자리이므로 자리를 옮기지 않아도 됨.
		//pivot값 위치 좌우로 재귀함수로 정렬
		if (left < pivotNum - 1)
			quickSort(list, left, pivotNum - 1);
		if (right > pivotNum + 1)
			quickSort(list, pivotNum + 1, right);
	}
}
void quickSort_reverse(double list[], int left, int right) { //내림차순으로 정렬하는 pivot을 가운데로 잡는 퀵정렬
	//거의 quickSort와 같음
	int i, j;
	int pivotNum = (left + right) / 2;//오름차순인거 내림차순으로 바꾸기위해 중간의 값을 사용하는게 효과적
	double temp, pivot;
	if (left < right) {
		i = left - 1;
		j = right + 1;
		pivot = list[pivotNum];
		do {
			do {
				i++;
				if (i == right + 1) {
					i--;
					break;
				}
			} while (list[i] > pivot || i == pivotNum);//내림차순 정렬이므로 list[i]>pivot
			do {
				j--;
				if (j == left - 1) {
					j++;
					break;
				}
			} while (list[j] < pivot || j == pivotNum);//내림차순 정렬이므로 list[j]<pivot
			if (i < j) {
				SWAP(list[i], list[j], temp);
			}
		} while (i < j);

		if (i < pivotNum || list[i] > pivot) {//내림차순 정렬이므로 그냥 quickSort 와 반대로 list[i]>pivot
			SWAP(list[pivotNum], list[i], temp);
			pivotNum = i;
		}
		else if (j > pivotNum || list[j] < pivot) {//내림차순 정렬이므로 그냥 quickSort 와 반대로 list[j]<pivot
			SWAP(list[pivotNum], list[j], temp);
			pivotNum = j;
		}
		if (left < pivotNum - 1)
			quickSort_reverse(list, left, pivotNum - 1);
		if (right > pivotNum + 1)
			quickSort_reverse(list, pivotNum + 1, right);
	}
}

bool isSorted(double list[], int n) {//정렬확인하는 함수
	int i;
	for (i = 0; i < n - 1; i++) {
		if (list[i] > list[i + 1])//역순 있으면 false리턴
			return false;
	}
	return true;
}
