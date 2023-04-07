"""
 Project : Homework 5.1 Sorting time measurement
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : March 30, 2023
 Major features:
   -정수 n을 입력받아 중복되지 않는 정수형 난수를 n개를 가지는 리스트 생성
   -라인당 출력 갯수와 출력 줄 수를 받아 리스트의 앞과 뒤의 원소 샘플을 출력
   -리스트를 받아 병합 정렬
   -정렬에 걸리는 시간 측정
 Date of last update : March 30, 2023
 Revised contesnt : 
   -v1.0 : March 30, 2023
        * first create
"""
import random, time # 모듈 import

# 중복되지 않는 정수형 난수 생성 함수
def genBigRandList(n):
  return random.sample(range(n),n)  # random.sample()을 사용하여 중복되지 않는 0~n-1의 n개의 난수 생성

# per_line과 sample_lines에 맞는 출력을 하는 함수
def printListSample(L, per_line=10, sample_lines=2):
  for j in range(sample_lines): # sample_lines 만큼의 줄 수로 출력
    # (출력한 줄 수 * 한줄에 출력 수) ~ (출력 한 줄 수 * 한줄에 출력 수 + 한줄에 출력 수) 로 이전에 출력한 줄 다음부터 현재 줄 출력
    for i in L[j*per_line:j*per_line + per_line]:
      print('{:>8d}'.format(i), end=" ")  # 8칸 우측으로 출력
    print()
  
  for j in range(sample_lines):  # sample_lines 만큼의 줄 수로 출력
    # L의 뒤에서 부터 (출력할 줄 수 * 한줄에 출력 수)만큼 슬라이싱 후
    # (출력한 줄 수 * 한줄에 출력 수) ~ (출력 한 줄 수 * 한줄에 출력 수 + 한줄에 출력 수) 로 이전에 출력한 줄 다음부터 현재 줄 출력
    for i in L[-per_line*sample_lines:][j*per_line:j*per_line + per_line]:
      print('{:>8d}'.format(i), end=" ")  # 8칸 우측으로 출력
    print()

def _merge(L_left, L_right):
  L_res = []
  i, j = 0, 0
  len_left, len_right = len(L_left), len(L_right)
  while i < len_left and j < len_right:
    if L_left[i] < L_right[j]:  # 왼쪽이 작으면
      L_res.append(L_left[i]) # 왼쪽 원소 추가
      i += 1
    else: # 오른쪽이 작으면
      L_res.append(L_right[j])  # 오른쪽 원소 추가
      j += 1
  while i < len_left: # 왼쪽리스트가 남았으면
    L_res.append(L_left[i]) # 왼쪽의 나머지 다 추가
    i += 1
  while j < len_right:  # 오른쪽리스트가 남았으면
    L_res.append(L_right[j])  # 오른쪽의 나머지 다 추가
    j += 1
  return L_res

# 병합 정렬
def mergeSort(L):
  if len(L) < 2:  # 길이가 2 미만이면 정렬할 원소 없음. L[:] 반환
    return L[:]
  else:
    middle = len(L) // 2
    L_left = mergeSort(L[:middle])  # 처음에서 중간 병합 정렬
    L_right = mergeSort(L[middle:]) # 중간에서 마지막 병합 정렬
    return _merge(L_left, L_right)  # (정렬된 처음~중간)과 (정렬된 중간~마지막)을 병합
  
while True:
  print("\nPerformance test of merge sorting algorithm")
  size = int(input("Input size of random list L (0 to quit) = "))
  if size == 0: # 0사이즈는 종료
    break
  # 입력받은 사이즈의 정수형 난수 리스트 생성
  L = genBigRandList(size)
  # 정렬 전 난수 리스트 출력
  print("\nBefore mergeSort of L :")
  printListSample(L, 10, 2)
  # 난수 리스트 정렬 및 정렬시간 측정
  t1 = time.time()
  sorted_L = mergeSort(L) # 병합 정렬
  t2 = time.time()
  # 정렬된 리스트 출력
  print("After mergeSort of L :")
  printListSample(sorted_L, 10, 2)
  # 정렬에 걸린 시간 출력
  time_elapsed = t2 - t1
  print("Merge sorting took {} sec".format(time_elapsed))