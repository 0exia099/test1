//#pragma once

#include <stdio.h>
#include "Node.h"

//@file : Stack.h
/*���Ḯ��Ʈ�� �����ϴ� ������ ������ ���� �Լ��� ������ ����*/

#ifndef _Stack_
#define _Stack_

void stack(node* A);//-1�� �Է��Ҷ����� ���Ḯ��Ʈ�� �������� ����Ͽ� push()�� pop()�� ��� �������� �Է¹ް� �����Ű�� �Լ�
//(���̵� ������ ������ �� ������ top�� ���� push�� insert_front()�� �����Ƿ� push()�� top�� �����ϴ� ������ ����)
void push(node* A, int data);//���Ḯ��Ʈ�� �̿��� ������ push�Լ�
int pop(node* A);//���Ḯ��Ʈ�� �̿��� ������ pop�Լ�

#endif