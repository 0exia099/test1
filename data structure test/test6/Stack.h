//#pragma once

#include <stdio.h>
#include "Node.h"

//@file : Stack.h
/*연결리스트로 구현하는 스택의 동작을 위한 함수를 선언한 파일*/

#ifndef _Stack_
#define _Stack_

void stack(node* A);//-1을 입력할때까지 연결리스트를 스택으로 사용하여 push()와 pop()중 어떤걸 실행할지 입력받고 실행시키는 함수
//(없이도 스택을 구현할 수 있지만 top이 없는 push는 insert_front()와 같으므로 push()는 top이 존재하는 것으로 구현)
void push(node* A, int data);//연결리스트를 이용한 스택의 push함수
int pop(node* A);//연결리스트를 이용한 스택의 pop함수

#endif