"""
 Project : Homework 5.3 Matrix output, arithmetic program
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : March 31, 2023
 Major features:
   -행렬을 출력하는 함수
   -행렬의 더하기 연산 함수, 행렬의 빼기 연산 함수, 행렬의 곱 연산 함수
 Date of last update : March 31, 2023
 Revised contesnt : 
   -v1.0 : March 31, 2023
        * first create
"""
def print_mtrx(name, M):  # 행렬 출력 함수
  print('{} ='.format(name))  # 행렬 이름 출력
  for i in M:
    print(' ', end='')
    for j in i: # 행렬 이차원 리스트의 1차원 리스트씩 뽑아 원소를 출력
      print('{:>2}'.format(j), end=' ')
    print()
  return

def add_mtrx(M1, M2):
  # 두 이차원 행렬 리스트의 1차원 리스트씩을 뽑아 zip을 이용하여 두 원소를 더하여 리스트 생성하고 해당 리스트들을 리스트로 감쌈
  return [[a + b for a, b in zip(M1[i], M2[i])] for i in range(len(M1))]

def sub_mtrx(M1, M2):
  # 두 이차원 행렬 리스트의 1차원 리스트씩을 뽑아 zip을 이용하여 두 원소를 빼서 리스트 생성하고 해당 리스트들을 리스트로 감쌈
  return [[a - b for a, b in zip(M1[i], M2[i])] for i in range(len(M1))]

def mul_mtrx(M1, M2):
  # 첫번째 이차원 행렬 리스트의 1차원 리스트와 두번째 이차원 행렬 리스트의 세로로의 원소들을 곱한 값들의 합으로 리스트를 생성하고 해당 리스트들을 리스트로 감쌈
  # 두번째 이차원 행렬 리스트의 세로로의 원소들은 두번째 이차원 행렬 리스트를 *로 언팩킹하여 나온 1차원 리스트들을 zip을 통해 같은 위치의 세로 원소들 끼리 묶어사용.
  return [[sum([a * b for a, b in zip(i, j)]) for j in zip(*M2)] for i in M1]

def main():
  # 초기 행렬
  A = [[1,2,3,4],[5,6,7,8],[9,10,0,1]]
  B = [[1,0,0,0],[0,1,0,0],[0,0,1,1]]
  C = [[1,0,0],[0,1,0],[0,0,1],[0,0,0]]
  print_mtrx('A',A)
  print_mtrx('B',B)
  print_mtrx('C',C)
  
  D = add_mtrx(A,B)
  print_mtrx('A + B', D)  # 행렬 덧셈 출력
  
  E = sub_mtrx(A,B)
  print_mtrx('A - B', E)  # 행렬 뺄셈 출력
  
  F = mul_mtrx(A,C)
  print_mtrx('A * C', F)  # 행렬 곱셈 출력
 
if __name__ == '__main__':
  main()