"""
 Project : Homework 6.2 Testing user-defined module MyMatrix
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : April 5, 2023
 Major features:
   -사용자 정의 모듈 MyMatrix.py를 이용하여 행렬의 출력, 덧셈, 뺄셈, 곱셈을 하는 응용 프로그램
 Date of last update : April 5, 2023
 Revised contesnt : 
   -v1.0 : April 5, 2023
        * first create
"""
import MyMatrix

# 행렬의 값 초기화
A = [[1,2,3,4], [5,6,7,8], [9,10,0,1]]
B = [[1,0,0,0], [0,1,0,0], [0,0,1,1]]
C = [[1,0,0], [0,1,0], [0,0,1], [0,0,0]]

# 각 행렬 출력
MyMatrix.printMtrx("A", A)
MyMatrix.printMtrx("B", B)
MyMatrix.printMtrx("C", C)

# 행렬의 덧셈 및 출력
D = MyMatrix.addMtrx(A, B)
MyMatrix.printMtrx("A + B", D)

# 행렬의 뺄셈 및 출력
E = MyMatrix.subMtrx(A, B)
MyMatrix.printMtrx("A - B", E)

# 행렬의 곱셈 및 출력
F = MyMatrix.mulMtrx(A, C)
MyMatrix.printMtrx("A * C", F)