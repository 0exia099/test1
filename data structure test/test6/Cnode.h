//#pragma once

#include <stdio.h>
#include "Node.h"

//@file : Cqueue.h
/*���� ���Ḯ��Ʈ�� ������ �ϱ����� �Լ����� �����س��� ����*/

#ifndef _Cnode_
#define _Cnode_

void Cinsert_front(node* A, int data);//A��������Ʈ�� ���� �տ� �����͸� �����ϴ� �Լ�
void Cprint_list(node* A);//A����Ʈ�� ����ϴ� �Լ�
void Cinsert_last(node* A, int data);//A����Ʈ�� ���� �ڿ� �����͸� �����ϴ� �Լ�
int Csearch(node* A, int data);//A����Ʈ���� data�� ���° ��忡 �ִ��� ã�� �Լ�
int Cdelete_front(node* A);//A����Ʈ�� ���� �� �����͸� �����ϴ� �Լ�
int Cdelete_(node* A, int data);//A����Ʈ���� data�� ã�� �����ϴ� �Լ�(���� �����Ͱ� �������ϰ�� �ϳ��� ����)

void Cscan(node* A);//-1�� �Էµɶ� ���� Cinsert_front, Cinsert_last, Csearch, Cdelete_front, Cdelete_, Cprint_list �� ��� �������� �Է¹ް� �����Ű�� �Լ�
void Cfree_list(node* A);//����ƮA�� �����Ҵ� �����ϴ� �Լ�(A�� ����Ʈ��head�� ����)

#endif
