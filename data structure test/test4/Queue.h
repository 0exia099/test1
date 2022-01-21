//#pragma once
#include <iostream>
using namespace std;

//@file : Queue.h
/*큐 동작 구현을 위한 동작을 C++클래스로 만들어 놓은 헤더파일.
template사용으로 여러 자료형으로 큐 생성가능.
다만 template으로 인해 class선언과 정의로 구분하여 헤더파일과 cpp파일로 나눌 시 오류발생*/

#ifndef _Queue_
#define _Queue_

template<class T>
class Queue {
private:
	T* queue;//큐에 사용할 배열을 동적할당 받을 변수
	T* pQueue;//재할당을 위해 queue의 값을 가지고 있을 변수
	int front = -1;
	int rear = -1;
	int max_size = 10;
public:
	Queue() {//클래스 생성자에서 동적할당
		queue = new (nothrow) T[max_size];
		pQueue = queue;
	}
	~Queue() {//소멸자 실행시 동적할당 해제
		delete[]pQueue;
	}
	T* getqueue() {
		return queue;
	}
	void queueFull() {//큐가 다 찼을시
		cout << "큐에 빈공간이 없습니다.\n큐의 크기를 증가 시킵니다." << endl;
		max_size *= 2;//원래 크기의 2배로 재할당
		queue = new (nothrow) T[max_size];
		if (queue == nullptr) {//동적할당 실패시
			cout << "동적할당에 실패했습니다. 종료합니다." << endl;
			return;
		}
		for (int i = 0; i < max_size / 2; i++) {//새로 할당한 배열에 전의 값들 옮김
			queue[i] = pQueue[i];
		}
		delete[]pQueue;//이전 배열 동적할당 해제
		pQueue = queue;
	}
	T queueEmpty() {//큐가 비어있을시 비었있다는 출력과 비기 전 마지막 값 출력
		cout << "큐가 비어있습니다." << endl;
		cout << "큐가 비기 전 마지막 값 : ";
		return queue[front];
	}
	void addq(T item) {//add동작
		if (rear == max_size - 1) {
			queueFull();
		}//큐가 가득찰 시 재할당 후 값을 저장
		queue[++rear] = item;
		return;
	}
	T deleteq() {//delete동작
		if (front == rear)
			return queueEmpty();
		return queue[++front];
	}
	void prtQueue() {//큐의 상태를 출력(배열 번호, front의 위치, rear의 위치, 큐에 저장된 값)
		cout << "큐" << endl;
		if (front == rear) {//front와 rear가 같을 경우(큐가 비었을 경우) 배열의 번호와 front,rear의 위치만 출력
			if (front == -1) {//front와 rear가 -1인경우
				cout << front << "<-F,R" << endl;//front와 rear의 위치 표시
				for (int i = 0; i < max_size; i++) {
					cout << i << endl;
				}
			}
			else {//front와 rear가 -1이 아닌경우
				for (int i = 0; i < front; i++) {//front전까지 출력
					cout << i << endl;
				}
				//fornt, rear출력
				cout << front << "<-F,R" << endl;//front와 rear의 위치 표시
				for (int i = front + 1; i < max_size; i++) {//front이후 출력
					cout << i << endl;
				}
			}
			return;
		}
		//front까지의 배열 번호 출력
		for (int i = 0; i < front; i++) {
			cout << i << endl;
		}
		//front의 위치 표시
		cout << front << "<-F" << endl;
		//front다음부터 저장된 값 출력
		for (int i = front + 1; i < rear; i++) {//rear전까지 출력
			if (i < 10) {//칸맞춤을 위한 if문
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
		//rear출력
		if (rear < 10) {
			cout << rear << "<-R      " << queue[rear] << endl;//rear의 위치 표시
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
		//rear이후 출력
		for (int i = rear + 1; i < max_size; i++) {
			cout << i << endl;
		}
		return;
	}
};

#endif