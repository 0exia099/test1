//#pragma once

#include <stdio.h>
#include "Node.h"

//@file : Cqueue.h
/*원형 연결리스트의 동작을 하기위한 함수들을 선언해놓은 파일*/

#ifndef _Cnode_
#define _Cnode_

void Cinsert_front(node* A, int data);//A원형리스트의 가장 앞에 데이터를 저장하는 함수
void Cprint_list(node* A);//A리스트를 출력하는 함수
void Cinsert_last(node* A, int data);//A리스트의 가장 뒤에 데이터를 저장하는 함수
int Csearch(node* A, int data);//A리스트에서 data가 몇번째 노드에 있는지 찾는 함수
int Cdelete_front(node* A);//A리스트의 가장 앞 데이터를 삭제하는 함수
int Cdelete_(node* A, int data);//A리스트에서 data를 찾아 삭제하는 함수(같은 데이터가 여러개일경우 하나만 삭제)

void Cscan(node* A);//-1이 입력될때 까지 Cinsert_front, Cinsert_last, Csearch, Cdelete_front, Cdelete_, Cprint_list 중 어떤걸 실행할지 입력받고 실행시키는 함수
void Cfree_list(node* A);//리스트A를 동적할당 해제하는 함수(A는 리스트의head만 가능)

#endif
