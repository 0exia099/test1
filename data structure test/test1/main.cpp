#include <stdlib.h>
#include <time.h>
#include "Sort.h"
#include "Is_sorted.h"
#include "COMPARE.h"
#include "Binsearch.h"

int main(void)
{
	//�迭ũ�Ⱑ 1000,000�ΰ�� �Ϲ������� �����Ǿ��ִ� ���ø޸� �������� Ŀ�� ������ �߻��� �� �ִ�.
	//������Ʈ->������Ʈ�Ӽ�->��Ŀ->�ý��ۿ��� ���ø޸� ������ �ø��ų� ���������� �����Ͽ� ���ø޸��� ������ ���� �ʰ��Ͽ� �ذ��� �� �ִ�.

	int i, n, step = 1;
	int ran;//���� ���庯��
	int count = 0;//�����˻����� while�� Ƚ�� ��꿡 ���Ǵ� ī����
	int num = 0;//�����˻����� �ش���� ��ã�� �� �ش� �迭ũ�⸦ �ٽ� �����Ͽ� ã�� ���ڸ� ���Խ�Ű������ �����ϴ� ����
	int list50T[11] = { 5,50,195,500,781,5000,12548,25012,28125,37500,50000 };//�����˻����� ã�� ���� ���
	int list100T[11] = { 1,10,100,1000,10000,12500,50000,53125,75000,75195,100000 };//�����˻����� ã�� ���ڸ��
	int list500T[11] = { 50,500,5000,50000,75000,98047,100000,250000,421379,475002,500000 };//�����˻����� ã�� ���ڸ��
	int list1M[11] = { 100,1000,10000,50000,85321,100000,380521,500000,695423,800000,1000000 };//�����˻����� ã�� ���ڸ��
	double duration, durationW;
	//clock_t start, stop;//4����Ʈ���� -�����ڸ� ���� 8����Ʈ �����־� �����÷ΰ� �߻��� ���� �����Ƿ� double���� ������ clock()����.
	double start, stop, startW, stopW;//��������÷θ� �����ϱ����� double����, �����϶� �ð������ ���� ����

	printf("      n       time/worst time\n");
	for (n = 0; n <= 1000000; n += step)
	{
		int* list = new int[n];//�ش� �迭ũ�⸸ŭ �����Ҵ����� �迭����

		for (i = 0; i < n; i++) {//n���� ���� ����
			ran = (rand() << 10) ^ rand();//rand()�Լ��� 0���� 32767���� ��Ÿ���µ� �̴� 15��Ʈ�̴�.
			//�ִ� 100������ ��Ÿ�������� 21��Ʈ�� ������ �ʿ������� ���� ���� ������ ������ ���� 25��Ʈ�� �����������ϱ����.
			// rand()<<10�� ���� rand()�� 25��Ʈ���� ����� ���� ��10��Ʈ�� ä��� ���� ^rand()�� ��25��Ʈ�� ������ ����
			list[i] = ( ran % n) + 1;//1���� n������ ���� �����ϱ����� %n�� ���� +1
		}

		//ó������ �����˻����� ã�¼��� ������� �ش�迭ũ�⸦ �ٽ� �����Ű���� �߽��ϴٸ�
		//������ ã�� ���� ���� �ʰ� ������ ���� �迭�� ����� ã�¼��� ���ԵǴ� Ȯ���� �ʹ� ���� �� �ð��� ������ ������ ���Ե� �迭�� �������ʾ�
		//ó�� �ѹ��� �����Ѽ��� �迭�� ����� ã�� ���ϴ� ���� ������� ������ ã�� ���� �ֵ��� �Ͽ����ϴ�.

		switch (num) {//�����˻����� �˻��ϴ� ���� ��ã����� �ش� �迭ũ�⸦ �ٽý����ϰ� ã�� ���ڸ� ������ �迭�� �ٲ�
		case 50000://�迭ũ��50000
			for (i = 0; i < 11; i++) list[i] = list50T[i];
			num = 0;
			break;
		case 100000://�迭ũ��100000
			for (i = 0; i < 11; i++) list[i] = list100T[i];
			num = 0;
			break;
		case 500000://�迭ũ��500000
			for (i = 0; i < 11; i++) list[i] = list500T[i];
			num = 0;
			break;
		case 1000000://�迭ũ��1000000
			for (i = 0; i < 11; i++) list[i] = list1M[i];
			num = 0;
			break;
		}

		start = (double)clock();
		sort(list, n);
		stop = (double)clock();
		if (!is_sorted(list, n)) {//�ش� �迭�� ������������ ���ĵǾ����� Ȯ��
			printf("n = %d�� list�� ���ĵ��� �ʾҽ��ϴ�.\n", n);
			return 0;
		}

		Rsort(list, n);//�־��� ����� �����϶��� ����
		startW = (double)clock();
		sort(list, n);
		stopW = (double)clock();
		if (!is_sorted(list, n)) {//�ش� �迭�� ������������ ���ĵǾ����� Ȯ��
			printf("n = %d�� list�� ���ĵ��� �ʾҽ��ϴ�.\n", n);
			return 0;
		}

		duration = (stop - start) / CLOCKS_PER_SEC;
		durationW = (stopW - startW) / CLOCKS_PER_SEC;
		printf("%6d    %f/%f\n", n, duration, durationW);

		if (n == 50000) {//�迭 ũ�Ⱑ 50000�϶� �˻�
			num = search(n, list, list50T, count, step);
		}

		if (n == 100000) {//�迭 ũ�Ⱑ 100000�϶� �˻�
			num = search(n, list, list100T, count, step);
		}

		if (n == 500000) {//�迭 ũ�Ⱑ 500000�϶� �˻�
			num = search(n, list, list500T, count, step);
		}

		if (n == 1000000) {//�迭 ũ�Ⱑ 1000000�϶� �˻�
			num = search(n, list, list1M, count, step);
		}

		switch (n) {// �ش� �ڸ������� �ڸ��� �÷��� ����
		case 10:
			step = 10;
			break;
		case 100:
			step = 100;
			break;
		case 1000:
			step = 1000;
			break;
		case 10000:
			step = 10000;
			break;
		case 100000:
			step = 100000;
			break;
		}
		delete[] list;//�Ҵ��ȯ
	}
	return 0;
}