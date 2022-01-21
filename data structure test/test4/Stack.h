//#pragma once
#include <iostream>
using namespace std;

//@file : Stack.h
/*���� ���� ������ ���� ������ C++Ŭ������ ����� ���� �������.
template������� ���� �ڷ������� ���� ��������.
�ٸ� template���� ���� class����� ���Ƿ� �����Ͽ� ������ϰ� cpp���Ϸ� ���� �� �����߻�*/

#ifndef _Stack_
#define _Stack_

template<class T>//class template�� ����Ͽ� ��ü ���� �� �ʿ��� Ÿ���� �迭�� ��������
class Stack {
private:
	T* stack;//���ÿ� ����� �迭�� �����Ҵ� ���� ����
	T* pStack;//���Ҵ��� ���� stack�� ���� ������ ���� ����
	int top = -1;
	int max_size = 10;
public:
	Stack() {//Ŭ���� �����ڿ��� �����Ҵ�
		stack = new (nothrow) T[max_size];
		pStack = stack;
	}
	~Stack() {//�Ҹ��� ����� �����Ҵ� ����
		delete[]pStack;
	}

	T* getstack() {//stack��ȯ
		return stack;
	}
	void stackFull() {//������ �� á����
		cout << "���ÿ� ������� �����ϴ�.\n������ ũ�⸦ ���� ��ŵ�ϴ�." << endl;
		max_size *= 2;//���� ũ���� 2��� ���Ҵ�
		stack = new (nothrow) T[max_size];
		if (stack == nullptr) {//�����Ҵ� ���н�
			cout << "�����Ҵ翡 �����߽��ϴ�. �����մϴ�." << endl;
			return;
		}
		for (int i = 0; i < max_size / 2; i++) {//���� �Ҵ��� �迭�� ���� ���� �ű�
			stack[i] = pStack[i];
		}
		delete[]pStack;//���� �迭 �����Ҵ� ����
		pStack = stack;
	}
	T stackEmpty() {//������ ��������� ����ִٴ� ��°� ��� �� ������ �� ���
		cout << "������ ����ֽ��ϴ�." << endl;
		cout << "������ ��� �� ������ �� : ";
		return stack[0];
	}
	void push(T item) {//push����
		if (top >= max_size - 1) {
			stackFull();
		}//������ ������ �� ���Ҵ� �� ���� ����
		stack[++top] = item;
		return;
	}
	T pop() {//pop����
		if (top == -1)
			return stackEmpty();
		return stack[top--];
	}
	void prtStack() {//������ ���¸� ���(�迭 ��ȣ, top�� ��ġ, ���ÿ� ����� ��)
		cout << "����" << endl;
		if (top == -1) {//top�� -1�ϰ��(������ �� ���) �迭�� ��ȣ�� top�� ��ġ�� ���
			cout << top << "<-top   " << endl;
			for (int i = 0; i < max_size; i++) {
				cout << i << endl;
			}
			return;
		}
		for (int i = 0; i < top; i++) {//top������ ���
			if (i < 10) {//ĭ������ ���� if��
				cout << i << "         " << stack[i] << endl;
			}
			else if (i < 100) {
				cout << i << "        " << stack[i] << endl;
			}
			else if (i < 1000) {
				cout << i << "       " << stack[i] << endl;
			}
			else {
				cout << i << "      " << stack[i] << endl;
			}
		}
		//top���
		if (top < 10) {
			cout << top << "<-top    " << stack[top] << endl;//top�� ��ġ ǥ��
		}
		else if (top < 100) {
			cout << top << "<-top   " << stack[top] << endl;
		}
		else if (top < 1000) {
			cout << top << "<-top  " << stack[top] << endl;
		}
		else {
			cout << top << "<-top " << stack[top] << endl;
		}
		//top���� ���
		for (int i = top + 1; i < max_size; i++) {
			cout << i << endl;
		}
		return;
	}
};

#endif