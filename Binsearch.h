//#pragma once
#ifndef _BINSEARCH_
#define _BINSEARCH_
#include <stdio.h>

bool binsearch(int list[], int searchnum, int left, int right, int& count);//�����˻� �� ã���� 1��ȯ, ��ã���� 0��ȯ�ϴ� �Լ�
int search(int& n, int list[], int listnum[], int& count, int& step);//binsearch�Լ� ���� �� ã�� ���� ������ ã�¼��� ������ �ְ��ϴ� ��ȣ����
//ã�� ���� ��� ������ 1����n���� ���� ���� �迭���� �����˻������ϰ� 0���� �ϴ� �Լ�
#endif