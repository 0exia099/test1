
//@file : main.cpp
/*��������, ��������, �������� ����ð��� ���ϴ� �ڵ�.
* �������� ���ĵ� �迭, ������������ ���ĵ� �迭, ������������ ���ĵ� �迭��
* ��������, ��������, �����ķ� �����Ͽ� �ɸ� ����ð��� ����Ѵ�.
* �߰��� ������ ���������� ����ȴ�.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))


void selectionSort(double list[], int n);//��������
void insertSort(double list[], int n);//��������
void quickSort(double list[], int left, int right);//���α׷� 7.6�� n=1000���� ���� �������� �ʾ� pivot�� �߰������� ���� �˰������� �ۼ�.
void quickSort_reverse(double list[], int left, int right);//������������ �����ϴ� �Լ�
bool isSorted(double list[], int n);//���ĵȰ��� Ȯ���ϴ� �Լ�

int main() {
	
	double* A = NULL;
	double* B = NULL;
	double start, stop;
	int n, i, j;
	
	for (j = 1000; j <= 1000000; j *= 10) {//1000���� 10�辿 �ݺ�
		for (n = j; n < j*10; n += j) {//j���� *9���� �ݺ�
			if (n > 1000000)//1000000���� ��� �� ����
				break;
			A = (double*)malloc(sizeof(double) * n);//A�迭 �����Ҵ�
			if (A == NULL) {
				fprintf(stderr, "The memory is full\n");
				exit(1);
			}

			B = (double*)malloc(sizeof(double) * n);//B�迭 �����Ҵ�
			if (B == NULL) {
				fprintf(stderr, "The memory is full\n");
				exit(1);
			}

			for (i = 0; i < n; i++) {//A�迭�� ���� ������ �Ǽ� ����, B�迭�� ����
				A[i] = (rand() / (0x7fff * 1.0)) * 100000000;
				B[i] = A[i];
			}
			printf("------------------n = %d------------------\n", n);//nǥ��
			//��������
			printf("***��������***\n");
			start = (double)clock();
			selectionSort(B, n);//���� ��������
			stop = (double)clock();
			if (!isSorted(B, n)) {//���� Ȯ��
				printf("���Ŀ� �����߽��ϴ�.\n");
				exit(1);//���� ���н� ����
			}
			printf("[�������� ����]����->�������� �ð� : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);
			//�������� ���ĵȰ� �״�� ���
			start = (double)clock();
			selectionSort(B, n);//�������� ��������
			stop = (double)clock();
			if (!isSorted(B, n)) {//���� Ȯ��
				printf("���Ŀ� �����߽��ϴ�.\n");
				exit(1);//���� ���н� ����
			}
			printf("[�������� ����]��������->�������� �ð� : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);

			quickSort_reverse(B, 0, n - 1);//������������ ����
			for (i = n - 1; i > 0; i--) {//������������ ����Ǿ����� Ȯ��
				if (B[i - 1] < B[i]) {
					printf("�������� ���Ŀ� �����߽��ϴ�.\n");
					exit(1);
				}
			}
			start = (double)clock();
			selectionSort(B, n);//�������� ��������
			stop = (double)clock();
			if (!isSorted(B, n)) {//���� Ȯ��
				printf("���Ŀ� �����߽��ϴ�.\n");
				exit(1);//���� ���н� ����
			}
			printf("[�������� ����]��������->�������� �ð� : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);
			///////////////////////////////////////////////////////////////////////////////////
			//��������
			printf("***��������***\n");
			for (i = 0; i < n; i++) {//B�� �ٽ� A�迭 ����
				B[i] = A[i];
			}
			start = (double)clock();
			insertSort(B, n);//���� ��������
			stop = (double)clock();
			if (!isSorted(B, n)) {//���� Ȯ��
				printf("���Ŀ� �����߽��ϴ�.\n");
				exit(1);//���� ���н� ����
			}
			printf("[�������� ����]����->�������� �ð� : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);
			//�������� ���ĵȰ� �״�� ���
			start = (double)clock();
			insertSort(B, n);//�������� ��������
			stop = (double)clock();
			if (!isSorted(B, n)) {//���� Ȯ��
				printf("���Ŀ� �����߽��ϴ�.\n");
				exit(1);//���� ���н� ����
			}
			printf("[�������� ����]��������->�������� �ð� : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);

			quickSort_reverse(B, 0, n - 1);//������������ ����
			for (i = n - 1; i > 0; i--) {//������������ ����Ǿ����� Ȯ��
				if (B[i - 1] < B[i]) {
					printf("�������� ���Ŀ� �����߽��ϴ�.\n");
					exit(1);
				}
			}
			start = (double)clock();
			insertSort(B, n);//�������� ��������
			stop = (double)clock();
			if (!isSorted(B, n)) {//���� Ȯ��
				printf("���Ŀ� �����߽��ϴ�.\n");
				exit(1);//���� ���н� ����
			}
			printf("[�������� ����]��������->�������� �ð� : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);
			/////////////////////////////////////////////////////////////////////////////////////////
			//������
			printf("***������***\n");
			for (i = 0; i < n; i++) {//B�ٽ� A�� ����
				B[i] = A[i];
			}
			start = (double)clock();
			quickSort(B, 0, n - 1);//���� ������
			stop = (double)clock();
			if (!isSorted(B, n)) {//���� Ȯ��
				printf("���Ŀ� �����߽��ϴ�.\n");
				exit(1);//���� ���н� ����
			}
			printf("[������ ����]����->�������� �ð� : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);
			//�������� ���ĵȰ� �״�� ���
			start = (double)clock();
			quickSort(B, 0, n - 1);//�������� ������
			stop = (double)clock();
			if (!isSorted(B, n)) {//���� Ȯ��
				printf("���Ŀ� �����߽��ϴ�.\n");
				exit(1);//���� ���н� ����
			}
			printf("[������ ����]��������->�������� �ð� : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);

			quickSort_reverse(B, 0, n - 1);//������������ ����
			for (i = n - 1; i > 0; i--) {//������������ ����Ǿ����� Ȯ��
				if (B[i - 1] < B[i]) {
					printf("�������� ���Ŀ� �����߽��ϴ�.\n");
					exit(1);
				}
			}
			start = (double)clock();
			quickSort(B, 0, n - 1);//�������� ������
			stop = (double)clock();
			if (!isSorted(B, n)) {//���� Ȯ��
				printf("���Ŀ� �����߽��ϴ�.\n");
				exit(1);//���� ���н� ����
			}
			printf("[������ ����]��������->�������� �ð� : %.3lf\n", (stop - start) / CLOCKS_PER_SEC);

			free(A);//n�� ��ŭ�� �迭 ����Ѱ� ��ȯ
			free(B);
		}
	}
	system("PAUSE");//�������Ͽ��� �ٷ� ����Ǵ� ���� �������� �Ͻ�����
}
void selectionSort(double list[], int n) {//��������
	int i, j, min;
	double temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[min])//�ּҰ����� ������ �� ���� �ּҰ�
				min = j;
		SWAP(list[i], list[min], temp);
	}
}
void insertSort(double list[], int n) {//��������
	int i, j;
	double next;
	for (i = 1; i < n; i++) {
		next = list[i];
		for (j = i - 1; j >= 0 && next < list[j]; j--)//ū������ ��ĭ�� �б�
			list[j + 1] = list[j];//���� ������ ������� ���� ��ü
		list[j + 1] = next;//�ڽ��� ��ġ ã���� �� ����
	}
}

//void quickSort(double list[], int left, int right) {// ���α׷�7.6
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


//���α׷� 7.6�� ���� �迭(n=10)������ �۵��Ǿ����� n=1000������ �������� �ʾ� �ٸ�������� �˰��� �ۼ���.
//���� pivot�� �� ó������ �ΰ� �ϴ� n=4000���� ���������� ������������ �����Ҷ� �������� �ʾ� pivot�� �߰� ������ �α�� ��.
void quickSort(double list[], int left, int right) {// ���α׷�7.6
	int i, j;
	int pivotNum = (left + right) / 2;//�߰����� pivot���� ���
	double temp, pivot;
	if (left < right) {
		i = left - 1;//do while�� ������ �ѹ� ����Ǳ⶧���� �糡���� ��ĭ�� �ְ� ����
		j = right + 1;
		pivot = list[pivotNum];
		do {
			do {
				i++;
				if (i == right + 1) {//i�� ������ ���� ���̻� �������ϰ� i--�� ����
					i--;
					break;
				}
			} while (list[i] < pivot || i == pivotNum);//pivot�� �߰��� �ֱ⶧���� pivot�� �������� �ʵ��� ��.
			do {
				j--;
				if (j == left - 1) {//j�� ������ ���� ���̻� �������ϰ� j++�� ����
					j++;
					break;
				}
			} while (list[j] > pivot || j == pivotNum);
			if (i < j) {
				SWAP(list[i], list[j], temp);
			}
		} while (i < j);
		//i�� pivot������ �����µ� j�� i���� �۰ų� ���� ��� i�� pivot���̿� pivot���� �������� ���ٴ� ��
		//�� i�� �����Ͽ� i�� pivot���̿��� pivot���� ū���� �����Ƿ� i�� pivot ����
		//i�� pivot������ �� ���� j�� i���� �۰ų� ������ i��ġ�� ���� pivot���� �������(right��ġ�� ���� pivot���� �������)
		//pivot�� i���̿� pivot���� ū ���� ���� ������ ����
		if (i < pivotNum || list[i] < pivot) {
			SWAP(list[(left + right) / 2], list[i], temp);
			pivotNum = i;//i��ġ�� pivot�� ���������Ƿ� i��ġ�� pivot���� ����
		}
		else if (j > pivotNum || list[j] > pivot) {
			//j�� pivot������ �����µ� j�� i���� �۰ų� ���� ��� j�� pivot���̿� pivot���� ū���� ���ٴ� ��
		//�� j�� �����Ͽ� j�� pivot���̿��� pivot���� �������� �����Ƿ� j�� pivot ����
		//j�� pivot������ �� ���� j�� i���� �۰ų� ������ j��ġ�� ���� pivot���� ū���(left��ġ�� ���� pivot���� ū���)
		//pivot�� j���̿� pivot���� ���� ���� ���� ������ ����
			SWAP(list[(left + right) / 2], list[j], temp);
			pivotNum = j;//j��ġ�� pivot�� ���������Ƿ� j��ġ�� pivot���� ����
		}
		//���� �ΰ��� ��츦 ���� pivot�� �ڸ��� �̹� �ڽ��� �ڸ��� ���ĵ� �ڸ��̹Ƿ� �ڸ��� �ű��� �ʾƵ� ��.
		//pivot�� ��ġ �¿�� ����Լ��� ����
		if (left < pivotNum - 1)
			quickSort(list, left, pivotNum - 1);
		if (right > pivotNum + 1)
			quickSort(list, pivotNum + 1, right);
	}
}
void quickSort_reverse(double list[], int left, int right) { //������������ �����ϴ� pivot�� ����� ��� ������
	//���� quickSort�� ����
	int i, j;
	int pivotNum = (left + right) / 2;//���������ΰ� ������������ �ٲٱ����� �߰��� ���� ����ϴ°� ȿ����
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
			} while (list[i] > pivot || i == pivotNum);//�������� �����̹Ƿ� list[i]>pivot
			do {
				j--;
				if (j == left - 1) {
					j++;
					break;
				}
			} while (list[j] < pivot || j == pivotNum);//�������� �����̹Ƿ� list[j]<pivot
			if (i < j) {
				SWAP(list[i], list[j], temp);
			}
		} while (i < j);

		if (i < pivotNum || list[i] > pivot) {//�������� �����̹Ƿ� �׳� quickSort �� �ݴ�� list[i]>pivot
			SWAP(list[pivotNum], list[i], temp);
			pivotNum = i;
		}
		else if (j > pivotNum || list[j] < pivot) {//�������� �����̹Ƿ� �׳� quickSort �� �ݴ�� list[j]<pivot
			SWAP(list[pivotNum], list[j], temp);
			pivotNum = j;
		}
		if (left < pivotNum - 1)
			quickSort_reverse(list, left, pivotNum - 1);
		if (right > pivotNum + 1)
			quickSort_reverse(list, pivotNum + 1, right);
	}
}

bool isSorted(double list[], int n) {//����Ȯ���ϴ� �Լ�
	int i;
	for (i = 0; i < n - 1; i++) {
		if (list[i] > list[i + 1])//���� ������ false����
			return false;
	}
	return true;
}