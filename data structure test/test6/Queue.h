//#pragma once

#include <stdio.h>
#include "Node.h"

//@file : Queue.h
/*���Ḯ��Ʈ�� �����ϴ� ť�� ������ ���� �Լ��� ������ ����*/

#ifndef _Queue_
#define _Queue_

void queue(node* A);//-1�� �Է��Ҷ����� ���Ḯ��Ʈ�� ť�� ����Ͽ� addQ()�� deleteQ()�� ��� �������� �Է¹ް� �����Ű�� �Լ�
void addQ(node* A, int data);//���Ḯ��Ʈ�� �̿��� ť�� add�Լ�
int deleteQ(node* A);//���Ḯ��Ʈ�� �̿��� ť�� delete�Լ�

#endif