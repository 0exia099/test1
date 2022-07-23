import random
import time
A = random.sample(range(1,1000001), 10000)
#target = int(input("양수를 입력하세요: ")) #1000000

A[-1] = 0
A[-2] = -1
target = -1
start = time.time()
for x in range(len(A)-1):
    for y in range(x+1,len(A)):
        if A[x] + A[y] == target:
            end = time.time()
            print(f"A[{x}] = {A[x]} A[{y}] = {A[y]}")
            print(f"실행시간 {end-start}")
#약 7.5~8초

start = time.time()
for x in range(len(A)-1):
    if target - A[x] in A[x+1:]:
        y = A[x+1:].index(target-A[x])+x+1
        end = time.time()
        print(f"A[{x}] = {A[x]} A[{y}] = {A[y]}")
        print(f"실행시간 {end-start}")
    else:
        continue
#약 0.35초 -> 훨씬 빠르다
#in하고 index는 파이썬 코드가 아니라 c로 구성되어있다.->파이썬코드보다 c가 빠르다

start = time.time()
imap = {}
for index, value in enumerate(A): #사전을 만든다
    imap[value] = index
    
for x in range(len(A)-1):
    if target - A[x] in imap:  #사전에 있으면
        y = imap[target - A[x]] #그값
        end = time.time()
        print(f"A[{x}] = {A[x]} A[{y}] = {A[y]}")
        print(f"실행시간 {end-start}")
    else:
        continue
#약 0.003초->훨씬 빠름. 사전을 통해 찾자!!