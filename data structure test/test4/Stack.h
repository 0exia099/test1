//#pragma once
#include <iostream>
using namespace std;

//@file : Stack.h
/*스택 동작 구현을 위한 동작을 C++클래스로 만들어 놓은 헤더파일.
template사용으로 여러 자료형으로 스택 생성가능.
다만 template으로 인해 class선언과 정의로 구분하여 헤더파일과 cpp파일로 나눌 시 오류발생*/

#ifndef _Stack_
#define _Stack_

template<class T>//class template을 사용하여 객체 생성 시 필요한 타입의 배열로 생성가능
class Stack {
private:
	T* stack;//스택에 사용할 배열을 동적할당 받을 변수
	T* pStack;//재할당을 위해 stack의 값을 가지고 있을 변수
	int top = -1;
	int max_size = 10;
public:
	Stack() {//클래스 생성자에서 동적할당
		stack = new (nothrow) T[max_size];
		pStack = stack;
	}
	~Stack() {//소멸자 실행시 동적할당 해제
		delete[]pStack;
	}

	T* getstack() {//stack반환
		return stack;
	}
	void stackFull() {//스택이 다 찼을시
		cout << "스택에 빈공간이 없습니다.\n스택의 크기를 증가 시킵니다." << endl;
		max_size *= 2;//원래 크기의 2배로 재할당
		stack = new (nothrow) T[max_size];
		if (stack == nullptr) {//동적할당 실패시
			cout << "동적할당에 실패했습니다. 종료합니다." << endl;
			return;
		}
		for (int i = 0; i < max_size / 2; i++) {//새로 할당한 배열에 전의 값들 옮김
			stack[i] = pStack[i];
		}
		delete[]pStack;//이전 배열 동적할당 해제
		pStack = stack;
	}
	T stackEmpty() {//스택이 비어있을시 비었있다는 출력과 비기 전 마지막 값 출력
		cout << "스택이 비어있습니다." << endl;
		cout << "스택이 비기 전 마지막 값 : ";
		return stack[0];
	}
	void push(T item) {//push동작
		if (top >= max_size - 1) {
			stackFull();
		}//스택이 가득찰 시 재할당 후 값을 저장
		stack[++top] = item;
		return;
	}
	T pop() {//pop동작
		if (top == -1)
			return stackEmpty();
		return stack[top--];
	}
	void prtStack() {//스택의 상태를 출력(배열 번호, top의 위치, 스택에 저장된 값)
		cout << "스택" << endl;
		if (top == -1) {//top이 -1일경우(스택이 빈 경우) 배열의 번호와 top의 위치만 출력
			cout << top << "<-top   " << endl;
			for (int i = 0; i < max_size; i++) {
				cout << i << endl;
			}
			return;
		}
		for (int i = 0; i < top; i++) {//top전까지 출력
			if (i < 10) {//칸맞춤을 위한 if문
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
		//top출력
		if (top < 10) {
			cout << top << "<-top    " << stack[top] << endl;//top의 위치 표시
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
		//top이후 출력
		for (int i = top + 1; i < max_size; i++) {
			cout << i << endl;
		}
		return;
	}
};

#endif