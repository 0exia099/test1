//#pragma once

#include <stdio.h>

//@file : Node.h
/*일반 연결리스트의 동작을 구현하는 함수들을 선언해놓은 파일
invert와 merge함수 포함, merge함수를 위한 input, insertAsc함수 포함*/

#ifndef _Node_
#define _Node_

struct node { int data; struct node* next; };

void insert_front(node* A, int data);//A리스트의 가장 앞에 데이터를 저장하는 함수
void print_list(node* A);//A리스트를 출력하는 함수
void insert_last(node* A, int data);//A리스트의 가장 뒤에 데이터를 저장하는 함수
int search(node* A, int data);//A리스트에서 data가 몇번째 노드에 있는지 찾는 함수
int delete_front(node* A);//A리스트의 가장 앞 데이터를 삭제하는 함수
int delete_(node* A, int data);//A리스트에서 data를 찾아 삭제하는 함수(같은 데이터가 여러개일경우 하나만 삭제)

void scan(node* A);//-1이 입력될때 까지 insert_front, insert_last, search, delete_front, delete_, print_list 중 어떤걸 실행할지 입력받고 실행시키는 함수
void free_list(node* A);//리스트A를 동적할당 해제하는 함수

void invert(node* A);//리스트A의 연결을 역순으로 만드는 함수
struct node* merge(node* A, node* B);//리스트 두개를 데이터의 오름차순으로 병합하는 함수

void input(node* A);//-1이 입력될때 까지 양수의 데이터를 입력받아 오름차순으로 리스트에 저장하는 함수
void insertAsc(node* A, int data);//A리스트에 오름차순으로 데이터를 저장하는 함수

#endif