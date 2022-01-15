#include <stdlib.h>
#include <time.h>
#include "Sort.h"
#include "Is_sorted.h"
#include "COMPARE.h"
#include "Binsearch.h"

int main(void)
{
	//배열크기가 1000,000인경우 일반적으로 설정되어있는 스택메모리 공간보다 커져 오류가 발생할 수 있다.
	//프로젝트->프로젝트속성->링커->시스템에서 스택메모리 공간을 늘리거나 전역변수로 생성하여 스택메모리의 영향을 받지 않게하여 해결할 수 있다.

	int i, n, step = 1;
	int ran;//난수 저장변수
	int count = 0;//이진검색에서 while문 횟수 계산에 사용되는 카운터
	int num = 0;//이진검색에서 해당숫자 못찾을 시 해당 배열크기를 다시 실행하여 찾는 숫자를 포함시키기위해 설정하는 변수
	int list50T[11] = { 5,50,195,500,781,5000,12548,25012,28125,37500,50000 };//이진검색에서 찾을 숫자 목록
	int list100T[11] = { 1,10,100,1000,10000,12500,50000,53125,75000,75195,100000 };//이진검색에서 찾을 숫자목록
	int list500T[11] = { 50,500,5000,50000,75000,98047,100000,250000,421379,475002,500000 };//이진검색에서 찾을 숫자목록
	int list1M[11] = { 100,1000,10000,50000,85321,100000,380521,500000,695423,800000,1000000 };//이진검색에서 찾을 숫자목록
	double duration, durationW;
	//clock_t start, stop;//4바이트값의 -연산자를 쓰고 8바이트 값에넣어 오버플로가 발생할 수도 있으므로 double형을 변수로 clock()받음.
	double start, stop, startW, stopW;//산술오버플로를 방지하기위해 double변수, 역순일때 시간계산을 위한 변수

	printf("      n       time/worst time\n");
	for (n = 0; n <= 1000000; n += step)
	{
		int* list = new int[n];//해당 배열크기만큼 동적할당으로 배열생성

		for (i = 0; i < n; i++) {//n개의 난수 생성
			ran = (rand() << 10) ^ rand();//rand()함수는 0부터 32767까지 나타내는데 이는 15비트이다.
			//최대 100만까지 나타내기위해 21비트의 난수가 필요하지만 좀더 많은 분포의 난수를 위해 25비트의 난수를생성하기로함.
			// rand()<<10을 통해 rand()를 25비트까지 만들고 뒤의 빈10비트를 채우기 위해 ^rand()로 총25비트의 난수를 생성
			list[i] = ( ran % n) + 1;//1부터 n이하의 수로 생성하기위해 %n을 한후 +1
		}

		//처음에는 이진검색에서 찾는수가 없을경우 해당배열크기를 다시 실행시키도록 했습니다만
		//강제로 찾는 수를 넣지 않고 랜덤한 수로 배열을 만드니 찾는수가 포함되는 확률이 너무 낮아 몇 시간이 지나도 모든수가 포함된 배열이 나오지않아
		//처음 한번만 랜덤한수로 배열을 만들고 찾지 못하는 수가 있을경우 강제로 찾는 수를 넣도록 하였습니다.

		switch (num) {//이진검색에서 검색하는 숫자 못찾을경우 해당 배열크기를 다시실행하고 찾는 숫자를 포함한 배열로 바꿈
		case 50000://배열크기50000
			for (i = 0; i < 11; i++) list[i] = list50T[i];
			num = 0;
			break;
		case 100000://배열크기100000
			for (i = 0; i < 11; i++) list[i] = list100T[i];
			num = 0;
			break;
		case 500000://배열크기500000
			for (i = 0; i < 11; i++) list[i] = list500T[i];
			num = 0;
			break;
		case 1000000://배열크기1000000
			for (i = 0; i < 11; i++) list[i] = list1M[i];
			num = 0;
			break;
		}

		start = (double)clock();
		sort(list, n);
		stop = (double)clock();
		if (!is_sorted(list, n)) {//해당 배열이 오름차순으로 정렬되었는지 확인
			printf("n = %d의 list가 정렬되지 않았습니다.\n", n);
			return 0;
		}

		Rsort(list, n);//최악의 경우인 역순일때의 정렬
		startW = (double)clock();
		sort(list, n);
		stopW = (double)clock();
		if (!is_sorted(list, n)) {//해당 배열이 오름차순으로 정렬되었는지 확인
			printf("n = %d의 list가 정렬되지 않았습니다.\n", n);
			return 0;
		}

		duration = (stop - start) / CLOCKS_PER_SEC;
		durationW = (stopW - startW) / CLOCKS_PER_SEC;
		printf("%6d    %f/%f\n", n, duration, durationW);

		if (n == 50000) {//배열 크기가 50000일때 검색
			num = search(n, list, list50T, count, step);
		}

		if (n == 100000) {//배열 크기가 100000일때 검색
			num = search(n, list, list100T, count, step);
		}

		if (n == 500000) {//배열 크기가 500000일때 검색
			num = search(n, list, list500T, count, step);
		}

		if (n == 1000000) {//배열 크기가 1000000일때 검색
			num = search(n, list, list1M, count, step);
		}

		switch (n) {// 해당 자릿수부터 자릿수 늘려서 실행
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
		delete[] list;//할당반환
	}
	return 0;
}