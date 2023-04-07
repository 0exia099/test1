"""
 Project : Homework 5.2 Dynamic Programming for Fibonacci Series
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : March 30, 2023
 Major features:
   -시작, 끝, 간격의 정수를 입력 받은 후 해당 순서의 피보나치 수열을 출력하는 프로그램
   -동적 프로그래밍과 재귀함수를 사용하여 피보나치 수열을 계산
   -피보나치 수열 계산에 걸린 시간 측정하여 출력
 Date of last update : March 30, 2023
 Revised contesnt : 
   -v1.0 : March 30, 2023
        * first create
"""
import time

memo = dict() # 동적 프로그래밍을 위한 memo 구현
def dynFibo(n):
  if n in memo:
    return memo[n]  # 동적 프로그래밍 구조를 이용해 저장된 memo값 사용
  elif n <= 1:
    memo[n] = n
    return n  # 1보다 작으면 해당 수 리턴
  else: # memo에 없고 1보다 큰 경우
    fibo_n = dynFibo(n-1) + dynFibo(n-2)  # 피보나치 수열 계산
    memo[n] = fibo_n  # 다음 사용을 위해(동적 프로그래밍을 위해) memo에 값 저장
    return fibo_n
# 입력값을 ' '으로 구분하여 start, stop, step 얻음
(start, stop, step) = tuple(map(int, \
  input('input start, stop, step of Fibonacci series : ').split(' ')))

for n in range(start, stop + 1, step):  # 입력값 순서에 맞게 반복
  t1 = time.time()
  fibo_n = dynFibo(n) # 피보나치 수열 계산
  t2 = time.time()
  t_elapse_us = t2 - t1 # 계산에 걸린 시간측정
  # 실행결과 출력
  print('dynFibo({:3d}) = {:25d}, took {:10.2f}[micro_sec]'.format(n, fibo_n, t_elapse_us))