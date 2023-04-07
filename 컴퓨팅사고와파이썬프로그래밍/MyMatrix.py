"""
 Project : MyMatrix
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : April 5, 2023
 Major features:
   -행렬의 출력을 하는 printMtrx(name, M) 함수 제공
   -행렬의 덧셈을 하는 addMtrx(A,B) 함수 제공
   -행렬의 뺄셈을 하는 subMtrx(A,B) 함수 제공
   -행렬의 곱셈을 하는 mulMtrx(A,B) 함수 제공
 Date of last update : April 5, 2023
 Revised contesnt : 
   -v1.0 : April 5, 2023
        * first create
"""
# 행렬 출력 함수
def printMtrx(name, M):
  print('{} ='.format(name))  # 행렬 이름 출력
  for i in M:
    print(' ', end='')
    for j in i: # 행렬 이차원 리스트의 1차원 리스트씩 뽑아 원소를 출력
      print('{:>2}'.format(j), end=' ')
    print()
  return

# 행렬 덧셈 함수
def addMtrx(A, B):
  # 두 이차원 행렬 리스트의 1차원 리스트씩을 뽑아 zip을 이용하여 두 원소를 더하여 리스트 생성하고 해당 리스트들을 리스트로 감쌈
  return [[a + b for a, b in zip(A[i], B[i])] for i in range(len(A))]

# 행렬 뺄셈 함수
def subMtrx(A, B):
  # 두 이차원 행렬 리스트의 1차원 리스트씩을 뽑아 zip을 이용하여 두 원소를 빼서 리스트 생성하고 해당 리스트들을 리스트로 감쌈
  return [[a - b for a, b in zip(A[i], B[i])] for i in range(len(A))]

# 행렬 곱셈 함수
def mulMtrx(A, B):
  # 첫번째 이차원 행렬 리스트의 1차원 리스트와 두번째 이차원 행렬 리스트의 세로로의 원소들을 곱한 값들의 합으로 리스트를 생성하고 해당 리스트들을 리스트로 감쌈
  # 두번째 이차원 행렬 리스트의 세로로의 원소들은 두번째 이차원 행렬 리스트를 *로 언팩킹하여 나온 1차원 리스트들을 zip을 통해 같은 위치의 세로 원소들 끼리 묶어사용.
  return [[sum([a * b for a, b in zip(i, j)]) for j in zip(*B)] for i in A]