//#pragma once
#include <iostream>
using namespace std;

//@file : CQueue.h
/*원형 큐 동작 구현을 위한 동작을 C++클래스로 만들어 놓은 헤더파일.
template사용으로 여러 자료형으로 원형 큐 생성가능.
다만 template으로 인해 class선언과 정의로 구분하여 헤더파일과 cpp파일로 나눌 시 오류발생*/

#ifndef _CQueue_
#define _CQueue_

template<class T>
class CQueue {
private:
	T* cqueue;//원형 큐에 사용할 배열을 동적할당 받을 변수
	T* pCQueue;//재할당을 위해 cqueue의 값을 가지고 있을 변수
	int max_size = 10;
	int front = max_size - 1;
	int rear = max_size - 1;
public:
	CQueue() {//클래스 생성자에서 동적할당
		cqueue = new (nothrow) T[max_size];
		pCQueue = cqueue;
	}
	~CQueue() {//소멸자 실행시 동적할당 해제
		delete[]pCQueue;
	}

	T* getcqueue() {//cqueue반환
		return cqueue;
	}

	void cqueueFull() {//원형 큐가 다 찼을시
		int j;

		cout << "원형 큐에 빈공간이 없습니다.\n원형 큐의 크기를 증가 시킵니다." << endl;
		max_size *= 2;//원래 크기의 2배로 재할당
		j = max_size - 1;
		cqueue = new (nothrow) T[max_size];
		if (cqueue == nullptr) {//동적할당 실패시
			cout << "동적할당에 실패했습니다. 종료합니다." << endl;
			return;
		}

		//새로 할당한 배열에 전의 값들 옮김
		if (rear < front) {//rear가 front보다 작은경우
			//front를 뒤로 옮겨 rear와 front사이의 크기를 늘림
			for (int i = 0; i <= rear; i++) {//rear까지의 값 복사
				cqueue[i] = pCQueue[i];
			}
			for (int i = max_size / 2 - 1; i > front; i--) {//전 배열의 front부터 끝까지의 값을 새로 할당한 배열의 끝부분에 복사
				cqueue[j--] = pCQueue[i];
			}
			front = max_size - (max_size / 2 - front);//front는 전 배열의 끝에서 부터의 거리만큼 새로 할당한 배열의 끝에서 부터의 거리에 위치
		}
		else {//front가 rear보다 작은 경우rear뒤로 크기를 늘림
			for (int i = front + 1; i <= rear; i++) {
				cqueue[i] = pCQueue[i];
			}
		}

		delete[]pCQueue;//이전 배열 동적할당 해제
		pCQueue = cqueue;
		return;
	}

	T cqueueEmpty() {//원형 큐가 비어있을시 비었있다는 출력과 비기 전 마지막 값 출력
		cout << "원형 큐가 비어있습니다." << endl;
		cout << "원형 큐가 비기 전 마지막 값 : ";
		return cqueue[front];
	}

	void addcq(T item) {//add동작
		if (front == (rear + 1) % max_size) {//원형 큐가 가득찰 시 재할당 후 값을 저장
			cqueueFull();
		}
		rear = (rear + 1) % max_size;
		cqueue[rear] = item;
		return;
	}

	T deletecq() {//delete동작
		if (front == rear)
			return cqueueEmpty();
		front = (front + 1) % max_size;
		return cqueue[front];
	}

	void prtCQueue() {//원형 큐의 상태를 출력(배열 번호, front의 위치, rear의 위치, 원형 큐에 저장된 값)
		cout << "원형 큐" << endl;
		if (front == rear) {//front와 rear가 같을 경우(원형 큐가 비었을 경우) 배열의 번호와 front,rear의 위치만 출력
			for (int i = 0; i < front; i++) {//front전까지 출력
				cout << i << endl;
			}
			//fornt, rear출력
			cout << front << "<-F,R" << endl;//front와 rear의 위치 표시
			for (int i = front + 1; i < max_size; i++) {//front이후 출력
				cout << i << endl;
			}
			return;
		}

		if (front < rear) {//front가 rear보다 작을경우
			//front까지의 배열 번호 출력
			for (int i = 0; i < front; i++) {
				cout << i << endl;
			}
			//front의 위치 표시
			if (front != -1)//front가 -1인경우 배열의 마지막에 front표시
				cout << front << "<-F" << endl;
			//front다음부터 저장된 값 출력
			for (int i = front + 1; i < rear; i++) {//rear전까지 출력
				if (i < 10) {//칸맞춤을 위한 if문
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
			//rear출력
			if (rear < 10) {
				cout << rear << "<-R      " << cqueue[rear] << endl;//rear의 위치 표시
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
			//rear이후 출력
			if (front == -1) {//front가 -1일경우 배열 마지막에 표시
				for (int i = rear + 1; i < max_size - 1; i++) {
					cout << i << endl;
				}
				cout << max_size - 1 << "<-F" << endl;
			}
			else {//아닌경우 끝까지 출력
				for (int i = rear + 1; i < max_size; i++) {
					cout << i << endl;
				}
			}
		}
		else {//rear가 front보다 작을경우
			//rear전까지 출력
			for (int i = 0; i < rear; i++) {
				if (i < 10) {//칸맞춤을 위한 if문
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
			//rear출력
			if (rear < 10) {
				cout << rear << "<-R      " << cqueue[rear] << endl;//rear의 위치 표시
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
			//rear후 부터 front전까지 배열번호 출력
			for (int i = rear + 1; i < front; i++) {
				cout << i << endl;
			}
			//front출력
			cout << front << "<-F" << endl;
			//front이후 출력
			for (int i = front + 1; i < max_size; i++) {
				if (i < 10) {//칸맞춤을 위한 if문
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
