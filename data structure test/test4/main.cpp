#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "CQueue.h"
using namespace std;

//@file : main.cpp
/*스택을 클래스로 정의한 Stack.h, 큐를 클래스로 정의한 Queue.h, 원형 큐를 클래스로 정의한 CQueue.h를 include하여
스택의 push, pop동작, 큐의 add, delete, 원형큐의 add, delete 를 실행하는 main소스파일.
처음 어떤 구조를 실행시킬지 입력받은 후
스택 동작을 실행하도록 하는 DoStack()함수, 큐 동작을 실행하도록 하는 DoQueue()함수, 원형 큐 동작을 실행하도록 하는 DoCQueue()함수를 사용하여
해당 동작을 실행한다. 해당 동작 종료후에 다시 어떤 구조를 실행시킬지 입력받음.
*/

void DoStack();//stack의 동작을 실행
void DoQueue();//queue의 동작을 실행
void DoCQueue();//cqueue의 동작을 실행

int main() {
	int num;
	int count = 0;

	while (true) {
		while (true) {//스택, 큐, 원형 큐 중 어떤 동작을 할지 입력받음
			cout << "\n#스택은 1, 큐는 2, 원형 큐는 3, 종료는 4를 입력해 주세요" << endl;
			cout << ">>";
			cin >> num;
			if (num != 1 && num != 2 && num != 3 && num != 4) {//해당 답 말고는 예외처리
				cout << "#다시 입력해 주세요." << endl;
			}
			else
				break;
		}
		switch (num) {
		case 1:
			DoStack();//stack의 동작을 실행하는 함수실행
			break;
		case 2:
			DoQueue();//queue의 동작을 실행하는 함수실행
			break;
		case 3:
			DoCQueue();//cqueue의 동작을 실행하는 함수실행
			break;
		case 4:
			count++;
			break;
		}
		if (count != 0) {
			break;
		}
	}

	//실행파일(exe)실행시 바로 종료되므로 일시정지추가 
	system("pause");
	return 0;
}
void DoStack() {
	int num;
	int input;
	int count = 0;

	Stack<int> stack = Stack<int>();//이번 실습에서는 간단하게 int형으로 배열 생성. 다른 자료형 필요시 변경해야함.
	if (stack.getstack() == nullptr) {//할당실패시
		cout << "동적할당에 실패했습니다. 종료합니다." << endl;
		return;
	}

	while (true) {
		while (true) {//push, pop, 스택상태 출력, 종료 입력받음
			cout << "*스택에 값을 저장하려면 1, 스택에서 값을 불러오려면 2, 스택의 상태를 보려면 3, 종료하려면 4를 입력해 주세요." << endl;
			cout << ">>";
			cin >> num;
			if (num != 1 && num != 2 && num != 3 && num != 4) {//예외처리
				cout << "*다시 입력해 주세요." << endl;
			}
			else
				break;
		}
		switch (num) {
		case 1:
			cout << "스택에 저장할 값을 입력해 주세요.\n" << ">>";
			cin >> input;
			stack.push(input);//입력받은값 push
			break;
		case 2:
			cout << "실행결과" << endl;
			cout << "->" <<stack.pop() << endl;//pop실행
			break;
		case 3:
			stack.prtStack();//스택 상태 출력
			break;
		case 4:
			count++;//종료신호
			break;
		}
		if (count != 0) {//종료신호 받을시 종료
			break;
		}
	}

	//아래는 push와 pop을 1000번 실행시켜 동작확인에 사용한 코드
	/*for(int i = 0;i<1000;i++) {
		stack.push(1);
	}
	cout << "push 1000번 실행 결과" << endl;
	stack.prtStack();

	for (int i = 0; i < 1000; i++) {
		stack.pop();
	}
	cout << "\npop 1000번 실행 결과" << endl;
	stack.prtStack();
	cout << "\npush 1000번 실행 결과와 pop 1000번 실행 결과가 출력되었습니다." << endl;*/

	return;
}
void DoQueue() {
	int num;
	int input;
	int count = 0;

	Queue<int> queue = Queue<int>();//이번 실습에서는 간단하게 int형으로 배열 생성. 다른 자료형 필요시 변경해야함.
	if (queue.getqueue() == nullptr) {
		cout << "동적할당에 실패했습니다. 종료합니다." << endl;
		return;
	}

	while (true) {
		while (true) {//add, delete, 큐 상태 출력, 종료 입력받음
			cout << "*큐에 값을 저장하려면 1, 큐에서 값을 불러오려면 2, 큐의 상태를 보려면 3, 종료하려면 4를 입력해 주세요." << endl;
			cout << ">>";
			cin >> num;
			if (num != 1 && num != 2 && num != 3 && num != 4) {//예외처리
				cout << "*다시 입력해 주세요." << endl;
			}
			else
				break;
		}
		switch (num) {
		case 1:
			cout << "큐에 저장할 값을 입력해 주세요.\n" << ">>";
			cin >> input;
			queue.addq(input);//add실행
			break;
		case 2:
			cout << "실행결과" << endl;
			cout << "->" << queue.deleteq() << endl;//delete실행
			break;
		case 3:
			queue.prtQueue();//큐 상태 출력
			break;
		case 4:
			count++;
			break;
		}
		if (count != 0) {//종료
			break;
		}
	}

	//아래는 addq와 deleteq를 1000번 실행시켜 동작확인에 사용한 코드
	/*for(int i = 0;i<1000;i++) {
		queue.addq(1);
	}
	cout << "addq 1000번 실행 결과" << endl;
	queue.prtQueue();

	for (int i = 0; i < 1000; i++) {
		queue.deleteq();
	}
	cout << "\ndeleteq 1000번 실행 결과" << endl;
	queue.prtQueue();
	cout << "\naddq 1000번 실행 결과와 deleteq 1000번 실행 결과가 출력되었습니다." << endl;*/
	return;
}
void DoCQueue() {
	int num;
	int input;
	int count = 0;

	CQueue<int> cqueue = CQueue<int>();//이번 실습에서는 간단하게 int형으로 배열 생성. 다른 자료형 필요시 변경해야함.
	if (cqueue.getcqueue() == nullptr) {
		cout << "동적할당에 실패했습니다. 종료합니다." << endl;
		return;
	}

	while (true) {
		while (true) {//add, delete, 원형큐 상태출력, 종료 입력받음
			cout << "*원형 큐에 값을 저장하려면 1, 원형 큐에서 값을 불러오려면 2, 원형 큐의 상태를 보려면 3, 종료하려면 4를 입력해 주세요." << endl;
			cout << ">>";
			cin >> num;
			if (num != 1 && num != 2 && num != 3 && num != 4) {//예외처리
				cout << "*다시 입력해 주세요." << endl;
			}
			else
				break;
		}
		switch (num) {
		case 1:
			cout << "원형 큐에 저장할 값을 입력해 주세요.\n" << ">>";
			cin >> input;
			cqueue.addcq(input);// 입력값 add
			break;
		case 2:
			cout << "실행결과" << endl;
			cout << "->" << cqueue.deletecq() << endl;//delete실행
			break;
		case 3:
			cqueue.prtCQueue();//원형 큐 상태 출력
			break;
		case 4:
			count++;
			break;
		}
		if (count != 0) {//종료
			break;
		}
	}

	//아래는 addq와 deleteq를 1000번 실행시켜 동작확인에 사용한 코드
	//for(int i = 0;i<1000;i++) {
	//	cqueue.addcq(1);
	//}
	//cout << "addcq 1000번 실행 결과" << endl;
	//cqueue.prtCQueue();
	//for (int i = 0; i < 500; i++) {//front값이 변하고도 잘 작동하는지 확인
	//	cqueue.deletecq();
	//}
	//for (int i = 0; i < 500; i++) {
	//	cqueue.addcq(1);
	//}
	//cout << "addcq 500번 추가 실행 결과" << endl;
	//cqueue.prtCQueue();
	//for (int i = 0; i < 1000; i++) {
	//	cqueue.deletecq();
	//}
	//cout << "\ndeletecq 1000번 실행 결과" << endl;
	//cqueue.prtCQueue();
	//cout << "\naddcq 1000번 실행 결과와 deletecq 1000번 실행 결과가 출력되었습니다." << endl;
	return;
}
