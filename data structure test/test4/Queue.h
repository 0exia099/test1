//#pragma once
#include <iostream>
using namespace std;

//@file : Queue.h
/*ť ���� ������ ���� ������ C++Ŭ������ ����� ���� �������.
template������� ���� �ڷ������� ť ��������.
�ٸ� template���� ���� class����� ���Ƿ� �����Ͽ� ������ϰ� cpp���Ϸ� ���� �� �����߻�*/

#ifndef _Queue_
#define _Queue_

template<class T>
class Queue {
private:
	T* queue;//ť�� ����� �迭�� �����Ҵ� ���� ����
	T* pQueue;//���Ҵ��� ���� queue�� ���� ������ ���� ����
	int front = -1;
	int rear = -1;
	int max_size = 10;
public:
	Queue() {//Ŭ���� �����ڿ��� �����Ҵ�
		queue = new (nothrow) T[max_size];
		pQueue = queue;
	}
	~Queue() {//�Ҹ��� ����� �����Ҵ� ����
		delete[]pQueue;
	}
	T* getqueue() {
		return queue;
	}
	void queueFull() {//ť�� �� á����
		cout << "ť�� ������� �����ϴ�.\nť�� ũ�⸦ ���� ��ŵ�ϴ�." << endl;
		max_size *= 2;//���� ũ���� 2��� ���Ҵ�
		queue = new (nothrow) T[max_size];
		if (queue == nullptr) {//�����Ҵ� ���н�
			cout << "�����Ҵ翡 �����߽��ϴ�. �����մϴ�." << endl;
			return;
		}
		for (int i = 0; i < max_size / 2; i++) {//���� �Ҵ��� �迭�� ���� ���� �ű�
			queue[i] = pQueue[i];
		}
		delete[]pQueue;//���� �迭 �����Ҵ� ����
		pQueue = queue;
	}
	T queueEmpty() {//ť�� ��������� ����ִٴ� ��°� ��� �� ������ �� ���
		cout << "ť�� ����ֽ��ϴ�." << endl;
		cout << "ť�� ��� �� ������ �� : ";
		return queue[front];
	}
	void addq(T item) {//add����
		if (rear == max_size - 1) {
			queueFull();
		}//ť�� ������ �� ���Ҵ� �� ���� ����
		queue[++rear] = item;
		return;
	}
	T deleteq() {//delete����
		if (front == rear)
			return queueEmpty();
		return queue[++front];
	}
	void prtQueue() {//ť�� ���¸� ���(�迭 ��ȣ, front�� ��ġ, rear�� ��ġ, ť�� ����� ��)
		cout << "ť" << endl;
		if (front == rear) {//front�� rear�� ���� ���(ť�� ����� ���) �迭�� ��ȣ�� front,rear�� ��ġ�� ���
			if (front == -1) {//front�� rear�� -1�ΰ��
				cout << front << "<-F,R" << endl;//front�� rear�� ��ġ ǥ��
				for (int i = 0; i < max_size; i++) {
					cout << i << endl;
				}
			}
			else {//front�� rear�� -1�� �ƴѰ��
				for (int i = 0; i < front; i++) {//front������ ���
					cout << i << endl;
				}
				//fornt, rear���
				cout << front << "<-F,R" << endl;//front�� rear�� ��ġ ǥ��
				for (int i = front + 1; i < max_size; i++) {//front���� ���
					cout << i << endl;
				}
			}
			return;
		}
		//front������ �迭 ��ȣ ���
		for (int i = 0; i < front; i++) {
			cout << i << endl;
		}
		//front�� ��ġ ǥ��
		cout << front << "<-F" << endl;
		//front�������� ����� �� ���
		for (int i = front + 1; i < rear; i++) {//rear������ ���
			if (i < 10) {//ĭ������ ���� if��
				cout << i << "         " << queue[i] << endl;
			}
			else if (i < 100) {
				cout << i << "        " << queue[i] << endl;
			}
			else if (i < 1000) {
				cout << i << "       " << queue[i] << endl;
			}
			else {
				cout << i << "      " << queue[i] << endl;
			}
		}
		//rear���
		if (rear < 10) {
			cout << rear << "<-R      " << queue[rear] << endl;//rear�� ��ġ ǥ��
		}
		else if (rear < 100) {
			cout << rear << "<-R     " << queue[rear] << endl;
		}
		else if (rear < 1000) {
			cout << rear << "<-R    " << queue[rear] << endl;
		}
		else {
			cout << rear << "<-R   " << queue[rear] << endl;
		}
		//rear���� ���
		for (int i = rear + 1; i < max_size; i++) {
			cout << i << endl;
		}
		return;
	}
};

#endif