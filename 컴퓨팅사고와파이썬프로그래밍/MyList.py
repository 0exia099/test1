"""
 Project : MyList
 Author : 심상혁
 St_ID : 21812076
 Major : 컴퓨터공학과
 Date of first create : April 5, 2023
 Major features:
   -중복되지 않는 정수형 난수의 리스트 생성하는 genRandList(L,size) 함수 제공
   -리스트의 샘플을 출력하는 printListSample(L,Per_line,sample_lines) 함수 제공
   -리스트를 뒤석는 shuffleList(L)함수 제공
 Date of last update : April 5, 2023
 Revised contesnt : 
   -v1.0 : April 5, 2023
        * first create
"""
import random
# 중복되지 않는 정수형 난수의 리스트를 생성하는 함수
def genRandList(L: list, size: int):
    # random.sample을 사용하여 중복되지 않는 난수를 생성해 L에 추가
    for i in random.sample(range(size), size):
        L.append(i)
    return

# 리스트의 샘플을 출력하는 함수
def printListSample(L: list, per_line, sample_lines):
    for j in range(sample_lines): # sample_lines 만큼의 줄 수로 출력
        # (출력한 줄 수 * 한줄에 출력 수) ~ (출력 한 줄 수 * 한줄에 출력 수 + 한줄에 출력 수) 로 이전에 출력한 줄 다음부터 현재 줄 출력
        for i in L[j*per_line:j*per_line + per_line]:
            print('{:>8d}'.format(i), end=" ")  # 8칸 우측으로 출력
        print()
    print('      . . . . . .')
    for j in range(sample_lines):  # sample_lines 만큼의 줄 수로 출력
        # L의 뒤에서 부터 (출력할 줄 수 * 한줄에 출력 수)만큼 슬라이싱 후
        # (출력한 줄 수 * 한줄에 출력 수) ~ (출력 한 줄 수 * 한줄에 출력 수 + 한줄에 출력 수) 로 이전에 출력한 줄 다음부터 현재 줄 출력
        for i in L[-per_line*sample_lines:][j*per_line:j*per_line + per_line]:
            print('{:>8d}'.format(i), end=" ")  # 8칸 우측으로 출력
        print()
    return

# 리스트를 뒤섞는 함수
def shuffleList(L):
    random.shuffle(L)   # random.shuffle을 사용하여 리스트 셔플
    return
