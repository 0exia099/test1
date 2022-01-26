//#pragma once

#include <stdio.h>

//@file : Node.h
/*�Ϲ� ���Ḯ��Ʈ�� ������ �����ϴ� �Լ����� �����س��� ����
invert�� merge�Լ� ����, merge�Լ��� ���� input, insertAsc�Լ� ����*/

#ifndef _Node_
#define _Node_

struct node { int data; struct node* next; };

void insert_front(node* A, int data);//A����Ʈ�� ���� �տ� �����͸� �����ϴ� �Լ�
void print_list(node* A);//A����Ʈ�� ����ϴ� �Լ�
void insert_last(node* A, int data);//A����Ʈ�� ���� �ڿ� �����͸� �����ϴ� �Լ�
int search(node* A, int data);//A����Ʈ���� data�� ���° ��忡 �ִ��� ã�� �Լ�
int delete_front(node* A);//A����Ʈ�� ���� �� �����͸� �����ϴ� �Լ�
int delete_(node* A, int data);//A����Ʈ���� data�� ã�� �����ϴ� �Լ�(���� �����Ͱ� �������ϰ�� �ϳ��� ����)

void scan(node* A);//-1�� �Էµɶ� ���� insert_front, insert_last, search, delete_front, delete_, print_list �� ��� �������� �Է¹ް� �����Ű�� �Լ�
void free_list(node* A);//����ƮA�� �����Ҵ� �����ϴ� �Լ�

void invert(node* A);//����ƮA�� ������ �������� ����� �Լ�
struct node* merge(node* A, node* B);//����Ʈ �ΰ��� �������� ������������ �����ϴ� �Լ�

void input(node* A);//-1�� �Էµɶ� ���� ����� �����͸� �Է¹޾� ������������ ����Ʈ�� �����ϴ� �Լ�
void insertAsc(node* A, int data);//A����Ʈ�� ������������ �����͸� �����ϴ� �Լ�

#endif