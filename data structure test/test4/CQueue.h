//#pragma once
#include <iostream>
using namespace std;

//@file : CQueue.h
/*���� ť ���� ������ ���� ������ C++Ŭ������ ����� ���� �������.
template������� ���� �ڷ������� ���� ť ��������.
�ٸ� template���� ���� class����� ���Ƿ� �����Ͽ� ������ϰ� cpp���Ϸ� ���� �� �����߻�*/

#ifndef _CQueue_
#define _CQueue_

template<class T>
class CQueue {
private:
	T* cqueue;//���� ť�� ����� �迭�� �����Ҵ� ���� ����
	T* pCQueue;//���Ҵ��� ���� cqueue�� ���� ������ ���� ����
	int max_size = 10;
	int front = max_size - 1;
	int rear = max_size - 1;
public:
	CQueue() {//Ŭ���� �����ڿ��� �����Ҵ�
		cqueue = new (nothrow) T[max_size];
		pCQueue = cqueue;
	}
	~CQueue() {//�Ҹ��� ����� �����Ҵ� ����
		delete[]pCQueue;
	}

	T* getcqueue() {//cqueue��ȯ
		return cqueue;
	}

	void cqueueFull() {//���� ť�� �� á����
		int j;

		cout << "���� ť�� ������� �����ϴ�.\n���� ť�� ũ�⸦ ���� ��ŵ�ϴ�." << endl;
		max_size *= 2;//���� ũ���� 2��� ���Ҵ�
		j = max_size - 1;
		cqueue = new (nothrow) T[max_size];
		if (cqueue == nullptr) {//�����Ҵ� ���н�
			cout << "�����Ҵ翡 �����߽��ϴ�. �����մϴ�." << endl;
			return;
		}

		//���� �Ҵ��� �迭�� ���� ���� �ű�
		if (rear < front) {//rear�� front���� �������
			//front�� �ڷ� �Ű� rear�� front������ ũ�⸦ �ø�
			for (int i = 0; i <= rear; i++) {//rear������ �� ����
				cqueue[i] = pCQueue[i];
			}
			for (int i = max_size / 2 - 1; i > front; i--) {//�� �迭�� front���� �������� ���� ���� �Ҵ��� �迭�� ���κп� ����
				cqueue[j--] = pCQueue[i];
			}
			front = max_size - (max_size / 2 - front);//front�� �� �迭�� ������ ������ �Ÿ���ŭ ���� �Ҵ��� �迭�� ������ ������ �Ÿ��� ��ġ
		}
		else {//front�� rear���� ���� ���rear�ڷ� ũ�⸦ �ø�
			for (int i = front + 1; i <= rear; i++) {
				cqueue[i] = pCQueue[i];
			}
		}

		delete[]pCQueue;//���� �迭 �����Ҵ� ����
		pCQueue = cqueue;
		return;
	}

	T cqueueEmpty() {//���� ť�� ��������� ����ִٴ� ��°� ��� �� ������ �� ���
		cout << "���� ť�� ����ֽ��ϴ�." << endl;
		cout << "���� ť�� ��� �� ������ �� : ";
		return cqueue[front];
	}

	void addcq(T item) {//add����
		if (front == (rear + 1) % max_size) {//���� ť�� ������ �� ���Ҵ� �� ���� ����
			cqueueFull();
		}
		rear = (rear + 1) % max_size;
		cqueue[rear] = item;
		return;
	}

	T deletecq() {//delete����
		if (front == rear)
			return cqueueEmpty();
		front = (front + 1) % max_size;
		return cqueue[front];
	}

	void prtCQueue() {//���� ť�� ���¸� ���(�迭 ��ȣ, front�� ��ġ, rear�� ��ġ, ���� ť�� ����� ��)
		cout << "���� ť" << endl;
		if (front == rear) {//front�� rear�� ���� ���(���� ť�� ����� ���) �迭�� ��ȣ�� front,rear�� ��ġ�� ���
			for (int i = 0; i < front; i++) {//front������ ���
				cout << i << endl;
			}
			//fornt, rear���
			cout << front << "<-F,R" << endl;//front�� rear�� ��ġ ǥ��
			for (int i = front + 1; i < max_size; i++) {//front���� ���
				cout << i << endl;
			}
			return;
		}

		if (front < rear) {//front�� rear���� �������
			//front������ �迭 ��ȣ ���
			for (int i = 0; i < front; i++) {
				cout << i << endl;
			}
			//front�� ��ġ ǥ��
			if (front != -1)//front�� -1�ΰ�� �迭�� �������� frontǥ��
				cout << front << "<-F" << endl;
			//front�������� ����� �� ���
			for (int i = front + 1; i < rear; i++) {//rear������ ���
				if (i < 10) {//ĭ������ ���� if��
					cout << i << "         " << cqueue[i] << endl;
				}
				else if (i < 100) {
					cout << i << "        " << cqueue[i] << endl;
				}
				else if (i < 1000) {
					cout << i << "       " << cqueue[i] << endl;
				}
				else {
					cout << i << "      " << cqueue[i] << endl;
				}
			}
			//rear���
			if (rear < 10) {
				cout << rear << "<-R      " << cqueue[rear] << endl;//rear�� ��ġ ǥ��
			}
			else if (rear < 100) {
				cout << rear << "<-R     " << cqueue[rear] << endl;
			}
			else if (rear < 1000) {
				cout << rear << "<-R    " << cqueue[rear] << endl;
			}
			else {
				cout << rear << "<-R   " << cqueue[rear] << endl;
			}
			//rear���� ���
			if (front == -1) {//front�� -1�ϰ�� �迭 �������� ǥ��
				for (int i = rear + 1; i < max_size - 1; i++) {
					cout << i << endl;
				}
				cout << max_size - 1 << "<-F" << endl;
			}
			else {//�ƴѰ�� ������ ���
				for (int i = rear + 1; i < max_size; i++) {
					cout << i << endl;
				}
			}
		}
		else {//rear�� front���� �������
			//rear������ ���
			for (int i = 0; i < rear; i++) {
				if (i < 10) {//ĭ������ ���� if��
					cout << i << "         " << cqueue[i] << endl;
				}
				else if (i < 100) {
					cout << i << "        " << cqueue[i] << endl;
				}
				else if (i < 1000) {
					cout << i << "       " << cqueue[i] << endl;
				}
				else {
					cout << i << "      " << cqueue[i] << endl;
				}
			}
			//rear���
			if (rear < 10) {
				cout << rear << "<-R      " << cqueue[rear] << endl;//rear�� ��ġ ǥ��
			}
			else if (rear < 100) {
				cout << rear << "<-R     " << cqueue[rear] << endl;
			}
			else if (rear < 1000) {
				cout << rear << "<-R    " << cqueue[rear] << endl;
			}
			else {
				cout << rear << "<-R   " << cqueue[rear] << endl;
			}
			//rear�� ���� front������ �迭��ȣ ���
			for (int i = rear + 1; i < front; i++) {
				cout << i << endl;
			}
			//front���
			cout << front << "<-F" << endl;
			//front���� ���
			for (int i = front + 1; i < max_size; i++) {
				if (i < 10) {//ĭ������ ���� if��
					cout << i << "         " << cqueue[i] << endl;
				}
				else if (i < 100) {
					cout << i << "        " << cqueue[i] << endl;
				}
				else if (i < 1000) {
					cout << i << "       " << cqueue[i] << endl;
				}
				else {
					cout << i << "      " << cqueue[i] << endl;
				}
			}
		}
		return;
	}
};

#endif
