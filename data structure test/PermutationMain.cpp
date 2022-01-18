#include <stdio.h>
//@file : PermutationMain.cpp
//@date : 2021/09/19
//@author : 21812076 �ɻ���
//������ ���ϴ� �˰��� ���� �� { "GO", "BOY", "GIRL", "GIRLS" }�� ���� �˰����� ȣ���Ͽ� ���

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))//perm�Լ��� ����� ���� ��ũ��

void perm(char* list, int i, int n);//char�迭���� i��°���� n������ ������ ����ϴ� �Լ�perm ����

int main() {

	int i, j, k;
	char list[][10] = { "GO", "BOY", "GIRL", "GIRLS", NULL };//list[]�� �������� �˸������� NULL

	for (i = 0; list[i][0] != NULL; i++) {//list[][]���� ���� ����� �κ��� ������ ��½�Ű������ �ݺ���
		for (j = 0; list[i][j] != NULL; j++)
			;//j�� list[i][]���� ���� ����� ������ �迭+1 (list[i][j-1]������ ���� ����Ǿ�����)
		for (k = 0; k <= j; k++) {
			printf("%c", list[i][k]);
		}
		printf(" : ");

		perm(list[i], 0, j-1);
		printf("\n\n");
	}
	return 0;
}

void perm(char* list, int i, int n) {
	/*���� n���� ������ ���� ���� ���� ��� ���� n�� �� �ϳ��� ������Ű�� ������ ���� n - 1���� ������ ���ϴ°Ͱ� ����.
	�̶� ��� ���Ұ� ���� ���� ���� �ü� �����Ƿ� ���� n-1���� ������ n�� ���ϴ°Ͱ� ����.*/
	int j, temp;
	if (i == n) {//i==n�� ��� ������ �ϳ��̹Ƿ� �ٷ� ���
		printf("{");
		for (j = 0; j <= n; j++) {
			printf("%c", list[j]);
		}
		printf("} ");
	}
	else {//������ �ϳ� �̻��� ��� ���� n-1���� ������ ���ϱ����� ��������� ���
		for (j = i; j <= n; j++) {
			//���� n-i���� �������� �����ϴ� ���� ���� ���� n-i�� �ٲٸ� ���� n-(i+1)���� ������ ���ϴ� �Լ�ȣ��
			SWAP(list[i], list[j], temp);
			perm(list, i + 1, n);
			SWAP(list[i], list[j], temp);//�ٲ�� ���� ���� ���� ������� �ʱ�ȭ��Ų��.
		}
	}
}