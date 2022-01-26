//#pragma once

#include <stdio.h>
#include "Node.h"

//@file : Queue.h
/*연결리스트로 구현하는 큐의 동작을 위한 함수를 선언한 파일*/

#ifndef _Queue_
#define _Queue_

void queue(node* A);//-1을 입력할때까지 연결리스트를 큐로 사용하여 addQ()와 deleteQ()중 어떤걸 실행할지 입력받고 실행시키는 함수
void addQ(node* A, int data);//연결리스트를 이용한 큐의 add함수
int deleteQ(node* A);//연결리스트를 이용한 큐의 delete함수

#endif