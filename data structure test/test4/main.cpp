#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "CQueue.h"
using namespace std;

//@file : main.cpp
/*������ Ŭ������ ������ Stack.h, ť�� Ŭ������ ������ Queue.h, ���� ť�� Ŭ������ ������ CQueue.h�� include�Ͽ�
������ push, pop����, ť�� add, delete, ����ť�� add, delete �� �����ϴ� main�ҽ�����.
ó�� � ������ �����ų�� �Է¹��� ��
���� ������ �����ϵ��� �ϴ� DoStack()�Լ�, ť ������ �����ϵ��� �ϴ� DoQueue()�Լ�, ���� ť ������ �����ϵ��� �ϴ� DoCQueue()�Լ��� ����Ͽ�
�ش� ������ �����Ѵ�. �ش� ���� �����Ŀ� �ٽ� � ������ �����ų�� �Է¹���.
*/

void DoStack();//stack�� ������ ����
void DoQueue();//queue�� ������ ����
void DoCQueue();//cqueue�� ������ ����

int main() {
	int num;
	int count = 0;

	while (true) {
		while (true) {//����, ť, ���� ť �� � ������ ���� �Է¹���
			cout << "\n#������ 1, ť�� 2, ���� ť�� 3, ����� 4�� �Է��� �ּ���" << endl;
			cout << ">>";
			cin >> num;
			if (num != 1 && num != 2 && num != 3 && num != 4) {//�ش� �� ����� ����ó��
				cout << "#�ٽ� �Է��� �ּ���." << endl;
			}
			else
				break;
		}
		switch (num) {
		case 1:
			DoStack();//stack�� ������ �����ϴ� �Լ�����
			break;
		case 2:
			DoQueue();//queue�� ������ �����ϴ� �Լ�����
			break;
		case 3:
			DoCQueue();//cqueue�� ������ �����ϴ� �Լ�����
			break;
		case 4:
			count++;
			break;
		}
		if (count != 0) {
			break;
		}
	}

	//��������(exe)����� �ٷ� ����ǹǷ� �Ͻ������߰� 
	system("pause");
	return 0;
}
void DoStack() {
	int num;
	int input;
	int count = 0;

	Stack<int> stack = Stack<int>();//�̹� �ǽ������� �����ϰ� int������ �迭 ����. �ٸ� �ڷ��� �ʿ�� �����ؾ���.
	if (stack.getstack() == nullptr) {//�Ҵ���н�
		cout << "�����Ҵ翡 �����߽��ϴ�. �����մϴ�." << endl;
		return;
	}

	while (true) {
		while (true) {//push, pop, ���û��� ���, ���� �Է¹���
			cout << "*���ÿ� ���� �����Ϸ��� 1, ���ÿ��� ���� �ҷ������� 2, ������ ���¸� ������ 3, �����Ϸ��� 4�� �Է��� �ּ���." << endl;
			cout << ">>";
			cin >> num;
			if (num != 1 && num != 2 && num != 3 && num != 4) {//����ó��
				cout << "*�ٽ� �Է��� �ּ���." << endl;
			}
			else
				break;
		}
		switch (num) {
		case 1:
			cout << "���ÿ� ������ ���� �Է��� �ּ���.\n" << ">>";
			cin >> input;
			stack.push(input);//�Է¹����� push
			break;
		case 2:
			cout << "������" << endl;
			cout << "->" <<stack.pop() << endl;//pop����
			break;
		case 3:
			stack.prtStack();//���� ���� ���
			break;
		case 4:
			count++;//�����ȣ
			break;
		}
		if (count != 0) {//�����ȣ ������ ����
			break;
		}
	}

	//�Ʒ��� push�� pop�� 1000�� ������� ����Ȯ�ο� ����� �ڵ�
	/*for(int i = 0;i<1000;i++) {
		stack.push(1);
	}
	cout << "push 1000�� ���� ���" << endl;
	stack.prtStack();

	for (int i = 0; i < 1000; i++) {
		stack.pop();
	}
	cout << "\npop 1000�� ���� ���" << endl;
	stack.prtStack();
	cout << "\npush 1000�� ���� ����� pop 1000�� ���� ����� ��µǾ����ϴ�." << endl;*/

	return;
}
void DoQueue() {
	int num;
	int input;
	int count = 0;

	Queue<int> queue = Queue<int>();//�̹� �ǽ������� �����ϰ� int������ �迭 ����. �ٸ� �ڷ��� �ʿ�� �����ؾ���.
	if (queue.getqueue() == nullptr) {
		cout << "�����Ҵ翡 �����߽��ϴ�. �����մϴ�." << endl;
		return;
	}

	while (true) {
		while (true) {//add, delete, ť ���� ���, ���� �Է¹���
			cout << "*ť�� ���� �����Ϸ��� 1, ť���� ���� �ҷ������� 2, ť�� ���¸� ������ 3, �����Ϸ��� 4�� �Է��� �ּ���." << endl;
			cout << ">>";
			cin >> num;
			if (num != 1 && num != 2 && num != 3 && num != 4) {//����ó��
				cout << "*�ٽ� �Է��� �ּ���." << endl;
			}
			else
				break;
		}
		switch (num) {
		case 1:
			cout << "ť�� ������ ���� �Է��� �ּ���.\n" << ">>";
			cin >> input;
			queue.addq(input);//add����
			break;
		case 2:
			cout << "������" << endl;
			cout << "->" << queue.deleteq() << endl;//delete����
			break;
		case 3:
			queue.prtQueue();//ť ���� ���
			break;
		case 4:
			count++;
			break;
		}
		if (count != 0) {//����
			break;
		}
	}

	//�Ʒ��� addq�� deleteq�� 1000�� ������� ����Ȯ�ο� ����� �ڵ�
	/*for(int i = 0;i<1000;i++) {
		queue.addq(1);
	}
	cout << "addq 1000�� ���� ���" << endl;
	queue.prtQueue();

	for (int i = 0; i < 1000; i++) {
		queue.deleteq();
	}
	cout << "\ndeleteq 1000�� ���� ���" << endl;
	queue.prtQueue();
	cout << "\naddq 1000�� ���� ����� deleteq 1000�� ���� ����� ��µǾ����ϴ�." << endl;*/
	return;
}
void DoCQueue() {
	int num;
	int input;
	int count = 0;

	CQueue<int> cqueue = CQueue<int>();//�̹� �ǽ������� �����ϰ� int������ �迭 ����. �ٸ� �ڷ��� �ʿ�� �����ؾ���.
	if (cqueue.getcqueue() == nullptr) {
		cout << "�����Ҵ翡 �����߽��ϴ�. �����մϴ�." << endl;
		return;
	}

	while (true) {
		while (true) {//add, delete, ����ť �������, ���� �Է¹���
			cout << "*���� ť�� ���� �����Ϸ��� 1, ���� ť���� ���� �ҷ������� 2, ���� ť�� ���¸� ������ 3, �����Ϸ��� 4�� �Է��� �ּ���." << endl;
			cout << ">>";
			cin >> num;
			if (num != 1 && num != 2 && num != 3 && num != 4) {//����ó��
				cout << "*�ٽ� �Է��� �ּ���." << endl;
			}
			else
				break;
		}
		switch (num) {
		case 1:
			cout << "���� ť�� ������ ���� �Է��� �ּ���.\n" << ">>";
			cin >> input;
			cqueue.addcq(input);// �Է°� add
			break;
		case 2:
			cout << "������" << endl;
			cout << "->" << cqueue.deletecq() << endl;//delete����
			break;
		case 3:
			cqueue.prtCQueue();//���� ť ���� ���
			break;
		case 4:
			count++;
			break;
		}
		if (count != 0) {//����
			break;
		}
	}

	//�Ʒ��� addq�� deleteq�� 1000�� ������� ����Ȯ�ο� ����� �ڵ�
	//for(int i = 0;i<1000;i++) {
	//	cqueue.addcq(1);
	//}
	//cout << "addcq 1000�� ���� ���" << endl;
	//cqueue.prtCQueue();
	//for (int i = 0; i < 500; i++) {//front���� ���ϰ� �� �۵��ϴ��� Ȯ��
	//	cqueue.deletecq();
	//}
	//for (int i = 0; i < 500; i++) {
	//	cqueue.addcq(1);
	//}
	//cout << "addcq 500�� �߰� ���� ���" << endl;
	//cqueue.prtCQueue();
	//for (int i = 0; i < 1000; i++) {
	//	cqueue.deletecq();
	//}
	//cout << "\ndeletecq 1000�� ���� ���" << endl;
	//cqueue.prtCQueue();
	//cout << "\naddcq 1000�� ���� ����� deletecq 1000�� ���� ����� ��µǾ����ϴ�." << endl;
	return;
}
